#include "main.h"

struct stSAMP* g_stSAMP;
struct stChatInfo* g_Chat;
struct stInputInfo* g_Input;

struct stSAMP_037* g_stSAMP037;
struct stChatInfo_037* g_Chat037;
struct stInputInfo_037* g_Input037;

#define FUNC_IsLineOfSightClear 0x56A490	// ##SA##
#define FUNC_ProcessLineOfSight 0x56BA00	// ##SA##

bool IsLineOfSightClear(CVector* vecStart, CVector* vecEnd, bool bCheckBuildings,
	bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects,
	bool bCheckDummies, bool bSeeThroughStuff, bool bIgnoreSomeObjectsForCamera)
{
	DWORD dwFunc = FUNC_IsLineOfSightClear;
	bool bReturn = false;
	// bool bCheckBuildings = true, bool bCheckVehicles = true, bool bCheckPeds = true, 
	// bool bCheckObjects = true, bool bCheckDummies = true, bool bSeeThroughStuff = false, 
	// bool bIgnoreSomeObjectsForCamera = false

	_asm
	{
		push	bIgnoreSomeObjectsForCamera
		push	bSeeThroughStuff
		push	bCheckDummies
		push	bCheckObjects
		push	bCheckPeds
		push	bCheckVehicles
		push	bCheckBuildings
		push	vecEnd
		push	vecStart
		call	dwFunc
		mov		bReturn, al
		add		esp, 0x24
	}
	return bReturn;
}


struct actor_info* actor_info_get_self()
{
	struct actor_info* info;

	info = (struct actor_info*)(UINT_PTR) * (uint32_t*)0x00B7CD98;

	return info;
}

int vehicle_contains_actor(struct vehicle_info* vehicle, struct actor_info* actor)
{
	struct actor_info* passengers[VEHICLE_MAX_PASSENGERS];
	struct actor_info* temp;

	if (actor == NULL)
		return NULL;

	memcpy(passengers, vehicle->passengers, sizeof(uint32_t) * VEHICLE_MAX_PASSENGERS);

	int i;
	for (i = 0; i < VEHICLE_MAX_PASSENGERS; i++)
	{
		temp = passengers[i];
		if (temp == actor)
			return 1;
	}

	return NULL;
}

struct vehicle_info* vehicle_info_get_self()
{
	struct vehicle_info* info;

	info = (struct vehicle_info*)(UINT_PTR) * (uint32_t*)0x00B6F980;
	
	struct actor_info* actor = actor_info_get_self();
	if (!vehicle_contains_actor(info, actor))
		return NULL;
	
	return info;
}

struct actor_info* getGTAPedFromSAMPPlayerID(int iPlayerID)
{
	if (samp037)
	{
		if (g_stSAMP037->pPools->pPlayer == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;
		if (iPlayerID == g_stSAMP037->pPools->pPlayer->sLocalPlayerID)
			return actor_info_get_self();
		if (g_stSAMP037->pPools->pPlayer->iIsListed[iPlayerID] != 1)
			return NULL;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID] == NULL)
			return NULL;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
			return NULL;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
			return NULL;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
			return NULL;

		// return actor_info, null or otherwise
		return g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
	}
	else
	{
		if (g_stSAMP->pPools->pPlayer == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;
		if (iPlayerID == g_stSAMP->pPools->pPlayer->sLocalPlayerID)
			return actor_info_get_self();
		if (g_stSAMP->pPools->pPlayer->iIsListed[iPlayerID] != 1)
			return NULL;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID] == NULL)
			return NULL;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
			return NULL;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
			return NULL;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
			return NULL;

		// return actor_info, null or otherwise
		return g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
	}
	return (actor_info*)NULL;
}

int getPlayerState(int iPlayerID)
{
	if (samp037)
	{
		if (g_stSAMP037->pPools->pPlayer == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;
		if (iPlayerID == g_stSAMP037->pPools->pPlayer->sLocalPlayerID)
			return NULL;
		if (g_stSAMP037->pPools->pPlayer->iIsListed[iPlayerID] != 1)
			return NULL;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
			return NULL;

		return g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->bytePlayerState;
	}
	else
	{
		if (g_stSAMP->pPools->pPlayer == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;
		if (iPlayerID == g_stSAMP->pPools->pPlayer->sLocalPlayerID)
			return NULL;
		if (g_stSAMP->pPools->pPlayer->iIsListed[iPlayerID] != 1)
			return NULL;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
			return NULL;

		return g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->bytePlayerState;

	}
	return NULL;
}

bool IsPlayerStreamed(uint16_t playerID)
{
	if (samp037)
	{
		if (g_stSAMP037->pPools->pPlayer == NULL)
			return false;
		if (g_stSAMP037->pPools->pPlayer->iIsListed[playerID] != 1)
			return false;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[playerID] == NULL)
			return false;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[playerID]->pPlayerData == NULL)
			return false;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
			return false;
	}
	else
	{
		if (g_stSAMP->pPools->pPlayer == NULL)
			return false;
		if (g_stSAMP->pPools->pPlayer->iIsListed[playerID] != 1)
			return false;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[playerID] == NULL)
			return false;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[playerID]->pPlayerData == NULL)
			return false;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
			return false;
	}
	return true;
}

