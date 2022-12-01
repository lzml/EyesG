#include "stdafx.h"
#include "SRadioBox2.h"

namespace SOUI
{
    SRadioBox2::SRadioBox2(void):m_pIcon(NULL),m_nTextOffset(0)
    {
		m_colorBkHover = 0;
		m_colorBkSelect = 0;
		m_pCheckedBk = NULL;
		m_ptCheckedBk = { 0, 0};
		m_colorTextNormal = 0;
		m_colorTextSelect = 0;

    }

    SRadioBox2::~SRadioBox2(void)
    {
    }

    void SRadioBox2::OnPaint(IRenderTarget *pRT)
    {
		SPainter painter;
		BeforePaint(pRT, painter);
		ON_SCOPE_EXIT([&]{
			AfterPaint(pRT, painter);
		});

		//×´Ì¬
		DWORD state = GetState();
		CRect rc;
		GetClientRect(&rc);
		if (m_colorBkSelect != 0 && (state & WndState_Check ))
		{
			pRT->FillSolidRect(rc, m_colorBkSelect);
		}
		else if (m_colorBkHover != 0 && (state & WndState_Hover))
		{
			pRT->FillSolidRect(rc, m_colorBkHover);
		}
		else if (GetStyle().m_crBg != 0 && (state & WndState_Normal))
		{
			pRT->FillSolidRect(rc, GetStyle().m_crBg);
		}

		//Æ¤·ô
        if(m_pSkin)
        {
            int nState = 0;
            if(GetState() & WndState_Check) nState = 2;
            else if(GetState() & WndState_PushDown) nState = 2;
            else if(GetState() & WndState_Hover) nState = 1;
            
            m_pSkin->Draw(pRT,rc,nState);
        }

		if (m_pCheckedBk && IsChecked())
		{
			CRect rcIcon = GetClientRect();
			rcIcon.OffsetRect(m_ptCheckedBk);
			rcIcon = CRect(rcIcon.TopLeft(), m_pCheckedBk->GetSkinSize());
			m_pCheckedBk->Draw(pRT, rcIcon, IIF_STATE3(0, 0, 0, 0));
		}

        if(m_pIcon)
        {
            CRect rcIcon=GetClientRect();
            rcIcon.OffsetRect(m_ptIcon);
            rcIcon=CRect(rcIcon.TopLeft(),m_pIcon->GetSkinSize());
            m_pIcon->Draw(pRT,rcIcon,IIF_STATE3(GetState(),0,1,2));


        }



		//ÉèÖÃÎÄ×ÖÑÕÉ«
		if (IsChecked())
		{
			if (m_colorTextSelect != 0)
			{
				pRT->SetTextColor(m_colorTextSelect);
			}

		}
		else
		{
			if (m_colorTextNormal != 0)
			{
				pRT->SetTextColor(m_colorTextNormal);
			}
		
		}

		
		

		CRect rcText;
		GetTextRect(rcText);
		DrawText(pRT, m_strText.GetText(), m_strText.GetText().GetLength(), rcText, GetTextAlign());


    }

}
