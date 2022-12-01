#include "stdafx.h"
#include "ScreenColorEffect.h"


typedef void (WINAPI* FnMagInitialize)(void);
FnMagInitialize _fnMagInitialize = NULL;

typedef BOOL(WINAPI* FnMagSetFullscreenColorEffect)(LPVOID param);
FnMagSetFullscreenColorEffect _fnMagSetFullscreenColorEffect = NULL;


ScreenColorEffect g_SCEffect;

ScreenColorEffect::ScreenColorEffect()
	:m_hMagnification(NULL)
{
}


ScreenColorEffect::~ScreenColorEffect()
{
}

void ScreenColorEffect::init()
{
	m_hMagnification = LoadLibraryA("Magnification.dll");
	if (m_hMagnification)
	{
		_fnMagInitialize = (FnMagInitialize)GetProcAddress(m_hMagnification, "MagInitialize");
		if (_fnMagInitialize)
		{
			_fnMagInitialize();

			const char* fnName_1 = "MagSetFullscreenColorEffect";
			_fnMagSetFullscreenColorEffect = (FnMagSetFullscreenColorEffect)GetProcAddress(m_hMagnification, "MagSetFullscreenColorEffect");
			if (!_fnMagSetFullscreenColorEffect)
			{
				HMODULE hUser32 = LoadLibraryA("user32.dll");
				_fnMagSetFullscreenColorEffect = (FnMagSetFullscreenColorEffect)GetProcAddress(hUser32, "SetMagnificationDesktopColorEffect");

				//float magEffectInvert[5][5] = { 0 };
				//typedef BOOL(WINAPI* FnMagGetFullscreenColorEffect)(LPVOID param);
				//FnMagGetFullscreenColorEffect xxx = (FnMagGetFullscreenColorEffect)GetProcAddress(hUser32, "GetMagnificationDesktopColorEffect");
				//if (xxx)
				//{

				//	xxx(&magEffectInvert);
				//}
				//int  m = 0;
			}
		}
	}
}


void ScreenColorEffect::ColorInversion()
{


	//反色矩阵
	float magEffectInvert[5][5] =
	{
		{-1.0f,		0.0f,	0.0f,		0.0f,	0.0f},
		{0.0f,		-1.0f,	0.0f,		0.0f,	0.0f},
		{0.0f,		0.0f,	-1.0f,		0.0f,	0.0f},
		{0.0f,		0.0f,	0.0f,		1.0f,	0.0f},
		{1.0f,		1.0f,	1.0f,		0.0f,	1.0f}
	};


	if (_fnMagSetFullscreenColorEffect)
	{
		_fnMagSetFullscreenColorEffect(magEffectInvert);
	}
}


void ScreenColorEffect::ColorGray()
{
	//灰色矩阵
	float redScale = 0.2126f, greenScale = 0.7152f, blueScale = 0.0722f;
	float magGrayInvert[5][5] =
	{
		{ redScale,   redScale,   redScale,   0.0f,		0.0f},
		{ greenScale, greenScale, greenScale, 0.0f,		0.0f},
		{ blueScale,  blueScale,  blueScale,  0.0f,		0.0f},
		{ 0.0f,       0.0f,       0.0f,       1.0f,		0.0f},
		{ 0.0f,       0.0f,       0.0f,       0.0f,		1.0f }
	};
	if (_fnMagSetFullscreenColorEffect)
	{
		_fnMagSetFullscreenColorEffect(magGrayInvert);
	}
}

void ScreenColorEffect::ColorNormal()
{
	//正常矩阵
	float magNormal[5][5] =
	{
		{ 1.0f,		  0.0f,		0.0f,		0.0f,		0.0f},
		{ 0.0f,		  1.0f,		0.0f,		0.0f,		0.0f},
		{ 0.0f,		  0.0f,		1.0f,		0.0f,		0.0f},
		{ 0.0f,       0.0f,     0.0f,       1.0f,		0.0f},
		{ 0.0f,       0.0f,     0.0f,       0.0f,		1.0f }
	};
	if (_fnMagSetFullscreenColorEffect)
	{
		_fnMagSetFullscreenColorEffect(magNormal);
	}
}