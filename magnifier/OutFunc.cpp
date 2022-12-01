#include "stdafx.h"
#include "OutFunc.h"
#include "ScreenColorEffect.h"

void __stdcall setColorInversion()
{
	g_SCEffect.ColorInversion();
}

void __stdcall setColorGray()
{
	g_SCEffect.ColorGray();
}

void __stdcall setColorNormal()
{
	g_SCEffect.ColorNormal();
}