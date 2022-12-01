#include "stdafx.h"
#include "EyesGuard_en.h"

#include "protect_eyes_en.h"
#include "MainDlg.h"
#include "uifunc.h"




CEyesGuard_en g_eyeguard;


void UISetProgressBarValue(int value) {


}

void CEyesGuard_en::RegulationThread(LPVOID ptr) {
	CEyesGuard_en* pEyesGuard = (CEyesGuard_en*)ptr;
	SYSTEMTIME st;
	WORD part = 0, rate = 0;
	RAYTYPE type = TYPE_NULL;
	while (true)
	{
		if (pEyesGuard->NeedTerminate())
		{
			break;
		}
#ifdef _DEBUG
		::Sleep(1000);
#else
		//::Sleep(1000 * 60 * 10);
		::Sleep(1000);
#endif // _DEBUG

		if (1 != g_protect_eye_en.changeType)
		{
			continue;
		}

		::GetLocalTime(&st);
		if (st.wHour < 7 || st.wHour > 18)
		{
			rate = 90;
		}
		else 
		{
			rate = 96;
		}
		
		{
			::PostMessage(g_hwnd_mainDlg, WM_auto_protect_eyes_params, 0, rate);
		}
	
	}
}

CEyesGuard_en::CEyesGuard_en(std::function<void(int)> callback) : m_pfUICallback(callback)
{
	m_bInit = FALSE;
	if (!m_pfUICallback)
	{
		m_pfUICallback = UISetProgressBarValue;
	}
	//Initialize all variables.
	hGDI32 = NULL;
	pGetDeviceGammaRamp = NULL;
	pSetDeviceGammaRamp = NULL;
	nDeepValue = 128;

	m_bNeedTerminate = false;
}

CEyesGuard_en::~CEyesGuard_en()
{
	//SetYellowRate(0);
}

VOID CEyesGuard_en::Init() {

	if (m_bInit == FALSE)
	{
		m_bInit = TRUE;
		// 开启自动调节线程
		m_hThread = std::thread(CEyesGuard_en::RegulationThread, this);
	}
}


BOOL CEyesGuard_en::SetRayRate(int type) {


	if (type == TYPE_YELLOW)
	{
		return SetYellowRate(g_protect_eye_en.m_brightness_value, NULL);
	}
	else if (type == TYPE_GREEN)
	{
		return SetGreenRate(g_protect_eye_en.m_brightness_value, NULL);
	}
	else if (type == TYPE_RED)
	{
		return SetRedRate(g_protect_eye_en.m_brightness_value, NULL);
	}
	else if (type == TYPE_BLACK)
	{
		return SetBlackRate(g_protect_eye_en.m_brightness_value, NULL);
	}
	else if (type == TYPE_RECOMMAND)
	{
		return SetRecommendRate(g_protect_eye_en.m_brightness_value, NULL);
	}
	return FALSE;
}



BOOL CEyesGuard_en::LoadLibrary()
{
	BOOL bReturn = FALSE;

	FreeLibrary();
	//Load the GDI library.
	hGDI32 = ::LoadLibrary(_T("gdi32.dll"));
	if (hGDI32 != NULL)
	{
		//Get the addresses of GetDeviceGammaRamp and SetDeviceGammaRamp API functions.
		pGetDeviceGammaRamp =
			(Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");

		pSetDeviceGammaRamp =
			(Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");

		//Return TRUE only if these functions exist.
		if (pGetDeviceGammaRamp == NULL || pSetDeviceGammaRamp == NULL)
			FreeLibrary();
		else
			bReturn = TRUE;
	}

	return bReturn;
}


void CEyesGuard_en::FreeLibrary()
{
	//Free the GDI library.
	if (hGDI32 != NULL)
	{
		::FreeLibrary(hGDI32);
		hGDI32 = NULL;
	}
}


BOOL CEyesGuard_en::LoadLibraryIfNeeded()
{
	BOOL bReturn = FALSE;

	if (hGDI32 == NULL)
		LoadLibrary();

	if (pGetDeviceGammaRamp != NULL && pSetDeviceGammaRamp != NULL)
		bReturn = TRUE;

	return bReturn;
}


BOOL CEyesGuard_en::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
	//Call to SetDeviceGammaRamp only if this function is successfully loaded.
	if (LoadLibraryIfNeeded())
	{
		return pSetDeviceGammaRamp(hDC, lpRamp);
	}
	else
		return FALSE;
}


BOOL CEyesGuard_en::GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
	//Call to GetDeviceGammaRamp only if this function is successfully loaded.
	if (LoadLibraryIfNeeded())
	{
		return pGetDeviceGammaRamp(hDC, lpRamp);
	}
	else
		return FALSE;

}

