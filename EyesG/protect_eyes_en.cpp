#include "stdafx.h"
#include "protect_eyes_en.h"
#include "path.h"
#include "string.h"

#include <iostream>
#include <fstream>
#include "uifunc.h"
#include "EyesGuard_en.h"
#include "uifunc.h"


extern wstring g_strUserSid;

protect_eyes_en g_protect_eye_en;

protect_eyes_en::protect_eyes_en()
{
	 m_brightness_value = 100;
	 m_colorT = 100;
	 changeType = Mode_None;
	 m_strColor = L"#000000";
	 m_strAlpha = L"240";
	 m_viewHeight = 400;

}


protect_eyes_en::~protect_eyes_en()
{
}

