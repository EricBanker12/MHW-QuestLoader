// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <loader.h>
#include <hooks.h>
#include "ghidra_export.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

#include <set>
#include <map>

using namespace loader;

nlohmann::json ConfigFile;

template<typename T>
inline T* offsetPtr(void* ptr, int offset) { return (T*)(((char*)ptr) + offset); }

static void* offsetPtr(void* ptr, int offset) { return offsetPtr<void>(ptr, offset); }

HOOKFUNC(AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	auto ret = originalAddPartTimer(timerMgr, index, timerStart);
	*offsetPtr<float>(ret, 0xc) = ConfigFile.value<float>("duration", 120);
	LOG(INFO) << "AddPartTimer lengthening tenderize timer " << ConfigFile.value<float>("duration", 120);
	return ret;
}

void onLoad()
{
	LOG(INFO) << "LongerTenderize Loading...";
	if (std::string(GameVersion) != "404549") {
		LOG(ERR) << "LongerTenderize: Wrong version";
		return;
	}

	ConfigFile = nlohmann::json::object();
	std::ifstream config("nativePC\\plugins\\LongerTenderizeConfig.json");
	if (config.fail()) return;

	config >> ConfigFile;
	LOG(INFO) << "LongerTenderize: Found config file";

	MH_Initialize();

	AddHook(AddPartTimer, MH::Monster_AddPartTimer);

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

