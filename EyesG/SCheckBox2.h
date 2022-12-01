#pragma once

class SCheckBox2 :
	public SCheckBox
{
	SOUI_CLASS_NAME(SCheckBox2, L"check2")
public:
	SCheckBox2();
	~SCheckBox2();

	virtual void DrawFocus(IRenderTarget *pRT) override
	{

	}
	virtual void GetTextRect(LPRECT pRect)
	{
		SWindow::GetTextRect(pRect);
		pRect->left += m_nTextOffset.x;
		pRect->top += m_nTextOffset.y;
	}
protected:
	void OnPaint(IRenderTarget *pRT);


	ISkinObj*		m_check3skin;
	CPoint		m_ptCheckedBk;
	CPoint         m_nTextOffset;

	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)
	SOUI_MSG_MAP_END()




	SOUI_ATTRS_BEGIN()
		ATTR_SKIN(L"check3skin", m_check3skin, TRUE)
		ATTR_POINT(L"checkedBkPos", m_ptCheckedBk, TRUE)
		ATTR_POINT(L"textOffset", m_nTextOffset, TRUE)
	SOUI_ATTRS_END()
};

