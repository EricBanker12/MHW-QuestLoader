// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <loader.h>
#include <hooks.h>
#include "ghidra_export.h"

#include <set>
#include <map>

using namespace loader;

template<typename T>
inline T* offsetPtr(void* ptr, int offset) { return (T*)(((char*)ptr) + offset); }

static void* offsetPtr(void* ptr, int offset) { return offsetPtr<void>(ptr, offset); }

HOOKFUNC(AddPartTimer, void*, void* timerMgr, unsigned int index, float timerStart)
{
	auto ret = originalAddPartTimer(timerMgr, index, timerStart);
	*offsetPtr<float>(ret, 0xc) = 120;
	LOG(INFO) << "AddPartTimer lengthening tenderize timer " << 120;
	return ret;
}

void onLoad()
{
	LOG(INFO) << "LongerTenderize Loading...";
	LOG(INFO) << GameVersion;
	if (std::string(GameVersion) != "404549") {
		LOG(ERR) << "Wrong version";
		return;
	}

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

