#pragma once

#include <control/SCmnCtrl.h>

namespace SOUI
{
    class SRadioBox2 : public SRadioBox
    {
    SOUI_CLASS_NAME(SRadioBox2,L"radio2")
    public:
        SRadioBox2(void);
        ~SRadioBox2(void);
        
    protected:
        virtual CSize GetDesiredSize(LPCRECT pRcContainer)
        {
            if(m_pSkin) return m_pSkin->GetSkinSize();
            else return SWindow::GetDesiredSize(pRcContainer);
        }
        virtual void GetTextRect(LPRECT pRect)
        {
            SWindow::GetTextRect(pRect);
            pRect->left+=m_nTextOffset.x;
			pRect->top += m_nTextOffset.y;
        }
        virtual void DrawFocus(IRenderTarget *pRT)
        {
        }

    protected:       
        void OnPaint(IRenderTarget *pRT);

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
        SOUI_MSG_MAP_END()

        ISkinObj *  m_pIcon;
        CPoint      m_ptIcon;
        CPoint         m_nTextOffset;
		COLORREF		m_colorBkHover;
		COLORREF		m_colorBkSelect;
		ISkinObj *	m_pCheckedBk;
		CPoint		m_ptCheckedBk;
		COLORREF		m_colorTextNormal;
		COLORREF		m_colorTextSelect;

		SOUI_ATTRS_BEGIN()
			ATTR_SKIN(L"iconSkin", m_pIcon, TRUE)
			ATTR_POINT(L"iconPos", m_ptIcon, TRUE)
			ATTR_POINT(L"textOffset", m_nTextOffset, TRUE)
			ATTR_COLOR(L"colorBkHover", m_colorBkHover, TRUE)
			ATTR_COLOR(L"colorBkSelect", m_colorBkSelect, TRUE)
			ATTR_SKIN(L"checkedBk", m_pCheckedBk, TRUE)
			ATTR_POINT(L"checkedBkPos", m_ptCheckedBk, TRUE)
			ATTR_COLOR(L"colorTextNormal", m_colorTextNormal,FALSE)
			ATTR_COLOR(L"colorTextSelect", m_colorTextSelect,FALSE)
        SOUI_ATTRS_END()

    };

}