BOOL CEyesGuard_en::SetYellowRate(WORD rate, HDC hDC) {
	if (rate > 100 || rate < 0)
	{
		return FALSE;
	}

	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };
		//GetDeviceGammaRamp(hGammaDC, GammaArray);

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * 256;
			int iBlueValue = (256 - nDeepValue * rate / 100) * iIndex;
			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] =
				GammaArray[1][iIndex] = (WORD)iArrayValue;
			GammaArray[2][iIndex] = iBlueValue;
		}

		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
	return bReturn;
}

BOOL CEyesGuard_en::SetGreenRate(WORD rate, HDC hDC) {
	if (rate > 100 || rate < 0)
	{
		return FALSE;
	}
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };
		//GetDeviceGammaRamp(hGammaDC, GammaArray);

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * 256;
			int iBlueValue = (256 - nDeepValue * rate / 100) * iIndex;
			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] =
				GammaArray[2][iIndex] = iBlueValue;
			GammaArray[1][iIndex] = (WORD)iArrayValue;
		}

		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
	return bReturn;
}

BOOL CEyesGuard_en::SetRedRate(WORD rate, HDC hDC) {
	if (rate > 100 || rate < 0)
	{
		return FALSE;
	}
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };
		GetDeviceGammaRamp(hGammaDC, GammaArray);

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * 256;
			int iBlueValue = (256 - nDeepValue * rate / 100) * iIndex;
			if (iArrayValue > 65535)
				iArrayValue = 65535;

		//	GammaArray[0][iIndex] = (WORD)iArrayValue;
			GammaArray[1][iIndex] =
				GammaArray[2][iIndex] = iBlueValue;
		}

		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
	return bReturn;
}

BOOL CEyesGuard_en::SetBlackRate(WORD rate, HDC hDC) {
	if (rate > 100 || rate < 0)
	{
		return FALSE;
	}
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };
		GetDeviceGammaRamp(hGammaDC, GammaArray);

		for (int iIndex = 0; iIndex < 256; iIndex ++)
		{
			int iRedValue = 256 * iIndex;
			int iBlueValue = (256 - nDeepValue * rate / 100) * iIndex;

			GammaArray[0][iIndex] = 
				GammaArray[1][iIndex] =
				GammaArray[2][iIndex] = iBlueValue;
		}

		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
	return bReturn;
}

BOOL CEyesGuard_en::SetRecommendRate(WORD rate, HDC hDC) {
	if (rate > 100 || rate < 0)
	{
		return FALSE;
	}
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };
		//GetDeviceGammaRamp(hGammaDC, GammaArray);

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iRedValue = (256 - nDeepValue * rate / 500) * iIndex;
			int iGreenValue = (256 - nDeepValue * rate / 200) * iIndex;
			int iBlueValue = (256 - nDeepValue * rate / 100) * iIndex;

			GammaArray[0][iIndex] = iRedValue;
			GammaArray[1][iIndex] = iGreenValue;
			GammaArray[2][iIndex] = iBlueValue;
		}

		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
	return bReturn;
}

VOID CEyesGuard_en::AutoTakeEffect() {
	WORD part = 0, rate = 0;
	SYSTEMTIME st;
	::GetLocalTime(&st);
	if (st.wHour >= 0 && st.wHour < 13)
	{
		// 递减
		//if (st.wMinute % 10 == 0)
		{
			part = (st.wHour * 6 + st.wMinute / 10);
			rate = 100 - 1.025*(part);
		}
	}
	else if (st.wHour >= 13 && st.wHour <= 23)
	{
		// 递增
		//if (st.wMinute % 10 == 0)
		{
			part = ((st.wHour - 13) * 6 + st.wMinute / 10);
			rate = 20 + 1.23*(part);
		}
	}
	SetRayRate(TYPE_RED);
}

VOID CEyesGuard_en::Close() {
	m_bNeedTerminate = true;
	FreeLibrary();
	if (m_hThread.joinable())
	{
		m_hThread.detach();
	}
	// 恢复
	SetYellowRate(0);
}

void CEyesGuard_en::SetScreenNormal()
{

	HDC hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };
		//GetDeviceGammaRamp(hGammaDC, GammaArray);

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iRedValue = 256 * iIndex;


			GammaArray[0][iIndex] = iRedValue;
			GammaArray[1][iIndex] = iRedValue;
			GammaArray[2][iIndex] = iRedValue;
		}

		SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
}

void CEyesGuard_en::SetScreenBlackAndRed(int black, int red)
{
	HDC hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL) {
		WORD GammaArray[3][256] = { 0 };

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iRedValue = (256 * black / 100 ) * iIndex;

			int iBlueValue = (256  * black / 100 * red / 100) * iIndex;

			GammaArray[0][iIndex] = iRedValue;
			GammaArray[1][iIndex] = iBlueValue;
			GammaArray[2][iIndex] = iBlueValue;
		}

		 SetDeviceGammaRamp(hGammaDC, GammaArray);
	}
	if (hGammaDC != NULL)
	{
		ReleaseDC(NULL, hGammaDC);
	}
}