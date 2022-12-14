//stamp:058b10010c8925f4
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
			}
			const TCHAR * XML_MAINWND;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * skin;
		}values;
		class _IMG{
			public:
			_IMG(){
				traymenu_icons = _T("IMG:traymenu_icons");
				main_bk = _T("IMG:main_bk");
				btn_close = _T("IMG:btn_close");
				img_shadow = _T("IMG:img_shadow");
				ck_intelligent = _T("IMG:ck_intelligent");
				slider_bk = _T("IMG:slider_bk");
				slider_pos = _T("IMG:slider_pos");
				slider_thumb = _T("IMG:slider_thumb");
				ck_swich = _T("IMG:ck_swich");
				img_trans = _T("IMG:img_trans");
				img_btn_style_1 = _T("IMG:img_btn_style_1");
				img_ck_style_1 = _T("IMG:img_ck_style_1");
				img_check_1 = _T("IMG:img_check_1");
			}
			const TCHAR * traymenu_icons;
			const TCHAR * main_bk;
			const TCHAR * btn_close;
			const TCHAR * img_shadow;
			const TCHAR * ck_intelligent;
			const TCHAR * slider_bk;
			const TCHAR * slider_pos;
			const TCHAR * slider_thumb;
			const TCHAR * ck_swich;
			const TCHAR * img_trans;
			const TCHAR * img_btn_style_1;
			const TCHAR * img_ck_style_1;
			const TCHAR * img_check_1;
		}IMG;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
				ICON_trans_ico = _T("ICON:ICON_trans_ico");
			}
			const TCHAR * ICON_LOGO;
			const TCHAR * ICON_trans_ico;
		}ICON;
		class _SMENU{
			public:
			_SMENU(){
			}
		}SMENU;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"_name_start",65535},
		{L"adjustColorT",65538},
		{L"adjustligthness",65539},
		{L"btn_close",65537},
		{L"rd_BW",65548},
		{L"rd_auto_adjust",65546},
		{L"rd_gloomy",65545},
		{L"rd_normal",65541},
		{L"rd_reversedcolor",65547},
		{L"rd_warm1",65542},
		{L"rd_warm2",65543},
		{L"rd_warm3",65544},
		{L"tab_main",65536},
		{L"txt_color_info",65540}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			_name_start = namedXmlID[0].strName;
			adjustColorT = namedXmlID[1].strName;
			adjustligthness = namedXmlID[2].strName;
			btn_close = namedXmlID[3].strName;
			rd_BW = namedXmlID[4].strName;
			rd_auto_adjust = namedXmlID[5].strName;
			rd_gloomy = namedXmlID[6].strName;
			rd_normal = namedXmlID[7].strName;
			rd_reversedcolor = namedXmlID[8].strName;
			rd_warm1 = namedXmlID[9].strName;
			rd_warm2 = namedXmlID[10].strName;
			rd_warm3 = namedXmlID[11].strName;
			tab_main = namedXmlID[12].strName;
			txt_color_info = namedXmlID[13].strName;
		}
		 const wchar_t * _name_start;
		 const wchar_t * adjustColorT;
		 const wchar_t * adjustligthness;
		 const wchar_t * btn_close;
		 const wchar_t * rd_BW;
		 const wchar_t * rd_auto_adjust;
		 const wchar_t * rd_gloomy;
		 const wchar_t * rd_normal;
		 const wchar_t * rd_reversedcolor;
		 const wchar_t * rd_warm1;
		 const wchar_t * rd_warm2;
		 const wchar_t * rd_warm3;
		 const wchar_t * tab_main;
		 const wchar_t * txt_color_info;
		}name;

		class _id{
		public:
		const static int _name_start	=	65535;
		const static int adjustColorT	=	65538;
		const static int adjustligthness	=	65539;
		const static int btn_close	=	65537;
		const static int rd_BW	=	65548;
		const static int rd_auto_adjust	=	65546;
		const static int rd_gloomy	=	65545;
		const static int rd_normal	=	65541;
		const static int rd_reversedcolor	=	65547;
		const static int rd_warm1	=	65542;
		const static int rd_warm2	=	65543;
		const static int rd_warm3	=	65544;
		const static int tab_main	=	65536;
		const static int txt_color_info	=	65540;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
