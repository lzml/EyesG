#pragma once
#include <functional>
#include <thread>




// 光谱类型
enum RAYTYPE {
	TYPE_NULL = -1,
	TYPE_YELLOW = 0,
	TYPE_GREEN,
	TYPE_RED,
	TYPE_BLACK,
	TYPE_RECOMMAND
};

enum ModeType
{
	Mode_None = -1,
	Mode_Normal = 0,
	Mode_Auto = 1,
	Mode_warm1 = 2,
	Mode_warm2 = 3,
	Mode_gloomy = 4,
	Mode_warm3 = 5,
	Mode_reversed_color = 6,
	Mode_BW = 7,
};



class CEyesGuard_en
{
public:
	CEyesGuard_en(std::function<void(int)> callback = nullptr);
	~CEyesGuard_en();
	// 主动清理
	VOID Close();
	// 初始化
	VOID Init();

	BOOL IsInit() { return m_bInit; };

	// 自动调节线程
	static void RegulationThread(LPVOID ptr);


	BOOL SetRayRate( int type);

	void SetScreenNormal();

	void SetScreenBlackAndRed(int black, int red);




	bool NeedTerminate() { return m_bNeedTerminate; }

	std::function<void(int)> UICallback() { return m_pfUICallback; }

private:

	BOOL m_bInit;		//是否经过了初始化


	HMODULE		hGDI32;
	WORD		nDeepValue;			// 100%比例时的深度值（0~255之间，默认128，不要更改）



	bool		m_bNeedTerminate;	// 是否结束线程

	std::thread m_hThread;			// 调节线程对象
	std::function<void(int)>	m_pfUICallback;	// 界面回显回调函数

	typedef BOOL(WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);

	Type_SetDeviceGammaRamp pGetDeviceGammaRamp;
	Type_SetDeviceGammaRamp pSetDeviceGammaRamp;

public:
	BOOL LoadLibrary();
	void FreeLibrary();
	BOOL LoadLibraryIfNeeded();
	BOOL SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
	BOOL GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);


	BOOL SetYellowRate(WORD rate, HDC hDC = NULL);


	BOOL SetGreenRate(WORD rate, HDC hDC = NULL);


	BOOL SetRedRate(WORD rate, HDC hDC = NULL);


	BOOL SetBlackRate(WORD rate, HDC hDC = NULL);


	BOOL SetRecommendRate(WORD rate, HDC hDC = NULL);

	// 自动模式时，立即生效
	VOID AutoTakeEffect();
};


extern CEyesGuard_en g_eyeguard;