static signed char hex_to_dec(signed char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	if (ch >= 'a' && ch <= 'f')
		return ch - 'A' + 10;

	return -1;
}

bool hex_is_valid(const std::string& hex)
{
	if (hex.empty())
		return false;
	for (size_t i = 0, len = hex.length(); i < len; i++)
	{
		if (hex_to_dec(hex[i]) == -1)
			return false;
	}
	return true;
}

size_t strlcpy(char* dst, const char* src, size_t size)
{
	size_t	len = strlen(src);

	if (size == 0)
		return len;

	if (len >= size)
	{
		size--;
		memcpy(dst, src, size);
		dst[size] = 0;
	}
	else if (size > 0)
	{
		strcpy(dst, src);
	}

	return len;
}

uint8_t* hex_to_bin(const char* str)
{
	int		len = (int)strlen(str);
	uint8_t* buf, * sbuf;

	if (len == 0 || len % 2 != 0)
		return NULL;

	sbuf = buf = (uint8_t*)malloc(len / 2);

	while (*str)
	{
		signed char bh = hex_to_dec(*str++);
		signed char bl = hex_to_dec(*str++);

		if (bl == -1 || bh == -1)
		{
			free(sbuf);
			return NULL;
		}

		*buf++ = (uint8_t)(bl | (bh << 4));
	}

	return sbuf;
}

bool isBadPtr_handlerAny(void* pointer, ULONG size, DWORD dwFlags)
{
	DWORD						dwSize;
	MEMORY_BASIC_INFORMATION	meminfo;

	if (NULL == pointer)
		return true;

	memset(&meminfo, 0x00, sizeof(meminfo));
	dwSize = VirtualQuery(pointer, &meminfo, sizeof(meminfo));

	if (0 == dwSize)
		return true;

	if (MEM_COMMIT != meminfo.State)
		return true;

	if (0 == (meminfo.Protect & dwFlags))
		return true;

	if (size > meminfo.RegionSize)
		return true;

	if ((unsigned)((char*)pointer - (char*)meminfo.BaseAddress) > (unsigned)(meminfo.RegionSize - size))
		return true;

	return false;
}

