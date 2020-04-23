// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <loader.h>

#include "ghidra_export.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <tlhelp32.h>
#include "util.h"

#include <set>
#include <map>

using namespace loader;

nlohmann::json ConfigFile;

HANDLE phandle;
DWORD_PTR playersPtr = 0x145104b58;
DWORD_PTR playersAddress;

static void* offsetPtr(void* ptr, int offset) { return offsetPtr<void>(ptr, offset); }

// https://stackoverflow.com/a/55030118
DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

int countPlayers()
{
	// check memory for other players
	if (ConfigFile.value<bool>("disableMultiplayerCheck", false)) {
		return false;
	}
	if (!phandle or !playersAddress) {
		if (phandle) {
			CloseHandle(phandle);
		}
		DWORD procID = FindProcessId(L"MonsterHunterWorld.exe");
		phandle = OpenProcess(PROCESS_VM_READ, FALSE, procID);
		ReadProcessMemory(phandle, (LPCVOID)playersPtr, &playersAddress, sizeof(playersAddress), 0);
	}
	int counter = 0;
	for (int i = 0; i < 4; i += 1) {
		char player;
		int playerOffset = 0x21 * i;
		ReadProcessMemory(phandle, (LPCVOID)(playersAddress+0x532ED+playerOffset), &player, sizeof(player), 0);
		if (player != 0x0) {
			counter += 1;
		}
	}
	// bugfix for solo arena
	if (counter == 0) {
		counter = 1;
	}
	return counter;
}

CreateHook(MH::Monster::SoftenTimers::AddWoundTimer, AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	auto ret = original(timerMgr, index, timerStart);
	
	int playerCount = countPlayers();
	char playerCountStr [16];
	sprintf_s(playerCountStr, sizeof(playerCountStr), "%d-player", playerCount);

	nlohmann::json config = ConfigFile.value<nlohmann::json>(playerCountStr, nlohmann::json::object());

	bool enabled = config.value<bool>("enabled", false);
	if (enabled) {
		float duration = config.value<float>("duration", 120);
		*offsetPtr<float>(ret, 0xc) = duration;
		LOG(INFO) << "LongerTenderize: lengthening tenderize timer " << duration;
	}
	else {
		LOG(INFO) << "LongerTenderize: " << playerCountStr << " is disabled.";
	}
	return ret;
}

void onLoad()
{
	if (std::string(GameVersion) != "410014") {
		LOG(ERR) << "LongerTenderize: Wrong version";
		return;
	}

	ConfigFile = nlohmann::json::object();
	std::ifstream config("nativePC\\plugins\\LongerTenderizeConfig.json");
	if (config.fail()) return;

	config >> ConfigFile;
	LOG(INFO) << "LongerTenderize: Found config file";

	MH_Initialize();

	QueueHook(AddPartTimer);
	// HookLambda(MH::GameVersion::CalcNum, []() -> undefined8 {return 1404549; });

	MH_ApplyQueued();
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

