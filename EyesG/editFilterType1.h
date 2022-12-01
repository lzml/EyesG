#pragma once


class editFilterType1 :public SOUI::InPutFilter
{
public:
	BOOL	filter(UINT nChar, UINT nRepCnt, UINT nFlags, SStringW oldString);
};