bool isBadPtr_readAny(void* pointer, ULONG size)
{
	return isBadPtr_handlerAny(pointer, size, PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
		PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
}

bool isBadPtr_writeAny(void* pointer, ULONG size)
{
	return isBadPtr_handlerAny(pointer, size,
		PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
}

static int __page_size_get(void)
{
	static int	page_size = -1;
	SYSTEM_INFO si;

	if (page_size == -1)
	{
		GetSystemInfo(&si);
		page_size = (int)si.dwPageSize;
	}

	return page_size;
}

static int __page_write(void* _dest, const void* _src, uint32_t len)
{
	static int		page_size = __page_size_get();
	uint8_t* dest = (uint8_t*)_dest;
	const uint8_t* src = (const uint8_t*)_src;
	DWORD			prot_prev = 0;
	int				prot_changed = 0;
	int				ret = 1;

	while (len > 0)
	{
		ret = 1;
		int page_offset = (int)((UINT_PTR)dest % page_size);
		int page_remain = page_size - page_offset;
		int this_len = len;

		if (this_len > page_remain)
			this_len = page_remain;

		if (isBadPtr_writeAny(dest, this_len))
		{
			if (!VirtualProtect((void*)dest, this_len, PAGE_EXECUTE_READWRITE, &prot_prev))
				ret = 0;
			else
				prot_changed = 1;
		}

		if (ret)
			memcpy(dest, src, this_len);

		if (prot_changed)
		{
			DWORD	dummy;
			if (!VirtualProtect((void*)dest, this_len, prot_prev, &dummy))
				printf("__page_write() could not restore original permissions for ptr %p\n", dest);
		}

		dest += this_len;
		src += this_len;
		len -= this_len;
	}

	return ret;
}

static int __page_read(void* _dest, const void* _src, uint32_t len)
{
	static int	page_size = __page_size_get();
	uint8_t* dest = (uint8_t*)_dest;
	uint8_t* src = (uint8_t*)_src;
	DWORD		prot_prev = 0;
	int			prot_changed = 0;
	int			ret = 1;

	while (len > 0)
	{
		ret = 1;
		int page_offset = (int)((UINT_PTR)src % page_size);
		int page_remain = page_size - page_offset;
		int this_len = len;

		if (this_len > page_remain)
			this_len = page_remain;

		if (isBadPtr_readAny(src, this_len))
		{
			if (!VirtualProtect((void*)src, this_len, PAGE_EXECUTE_READWRITE, &prot_prev))
				ret = 0;
			else
				prot_changed = 1;
		}

		if (ret)
			memcpy(dest, src, this_len);
		else
			memset(dest, 0, this_len);

		if (prot_changed)
		{
			DWORD	dummy;
			if (!VirtualProtect((void*)src, this_len, prot_prev, &dummy))
				printf("__page_read() could not restore original permissions for ptr %p\n", src);
		}

		dest += this_len;
		src += this_len;
		len -= this_len;
	}

	return ret;
}

int memcpy_safe(void* _dest, const void* _src, uint32_t len, int check, const void* checkdata)
{
	static int		page_size = __page_size_get();
	static int		recurse_ok = 1;
	uint8_t			buf[4096];
	uint8_t* dest = (uint8_t*)_dest;
	const uint8_t* src = (const uint8_t*)_src;
	int				ret = 1;

	if (check && checkdata)
	{
		if (!memcmp_safe(checkdata, _dest, len))
			return 0;
	}

	while (len > 0)
	{
		uint32_t	this_len = sizeof(buf);

		if (this_len > len)
			this_len = len;

		if (!__page_read(buf, src, this_len))
			ret = 0;

		if (!__page_write(dest, buf, this_len))
			ret = 0;

		len -= this_len;
		src += this_len;
		dest += this_len;
	}

	return ret;
}

int memcmp_safe(const void* _s1, const void* _s2, uint32_t len)
{
	const uint8_t* s1 = (const uint8_t*)_s1;
	const uint8_t* s2 = (const uint8_t*)_s2;
	uint8_t			buf[4096];

	for (;; )
	{
		if (len > 4096)
		{
			if (!memcpy_safe(buf, s1, 4096))
				return 0;
			if (memcmp(buf, s2, 4096))
				return 0;
			s1 += 4096;
			s2 += 4096;
			len -= 4096;
		}
		else
		{
			if (!memcpy_safe(buf, s1, len))
				return 0;
			if (memcmp(buf, s2, len))
				return 0;
			break;
		}
	}

	return 1;
}

void SetupSAMPHook(const char* szName, DWORD dwFuncOffset, void* Func, int iType, int iSize, const char* szCompareBytes)
{
	CDetour api;
	int strl = strlen(szCompareBytes);
	uint8_t* bytes = hex_to_bin(szCompareBytes);

	if (!strl || !bytes || memcmp_safe((uint8_t*)g_SAMP + dwFuncOffset, bytes, strl / 2))
	{
		if (api.Create((uint8_t*)((uint32_t)g_SAMP) + dwFuncOffset, (uint8_t*)Func, iType, iSize) == 0)
			printf("[HOOK] Failed to hook %s.\n", szName);
	}
	else
	{
		printf("[HOOK] Failed to hook %s (memcmp)\n", szName);
	}

	if (bytes)
		free(bytes);
}

template<typename T>
T GetSAMPPtrInfo(uint32_t offset)
{
	return *(T*)(g_SAMP + offset);
}

struct stSAMP_037* stGetSampInfo037(void)
{
	return GetSAMPPtrInfo<stSAMP_037*>(SAMP037_INFO_OFFSET);
}

struct stChatInfo_037* stGetSampChatInfo037(void)
{
	return GetSAMPPtrInfo<stChatInfo_037*>(SAMP037_CHAT_INFO_OFFSET);
}

struct stInputInfo_037* stGetInputInfo037(void)
{
	return GetSAMPPtrInfo<stInputInfo_037*>(SAMP037_CHAT_INPUT_INFO_OFFSET);
}

struct stSAMP* stGetSampInfo(void)
{
	return GetSAMPPtrInfo<stSAMP*>(SAMP_INFO_OFFSET);
}

struct stChatInfo* stGetSampChatInfo(void)
{
	return GetSAMPPtrInfo<stChatInfo*>(SAMP_CHAT_INFO_OFFSET);
}

struct stInputInfo* stGetInputInfo(void)
{
	return GetSAMPPtrInfo<stInputInfo*>(SAMP_CHAT_INPUT_INFO_OFFSET);
}

void addMessageToChatWindow(D3DCOLOR col, const char* text, ...)
{
	if (g_stSAMP != NULL || g_stSAMP037 != NULL)
	{
		va_list ap;
		if (text == NULL)
			return;

		char	tmp[512];
		memset(tmp, 0, 512);

		va_start(ap, text);
		vsnprintf(tmp, sizeof(tmp) - 1, text, ap);
		va_end(ap);

		addToChatWindow(tmp, col);
	}
}

void __stdcall CNetGame__destructor(void)
{
	// release hooked rakclientinterface, restore original rakclientinterface address and call CNetGame destructor

	if (samp037)
	{
		if (g_stSAMP037->pRakClientInterface != NULL)
			delete g_stSAMP037->pRakClientInterface;
		g_stSAMP037->pRakClientInterface = g_RakClient->GetInterface();

		return ((void(__thiscall*) (void*)) (g_SAMP + SAMP037_FUNC_CNETGAMEDESTRUCTOR))(g_stSAMP037);
	}
	else
	{
		if (g_stSAMP->pRakClientInterface != NULL)
			delete g_stSAMP->pRakClientInterface;
		g_stSAMP->pRakClientInterface = g_RakClient->GetInterface();

		return ((void(__thiscall*) (void*)) (g_SAMP + SAMP_FUNC_CNETGAMEDESTRUCTOR))(g_stSAMP);
	}
}

void addToChatWindow(char* text, D3DCOLOR textColor)
{
	if (g_stSAMP == NULL && g_stSAMP037 == NULL)
		return;

	if (g_Chat == NULL && g_Chat037 == NULL)
		return;

	if (text == NULL)
		return;

	if (samp037)
	{
		void(__thiscall * AddToChatWindowBuffer) (void*, ChatMessageType, const char*, const char*, D3DCOLOR, D3DCOLOR) =
			(void(__thiscall*) (void* _this, ChatMessageType Type, const char* szString, const char* szPrefix, D3DCOLOR TextColor, D3DCOLOR PrefixColor))
			(g_SAMP + SAMP037_FUNC_ADDTOCHATWND);

		AddToChatWindowBuffer(g_Chat037, CHAT_TYPE_DEBUG, text, nullptr, textColor, 0);
	}
	else
	{
		void(__thiscall * AddToChatWindowBuffer) (void*, ChatMessageType, const char*, const char*, D3DCOLOR, D3DCOLOR) =
			(void(__thiscall*) (void* _this, ChatMessageType Type, const char* szString, const char* szPrefix, D3DCOLOR TextColor, D3DCOLOR PrefixColor))
			(g_SAMP + SAMP_FUNC_ADDTOCHATWND);

		AddToChatWindowBuffer(g_Chat, CHAT_TYPE_DEBUG, text, nullptr, textColor, 0);
	}
}

void say(char* msg)
{
	if (g_SAMP == NULL)
		return;

	if (msg == NULL)
		return;

	if (isBadPtr_readAny(msg, 128))
		return;

	if (msg == NULL)
		return;

	if (msg[0] == '/')
	{
		if(samp037) ((void(__thiscall*) (void* _this, char* message)) (g_SAMP + SAMP037_FUNC_SENDCMD))(g_Input037, msg);
		else ((void(__thiscall*) (void* _this, char* message)) (g_SAMP + SAMP_FUNC_SENDCMD))(g_Input, msg);
	}
	else
	{
		if(samp037) ((void(__thiscall*) (void* _this, char* message)) (g_SAMP + SAMP037_FUNC_SAY)) (g_stSAMP037->pPools->pPlayer->pLocalPlayer, msg);
		else ((void(__thiscall*) (void* _this, char* message)) (g_SAMP + SAMP_FUNC_SAY)) (g_stSAMP->pPools->pPlayer->pLocalPlayer, msg);
	}
}

void addClientCommand(char* name, CMDPROC function)
{
	if (name == NULL || function == NULL || (g_Input == NULL && g_Input037 == NULL))
		return;

	if (samp037)
		((void(__thiscall*) (void* _this, char* command, CMDPROC function)) (g_SAMP + SAMP037_FUNC_ADDCLIENTCMD)) (g_Input037, name, function);
	else
		((void(__thiscall*) (void* _this, char* command, CMDPROC function)) (g_SAMP + SAMP_FUNC_ADDCLIENTCMD)) (g_Input, name, function);
}

bool ValidPlayer(int PlayerID)
{
	if (samp037)
	{
		if (g_stSAMP037->pPools->pPlayer == NULL)
			return 0;

		if (PlayerID < 0 || PlayerID > SAMP_MAX_PLAYERS)
			return 0;

		if (PlayerID == g_stSAMP037->pPools->pPlayer->sLocalPlayerID)
			return 0;

		if (g_stSAMP037->pPools->pPlayer->iIsListed[PlayerID] != 1)
			return 0;
	}
	else
	{
		if (g_stSAMP->pPools->pPlayer == NULL)
			return 0;

		if (PlayerID < 0 || PlayerID > SAMP_MAX_PLAYERS)
			return 0;

		if (PlayerID == g_stSAMP->pPools->pPlayer->sLocalPlayerID)
			return 0;

		if (g_stSAMP->pPools->pPlayer->iIsListed[PlayerID] != 1)
			return 0;
	}
	return 1;
}

int near_zero(float v)
{
	if (!isfinite(v))
		return 1;
	return fabs(v) < FLOAT_EPSILON;
}


int vect3_near_zero(const float in[3])
{
	//if ( !isfinite(in[0]) || !isfinite(in[1]) || !isfinite(in[2]) )
	//	return 1;
	return near_zero(in[0]) && near_zero(in[1]) && near_zero(in[2]);
}

void vect3_copy(const float in[3], float out[3])
{
	memcpy(out, in, sizeof(float) * 3);
}

float vect3_length(const float in[3])
{
	return sqrtf(in[0] * in[0] + in[1] * in[1] + in[2] * in[2]);
}


void vect3_vect3_sub(const float in1[3], const float in2[3], float out[3])
{
	int i;

	for (i = 0; i < 3; i++)
		out[i] = in1[i] - in2[i];
}

float vect3_dist(const float in1[3], const float in2[3])
{
	float	dist[3];

	vect3_vect3_sub(in1, in2, dist);
	return vect3_length(dist);
}

int getPlayerPos(int iPlayerID, float fPos[3])
{
	struct actor_info* pActor = NULL;
	struct vehicle_info* pVehicle = NULL;

	struct actor_info* pSelfActor = actor_info_get_self();

	if (samp037)
	{
		if (g_stSAMP037->pPools->pPlayer == NULL)
			return 0;
		if (g_stSAMP037->pPools->pPlayer->iIsListed[iPlayerID] != 1)
			return 0;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID] == NULL)
			return 0;
		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
			return 0;

		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
			return 0;	// not streamed
		else
		{
			pActor = g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;

			vect3_copy(&pActor->base.matrix[4 * 3], fPos);
		}

		if (pSelfActor != NULL)
		{
			if (vect3_dist(&pSelfActor->base.matrix[4 * 3], fPos) < 100.0f)
				vect3_copy(&pActor->base.matrix[4 * 3], fPos);
		}

		// detect zombies
		if (vect3_near_zero(fPos))
			vect3_copy(&pActor->base.matrix[4 * 3], fPos);
	}
	else
	{
		if (g_stSAMP->pPools->pPlayer == NULL)
			return 0;
		if (g_stSAMP->pPools->pPlayer->iIsListed[iPlayerID] != 1)
			return 0;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID] == NULL)
			return 0;
		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
			return 0;

		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
			return 0;	// not streamed
		else
		{
			pActor = g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;

			vect3_copy(&pActor->base.matrix[4 * 3], fPos);
		}

		if (pSelfActor != NULL)
		{
			if (vect3_dist(&pSelfActor->base.matrix[4 * 3], fPos) < 100.0f)
				vect3_copy(&pActor->base.matrix[4 * 3], fPos);
		}

		// detect zombies
		if (vect3_near_zero(fPos))
			vect3_copy(&pActor->base.matrix[4 * 3], fPos);
	}

	return !vect3_near_zero(fPos);
}

