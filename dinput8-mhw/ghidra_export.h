
#pragma once
typedef unsigned char undefined; 
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned long long undefined8;
typedef unsigned char byte; 
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef unsigned int uint;

namespace MH {
  static undefined8(*Monster_Spawn)() = (undefined8(*)())0x1546dcd30;
  static undefined8(*QuestUI_DisplayQuests)() = (undefined8(*)())0x14b16ed00;
  static undefined8(*String_Unkn)() = (undefined8(*)())0x156290820;
  static bool(*Quest_CheckComplete)(longlong,int) = (bool(*)(longlong,int))0x14b816d90;
  static undefined8(*Quest_Category)() = (undefined8(*)())0x1542b6870;
  static bool(*Quest_CheckCommon)(longlong,uint) = (bool(*)(longlong,uint))0x151cf55b0;
  static void *Quest_OptionalList = (void*)0x1430820d0;
  static undefined8(*Monster_Construct)() = (undefined8(*)())0x154e90c10;
  static undefined8(*Monster_CreateFilePaths)() = (undefined8(*)())0x154f2b050;
  static bool(*Monster_LaunchAction)(undefined *,uint) = (bool(*)(undefined *,uint))0x154f10e30;
  static bool(*Monster_CanClawTurn)(longlong) = (bool(*)(longlong))0x154ed4e10;
  static bool(*Quest_UnknownCategoryCheck_)(undefined8) = (bool(*)(undefined8))0x1541cc440;
  static undefined8(*Quest_AtIndex)() = (undefined8(*)())0x151ce9920;
  namespace File {
    static undefined8(*NativePCCheck)(undefined,undefined,undefined,undefined,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined8))0x15624f080;
    static undefined8(*FilePathCheck)() = (undefined8(*)())0x1560a8750;
    static undefined8(*LoadResource)() = (undefined8(*)())0x156246510;
  }
  static undefined8(*Network_HandlePacket)() = (undefined8(*)())0x153434f00;
  static undefined8(*Monster_Tenderize_HandleMP_)() = (undefined8(*)())0x154f0d0c0;
  static undefined8(*Quest_FullAccessTest)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined4,undefined8,undefined8,undefined2,undefined4))0x14b165690;
  static bool(*Quest_CheckProgress)(longlong,int) = (bool(*)(longlong,int))0x14b8172b0;
  namespace Chat {
    static void(*BuildShowGameMessage)(undefined8,uint,byte,uint) = (void(*)(undefined8,uint,byte,uint))0x154398e70;
    static void *MainPtr = (void*)0x144df09d0;
    static void(*ShowGameMessage)(undefined *,char *,float,uint,byte) = (void(*)(undefined *,char *,float,uint,byte))0x15467e210;
  }
  static undefined8(*String_Format)(char *,char *) = (undefined8(*)(char *,char *))0x146d32f30;
  static undefined8(*Damage_Call)() = (undefined8(*)())0x146c2a750;
  static undefined8(*Damage_UnknCallsHitzone)(undefined,undefined,undefined,undefined,undefined4,undefined8) = (undefined8(*)(undefined,undefined,undefined,undefined,undefined4,undefined8))0x146c19910;
  static ulonglong(*Damage_GetHitzoneValue)(longlong,uint,ulonglong,ulonglong,uint,bool) = (ulonglong(*)(longlong,uint,ulonglong,ulonglong,uint,bool))0x146c22f60;
  static undefined8(*Monster_CalcSoftenedHitzone)() = (undefined8(*)())0x1486c80d0;
  static undefined8(*Monster_GetHitzoneArray)() = (undefined8(*)())0x154ecd3d0;
  static void(*Damage_Apply)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x146c30bf0;
  static bool(*Damage_ApplyTenderizeDmg)(longlong,longlong,float) = (bool(*)(longlong,longlong,float))0x146c32000;
  static bool(*Monster_CheckDamageTenderized)(undefined8,undefined8,float) = (bool(*)(undefined8,undefined8,float))0x146c72690;
  static undefined8(*Monster_TenderizePart)() = (undefined8(*)())0x1409c4d20;
  static undefined8(*Monster_SetTenderizeTimer)(undefined8,undefined8,float) = (undefined8(*)(undefined8,undefined8,float))0x148abf250;
  static longlong(*Monster_AddPartTimer)(longlong,int,float) = (longlong(*)(longlong,int,float))0x148abee20;
  static void(*Damage_LoadSomeValues)(undefined *,undefined *,undefined *) = (void(*)(undefined *,undefined *,undefined *))0x146c25990;
  static bool(*Monster_TenderizeManager_CheckPartTenderized)(undefined *,uint,uint) = (bool(*)(undefined *,uint,uint))0x148abe190;
  static longlong(*Monster_LoadMotion)(longlong,ulonglong) = (longlong(*)(longlong,ulonglong))0x154ca9dc0;
  static undefined8(*Quest_Count)() = (undefined8(*)())0x151ce99b0;
  static void(*Unkn_IncreaseTimer)(longlong) = (void(*)(longlong))0x148adb7d0;
  static bool(*IncreaseTimer)(undefined *,float) = (bool(*)(undefined *,float))0x14b7f4030;
  static undefined8(*QuestUI_FilterList)() = (undefined8(*)())0x14b172a30;
  static undefined8(*Quest_CheckFlag)() = (undefined8(*)())0x1542b84c0;
  static undefined8(*Quest_StarCategoryCheck)() = (undefined8(*)())0x14aa42e50;
  static void(*Monster_ManageEnrageTimer)(undefined *,undefined *) = (void(*)(undefined *,undefined *))0x148abe710;
  namespace Monster {
    namespace DamageBehavior {
      static undefined8(*NextAction)() = (undefined8(*)())0x151dbfb10;
    }
    static bool(*HasEmDmg)(undefined *) = (bool(*)(undefined *))0x154eeda40;
    static undefined *(*GetEmDmg)(undefined *) = (undefined *(*)(undefined *))0x154eca3f0;
    namespace EmDmg {
      static ulonglong(*Count)(undefined *) = (ulonglong(*)(undefined *))0x146be4070;
      static undefined *(*At)(undefined *,uint) = (undefined *(*)(undefined *,uint))0x1470e4c20;
      static void *vTable = (void*)0x143210a80;
    }
  }
  namespace Damage {
    static bool(*HandleReaction)(longlong,float *,undefined8 *,undefined4 *,undefined4 *,undefined) = (bool(*)(longlong,float *,undefined8 *,undefined4 *,undefined4 *,undefined))0x146c33660;
    static undefined8(*OverrideReaction)() = (undefined8(*)())0x146c1e210;
    namespace Unkn {
      static void *ReactionList = (void*)0x142d8d0d0;
      static undefined8(*HandleReactionU)() = (undefined8(*)())0x146c32460;
      static undefined8(*HandleReactionUU)() = (undefined8(*)())0x154b0aed0;
    }
    static int(*GetReactionType)(longlong,uint *,int *,uint *,uint *,char) = (int(*)(longlong,uint *,int *,uint *,uint *,char))0x146c1f7e0;
    static bool(*FetchReactedAction)(undefined *,uint,uint,uint *) = (bool(*)(undefined *,uint,uint,uint *))0x146c1dbd0;
  }
  namespace Quest {
    namespace QuestData {
      static void *ResourcePtr = (void*)0x144def0a8;
    }
    namespace QuestNoList {
      static void *ResourcePtr = (void*)0x144aa7d10;
    }
  }
  static void *GameVersion = (void*)0x14307f2b8;
  namespace List {
    static void(*IncreaseCapacity)(void *,ulonglong) = (void(*)(void *,ulonglong))0x1469e3690;
  }
}
