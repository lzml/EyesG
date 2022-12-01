#include "stdafx.h"
#include "editFilterType1.h"




BOOL	editFilterType1::filter(UINT nChar, UINT nRepCnt, UINT nFlags, SStringW oldString)
{	if (isdigit(nChar))
	{

	}
	else
	{
		return TRUE;
	}
	return FALSE;
}