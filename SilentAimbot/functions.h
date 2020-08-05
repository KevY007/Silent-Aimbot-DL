#pragma once

#include "main.h"

#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

#ifndef byte
typedef unsigned char byte;
#endif

// maps unsigned 8 bits/channel to D3DCOLOR // Copied from d3d9types with love.
#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

#define D3DCOLOR_XYUV(y,u,v)   D3DCOLOR_ARGB(0xff,y,u,v)
#define D3DCOLOR_AYUV(a,y,u,v) D3DCOLOR_ARGB(a,y,u,v)

// maps floating point channels (0.f to 1.f range) to D3DCOLOR
#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))

#pragma pack(push, 1)


enum Limits
{
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 2100,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
	SAMP_MAX_MAPICONS = 100,
};

struct stBulletData
{
	uint8_t		byteType;
	uint16_t	sTargetID;
	float		fOrigin[3];
	float		fTarget[3];
	float		fCenter[3];
	uint8_t		byteWeaponID;
};

enum Gamestate
{
	GAMESTATE_WAIT_CONNECT = 9,
	GAMESTATE_CONNECTING = 13,
	GAMESTATE_AWAIT_JOIN = 15,
	GAMESTATE_CONNECTED = 14,
	GAMESTATE_RESTARTING = 18
};
struct stOnFootData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys*	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	short		sCurrentAnimationID;
	short		sAnimFlags;
};

struct stInCarData
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys*	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
		float       fBikeSideAngle;
	};
};

struct stSAMP_037
{
	void* pUnk0;
	struct stServerInfo_037* pServerInfo;
	uint8_t					byteSpace[24];
	char					szIP[257];
	char					szHostname[259];
	bool					bNametagStatus; // changes by /nametagstatus
	uint32_t				ulPort;
	uint32_t				ulMapIcons[100];
	int						iLanMode;
	int						iGameState;
	uint32_t				ulConnectTick;
	struct stServerPresets_037* pSettings;
	void* pRakClientInterface;
	struct stSAMPPools_037* pPools;
};

struct stChatEntry_037
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stFontRenderer_037
{
	void* m_pChatFont;
	void* m_pLittleFont;
	void* m_pChatShadowFont;
	void* m_pLittleShadowFont;
	void* m_pCarNumberFont;
	void* m_pTempSprite;
	void* m_pD3DDevice;
	char* m_pszTextBuffer;
};

struct stChatInfo_037
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	struct stChatEntry_037	chatEntry[100];
	stFontRenderer_037* m_pFontRenderer;
	void* m_pChatTextSprite;
	void* m_pSprite;
	void* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void* pID3DXRenderToSurface;
	void* m_pTexture;
	void* pSurface;
	void* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
	int					m_iTimeStampTextOffset;
};

struct stInputBox_037
{
	void* pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unk;
	DWORD	dwPosChatInput[2];
	uint8_t	unk2[263];
	int		iCursorPosition;
	uint8_t	unk3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unk4[20];
	int		iMouseLeftButton;
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct stInputInfo_037
{
	void* pD3DDevice;
	void* pDXUTDialog;
	stInputBox_037* pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;
};

struct stTextdraw_037
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct stTextdrawPool_037
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw_037* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw_037* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stServerInfo_037 {
	uint32_t 			uiIP;
	uint16_t 			usPort;

	// ...

};

struct stServerPresets_037
{
	uint8_t byteCJWalk;
	int m_iDeathDropMoney;
	float	fWorldBoundaries[4];
	bool m_bAllowWeapons;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	bool m_byteHoldTime;
	bool m_bInstagib;
	bool m_bZoneNames;
	bool m_byteFriendlyFire;
	int		iClassesAvailable;
	float	fNameTagsDistance;
	bool m_bManualVehicleEngineAndLight;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	int iPlayerMarkersMode;
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
	bool m_bLimitGlobalChatRadius;
};

struct stSAMPKeys_037
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stOnFootData_037
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys_037	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	short		sCurrentAnimationID;
	short		sAnimFlags;
};

struct stInCarData_037
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys*	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
	};
};

struct stVehiclePool_037
{
	int						iVehicleCount;
	void* pUnk0;
	uint8_t					byteSpace1[0x112C];
	struct stSAMPVehicle* pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	struct vehicle_info* pGTA_Vehicle[SAMP_MAX_VEHICLES];
	uint8_t					byteSpace2[SAMP_MAX_VEHICLES * 6];
	uint32_t				ulShit[SAMP_MAX_VEHICLES];
	int						iIsListed2[SAMP_MAX_VEHICLES];
	uint32_t				byteSpace3[SAMP_MAX_VEHICLES * 2];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;
};

struct stSAMPPools_037
{
	struct stActorPool_037* pActor;
	struct stObjectPool_037* pObject;
	struct stGangzonePool_037* pGangzone;
	struct stTextLabelPool_037* pText3D;
	struct stTextdrawPool_037* pTextdraw;
	void* pPlayerLabels;
	struct stPlayerPool_037* pPlayer;
	struct stVehiclePool_037* pVehicle;
	struct stPickupPool_037* pPickup;
};

struct stPlayerPool_037
{
	uint32_t				ulMaxPlayerID;
	uint16_t				sLocalPlayerID;
	void* pVTBL_txtHandler;
	std::string				strLocalPlayerName;
	struct stLocalPlayer_037* pLocalPlayer;
	int						iLocalPlayerPing;
	int						iLocalPlayerScore;
	struct stRemotePlayer_037* pRemotePlayer[SAMP_MAX_PLAYERS];
	int						iIsListed[SAMP_MAX_PLAYERS];
	DWORD						dwPlayerIP[SAMP_MAX_PLAYERS]; // always 0
};

struct stDamageData
{
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};

struct stHeadSync
{
	float	fHeadSync[3];
	int		iHeadSyncUpdateTick;
	int		iHeadSyncLookTick;
};

struct stSurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnk0;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	struct stSAMPVehicle* pSurfingVehicle;
	int			iUnk1;
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};

struct stAimData_037
{
	BYTE	byteCamMode;
	float	vecAimf1[3];
	float	vecAimPos[3];
	float	fAimZ;
	BYTE	byteCamExtZoom : 6;		// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	bUnk;
};


