////////////////////////////////////////////////////////////////////////////////////////
// AfxCntrlLib.h : Implementation of MFC Control Subclasses
#pragma once

#include "..\PAUsrApp\PAIFMainLib.h"
#include "SqlOleDB.h"

using namespace SQLOLEDB;

namespace AFXCNTRLLIB
{
	//
	// CPSEdit
	//
	class CPSEdit : public CEdit
	{
		DECLARE_DYNAMIC(CPSEdit)
	public:
		CPSEdit();
		~CPSEdit();

		// Extraction Operators
		operator const char*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const char*)s);
		}
		operator const wchar_t*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const wchar_t*)s);
		}

		DECLARE_MESSAGE_MAP()
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	private:
		_bstr_t s;
	}; 

	//
	// CPSComboBox
	//
	class CPSComboBox : public CComboBox
	{
		DECLARE_DYNAMIC(CPSComboBox)
	public:
		CPSComboBox();
		virtual ~CPSComboBox();

		// Extraction Operators
		operator const char*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const char*)s);
		}
		operator const wchar_t*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const wchar_t*)s);
		}
		LPCTSTR GetLBText(int nIndex)
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			if ((nIndex > -1) && (nIndex < GetCount()))
			{
				CComboBox::GetLBText(nIndex, sz);
			}
			s = _bstr_t(sz).copy();
			return ((LPCTSTR)s);
		}
		int GetLBText(int nIndex, LPTSTR lpszText)
		{
			return (CComboBox::GetLBText(nIndex, lpszText));
		}
		void GetLBText(int nIndex, CString& rString)
		{
			CComboBox::GetLBText(nIndex, rString);
		}

		DECLARE_MESSAGE_MAP()
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	private:
		_bstr_t s;

	};

	//
	// CPSListBox
	//
	class CPSListBox : public CListBox
	{
		DECLARE_DYNAMIC(CPSListBox)
	public:
		CPSListBox();
		virtual ~CPSListBox();

		// Extraction Operators
		operator const char*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const char*)s);
		}
		operator const wchar_t*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const wchar_t*)s);
		}

		DECLARE_MESSAGE_MAP()
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	private:
		_bstr_t s;

	};

	//
	// CPSCheckListBox
	//
	class CPSCheckListBox : public CCheckListBox
	{
		DECLARE_DYNAMIC(CPSCheckListBox)
	public:
		CPSCheckListBox();
		virtual ~CPSCheckListBox();
		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
		virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);
		virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);

		// Extraction Operators
		operator const char*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const char*)s);
		}
		operator const wchar_t*()
		{
			TCHAR sz[256]; memset(sz, 0, (sizeof(TCHAR) * 256));
			GetWindowText(sz, 255); s = _bstr_t(sz).copy(); return((const wchar_t*)s);
		}

		DECLARE_MESSAGE_MAP()
		afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	private:
		_bstr_t s;
	};

	//
	// CPSListCtrl
	//
	class CPSListCtrl : public CListCtrl
	{
		DECLARE_DYNAMIC(CPSListCtrl)

	public:
		CPSListCtrl();
		virtual ~CPSListCtrl();

		DECLARE_MESSAGE_MAP()
		afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
		afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	};

	// CPSSpecListCtrl
	class CPSSpecListCtrl : public CListCtrl
	{
		DECLARE_DYNAMIC(CPSSpecListCtrl)

	public:
		CPSSpecListCtrl();
		virtual ~CPSSpecListCtrl();

		void Init();
		void Hide();
		void ShowMatlSpec(SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>& MatlSpec);
		void ShowCGrpSpec(SqlInt& CGrpID, SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>& CGrpSpec);
		void ShowOperSpec(SqlChar<2>& DeptID, SqlChar<2>& OperID, SqlVarChar<255>& OperSpec);
		void EditMatlSpec(SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>* pMatlSpec);
		void EditCGrpSpec(SqlInt& CGrpID, SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>* pCGrpSpec);
		void EditOperSpec(SqlChar<2>& DeptID, SqlChar<2>& OperID, SqlVarChar<255>* pOperSpec);
		void SetReadOnly(BOOL bReadOnly) { m_edt.SetReadOnly(bReadOnly); }

		DECLARE_MESSAGE_MAP()
		afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
		afx_msg BOOL OnItemChanging(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg BOOL OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnEditUpdate();

	private:
		SqlVarChar<255>*	p_str;
		CPSEdit				m_edt;
		int					m_itm;
	};	

	// CPSCldrListCtrl
	class CPSCldrListCtrl : public CListCtrl
	{
		DECLARE_DYNAMIC(CPSCldrListCtrl)

	public:
		CPSCldrListCtrl();
		virtual ~CPSCldrListCtrl();

		typedef enum tagCldrShow {
			CS_VIEW					= 0,
			CS_EDIT					= 1,
			CS_DELE					= 2
		} CLDRSHOW, * LPCLDRSHOW;

		typedef enum tagCldrFill {
			CF_LINE					= 1,
			CF_AREA					= 2
		} CLDRFILL, * LPCLDRFILL;

		typedef enum tagCldrDraw {
			CD_BIT0					= 0,
			CD_BIT1					= 1
		} CLDRDRAW, * LPCLDRDRAW;

		typedef struct tagCldrBase {
			LPCLDR					pCldr;
			LPPLNTCLDRBASE			pPlnt;
			LPDEPTCLDRBASE			pDept;
			LPOPERCLDRBASE			pOper;
			LPEMPLCLDRBASE			pEmpl;
			LPMACHCLDRBASE			pMach;
		} CLDRBASE, * LPCLDRBASE;

		typedef struct tagCldrOver {
			LPHORZWEEK				pWeek;
			LPPLNTCLDROVER			pPlnt;
			LPDEPTCLDROVER			pDept;
			LPOPERCLDROVER			pOper;
			LPEMPLCLDROVER			pEmpl;
			LPMACHCLDROVER			pMach;
		} CLDROVER, * LPCLDROVER;

		typedef struct tagCldrWeek {
			SqlTinyInt				CldrDW;
			SqlInt					CldrD1;
			SqlInt					CldrD2;
			SqlInt					CldrD3;
			SqlInt					CldrD4;
			SqlInt					CldrD5;
			SqlInt					CldrD6;
			SqlInt					CldrD7;
		} CLDRWEEK, * LPCLDRWEEK;

		class CType
		{
		public:
			CType() : b_Init(false), p_Type(NULL), p_hTBr(NULL)
			{
			}
			void Init(CLDRTYPE* pType, HWND* phTBr)
			{
				b_Init = true;
				p_Type = pType;
				p_hTBr = phTBr;
			}
			operator CLDRTYPE()
			{
				if (!b_Init)
					return (CT_NULL);

				return (*p_Type);
			}
			CLDRTYPE operator= (CLDRTYPE v)
			{
				if (!b_Init)
					return (CT_NULL);

				TBBUTTONINFO bi = { sizeof(TBBUTTONINFO), (TBIF_COMMAND | TBIF_IMAGE), 0, 0, 0, 0, 0, 0, NULL, 0 };

				switch (v)
				{
				case CT_BASE:
					bi.idCommand = IDC_TBB_RUNB;
					bi.iImage = 2;
					::SendMessage(*p_hTBr, TB_SETBUTTONINFO, (WPARAM)IDC_TBB_RUNO, (LPARAM)&bi);
					break;
				case CT_OVER:
					bi.idCommand = IDC_TBB_RUNO;
					bi.iImage = 3;
					::SendMessage(*p_hTBr, TB_SETBUTTONINFO, (WPARAM)IDC_TBB_RUNB, (LPARAM)&bi);
					break;
				}

				*p_Type = v;
				return (*p_Type);
			}
		private:
			bool		b_Init;
			CLDRTYPE*	p_Type;
			HWND*		p_hTBr;
		};

		class CNode
		{
		public:
			CNode() : b_Init(false), p_Node(NULL), p_hTBr(NULL)
			{
			}
			void Init(CLDRNODE* pNode, HWND* phTBr)
			{
				b_Init = true;
				p_Node = pNode;
				p_hTBr = phTBr;
			}
			operator CLDRNODE() throw(CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				return (*p_Node);
			}
			CLDRNODE operator= (CLDRNODE v) throw(CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				*p_Node = v;
				return (*p_Node);
			}
		private:
			bool		b_Init;
			CLDRNODE*	p_Node;
			HWND*		p_hTBr;
		};

		class CShow
		{
		public:
			CShow() : b_Init(false), p_Show(NULL), p_hTBr(NULL)
			{
			}
			void Init(CLDRSHOW* pShow, HWND* phTBr)
			{
				b_Init = true;
				p_Show = pShow;
				p_hTBr = phTBr;
			}
			operator CLDRSHOW() throw (CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				return (*p_Show);
			}
			CLDRSHOW operator= (CLDRSHOW v) throw (CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_LINE, (LPARAM)MAKELONG(FALSE, 0));
				::SendMessage(*p_hTBr, TB_CHECKBUTTON, (WPARAM)IDC_TBB_LINE, (LPARAM)MAKELONG(FALSE, 0));
				::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_AREA, (LPARAM)MAKELONG(FALSE, 0));
				::SendMessage(*p_hTBr, TB_CHECKBUTTON, (WPARAM)IDC_TBB_AREA, (LPARAM)MAKELONG(FALSE, 0));
				::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_VIEW, (LPARAM)MAKELONG(FALSE, 0));
				::SendMessage(*p_hTBr, TB_CHECKBUTTON, (WPARAM)IDC_TBB_VIEW, (LPARAM)MAKELONG(FALSE, 0));

				switch (v)
				{
				case CS_VIEW:
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_SAVE, (LPARAM)MAKELONG(FALSE, 0));
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(FALSE, 0));
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_LINE, (LPARAM)MAKELONG(FALSE, 0));
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_AREA, (LPARAM)MAKELONG(FALSE, 0));
					::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_VIEW, (LPARAM)MAKELONG(TRUE, 0));
					break;
				case CS_EDIT:
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_SAVE, (LPARAM)MAKELONG(FALSE, 0));
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(FALSE, 0));
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_LINE, (LPARAM)MAKELONG(TRUE, 0));
					::SendMessage(*p_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_AREA, (LPARAM)MAKELONG(TRUE, 0));
					::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_VIEW, (LPARAM)MAKELONG(FALSE, 0));
					break;
				case CS_DELE:
					break;
				}

				*p_Show = v;
				return (*p_Show);
			}
		private:
			bool		b_Init;
			CLDRSHOW*	p_Show;
			HWND*		p_hTBr;
		};

		class CFill
		{
		public:
			CFill() : b_Init(false), p_Fill(NULL), p_hTBr(NULL)
			{
			}
			void Init(CLDRFILL* pFill, HWND* phTBr)
			{
				b_Init = true;
				p_Fill = pFill;
				p_hTBr = phTBr;
			}
			operator CLDRFILL() throw (CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				return (*p_Fill);
			}
			CLDRFILL operator= (CLDRFILL v) throw (CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				switch (v)
				{
				case CF_LINE:
					::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_LINE, (LPARAM)MAKELONG(TRUE, 0));
					break;
				case CF_AREA:
					::SendMessage(*p_hTBr, TB_PRESSBUTTON, (WPARAM)IDC_TBB_AREA, (LPARAM)MAKELONG(TRUE, 0));
					break;
				}

				*p_Fill = v;
				return (*p_Fill);
			}
		private:
			bool		b_Init;
			CLDRFILL*	p_Fill;
			HWND*		p_hTBr;
		};

		class CDraw
		{
		public:
			CDraw() : b_Init(false), p_Draw(NULL), p_hTBr(NULL)
			{
			}
			void Init(CLDRDRAW* pDraw, HWND* phTBr)
			{
				b_Init = true;
				p_Draw = pDraw;
				p_hTBr = phTBr;
			}
			operator CLDRDRAW() throw (CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				return (*p_Draw);
			}
			CLDRDRAW operator= (CLDRDRAW v) throw (CInvalidArgException)
			{
				if (!b_Init)
					AfxThrowInvalidArgException();

				*p_Draw = v;
				return (*p_Draw);
			}
		private:
			bool		b_Init;
			CLDRDRAW*	p_Draw;
			HWND*		p_hTBr;
		};

		void DumpCldr();
		bool NeedSave();
		void GotoNode();
		void GotoNode(SqlChar<3>& EmplID);
		void GotoNode(SqlChar<2>& DeptID);
		void GotoNode(SqlChar<2>& DeptID, SqlChar<2>& OperID);
		void GotoNode(SqlChar<2>& DeptID, SqlChar<2>& OperID, SqlChar<4>& MachID);
		
		HRESULT Init(LPCLDR pCldr, LPHORZWEEK pWeek, HWND hTBr);

		DECLARE_MESSAGE_MAP()
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnNMCustomDraw(NMHDR *pNMHDR, LRESULT *pResult);
	protected:
		virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	private:
		CFont			m_fntH;
		COLORREF		m_rgbG;
		CBrush			m_brHG;
		CBrush			m_brSG;
		COLORREF		m_rgbW;
		CBrush			m_brHW;
		CBrush			m_brSW;
		COLORREF		m_rgbB;
		CBrush			m_brHB;
		CBrush			m_brSB;
		COLORREF		m_rgbO;
		CBrush			m_brHO;
		CBrush			m_brSO;

		int				m_MDwn[1][2];	// Mouse Down Item/Subitem
		int				m_MSel[2][2];	// Mouse Selection Item/Subitem Pair
		CLDRBASE		m_Base;
		CLDROVER		m_Over;
	
	private:
		CLDRTYPE		m_Type;
		CLDRNODE		m_Node;
		CLDRSHOW		m_Show;
		CLDRFILL		m_Fill;
		CLDRDRAW		m_Draw;
		HWND			m_hTBr;

	public:
		CType			Type;
		CNode			Node;
		CShow			Show;
		CFill			Fill;
		CDraw			Draw;
		LONG			m_Cell[7][4];	// DOW x HOD

	};

	// CPSDateTimeCtrl
	class CPSDateTimeCtrl : public CDateTimeCtrl
	{
		DECLARE_DYNAMIC(CPSDateTimeCtrl)

	public:
		CPSDateTimeCtrl();
		virtual ~CPSDateTimeCtrl();

		void DoTest();

		void SetTextColor(COLORREF rgb)
		{
			memcpy(&f, &rgb, sizeof(COLORREF));
		}
		void SetBkgndColor(COLORREF rgb)
		{
			memcpy(&b, &rgb, sizeof(COLORREF));
		}

		// Extraction Operators
		operator SYSTEMTIME()
		{
			GetTime(&v);
			return (v);
		}

		DECLARE_MESSAGE_MAP()
		afx_msg void OnPaint();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	private:
		SYSTEMTIME	v;
		COLORREF	f;
		COLORREF	b;
	};


	// LVIS Constants not defined in commctrl.h
	#define LVIS_CHECKED			0x2000
	#define LVIS_UNCHECKED			0x1000

	// Hub Virtual Keys
	// - Bit Mask of Keys
	// - NMRIMCTRLMOVE contains 2 NMHDR structures
	//   - 1st for 
	#define HK_TAB					(0x1 <<  9)
	#define HK_SHIFT				(0x1 << 10)
	#define HK_CONTROL				(0x1 << 11)
	#define HK_END					(0x1 << 23)
	#define HK_HOME					(0x1 << 24)
	#define HK_LEFT					(0x1 << 25)
	#define HK_UP					(0x1 << 26)
	#define HK_RIGHT				(0x1 << 27)
	#define HK_DOWN					(0x1 << 28)

	// Hub List Control Messages
	// 
	#define	WM_RIMCTRLSETFOCUS		(WM_USER + 1)		// wParam=hRimCtl wParam=&NMRIMCTRL
	#define	WM_RIMCTRLKILLFOCUS		(WM_USER + 2)		// wParam=hRimCtl wParam=&NMRIMCTRL
	#define	WM_RIMCTRLKEYS			(WM_USER + 3)		// wParam=hRimCtl wParam=&NMRIMCTRL

	// Hub List Control Notifications
	// The dialog handler f() of this notification decides behavior
	// - when moving from last->first or first->last to repeat cycle or call 
	//   SetFocus.Next() or SetFocus.Prev() on dialog member to set the "focused" list item.
	// - when moving to next/previous rim control
	#define LVN_RIMCTRLKEYS			(LVN_FIRST-199)		// RimCtrl sends to parent dialog/NotifyReflectEx'd by HubListCtrl
	#define LVN_RIMCTRLMOVE			(LVN_FIRST-198)		// Dialog handles

	typedef struct tagNMRIMCTRL
	{
		//
		// hWndFrom is hWnd of CPSHubListCtrl
		// idFrom is ID of CPSHubListCtrl
		// Code is LVN_RIMCTRLKEYS | LVN_RIMCTRLMOVE
		NMHDR	hdr;
		//
		// hWndFrom is hWnd of CPSRim control
		// idFrom is ID of CPSRim control
		// Code is bit mask of HK_XXX
		// - Up/Down internal
		// - Left/Right passed up to dialog
		NMHDR	rim;
	}
	NMRIMCTRL, * LPNMRIMCTRL;

	// Forward Declares
	class CPSRimEdit;
	class CPSRimButton;
	class CPSRimDateTimeCtrl;
	class CPSRimComboBox;

	// CPSHubListCtrl
	//
	//
	// - Control to manage navigating items in a CListCtrl using rim controls
	// - Allows items in CListCtrl to be "focused" from rim control
	//   - Can use LVS_EX_CHECKBOXES to filter items
	//   - Can omit LVS_SINGLESEL to allow partial list as filter items
	//   - Can add LVS_SINGLESEL to allow complete list as filter items
	// - Designed to give dialog complete control over rim control paths (next, prev)
	// - CListCtrl is disabled when a rim control gets focus, enabled when a non-rim control gets focus
	// - CListCtrl Styles: Can be LVS_SINGLESEL. Can be LVS_EX_CHECKBOXES
	// - LVITEM's lParam member is usually existing POSITION of item in collection class. LVN_ITEMCHANGED handler
	//   is responsible for updating all controls from item at POSITION
	// - Rim control 4-Way navigation keys
	//   - PREV CTRL : Shift+Tab or Ctrl+Left Arrow
	//	 - NEXT CTRL : Tab or Ctrl+Right Arrow
	//   - PREV ITEM : Arrow Up
	//   - NEXT ITEM : Arrow Down

	class CPSHubListCtrl : public CListCtrl
	{
	DECLARE_DYNAMIC(CPSHubListCtrl)
	friend class CPSRimEdit;
	friend class CPSRimButton;
	friend class CPSRimDateTimeCtrl;
	friend class CPSRimComboBox;
	
	public:
		// - Item Filter Mode
		//   - Determined when focus set to rim control
		//   - FM_SELD If SelectedCount() >= 2
		//   - FM_CHKD If LVS_EX_CHECKBOXES && SelectedCount() <= 1
		//   - IF_LIST If !LVS_EX_CHECKBOXES && SelectedCount() <= 1
		typedef enum tagFilterFlag
		{
			FF_NONE			= 0,			// No items present
			FF_LIST			= 1,			// All items
			FF_SELD			= 2,			// All selected items, checked or otherwise
			FF_CHKD			= 4				// All checked items
		}
		FILTERFLAG, * LPFILTERFLAG;

		typedef enum tagFocusItem
		{
			FI_NONE			= 0,
			FI_HEAD			= 1,
			FI_TAIL			= 2,
			FI_PREV			= 3,
			FI_NEXT			= 4
		}
		FOCUSITEM, * LPFOCUSITEM;

		//
		// Nested Classes
		//
		class CFilterFlags
		{
		friend class CPSHubListCtrl;
		public:
			CFilterFlags(CPSHubListCtrl& o);
			operator int();
		private:
			CPSHubListCtrl&			_o;
		};

		class CUpDownEnabled
		{
		friend class CPSHubListCtrl;
		public:
			CUpDownEnabled(CPSHubListCtrl& o);
			operator BOOL();
		private:
			CPSHubListCtrl&			_o;
		};

		class CFocusedItem
		{
		friend class CPSHubListCtrl;
		public:
			class CIsHead
			{
			friend class CPSHubListCtrl;
			friend class CPSHubListCtrl::CFocusedItem;
			public:
				CIsHead(CFocusedItem& o);
				operator const BOOL() const;
			private:
				CFocusedItem&			_o;
			};
			class CIsTail
			{
			friend class CPSHubListCtrl;
			friend class CPSHubListCtrl::CFocusedItem;
			public:
				CIsTail(CPSHubListCtrl::CFocusedItem& o);
				operator const BOOL() const;
			private:
				CFocusedItem&			_o;
			};

			CFocusedItem(CPSHubListCtrl& o);
			operator const int() const;

		public:
			CIsHead					IsHead;
			CIsTail					IsTail;

		private:
			CPSHubListCtrl&			_o;
		};
		
		CPSHubListCtrl();
		virtual ~CPSHubListCtrl();
		const int FocusItem(FOCUSITEM fi);
		BOOL UpDownEnable(BOOL tf);

		BOOL AttachRimCtrl(HWND hwRim);
		BOOL DetachRimCtrl(HWND hwRim);
		BOOL AttachHubCtrl(HWND hwHub);
		BOOL DetachHubCtrl(HWND hwHub);

		DECLARE_MESSAGE_MAP()
		afx_msg LRESULT OnRimCtrlSetFocus(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnRimCtrlKillFocus(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnRimCtrlKeys(WPARAM wParam, LPARAM lParam);
		afx_msg void OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg BOOL OnItemChanging(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg BOOL OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);

	public:
		CFilterFlags			FilterFlags;
		CUpDownEnabled			UpDownEnabled;
		CFocusedItem			FocusedItem;

	protected:

	private:
		void ScanStat();
		void EnterRimLoop();
		void LeaveRimLoop();

		struct tagStats
		{
			int						cChkd;			// Items with State & 0x2000 = 0x2000
			int						cSeld;			// Items with State & 0x0002 = 0x0002
			int						iFcsd;			// Item  with State & 0x0001 = 0x0001
		}							Stats;
		struct tagItems
		{
			BOOL					bNRim;
			int						iFilt;
			BOOL					bUpDn;
			int						iSItm;
		}							Items;

		
		CAtlMap<HWND, int>		ChdRims;		// Child Rims Map
		CAtlMap<HWND, int>		ChdHubs;		// Child Hubs Map
		CAtlMap<HWND, int>		PrntHub;		// Parent Hub Map
	};

	// CPSRimEdit
	class CPSRimEdit : public CEdit
	{
	friend class CPSHubListCtrl;
	DECLARE_DYNAMIC(CPSRimEdit)

	public:
		CPSRimEdit();
		virtual ~CPSRimEdit();

		DECLARE_MESSAGE_MAP()
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg BOOL OnSetFocus();
		afx_msg BOOL OnKillFocus();

	private:
		HWND					hwHub;
		int						idHub;
		int						hkMap;
	};

	// CPSRimButton
	class CPSRimButton : public CButton
	{
	friend class CPSHubListCtrl;
	DECLARE_DYNAMIC(CPSRimButton)

	public:
		CPSRimButton();
		virtual ~CPSRimButton();

		DECLARE_MESSAGE_MAP()
		afx_msg UINT OnGetDlgCode();
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg BOOL OnSetFocus();
		afx_msg BOOL OnKillFocus();

	private:
		HWND					hwHub;
		int						idHub;
		int						hkMap;
	};
	// - Rim controls
	//   - send WM_
	//   - send set/kill focus to hub
	//   - a hub can be a rim if child of another hub listctrl

	// - Item Cycle State
	//   - Determined when focus set to rim control
	//   - IC_ISSELD If SelectedCount() >= 2
	//   - IC_ISCHKD If LVS_EX_CHECKBOXES && SelectedCount() <= 1
	//   - IC_INLIST If !LVS_EX_CHECKBOXES && SelectedCount() <= 1

	// - List Modal State
	//   - Determined when focus set to rim control

	// - Modeless state
	//   - Rim controls disabled but updated when single selection is made
	//   - ListCtrl allows check/uncheck select/unselect

	// - Modal state
	//   - Hub disabled but [checked], selected items re-drawn to show "focused" item
	//   - ListCtrl disallows check/uncheck select/unselect
	//   - Rim controls  

	// CPSRimDateTimeCtrl
	// CPSRimButton
	// CPSRimComboBox

	
}; // AFXCNTRLLIB



