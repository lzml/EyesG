// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <atltime.h>
#include "uifunc.h"
#include "SRadioBox2.h"


#define  WM_auto_protect_eyes_params					(WM_USER +  1159)
#define  OnSecondTimerId		80  
#define	 OnCloseLockScreen		82
// 1分钟定时器
#define TimerID_one_minute_event		83

class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);

	//演示如何响应菜单事件
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);




	void OnFinalMessage(HWND hWnd) override;

	void OnBtnAutoAdjust();
private:
	void InitUpdateMemToUI();


	void OnTimer(UINT_PTR idEvent);


	void OnAdjustBrightness(EventArgs *pEvt);
	void OnAdjustColorT(EventArgs* pEvt);


	LRESULT On_auto_protect_eyes_params(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL lResul);



	void OnBtnClose();

	void OnRdNormal();
	void OnRdWarm1();
	void OnRdWarm2();
	void OnRdGloomy();
	void OnRdWarm3();
	void OnRdReversedcolor();
	void OnRdBW();
	void ClearCheck();





protected:
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnBtnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"rd_auto_adjust", OnBtnAutoAdjust)
		EVENT_NAME_COMMAND(L"rd_normal", OnRdNormal)
		EVENT_NAME_COMMAND(L"rd_warm1", OnRdWarm1)
		EVENT_NAME_COMMAND(L"rd_warm2", OnRdWarm2)
		EVENT_NAME_COMMAND(L"rd_gloomy", OnRdGloomy)
		EVENT_NAME_COMMAND(L"rd_warm3", OnRdWarm3)
		EVENT_NAME_COMMAND(L"rd_reversedcolor", OnRdReversedcolor)
		EVENT_NAME_COMMAND(L"rd_BW", OnRdBW)

		EVENT_NAME_HANDLER(L"adjustligthness", EVT_SLIDER_POS, OnAdjustBrightness)
		EVENT_NAME_HANDLER(L"adjustColorT", EVT_SLIDER_POS, OnAdjustColorT)
		EVENT_MAP_END()

		//HostWnd真实窗口消息处理
		BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_TIMER_EX(OnTimer)


		MESSAGE_HANDLER(WM_auto_protect_eyes_params, On_auto_protect_eyes_params)

	//托盘消息处理
		MSG_WM_COMMAND(OnCommand)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;	
	SSliderBar*		m_adjustligthness;
	SSliderBar*		m_adjustColorT;

	SRadioBox2*		m_rd_normal;
	SRadioBox2*		m_rd_auto_adjust;
	SRadioBox2*		m_rd_warm1;
	SRadioBox2*		m_rd_warm2;
	SRadioBox*		m_rd_gloomy;
	SRadioBox2*		m_rd_warm3;
	SRadioBox2*		m_rd_reversed_color;
	SRadioBox2*		m_rd_BW;

	
	

	SStatic*		m_txt_ver;
};

extern HWND g_hwnd_mainDlg;

extern string   g_packdownurl;
extern string	g_packname;