void GetAimingCenter(float& x, float& y)
{
	if (GetCurrentWeapon() != 34)
	{
		x = (float)pD3DHook->pPresentParam.BackBufferWidth * 0.5299999714f;
		y = (float)pD3DHook->pPresentParam.BackBufferHeight * 0.4f;
	}
	else
	{
		x = (float)pD3DHook->pPresentParam.BackBufferWidth / 2.f;
		y = (float)pD3DHook->pPresentParam.BackBufferHeight / 2.f;
	}
	
	return;
}

bool isInsideCircle(float circle_x, float circle_y,
	float rad, float x, float y)
{
	if ((x - circle_x) * (x - circle_x) +
		(y - circle_y) * (y - circle_y) <= rad * rad)
		return true;
	else
		return false;
}

void CalcScreenCoors(D3DXVECTOR3* vecWorld, D3DXVECTOR3* vecScreen)
{
	/** C++-ifyed function 0x71DA00, formerly called by CHudSA::CalcScreenCoors **/
	// Get the static view matrix as D3DXMATRIX
	D3DXMATRIX	m((float*)(0xB6FA2C));

	// Get the static virtual screen (x,y)-sizes
	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	//DWORD *dwLenZ = (DWORD*)(0xC1704C);
	//double aspectRatio = (*dwLenX) / (*dwLenY);
	// Do a transformation
	vecScreen->x = (vecWorld->z * m._31) + (vecWorld->y * m._21) + (vecWorld->x * m._11) + m._41;
	vecScreen->y = (vecWorld->z * m._32) + (vecWorld->y * m._22) + (vecWorld->x * m._12) + m._42;
	vecScreen->z = (vecWorld->z * m._33) + (vecWorld->y * m._23) + (vecWorld->x * m._13) + m._43;

	// Get the correct screen coordinates
	double	fRecip = (double)1.0 / vecScreen->z;	//(vecScreen->z - (*dwLenZ));
	vecScreen->x *= (float)(fRecip * (*dwLenX));
	vecScreen->y *= (float)(fRecip * (*dwLenY));
}

