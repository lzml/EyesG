// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
#include "SRadioBox2.h"
#include "uifunc.h"
#include "EyesGuard_en.h"
#include "protect_eyes_en.h"
#include "SCheckBox2.h"
#include "string.h"
#include "DllFunc.h"
#include "path.h"
#include "stringinfo.h"

HWND g_hwnd_mainDlg = NULL;

 string   g_packdownurl;
 string	g_packname;



extern wstring g_strUserSid;

//右下角托盘广告url
wstring g_strShellAdUrl;

//运行一次标志
static BOOL __OnceTime__ = TRUE;
static BOOL __OnceTime_闪烁托盘__ = TRUE;

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{


	::SetWindowTextW(m_hWnd, WINDOWNAME);

	g_hwnd_mainDlg = m_hWnd;
	m_bLayoutInited = TRUE;
	SShellNotifyIcon *notify = FindChildByID2<SShellNotifyIcon>(110);
	//notify->ShowNotify(L"Hello SOUI", L"这可能是一个提示");

	m_adjustligthness = FindChildByName2<SSliderBar>(L"adjustligthness");
	m_adjustColorT = FindChildByName2<SSliderBar>(L"adjustColorT");
	m_rd_auto_adjust = FindChildByName2<SRadioBox2>(L"rd_auto_adjust");
	m_rd_normal = FindChildByName2<SRadioBox2>(L"rd_normal");
	m_rd_warm1 = FindChildByName2<SRadioBox2>(L"rd_warm1");
	m_rd_warm2 = FindChildByName2<SRadioBox2>(L"rd_warm2");
	m_rd_gloomy = FindChildByName2<SRadioBox2>(L"rd_gloomy");
	m_rd_warm3 = FindChildByName2<SRadioBox2>(L"rd_warm3");
	m_rd_reversed_color = FindChildByName2<SRadioBox2>(L"rd_reversedcolor");
	m_rd_BW = FindChildByName2<SRadioBox2>(L"rd_BW");
 


	m_txt_ver = FindChildByName2<SStatic>(L"txt_ver");


	g_eyeguard.Init();


	SetTimer(OnSecondTimerId, 1000);

	string strCmd = ParamStr(1);


	//启动1分钟定时器
	::SetTimer(m_hWnd, TimerID_one_minute_event, 1000 * 60, NULL);


	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();

}

void CMainDlg::OnBtnClose()
{
	OnClose();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;

	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if (!pBtnMax || !pBtnRestore) return;

	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}


//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{

}


void CMainDlg::OnFinalMessage(HWND hWnd)
{

	g_eyeguard.Close();
}

void CMainDlg::OnBtnAutoAdjust()
{
	BOOL bCk = m_rd_auto_adjust->IsChecked();

	g_protect_eye_en.changeType = Mode_Auto;



}

void CMainDlg:: OnTimer(UINT_PTR idEvent)
{

}


void CMainDlg:: OnAdjustBrightness(EventArgs *pEvt)
{
	setColorNormal();
	ClearCheck();
	
	g_protect_eye_en.changeType = Mode_None;
	g_protect_eye_en.m_brightness_value = m_adjustligthness->GetValue();

	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);

}

void CMainDlg::OnAdjustColorT(EventArgs* pEvt)
{
	setColorNormal();
	ClearCheck();

	g_protect_eye_en.changeType = Mode_None;
	g_protect_eye_en.m_colorT = m_adjustColorT->GetValue();

	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);

}




LRESULT CMainDlg::On_auto_protect_eyes_params(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL lResul)
{
	g_protect_eye_en.m_colorT = lParam;
	g_protect_eye_en.m_brightness_value = 90;
	

	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);
	m_adjustligthness->SetValue(g_protect_eye_en.m_brightness_value);
	m_adjustColorT->SetValue(g_protect_eye_en.m_colorT);


	return S_OK;
}


