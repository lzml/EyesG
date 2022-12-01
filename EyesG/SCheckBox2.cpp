#include "stdafx.h"
#include "SCheckBox2.h"


SCheckBox2::SCheckBox2() 
: m_check3skin(NULL),
m_ptCheckedBk(0,0)
{
}


SCheckBox2::~SCheckBox2()
{
}


void SCheckBox2::OnPaint(IRenderTarget *pRT)
{
	SPainter painter;
	BeforePaint(pRT, painter);
	ON_SCOPE_EXIT([&]{
		AfterPaint(pRT, painter);
	});

	DWORD state = GetState();
	CRect rc;
	GetClientRect(&rc);

	if (m_check3skin)
	{
		CRect rcIcon = GetClientRect();
		rcIcon.OffsetRect(m_ptCheckedBk);
		rcIcon = CRect(rcIcon.TopLeft(), m_check3skin->GetSkinSize());
		int iStates = m_check3skin->GetStates();

		if (!IsChecked())
		{
			if (iStates > 2)
			{
				if (state & WndState_Hover)
				{
					m_check3skin->Draw(pRT, rcIcon, 1);
				}
				else
				{
					m_check3skin->Draw(pRT, rcIcon, 0);
				}
			}
			else
			{
				m_check3skin->Draw(pRT, rcIcon, 0);
			}

		}
		else
		{
			if (iStates > 2)
			{
				m_check3skin->Draw(pRT, rcIcon, 2);
			}
			else
			{
				m_check3skin->Draw(pRT, rcIcon, 1);
			}

		}

	}

	CRect rcText;
	GetTextRect(rcText);
	DrawText(pRT, m_strText.GetText(), m_strText.GetText().GetLength(), rcText, GetTextAlign());

}