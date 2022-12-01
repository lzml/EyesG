#pragma once




class protect_eyes_en
{
public:
	protect_eyes_en();
	~protect_eyes_en();



	int m_brightness_value;
	int m_colorT;	//色温
	int changeType;	// -1表示都没选中

	wstring m_strColor;
	wstring m_strAlpha;
	int m_viewHeight;



};

extern protect_eyes_en g_protect_eye_en;
