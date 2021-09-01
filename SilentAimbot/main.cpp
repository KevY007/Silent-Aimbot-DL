#include "main.h"

DWORD				g_SAMP = NULL;
HANDLE				g_DllHandle;

bool				samp037 = false;

bool				g_MainLoopInit = false;

int silentaim = 1;
int silentaim_afkFilter = 1;
int silentaim_friendFilter = 1;
int silentaim_aliveFilter = 1;
int silentaim_colorFilter = 0;
int silentaim_wallHack = 0;
int silentaim_iAimID = -1;
int silentaim_outOfRangeFilter = 0;
float silentaim_lastAimDist = 0.0;
int silentaim_skinFilter = 0;
int silentaim_fov = 180;
int silentaim_teamFilter = 0;
int silentaim_antiAimBypass = 1;
int silentaim_hideESP = 0;
bool FriendsListLoaded = false;
std::vector<std::string> Friends;

bool testNoShots = false; // SET TO TRUE THEN IT WILL NEVER SEND THE BULLETS.

bool letBulletGo = false;

DWORD hideESPTick = -1;

bool initSampRak = false;
CD3DHook* pD3DHook;

template<typename T>
T random(T min, T max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<T> dist(min, max);
	return dist(mt);
}

void cmd_friendlist_reload(char* params)
{
	FriendsListLoaded = false;
	displayTextScr(0x00, 0xCC, 0xFF, "Reloaded Friendlist!");
}

void cmd_friendlist_add(char* params)
{
	if (!FriendsListLoaded) return displayTextScr(0x99, 0x00, 0x00, "Friendlist isn't loaded yet!");

	if (params[0] == '\0')
		return addMessageToChatWindow(D3DCOLOR_XRGB(0xff, 0xff, 0xff), "USAGE: /friendlist_add <name>");

	if (strlen(params) < 3 || strlen(params) > SAMP_MAX_PLAYER_NAME)
		return addMessageToChatWindow(D3DCOLOR_XRGB(0xff, 0xff, 0xff), "Name cannot be less than 3 or more than %d characters!", SAMP_MAX_PLAYER_NAME);

	std::string name = params;
	Friends.push_back(name);
	std::remove(".\\silentaim_friends.ini");
	std::ofstream frenFile;
	frenFile.open(".\\silentaim_friends.ini");
	if (!frenFile.is_open()) return addMessageToChatWindow(D3DCOLOR_XRGB(0x99, 0x00, 0x00), "Failed to open friends file!");
	for (unsigned int i = 0; i < Friends.size(); i++)
	{
		frenFile << "\n" << Friends[i];
	}
	frenFile.close();
	FriendsListLoaded = false;
	displayTextScr(0xFF, 0x6D, 0x70, "Added %s to friend list.", name.c_str());
}

void cmd_friendlist_remove(char* params)
{
	if (!FriendsListLoaded) return displayTextScr(0x99, 0x00, 0x00, "Friendlist isn't loaded yet!");

	if (params[0] == '\0')
		return addMessageToChatWindow(D3DCOLOR_XRGB(0xff, 0xff, 0xff), "USAGE: /friendlist_remove <name>");

	std::string name = params;
	std::remove(".\\silentaim_friends.ini");
	std::ofstream frenFile;
	frenFile.open(".\\silentaim_friends.ini");
	if (!frenFile.is_open()) return addMessageToChatWindow(D3DCOLOR_XRGB(0x99, 0x00, 0x00), "Failed to open friends file!");
	for (unsigned int i = 0; i < Friends.size(); i++)
	{
		if (name.compare(Friends[i]) == 0) continue;
		frenFile << "\n" << Friends[i];
	}
	frenFile.close();
	FriendsListLoaded = false;
	displayTextScr(0xFF, 0x6D, 0x70, "Removed %s from friend list.", name.c_str());
}