void CalcWorldCoors(D3DXVECTOR3* vecScreen, D3DXVECTOR3* vecWorld)
{
	// Get the static view matrix as D3DXMATRIX
	D3DXMATRIX	m((float*)(0xB6FA2C));

	// Invert the view matrix
	D3DXMATRIX minv;
	memset(&minv, 0, sizeof(D3DXMATRIX));
	m._44 = 1.0f;
	D3DXMatrixInverse(&minv, NULL, &m);

	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	// Reverse screen coordinates
	double fRecip = (double)1.0 / vecScreen->z;
	vecScreen->x /= (float)(fRecip * (*dwLenX));
	vecScreen->y /= (float)(fRecip * (*dwLenY));

	// Do an (inverse) transformation
	vecWorld->x = (vecScreen->z * minv._31) + (vecScreen->y * minv._21) + (vecScreen->x * minv._11) + minv._41;
	vecWorld->y = (vecScreen->z * minv._32) + (vecScreen->y * minv._22) + (vecScreen->x * minv._12) + minv._42;
	vecWorld->z = (vecScreen->z * minv._33) + (vecScreen->y * minv._23) + (vecScreen->x * minv._13) + minv._43;
}

float fWeaponRange[39] =
{
	0.0, // 0 - Fist
	0.0, // 1 - Brass knuckles
	0.0, // 2 - Golf club
	0.0, // 3 - Nitestick
	0.0, // 4 - Knife
	0.0, // 5 - Bat
	0.0, // 6 - Shovel
	0.0, // 7 - Pool cue
	0.0, // 8 - Katana
	0.0, // 9 - Chainsaw
	0.0, // 10 - Dildo
	0.0, // 11 - Dildo 2
	0.0, // 12 - Vibrator
	0.0, // 13 - Vibrator 2
	0.0, // 14 - Flowers
	0.0, // 15 - Cane
	0.0, // 16 - Grenade
	0.0, // 17 - Teargas
	0.0, // 18 - Molotov
	90.0, // 19 - Vehicle M4 (custom)
	75.0, // 20 - Vehicle minigun (custom)
	0.0, // 21
	35.0, // 22 - Colt 45
	35.0, // 23 - Silenced
	35.0, // 24 - Deagle
	40.0, // 25 - Shotgun
	35.0, // 26 - Sawed-off
	40.0, // 27 - Spas
	35.0, // 28 - UZI
	45.0, // 29 - MP5
	70.0, // 30 - AK47
	90.0, // 31 - M4
	35.0, // 32 - Tec9
	100.0, // 33 - Cuntgun
	320.0, // 34 - Sniper
	0.0, // 35 - Rocket launcher
	0.0, // 36 - Heatseeker
	0.0, // 37 - Flamethrower
	75.0  // 38 - Minigun
};

