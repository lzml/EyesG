#pragma once




class protect_eyes_en
{
public:
	protect_eyes_en();
	~protect_eyes_en();



	int m_brightness_value;
	int m_colorT;	//ɫ��
	int changeType;	// -1��ʾ��ûѡ��

	wstring m_strColor;
	wstring m_strAlpha;
	int m_viewHeight;



};

extern protect_eyes_en g_protect_eye_en;
