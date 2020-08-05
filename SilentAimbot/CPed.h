#include "main.h"

//some addresses and flags
#define NO_WAYPOINT 256
#define WAYPOINT_FLAGS_ADDY 0xBA97A4
#define WAYPOINT_X_ADDY 0xBA9788
#define WAYPOINT_Y_ADDY 0xBA978C

class CPedLocations
{
public:
	float m_rotationMatrix[12];
	struct CPedCoords
	{
		float m_XPos; //0x0030
		float m_YPos; //0x0034
		float m_ZPos;
	}coords;//0x0038 ;
}; //Size=0x003C

class CPed
{
public:
	char pad_0x0000[0x14]; //0x0000
	CPedLocations* pCpedCoords; //0x0014
	char pad_0x0018[0x528]; //0x0018
	float m_Health; //0x0540
	float m_maxHealth; //0x0544
	float m_Armor; //0x0548
	char pad_0x054C[0x8C]; //0x054C
	int m_pistolType; //0x05D8
	int m_pistolState; //0x05DC
	int m_pistolClips; //0x05E0
	int m_pistolTotalAmmo; //0x05E4
	char pad_0x05E8[0xC]; //0x05E8
	int m_shotgunType; //0x05F4
	int m_shotgunState; //0x05F8
	int m_shotgunClips; //0x05FC
	int m_shotgunTotalAmmo; //0x0600
	char pad_0x0604[0x13C]; //0x0604
	char m_curWeapID; //0x0740
	char pad_0x0741[0x8FF]; //0x0741

	void teleportTo(float x, float y, float z);
	bool teleportToWayPoint();
	bool IsPlayingAnimation(char* szAnimName);
	bool IsPlayingAnimation(uint32_t animID);
}; //Size=0x1040