//Hook By GAM

#include "main.h"

typedef HRESULT(__stdcall *Prototype_Present)(IDirect3DDevice9 *, CONST RECT *, CONST RECT *, HWND, CONST RGNDATA *);
typedef HRESULT(__stdcall *Prototype_Reset)(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *);

HRESULT __stdcall Hooked_Present(IDirect3DDevice9 *pDevice, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion);
HRESULT __stdcall Hooked_Reset(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS* pPresentParams);

void displayTextScr(int r, int g, int b, const char* text, ...);

class CD3DHook
{
public:
	CD3DHook()
	{
		Orginal_Present = (Prototype_Present) GetDeviceAddress(17);
		Orginal_Reset = (Prototype_Reset) GetDeviceAddress(16);
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&) Orginal_Present, Hooked_Present);
		DetourAttach(&(PVOID&) Orginal_Reset, Hooked_Reset);
		DetourTransactionCommit();
	};

	D3DPRESENT_PARAMETERS pPresentParam;

	CD3DRender *pRender = new CD3DRender(128);
	CD3DFont *pD3DFont = new CD3DFont("Arial", 16, FCR_BORDER);
	bool bD3DRenderInit = false;

	Prototype_Present Orginal_Present;
	Prototype_Reset Orginal_Reset;

private:
	DWORD FindDevice(DWORD Len)
	{
		DWORD dwObjBase = 0;
		char infoBuf[MAX_PATH];
		GetSystemDirectory(infoBuf, MAX_PATH);
		strcat_s(infoBuf, MAX_PATH, "\\d3d9.dll");
		dwObjBase = (DWORD) LoadLibrary(infoBuf);
		while (dwObjBase++ < dwObjBase + Len)
		{
			if ((*(WORD*) (dwObjBase + 0x00)) == 0x06C7 &&
				(*(WORD*) (dwObjBase + 0x06)) == 0x8689 &&
				(*(WORD*) (dwObjBase + 0x0C)) == 0x8689)
			{
				dwObjBase += 2;
				break;
			}
		}
		return(dwObjBase);
	};

	DWORD GetDeviceAddress(int VTableIndex)
	{
		PDWORD VTable;
		*(DWORD*) &VTable = *(DWORD*) FindDevice(0x128000);
		return VTable[VTableIndex];
	};
};