void CMainDlg::OnRdNormal()
{
	setColorNormal();
	g_eyeguard.SetScreenNormal();
	m_adjustligthness->SetValue(100);
	m_adjustColorT->SetValue(100);
	g_protect_eye_en.changeType = Mode_Normal;
	g_protect_eye_en.m_colorT = 100;
	g_protect_eye_en.m_brightness_value = 100;
 

}
void CMainDlg::OnRdWarm1()
{
	setColorNormal();
	g_protect_eye_en.m_colorT = 95;
	g_protect_eye_en.m_brightness_value = 90;
	g_protect_eye_en.changeType = Mode_warm1;
	m_adjustligthness->SetValue(g_protect_eye_en.m_brightness_value);
	m_adjustColorT->SetValue(g_protect_eye_en.m_colorT);
 
	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);

}

void CMainDlg::OnRdWarm2()
{
	setColorNormal();
	g_protect_eye_en.m_colorT = 85;
	g_protect_eye_en.m_brightness_value = 90;
	g_protect_eye_en.changeType = Mode_warm2;
	m_adjustligthness->SetValue(g_protect_eye_en.m_brightness_value);
	m_adjustColorT->SetValue(g_protect_eye_en.m_colorT);
 
	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);

}

void CMainDlg::OnRdGloomy()
{
	setColorNormal();
	g_protect_eye_en.m_colorT = 100;
	g_protect_eye_en.m_brightness_value = 80;
	g_protect_eye_en.changeType = Mode_gloomy;
	m_adjustligthness->SetValue(g_protect_eye_en.m_brightness_value);
	m_adjustColorT->SetValue(g_protect_eye_en.m_colorT);
 
	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);

}

void CMainDlg::OnRdWarm3()
{
	setColorNormal();
	g_protect_eye_en.m_colorT = 97;
	g_protect_eye_en.m_brightness_value = 100;
	g_protect_eye_en.changeType = Mode_warm3;
	m_adjustligthness->SetValue(g_protect_eye_en.m_brightness_value);
	m_adjustColorT->SetValue(g_protect_eye_en.m_colorT);
 
	g_eyeguard.SetScreenBlackAndRed(g_protect_eye_en.m_brightness_value, g_protect_eye_en.m_colorT);

}

void CMainDlg::OnRdReversedcolor()
{
	setColorInversion();
	g_protect_eye_en.changeType = Mode_reversed_color;
 

}

void CMainDlg::OnRdBW()
{
	setColorGray();
	g_protect_eye_en.changeType = Mode_BW;
 

}

void CMainDlg::ClearCheck()
{
	m_rd_normal->SetCheck(FALSE);
	m_rd_auto_adjust->SetCheck(FALSE);
	m_rd_warm1->SetCheck(FALSE);
	m_rd_warm2->SetCheck(FALSE);
	m_rd_gloomy->SetCheck(FALSE);
	m_rd_warm3->SetCheck(FALSE);
	m_rd_reversed_color->SetCheck(FALSE);
	m_rd_BW->SetCheck(FALSE);
 
}

void CMainDlg::InitUpdateMemToUI()
{
	
	switch (g_protect_eye_en.changeType)
	{
	case Mode_None:
		ClearCheck();
		break;
	case Mode_Normal:
		m_rd_normal->SetCheck(TRUE); 
	 
		break;
	case Mode_Auto:
		m_rd_auto_adjust->SetCheck(TRUE);
 
		break;
	case Mode_warm1:
		m_rd_warm1->SetCheck(TRUE);
 
		break;
	case Mode_warm2:
		m_rd_warm2->SetCheck(TRUE);
 
		break;
	case Mode_gloomy:
		m_rd_gloomy->SetCheck(TRUE);
 
		break;
	case Mode_warm3:
		m_rd_warm3->SetCheck(TRUE);
	 
		break;
	case Mode_reversed_color:
		m_rd_reversed_color->SetCheck(TRUE);
	 
		break;
	case Mode_BW:
		m_rd_BW->SetCheck(TRUE);
 
		break;
	default:
		break;
	}
	m_adjustligthness->SetValue(g_protect_eye_en.m_brightness_value);
	m_adjustColorT->SetValue(g_protect_eye_en.m_colorT);
	
}