const char* getPlayerName(int iPlayerID)
{
	if (samp037)
	{
		if (g_stSAMP037->pPools->pPlayer == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;

		if (iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;

		if (iPlayerID == g_stSAMP037->pPools->pPlayer->sLocalPlayerID)
			return g_stSAMP037->pPools->pPlayer->strLocalPlayerName.c_str();

		if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID] == NULL)
			return NULL;

		return g_stSAMP037->pPools->pPlayer->pRemotePlayer[iPlayerID]->strPlayerName.c_str();
	}
	else
	{
		if (g_stSAMP->pPools->pPlayer == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;

		if (iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
			return NULL;

		if (iPlayerID == g_stSAMP->pPools->pPlayer->sLocalPlayerID)
			return g_stSAMP->pPools->pPlayer->strLocalPlayerName.c_str();

		if (g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID] == NULL)
			return NULL;

		return g_stSAMP->pPools->pPlayer->pRemotePlayer[iPlayerID]->strPlayerName.c_str();
	}
	return NULL;
}


D3DCOLOR samp_color_get(int id, DWORD trans)
{
	if (g_SAMP == NULL)
		return NULL;

	D3DCOLOR* color_table;
	if (id < 0 || id >= (SAMP_MAX_PLAYERS + 3))
		return D3DCOLOR_ARGB(0xFF, 0xff, 0xff, 0xff);

	switch (id)
	{
	case (SAMP_MAX_PLAYERS):
		return 0xFF888888;

	case (SAMP_MAX_PLAYERS + 1):
		return 0xFF0000AA;

	case (SAMP_MAX_PLAYERS + 2):
		return 0xFF63C0E2;
	}

	if (samp037) color_table = (D3DCOLOR*)((uint8_t*)g_SAMP + SAMP037_COLOR_OFFSET);
	else color_table = (D3DCOLOR*)((uint8_t*)g_SAMP + SAMP_COLOR_OFFSET);

	return (color_table[id] >> 8) | trans;
}

void traceLastFunc(char* func)
{
	/*DeleteFile("silentaim.log");

	std::ofstream file;
	file.open("silentaim.log", std::ios::app);
	if (file.is_open())
	{
		file << "Last Function Traced: " << func << "\n";
		file.close();
	}*/
	return;
}

void ReloadFriendlist()
{
	FriendsListLoaded = true;
	Friends.clear();
	std::ifstream file(".\\silentaim_friends.ini");
	if (!file.is_open())
	{
		std::ofstream dictFileEx(".\\silentaim_friends.ini");
		if (file.is_open())
		{
			dictFileEx << "[dont_remove_this]";
		}
		dictFileEx.close();
		FriendsListLoaded = false;
	}
	else
	{
		std::string temp;
		while (!file.eof())
		{
			file >> temp;
			Friends.push_back(temp);
		}
	}
	file.close();
}

bool IsPlayingAnimationAInfo(actor_info* act, char* szAnimName)
{
	DWORD dwReturn = 0;
	DWORD dwFunc = FUNC_RpAnimBlendClumpGetAssociation;
	DWORD dwThis = (DWORD)act;

	_asm
	{
		push    szAnimName
		push    dwThis
		call    dwFunc
		add     esp, 8
		mov     dwReturn, eax
	}
	if (dwReturn)
		return true;
	else
		return false;
}

int GetSilentAimTarget()
{
	if (g_SAMP == NULL)
		return -1;

	int			targetID = -1;

	traceLastFunc("GetSilentAimTarget() -- 1");

	if (samp037)
	{
		if (!g_stSAMP037->pPools->pPlayer || !g_stSAMP037->pPools->pPlayer->pLocalPlayer)
			return -1;

		traceLastFunc("GetSilentAimTarget() -- 2 [BRANCH: 037]");

		D3DXVECTOR3 poss, screenposs;
		float		centerX, centerY;
		CVector2D screenPosition;

		GetAimingCenter(centerX, centerY);

		traceLastFunc("GetSilentAimTarget() -- 3 [BRANCH: 037]");

		CVector src;

		silentaim_lastAimDist = 0.0;

		traceLastFunc("GetSilentAimTarget() -- 4 [BRANCH: 037]");

		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!ValidPlayer(i) || !IsPlayerStreamed(i)) continue;

			struct actor_info* targetact = g_stSAMP037->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped;

			float fPos[3];
			getPlayerPos(i, fPos);

			fPos[2] += 0.35;

			poss.x = fPos[0];
			poss.y = fPos[1];
			poss.z = fPos[2];
			CalcScreenCoors(&poss, &screenposs);

			screenPosition.fX = screenposs.x;
			screenPosition.fY = screenposs.y;

			traceLastFunc("GetSilentAimTarget() -- 5 [BRANCH: 037]");

			if (!isInsideCircle(centerX, centerY, silentaim_fov + 10.0, screenPosition.fX, screenPosition.fY))
				continue;

			double distance = sqrt(((centerX - screenPosition.fX) * (centerX - screenPosition.fX)) +
				((centerY - screenPosition.fY) * (centerY - screenPosition.fY)));

			src.fX = fPos[0];
			src.fY = fPos[1];
			src.fZ = fPos[2];

			traceLastFunc("GetSilentAimTarget() -- 6 [BRANCH: 037]");

			if (screenposs.z < 1.f)
				continue;

			if (distance > silentaim_lastAimDist && silentaim_lastAimDist != 0.0)
				continue;

			CVector campos;
			float fPosSelf[3];

			vect3_copy(&g_stSAMP037->pPools->pPlayer->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3], fPosSelf);
			fPosSelf[2] += 0.35;
			campos.fX = fPosSelf[0];
			campos.fY = fPosSelf[1];
			campos.fZ = fPosSelf[2];

			// FILTERS
			
			if (!silentaim_outOfRangeFilter && vect3_dist(fPos, fPosSelf) > fWeaponRange[GetCurrentWeapon()] + 3.0)
			{
				continue;
			}

			traceLastFunc("GetSilentAimTarget() -- 7 [BRANCH: 037]");

			bool IsPlayerAfk = g_stSAMP037->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->iAFKState == 2;

			bool IsPlayerVisible = IsLineOfSightClear(&campos, &src, true, false, false, true, true, false, false);

			bool IsPlayerAlive = true;

			//if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->fActorHealth <= 0.9f) IsPlayerAlive = false; // this is bugged

			traceLastFunc("GetSilentAimTarget() -- 8 [BRANCH: 037]");

			/*if (iterPed->IsPlayingAnimation("SWEET_INJUREDLOOP")) IsPlayerAlive = false;
			if (iterPed->IsPlayingAnimation("CS_DEAD_GUY")) IsPlayerAlive = false;
			if (iterPed->IsPlayingAnimation("KO_SKID_FRONT")) IsPlayerAlive = false;
			if (iterPed->IsPlayingAnimation("KO_SKID_BACK")) IsPlayerAlive = false;*/

			if (silentaim_teamFilter && g_stSAMP037->pPools->pPlayer->pLocalPlayer->byteTeamID2 != 255)
			{
				if (g_stSAMP037->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->byteTeamID == g_stSAMP037->pPools->pPlayer->pLocalPlayer->byteTeamID2)
					continue;
			}

			if (silentaim_colorFilter && samp_color_get(i) == samp_color_get(g_stSAMP037->pPools->pPlayer->sLocalPlayerID))
				continue;

			if (silentaim_skinFilter &&
				g_stSAMP037->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.model_alt_id == g_stSAMP037->pPools->pPlayer->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.model_alt_id)
				continue;

			if (!silentaim_wallHack && !IsPlayerVisible)
				continue;

			if (silentaim_afkFilter && IsPlayerAfk)
				continue;

			if (silentaim_aliveFilter && !IsPlayerAlive)
				continue;

			traceLastFunc("GetSilentAimTarget() -- 9 [BRANCH: 037]");

			if (silentaim_friendFilter && Friends.size() > 0 && FriendsListLoaded)
			{
				if (std::find(Friends.begin(), Friends.end(), getPlayerName(i)) != Friends.end()) continue;
			}

			traceLastFunc("GetSilentAimTarget() -- 10 [BRANCH: 037]");

			// FILTERS END

			silentaim_lastAimDist = (float)distance;
			targetID = i;
		}
	}
	else
	{
		if (!g_stSAMP->pPools->pPlayer || !g_stSAMP->pPools->pPlayer->pLocalPlayer)
			return -1;

		traceLastFunc("GetSilentAimTarget() -- 2");

		D3DXVECTOR3 poss, screenposs;
		float		centerX, centerY;
		CVector2D screenPosition;

		GetAimingCenter(centerX, centerY);

		traceLastFunc("GetSilentAimTarget() -- 3");

		CVector src;

		traceLastFunc("GetSilentAimTarget() -- 4");

		silentaim_lastAimDist = 0.0;

		for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
		{
			if (!ValidPlayer(i) || !IsPlayerStreamed(i)) continue;

			struct actor_info* targetact = g_stSAMP->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped;

			float fPos[3];
			getPlayerPos(i, fPos);
			fPos[2] += 0.35;

			poss.x = fPos[0];
			poss.y = fPos[1];
			poss.z = fPos[2];
			CalcScreenCoors(&poss, &screenposs);

			screenPosition.fX = screenposs.x;
			screenPosition.fY = screenposs.y;

			traceLastFunc("GetSilentAimTarget() -- 5");

			if (!isInsideCircle(centerX, centerY, silentaim_fov + 10.0, screenPosition.fX, screenPosition.fY))
				continue;

			double distance = sqrt(((centerX - screenPosition.fX) * (centerX - screenPosition.fX)) +
				((centerY - screenPosition.fY) * (centerY - screenPosition.fY)));

			src.fX = fPos[0];
			src.fY = fPos[1];
			src.fZ = fPos[2];

			traceLastFunc("GetSilentAimTarget() -- 6");

			if (screenposs.z < 1.f)
				continue;

			if (distance > silentaim_lastAimDist && silentaim_lastAimDist != 0.0)
				continue;

			CVector campos;
			float fPosSelf[3];

			vect3_copy(&g_stSAMP->pPools->pPlayer->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3], fPosSelf);
			fPosSelf[2] += 0.35;
			campos.fX = fPosSelf[0];
			campos.fY = fPosSelf[1];
			campos.fZ = fPosSelf[2];

			// FILTERS


			if (!silentaim_outOfRangeFilter && vect3_dist(fPos, fPosSelf) > fWeaponRange[GetCurrentWeapon()] + 3.0)
			{
				continue;
			}

			traceLastFunc("GetSilentAimTarget() -- 7");

			bool IsPlayerAfk = g_stSAMP->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->iAFKState == 2;

			bool IsPlayerVisible = IsLineOfSightClear(&campos, &src, true, false, false, true, true, false, false);

			bool IsPlayerAlive = true;

			//if (g_stSAMP->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->fActorHealth <= 0.9f) IsPlayerAlive = false;

			traceLastFunc("GetSilentAimTarget() -- 8");

			/*if (iterPed->IsPlayingAnimation("SWEET_INJUREDLOOP")) IsPlayerAlive = false;
			if (iterPed->IsPlayingAnimation("CS_DEAD_GUY")) IsPlayerAlive = false;
			if (iterPed->IsPlayingAnimation("KO_SKID_FRONT")) IsPlayerAlive = false;
			if (iterPed->IsPlayingAnimation("KO_SKID_BACK")) IsPlayerAlive = false;*/

			if (silentaim_teamFilter && g_stSAMP->pPools->pPlayer->pLocalPlayer->byteTeamID2 != 255)
			{
				if (g_stSAMP->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->byteTeamID == g_stSAMP->pPools->pPlayer->pLocalPlayer->byteTeamID2)
					continue;
			}

			if (silentaim_colorFilter && samp_color_get(i) == samp_color_get(g_stSAMP->pPools->pPlayer->sLocalPlayerID))
				continue;

			if (silentaim_skinFilter &&
				g_stSAMP->pPools->pPlayer->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.model_alt_id == g_stSAMP->pPools->pPlayer->pLocalPlayer->pSAMP_Actor->pGTA_Ped->base.model_alt_id)
				continue;

			if (!silentaim_wallHack && !IsPlayerVisible)
				continue;

			if (silentaim_afkFilter && IsPlayerAfk)
				continue;

			if (silentaim_aliveFilter && !IsPlayerAlive)
				continue;

			if (silentaim_friendFilter && Friends.size() > 0 && FriendsListLoaded)
			{
				if (std::find(Friends.begin(), Friends.end(), getPlayerName(i)) != Friends.end()) continue;
			}

			traceLastFunc("GetSilentAimTarget() -- 9");

			// FILTERS END

			silentaim_lastAimDist = (float)distance;
			targetID = i;
			traceLastFunc("GetSilentAimTarget() -- 10");
		}
	}
	return targetID;
}