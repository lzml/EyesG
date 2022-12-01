#pragma once
class ScreenColorEffect
{
public:
	ScreenColorEffect();
	~ScreenColorEffect();

	void init();

	void ColorInversion();

	void ColorGray();

	void ColorNormal();

private:

	 


	HMODULE m_hMagnification;
};

extern ScreenColorEffect g_SCEffect;