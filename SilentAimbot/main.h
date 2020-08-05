#pragma once

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "detours.lib")

#pragma warning(disable: 4409)

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <cstdio>
#include <stdio.h>
#include <cassert>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <algorithm>
#include <process.h>
#include <d3dx9.h> // We use #define D3DCOLOR now so you don't really need SDK just for this.
#include <d3d9.h>
#include <cstring>
#include <thread>
#include <random>

#include "CVector.h"
#include "CVector2D.h"

#include "CPed.h"

#include "CDetour.h"
#include "functions.h"

#include "ADE32.h"
#include "BitStream.h"
#include "RakClient.h"
#include "HookedRakClient.h"
#include "gtashit.h"

#include "detours.h"
#include "d3drender.h"
#include "d3dhook.h"

#include "IniFuncs.h"

using namespace std;

void MainLoop();
bool OnReceivePacket(Packet* p);
bool OnSendPacket(BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel);
bool OnSendRPC(int uniqueID, BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);

extern DWORD g_SAMP;
extern HANDLE g_DllHandle;
extern bool samp037;
extern bool initSampRak;

extern CD3DHook* pD3DHook;

extern int						silentaim;
extern int						silentaim_iAimID;
extern float					silentaim_lastAimDist;
extern int						silentaim_wallHack;
extern int						silentaim_fov;
extern int						silentaim_teamFilter;
extern int						silentaim_colorFilter;
extern int						silentaim_skinFilter;
extern int						silentaim_afkFilter;
extern int						silentaim_aliveFilter;
extern int						silentaim_outOfRangeFilter;
extern int						silentaim_antiAimBypass;
extern bool						FriendsListLoaded;
extern std::vector<std::string> Friends;
extern int						silentaim_friendFilter;
extern int						silentaim_hideESP;

#define SAMP037_CMP		"F8036A004050518D4C24"

#define SAMP037_CHAT_INFO_OFFSET					0x21A0E4
#define SAMP037_CHAT_INPUT_INFO_OFFSET				0x21A0E8
#define SAMP037_INFO_OFFSET							0x21A0F8
#define SAMP037_DRAWING_DISTANCE					0xD3DCC

#define SAMP037_FUNC_ADDTOCHATWND					0x64010
#define SAMP037_FUNC_SAY							0x57F0
#define SAMP037_FUNC_SENDCMD						0x65C60
#define SAMP037_FUNC_CNETGAMEDESTRUCTOR				0x9380
#define SAMP037_FUNC_ADDCLIENTCMD					0x65AD0

#define SAMP037_HOOKENTER_HANDLE_RPC				0x3743D
#define SAMP037_HOOKENTER_HANDLE_RPC2				0x373C9
#define SAMP037_HOOKEXIT_HANDLE_RPC					0x37443
#define SAMP037_HOOKEXIT_HANDLE_RPC2				0x37451
#define SAMP037_HOOKENTER_CNETGAME_DESTR			0xB2893
#define SAMP037_HOOKENTER_CNETGAME_DESTR2			0xB3A32



#define SAMP_CHAT_INFO_OFFSET						0x2ACA10
#define SAMP_CHAT_INPUT_INFO_OFFSET					0x2ACA14
#define SAMP_INFO_OFFSET							0x2ACA24
#define SAMP_MISC_INFO								0x2ACA3C
#define SAMP_DRAWING_DISTANCE						0x11812C


#define SAMP_FUNC_ADDTOCHATWND						0x67650
#define SAMP_FUNC_SAY								0x5860
#define SAMP_FUNC_SENDCMD							0x69340
#define SAMP_FUNC_ADDCLIENTCMD						0x691B0


#define SAMP_HOOKENTER_HANDLE_RPC					0x3A9ED
#define SAMP_HOOKENTER_HANDLE_RPC2					0x3A979
#define SAMP_HOOKEXIT_HANDLE_RPC					0x3A9F3
#define SAMP_HOOKEXIT_HANDLE_RPC2					0x3AA01
#define SAMP_FUNC_CNETGAMEDESTRUCTOR				0x9570
#define SAMP_HOOKENTER_CNETGAME_DESTR				0xC5533
#define SAMP_HOOKENTER_CNETGAME_DESTR2				0xC6736

#define SAMP_COLOR_OFFSET							0x18F6C0
#define SAMP037_COLOR_OFFSET						0x216378

#define VEHICLE_MAX_PASSENGERS						9