void AimSettings(char* parc)
{
	if (strlen(parc) <= 2 || parc == nullptr) return addMessageToChatWindow(D3DCOLOR_XRGB(0x79, 0xc5, 0x72), "/configaim [toggle/filter/fov/shotmiss/esp]");

	std::stringstream s(parc);

	std::string first, second, three;
	s >> first >> second >> three;

	if (first.find("toggle") != string::npos)
	{
		silentaim = !silentaim;

		if (silentaim)
			displayTextScr(0x30, 0xB9, 0x0E, "Silent Aim Aktif Edildi -J.");
		else
			displayTextScr(0xCC, 0x00, 0x00, "Silent Aim Deaktif Edildi -J.");
	}
	else if (first.find("fov") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(D3DCOLOR_XRGB(0xff, 0xff, 0xff), "/configaim fov [radius]");

		silentaim_fov = stoi(second);

		displayTextScr(0xE4, 0xBD, 0x11, "The searching radius/FOV is now %d.", silentaim_fov);
	}
	else if (first.find("shotmiss") != string::npos)
	{
		silentaim_antiAimBypass = !silentaim_antiAimBypass;

		if (silentaim_antiAimBypass)
			displayTextScr(0x30, 0xB9, 0x0E, "Some shots will now randomly miss.");
		else
			displayTextScr(0xCC, 0x00, 0x00, "You hit every shot now.");
	}
	else if (first.find("esp") != string::npos)
	{
		silentaim_hideESP = !silentaim_hideESP;

		if (silentaim_hideESP)
			displayTextScr(0x30, 0xB9, 0x0E, "ESP is now hidden.");
		else
			displayTextScr(0xE4, 0xBD, 0x11, "ESP is no longer hidden.");
	}
	else if (first.find("filter") != string::npos)
	{
		if (second.empty())
			return addMessageToChatWindow(D3DCOLOR_XRGB(0x9a, 0x23, 0x23), "/configaim filter [afk/friend/alive/color/wallhack/rangehack/skin/team]");

		if (second.find("afk") != string::npos)
		{
			silentaim_afkFilter = !silentaim_afkFilter;

			if (silentaim_afkFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "AFK Players will be ignored.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "AFK Players will not be ignored.");
		}
		else if (second.find("friend") != string::npos)
		{
			silentaim_friendFilter = !silentaim_friendFilter;

			if (silentaim_friendFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "Friends will be ignored.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "Friends will not be ignored.");
		}
		else if (second.find("alive") != string::npos)
		{
			silentaim_aliveFilter = !silentaim_aliveFilter;

			if (silentaim_aliveFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "Dead players will be ignored.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "Dead players will not be ignored.");
		}
		else if (second.find("color") != string::npos)
		{
			silentaim_colorFilter = !silentaim_colorFilter;

			if (silentaim_colorFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "Players with same color will be ignored.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "Players with same color will not be ignored.");
		}
		else if (second.find("wallhack") != string::npos)
		{
			silentaim_wallHack = !silentaim_wallHack;

			if (silentaim_wallHack)
				displayTextScr(0x30, 0xB9, 0x0E, "You can now shoot people through walls.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "You cannot shoot through walls anymore.");
		}
		else if (second.find("rangehack") != string::npos)
		{
			silentaim_outOfRangeFilter = !silentaim_outOfRangeFilter;

			if (silentaim_outOfRangeFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "You can now shoot people from extraordinary distance.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "You cannot shoot outside weapon range anymore.");
		}
		else if (second.find("skin") != string::npos)
		{
			silentaim_skinFilter = !silentaim_skinFilter;

			if (silentaim_skinFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "You will ignore people with same skin now.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "You will not ignore people with same skin.");
		}
		else if (second.find("team") != string::npos)
		{
			silentaim_teamFilter = !silentaim_teamFilter;

			if (silentaim_teamFilter)
				displayTextScr(0x30, 0xB9, 0x0E, "You will ignore people with same team ID.");
			else
				displayTextScr(0xCC, 0x00, 0x00, "You will not ignore people with same team ID.");
		}
		else AimSettings("filter");
	}
	else AimSettings(""); // This will show the USAGE as strlen(parc) <= 1

	CIniWriter iniWriter(".\\silentaim.ini");
	iniWriter.WriteInteger("Settings", "Toggled", silentaim);
	iniWriter.WriteInteger("Settings", "FieldOfView", silentaim_fov);
	iniWriter.WriteInteger("Settings", "MissShots", silentaim_antiAimBypass);
	iniWriter.WriteInteger("Settings", "HideESP", silentaim_hideESP);

	iniWriter.WriteInteger("Filters", "AFKFilter", silentaim_afkFilter);
	iniWriter.WriteInteger("Filters", "FriendFilter", silentaim_friendFilter);
	iniWriter.WriteInteger("Filters", "AliveFilter", silentaim_aliveFilter);
	iniWriter.WriteInteger("Filters", "ColorFilter", silentaim_colorFilter);
	iniWriter.WriteInteger("Filters", "WallHack", silentaim_wallHack);
	iniWriter.WriteInteger("Filters", "RangeHack", silentaim_outOfRangeFilter);
	iniWriter.WriteInteger("Filters", "SkinFilter", silentaim_skinFilter);
	iniWriter.WriteInteger("Filters", "TeamFilter", silentaim_teamFilter);
	return;
}

void MainLoop() // addMessageToChatWindow etc here won't bug out as it's in game thread, use this thread for game functions etc.
{	
	if (!g_MainLoopInit)
	{
		if (!silentaim_hideESP)
		{
			if (samp037)
				addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 10), "{990000}Silent Aimbot. 037 Compat.");
			else
				addMessageToChatWindow(D3DCOLOR_XRGB(255, 255, 10), "{990000}Silent Aimbot.");
		}
		
		g_MainLoopInit = true;
	}

	if ((GetKeyState(VK_F8) & 0x100) != 0 && silentaim)
	{
		if (silentaim_hideESP != 1)
		{
			silentaim_hideESP = 1;
			hideESPTick = GetTickCount();
		}
	}

	if (hideESPTick != -1 && GetTickCount() - hideESPTick >= 2000)
	{
		hideESPTick = -1;
		if(silentaim_hideESP == 1) silentaim_hideESP = 0;
	}

	if (samp037)
	{
		g_stSAMP037 = stGetSampInfo037();

		if (isBadPtr_writeAny(g_stSAMP037->pPools, sizeof(stSAMPPools_037)))
			return;
		
		else if (isBadPtr_writeAny(g_stSAMP037->pPools->pPlayer, sizeof(stPlayerPool_037)))
			return;
	}
	else
	{
		g_stSAMP = stGetSampInfo();

		if (isBadPtr_writeAny(g_stSAMP->pPools, sizeof(stSAMPPools)))
			return;

		else if (isBadPtr_writeAny(g_stSAMP->pPools->pPlayer, sizeof(stPlayerPool)))
			return;
	}

	if (FriendsListLoaded == false) ReloadFriendlist();

	int aimedID = GetSilentAimTarget();

	if (silentaim_iAimID != -1 && ValidPlayer(aimedID) && IsPlayerStreamed(aimedID) &&
		silentaim_friendFilter && FriendsListLoaded && Friends.size() > 0 &&
		std::find(Friends.begin(), Friends.end(), getPlayerName(silentaim_iAimID)) != Friends.end())
	{
		silentaim_iAimID = -1;
	}
	else
	{
		silentaim_iAimID = aimedID;
	}

	if((GetKeyState(VK_RBUTTON) & 0x100) != 0 && silentaim && silentaim_hideESP == 0)
	{
		float centerX, centerY;
		GetAimingCenter(centerX, centerY);

		pD3DHook->pRender->CircleOutlined(centerX, centerY, (float)silentaim_fov, 42, 1.25, D3DCOLOR_ARGB(32, 255, 255, 255), D3DCOLOR_ARGB(32, 0, 0, 0));
		
		if (silentaim_iAimID != -1)
		{	
			struct actor_info* targetact = getGTAPedFromSAMPPlayerID(silentaim_iAimID);
			
			D3DXVECTOR3 vWorld, vScreen;
			float fPos[3];
			getPlayerPos(silentaim_iAimID, fPos);

			fPos[2] += 0.35;

			vWorld.x = fPos[0];
			vWorld.y = fPos[1];
			vWorld.z = fPos[2];

			CalcScreenCoors(&vWorld, &vScreen);

			float fPosSelf[3];
			vect3_copy(&actor_info_get_self()->base.matrix[4 * 3], fPosSelf);

			float dist = vect3_dist(fPos, fPosSelf);

			pD3DHook->pRender->D3DLineOutlined(vScreen.x,
				vScreen.y,
				centerX,
				centerY,
				1.25,
				samp_color_get(silentaim_iAimID), D3DCOLOR_XRGB(0, 0, 0));

			pD3DHook->pRender->D3DBox(vScreen.x, vScreen.y, 3.5, 3.5, D3DCOLOR_XRGB(0xE2, 0xD9, 0x6F));

			float w, h;
			w = 80.0f - (dist * 0.75f);
			h = 125.0f - (dist * 0.75f);

			if (w > 0.0f && h > 0.0f)
			{
				pD3DHook->pRender->D3DBoxBorder(vScreen.x - (dist * 0.50f) + 1.0f - (w / 2), vScreen.y - (dist * 0.75f) + 1.0f - 2.5f, w, h, D3DCOLOR_XRGB(1, 1, 1), D3DCOLOR_ARGB(0, 1, 1, 1));

				pD3DHook->pRender->D3DBoxBorder(vScreen.x - (dist * 0.50f) - 1.0f - (w / 2), vScreen.y - (dist * 0.75f) - 1.0f - 2.5f, w, h, D3DCOLOR_XRGB(1, 1, 1), D3DCOLOR_ARGB(0, 1, 1, 1));

				pD3DHook->pRender->D3DBoxBorder(vScreen.x - (dist * 0.50f) - (w / 2), vScreen.y - (dist * 0.75f), w, h, samp_color_get(silentaim_iAimID), D3DCOLOR_ARGB(0, 1, 1, 1));
			}

			//pD3DHook->pD3DFont->Print(vScreen.x, vScreen.y, samp_color_get(silentaim_iAimID), "Target", true);
		}
	}
}


bool OnSendRPC(int uniqueID, BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (uniqueID == RPC_GiveTakeDamage)
	{
		if (silentaim)
		{
			bool bGiveOrTake;
			UINT16 iPlayerID;
			float fAmount;
			UINT32 iWeaponID, iBodyPart;

			parameters->ResetReadPointer();
			parameters->Read(bGiveOrTake);
			parameters->Read(iPlayerID);
			parameters->Read(fAmount);
			parameters->Read(iWeaponID);
			parameters->Read(iBodyPart);

			parameters->SetWriteOffset(0);
			parameters->Write(bGiveOrTake);
			parameters->Write(iPlayerID);
			parameters->Write(fAmount);
			parameters->Write(iWeaponID);
			parameters->Write(iBodyPart);

			if (!bGiveOrTake)
			{
				if (letBulletGo)
				{
					letBulletGo = false;
					return true;
				}
				else
				{
					if (silentaim_iAimID != -1)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

float fWeaponDamage[55] =
{
	1.0, // 0 - Fist
	1.0, // 1 - Brass knuckles
	1.0, // 2 - Golf club
	1.0, // 3 - Nitestick
	1.0, // 4 - Knife
	1.0, // 5 - Bat
	1.0, // 6 - Shovel
	1.0, // 7 - Pool cue
	1.0, // 8 - Katana
	1.0, // 9 - Chainsaw
	1.0, // 10 - Dildo
	1.0, // 11 - Dildo 2
	1.0, // 12 - Vibrator
	1.0, // 13 - Vibrator 2
	1.0, // 14 - Flowers
	1.0, // 15 - Cane
	82.5, // 16 - Grenade
	0.0, // 17 - Teargas
	1.0, // 18 - Molotov
	9.9, // 19 - Vehicle M4 (custom)
	46.2, // 20 - Vehicle minigun (custom)
	0.0, // 21
	8.25, // 22 - Colt 45
	13.2, // 23 - Silenced
	46.2, // 24 - Deagle
	49.5,//3.3, // 25 - Shotgun
	49.5,//3.3, // 26 - Sawed-off
	39.6,//4.95, // 27 - Spas
	6.6, // 28 - UZI
	8.25, // 29 - MP5
	9.900001, // 30 - AK47
	9.900001, // 31 - M4
	6.6, // 32 - Tec9
	24.750001, // 33 - Cuntgun
	41.25, // 34 - Sniper
	82.5, // 35 - Rocket launcher
	82.5, // 36 - Heatseeker
	1.0, // 37 - Flamethrower
	46.2, // 38 - Minigun
	82.5, // 39 - Satchel
	0.0, // 40 - Detonator
	0.33, // 41 - Spraycan
	0.33, // 42 - Fire extinguisher
	0.0, // 43 - Camera
	0.0, // 44 - Night vision
	0.0, // 45 - Infrared
	0.0, // 46 - Parachute
	0.0, // 47 - Fake pistol
	2.64, // 48 - Pistol whip (custom)
	9.9, // 49 - Vehicle
	330.0, // 50 - Helicopter blades
	82.5, // 51 - Explosion
	1.0, // 52 - Car park (custom)
	1.0, // 53 - Drowning
	165.0 // 54 - Splat
};

bool OnSendPacket(BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	uint8_t packetId;
	parameters->ResetReadPointer();
	parameters->Read(packetId);

	if (packetId == ID_BULLET_SYNC)
	{
		bool bEditBulletSync = false;
		stBulletData BulletData;
		parameters->Read((PCHAR)& BulletData, sizeof(stBulletData));
		if (silentaim)
		{
			if (BulletData.byteType == 1)
			{
				letBulletGo = true;
				return true;
			}

			if (silentaim_iAimID == -1)
				return true;

			if (!IsPlayerStreamed(silentaim_iAimID))
				return true;

			BulletData.byteType = 1;

			if (samp037)
			{
				vect3_copy(&g_stSAMP037->pPools->pPlayer->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fOrigin);

				vect3_copy(&g_stSAMP037->pPools->pPlayer->pRemotePlayer[silentaim_iAimID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fTarget);

			}
			else
			{
				vect3_copy(&g_stSAMP->pPools->pPlayer->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fOrigin);

				vect3_copy(&g_stSAMP->pPools->pPlayer->pRemotePlayer[silentaim_iAimID]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[12],
					BulletData.fTarget);
			}
			
			BulletData.fCenter[0] = 0;
			BulletData.fCenter[1] = 0;
			if (getPlayerState(silentaim_iAimID) == PLAYER_STATE_ONFOOT)
			{
				BulletData.fCenter[2] = 0;
			}
			else
			{
				BulletData.fCenter[2] = 0.56 - ((rand() % 5) / 100.0f);
			}
			
			BulletData.sTargetID = silentaim_iAimID;
			bool go = true;
			if (silentaim_antiAimBypass)
			{
				int wepid = GetCurrentWeapon();

				if (wepid >= 22 && wepid <= 25)
				{
					int random_ac_bypass = random(0, 3);
					if (random_ac_bypass == 0) go = false;
				}

				if (wepid >= 26 && wepid <= 27)
				{
					int random_ac_bypass = random(0, 5);
					if (random_ac_bypass > 2) go = false;
				}

				if (wepid >= 28 && wepid <= 32)
				{
					int random_ac_bypass = random(0, 10);
					if (random_ac_bypass > 3) go = false;
				}

				if (wepid >= 33 && wepid <= 34)
				{
					int random_ac_bypass = random(0, 5);
					if (random_ac_bypass > 2) go = false;
				}
			}
			if (testNoShots) go = false;
			if (go)
			{
				BitStream bsGiveDamage;
				bsGiveDamage.Write(false);
				bsGiveDamage.Write((UINT16)silentaim_iAimID);
				bsGiveDamage.Write(fWeaponDamage[GetCurrentWeapon()]);
				bsGiveDamage.Write((UINT32)GetCurrentWeapon());
				//Log("Custom Send: damage %f, player %d, weapon %d", fWeaponDamage[g_Players->pLocalPlayer->byteCurrentWeapon], g_NewModSa->iAimPlayerID, g_Players->pLocalPlayer->byteCurrentWeapon);
				
				bsGiveDamage.Write((UINT32)random<UINT32>(3, 9));
				
				g_RakClient->RPC(RPC_GiveTakeDamage, &bsGiveDamage, HIGH_PRIORITY, RELIABLE_SEQUENCED, NULL, false);
			}
			else
			{
				BulletData.byteType = 0;
			}
			bEditBulletSync = true;
		}
		if (bEditBulletSync)
		{
			parameters->Reset();
			parameters->Write((BYTE)ID_BULLET_SYNC);
			parameters->Write((PCHAR)& BulletData, sizeof(stBulletData));
			g_RakClient->Send(parameters, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
			return false;
		}
	}
	return true;
}

bool OnReceivePacket(Packet* p)
{
	if (p->data == nullptr || p->length == 0)
		return true;

	if (p->data[0] == PacketEnumeration::ID_VEHICLE_SYNC) // Example.
	{

	}
	return true;
}

void ThrMainFS() 
{
	while (g_SAMP == NULL || (g_Chat == NULL && g_Chat037 == NULL))
	{
		g_SAMP = (DWORD)GetModuleHandleA("samp.dll");

		g_Chat = stGetSampChatInfo();
        g_Chat037 = stGetSampChatInfo037();
		Sleep(1000);
	}
	
	while (true)
	{
		if (!initSampRak)
		{
			if (memcmp_safe((uint8_t*)g_SAMP + 0xBABE, hex_to_bin(SAMP037_CMP), 10))
			{
				samp037 = true;
			}
			else samp037 = false;

			if (samp037)
			{
				g_stSAMP037 = stGetSampInfo037();

				if (isBadPtr_writeAny(g_stSAMP037, sizeof(stSAMP_037)))
				{
					continue;
				}

				if (isBadPtr_writeAny(g_stSAMP037->pPools, sizeof(stSAMPPools_037)))
				{
					continue;
				}

				g_Chat037 = stGetSampChatInfo037();
				if (isBadPtr_writeAny(g_Chat037, sizeof(stChatInfo_037)))
				{
					continue;
				}

				g_Input037 = stGetInputInfo037();
				if (isBadPtr_writeAny(g_Input037, sizeof(stInputInfo_037)))
				{
					continue;
				}

				if (g_stSAMP037->pRakClientInterface == NULL)
				{
					continue;
				}

				g_RakClient = new RakClient(g_stSAMP037->pRakClientInterface);
				g_stSAMP037->pRakClientInterface = new HookedRakClientInterface();

				SetupSAMPHook("CNETGAMEDESTR1", SAMP037_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
				SetupSAMPHook("CNETGAMEDESTR2", SAMP037_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
			}
			else
			{
				g_stSAMP = stGetSampInfo();

				if (isBadPtr_writeAny(g_stSAMP, sizeof(stSAMP)))
				{
					continue;
				}

				if (isBadPtr_writeAny(g_stSAMP->pPools, sizeof(stSAMPPools)))
				{
					continue;
				}

				g_Chat = stGetSampChatInfo();
				if (isBadPtr_writeAny(g_Chat, sizeof(stChatInfo)))
				{
					continue;
				}

				g_Input = stGetInputInfo();
				if (isBadPtr_writeAny(g_Input, sizeof(stInputInfo)))
				{
					continue;
				}

				if (g_stSAMP->pRakClientInterface == NULL)
				{
					continue;
				}

				g_RakClient = new RakClient(g_stSAMP->pRakClientInterface);
				g_stSAMP->pRakClientInterface = new HookedRakClientInterface();


				SetupSAMPHook("CNETGAMEDESTR1", SAMP_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
				SetupSAMPHook("CNETGAMEDESTR2", SAMP_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
			}

			CIniReader iniReader(".\\silentaim.ini");
			silentaim = iniReader.ReadInteger("Settings", "Toggled", 1);
			silentaim_fov = iniReader.ReadInteger("Settings", "FieldOfView", 180);
			silentaim_antiAimBypass = iniReader.ReadInteger("Settings", "MissShots", 1);
			silentaim_hideESP = iniReader.ReadInteger("Settings", "HideESP", 0);

			silentaim_afkFilter = iniReader.ReadInteger("Filters", "AFKFilter", 1);
			silentaim_friendFilter = iniReader.ReadInteger("Filters", "FriendFilter", 1);
			silentaim_aliveFilter = iniReader.ReadInteger("Filters", "AliveFilter", 1);
			silentaim_colorFilter = iniReader.ReadInteger("Filters", "ColorFilter", 0);
			silentaim_wallHack = iniReader.ReadInteger("Filters", "WallHack", 0);
			silentaim_outOfRangeFilter = iniReader.ReadInteger("Filters", "RangeHack", 0);
			silentaim_skinFilter = iniReader.ReadInteger("Filters", "SkinFilter", 0);
			silentaim_teamFilter = iniReader.ReadInteger("Filters", "TeamFilter", 1);

			addClientCommand("configaim", AimSettings);

			addClientCommand("aimfl_remove", cmd_friendlist_remove);
			addClientCommand("aimfl_add", cmd_friendlist_add);
			addClientCommand("aimfl_reload", cmd_friendlist_reload);


			initSampRak = true;
		}
		if (initSampRak)
		{
			// Code if you wanna execute any. Put it in here so it doesn't execute before samp has loaded.
			// CODE HERE WILL BE MULTI THREADED, DN'T DRAW HERE, ITS GONNA BE DA CODE RUNNING OUTSIDE OF GAME THREAD
		}
		Sleep(1000); // Adjust according to your needs
	}
}

void mainThreadTest(void* pvParams)
{

}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, 
	DWORD fdwReason,    
	LPVOID lpReserved) 
{

	g_DllHandle = hinstDLL;

	DisableThreadLibraryCalls((HMODULE)hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return TRUE;

	if (GetModuleHandle("samp.dll"))
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThrMainFS, NULL, 0, NULL);
		_beginthread(mainThreadTest, NULL, NULL);
		pD3DHook = new CD3DHook();
	}

	return TRUE;  
}
