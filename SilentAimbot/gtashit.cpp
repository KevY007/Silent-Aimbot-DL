#include "main.h"

int GetWeaponIDByModelID(WORD modelid)
{
	switch (modelid)
	{
	case 331: return 1;
	case 333: return 2;
	case 334: return 3;
	case 335: return 4;
	case 336: return 5;
	case 337: return 6;
	case 338: return 7;
	case 339: return 8;
	case 341: return 9;
	case 321: return 10;
	case 322: return 11;
	case 323: return 12;
	case 324: return 13;
	case 325: return 14;
	case 326: return 15;
	case 342: return 16;
	case 343: return 17;
	case 344: return 18;
	case 346: return 22;
	case 347: return 23;
	case 348: return 24;
	case 349: return 25;
	case 350: return 26;
	case 351: return 27;
	case 352: return 28;
	case 353: return 29;
	case 355: return 30;
	case 356: return 31;
	case 372: return 32;
	case 357: return 33;
	case 358: return 34;
	case 359: return 35;
	case 360: return 36;
	case 361: return 37;
	case 362: return 38;
	case 363: return 39;
	case 364: return 40;
	case 365: return 41;
	case 366: return 42;
	case 367: return 43;
	case 368: return 44;
	case 369: return 45;
	case 371: return 46;
	default: return 0;
	}
	return 0;
}

int GetCurrentWeapon()
{
	if (*(int*)(0xB6F5F0) == NULL) return 0; // NO VEHICLE, ONFOOT?

	DWORD vptr = *(DWORD*)(0xB6F5F0);
	vptr = *(DWORD*)(vptr + 0x740);

	return GetWeaponIDByModelID((WORD)(WORD*)vptr);
}