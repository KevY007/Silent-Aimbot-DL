//Hook By GAM

#include "main.h"

int lastCol[4];
DWORD startTick = 0;

DWORD viewTick = -1;
int lastViewAlpha = 255;
int viewCol[3] = { 255, 255, 255 };
float viewPlusY = 0.0;
char viewText[128];

void displayTextScr(int r, int g, int b, const char* text, ...)
{
	va_list ap;
	if (text == NULL)
		return;

	char	tmp[512];
	memset(tmp, 0, 512);

	va_start(ap, text);
	vsnprintf(tmp, sizeof(tmp) - 1, text, ap);
	va_end(ap);

	viewCol[0] = r;
	viewCol[1] = g;
	viewCol[2] = b;
	lastViewAlpha = 255;

	sprintf(viewText, tmp);

	viewPlusY = 0.0;
	viewTick = GetTickCount();
	return;
}

HRESULT __stdcall Hooked_Present(IDirect3DDevice9 *pDevice, CONST RECT *pSrcRect, CONST RECT *pDestRect, HWND hDestWindow, CONST RGNDATA *pDirtyRegion)
{
	if (!pDevice)
		return pD3DHook->Orginal_Present(pDevice, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);

	if (pD3DHook->bD3DRenderInit == false)
	{
		pD3DHook->pRender->Initialize(pDevice);
		pD3DHook->pD3DFont->Initialize(pDevice);

		pD3DHook->bD3DRenderInit = true;
	}

	if (initSampRak)
	{
		if (viewTick != -1)
		{
			pD3DHook->pD3DFont->Print((float)pD3DHook->pPresentParam.BackBufferWidth / 2.f -
				pD3DHook->pD3DFont->DrawLength(viewText)
				, (float)pD3DHook->pPresentParam.BackBufferHeight / 2.f + viewPlusY,
				D3DCOLOR_ARGB(lastViewAlpha, viewCol[0], viewCol[1], viewCol[2]), viewText, true);

			if (GetTickCount() - viewTick > 700 && viewPlusY < 200.0)
			{
				viewPlusY -= 0.5;
				lastViewAlpha -= 2;
			}

			if (GetTickCount() - viewTick > 1500)
			{
				viewTick = -1;
			}
		}
		if (startTick != -1)
		{
			if (startTick == 0)
			{
				startTick = GetTickCount();
				lastCol[3] = 255;
			}

			for (int i = 0; i < 3; i++)
			{
				if (lastCol[i] >= 255)
				{
					lastCol[i] = rand() % 255;
				}
				else lastCol[i]++;
			}

			if (silentaim_hideESP == 0)
			{
				pD3DHook->pD3DFont->Print((float)pD3DHook->pPresentParam.BackBufferWidth / 2.f -
					pD3DHook->pD3DFont->DrawLength("=> Silent Aimbot <=")
					, (float)pD3DHook->pPresentParam.BackBufferHeight / 2.f,
					D3DCOLOR_ARGB(lastCol[3], lastCol[0], lastCol[1], lastCol[2]), "=> Silent Aimbot <=", true);

				pD3DHook->pD3DFont->Print((float)pD3DHook->pPresentParam.BackBufferWidth / 2.f -
					pD3DHook->pD3DFont->DrawLength("=> By 0x32789/ProCoder/KevY <=")
					, (float)pD3DHook->pPresentParam.BackBufferHeight / 2.f + 25.0f,
					D3DCOLOR_ARGB(lastCol[3], lastCol[0], lastCol[1], lastCol[2]), "=> By 0x32789/ProCoder/KevY <=", true);
			}

			if (GetTickCount() - startTick >= 3000)
			{
				lastCol[3]--;

				if (lastCol[3] == 0)
					startTick = -1;
			}
		}
		
		


		MainLoop();
	}
	
	return pD3DHook->Orginal_Present(pDevice, pSrcRect, pDestRect, hDestWindow, pDirtyRegion);
}

HRESULT __stdcall Hooked_Reset(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParams)
{
	if (!pDevice)
		return pD3DHook->Orginal_Reset(pDevice, pPresentParams);

	if (pD3DHook->bD3DRenderInit == true)
	{
		pD3DHook->pD3DFont->Invalidate();
		pD3DHook->pRender->Invalidate();

		pD3DHook->bD3DRenderInit = false;
	}

	HRESULT ret = pD3DHook->Orginal_Reset(pDevice, pPresentParams);

	if (ret == D3D_OK)
	{
		pD3DHook->pRender->Initialize(pDevice);
		pD3DHook->pD3DFont->Initialize(pDevice);
		pD3DHook->pPresentParam = *pPresentParams;

		pD3DHook->bD3DRenderInit = true;
	}

	return ret;
}