struct stTrailerData_037
{
	uint16_t	sTrailerID;
	float		fPosition[3];
	float		fQuaternion[4];
	float		fSpeed[3];
	float		fSpin[3];
};

struct stSAMPKeys
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stPassengerData_037
{
	uint16_t	sVehicleID;
	uint8_t		byteSeatID;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct object_base
{
#pragma pack( 1 )
	void* vtbl;	// 0

	// this is now in CEntity
	//	CPlaceableSAInterface	Placeable;	// 4
	// but the following variables exist for compatability till we remove object_base completely
	float					coords[3];			// 4
	union
	{
		// is MTA right?
		float			m_heading;				// 16

		// and are we wrong?
		void* m_CMatrixPre;			// 16, a part of CPlaceable
		float* preMatrix;				// 16, a part of CPlaceable
		void* preMatrixStruct;		// 16, a part of CPlaceable
	};
	union
	{
		void* m_CMatrix;				// 20
		float* matrix;				// 20
		void* matrixStruct;			// 20
	};

	void* m_pRwObject;				// 24

	/********** BEGIN CFLAGS **************/
	unsigned long	bUsesCollision : 1;			// does entity use collision
	unsigned long	bCollisionProcessed : 1;	// has object been processed by a ProcessEntityCollision function
	unsigned long	bIsStatic : 1;			// is entity static
	unsigned long	bHasContacted : 1;		// has entity processed some contact forces
	unsigned long	bIsStuck : 1;			// is entity stuck
	unsigned long	bIsInSafePosition : 1;	// is entity in a collision free safe position
	unsigned long	bWasPostponed : 1;		// was entity control processing postponed
	unsigned long	bIsVisible : 1;			//is the entity visible
	unsigned long	bIsBIGBuilding : 1;		// Set if this entity is a big building
	unsigned long	bRenderDamaged : 1;		// use damaged LOD models for objects with applicable damage
	unsigned long	bStreamingDontDelete : 1;	// Dont let the streaming remove this
	unsigned long	bRemoveFromWorld : 1;		// remove this entity next time it should be processed
	unsigned long	bHasHitWall : 1;			// has collided with a building (changes subsequent collisions)
	unsigned long	bImBeingRendered : 1;		// don't delete me because I'm being rendered
	unsigned long	bDrawLast : 1;			// draw object last
	unsigned long	bDistanceFade : 1;		// Fade entity because it is far away
	unsigned long	bDontCastShadowsOn : 1; // Dont cast shadows on this object
	unsigned long	bOffscreen : 1;			// offscreen flag. This can only be trusted when it is set to true
	unsigned long	bIsStaticWaitingForCollision : 1;	// this is used by script created entities - they are static until the collision is loaded below them
	unsigned long	bDontStream : 1;			// tell the streaming not to stream me
	unsigned long	bUnderwater : 1;			// this object is underwater change drawing order
	unsigned long	bHasPreRenderEffects : 1;	// Object has a prerender effects attached to it
	unsigned long	bIsTempBuilding : 1;		// whether or not the building is temporary (i.e. can be created and deleted more than once)
	unsigned long	bDontUpdateHierarchy : 1;	// Don't update the aniamtion hierarchy this frame
	unsigned long	bHasRoadsignText : 1;		// entity is roadsign and has some 2deffect text stuff to be rendered
	unsigned long	bDisplayedSuperLowLOD : 1;
	unsigned long	bIsProcObject : 1;			// set object has been generate by procedural object generator
	unsigned long	bBackfaceCulled : 1;		// has backface culling on
	unsigned long	bLightObject : 1;			// light object with directional lights
	unsigned long	bUnimportantStream : 1;		// set that this object is unimportant, if streaming is having problems
	unsigned long	bTunnel : 1;			// Is this model part of a tunnel
	unsigned long	bTunnelTransition : 1;	// This model should be rendered from within and outside of the tunnel

	/********** END CFLAGS **************/
	uint8_t			wSeedColFlags;			// 32
	uint8_t			wSeedVisibleFlags;		// 33
	uint16_t		model_alt_id;			// 34 - model index
	uint8_t			__unknown_36[4];		// 36 - collision related (objects only?)

	//CReferences *pReferences; //36
	uint32_t* m_pLastRenderedLink;	// 40 CLink<CEntity*>* m_pLastRenderedLink;
	uint16_t		timer;			// 44
	uint8_t			m_iplIndex;		// 46 used to define which IPL file object is in
	uint8_t			interior_id;	// 47
	uint8_t			__unknown_48[6];		// 48

	//********* BEGIN CEntityInfo **********//
	uint8_t			nType : 3;				// 54 what type is the entity (2 == Vehicle)
	uint8_t			nStatus : 5;			// 54 control status

	// 55 alignment
	//********* END CEntityInfo **********//
	uint8_t			__unknown_56[8];		// 56
	uint8_t			quantumPhysics;			// 64 // this really needs to be figured out cos it's probably a bit field
	uint8_t			nImmunities;			// 65
	uint8_t			__unknown_66;			// 66
};

struct object_info
{
#pragma pack( 1 )
	struct object_base	base;
	uint8_t				__unknown_66;			/* 66 */
	uint8_t				flags;	/* 67 - collision and ...? */
	uint8_t				__unknown_68[7];	/* 68 */
	float				physical_height;	/* 75 - normally max. 0.2 (bigger value = more 'ouch' when jumping), different results for different objects? */
	uint8_t				__unknown_79[173];	/* 79 - first value changing when last movement was going up or going down*/
	struct actor_info* actor; /* 252 - pointer to Actor Object is attached to, 0 when not attached */
	uint8_t				__unknown_256[8];	/* 256 */
	float				height_to_actor;	/* 264 - when attached height difference to actor, else 0*/
	uint8_t				__unknown_268[4];	/* 268 */
	float				pitch;	/* 272 - rotation, pitch (attached) */
	float				roll;	/* 276 - rotation, roll (attached) */
	uint8_t				__unknown_280[68];	/* 280 */
	float				scale;	/* 348 - Scale */
	uint8_t				__unknown_352[59];	/* 352 */
};

struct stLocalPlayer037
{
	struct stSAMPPed		*pSAMP_Actor;
	uint16_t				sCurrentAnimID;
	uint16_t				sAnimFlags;
	uint32_t				ulUnk0;
	int						iIsActive;
	int						iIsWasted;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	struct stOnFootData_037		onFootData;
	struct stPassengerData*	passengerData;
	struct stTrailerData*	trailerData;
	struct stInCarData_037		inCarData;
	struct stAimData*		aimData;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					byteUnk1;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2;
	uint16_t				usUnk2;
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid;
	uint16_t				usUnk3;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint16_t				sTargetObjectID;
	uint16_t				sTargetVehicleID;
	uint16_t				sTargetPlayerID;
	struct stHeadSync*		headSyncData;
	uint32_t				ulHeadSyncTick;
	BYTE					byteSpace3[260];
	struct stSurfData*		surfData;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t				ulUnk4;
	uint8_t					byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;
	int						iInitiatedSpectating;
	struct stDamageData*		vehicleDamageData;
};


struct weapon
{
#pragma pack( 1 )
	uint32_t	id;
	uint32_t	state;
	int32_t		ammo_clip;
	int32_t		ammo;
	uint32_t	__unknown_count;
	uint32_t	__goggle;	/* 0 off, 256 on */
	uint32_t	__unknown;
};

struct actor_info
{
#pragma pack( 1 )
	struct object_base	base;				/* 0-65 */
	uint8_t				flags;				/* 66 immunities */
	uint8_t				__unknown_67[1];	/* 67 */
	union	/* 68 */
	{
		struct
		{
			void* m_SpeedVec;
		};
		float	speed[3];
		struct
		{
			void* m_SpeedD3DVec;
		};
	};
	float				spin[3];			/* 80 */
	float				speed_rammed[3];	/* 92 */
	float				spin_rammed[3];		/* 104 */
	uint8_t				__unknown_116[60];	/* 116 */
	void* __unknown_176;		/* 176 - pointer to a "entry node info" pool item */
	void* __unknown_180;		/* 180 - pointer to a "ptr node Double" pool item */

	//collision data
	DWORD				collision_flags;	/* 184 - 2nd byte = currently colliding 1/0, or actively
										  running against (0x2), 3rd byte = type colliding with
										  (1 = road, 4=pavement, 35 = object, 3f=car).. unsure about 3rd byte

										  nuck notes: 186 is used to tell if a surface is "steep" too,
										  actually any slight angle at all
										  */
	void* last_touched_object;	/* 188 - You can touch roads - those are considered buildings */
	void* last_collided_object;	/* 192 - pointer to object last collided with (on foot, not jetpack) */
	uint8_t				__unknown_196[16];		/* 196 */
	float				speed_z;			/* 212 */
	float				collision_time_216; /* 216 - collision timer? */
	void* collision_current_obj;		/* 220 - pointer to current thing colliding with */
	uint8_t				collision_something[12];	/* 224 - related to collision */
	float				collision_last_coord[3];	/* 236 - coordination of last collision */

	//end of collision data
	uint8_t				__unknown_248[100];			/* 248 */
	// 252 - animation related
	uint8_t				animation_state;			/* 348 */
	uint8_t				__unknown_349[7];			/* 349 */
	float				step_pos[3];		/* 356 - coordinates, last foot step */
	float				step_pos_before[3]; /* 368 - coordinates, foot step before last one */
	uint8_t				__unknown_380[752]; /* 380 */

	void* unk;			/* 1132 */
	void* pPedIntelligence; /* 1148 */
	void* pPlayerData; /* 1152 */

	uint8_t				__unknown_1156[8]; /* 1156 */

	// relative body-part-positions
	void* pNeck;				/* 1164 - void* pNeck
	  (pChest?)
	   - 4 unknown
	   - float height
	   - float front/back
	   - float left/right
	   - void* pObject
	   (same struct for the following body-part-pointers [except pLeft/RightArm])
	*/
	void* pHead;				/* 1168 */
	void* pLeftArm;			/* 1172 */
	void* pRightArm;			/* 1176 */
	void* pLeftLowArm;		/* 1180 */
	void* pRightLowArm;		/* 1184 */
	void* pLeftLeg;			/* 1188 */
	void* pRightLeg;			/* 1192 */
	void* pLeftLowLeg;		/* 1196 */
	void* pRightLowLeg;		/* 1200 */
	void* pRightMidLeg;		/* 1204 */
	void* pLeftMidLeg;		/* 1208 */
	void* pLeftMidArm;		/* 1212 */
	void* pRightMidArm;		/* 1216 */
	void* pLeftShoulder;		/* 1220 */
	void* pRightShoulder;	/* 1224 */
	void* pChest;			/* 1228 */
	void* pMouth;			/* 1232 */
	// end of body-part-positions

	uint8_t				runningStyle;		/* 1236 - 0x36 = cj, 0x8A = rollerskate,
									0x7F = woozie, 0x75 = crash.. etc. */
	uint8_t				__unknown_1237[7];	/* 1237 */
	float				runspeed;			/* 1244 */
	uint8_t				__unknown_1248[36]; /* 1248 */
	uint16_t			muzzle_flash;		/* 1284 */
	uint8_t				__unknown_1286[6];	/* 1286 */

	void* pedIK;	/* 1292 - Inverse Kinematics */
	uint8_t				__unknown_1324[4];	/* 1324 */

	uint32_t			state;	/* 1328 - ACTOR_STATE_* */
	uint32_t			mstate; /* 1332 - ACTOR_MSTATE_* */
	uint8_t				__unknown_1336[8];	/* 1336 */
	float				hitpoints;			/* 1344 */
	float				hitpoints_max;		/* 1348 - hmm, does not seem to be right.. it's set to "100.1318519" or something like that */
	float				armor;	/* 1352 */
	uint8_t				__unknown_1356[12];		/* 1356 */

	// 1360 and 1364 are using in resetting on-foot position when re-standing up

	float				fCurrentRotation;		/* 1368 */
	float				fTargetRotation;		/* 1372 */
	float				fRotationSpeed;			/* 1376 */
	float				fRotationCalculation;	/* 1380 - is 0.1 when target rotation reached */

	union
	{
		void* pContactEntity;	/* 1384 - touching a CEntitySAInterface */
		struct vehicle_info* vehicle_contact;	/* 1384 - standing on top of vehicle */
	};

	float	vehicle_contact_dist[3];			/* 1388 - distance to the middle of the car standing on */
	float	fPlaneAnglesContactEntity[3];		/* 1400 - Angles of the plane of the contact entity the actor is
													standing on (?) */
	void* item_contact;						/* 1412 - standing on top of vehicle/object/building/...*/
	float	fUnknown_1416;						/* 1416 - only changing when slightly under map */

	union
	{
		//CEntitySAInterface	*CurrentObjective;	/* 1420 - usually current vehicle's entity */
		struct vehicle_info* vehicle;
	};

	uint8_t				__unknown_1424[8];	/* 1424 */
	uint8_t				actor_lock;			/* 1432 */
	uint8_t				__unknown_1433[7];	/* 1433 */
	struct weapon		weapon[13];			/* 1440 */
	uint8_t				__unknown_1804[12]; /* 1804 */
	uint8_t				weapon_slot;		/* 1816 */
	uint8_t				__unknown_1817[3];	/* 1817 */
	void* ptr_autoAimTarget;	/* 1820 - weapon target */
	float				fImpactPos_close[3];/* 1824 - last impact point of close range weapon [fist/knife/csaw/etc.] */
	uint8_t				__unknown_1836[20]; /* 1836 */
	uint32_t			weapon_model;		/* 1856 */
	uint8_t				__unknown_1860[28]; /* 1860 */
	uint32_t			weapon_hit_type;	/* 1888 - last hit by this weapon */
	struct actor_info* weapon_hit_by;		/* 1892 - last hit by this object (usually an actor) */
	uint8_t				__unknown_1889[92]; /* 1896 */
};	/* 1988 */

struct vehicle_info
{
#pragma pack( 1 )
	struct object_base	base;
	uint8_t				flags;			/* 66 - flags */
	uint8_t				__unknown_67;	/* 67 */
	union	/* 68 */
	{
		struct
		{
			void* m_SpeedVec;
		};
		float	speed[3];
	};
	union	/* 80 */
	{
		struct
		{
			void* m_SpinVec;
		};
		float	spin[3];
	};
	float						speed_rammed[3];	/* 92 - speed from collision, will be added to speed[3] */
	float						spin_rammed[3];		/* 104 - spin from collision, will be added to spin[3] */

	uint8_t						__unknown_116[20];	/* 116 */

	// handling should start here
	uint8_t						__unknown_136[4];	/* 136 */
	float						mass;		/* 140 - vehicle mass from handling.cfg */
	float						turn_mass;	/* 144 - turn mass */
	float						grip_div;	/* 148 - grip divisor */
	float						mass_to_grip_mult;		/* 152 - mass to grip multiplier */
	float						fTurnMass;				/* 156 - 0.05 or 0.1 */
	float						grip_level_norm;		/* 160 - normalized grip level */
	float						center_of_mass[3];		/* 164 - center of mass */
	void* __unknown_176;			/* 176 - pointer to a "entry node info" pool item */
	void* __unknown_180;			/* 180 - pointer to a "ptr node Double" pool item */

	//collision data
	DWORD						collision_flags;		/* 184 - 2nd byte = currently colliding 1/0, or actively
										  running against (0x02), being moved/rammed (0x03), 1st byte = 0, if noone inside and colliding
										  with actor, else ever 0x0a*/
	void* last_touched_object;	/* 188 - You can touch roads - those are considered buildings */
	void* last_collided_object;	/* 192 - pointer to last collided object.. not for ALL collisions?!? */
	uint8_t						__unknown_196[20];		/* 196 */
	float						collision_something;	/* 216 - collision timer?*/
	void* collision_current_obj; /* 220 - pointer to current thing colliding with */

	// end of handling should be here
	uint8_t						__unknown_224[12];		/* 224 */
	float						collision_position[3];	/* 236 - last collision coordinates */
	uint8_t						__unknown_248[68];		/* 248 */
	void* __unknown_316;			/* 316 - pointer to this something in this structure */
	uint8_t						__unknown_320[157];		/* 320 */
	uint8_t						in_vehicle;			/* 477 */
	uint8_t						__unknown_478[422]; /* 478 */

	void* pHandlingData;		/* 900 */
	struct physicalFlyParams* pFlyData;			/* 904 */
	uint8_t						__unknown_908[96];	/* 908 */
	uint32_t					hFlagsLocal;		/* 1004 */
	uint8_t						__unknown_1008[56]; /* 1008 - AutoPilot */
	void* m_nVehicleFlags;	/* 1064 - 60 bits/flags */
	uint32_t					m_TimeOfCreation;	/* 1072 - GetTimeInMilliseconds when this vehicle was created. */

	uint8_t						color[4];			/* 1076 - as in carcolors.dat - body, stripe, body2, stripe2 */
	uint8_t						modding[2];			/* 1080 - modding data */
	unsigned short				UpgradeModelID[15];	/* 1082 - attached upgrades */
	float						wheel_size;			/* 1112 */
	unsigned short				CarAlarmState;		/* 1116 - time left for car alarm to sound in ms */
	unsigned short				ForcedRandomSeed;	/* 1118 - if this is non-zero the random wander gets deterministic */
	struct actor_info* passengers[9];		/* 1120 (pointer to the passenger player structs) */

	unsigned char				m_nNumPassengers;	/* 1156 */
	unsigned char				m_nNumGettingIn;	/* 1157 */
	unsigned char				m_nGettingInFlags;	/* 1158 */
	unsigned char				m_nGettingOutFlags; /* 1159 */
	unsigned char				m_nMaxPassengers;	/* 1160 */
	unsigned char				m_windowsOpenFlags; /* 1161 */
	char						m_nNitroBoosts;		/* 1162 */
	char						m_nSpecialColModel; /* 1163 */
	DWORD* pEntityWeAreOnForVisibilityCheck;	/* 1164 - we need a CEntity */
	DWORD* m_pFire;			/* 1168 - CFire*/

	float						steer_angles[2];	/* 1172 - steer angles */
	float						gas_pedal;			/* 1180 - gas pedal */
	float						break_pedal;		/* 1184 - break pedal */

	// 1188
	unsigned char				VehicleCreatedBy;	// Contains information on whether this vehicle can be deleted or not. Probably only need this or IsLocked.
	short						ExtendedRemovalRange;

	// this padding probably isn't in the right place.
	uint8_t						__unknown_1191;

	//1192
	unsigned char				car_bomb : 3;		// 0 = None. 1 = Timed. 2 = On ignition, 3 = remotely set ? 4 = Timed Bomb has been activated. 5 = On ignition has been activated.
	unsigned char				OverrideLights : 2; // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
	unsigned char				WinchType : 2;		// Does this vehicle use a winch?

	// this padding probably isn't in the right place.
	uint8_t						__unknown_1193;

	//1194
	unsigned char				m_GunsCycleIndex : 2;		// Cycle through alternate gun hardpoints on planes/helis
	unsigned char				m_OrdnanceCycleIndex : 2;	// Cycle through alternate ordnance hardpoints on planes/helis

	// 1195
	unsigned char				nUsedForCover;			// Has n number of cops hiding/attempting to hid behind it
	unsigned char				AmmoInClip;				// Used to make the guns on boat do a reload.
	unsigned char				PacMansCollected;
	unsigned char				PedsPositionForRoadBlock;
	unsigned char				NumPedsForRoadBlock;

	//1200
	float						nBodyDirtLevel;			// Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible, it may be altered at any time while vehicle's cycle of lige

	// values used by transmission
	unsigned char				m_nCurrentGear;			/* 1204 */
	float						m_fGearChangeCount;		/* 1205 */
	float						m_fWheelSpinForAudio;	/* 1209 */
	uint8_t						__unknown_1213[3];		/* 1213 */

	float						hitpoints;			/* 1216 */
	void* pulling_truck;		/* 1220 - vehicle_info - pulling truck */
	struct vehicle_info* trailer;			/* 1224 - pointer to the currently attached trailer; 0 if theres no trailer */
	uint8_t						__unknown_1228[44]; /* 1228 */
	uint32_t					door_status;		/* 1272 - car door status (1:Opened 2:Locked) */
	uint8_t						__unknown_1276[148];	/* 1276 */
	uint8_t						vehicle_type;			/* 1424 - VEHICLE_TYPE_* */
	uint8_t						__unknown_1425[19];		/* 1425 */

	union
	{
		struct
		{
			float	m_fTrainSpeed;			/* 1444 - Train speed along rails */
			float	m_fTrainRailDistance;	/* 1448 - Distance along rail starting from first rail node (determines train position when on rails) -max 18106 */
			float	m_fDistanceToNextCarriage;		/* 1452 - Distance to Carriage being infront of this */
		};
		struct
		{
			uint8_t boat_sound_level;				/* 1444 */
			uint8_t car_tire_status[4];				/* 1445 - LF, LR, RF, RR, 0 = ok, 1 = flat, 2 = landing gear up */
			uint8_t door_damage_status[6];			/* 1449 - damage status of doors, 0 = ok, 2 = damaged, 3 = open free, 4 = lost */
		};
	};

	// light damage states
	//uint8_t			lights;						/* 1456 - Light status, 0 = no dmg, 1 = front left dmg, 4 = front right dmg, 5 = front dmg, ...+0x40 = ...+back dmg */
	unsigned char		lights_status_frontLeft : 1;
	unsigned char		__unknown_lights_status_2 : 1;
	unsigned char		lights_status_frontRight : 1;
	unsigned char		__unknown_lights_status_4 : 3;
	unsigned char		lights_status_rear : 1;

	// end of light damage states
	uint8_t				__unknown_1457[3];			/* 1457 - 1475 related to doorHood (byte??)*/

	// misc damage states
	unsigned char		car_status_left : 4;		/* 1460 - 0 = ok, 1 = damaged, 2 = free movement, 3 = lost - same status codes for following bumper/windshield */
	unsigned char		car_status_right : 4;
	uint8_t				car_bumper_status;			/* 1461 - unknown */
	unsigned char		car_windshield_status : 4;
	unsigned char		car_bumper_status_front : 4;
	uint8_t				car_bumper_status_rear;
	// end of misc damage states

	void* m_trainFlags;				/* 1464 */
	uint8_t				__unknown_1468[8];			/* 1468 */
	float				doorHood_dist;				/* 1476 - positive = open */
	uint8_t				__unknown_1480[4];			/* 1480 - detachable related*/
	float				doorHood_dist_two;			/* 1484 - positive = open*/
	uint8_t				__unknown_1488[4];			/* 1488 */
	struct vehicle_info* m_train_next_carriage;		/* 1492 */
	uint8_t				__unknown_1496[4];			/* 1496 */
	float				doorTrunk_dist;				/* 1500 - negative = open */
	uint8_t				__unknown_1504[4];			/* 1504 */
	float				doorTrunk_dist_two;			/* 1508 - negative = open */
	uint8_t				__unknown_1512[12];			/* 1512 */
	float				doorOne_dist;				/* 1524 - also for movable part of boats (marquis)*/
	uint8_t				__unknown_1528[4];			/* 1528 */
	union
	{
		struct detachable* detachable_bike1[1];	/* 1532 - bike/motorcycle/car part */
		struct
		{
			float	doorOne_dist_two;			/* 1532 - negative = open */
			uint8_t __unknown_1536[12];			/* 1536 */
			float	doorTwo_dist;				/* 1548 - positive = open */
			uint8_t __unknown_1552[4];			/* 1552 */
			float	doorTwo_dist_two;			/* 1556  - positive = open */
			uint8_t __unknown_1560[12];			/* 1560 */
			float	doorThree_dist;				/* 1572 - negative = open */
			uint8_t __unknown_1576[4];			/* 1576 */
			float	doorThree_dist_two;			/* 1580 - negative = open */
			uint8_t __unknown_1584[12];			/* 1584 */
			float	doorFour_dist;				/* 1596 - positive = open */
			uint8_t __unknown_1600[6];			/* 1600 */
			float	doorFour_dist_two;			/* 1606 - positive = open */
		};
	};
	uint8_t				__unknown_1610[18];		/* 1610 */
	uint8_t				bike_tire_status[2];	/* 1628 Front, Rear, 0 = ok, 1 = flat */
	uint8_t				__unknown_1630[2];		/* 1630 */

	//maybe also door positions in here, like in 15xx?
	struct detachable* detachable_bike2[4];	/* 1632 - bike/motorcycle and boat parts */
	uint8_t				__unknown_1808[8];		/* 1808 */
	float				fPos_FireCarLadder[3];	/* 1816 - train ladder positioning (part of detachables?) */
	struct detachable* detachable_car[4];		/* 1828 - car/helicopter/airplane parts */
	uint8_t				__unknown_2004[12];		/* 2004 */
	float				suspension[4];			/* 2016 - FL, RL, FR, RR suspension height */
	uint8_t				__unknown_2032[244];	/* 2032 */
	float				burn_timer;				/* 2276 - burn timer counting up from 0.0f */
	uint8_t				__unknown_2280[100];	/* 2280 */
	float				fCannonAimX_Y[2];		/* 2380 - cannon offset (x/y) */
	uint8_t				__unknown_2388[48];		/* 2388 */
	float				fHeliDistanceToGround;	/* 2436 - (between 0.9 and 1 = touching ground) */
	uint8_t				__unknown_2440[24];		/* 2440 */
	float				fHeliMainRotorDistance;	/* 2464 - distance/rotation */
	float				fHeliSecRotorDistance;	/* 2468 - distance/rotation secondary rotor */
	uint8_t				__unknown_2472[88];		/* 2472 */
	uint8_t				SmokeTrailEnabled;		/* 2560 */
	uint8_t				__unknown_2561[23];		/* 2561 */
	/* 2584 */
};


struct stLocalPlayer_037
{
	struct stSAMPPed* pSAMP_Actor;
	uint16_t				sCurrentAnimID;
	uint16_t				sAnimFlags;
	uint32_t				ulUnk0;
	int						iIsActive;
	int						iIsWasted;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	struct stOnFootData_037		onFootData;
	struct stPassengerData_037	passengerData;
	struct stTrailerData_037	trailerData;
	struct stInCarData_037		inCarData;
	struct stAimData_037		aimData;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					byteUnk1;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2;
	uint16_t				usUnk2;
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid;
	uint16_t				usUnk3;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint16_t				sTargetObjectID;
	uint16_t				sTargetVehicleID;
	uint16_t				sTargetPlayerID;
	struct stHeadSync		headSyncData;
	uint32_t				ulHeadSyncTick;
	BYTE					byteSpace3[260];
	struct stSurfData		surfData;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t				ulUnk4;
	uint8_t					byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;
	int						iInitiatedSpectating;
	struct stDamageData		vehicleDamageData;
};


template <typename T>
struct stSAMPEntity
{
	void* pVTBL;
	uint8_t		byteUnk0[60]; // game CEntity object maybe. always empty.
	T* pGTAEntity;
	uint32_t	ulGTAEntityHandle;
};

struct stSAMPPed : public stSAMPEntity < actor_info >
{
	int					usingCellPhone;
	uint8_t				byteUnk0[600];
	struct actor_info* pGTA_Ped;
	uint8_t				byteUnk1[22];
	uint8_t				byteKeysId;
	uint16_t			ulGTA_UrinateParticle_ID;
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	uint8_t				byteUnk2[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
	uint8_t				byteUnk3[20];
	int					isUrinating;
};

struct stSAMPVehicle : public stSAMPEntity < vehicle_info >
{
	uint32_t			bUnk0;
	struct vehicle_info* pGTA_Vehicle;
	uint8_t				byteUnk1[8];
	int					bIsMotorOn;
	int					iIsLightsOn;
	int					iIsLocked;
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnk2[16];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;
};

struct stObject : public stSAMPEntity < object_info >
{
	uint8_t				byteUnk0[2];
	uint32_t			ulUnk1;
	int					iModel;
	uint16_t			byteUnk2;
	float				fDrawDistance;
	float				fUnk;
	float				fPos[3];
	uint8_t				byteUnk3[68];
	uint8_t				byteUnk4;
	float				fRot[3];
	// ...
};

struct stRemotePlayerData_037
{
	struct stSAMPPed* pSAMP_Actor;
	struct stSAMPVehicle* pSAMP_Vehicle;
	uint8_t					byteTeamID;
	uint8_t					bytePlayerState;
	uint8_t					byteSeatID;
	uint32_t				ulUnk3;
	int						iPassengerDriveBy;
	void* pUnk0;
	uint8_t					byteUnk1[60];
	float					fSomething[3];
	float					fVehicleRoll[4];
	uint32_t				ulUnk2[3];
	float					fOnFootPos[3];
	float					fOnFootMoveSpeed[3];
	float					fVehiclePosition[3];
	float					fVehicleMoveSpeed[3];
	uint16_t				sPlayerID;
	uint16_t				sVehicleID;
	uint32_t				ulUnk5;
	int						iShowNameTag;
	int						iHasJetPack;
	uint8_t					byteSpecialAction;
	uint32_t				ulUnk4[3];
	struct stOnFootData		onFootData;
	struct stInCarData		inCarData;
	struct stTrailerData_037	trailerData;
	struct stPassengerData_037	passengerData;
	struct stAimData_037		aimData;
	float					fActorArmor;
	float					fActorHealth;
	uint32_t				ulUnk10;
	uint8_t					byteUnk9;
	uint32_t				dwTick;
	uint32_t				dwLastStreamedInTick;	// is 0 when currently streamed in
	uint32_t				ulUnk7;
	int						iAFKState;
	struct stHeadSync		headSyncData;
	int						iGlobalMarkerLoaded;
	int						iGlobalMarkerLocation[3];
	uint32_t				ulGlobalMarker_GTAID;
};

struct stRemotePlayer_037
{
	stRemotePlayerData_037* pPlayerData;
	int					iIsNPC;
	void* pVTBL_txtHandler;
	std::string			strPlayerName;
	int					iScore;
	int					iPing;
};

struct stSAMPPools
{
	void* pMenu;
	struct stActorPool* pActor;
	struct stPlayerPool* pPlayer;
	struct stVehiclePool* pVehicle;
	struct stPickupPool* pPickup;
	struct stObjectPool* pObject;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
};

struct stSAMP
{
	uint8_t                  	_pad0[20];
	void* pUnk0;
	struct stServerInfo* pServerInfo;
	uint8_t				_pad1[16];
	void* pRakClientInterface;
	char				szIP[256 + 1];
	char				szHostname[256 + 1];
	uint8_t                 	_pad2;
	bool                    	m_bUpdateCameraTarget;
	bool				m_bNoNameTagStatus;
	uint32_t			ulPort;
	BOOL				m_bLanMode;
	uint32_t			ulMapIcons[SAMP_MAX_MAPICONS];
	Gamestate			iGameState;
	uint32_t			ulConnectTick;
	struct stServerPresets* pSettings;
	uint8_t                 	_pad3[5];
	struct stSAMPPools* pPools;
};

struct stChatEntry
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stFontRenderer
{
	void* m_pChatFont;
	void* m_pLittleFont;
	void* m_pChatShadowFont;
	void* m_pLittleShadowFont;
	void* m_pCarNumberFont;
	void* m_pTempSprite;
	void* m_pD3DDevice;
	char* m_pszTextBuffer;
};

struct stChatInfo
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	struct stChatEntry	chatEntry[100];
	stFontRenderer* m_pFontRenderer;
	void* m_pChatTextSprite;
	void* m_pSprite;
	void* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void* pID3DXRenderToSurface;
	void* m_pTexture;
	void* pSurface;
	void* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
};

struct stInputBox
{
	void* pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unk;
	DWORD	dwPosChatInput[2];
	uint8_t	unk2[263];
	int		iCursorPosition;
	uint8_t	unk3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unk4[20];
	int		iMouseLeftButton;
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct stInputInfo
{
	void* pD3DDevice;
	void* pDXUTDialog;
	stInputBox* pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;
};

struct stTextdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct stTextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stServerInfo {
	uint32_t 			uiIP;
	uint16_t 			usPort;

	// ...

};


struct stTrailerData
{
	uint16_t	sTrailerID;
	float		fPosition[3];
	float		fQuaternion[4];
	float		fSpeed[3];
	float		fSpin[3];
};

struct stPassengerData
{
	uint16_t	sVehicleID;
	uint8_t		byteSeatID;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct stAimData
{
	BYTE	byteCamMode;
	float	vecAimf1[3];
	float	vecAimPos[3];
	float	fAimZ;
	BYTE	byteCamExtZoom : 6;		// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	byteAspectRatio;
};


struct stServerPresets
{
	uint8_t byteCJWalk;
	int m_iDeathDropMoney;
	float	fWorldBoundaries[4];
	bool m_bAllowWeapons;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	bool m_byteHoldTime;
	bool m_bInstagib;
	bool m_bZoneNames;
	bool m_byteFriendlyFire;
	int		iClassesAvailable;
	float	fNameTagsDistance;
	bool m_bManualVehicleEngineAndLight;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	int iPlayerMarkersMode;
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
	bool m_bLimitGlobalChatRadius;
};

typedef struct _VECTOR
{
#pragma pack( 1 )
	float	X, Y, Z;
} VECTOR, * PVECTOR;

struct stRemotePlayerData
{
	uint16_t			sPlayerID;
	uint16_t			sVehicleID;
	struct stSAMPPed* pSAMP_Actor;
	struct stSAMPVehicle* pSAMP_Vehicle;
	int				iHasJetPack;
	int				iShowNameTag;
	BOOL                   	 	bUsingJetPack;
	uint8_t				byteSpecialAction;
	uint8_t				byteTeamID;
	uint8_t				bytePlayerState;
	uint8_t				byteSeatID;
	BOOL                    	bIsNpc;
	int				iPassengerDriveBy;
	struct stPassengerData		passengerData;
	struct stOnFootData		onFootData;
	struct stInCarData		inCarData;
	struct stTrailerData		trailerData;
	struct stAimData		aimData;
	uint32_t			ulUnk0[3];
	float				fOnFootPos[3];
	float				fOnFootMoveSpeed[3];
	float				fVehiclePosition[3];
	float				fVehicleMoveSpeed[3];
	void* pUnk0;
	uint8_t				byteUnk1[60];
	VECTOR				vecVehiclePosOffset;
	float				fVehicleRoll[4];
	float				fActorArmor;
	float				fActorHealth;
	uint32_t			ulUnk1[3];
	int				iLastAnimationID;
	uint8_t				byteUpdateFromNetwork;
	uint32_t			dwTick;
	uint32_t			dwLastStreamedInTick;	// is 0 when currently streamed in
	uint32_t                	ulUnk2;
	int				iAFKState;
	struct stHeadSync		headSyncData;
	int				iGlobalMarkerLoaded;
	int				iGlobalMarkerLocation[3];
	uint32_t			ulGlobalMarker_GTAID;
};

enum ChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};

struct stPlayerPool
{
	uint16_t				sLocalPlayerID;
	void* pVTBL_txtHandler;
	std::string				strLocalPlayerName;
	struct stLocalPlayer* pLocalPlayer;
	uint32_t				ulMaxPlayerID;
	struct stRemotePlayer* pRemotePlayer[SAMP_MAX_PLAYERS];
	int					iIsListed[SAMP_MAX_PLAYERS];
	BOOL					bSavedCheckCollision[SAMP_MAX_PLAYERS];
	int					iLocalPlayerPing;
	int					iLocalPlayerScore;
};

struct stRemotePlayer
{
	int				iScore;
	int				iIsNPC;
	stRemotePlayerData *pPlayerData;
	int				iPing;
	void* pVTBL_txtHandler;
	std::string			strPlayerName;
};

struct CAMERA_TARGET_AIM
{
	uint16_t ObjectID;
	uint16_t VehicleID;
	uint16_t PlayerID;
	uint16_t ActorID;
};

struct PLAYER_SPAWN_INFO
{
	BYTE byteTeam;
	int iSkin;
	int iCustomModel;
	BYTE unk;
	VECTOR vecPos;
	float fRotation;
	int iSpawnWeapons[3];
	int iSpawnWeaponsAmmo[3];
};


struct stLocalPlayer
{
	struct stSAMPPed* pSAMP_Actor;
	struct stTrailerData		trailerData;
	struct stOnFootData		onFootData;
	struct stPassengerData		passengerData;
	struct stInCarData		inCarData;
	struct stAimData		aimData;
	int				iIsActive;
	int				iIsWasted;
	uint16_t			sCurrentVehicleID;
	uint16_t			sLastVehicleID;
	uint16_t			sCurrentAnimID;
	uint16_t			sAnimFlags;
	uint32_t			ulUnk0;
	CAMERA_TARGET_AIM       	cameraTarget;
	uint32_t			ulCameraTargetTick;
	struct stHeadSync		headSyncData;
	uint32_t			ulHeadSyncTick;
	int				iIsSpectating;
	uint8_t				byteTeamID2;
	uint16_t			usUnk2;
	uint32_t			ulSendTick;
	uint32_t			ulSpectateTick;
	uint32_t			ulAimTick;
	uint32_t			ulStatsUpdateTick;
	int				iSpawnClassLoaded;
	uint32_t			ulSpawnSelectionTick;
	uint32_t			ulSpawnSelectionStart;
	PLAYER_SPAWN_INFO      		spawnInfo;
	int				iIsActorAlive;
	uint32_t			ulWeapUpdateTick;
	uint16_t			sAimingAtPlayerID;
	uint16_t			sAimingAtActorID;
	uint8_t				byteCurrentWeapon;
	uint8_t				byteWeaponInventory[13];
	int				iWeaponAmmo[13];
	int				iPassengerDriveBy;
	uint8_t				byteCurrentInterior;
	int				iIsInRCVehicle;
	char                    	szPlayerName[256];
	struct stSurfData		surfData;
	int				iClassSelectionOnDeath;
	int				iSpawnClassID;
	int				iRequestToSpawn;
	int				iIsInSpawnScreen;
	uint32_t			ulDisplayZoneTick;
	uint8_t				byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t				byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int				iSpectateID;
	int				iInitiatedSpectating;
	struct stDamageData		vehicleDamageData;
};

// FUNCTIONS

struct stSAMP* stGetSampInfo(void);
struct stSAMP_037* stGetSampInfo037(void);
extern struct stSAMP* g_stSAMP;
extern struct stChatInfo* g_Chat;
extern struct stInputInfo* g_Input;

extern struct stSAMP_037* g_stSAMP037;
extern struct stChatInfo_037* g_Chat037;
extern struct stInputInfo_037* g_Input037;


static signed char hex_to_dec(signed char ch);
uint8_t* hex_to_bin(const char* str);
void SetupSAMPHook(const char* szName, DWORD dwFuncOffset, void* Func, int iType, int iSize, const char* szCompareBytes);
int memcpy_safe(void* _dest, const void* _src, uint32_t len, int check = NULL, const void* checkdata = NULL);
int memcmp_safe(const void* _s1, const void* _s2, uint32_t len);
bool isBadPtr_writeAny(void* pointer, ULONG size);
bool isBadPtr_readAny(void* pointer, ULONG size);
bool isBadPtr_handlerAny(void* pointer, ULONG size, DWORD dwFlags);
struct stChatInfo* stGetSampChatInfo(void);
struct stInputInfo* stGetInputInfo(void);
struct stChatInfo_037* stGetSampChatInfo037(void);
struct stInputInfo_037* stGetInputInfo037(void);
void addToChatWindow(char* text, D3DCOLOR textColor);
void addMessageToChatWindow(D3DCOLOR col, const char* text, ...);
int GetSilentAimTarget();
void GetAimingCenter(float& x, float& y);
D3DCOLOR samp_color_get(int id, DWORD trans = 0xFF000000);
const char* getPlayerName(int iPlayerID);
void CalcWorldCoors(D3DXVECTOR3* vecScreen, D3DXVECTOR3* vecWorld);
void CalcScreenCoors(D3DXVECTOR3* vecWorld, D3DXVECTOR3* vecScreen);

int getPlayerPos(int iPlayerID, float fPos[3]);
void ReloadFriendlist();
bool IsLineOfSightClear(CVector* vecStart, CVector* vecEnd, bool bCheckBuildings,
	bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects,
	bool bCheckDummies, bool bSeeThroughStuff, bool bIgnoreSomeObjectsForCamera);

void __stdcall CNetGame__destructor();
void say(char* msg);
void addClientCommand(char* name, CMDPROC function);
size_t strlcpy(char* dst, const char* src, size_t size);
bool hex_is_valid(const std::string& hex);
bool ValidPlayer(int PlayerID);
bool IsPlayerStreamed(uint16_t playerID);
int getPlayerState(int iPlayerID); 
float vect3_dist(const float in1[3], const float in2[3]);

enum PlayerState
{
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 17,
	PLAYER_STATE_PASSENGER,
	PLAYER_STATE_DRIVER,
	PLAYER_STATE_WASTED = 32,
	PLAYER_STATE_SPAWNED
};


// VEHICLE MODEL INFO

enum eVehicleModelInfo
{
	VEHICLE_MODEL_INFO_SIZE,            // Vehicle size
	VEHICLE_MODEL_INFO_FRONTSEAT,       // Position of the front seat*
	VEHICLE_MODEL_INFO_REARSEAT,        // Position of the rear seat*
	VEHICLE_MODEL_INFO_PETROLCAP,       // Position of the fuel cap*
	VEHICLE_MODEL_INFO_WHEELSFRONT,     // Position of the front wheels*
	VEHICLE_MODEL_INFO_WHEELSREAR,      // Position of the rear wheels*
	VEHICLE_MODEL_INFO_WHEELSMID,       // Position of the middle wheels (applies to vehicles with 3 axes)*
	VEHICLE_MODEL_INFO_FRONT_BUMPER_Z,  // Height of the front bumper
	VEHICLE_MODEL_INFO_REAR_BUMPER_Z,   // Height of the rear bumper
};

struct actor_info* actor_info_get_self();
struct actor_info* getGTAPedFromSAMPPlayerID(int iPlayerID);
struct vehicle_info* vehicle_info_get_self();
int vehicle_contains_actor(struct vehicle_info* vehicle, struct actor_info* actor);
void vect3_copy(const float in[3], float out[3]);

#define FUNC_RpAnimBlendClumpGetAssociation                 0x4D6870
#define FUNC_RpAnimBlendClumpGetAssociation_int             0x4d68b0

bool IsPlayingAnimationAInfo(actor_info * act, char* szAnimName);