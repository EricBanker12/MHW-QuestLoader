// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <loader.h>

#include "ghidra_export.h"
#include "util.h"

#include <set>
#include <map>

using namespace loader;
static void* offsetPtr(void* ptr, int offset) { return offsetPtr<void>(ptr, offset); }

void showMessage(std::string message) {
	MH::Chat::ShowGameMessage(*(undefined**)MH::Chat::MainPtr, &message[0], -1, -1, 0);
}

int getReactedAction(undefined* monster, int reactionType) {
	if (MH::Monster::HasEmDmg(monster)) {
		undefined* emDmg = MH::Monster::GetEmDmg(monster);
		for (int i = 0; i < MH::Monster::EmDmg::Count(emDmg); ++i) {
			undefined* entry = MH::Monster::EmDmg::At(emDmg, i);
			LOG(INFO) << *offsetPtr<int>(entry, 0x30);
			if (*offsetPtr<int>(entry, 0x20) == reactionType) {
				return *offsetPtr<int>(entry, 0x30);
			}
		}
	}
	return 0;
}

struct monsterData {
	int clawExtendAction = -1;
	int turnClawActions[2] = { -1, -1 };
};

static std::map<void*, monsterData> data;

CreateHook(MH::Monster::CanClawTurn, TurnClawCheck, bool, void* monster)
{
	int action = *offsetPtr<int>(monster, 0x61c8 + 0xb0);
	auto mdata = data[monster];
	if (action == mdata.clawExtendAction
		|| action == mdata.turnClawActions[0]
		|| action == mdata.turnClawActions[1]) {
		return true;
	}
	return false;
}

CreateHook(MH::Monster::SoftenTimers::AddWoundTimer, AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	void* monster = offsetPtr<void>(timerMgr, -0x1c3f0);
	int action = *offsetPtr<int>(monster, 0x61c8 + 0xb0);
	LOG(INFO) << SHOW(action);
	if (action != data[monster].clawExtendAction) {
		showMessage("Wound resisted.");
		return nullptr;
	}
	auto ret = originalAddPartTimer(timerMgr, index, timerStart);
	*offsetPtr<float>(ret, 0xc) = 3000;
	return ret;
}

void onLoad()
{
	LOG(INFO) << "ClutchRework Loading...";
	LOG(INFO) << GameVersion;
	if (std::string(GameVersion) != "404549") {
		LOG(ERR) << "ClutchRework: Wrong version";
		return;
	}

	MH_Initialize();

	QueueHook(AddPartTimer);
	QueueHook(TurnClawCheck);
	HookLambda(MH::Monster::LaunchAction, [](auto monster, auto id)
		{
			auto ret = original(monster, id);
			char* monsterName = offsetPtr<char>(monster, 0x7741);
			if (monsterName[2] == '0' || monsterName[2] == '1') {
				if (data[monster].clawExtendAction == -1) {
					data[monster].clawExtendAction = getReactedAction(monster, 172);
					LOG(INFO) << SHOW(data[monster].clawExtendAction);
					data[monster].turnClawActions[0] = getReactedAction(monster, 164);
					data[monster].turnClawActions[1] = getReactedAction(monster, 165);
				}
			}
			return ret;
		});

	HookLambda(MH::Monster::dtor, [](auto monster)
		{
			data.erase(monster);
			return original(monster);
		});


	MH_ApplyQueued();

	LOG(INFO) << "DONE !";
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        onLoad();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

