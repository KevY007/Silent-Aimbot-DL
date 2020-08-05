#include "main.h"

void CPed::teleportTo(float x, float y, float z)
{
	//set x, y, z to some coordinates
	pCpedCoords->coords.m_XPos = x;
	pCpedCoords->coords.m_YPos = y;
	pCpedCoords->coords.m_ZPos = z;
}

bool CPed::teleportToWayPoint()
{
	float* wayPointXPtr = (float*)WAYPOINT_X_ADDY; //waypoint x addy pointer
	float* wayPointYPtr = (float*)WAYPOINT_Y_ADDY; //waypoint y addy pointer
	int* wayPointFlags = (int*)WAYPOINT_FLAGS_ADDY; //flags waypoint addy pointer
	if (*wayPointFlags == NO_WAYPOINT) // if waypoint not in map
	{
		return false; // return false
	}
	teleportTo(*wayPointXPtr, *wayPointYPtr, this->pCpedCoords->coords.m_ZPos); // teleport to waypoint coords
	return true;
}

bool CPed::IsPlayingAnimation(uint32_t animID)
{
	DWORD dwReturn = 0;
	DWORD dwThis = (DWORD)this;
	DWORD dwFunc = FUNC_RpAnimBlendClumpGetAssociation_int;

	_asm
	{
		push    animID
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

bool CPed::IsPlayingAnimation(char* szAnimName)
{
	DWORD dwReturn = 0;
	DWORD dwFunc = FUNC_RpAnimBlendClumpGetAssociation;
	DWORD dwThis = (DWORD)this;

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