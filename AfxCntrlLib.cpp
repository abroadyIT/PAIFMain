#include "stdafx.h"

#include "..\PAUsrApp\PAIFMain.h"
#include "..\PAIFLibs\AfxCntrlLib.h"

extern	LONG	cMSpc;
extern	LPMSPC	pMSpc;
extern	LONG	cCSpc;
extern	LPCSPC	pCSpc;
extern	LONG	cOSpc;
extern	LPOSPC	pOSpc;

//
//	AfxCntrlLib
//
//	CEdit
//	 CXXXEdit
//   - Overrides
namespace AFXCNTRLLIB
{
	//
	// CPSEdit
	//
	IMPLEMENT_DYNAMIC(CPSEdit, CEdit)

	CPSEdit::CPSEdit()
	{
	}
	CPSEdit::~CPSEdit()
	{
	}
	BEGIN_MESSAGE_MAP(CPSEdit, CEdit)
		ON_WM_CHAR()
		ON_WM_KEYDOWN()
	END_MESSAGE_MAP()

	void CPSEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// AfxTrace(_T("CPSEdit::OnChar(%c)\n"), nChar);
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	void CPSEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch ((BYTE)nChar)
		{
		case VK_DOWN:
		case VK_UP:
			((CWnd*)GetParent())->SendNotifyMessage(WM_KEYDOWN, (WPARAM)nChar, MAKELPARAM(nRepCnt, nFlags));
			break;
		default:
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			break;
		}
	}

	//
	// CPSComboBox
	//
	IMPLEMENT_DYNAMIC(CPSComboBox, CComboBox)

	CPSComboBox::CPSComboBox()
	{
	}

	CPSComboBox::~CPSComboBox()
	{
	}

	BEGIN_MESSAGE_MAP(CPSComboBox, CComboBox)
		ON_WM_CTLCOLOR()
	END_MESSAGE_MAP()

	// CPSComboBox message handlers
	HBRUSH CPSComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		static CBrush wht(RGB(255, 255, 255));

		// Change any attributes of the DC here
		switch (nCtlColor)
		{
		case CTLCOLOR_STATIC:
			pDC->SetTextColor(RGB(127, 127, 127));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		default:
			// Return default brush
			return CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
		}
	}

	//
	// CPSListBox
	//
	IMPLEMENT_DYNAMIC(CPSListBox, CListBox)

	CPSListBox::CPSListBox()
	{
	}

	CPSListBox::~CPSListBox()
	{
	}

	BEGIN_MESSAGE_MAP(CPSListBox, CListBox)
		ON_WM_CTLCOLOR()
	END_MESSAGE_MAP()

	// CPSListBox message handlers
	HBRUSH CPSListBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		static CBrush wht(RGB(255, 255, 255));

		// Change any attributes of the DC here
		switch (nCtlColor)
		{
		case CTLCOLOR_STATIC:
			pDC->SetTextColor(RGB(127, 127, 127));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		default:
			// Return default brush
			return CListBox::OnCtlColor(pDC, pWnd, nCtlColor);
		}
	}

	//
	// CPSCheckListBox
	//
	IMPLEMENT_DYNAMIC(CPSCheckListBox, CCheckListBox)

	CPSCheckListBox::CPSCheckListBox()
	{
	}

	CPSCheckListBox::~CPSCheckListBox()
	{
	}

	void AFXCNTRLLIB::CPSCheckListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		CCheckListBox::DrawItem(lpDrawItemStruct);
	}

	int AFXCNTRLLIB::CPSCheckListBox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/)
	{
		// TODO:  Add your code to determine the sorting order of the specified items
		// return -1 = item 1 sorts before item 2
		// return 0 = item 1 and item 2 sort the same
		// return 1 = item 1 sorts after item 2
		return 0;
	}

	void AFXCNTRLLIB::CPSCheckListBox::MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/)
	{
		// TODO:  Add your code to determine the size of specified item
	}

	BEGIN_MESSAGE_MAP(CPSCheckListBox, CCheckListBox)
		ON_WM_CTLCOLOR()
	END_MESSAGE_MAP()

	// CPSCheckListBox message handlers
	HBRUSH CPSCheckListBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
	{
		static CBrush wht(RGB(255, 255, 255));

		// Change any attributes of the DC here
		switch (nCtlColor)
		{
		case CTLCOLOR_STATIC:
			pDC->SetTextColor(RGB(127, 127, 127));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		default:
			// Return default brush
			return CCheckListBox::OnCtlColor(pDC, pWnd, nCtlColor);
		}
	}

	//
	// CPSListCtrl
	//
	IMPLEMENT_DYNAMIC(CPSListCtrl, CListCtrl)

	CPSListCtrl::CPSListCtrl()
	{
	}

	CPSListCtrl::~CPSListCtrl()
	{
	}

	BEGIN_MESSAGE_MAP(CPSListCtrl, CListCtrl)
		ON_WM_NCLBUTTONDOWN()
		ON_WM_VSCROLL()
		ON_WM_CTLCOLOR_REFLECT()
	END_MESSAGE_MAP()

	// CPSListCtrl message handlers
	void CPSListCtrl::OnNcLButtonDown(UINT nHitTest, CPoint point)
	{
		AfxTrace(_T("CPSListCtrl::OnNcLButtonDown\n"));
		CListCtrl::OnNcLButtonDown(nHitTest, point);
		SetFocus();
	}
	void CPSListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
	{
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
		SetFocus();
	}
	HBRUSH CPSListCtrl::CtlColor(CDC* pDC, UINT nCtlColor)
	{
		HBRUSH hbr = CListCtrl::OnCtlColor(pDC, this, nCtlColor);

		// TODO:  Change any attributes of the DC here

		// TODO:  Return a different brush if the default is not desired
		if (GetBkColor() == RGB(0, 0, 0))
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(GetBkColor());
		}
		return hbr;
	}

	//
	// CPSSpecListCtrl
	//
	IMPLEMENT_DYNAMIC(CPSSpecListCtrl, CListCtrl)

	CPSSpecListCtrl::CPSSpecListCtrl() : p_str(NULL), m_itm(-1)
	{
	}
	CPSSpecListCtrl::~CPSSpecListCtrl()
	{
	}
	void CPSSpecListCtrl::Init()
	{
		if (!m_edt.m_hWnd)
		{
			m_edt.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 20, 20), this, 0x0066);
			m_edt.SetFont(GetFont(), 1);
		}

		RECT	rc;		GetWindowRect(&rc);
		int		w1;		w1 = (int)(((double)rc.right - (double)rc.left) * (double)0.28125) - 2; // / (double)1.278);
		int		w2;		w2 = (int)(((double)rc.right - (double)rc.left) * (double)0.71875) - 2; // / (double)1.278);

		while (GetHeaderCtrl()->GetItemCount())
		{
			DeleteColumn(0);
		}

		InsertColumn(0, _T("Field"), LVCFMT_LEFT, w1, -1);
		InsertColumn(1, _T("Value"), LVCFMT_LEFT, w2, 1);
		
		RedrawWindow();   
	}
	void CPSSpecListCtrl::Hide()
	{
		if (m_edt.m_hWnd)
		{
			m_edt.ShowWindow(SW_HIDE);
		}
		DeleteAllItems();
	}
	void CPSSpecListCtrl::ShowMatlSpec(SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>& MatlSpec)
	{
		DeleteAllItems();

		TCHAR	buf[256]; memset(buf, 0, sizeof(buf));
		TCHAR	val[256]; memset(val, 0, sizeof(val));
		int		n			= -1;
		size_t	p			= 0;

		p_str = NULL; 
		_tcscpy_s(buf, _countof(buf), (LPCTSTR)MatlSpec);
		if (_tcslen(buf) < 255)
		{
			memset(&buf[_tcslen(buf) + 1], 0, (255 - _tcslen(buf)));
		}

		for (LONG i = 0; i < cMSpc; i++)
		{
			if (pMSpc[i].MGrpID == (LPCTSTR)MGrpID)
			{
				if ((pMSpc[i].MClsID == SqlNull) || (pMSpc[i].MClsID == (LPCTSTR)MClsID))
				{
					n = InsertItem(++n, (LPCTSTR)pMSpc[i].Item.Name);

					memset(val, 0, sizeof(val));
					_tcsncpy_s(val, _countof(val), &buf[(BYTE)pMSpc[i].Item.VNdx - (BYTE)1], (size_t)(BYTE)pMSpc[i].Item.VLen);
					
					for (p = (_tcslen(val) - 1); p >= 0; p--) 
					{
						if (val[p] == _T(' ')) val[p] = 0; else break;
					}
					for (p = 0; p < _tcslen(val); p++)
					{
						if (val[p] != _T(' ')) break;
					}

					SetItemText(n, 1, &val[p]);
					SetItemData(n, (DWORD_PTR)&pMSpc[i].Item);
				}
			}
		}
	}
	void CPSSpecListCtrl::ShowCGrpSpec(SqlInt& CGrpID, SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>& CGrpSpec)
	{
		DeleteAllItems();

		TCHAR	buf[256]; memset(buf, 0, sizeof(buf));
		TCHAR	val[256]; memset(val, 0, sizeof(val));
		int		n			= -1;
		size_t	p			= 0;

		p_str = NULL; 
		_tcscpy_s(buf, _countof(buf), (LPCTSTR)CGrpSpec);
		if (_tcslen(buf) < 255)
		{
			memset(&buf[_tcslen(buf) + 1], 0, (255 - _tcslen(buf)));
		}

		for (LONG i = 0; i < cCSpc; i++)
		{
			if (((LONG)pCSpc[i].CGrpOD & (LONG)CGrpID) == (LONG)pCSpc[i].CGrpOD)
			{
				if (pCSpc[i].MGrpID == (LPCTSTR)MGrpID)
				{
					if ((pCSpc[i].MClsID == SqlNull) || (pCSpc[i].MClsID == (LPCTSTR)MClsID))
					{
						n = InsertItem(++n, (LPCTSTR)pCSpc[i].Item.Name);

						memset(val, 0, sizeof(val));
						_tcsncpy_s(val, _countof(val), &buf[(BYTE)pCSpc[i].Item.VNdx - (BYTE)1], (size_t)(BYTE)pCSpc[i].Item.VLen);
						
						for (p = (_tcslen(val) - 1); p >= 0; p--) 
						{
							if (val[p] == _T(' ')) val[p] = 0; else break;
						}
						for (p = 0; p < _tcslen(val); p++)
						{
							if (val[p] != _T(' ')) break;
						}

						SetItemText(n, 1, &val[p]);
						SetItemData(n, (DWORD_PTR)&pCSpc[i].Item);
					}
				}
			}
		}
	}
	void CPSSpecListCtrl::ShowOperSpec(SqlChar<2>& DeptID, SqlChar<2>& OperID, SqlVarChar<255>& OperSpec)
	{
		DeleteAllItems();

		TCHAR	buf[256]; memset(buf, 0, sizeof(buf));
		TCHAR	val[256]; memset(val, 0, sizeof(val));
		int		n			= -1;
		size_t	p			= 0;

		p_str = NULL; 
		_tcscpy_s(buf, _countof(buf), (LPCTSTR)OperSpec);
		if (_tcslen(buf) < 255)
		{
			memset(&buf[_tcslen(buf) + 1], 0, (255 - _tcslen(buf)));
		}

		for (LONG i = 0; i < cOSpc; i++)
		{
			if (pOSpc[i].DeptID == (LPCTSTR)DeptID)
			{
				if ((pOSpc[i].OperID == SqlNull) || (pOSpc[i].OperID == (LPCTSTR)OperID))
				{
					n = InsertItem(++n, (LPCTSTR)pOSpc[i].Item.Name);

					memset(val, 0, sizeof(val));
					_tcsncpy_s(val, _countof(val), &buf[(BYTE)pOSpc[i].Item.VNdx - (BYTE)1], (size_t)(BYTE)pOSpc[i].Item.VLen);
					
					for (p = (_tcslen(val) - 1); p >= 0; p--) 
					{
						if (val[p] == _T(' ')) val[p] = 0; else break;
					}
					for (p = 0; p < _tcslen(val); p++)
					{
						if (val[p] != _T(' ')) break;
					}

					SetItemText(n, 1, &val[p]);
					SetItemData(n, (DWORD_PTR)&pOSpc[i].Item);
				}
			}
		}
	}
	void CPSSpecListCtrl::EditMatlSpec(SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>* pMatlSpec)
	{
		DeleteAllItems();

		TCHAR	buf[256]; memset(buf, 0, sizeof(buf));
		TCHAR	val[256]; memset(val, 0, sizeof(val));
		int		n			= -1;
		size_t	p			= 0;

		p_str = pMatlSpec; 
		_tcscpy_s(buf, _countof(buf), (LPCTSTR)*pMatlSpec);
		if (_tcslen(buf) < 255)
		{
			memset(&buf[_tcslen(buf) + 1], 0, (255 - _tcslen(buf)));
		}

		for (LONG i = 0; i < cMSpc; i++)
		{
			if (pMSpc[i].MGrpID == (LPCTSTR)MGrpID)
			{
				if ((pMSpc[i].MClsID == SqlNull) || (pMSpc[i].MClsID == (LPCTSTR)MClsID))
				{
					n = InsertItem(++n, (LPCTSTR)pMSpc[i].Item.Name);

					memset(val, 0, sizeof(val));
					_tcsncpy_s(val, _countof(val), &buf[(BYTE)pMSpc[i].Item.VNdx - (BYTE)1], (size_t)(BYTE)pMSpc[i].Item.VLen);
					
					for (p = (_tcslen(val) - 1); p >= 0; p--) 
					{
						if (val[p] == _T(' ')) val[p] = 0; else break;
					}
					for (p = 0; p < _tcslen(val); p++)
					{
						if (val[p] != _T(' ')) break;
					}

					SetItemText(n, 1, &val[p]);
					SetItemData(n, (DWORD_PTR)&pMSpc[i].Item);
				}
			}
		}
	}
	void CPSSpecListCtrl::EditCGrpSpec(SqlInt& CGrpID, SqlChar<1>& MGrpID, SqlChar<2>& MClsID, SqlVarChar<255>* pCGrpSpec)
	{
		DeleteAllItems();

		TCHAR	buf[256]; memset(buf, 0, sizeof(buf));
		TCHAR	val[256]; memset(val, 0, sizeof(val));
		int		n			= -1;
		size_t	p			= 0;

		p_str = pCGrpSpec; 
		_tcscpy_s(buf, _countof(buf), (LPCTSTR)*pCGrpSpec);
		if (_tcslen(buf) < 255)
		{
			memset(&buf[_tcslen(buf) + 1], 0, (255 - _tcslen(buf)));
		}

		for (LONG i = 0; i < cCSpc; i++)
		{
			if (((LONG)pCSpc[i].CGrpOD & (LONG)CGrpID) == (LONG)pCSpc[i].CGrpOD)
			{
				if (pCSpc[i].MGrpID == (LPCTSTR)MGrpID)
				{
					if ((pCSpc[i].MClsID == SqlNull) || (pCSpc[i].MClsID == (LPCTSTR)MClsID))
					{
						n = InsertItem(++n, (LPCTSTR)pCSpc[i].Item.Name);

						memset(val, 0, sizeof(val));
						_tcsncpy_s(val, _countof(val), &buf[(BYTE)pCSpc[i].Item.VNdx - (BYTE)1], (size_t)(BYTE)pCSpc[i].Item.VLen);
						
						for (p = (_tcslen(val) - 1); p >= 0; p--) 
						{
							if (val[p] == _T(' ')) val[p] = 0; else break;
						}
						for (p = 0; p < _tcslen(val); p++)
						{
							if (val[p] != _T(' ')) break;
						}

						SetItemText(n, 1, &val[p]);
						SetItemData(n, (DWORD_PTR)&pCSpc[i].Item);
					}
				}
			}
		}
		if (n > -1)
		{
			SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		}
	}
	void CPSSpecListCtrl::EditOperSpec(SqlChar<2>& DeptID, SqlChar<2>& OperID, SqlVarChar<255>* pOperSpec)
	{
		DeleteAllItems();

		TCHAR	buf[256]; memset(buf, 0, sizeof(buf));
		TCHAR	val[256]; memset(val, 0, sizeof(val));
		int		n			= -1;
		size_t	p			= 0;

		p_str = pOperSpec;
		_tcscpy_s(buf, _countof(buf), (LPCTSTR)*pOperSpec);
		if (_tcslen(buf) < 255)
		{
			memset(&buf[_tcslen(buf) + 1], 0, (255 - _tcslen(buf)));
		}

		for (LONG i = 0; i < cOSpc; i++)
		{
			if (pOSpc[i].DeptID == (LPCTSTR)DeptID)
			{
				if ((pOSpc[i].OperID == SqlNull) || (pOSpc[i].OperID == (LPCTSTR)OperID))
				{
					n = InsertItem(++n, (LPCTSTR)pOSpc[i].Item.Name);

					memset(val, 0, sizeof(val));
					_tcsncpy_s(val, _countof(val), &buf[(BYTE)pOSpc[i].Item.VNdx - (BYTE)1], (size_t)(BYTE)pOSpc[i].Item.VLen);
					
					for (p = (_tcslen(val) - 1); p >= 0; p--) 
					{
						if (val[p] == _T(' ')) val[p] = 0; else break;
					}
					for (p = 0; p < _tcslen(val); p++)
					{
						if (val[p] != _T(' ')) break;
					}

					SetItemText(n, 1, &val[p]);
					SetItemData(n, (DWORD_PTR)&pOSpc[i].Item);
				}
			}
		}
	}

	BEGIN_MESSAGE_MAP(CPSSpecListCtrl, CListCtrl)
		ON_WM_CTLCOLOR_REFLECT()
		ON_NOTIFY_REFLECT_EX(LVN_ITEMCHANGING, &CPSSpecListCtrl::OnItemChanging)
		ON_NOTIFY_REFLECT_EX(LVN_ITEMCHANGED, &CPSSpecListCtrl::OnItemChanged)
		ON_EN_UPDATE(0x0066, &CPSSpecListCtrl::OnEditUpdate)
	END_MESSAGE_MAP()

	// CPSSpecListCtrl message handlers
	HBRUSH CPSSpecListCtrl::CtlColor(CDC* pDC, UINT nCtlColor)
	{
		static CBrush wht(RGB(255, 255, 255));

		// Change any attributes of the DC here
		switch (nCtlColor)
		{
		case CTLCOLOR_STATIC:
			pDC->SetTextColor(RGB(127, 127, 127));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		case CTLCOLOR_EDIT:
		case CTLCOLOR_LISTBOX:
			pDC->SetTextColor(RGB(127, 127, 127));
			pDC->SetBkColor(RGB(255, 255, 255));
			return ((HBRUSH)wht);
		default:
			// Return NULL brush and let Parent Handle
			return (HBRUSH)NULL;
		}
	}
	BOOL CPSSpecListCtrl::OnItemChanging(NMHDR *pNMHDR, LRESULT *pResult)
	{
		m_itm = -1;
		
		if (p_str)
		{
			if (m_edt.m_hWnd)
			{
				m_edt.ShowWindow(SW_HIDE);
			}
		}
		return (TRUE);
	}
	BOOL CPSSpecListCtrl::OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLISTVIEW	pNMLV		= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		CRect			rect;
		LPSITM			pI			= (LPSITM)GetItemData(pNMLV->iItem);

		m_itm = pNMLV->iItem;

		if (p_str)
		{
			if ((pI != NULL) && (m_edt.m_hWnd))
			{
				GetSubItemRect(pNMLV->iItem, 1, LVIR_BOUNDS, rect);
				m_edt.MoveWindow(rect.TopLeft().x + 3, rect.TopLeft().y, rect.Width() - 3, rect.Height(), 1);
				if (pI->DBDT == (BYTE)131)
				{
					m_edt.SetLimitText((UINT)(BYTE)pI->VLen);
					// m_edt.SetLimitText((UINT)((BYTE)pI->DBNP + (BYTE)pI->DBNS + (((BYTE)pI->DBNS > 0) ? (BYTE)1 : (BYTE)0)));
				}
				else
				{
					m_edt.SetLimitText((UINT)(BYTE)pI->VLen);
				}
				m_edt.SetWindowTextW((LPCTSTR)GetItemText(pNMLV->iItem, 1));
				m_edt.SetSel(0, -1);
				m_edt.ShowWindow(SW_SHOW);
				m_edt.SetFocus();
			}
		}
		return (TRUE);
	}
	void CPSSpecListCtrl::OnEditUpdate()
	{
		TCHAR			val[256];	memset(val, 0, sizeof(val));
		TCHAR			num[256];	memset(num, 0, sizeof(num));
		TCHAR			tmp[256];	memset(tmp, 0, sizeof(tmp));
		TCHAR			str[256];	memset(str, 0, sizeof(str));
		TCHAR			fmt[256];	memset(fmt, 0, sizeof(fmt));
		TCHAR			err[256];	memset(err, 0, sizeof(err));
		BOOL			bOK			= TRUE;
		LPSITM			pI			= (LPSITM)GetItemData(m_itm);
		BYTE			iNP			= 0;
		BYTE			nND			= 0;
		BYTE			iNS			= 0;
		BYTE			iML			= 0;
		double			dbl			= 0;

		_stprintf_s(str, _countof(str), _T("%s"), (LPCTSTR)*p_str);
		for (size_t i = _tcslen(str); i < 256; i++)	str[i] = _T('\0');

		AfxTrace(_T("0:%s\n"), str);

		if ((pI != NULL) && (m_edt.m_hWnd) && (p_str))
		{		
			m_edt.GetWindowTextW(val, 255);

			switch (pI->DBDT)
			{
			case 131:
				dbl = _tcstod(val, NULL);
				if (pI->DBNS > (BYTE)0)
				{
					_stprintf_s(fmt, _countof(fmt), _T("%%%d.%df"), (BYTE)pI->DBNP + (BYTE)1, (BYTE)pI->DBNS);
				}
				else
				{
					_stprintf_s(fmt, _countof(fmt), _T("%%%d.%df"), (BYTE)pI->DBNP, (BYTE)pI->DBNS);
				}
				_stprintf_s(num, _countof(num), fmt, dbl);
				_stprintf_s(fmt, _countof(fmt), _T("%%%ds"), (BYTE)pI->VLen);
				_stprintf_s(tmp, _countof(tmp), fmt, num);

				if (_tcslen(tmp) != (BYTE)pI->VLen)
				{
					bOK = FALSE;
					_stprintf_s(
						err, 
						_countof(err), 
						_T("Specification field [%s] of type numeric(%d,%d). Value [%s] is not valid and will be changed to 0."),
						(LPCTSTR)pI->Name,
						(byte)pI->DBNP,
						(byte)pI->DBNS,
						tmp
					);
					::AfxMessageBox(err, MB_ICONEXCLAMATION);
					m_edt.SetWindowTextW(_T("0"));
				}

				for (BYTE i = ((BYTE)pI->VNdx - (BYTE)1), j = 0; i < (((BYTE)pI->VNdx - (BYTE)1) + (BYTE)pI->VLen); i++, j++)
				{
					str[i] = tmp[j];
				}

				AfxTrace(_T("1:%s\n"), str);

				break;
			case 203:
				_stprintf_s(fmt, _countof(fmt), _T("%%%ds"), (BYTE)pI->VLen);
				_stprintf_s(tmp, _countof(tmp), fmt, val);

				if (_tcslen(tmp) != (BYTE)pI->VLen)
				{
					bOK = FALSE;
					_stprintf_s(
						err, 
						_countof(err), 
						_T("Specification field [%s] of type char(%d). Value [%s] is not valid and will be cleared."),
						(LPCTSTR)pI->Name,
						(byte)pI->DBML,
						tmp
					);
					::AfxMessageBox(err, MB_ICONEXCLAMATION);
					m_edt.SetWindowTextW(_T(""));
				}

				for (BYTE i = ((BYTE)pI->VNdx - (BYTE)1), j = 0; i < (((BYTE)pI->VNdx - (BYTE)1) + (BYTE)pI->VLen); i++, j++)
				{
					str[i] = tmp[j];
				}

//				AfxTrace(_T("1:%s\n"), str);
				
				break;
			case 204:
				_stprintf_s(fmt, _countof(fmt), _T("%%-%ds"), (BYTE)pI->VLen);
				_stprintf_s(tmp, _countof(tmp), fmt, val);

				if (_tcslen(tmp) != (BYTE)pI->VLen)
				{
					bOK = FALSE;
					_stprintf_s(
						err, 
						_countof(err), 
						_T("Specification field [%s] of type varchar(%d). Value [%s] is not valid and will be cleared."),
						(LPCTSTR)pI->Name,
						(byte)pI->DBML,
						tmp
					);
					::AfxMessageBox(err, MB_ICONEXCLAMATION);
					m_edt.SetWindowTextW(_T(""));
				}

				for (size_t i = (size_t)((BYTE)pI->VLen - (BYTE)1); i > 0; i--)
				{
					if (tmp[i] == _T(' '))
					{
						tmp[i] = _T('\0');
					}
					else
					{
						break;
					}
				}
				for (BYTE i = ((BYTE)pI->VNdx - (BYTE)1), j = 0; i < (((BYTE)pI->VNdx - (BYTE)1) + (BYTE)pI->VLen); i++, j++)
				{
					str[i] = tmp[j];
				}

//				AfxTrace(_T("1:%s\n"), str);
				
				break;
			}

			if (bOK)
			{
				SetItemText(m_itm, 1, tmp);
				(*p_str) = str;
			}
		}
	}

	//
	// CPSCldrListCtrl
	//
	IMPLEMENT_DYNAMIC(CPSCldrListCtrl, CListCtrl)

	CPSCldrListCtrl::CPSCldrListCtrl()
	{
		m_Draw = CD_BIT0;
		m_Fill = CF_LINE;
		m_Show = CS_VIEW;
		m_Node = CN_NULL;
		m_Type = CT_NULL;
		m_hTBr = NULL;

		Type.Init(&m_Type, &m_hTBr);
		Node.Init(&m_Node, &m_hTBr);
		Show.Init(&m_Show, &m_hTBr);
		Fill.Init(&m_Fill, &m_hTBr);
		Draw.Init(&m_Draw, &m_hTBr);

		m_Over.pMach = NULL;
		m_Over.pOper = NULL;
		m_Over.pDept = NULL;
		m_Over.pEmpl = NULL;
		m_Over.pPlnt = NULL;
		m_Over.pWeek = NULL;

		m_Base.pMach = NULL;
		m_Base.pOper = NULL;
		m_Base.pDept = NULL;
		m_Base.pEmpl = NULL;
		m_Base.pPlnt = NULL;
		m_Base.pCldr = NULL;

		for (LONG i = 0; i < 7; i++)
		{
			for (LONG j = 0; j < 4; j++)
			{
				m_Cell[i][j] = 0;
			}
		}

		m_MSel[0][0] = m_MSel[0][1] = m_MSel[1][0] = m_MSel[1][1] = m_MDwn[0][0] = m_MDwn[0][1] = -1;

		m_fntH.CreatePointFont(60, _T("Lucida Console"));
		m_rgbG = RGB(127, 127, 127);
		m_brHG.CreateHatchBrush(HS_DIAGCROSS, m_rgbG);
		m_brSG.CreateSolidBrush(m_rgbG);
		m_rgbW = RGB(255, 255, 255);
		m_brHW.CreateHatchBrush(HS_DIAGCROSS, m_rgbW);
		m_brSW.CreateSolidBrush(m_rgbW);
		m_rgbB = RGB(0, 64, 255);
		m_brHB.CreateHatchBrush(HS_DIAGCROSS, m_rgbB);
		m_brSB.CreateSolidBrush(m_rgbB);
		m_rgbO = RGB(255, 64, 0);
		m_brHO.CreateHatchBrush(HS_DIAGCROSS, m_rgbO);
		m_brSO.CreateSolidBrush(m_rgbO);
	}

	CPSCldrListCtrl::~CPSCldrListCtrl()
	{
		m_brSO.DeleteObject();
		m_brHO.DeleteObject();
		m_brSB.DeleteObject();
		m_brHB.DeleteObject();
		m_brHW.DeleteObject();
		m_brSW.DeleteObject();
		m_brSG.DeleteObject();
		m_brHG.DeleteObject();
		m_fntH.DeleteObject();
	}

	void CPSCldrListCtrl::DumpCldr()
	{
		LPCTSTR	pzBit[2]	= {_T("0"), _T("1")};
		TCHAR	szTxt[99];	memset(szTxt, 0, sizeof(szTxt));

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				_stprintf_s(
					szTxt,
					_countof(szTxt),
					_T("%1d.%1d: %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"),
					i, j,
					pzBit[(((m_Cell[i][j] & (0x1 << 0)) == (0x1 << 0)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 1)) == (0x1 << 1)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 2)) == (0x1 << 2)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 3)) == (0x1 << 3)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 4)) == (0x1 << 4)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 5)) == (0x1 << 5)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 6)) == (0x1 << 6)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 7)) == (0x1 << 7)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 8)) == (0x1 << 8)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 9)) == (0x1 << 9)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 10)) == (0x1 << 10)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 11)) == (0x1 << 11)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 12)) == (0x1 << 12)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 13)) == (0x1 << 13)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 14)) == (0x1 << 14)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 15)) == (0x1 << 15)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 16)) == (0x1 << 16)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 17)) == (0x1 << 17)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 18)) == (0x1 << 18)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 19)) == (0x1 << 19)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 20)) == (0x1 << 20)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 21)) == (0x1 << 21)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 22)) == (0x1 << 22)) ? 1 : 0)],
					pzBit[(((m_Cell[i][j] & (0x1 << 23)) == (0x1 << 23)) ? 1 : 0)]
				);
				AfxTrace(_T("%s\n"), szTxt);
			}
			AfxTrace(_T("%s\n"), _T(""));
		}
	}

	bool CPSCldrListCtrl::NeedSave()
	{
		bool	be	= false;

		switch(m_Type)
		{
		case CT_BASE:

			switch (m_Node)
			{
			case CN_PLNT:
				
				if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else
				{
					be = true;
				}
				break;

			case CN_PLNTEMPL:
				
				if (m_Base.pEmpl->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					be = true;
				}
				break;

			case CN_PLNTDEPT:
				
				if (m_Base.pDept->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else
				{
					be = true;
				}
				break;

			case CN_PLNTDEPTOPER:
				
				if (m_Base.pOper->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Base.pDept->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else
				{
					be = true;
				}
				break;

			case CN_PLNTDEPTOPERMACH:
				
				if (m_Base.pMach->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Base.pOper->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Base.pDept->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					be = true;
				}
				break;
			}
			break;

		case CT_OVER:

			switch (m_Node)
			{
			case CN_PLNT:
				
				if (m_Over.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else
				{
					be = true;
				}
				break;

			case CN_PLNTEMPL:

				if (m_Over.pEmpl->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pEmpl->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Over.pPlnt->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					be = true;
				}
				break;

			case CN_PLNTDEPT:
				
				if (m_Over.pDept->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pDept->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Over.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else
				{
					be = true;
				}
				break;

			case CN_PLNTDEPTOPER:
				
				if (m_Over.pOper->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pOper->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Over.pDept->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pDept->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Over.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else
				{
					be = true;
				}
				break;

			case CN_PLNTDEPTOPERMACH:

				if (m_Over.pMach->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][1])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][1])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][1])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][1])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][1])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][1])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][1])
						be = true;
				}
				else if (m_Base.pMach->CldrDW != SqlNull)
				{
					if (m_Cell[0][0] != m_Cell[0][2])
						be = true;
					else if (m_Cell[1][0] != m_Cell[1][2])
						be = true;
					else if (m_Cell[2][0] != m_Cell[2][2])
						be = true;
					else if (m_Cell[3][0] != m_Cell[3][2])
						be = true;
					else if (m_Cell[4][0] != m_Cell[4][2])
						be = true;
					else if (m_Cell[5][0] != m_Cell[5][2])
						be = true;
					else if (m_Cell[6][0] != m_Cell[6][2])
						be = true;
				}
				else if (m_Over.pOper->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Base.pOper->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Over.pDept->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Base.pDept->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Over.pPlnt->CldrDW != SqlNull)
				{
					be = true;
				}
				else if (m_Base.pPlnt->CldrDW != SqlNull)
				{
					be = true;
				}
				break;
			}
			break;
		}

		return (be);
	}

	void CPSCldrListCtrl::GotoNode()
	{
		m_Over.pMach = NULL;
		m_Over.pOper = NULL;
		m_Over.pDept = NULL;
		m_Over.pEmpl = NULL;

		m_Base.pMach = NULL;
		m_Base.pOper = NULL;
		m_Base.pDept = NULL;
		m_Base.pEmpl = NULL;

		m_Node = CN_PLNT;

		for (LONG i = 0; i < 7; i++)
		{
			for (LONG j = 0; j < 4; j++)
			{
				m_Cell[i][j] = 0;
			}
		}

		::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(false, 0));

		switch (m_Type)
		{
		case CT_BASE:

			// POOL (All Hours / All Days)
			m_Cell[0][3] = 0x00FFFFFF;
			m_Cell[1][3] = 0x00FFFFFF;
			m_Cell[2][3] = 0x00FFFFFF;
			m_Cell[3][3] = 0x00FFFFFF;
			m_Cell[4][3] = 0x00FFFFFF;
			m_Cell[5][3] = 0x00FFFFFF;
			m_Cell[6][3] = 0x00FFFFFF;
			
			// ITEM => EDIT (Plnt.Base Hours | No Hours if no record)
			if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}

			break;

		case CT_OVER:

			// POOL (All Hours / Available Days)
			m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)m_Over.pWeek->CldrD1 : 0x00000000);
			m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)m_Over.pWeek->CldrD2 : 0x00000000);
			m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)m_Over.pWeek->CldrD3 : 0x00000000);
			m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)m_Over.pWeek->CldrD4 : 0x00000000);
			m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)m_Over.pWeek->CldrD5 : 0x00000000);
			m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)m_Over.pWeek->CldrD6 : 0x00000000);
			m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)m_Over.pWeek->CldrD7 : 0x00000000);
			
			// ITEM => EDIT (Plnt.Over Hours | No Hours if no record)
			if (m_Over.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;
		}

		DumpCldr();

		RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
		RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
		RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

		InvalidateRect(&rcXX, 0);
	}
	
	void CPSCldrListCtrl::GotoNode(SqlChar<3>& EmplID)
	{
		m_Over.pMach = NULL;
		m_Over.pOper = NULL;
		m_Over.pDept = NULL;
		m_Over.pEmpl = NULL;

		if (m_Type == CT_OVER)
		{
			for (LONG e = 0; e < m_Over.pPlnt->cEmpl; e++)
			{
				if (m_Over.pPlnt->pEmpl[e].EmplID == (LPCTSTR)EmplID)
				{
					m_Over.pEmpl = &m_Over.pPlnt->pEmpl[e];
					break;
				}
			}
		}

		m_Base.pMach = NULL;
		m_Base.pOper = NULL;
		m_Base.pDept = NULL;
		m_Base.pEmpl = NULL;

		for (LONG e = 0; e < m_Base.pPlnt->cEmpl; e++)
		{
			if (m_Base.pPlnt->pEmpl[e].EmplID == (LPCTSTR)EmplID)
			{
				m_Base.pEmpl = &m_Base.pPlnt->pEmpl[e];
				break;
			}
		}

		m_Node = CN_PLNTEMPL;

		for (LONG i = 0; i < 7; i++)
		{
			for (LONG j = 0; j < 4; j++)
			{
				m_Cell[i][j] = 0;
			}
		}

		::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(false, 0));

		switch (m_Type)
		{
		case CT_BASE:

			// POOL (Plnt.Base Hours)
			if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][3] = ((LONG)m_Base.pPlnt->CldrD1);
				m_Cell[1][3] = ((LONG)m_Base.pPlnt->CldrD2);
				m_Cell[2][3] = ((LONG)m_Base.pPlnt->CldrD3);
				m_Cell[3][3] = ((LONG)m_Base.pPlnt->CldrD4);
				m_Cell[4][3] = ((LONG)m_Base.pPlnt->CldrD5);
				m_Cell[5][3] = ((LONG)m_Base.pPlnt->CldrD6);
				m_Cell[6][3] = ((LONG)m_Base.pPlnt->CldrD7);
			}

			// ITEM => EDIT
			if (m_Base.pEmpl->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pEmpl->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pEmpl->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pEmpl->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pEmpl->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pEmpl->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pEmpl->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pEmpl->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}

			break;

		case CT_OVER:

			// POOL
			if (m_Over.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pPlnt->CldrDW) == 0x02) ? (LONG)m_Over.pPlnt->CldrD1 : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pPlnt->CldrDW) == 0x04) ? (LONG)m_Over.pPlnt->CldrD2 : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pPlnt->CldrDW) == 0x08) ? (LONG)m_Over.pPlnt->CldrD3 : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pPlnt->CldrDW) == 0x10) ? (LONG)m_Over.pPlnt->CldrD4 : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pPlnt->CldrDW) == 0x20) ? (LONG)m_Over.pPlnt->CldrD5 : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pPlnt->CldrDW) == 0x40) ? (LONG)m_Over.pPlnt->CldrD6 : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pPlnt->CldrDW) == 0x80) ? (LONG)m_Over.pPlnt->CldrD7 : 0x00000000);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Over.pWeek->CldrD1) : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Over.pWeek->CldrD2) : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Over.pWeek->CldrD3) : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Over.pWeek->CldrD4) : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Over.pWeek->CldrD5) : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Over.pWeek->CldrD6) : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Over.pWeek->CldrD7) : 0x00000000);
			}

			// ITEM => EDIT
			if (m_Over.pEmpl->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pEmpl->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pEmpl->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pEmpl->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pEmpl->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pEmpl->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pEmpl->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pEmpl->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pEmpl->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pEmpl->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pEmpl->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pEmpl->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pEmpl->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pEmpl->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pEmpl->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pEmpl->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;
		}

		DumpCldr();

		RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
		RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
		RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

		InvalidateRect(&rcXX, 0);
	}

	void CPSCldrListCtrl::GotoNode(SqlChar<2>& DeptID)
	{
		m_Over.pMach = NULL;
		m_Over.pOper = NULL;
		m_Over.pDept = NULL;
		m_Over.pEmpl = NULL;

		if (m_Type == CT_OVER)
		{
			for (LONG d = 0; d < m_Over.pPlnt->cDept; d++)
			{
				if (m_Over.pPlnt->pDept[d].DeptID == (LPCTSTR)DeptID)
				{
					m_Over.pDept = &m_Over.pPlnt->pDept[d];
					break;
				}
			}
		}

		m_Base.pMach = NULL;
		m_Base.pOper = NULL;
		m_Base.pDept = NULL;
		m_Base.pEmpl = NULL;

		for (LONG d = 0; d < m_Base.pPlnt->cDept; d++)
		{
			if (m_Base.pPlnt->pDept[d].DeptID == (LPCTSTR)DeptID)
			{
				m_Base.pDept = &m_Base.pPlnt->pDept[d];
				break;
			}
		}

		m_Node = CN_PLNTDEPT;

		for (LONG i = 0; i < 7; i++)
		{
			for (LONG j = 0; j < 4; j++)
			{
				m_Cell[i][j] = 0;
			}
		}

		::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(false, 0));

		switch (m_Type)
		{
		case CT_BASE:

			// POOL (All Hours / All Days)
			m_Cell[0][3] = 0x00FFFFFF;
			m_Cell[1][3] = 0x00FFFFFF;
			m_Cell[2][3] = 0x00FFFFFF;
			m_Cell[3][3] = 0x00FFFFFF;
			m_Cell[4][3] = 0x00FFFFFF;
			m_Cell[5][3] = 0x00FFFFFF;
			m_Cell[6][3] = 0x00FFFFFF;

			// ITEM => EDIT
			if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			
				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;

		case CT_OVER:

			// POOL
			m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)m_Over.pWeek->CldrD1 : 0x00000000);
			m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)m_Over.pWeek->CldrD2 : 0x00000000);
			m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)m_Over.pWeek->CldrD3 : 0x00000000);
			m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)m_Over.pWeek->CldrD4 : 0x00000000);
			m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)m_Over.pWeek->CldrD5 : 0x00000000);
			m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)m_Over.pWeek->CldrD6 : 0x00000000);
			m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)m_Over.pWeek->CldrD7 : 0x00000000);

			// ITEM => EDIT
			if (m_Over.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			
				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Over.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;
		}

		DumpCldr();

		RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
		RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
		RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

		InvalidateRect(&rcXX, 0);
	}
	
	void CPSCldrListCtrl::GotoNode(SqlChar<2>& DeptID, SqlChar<2>& OperID)
	{
		m_Over.pMach = NULL;
		m_Over.pOper = NULL;
		m_Over.pDept = NULL;
		m_Over.pEmpl = NULL;

		if (m_Type == CT_OVER)
		{
			for (LONG d = 0; d < m_Over.pPlnt->cDept; d++)
			{
				if (m_Over.pPlnt->pDept[d].DeptID == (LPCTSTR)DeptID)
				{
					for (LONG o = 0; o < m_Over.pPlnt->pDept[d].cOper; o++)
					{
						if (m_Over.pPlnt->pDept[d].pOper[o].OperID == (LPCTSTR)OperID)
						{
							m_Over.pDept = &m_Over.pPlnt->pDept[d];
							m_Over.pOper = &m_Over.pPlnt->pDept[d].pOper[o];
							break;
						}
					}
					break;
				}
			}
		}

		m_Base.pMach = NULL;
		m_Base.pOper = NULL;
		m_Base.pDept = NULL;
		m_Base.pEmpl = NULL;

		for (LONG d = 0; d < m_Base.pPlnt->cDept; d++)
		{
			if (m_Base.pPlnt->pDept[d].DeptID == (LPCTSTR)DeptID)
			{
				for (LONG o = 0; o < m_Base.pPlnt->pDept[d].cOper; o++)
				{
					if (m_Base.pPlnt->pDept[d].pOper[o].OperID == (LPCTSTR)OperID)
					{
						m_Base.pDept = &m_Base.pPlnt->pDept[d];
						m_Base.pOper = &m_Base.pPlnt->pDept[d].pOper[o];
						break;
					}
				}
				break;
			}
		}

		m_Node = CN_PLNTDEPTOPER;

		for (LONG i = 0; i < 7; i++)
		{
			for (LONG j = 0; j < 4; j++)
			{
				m_Cell[i][j] = 0;
			}
		}

		::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(false, 0));

		switch (m_Type)
		{
		case CT_BASE:

			// POOL (All Hours / All Days)
			m_Cell[0][3] = 0x00FFFFFF;
			m_Cell[1][3] = 0x00FFFFFF;
			m_Cell[2][3] = 0x00FFFFFF;
			m_Cell[3][3] = 0x00FFFFFF;
			m_Cell[4][3] = 0x00FFFFFF;
			m_Cell[5][3] = 0x00FFFFFF;
			m_Cell[6][3] = 0x00FFFFFF;

			// ITEM => EDIT
			if (m_Base.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pOper->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pOper->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pOper->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pOper->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pOper->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pOper->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pOper->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;

		case CT_OVER:

			// POOL
			m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)m_Over.pWeek->CldrD1 : 0x00000000);
			m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)m_Over.pWeek->CldrD2 : 0x00000000);
			m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)m_Over.pWeek->CldrD3 : 0x00000000);
			m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)m_Over.pWeek->CldrD4 : 0x00000000);
			m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)m_Over.pWeek->CldrD5 : 0x00000000);
			m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)m_Over.pWeek->CldrD6 : 0x00000000);
			m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)m_Over.pWeek->CldrD7 : 0x00000000);

			// ITEM => EDIT
			if (m_Over.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pOper->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pOper->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pOper->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pOper->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pOper->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pOper->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pOper->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pOper->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pOper->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pOper->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pOper->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pOper->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pOper->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pOper->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Over.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Over.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;
		}

		DumpCldr();

		RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
		RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
		RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

		InvalidateRect(&rcXX, 0);
	}

	void CPSCldrListCtrl::GotoNode(SqlChar<2>& DeptID, SqlChar<2>& OperID, SqlChar<4>& MachID)
	{
		m_Over.pMach = NULL;
		m_Over.pOper = NULL;
		m_Over.pDept = NULL;
		m_Over.pEmpl = NULL;

		if (m_Type == CT_OVER)
		{
			for (LONG d = 0; d < m_Over.pPlnt->cDept; d++)
			{
				if (m_Over.pPlnt->pDept[d].DeptID == (LPCTSTR)DeptID)
				{
					for (LONG o = 0; o < m_Over.pPlnt->pDept[d].cOper; o++)
					{
						if (m_Over.pPlnt->pDept[d].pOper[o].OperID == (LPCTSTR)OperID)
						{
							for (LONG m = 0; m < m_Over.pPlnt->pDept[d].pOper[o].cMach; m++)
							{
								if (m_Over.pPlnt->pDept[d].pOper[o].pMach[m].MachID == (LPCTSTR)MachID)
								{
									m_Over.pDept = &m_Over.pPlnt->pDept[d];
									m_Over.pOper = &m_Over.pPlnt->pDept[d].pOper[o];
									m_Over.pMach = &m_Over.pPlnt->pDept[d].pOper[o].pMach[m];
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
		}

		m_Base.pMach = NULL;
		m_Base.pOper = NULL;
		m_Base.pDept = NULL;
		m_Base.pEmpl = NULL;

		for (LONG d = 0; d < m_Base.pPlnt->cDept; d++)
		{
			if (m_Base.pPlnt->pDept[d].DeptID == (LPCTSTR)DeptID)
			{
				for (LONG o = 0; o < m_Base.pPlnt->pDept[d].cOper; o++)
				{
					if (m_Base.pPlnt->pDept[d].pOper[o].OperID == (LPCTSTR)OperID)
					{
						for (LONG m = 0; m < m_Base.pPlnt->pDept[d].pOper[o].cMach; m++)
						{
							if (m_Base.pPlnt->pDept[d].pOper[o].pMach[m].MachID == (LPCTSTR)MachID)
							{
								m_Base.pDept = &m_Base.pPlnt->pDept[d];
								m_Base.pOper = &m_Base.pPlnt->pDept[d].pOper[o];
								m_Base.pMach = &m_Base.pPlnt->pDept[d].pOper[o].pMach[m];
								break;
							}
						}
						break;
					}
				}
				break;
			}
		}

		m_Node = CN_PLNTDEPTOPERMACH;

		for (LONG i = 0; i < 7; i++)
		{
			for (LONG j = 0; j < 4; j++)
			{
				m_Cell[i][j] = 0;
			}
		}

		::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(false, 0));

		switch (m_Type)
		{
		case CT_BASE:

			// POOL (Plnt.Base Hours)
			if (m_Base.pMach->CldrDW != SqlNull)
			{
				m_Cell[0][3] = ((LONG)m_Base.pMach->CldrD1);
				m_Cell[1][3] = ((LONG)m_Base.pMach->CldrD2);
				m_Cell[2][3] = ((LONG)m_Base.pMach->CldrD3);
				m_Cell[3][3] = ((LONG)m_Base.pMach->CldrD4);
				m_Cell[4][3] = ((LONG)m_Base.pMach->CldrD5);
				m_Cell[5][3] = ((LONG)m_Base.pMach->CldrD6);
				m_Cell[6][3] = ((LONG)m_Base.pMach->CldrD7);
			}
			else if (m_Base.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][3] = ((LONG)m_Base.pOper->CldrD1);
				m_Cell[1][3] = ((LONG)m_Base.pOper->CldrD2);
				m_Cell[2][3] = ((LONG)m_Base.pOper->CldrD3);
				m_Cell[3][3] = ((LONG)m_Base.pOper->CldrD4);
				m_Cell[4][3] = ((LONG)m_Base.pOper->CldrD5);
				m_Cell[5][3] = ((LONG)m_Base.pOper->CldrD6);
				m_Cell[6][3] = ((LONG)m_Base.pOper->CldrD7);
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][3] = ((LONG)m_Base.pDept->CldrD1);
				m_Cell[1][3] = ((LONG)m_Base.pDept->CldrD2);
				m_Cell[2][3] = ((LONG)m_Base.pDept->CldrD3);
				m_Cell[3][3] = ((LONG)m_Base.pDept->CldrD4);
				m_Cell[4][3] = ((LONG)m_Base.pDept->CldrD5);
				m_Cell[5][3] = ((LONG)m_Base.pDept->CldrD6);
				m_Cell[6][3] = ((LONG)m_Base.pDept->CldrD7);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][3] = ((LONG)m_Base.pPlnt->CldrD1);
				m_Cell[1][3] = ((LONG)m_Base.pPlnt->CldrD2);
				m_Cell[2][3] = ((LONG)m_Base.pPlnt->CldrD3);
				m_Cell[3][3] = ((LONG)m_Base.pPlnt->CldrD4);
				m_Cell[4][3] = ((LONG)m_Base.pPlnt->CldrD5);
				m_Cell[5][3] = ((LONG)m_Base.pPlnt->CldrD6);
				m_Cell[6][3] = ((LONG)m_Base.pPlnt->CldrD7);
			}

			// ITEM => EDIT
			if (m_Base.pMach->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pMach->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pMach->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pMach->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pMach->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pMach->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pMach->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pMach->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pOper->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pOper->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pOper->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pOper->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pOper->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pOper->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pOper->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;

		case CT_OVER:

			// POOL
			if (m_Over.pMach->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pMach->CldrDW) == 0x02) ? (LONG)m_Over.pMach->CldrD1 : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pMach->CldrDW) == 0x04) ? (LONG)m_Over.pMach->CldrD2 : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pMach->CldrDW) == 0x08) ? (LONG)m_Over.pMach->CldrD3 : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pMach->CldrDW) == 0x10) ? (LONG)m_Over.pMach->CldrD4 : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pMach->CldrDW) == 0x20) ? (LONG)m_Over.pMach->CldrD5 : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pMach->CldrDW) == 0x40) ? (LONG)m_Over.pMach->CldrD6 : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pMach->CldrDW) == 0x80) ? (LONG)m_Over.pMach->CldrD7 : 0x00000000);
			}
			else if (m_Base.pMach->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)(m_Base.pMach->CldrD1 & (LONG)m_Over.pWeek->CldrD1) : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)(m_Base.pMach->CldrD2 & (LONG)m_Over.pWeek->CldrD2) : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)(m_Base.pMach->CldrD3 & (LONG)m_Over.pWeek->CldrD3) : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)(m_Base.pMach->CldrD4 & (LONG)m_Over.pWeek->CldrD4) : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)(m_Base.pMach->CldrD5 & (LONG)m_Over.pWeek->CldrD5) : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)(m_Base.pMach->CldrD6 & (LONG)m_Over.pWeek->CldrD6) : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)(m_Base.pMach->CldrD7 & (LONG)m_Over.pWeek->CldrD7) : 0x00000000);
			}
			else if (m_Over.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pOper->CldrDW) == 0x02) ? (LONG)m_Over.pOper->CldrD1 : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pOper->CldrDW) == 0x04) ? (LONG)m_Over.pOper->CldrD2 : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pOper->CldrDW) == 0x08) ? (LONG)m_Over.pOper->CldrD3 : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pOper->CldrDW) == 0x10) ? (LONG)m_Over.pOper->CldrD4 : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pOper->CldrDW) == 0x20) ? (LONG)m_Over.pOper->CldrD5 : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pOper->CldrDW) == 0x40) ? (LONG)m_Over.pOper->CldrD6 : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pOper->CldrDW) == 0x80) ? (LONG)m_Over.pOper->CldrD7 : 0x00000000);
			}
			else if (m_Base.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)(m_Base.pOper->CldrD1 & (LONG)m_Over.pWeek->CldrD1) : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)(m_Base.pOper->CldrD2 & (LONG)m_Over.pWeek->CldrD2) : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)(m_Base.pOper->CldrD3 & (LONG)m_Over.pWeek->CldrD3) : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)(m_Base.pOper->CldrD4 & (LONG)m_Over.pWeek->CldrD4) : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)(m_Base.pOper->CldrD5 & (LONG)m_Over.pWeek->CldrD5) : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)(m_Base.pOper->CldrD6 & (LONG)m_Over.pWeek->CldrD6) : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)(m_Base.pOper->CldrD7 & (LONG)m_Over.pWeek->CldrD7) : 0x00000000);
			}
			else if (m_Over.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pDept->CldrDW) == 0x02) ? (LONG)m_Over.pDept->CldrD1 : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pDept->CldrDW) == 0x04) ? (LONG)m_Over.pDept->CldrD2 : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pDept->CldrDW) == 0x08) ? (LONG)m_Over.pDept->CldrD3 : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pDept->CldrDW) == 0x10) ? (LONG)m_Over.pDept->CldrD4 : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pDept->CldrDW) == 0x20) ? (LONG)m_Over.pDept->CldrD5 : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pDept->CldrDW) == 0x40) ? (LONG)m_Over.pDept->CldrD6 : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pDept->CldrDW) == 0x80) ? (LONG)m_Over.pDept->CldrD7 : 0x00000000);
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Over.pWeek->CldrD1) : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Over.pWeek->CldrD2) : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Over.pWeek->CldrD3) : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Over.pWeek->CldrD4) : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Over.pWeek->CldrD5) : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Over.pWeek->CldrD6) : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Over.pWeek->CldrD7) : 0x00000000);
			}
			else if (m_Over.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pPlnt->CldrDW) == 0x02) ? (LONG)m_Over.pPlnt->CldrD1 : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pPlnt->CldrDW) == 0x04) ? (LONG)m_Over.pPlnt->CldrD2 : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pPlnt->CldrDW) == 0x08) ? (LONG)m_Over.pPlnt->CldrD3 : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pPlnt->CldrDW) == 0x10) ? (LONG)m_Over.pPlnt->CldrD4 : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pPlnt->CldrDW) == 0x20) ? (LONG)m_Over.pPlnt->CldrD5 : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pPlnt->CldrDW) == 0x40) ? (LONG)m_Over.pPlnt->CldrD6 : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pPlnt->CldrDW) == 0x80) ? (LONG)m_Over.pPlnt->CldrD7 : 0x00000000);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][3] = (((0x02 & (BYTE)m_Over.pWeek->CldrDW) == 0x02) ? (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Over.pWeek->CldrD1) : 0x00000000);
				m_Cell[1][3] = (((0x04 & (BYTE)m_Over.pWeek->CldrDW) == 0x04) ? (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Over.pWeek->CldrD2) : 0x00000000);
				m_Cell[2][3] = (((0x08 & (BYTE)m_Over.pWeek->CldrDW) == 0x08) ? (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Over.pWeek->CldrD3) : 0x00000000);
				m_Cell[3][3] = (((0x10 & (BYTE)m_Over.pWeek->CldrDW) == 0x10) ? (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Over.pWeek->CldrD4) : 0x00000000);
				m_Cell[4][3] = (((0x20 & (BYTE)m_Over.pWeek->CldrDW) == 0x20) ? (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Over.pWeek->CldrD5) : 0x00000000);
				m_Cell[5][3] = (((0x40 & (BYTE)m_Over.pWeek->CldrDW) == 0x40) ? (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Over.pWeek->CldrD6) : 0x00000000);
				m_Cell[6][3] = (((0x80 & (BYTE)m_Over.pWeek->CldrDW) == 0x80) ? (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Over.pWeek->CldrD7) : 0x00000000);
			}

			// ITEM => EDIT
			if (m_Over.pMach->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pMach->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pMach->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pMach->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pMach->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pMach->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pMach->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pMach->CldrD7 & (LONG)m_Cell[6][3]);

				::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_DELE, (LPARAM)MAKELONG(true, 0));
			}
			else if (m_Base.pMach->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pMach->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pMach->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pMach->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pMach->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pMach->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pMach->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pMach->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Over.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pOper->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pOper->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pOper->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pOper->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pOper->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pOper->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pOper->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pOper->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pOper->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pOper->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pOper->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pOper->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pOper->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pOper->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pOper->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Over.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pDept->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pDept->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pDept->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pDept->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pDept->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pDept->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pDept->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pDept->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Over.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][1] = m_Cell[0][0] = (LONG)(m_Over.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][1] = m_Cell[1][0] = (LONG)(m_Over.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][1] = m_Cell[2][0] = (LONG)(m_Over.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][1] = m_Cell[3][0] = (LONG)(m_Over.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][1] = m_Cell[4][0] = (LONG)(m_Over.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][1] = m_Cell[5][0] = (LONG)(m_Over.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][1] = m_Cell[6][0] = (LONG)(m_Over.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}
			else if (m_Base.pPlnt->CldrDW != SqlNull)
			{
				m_Cell[0][2] = m_Cell[0][0] = (LONG)(m_Base.pPlnt->CldrD1 & (LONG)m_Cell[0][3]);
				m_Cell[1][2] = m_Cell[1][0] = (LONG)(m_Base.pPlnt->CldrD2 & (LONG)m_Cell[1][3]);
				m_Cell[2][2] = m_Cell[2][0] = (LONG)(m_Base.pPlnt->CldrD3 & (LONG)m_Cell[2][3]);
				m_Cell[3][2] = m_Cell[3][0] = (LONG)(m_Base.pPlnt->CldrD4 & (LONG)m_Cell[3][3]);
				m_Cell[4][2] = m_Cell[4][0] = (LONG)(m_Base.pPlnt->CldrD5 & (LONG)m_Cell[4][3]);
				m_Cell[5][2] = m_Cell[5][0] = (LONG)(m_Base.pPlnt->CldrD6 & (LONG)m_Cell[5][3]);
				m_Cell[6][2] = m_Cell[6][0] = (LONG)(m_Base.pPlnt->CldrD7 & (LONG)m_Cell[6][3]);
			}

			break;
		}

		DumpCldr();

		RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
		RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
		RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

		InvalidateRect(&rcXX, 0);
	}

	HRESULT CPSCldrListCtrl::Init(LPCLDR pCldr, LPHORZWEEK pWeek, HWND hTBr)
	{
		if (m_Base.pCldr)
			return (S_OK);

		m_hTBr = hTBr;

		m_Base.pCldr = pCldr;
		m_Base.pPlnt = &pCldr->Plnt;
		m_Over.pPlnt = &pWeek->Plnt;
		m_Over.pWeek = pWeek;

		SetExtendedStyle(GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
		
		InsertColumn(0, _T("Day"), LVCFMT_LEFT, 38, -1);
		InsertColumn(1, _T(""), LVCFMT_CENTER, 20, 1);
		InsertColumn(2, _T(""), LVCFMT_CENTER, 20, 2);
		InsertColumn(3, _T(""), LVCFMT_CENTER, 20, 3);
		InsertColumn(4, _T(""), LVCFMT_CENTER, 20, 4);
		InsertColumn(5, _T(""), LVCFMT_CENTER, 20, 5);
		InsertColumn(6, _T(""), LVCFMT_CENTER, 20, 6);
		InsertColumn(7, _T(""), LVCFMT_CENTER, 20, 7);
		InsertColumn(8, _T(""), LVCFMT_CENTER, 20, 8);
		InsertColumn(9, _T(""), LVCFMT_CENTER, 20, 9);
		InsertColumn(10, _T(""), LVCFMT_CENTER, 20, 10);
		InsertColumn(11, _T(""), LVCFMT_CENTER, 20, 11);
		InsertColumn(12, _T(""), LVCFMT_CENTER, 20, 12);
		InsertColumn(13, _T(""), LVCFMT_CENTER, 20, 13);
		InsertColumn(14, _T(""), LVCFMT_CENTER, 20, 14);
		InsertColumn(15, _T(""), LVCFMT_CENTER, 20, 15);
		InsertColumn(16, _T(""), LVCFMT_CENTER, 20, 16);
		InsertColumn(17, _T(""), LVCFMT_CENTER, 20, 17);
		InsertColumn(18, _T(""), LVCFMT_CENTER, 20, 18);
		InsertColumn(19, _T(""), LVCFMT_CENTER, 20, 19);
		InsertColumn(20, _T(""), LVCFMT_CENTER, 20, 20);
		InsertColumn(21, _T(""), LVCFMT_CENTER, 20, 21);
		InsertColumn(22, _T(""), LVCFMT_CENTER, 20, 22);
		InsertColumn(23, _T(""), LVCFMT_CENTER, 20, 23);
		InsertColumn(24, _T(""), LVCFMT_CENTER, 20, 24);

		InsertItem(0, _T("Sun"));
		InsertItem(1, _T("Mon"));
		InsertItem(2, _T("Tue"));
		InsertItem(3, _T("Wed"));
		InsertItem(4, _T("Thu"));
		InsertItem(5, _T("Fri"));
		InsertItem(6, _T("Sat"));

		return (S_OK);
	}

	BEGIN_MESSAGE_MAP(CPSCldrListCtrl, CListCtrl)
		ON_WM_MOUSEMOVE()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CPSCldrListCtrl::OnNMCustomDraw)
	END_MESSAGE_MAP()

	void CPSCldrListCtrl::OnMouseMove(UINT nFlags, CPoint point)
	{
		if ((m_Show == CS_EDIT) && (GetCapture() == this))
		{
			LVHITTESTINFO	hti;	memset(&hti, 0, sizeof(LVHITTESTINFO));

			hti.pt = point;

			if (SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hti) > -1)
			{
				if (hti.iSubItem > 0)
				{
					if (m_Fill == CF_AREA)
					{
						// AREA:MD:NE
						if ((hti.iItem < m_MDwn[0][0]) && (hti.iSubItem > m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = hti.iSubItem;
						}
						// AREA:MD:N
						else if ((hti.iItem < m_MDwn[0][0]) && (hti.iSubItem == m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// AREA:MD:NW
						else if ((hti.iItem < m_MDwn[0][0]) && (hti.iSubItem < m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// AREA:MD:W
						else if ((hti.iItem == m_MDwn[0][0]) && (hti.iSubItem < m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// AREA:MD:SW
						else if ((hti.iItem > m_MDwn[0][0]) && (hti.iSubItem < m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// AREA:MD:S
						else if ((hti.iItem > m_MDwn[0][0]) && (hti.iSubItem == m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// AREA:MD:SE
						else if ((hti.iItem > m_MDwn[0][0]) && (hti.iSubItem > m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = hti.iSubItem;
						}
						// AREA:MD:E
						else if ((hti.iItem == m_MDwn[0][0]) && (hti.iSubItem > m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = hti.iSubItem;
						}
						// AREA:MD
						else
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
					}
					else
					{
						// LINE:MD:NE
						if ((hti.iItem < m_MDwn[0][0]) && (hti.iSubItem > m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// LINE:MD:N
						else if ((hti.iItem < m_MDwn[0][0]) && (hti.iSubItem == m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// LINE:MD:NW
						else if ((hti.iItem < m_MDwn[0][0]) && (hti.iSubItem < m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// LINE:MD:W
						else if ((hti.iItem == m_MDwn[0][0]) && (hti.iSubItem < m_MDwn[0][1]))
						{
							m_MSel[0][0] = hti.iItem;
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// LINE:MD:SW
						else if ((hti.iItem > m_MDwn[0][0]) && (hti.iSubItem < m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = hti.iSubItem;
						}
						// LINE:MD:S
						else if ((hti.iItem > m_MDwn[0][0]) && (hti.iSubItem == m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = hti.iSubItem;
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = m_MDwn[0][1];
						}
						// LINE:MD:SE
						else if ((hti.iItem > m_MDwn[0][0]) && (hti.iSubItem > m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = hti.iSubItem;
						}
						// LINE:MD:E
						else if ((hti.iItem == m_MDwn[0][0]) && (hti.iSubItem > m_MDwn[0][1]))
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = hti.iItem;
							m_MSel[1][1] = hti.iSubItem;
						}
						// LINE:MD
						else
						{
							m_MSel[0][0] = m_MDwn[0][0];
							m_MSel[0][1] = m_MDwn[0][1];
							m_MSel[1][0] = m_MDwn[0][0];
							m_MSel[1][1] = m_MDwn[0][1];
						}
					}

					RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
					RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
					RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

					InvalidateRect(&rcXX, 0);

//					AfxTrace(_T("HTm FLG:%08x ITM:%04d SUB:%04d\n"), hti.flags, hti.iItem, hti.iSubItem);

					return;
				}
			}
		}

		CListCtrl::OnMouseMove(nFlags, point);
	}

	void CPSCldrListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (m_Show == CS_EDIT)
		{
			LVHITTESTINFO	hti;	memset(&hti, 0, sizeof(LVHITTESTINFO));

			hti.pt = point;

			if (SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hti) > -1)
			{
				if (hti.iSubItem > 0)
				{
					m_MDwn[0][0] = m_MSel[0][0] = m_MSel[1][0] = hti.iItem;
					m_MDwn[0][1] = m_MSel[0][1] = m_MSel[1][1] = hti.iSubItem;

					RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
					RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
					RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

					InvalidateRect(&rcXX, 0);
					
					SetCapture();

//					AfxTrace(_T("HTd FLG:%08x ITM:%04d SUB:%04d\n"), hti.flags, hti.iItem, hti.iSubItem);

					return;
				}
			}
		}

		CListCtrl::OnLButtonDown(nFlags, point);
	}

	void CPSCldrListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
	{
		if ((m_Show == CS_EDIT) && (GetCapture() == this))
		{
			LVHITTESTINFO	hti;	memset(&hti, 0, sizeof(LVHITTESTINFO));

			hti.pt = point;

			if (SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)&hti) > -1)
			{
				if (hti.iSubItem > 0)
				{
					int		ixDOW	= 0;
					int		ixHOD	= 0;
					LONG	bmHOD	= 0x00000000;

					// Edit based on m_Fill
					if (m_Fill == CF_AREA)
					{
						for (ixDOW = m_MSel[0][0]; ixDOW <= m_MSel[1][0]; ixDOW++)
						{
							for (ixHOD = (m_MSel[0][1] - 1); ixHOD <= (m_MSel[1][1] - 1); ixHOD++)
							{
								bmHOD = (LONG)pow((double)2, ixHOD);

								switch (m_Draw)
								{
								case CD_BIT0:
									m_Cell[ixDOW][0] = (m_Cell[ixDOW][0] & (~bmHOD));
									break;
								case CD_BIT1:
									m_Cell[ixDOW][0] = (((m_Cell[ixDOW][3] & bmHOD) == bmHOD) ? (m_Cell[ixDOW][0] | bmHOD) : (m_Cell[ixDOW][0] & (~bmHOD)));
									break;
								}
							}
						}
					}

					else if (m_Fill == CF_LINE)
					{
						if (m_MSel[0][0] == m_MSel[1][0])
						{
							for (ixDOW = m_MSel[0][0], ixHOD = (m_MSel[0][1] - 1); ixHOD <= (m_MSel[1][1] - 1); ixHOD++)
							{
								bmHOD = (LONG)pow((double)2, ixHOD);

								switch (m_Draw)
								{
								case CD_BIT0:
									m_Cell[ixDOW][0] = (m_Cell[ixDOW][0] & (~bmHOD));
									break;
								case CD_BIT1:
									m_Cell[ixDOW][0] = (((m_Cell[ixDOW][3] & bmHOD) == bmHOD) ? (m_Cell[ixDOW][0] | bmHOD) : (m_Cell[ixDOW][0] & (~bmHOD)));
									break;
								}
							}
						}
						else
						{
							for (ixDOW = m_MSel[0][0], ixHOD = (m_MSel[0][1] - 1); ixHOD <= 24; ixHOD++)
							{
								bmHOD = (LONG)pow((double)2, ixHOD);

								switch (m_Draw)
								{
								case CD_BIT0:
									m_Cell[ixDOW][0] = (m_Cell[ixDOW][0] & (~bmHOD));
									break;
								case CD_BIT1:
									m_Cell[ixDOW][0] = (((m_Cell[ixDOW][3] & bmHOD) == bmHOD) ? (m_Cell[ixDOW][0] | bmHOD) : (m_Cell[ixDOW][0] & (~bmHOD)));
									break;
								}
							}

							for (ixDOW = (m_MSel[0][0] + 1); ixDOW <= (m_MSel[1][0] - 1); ixDOW++)
							{
								for (ixHOD = 0; ixHOD <= 23; ixHOD++)
								{
									bmHOD = (LONG)pow((double)2, ixHOD);

									switch (m_Draw)
									{
									case CD_BIT0:
										m_Cell[ixDOW][0] = (m_Cell[ixDOW][0] & (~bmHOD));
										break;
									case CD_BIT1:
										m_Cell[ixDOW][0] = (((m_Cell[ixDOW][3] & bmHOD) == bmHOD) ? (m_Cell[ixDOW][0] | bmHOD) : (m_Cell[ixDOW][0] & (~bmHOD)));
										break;
									}
								}
							}

							for (ixDOW = m_MSel[1][0], ixHOD = 0; ixHOD <= (m_MSel[1][1] - 1); ixHOD++)
							{
								bmHOD = (LONG)pow((double)2, ixHOD);

								switch (m_Draw)
								{
								case CD_BIT0:
									m_Cell[ixDOW][0] = (m_Cell[ixDOW][0] & (~bmHOD));
									break;
								case CD_BIT1:
									m_Cell[ixDOW][0] = (((m_Cell[ixDOW][3] & bmHOD) == bmHOD) ? (m_Cell[ixDOW][0] | bmHOD) : (m_Cell[ixDOW][0] & (~bmHOD)));
									break;
								}
							}
						}
					}

					m_MDwn[0][0] = m_MSel[0][0] = m_MSel[1][0] = -1;
					m_MDwn[0][1] = m_MSel[0][1] = m_MSel[1][1] = -1;

					RECT	rcTL = {LVIR_BOUNDS, 1, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)0, (LPARAM)&rcTL);
					RECT	rcBR = {LVIR_BOUNDS, 24, 0, 0};	SendMessage(LVM_GETSUBITEMRECT, (WPARAM)6, (LPARAM)&rcBR);
					RECT	rcXX = {rcTL.left, rcTL.top, rcBR.right, rcBR.bottom};

					InvalidateRect(&rcXX, 0);

					ReleaseCapture();

//					AfxTrace(_T("HTu FLG:%08x ITM:%04d SUB:%04d\n"), hti.flags, hti.iItem, hti.iSubItem);

					DumpCldr();

					::SendMessage(m_hTBr, TB_ENABLEBUTTON, (WPARAM)IDC_TBB_SAVE, (LPARAM)MAKELONG(NeedSave(), 0));
				}
			}
		}

		CListCtrl::OnLButtonUp(nFlags, point);
	}


	void CPSCldrListCtrl::OnNMCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMCUSTOMDRAW		pNMCD		= reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		LPNMLVCUSTOMDRAW	pNMLVCD		= NULL;

		if (pNMHDR->hwndFrom == m_hWnd)
		{
			switch (pNMHDR->code)
			{
			case NM_CUSTOMDRAW:

				pNMLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

				if (pNMCD->dwDrawStage == CDDS_PREPAINT)
				{
					*pResult = CDRF_NOTIFYITEMDRAW;
					return;
				}

				else if (pNMCD->dwDrawStage == CDDS_ITEMPREPAINT)
				{
					::SelectObject(pNMCD->hdc, (HBRUSH)m_brSW);
					*pResult = CDRF_NOTIFYSUBITEMDRAW;
					return;
				}

				else if (pNMCD->dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
				{
					if (pNMLVCD->iSubItem > 0)
					{
						*pResult = CDRF_NOTIFYPOSTPAINT;
						return;
					}
				}

				else if (pNMCD->dwDrawStage == (CDDS_ITEMPOSTPAINT | CDDS_SUBITEM))
				{
					int			ixDOW	= (int)pNMCD->dwItemSpec;
					LONG		bmHOD	= (LONG)pow(2.0, (pNMLVCD->iSubItem - 1));
					RECT		rcCel	= {LVIR_BOUNDS, pNMLVCD->iSubItem, 0, 0};
					COLORREF	bkCel	= RGB(0, 0, 0);
					HBRUSH		hbCel	= NULL;

					SendMessage(LVM_GETSUBITEMRECT, (WPARAM)pNMCD->dwItemSpec, (LPARAM)&rcCel);

//					AfxTrace(_T("i:%d si:%d rc:%d,%d,%d,%d\n"), pNMCD->dwItemSpec, pNMLVCD->iSubItem, rcCel.top, rcCel.left, rcCel.bottom, rcCel.right);

					if ((m_Cell[ixDOW][3] & bmHOD) == 0x00000000)
					{
						bkCel = m_rgbG;
						hbCel = (HBRUSH)m_brHG;
					}
					else if ((m_Cell[ixDOW][1] & bmHOD) == bmHOD)
					{
						bkCel = m_rgbO;
//						hbCel = (HBRUSH)m_brHO;
						hbCel = (HBRUSH)(((m_Cell[ixDOW][0] & bmHOD) == bmHOD) ? m_brHO : m_brHW);
					}
					else if ((m_Cell[ixDOW][2] & bmHOD) == bmHOD)
					{
						bkCel = m_rgbB;
//						hbCel = (HBRUSH)m_brHB;
						hbCel = (HBRUSH)(((m_Cell[ixDOW][0] & bmHOD) == bmHOD) ? m_brHB : m_brHW);
					}
					else
					{
						bkCel = m_rgbW;
//						hbCel = (HBRUSH)m_brHW;
						hbCel = (HBRUSH)(((m_Cell[ixDOW][0] & bmHOD) == bmHOD) ? ((m_Type == CT_BASE) ? m_brHB : m_brHO) : m_brHW);
					}

					// Show::Edit
					if (m_Show == CS_EDIT)
					{
						// Fill::Area
						if (m_Fill == CF_AREA)
						{
							if (((int)pNMCD->dwItemSpec >= m_MSel[0][0]) && ((int)pNMCD->dwItemSpec <= m_MSel[1][0]))
							{
								if ((pNMLVCD->iSubItem >= m_MSel[0][1]) && (pNMLVCD->iSubItem <= m_MSel[1][1]))
								{
									hbCel = (HBRUSH)((m_Draw == CD_BIT0) ? m_brHW : ((m_Type == CT_BASE) ? m_brHB : m_brHO));
								}
							}
						}
						
						// Fill::Line
						else if (m_Fill == CF_LINE)
						{
							if (
								((m_MSel[0][0] == m_MSel[1][0]) && ((int)pNMCD->dwItemSpec == m_MSel[0][0]) && ((int)pNMLVCD->iSubItem >= m_MSel[0][1]) && ((int)pNMLVCD->iSubItem <= m_MSel[1][1]))
							||  ((m_MSel[0][0] != m_MSel[1][0]) && ((int)pNMCD->dwItemSpec == m_MSel[0][0]) && ((int)pNMLVCD->iSubItem >= m_MSel[0][1]) && ((int)pNMLVCD->iSubItem <= 24))
							||  ((m_MSel[0][0] != m_MSel[1][0]) && ((int)pNMCD->dwItemSpec == m_MSel[1][0]) && ((int)pNMLVCD->iSubItem >= 1) && ((int)pNMLVCD->iSubItem <= m_MSel[1][1]))
							||  (((int)pNMCD->dwItemSpec > m_MSel[0][0]) && ((int)pNMCD->dwItemSpec < m_MSel[1][0]))
							)
							{
								hbCel = (HBRUSH)((m_Draw == CD_BIT0) ? m_brHW : ((m_Type == CT_BASE) ? m_brHB : m_brHO));
							}
						}
					}

					::SetBkMode(pNMCD->hdc, OPAQUE);
					::SetBkColor(pNMCD->hdc, bkCel);
					::FillRect(pNMCD->hdc, &rcCel, hbCel);

					return;
				}
				break;

			}
		}

		*pResult = (LRESULT)CDRF_DODEFAULT;
	}


	BOOL CPSCldrListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{
		LPNMHDR			pNMHDR	= (LPNMHDR)lParam;
		LPNMCUSTOMDRAW	pNMCD	= NULL;
		TCHAR			sz[3];	memset(sz, 0, sizeof(sz));

		if (pNMHDR->hwndFrom == GetHeaderCtrl()->m_hWnd)
		{
			switch (pNMHDR->code)
			{
			case NM_CUSTOMDRAW:

				pNMCD = (LPNMCUSTOMDRAW)lParam;

				if (pNMCD->dwDrawStage == CDDS_PREPAINT)
				{
					*pResult = CDRF_NOTIFYITEMDRAW;
					return (TRUE);
				}
				else if (pNMCD->dwDrawStage == CDDS_ITEMPREPAINT)
				{
					if (pNMCD->dwItemSpec == 0)
					{
						*pResult = CDRF_DODEFAULT;
						return (TRUE);
					}
					else
					{
						::SelectObject(pNMCD->hdc, m_fntH.m_hObject);
						*pResult = (CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT);
						return (TRUE);
					}
				}
				else if (pNMCD->dwDrawStage == CDDS_ITEMPOSTPAINT)
				{
					::SetBkColor(pNMCD->hdc, ::GetDCBrushColor(pNMCD->hdc));
					_stprintf_s(sz, _countof(sz), _T("%02d"), ((((pNMCD->dwItemSpec % 12)) == 0) ? 11 : (((pNMCD->dwItemSpec % 12) - 1) == 0) ? 12 : (pNMCD->dwItemSpec % 12) - 1) );
					::TextOut(pNMCD->hdc, (pNMCD->rc.left + 4), 3, sz, 2);
					_stprintf_s(sz, _countof(sz), _T("%s"), ((pNMCD->dwItemSpec < 13) ? _T("AM") : _T("PM")));
					::TextOut(pNMCD->hdc, (pNMCD->rc.left + 3), 9, sz, 2);
				}
				break;
			}
		}

		return CListCtrl::OnNotify(wParam, lParam, pResult);
	}


	//
	//	CPSDateTimeCtrl
	//
	IMPLEMENT_DYNAMIC(CPSDateTimeCtrl, CDateTimeCtrl)

	CPSDateTimeCtrl::CPSDateTimeCtrl()
	{
		f = RGB(0, 192, 0);
		b = RGB(255, 0, 0);
	}

	CPSDateTimeCtrl::~CPSDateTimeCtrl()
	{
	}

	void CPSDateTimeCtrl::DoTest()
	{
		//
		// Test to use bitmap, bitblt to change CDateTimeCtrl Background color
		//
		CRect	rc;			GetClientRect(&rc);
		CDC*	pcDC		= GetDC();
		CDC		imDC;		imDC.CreateCompatibleDC(pcDC);
		CBitmap	imBM;		imBM.CreateCompatibleBitmap(pcDC, rc.Width(), rc.Height());

		imDC.SelectObject(&imBM);
		imDC.BitBlt(0, 0, rc.Width(), rc.Height(), pcDC, 0, 0, SRCCOPY);

		int		cPix		= ((rc.Width() * 4) * rc.Height());
		LPBYTE	pPix		= new BYTE[cPix];

		imBM.GetBitmapBits((DWORD)cPix, (LPVOID)pPix);

		// Trace Quads for arbitrary line
		{
			int		r = rc.Height() / 2;
			LPDWORD	p = (LPDWORD)&pPix[(r * (rc.Width() * 4))];

			for (int c = 0; c < rc.Width(); c++)
			{
				AfxTrace(_T("\n%03d: [%08X]"), c, p[c]);

				if (p[c] == 0xffffffff)
				{
					p[c] = 0x0000ffff;
				}
			}
			AfxTrace(_T("\n"));
		}

		imBM.SetBitmapBits((DWORD)cPix, (LPVOID)pPix);
		pcDC->SelectObject(&imBM);
		pcDC->BitBlt(0, 0, rc.Width(), rc.Height(), &imDC, 0, 0, SRCCOPY);
		imDC.SelectObject((CBitmap*)NULL);

		delete [] pPix;
		pPix = NULL;
		cPix = 0;
	}

	BEGIN_MESSAGE_MAP(AFXCNTRLLIB::CPSDateTimeCtrl, CDateTimeCtrl)
		ON_WM_PAINT()
		ON_WM_ERASEBKGND()
	END_MESSAGE_MAP()

	void CPSDateTimeCtrl::OnPaint()
	{
		CDateTimeCtrl::OnPaint();

		return;

		DoTest();
	}
	BOOL CPSDateTimeCtrl::OnEraseBkgnd(CDC* pDC)
	{
		static CBrush	br(RGB(192, 64, 64));
		static CRect	rc;

		GetClientRect(&rc);

		br.UnrealizeObject();
		// pDC->SetBoundsRect(&rc, DCB_RESET | DCB_ACCUMULATE);
		pDC->SelectObject((CBrush*)&br);
		pDC->FillRect(&rc, &br);

		return (TRUE);

		CDateTimeCtrl::OnEraseBkgnd(pDC);
	}

	//
	// CPSHubListCtrl
	//
	CPSHubListCtrl::CFilterFlags::CFilterFlags(AFXCNTRLLIB::CPSHubListCtrl &o) : _o(o)
	{
	}

	CPSHubListCtrl::CFilterFlags::operator int()
	{
		return (_o.Items.iFilt);
	}

	CPSHubListCtrl::CUpDownEnabled::CUpDownEnabled(AFXCNTRLLIB::CPSHubListCtrl &o) : _o(o)
	{
	}

	CPSHubListCtrl::CUpDownEnabled::operator BOOL()
	{
		return (_o.Items.bUpDn);
	}


	CPSHubListCtrl::CFocusedItem::CFocusedItem(AFXCNTRLLIB::CPSHubListCtrl& o) : _o(o)
	, IsHead((CPSHubListCtrl::CFocusedItem&)*this), IsTail((CPSHubListCtrl::CFocusedItem&)*this)
	{
	}

	CPSHubListCtrl::CFocusedItem::CIsHead::CIsHead(AFXCNTRLLIB::CPSHubListCtrl::CFocusedItem& o) : _o(o)
	{
	}

	CPSHubListCtrl::CFocusedItem::operator const int() const
	{
		return (_o.Stats.iFcsd);
	}

	CPSHubListCtrl::CFocusedItem::CIsHead::operator const BOOL() const
	{
		if (_o._o.GetItemCount() == 0)
		{
			return (TRUE);
		}
		else if (_o._o.Stats.cSeld == 0)
		{
			return (FALSE);
		}
		else if (_o._o.Items.iFilt == (FF_SELD | FF_CHKD))
		{
			for (int i = (_o._o.Stats.iFcsd - 1); i >= 0; i--)
			{
				if (_o._o.GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED)
				{
					return (FALSE);
				}
			}
			return (TRUE);
		}
		else if (_o._o.Items.iFilt == FF_SELD)
		{
			for (int i = (_o._o.Stats.iFcsd - 1); i >= 0; i--)
			{
				if (_o._o.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
				{
					return (FALSE);
				}
			}
			return (TRUE);
		}
		else
		{
			if (_o._o.Stats.iFcsd != 0)
			{
				return (FALSE);
			}
			return (TRUE);
		}
	}

	CPSHubListCtrl::CFocusedItem::CIsTail::CIsTail(AFXCNTRLLIB::CPSHubListCtrl::CFocusedItem& o) : _o(o)
	{
	}

	CPSHubListCtrl::CFocusedItem::CIsTail::operator const BOOL() const
	{
		if (_o._o.GetItemCount() == 0)
		{
			return (TRUE);
		}
		else if (_o._o.Stats.cSeld == 0)
		{
			return (FALSE);
		}
		else if (_o._o.Items.iFilt == (FF_SELD | FF_CHKD))
		{
			for (int i = (_o._o.Stats.iFcsd + 1), c = _o._o.GetItemCount(); i < c; i++)
			{
				if (_o._o.GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED)
				{
					return (FALSE);
				}
			}
			return (TRUE);
		}
		else if (_o._o.Items.iFilt == FF_SELD)
		{
			for (int i = (_o._o.Stats.iFcsd + 1), c = _o._o.GetItemCount(); i < c; i++)
			{
				if (_o._o.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
				{
					return (FALSE);
				}
			}
			return (TRUE);
		}
		else
		{
			if (_o._o.Stats.iFcsd != (_o._o.GetItemCount() - 1))
			{
				return (FALSE);
			}
			return (TRUE);
		}
	}

	IMPLEMENT_DYNAMIC(CPSHubListCtrl, CListCtrl)

	CPSHubListCtrl::CPSHubListCtrl() 
	: CListCtrl()
	, FilterFlags((CPSHubListCtrl&)*this), UpDownEnabled((CPSHubListCtrl&)*this), FocusedItem((CPSHubListCtrl&)*this)
	{
		Stats.cChkd = 0;
		Stats.cSeld = 0;
		Stats.iFcsd = -1;
		Items.iFilt = FI_NONE;
		Items.iSItm = -1;
		Items.bUpDn = TRUE;
	}

	CPSHubListCtrl::~CPSHubListCtrl()
	{
	}

	const int CPSHubListCtrl::FocusItem(AFXCNTRLLIB::CPSHubListCtrl::FOCUSITEM fi)
	{
		if (Items.bUpDn == TRUE)
		{
			//
			// Routine must try to de-select current select, but dialog can accept/reject
			switch (fi)
			{
			case FI_NEXT:
				for (int h = Stats.iFcsd, i = (Stats.iFcsd + 1), c = GetItemCount(); i < c; i++)
				{
					switch (Items.iFilt)
					{
					case (FF_SELD | FF_CHKD):
						if ((GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED) && (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED))
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_CHKD):
						if (GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED)
						{
							SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_SELD):
						if (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					default:
						SetItemState(h, 0, LVIS_SELECTED);
						SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
						return (i);
					}
				}
				// Fall through to HEAD intended
			case FI_HEAD:
				for (int h = Stats.iFcsd, i = 0, c = GetItemCount(); i < c; i++)
				{
					switch (Items.iFilt)
					{
					case (FF_SELD | FF_CHKD):
						if ((GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED) && (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED))
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_CHKD):
						if (GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED)
						{
							SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_SELD):
						if (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					default:
						SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
						return (i);
					}
				}
				break;
			case FI_PREV:
				for (int h = Stats.iFcsd, i = (Stats.iFcsd - 1); i > -1; i--)
				{
					switch (Items.iFilt)
					{
					case (FF_SELD | FF_CHKD):
						if ((GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED) && (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED))
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_CHKD):
						if (GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED)
						{
							SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_SELD):
						if (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					default:
						SetItemState(h, 0, LVIS_SELECTED);
						SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
						return (i);
					}
				}
				// Fall through to TAIL intended
			case FI_TAIL:
				for (int h = Stats.iFcsd, i = (GetItemCount() - 1); i > -1; i--)
				{
					switch (Items.iFilt)
					{
					case (FF_SELD | FF_CHKD):
						if ((GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED) && (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED))
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_CHKD):
						if (GetItemState(i, LVIS_STATEIMAGEMASK) == LVIS_CHECKED)
						{
							SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					case (FF_SELD):
						if (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
						{
							SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
							return (i);
						}
						break;
					default:
						SetItemState(h, 0, LVIS_SELECTED);
						SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
						return (i);
					}
				}
				break;
			}
		}

		return (-1);
	}

	BOOL CPSHubListCtrl::UpDownEnable(BOOL tf)
	{
		BOOL ud = Items.bUpDn;

		Items.bUpDn = tf;

		return (ud);
	}

	
	BOOL CPSHubListCtrl::AttachRimCtrl(HWND hwRim)
	{
		// Ensure non-null
		if (hwRim == NULL)
			return (FALSE);
		// Ensure valid window
		if (::IsWindow(hwRim) == FALSE)
			return (FALSE);

		int				id	= CWnd::FromHandle(hwRim)->GetDlgCtrlID();
		CRuntimeClass*	pr	= NULL;

		// - Can we get the runtime class?
		if ((pr = GetParent()->GetDlgItem(id)->GetRuntimeClass()) == NULL)
			return (FALSE);
		
		// - Did we get message from a rim control?
		if (_strcmpi(pr->m_lpszClassName, "CPSRimEdit") == 0)
		{
			CPSRimEdit*			pRim = dynamic_cast<CPSRimEdit*>(GetParent()->GetDlgItem(id));

			if ((ChdRims.Lookup(hwRim) == NULL) && (pRim->hwHub == NULL))
			{
				ChdRims.SetAt(hwRim, id);
				pRim->hwHub = m_hWnd;
				pRim->idHub = GetDlgCtrlID();

				return (TRUE);
			}
		}
		else if (_strcmpi(pr->m_lpszClassName, "CPSRimButton") == 0)
		{
			CPSRimButton*		pRim = dynamic_cast<CPSRimButton*>(GetParent()->GetDlgItem(id));

			if ((ChdRims.Lookup(hwRim) == NULL) && (pRim->hwHub == NULL))
			{
				ChdRims.SetAt(hwRim, id);
				pRim->hwHub = m_hWnd;
				pRim->idHub = GetDlgCtrlID();

				return (TRUE);
			}
		}

		return (FALSE);
	}

	BOOL CPSHubListCtrl::DetachRimCtrl(HWND hwRim)
	{
		// Ensure non-null
		if (hwRim == NULL)
			return (FALSE);
		// Ensure valid window
		if (::IsWindow(hwRim) == FALSE)
			return (FALSE);

		int				id	= CWnd::FromHandle(hwRim)->GetDlgCtrlID();
		CRuntimeClass*	pr	= NULL;

		// - Can we get the runtime class?
		if ((pr = GetParent()->GetDlgItem(id)->GetRuntimeClass()) == NULL)
			return (FALSE);
		
		// - Did we get message from a rim control?
		if (_strcmpi(pr->m_lpszClassName, "CPSRimEdit") == 0)
		{
			CPSRimEdit*			pRim = dynamic_cast<CPSRimEdit*>(GetParent()->GetDlgItem(id));

			if ((ChdRims.Lookup(hwRim) != NULL) && (pRim->hwHub != NULL))
			{
				ChdRims.RemoveKey(hwRim);
				pRim->hwHub = NULL;
				pRim->idHub = -1;

				return (TRUE);
			}
		}
		else if (_strcmpi(pr->m_lpszClassName, "CPSRimButton") == 0)
		{
			CPSRimButton*		pRim = dynamic_cast<CPSRimButton*>(GetParent()->GetDlgItem(id));

			if ((ChdRims.Lookup(hwRim) != NULL) && (pRim->hwHub != NULL))
			{
				ChdRims.RemoveKey(hwRim);
				pRim->hwHub = NULL;
				pRim->idHub = -1;

				return (TRUE);
			}
		}

		return (FALSE);
	}

	BOOL CPSHubListCtrl::AttachHubCtrl(HWND hwHub)
	{
		// Ensure non-null
		if (hwHub == NULL)
			return (FALSE);
		// Ensure valid window
		if (::IsWindow(hwHub) == FALSE)
			return (FALSE);
		// Ensure other attachment
		if (hwHub == m_hWnd)
			return (FALSE);

		int				id	= CWnd::FromHandle(hwHub)->GetDlgCtrlID();
		CRuntimeClass*	pr	= NULL;

		// - Can we get the runtime class?
		if ((pr = GetParent()->GetDlgItem(id)->GetRuntimeClass()) == NULL)
			return (FALSE);
		
		// - Did we get message from a hub control?
		if ((_strcmpi(pr->m_lpszClassName, "CPSHubListCtrl") == 0))
		{
			CAtlMap<HWND, int>&			mP	= ((CPSHubListCtrl*)CWnd::FromHandle(hwHub))->PrntHub;
			size_t						cP	= mP.GetCount();
			CAtlMap<HWND, int>::CPair*	pP	= ((cP == 1) ? mP.Lookup(hwHub) : NULL);

			if ((ChdHubs.Lookup(hwHub) == NULL) && (cP == 0))
			{
				ChdHubs.SetAt(hwHub, id);
				mP.SetAt(m_hWnd, id);

				return (TRUE);
			}
			else if ((ChdHubs.Lookup(hwHub) != NULL) && (cP == 1) && (pP != NULL))
			{
				return (TRUE);
			}
		}

		return (FALSE);
	}

	BOOL CPSHubListCtrl::DetachHubCtrl(HWND hwHub)
	{
		if (hwHub == NULL)
			return (FALSE);

		CAtlMap<HWND, int>&			mP	= ((CPSHubListCtrl*)CWnd::FromHandle(hwHub))->PrntHub;
		size_t						cP	= mP.GetCount();
		CAtlMap<HWND, int>::CPair*	pP	= ((cP == 1) ? mP.Lookup(hwHub) : NULL);

		if ((ChdHubs.Lookup(hwHub) != NULL) && (cP == 1) && (pP != NULL))
		{
			ChdHubs.RemoveKey(hwHub);
			mP.RemoveKey(m_hWnd);
			
			return (TRUE);
		}

		return (FALSE);
	}

	void CPSHubListCtrl::ScanStat()
	{
		Stats.cChkd = 0;
		Stats.cSeld = 0;
		Stats.iFcsd = -1;

		for (int i = 0, c = GetItemCount(); i < c; i++)
		{
			WORD is = GetItemState(i, (LVIS_STATEIMAGEMASK | LVIS_SELECTED | LVIS_FOCUSED));

			Stats.cChkd += (((is & LVIS_CHECKED) == LVIS_CHECKED) ? 1 : 0);
			Stats.cSeld += (((is & LVIS_SELECTED) == LVIS_SELECTED) ? 1 : 0);
			Stats.iFcsd  = (((Stats.iFcsd == -1) && ((is & LVIS_FOCUSED) == LVIS_FOCUSED)) ? i : Stats.iFcsd);
		}

		//AfxTrace(_T("- [%3d] cChkd\n"), Stats.cChkd);
		//AfxTrace(_T("- [%3d] cSeld\n"), Stats.cSeld);
		//AfxTrace(_T("- [%3d] iFcsd\n"), Stats.iFcsd);
	}

	void CPSHubListCtrl::EnterRimLoop()
	{
		EnableWindow(0);

		ScanStat();

		Items.iFilt = FI_NONE;
		Items.iSItm = -1;

		// - Determine the item filter mode
		if (Stats.cSeld > 0)
		{
			Items.iFilt |= FF_SELD;

			if ((GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES)
			{
				Items.iFilt |= FF_CHKD;
			}
		}
		else
		{
			if ((GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES)
			{
				Items.iFilt |= FF_CHKD;
			}
		}

		if (PrntHub.GetCount() == 1)
		{
			HWND	hwMom = PrntHub.GetKeyAt(PrntHub.GetStartPosition());

			((CPSHubListCtrl*)CWnd::FromHandle(hwMom))->EnterRimLoop();
		}

		Items.bNRim = TRUE;
	}

	void CPSHubListCtrl::LeaveRimLoop()
	{
		if (PrntHub.GetCount() == 1)
		{
			HWND	hwMom = PrntHub.GetKeyAt(PrntHub.GetStartPosition());

			((CPSHubListCtrl*)CWnd::FromHandle(hwMom))->LeaveRimLoop();
		}

		if (Items.iFilt == FI_NONE)
		{
			for (int i = 0, c = GetItemCount(); i < c; i++)
			{
				if (GetItemState(i, LVIS_FOCUSED) == LVIS_FOCUSED)
				{
					SetItemState(i, 0, LVIS_FOCUSED);
				}
				if (GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
				{
					SetItemState(i, 0, LVIS_SELECTED);
				}
			}
		}

		Items.iFilt = FI_NONE;
		Items.iSItm = -1;

		EnableWindow(1);

		Items.bNRim = FALSE;
	}

	BEGIN_MESSAGE_MAP(AFXCNTRLLIB::CPSHubListCtrl, CListCtrl)
		ON_MESSAGE(WM_RIMCTRLSETFOCUS, &CPSHubListCtrl::OnRimCtrlSetFocus)
		ON_MESSAGE(WM_RIMCTRLKILLFOCUS, &CPSHubListCtrl::OnRimCtrlKillFocus)
		ON_MESSAGE(WM_RIMCTRLKEYS, &CPSHubListCtrl::OnRimCtrlKeys)
		ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CPSHubListCtrl::OnCustomDraw)
		ON_NOTIFY_REFLECT_EX(LVN_ITEMCHANGING, &CPSHubListCtrl::OnItemChanging)
		ON_NOTIFY_REFLECT_EX(LVN_ITEMCHANGED, &CPSHubListCtrl::OnItemChanged)
	END_MESSAGE_MAP()

	LRESULT CPSHubListCtrl::OnRimCtrlSetFocus(WPARAM wParam, LPARAM lParam)
	{
		HWND			hw		= (HWND)lParam;		// Rim Control passes its hWnd as wParam
		UINT			id		= ::GetDlgCtrlID(hw);

		//
		// Procedure to determine item filter and enter navigation mode
		// 

		//AfxTrace(_T("HUB::OnRimSetFocus(%5d)\n"), CWnd::FromHandle(hw)->GetDlgCtrlID());
		
		// - No need to re-evaluate, already in navigation mode
		if (IsWindowEnabled() == FALSE)
			return (-1);
		// - Did we get message from a valid window?
		if (::IsWindow(hw) == FALSE)
			return (-1);
		// - Did the Rim Control map to us?
		if (ChdRims.Lookup(hw) == NULL)
			return (-1);
		// - Purpose of LVS_EX_CHECKBOXES is to pick subset from an entire set
		//   - Are > 0 items checked?
		if (((GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES) && (Stats.cChkd == 0))
			return -1;
		
		EnterRimLoop();

		//AfxTrace(_T("ScanStat.2\n"));
		ScanStat();

		if (Stats.iFcsd == -1)
		{
			FocusItem(FI_HEAD);
		}

		return 0;
	}

	LRESULT CPSHubListCtrl::OnRimCtrlKillFocus(WPARAM wParam, LPARAM lParam)
	{
		HWND			hw[2]	= {(HWND)lParam, (HWND)NULL};		// Rim Control passes its hWnd as wParam
		UINT			id[2]	= {0, 0};
		CRuntimeClass*	pr[2]	= {NULL, NULL};

		//
		// Procedure to determine if the control losing focus is a rim control
		// and the control gaining focus is NOT a rim control
		// - Rim controls should map ON_CONTROL_REFLECT_EX(XX_SETFOCUS) passing FALSE to pass up to dialog
		// 

		// AfxTrace(_T("HUB::OnRimKillFocus(%5d)\n"), CWnd::FromHandle(hw[0])->GetDlgCtrlID());

		// - No need to re-evaluate, already out of navigation mode
		if (IsWindowEnabled() == TRUE)
			return -1;

		// Did we get a message from a valid window?
		if (::IsWindow(hw[0]) == FALSE)
			return -1;

		id[0] = ::GetDlgCtrlID(hw[0]);

		// - Can we get the runtime class?
		if ((pr[0] = GetParent()->GetDlgItem(id[0])->GetRuntimeClass()) == NULL)
			return -1;
		
		// - Did we get message from a rim control?
		if ((_strcmpi(pr[0]->m_lpszClassName, "CPSRimEdit") != 0)
		&&	(_strcmpi(pr[0]->m_lpszClassName, "CPSRimButton") != 0)
		&&	(_strcmpi(pr[0]->m_lpszClassName, "CPSRimListCtrl") != 0)
		&&	(_strcmpi(pr[0]->m_lpszClassName, "CPSRimDateTimeCtrl") != 0)
		&&	(_strcmpi(pr[0]->m_lpszClassName, "CPSRimComboBox") != 0)
		)
		{
			return -1;
		}

		// - Can we get the control gaining focus?
		CWnd* pWnd = GetParent();
		CWnd* pCtl = pWnd->GetFocus();

		if (pCtl == NULL)
			return (-1);
		if (::IsWindow(pCtl->m_hWnd) == FALSE)
			return (-1);

		if ((hw[1] = pCtl->m_hWnd) == NULL)
			return -1;
		if ((id[1] = ::GetDlgCtrlID(hw[1])) == 0)
			return -1;

		// - Can we get the runtime class?
		if ((pr[1] = GetParent()->GetDlgItem(id[1])->GetRuntimeClass()) == NULL)
			return -1;
		
		// - Did we get message from a non-rim control?
		if ((_strcmpi(pr[1]->m_lpszClassName, "CPSRimEdit") == 0)
		||	(_strcmpi(pr[1]->m_lpszClassName, "CPSRimButton") == 0)
		||	(_strcmpi(pr[1]->m_lpszClassName, "CPSRimListCtrl") == 0)
		||	(_strcmpi(pr[1]->m_lpszClassName, "CPSRimDateTimeCtrl") == 0)
		||	(_strcmpi(pr[1]->m_lpszClassName, "CPSRimComboBox") == 0)
		)
		{
			return -1;
		}

		Items.iFilt = FI_NONE;
		Items.iSItm = -1;

		LeaveRimLoop();

		return 0;
	}

	LRESULT CPSHubListCtrl::OnRimCtrlKeys(WPARAM wParam, LPARAM lParam)
	{
		LPNMRIMCTRL	pNM = (LPNMRIMCTRL)lParam;
		LRESULT		lRC = 0;

		switch (pNM->rim.code)
		{
		case (HK_CONTROL + HK_END):
			LeaveRimLoop();
			SetFocus();
			break;
		case (HK_CONTROL + HK_RIGHT):
		case (HK_CONTROL + HK_LEFT):
			pNM->hdr.hwndFrom = m_hWnd;
			pNM->hdr.idFrom = GetDlgCtrlID();
			pNM->hdr.code = LVN_RIMCTRLMOVE;
			lRC = ::SendMessage(GetParent()->m_hWnd, WM_NOTIFY, (WPARAM)GetDlgCtrlID(), (LPARAM)pNM);
			break;

		case (HK_UP):
			// Do we have a parent hub?
			if (PrntHub.GetCount() == 1)
			{
				// If FocusedItem is HEAD or NOT UpDownEnabled
				if ((FocusedItem.IsHead == TRUE) || (Items.bUpDn == FALSE))
				{
					lRC = ::SendMessage(PrntHub.GetKeyAt(PrntHub.GetStartPosition()), WM_RIMCTRLKEYS, wParam, lParam);

					// If UpDownEnabled
					if (Items.bUpDn == TRUE)
					{
						FocusItem(FI_TAIL);
					}
				}
				else
				{
					// If UpDownEnabled
					if (Items.bUpDn == TRUE)
					{
						FocusItem(FI_PREV);
					}
				}
			}
			else
			{
				// If UpDownEnabled
				if (Items.bUpDn == TRUE)
				{
					FocusItem(FI_PREV);
				}
			}
			break;

		case (HK_DOWN):
			// Do we have a parent hub?
			if (PrntHub.GetCount() == 1)
			{
				// If FocusedItem is TAIL or NOT UpDownEnabled
				if ((FocusedItem.IsTail == TRUE) || (Items.bUpDn == FALSE))
				{
					lRC = ::SendMessage(PrntHub.GetKeyAt(PrntHub.GetStartPosition()), WM_RIMCTRLKEYS, wParam, lParam);

					// If UpDownEnabled
					if (Items.bUpDn == TRUE)
					{
						FocusItem(FI_HEAD);
					}
				}
				else
				{
					// If UpDownEnabled
					if (Items.bUpDn == TRUE)
					{
						FocusItem(FI_NEXT);
					}
				}
			}
			else
			{
				// If UpDownEnabled
				if (Items.bUpDn == TRUE)
				{
					FocusItem(FI_NEXT);
				}
			}
			break;

		case (HK_END):
			// If UpDownEnabled
			if (Items.bUpDn == TRUE)
			{
				FocusItem(FI_TAIL);
			}
			// else if we have a parent hub
			else if (PrntHub.GetCount() == 1)
			{
				lRC = ::SendMessage(PrntHub.GetKeyAt(PrntHub.GetStartPosition()), WM_RIMCTRLKEYS, wParam, lParam);
			}
			break;
		case (HK_HOME):
			// If UpDownEnabled
			if (Items.bUpDn == TRUE)
			{
				FocusItem(FI_HEAD);
			}
			// else if we have a parent hub
			else if (PrntHub.GetCount() == 1)
			{
				lRC = ::SendMessage(PrntHub.GetKeyAt(PrntHub.GetStartPosition()), WM_RIMCTRLKEYS, wParam, lParam);
			}
			break;
		}
		
		//AfxTrace(_T("ScanStat.3\n"));
		ScanStat();

		return (lRC);
	}

	void CPSHubListCtrl::OnCustomDraw(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMCUSTOMDRAW		pCD			= reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		LPNMLVCUSTOMDRAW	pLVCD		= NULL;

		if (pCD->hdr.hwndFrom == m_hWnd)
		{
			switch (pCD->hdr.code)
			{
			case NM_CUSTOMDRAW:

				pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pCD);

				if (pCD->dwDrawStage == CDDS_PREPAINT)
				{
					*pResult = CDRF_NOTIFYITEMDRAW;
					return;
				}

				else if (pCD->dwDrawStage == CDDS_ITEMPREPAINT)
				{
					*pResult = CDRF_NOTIFYSUBITEMDRAW;
					return;
				}

				else if (pCD->dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
				{
					*pResult = CDRF_NOTIFYPOSTPAINT;
					return;
				}

				else if (pCD->dwDrawStage == (CDDS_ITEMPOSTPAINT | CDDS_SUBITEM))
				{
					RECT		rcCel		= {0, 0, 0, 0};
					CRect		rcTxt;
					TCHAR		tzCel[256];	memset(tzCel, 0, sizeof(tzCel));
					LVCOLUMN	lvCol;		memset(&lvCol, 0, sizeof(LVCOLUMN));
					UINT		uiFmt		= 0;
					BOOL		isLVE		= IsWindowEnabled();
					BOOL		isLIC		= ((GetItemState((int)pCD->dwItemSpec, LVIS_STATEIMAGEMASK) == LVIS_CHECKED) ? TRUE : FALSE);
					BOOL		isLIS		= ((GetItemState((int)pCD->dwItemSpec, LVIS_SELECTED) == LVIS_SELECTED) ? TRUE : FALSE);
					BOOL		isLIF		= ((GetItemState((int)pCD->dwItemSpec, LVIS_FOCUSED) == LVIS_FOCUSED) ? TRUE : FALSE);
					
					// AfxTrace(_T("PostPaint Item=%d SubItem=%d\n"), pCD->dwItemSpec, pLVCD->iSubItem);

					lvCol.mask = LVCF_FMT;
					GetColumn(pLVCD->iSubItem, &lvCol);
					
					switch (lvCol.fmt & LVCFMT_JUSTIFYMASK)
					{
					case LVCFMT_LEFT:
						uiFmt = DT_LEFT;
						// AfxTrace(_T("- LVCFMT_LEFT\n"));
						break;
					case LVCFMT_RIGHT:
						uiFmt = DT_RIGHT;
						// AfxTrace(_T("- LVCFMT_RIGHT\n"));
						break;
					case LVCFMT_CENTER:
						uiFmt = DT_CENTER;
						// AfxTrace(_T("- LVCFMT_CENTER\n"));
						break;
					}

					GetItemText((int)pCD->dwItemSpec, pLVCD->iSubItem, tzCel, 255);
					// AfxTrace(_T("- %s\n"), tzCel);
					
					if (pLVCD->iSubItem > 0)
					{
						rcCel.left	= LVIR_BOUNDS;
						rcCel.top	= pLVCD->iSubItem;
						SendMessage(LVM_GETSUBITEMRECT, (WPARAM)pCD->dwItemSpec, (LPARAM)&rcCel);
						rcTxt = rcCel;
						// AfxTrace(_T("- cel t:%d l:%d b:%d r:%d\n"), rcCel.top, rcCel.left, rcCel.bottom, rcCel.right);
					}
					else
					{
						rcCel.left	= LVIR_LABEL;
						SendMessage(LVM_GETITEMRECT, (WPARAM)pCD->dwItemSpec, (LPARAM)&rcCel);
						rcTxt = rcCel;
						// AfxTrace(_T("- cel t:%d l:%d b:%d r:%d\n"), rcCel.top, rcCel.left, rcCel.bottom, rcCel.right);
					}

					::SetBkMode(pCD->hdc, OPAQUE);

					// Brush, Text Background and Text
					if (isLVE)
					{
						::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_WINDOW));
						
						if (((GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES) && (!isLIC))
						{
							::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_INACTIVECAPTIONTEXT));
							::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_WINDOW)));
						}
						else
						{
							if (isLIS)
							{
								::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
								::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
								::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
								// AfxTrace(_T("LIS: FillRect COLOR_HIGHLIGHTTEXT/COLOR_HIGHLIGHT\n"));
							}
							else
							{
								::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_WINDOWTEXT));
								::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_WINDOW)));
								// AfxTrace(_T("OTH: FillRect COLOR_WINDOWTEXT/COLOR_WINDOW\n"));
							}
							if ((isLIF) && (!isLIS) && (pLVCD->iSubItem == 0))
							{
								::DrawFocusRect(pCD->hdc, &rcTxt);
							}
						}
					}
					else
					{
						::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_BTNFACE));

						if ((GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES)
						{
							// All checked considered selected
							if (Items.iFilt == FF_CHKD)
							{
								if (isLIC)
								{
									if (isLIF)
									{
										::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
										::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
										::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
									}
									else
									{
										::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
										::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_BTNFACE));
										::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
									}
								}
								else
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_INACTIVECAPTIONTEXT));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
								}
							}
							// Only checked && selected
							else
							{
								if (isLIC)
								{
									if (isLIF)
									{
										::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
										::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
										::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
									}
									else if (isLIS)
									{
										::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
										::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_BTNFACE));
										::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
									}
									else
									{
										::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_WINDOWTEXT));
										::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
									}
								}
								else
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_INACTIVECAPTIONTEXT));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
								}
							}
						}
						else
						{
							// All considered selected
							if (Items.iFilt == FI_NONE)
							{
								if (isLIF)
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
									::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
								}
								else
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
									::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_BTNFACE));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
								}
							}
							// Only selected
							else
							{
								if (isLIF)
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
									::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
								}
								else if (isLIS)
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_HIGHLIGHT));
									::SetBkColor(pCD->hdc, ::GetSysColor(COLOR_BTNFACE));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
								}
								else
								{
									::SetTextColor(pCD->hdc, ::GetSysColor(COLOR_WINDOWTEXT));
									::FillRect(pCD->hdc, &rcCel, (HBRUSH)CBrush(::GetSysColor(COLOR_BTNFACE)));
								}
							}
						}
					}
					rcTxt.DeflateRect(6, 2);
					// AfxTrace(_T("- txt t:%d l:%d b:%d r:%d\n"), rcTxt.top, rcTxt.left, rcTxt.bottom, rcTxt.right);
					::DrawText(pCD->hdc, tzCel, (int)_tcslen(tzCel), &rcTxt, (UINT)uiFmt);

					if ((isLIF) && (pLVCD->iSubItem == Items.iSItm) && (!isLVE))
					{
						::DrawFocusRect(pCD->hdc, &rcCel);
					}
					
					return;
				}

				break;
			}
		}

		*pResult = (LRESULT)CDRF_DODEFAULT;
	}


	// If you use ON_NOTIFY_REFLECT_EX() in your message map, your message handler may or may not 
	// allow the parent window to handle the message. If the handler returns FALSE, the message will
	// be handled by the parent as well, while a call that returns TRUE does not allow the parent to
	// handle it. Note that the reflected message is handled before the notification message.
	//
	BOOL CPSHubListCtrl::OnItemChanging(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLISTVIEW	pLV			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		int				iLV			= pLV->iItem;
		BOOL			bEX			= FALSE;

		*pResult = 0;
		
		// State Change
		if ((pLV->uChanged & LVIF_STATE) == LVIF_STATE)
		{
			// If LVS_EX_CHECKBOXES
			if ((GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES)
			{
				// Disallow uncheck if item is selected
				if (((pLV->uOldState & LVIS_STATEIMAGEMASK) == LVIS_CHECKED) && ((pLV->uNewState & LVIS_STATEIMAGEMASK) == LVIS_UNCHECKED))
				{
					*pResult = ((GetItemState(iLV, LVIS_SELECTED) == LVIS_SELECTED) ? 1 : 0);
				}
				// Disallow item selected if not checked
				if (((pLV->uOldState & LVIS_SELECTED) != LVIS_SELECTED) && ((pLV->uNewState & LVIS_SELECTED) == LVIS_SELECTED))
				{
					*pResult = ((GetItemState(iLV, LVIS_STATEIMAGEMASK) != LVIS_CHECKED) ? 1 : 0);
				}
				// Allow notification to be passed up to dialog?
				bEX = ((*pResult == 1) ? TRUE : FALSE);
			}
			// AfxTrace(_T("HUB::OnItemChanging(%3d:%08x->%08x)\n"), iLV, pLV->uOldState, pLV->uNewState);
		}

		return (bEX);
	}

	BOOL CPSHubListCtrl::OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLISTVIEW	pLV			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		int				iLV			= pLV->iItem;
		BOOL			bEX			= FALSE;

		*pResult = 0;

		// State Change
		if ((pLV->uChanged & LVIF_STATE) == LVIF_STATE)
		{
			if (((pLV->uOldState & LVIS_FOCUSED) == LVIS_FOCUSED) && ((pLV->uNewState & LVIS_FOCUSED) != LVIS_FOCUSED))
			{
				Stats.iFcsd = -1;
			}
			else if (((pLV->uOldState & LVIS_FOCUSED) != LVIS_FOCUSED) && ((pLV->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED))
			{
				Stats.iFcsd = iLV;
				EnsureVisible(iLV, FALSE);
			}
			//AfxTrace(_T("ScanStat.1\n"));
			ScanStat();
		}

		// Appears to be bug in SysListView32 caching old rects/states
		// - When column resizes, it remedies
		// - Force this by Get/Set Item on last column
		//
		if (1)
		{
			HDITEM			hdI;		memset(&hdI, 0, sizeof(HDITEM));
			int				iCH			= (GetHeaderCtrl()->GetItemCount() - 1);

			hdI.mask = HDI_WIDTH;

			GetHeaderCtrl()->GetItem(iCH, &hdI);
			GetHeaderCtrl()->SetItem(iCH, &hdI);
		}

		// We want dialog to handle updating controls if new item selected
		return (bEX);
	}



	//
	// CPSRimEdit
	//
	IMPLEMENT_DYNAMIC(CPSRimEdit, CEdit)

	CPSRimEdit::CPSRimEdit() : CEdit(), hwHub(NULL), idHub(-1), hkMap(0)
	{
	}
	CPSRimEdit::~CPSRimEdit()
	{
	}

	BEGIN_MESSAGE_MAP(AFXCNTRLLIB::CPSRimEdit, CEdit)
		ON_WM_KEYDOWN()
		ON_WM_KEYUP()
		ON_CONTROL_REFLECT_EX(EN_SETFOCUS, CPSRimEdit::OnSetFocus)
		ON_CONTROL_REFLECT_EX(EN_KILLFOCUS, CPSRimEdit::OnKillFocus)
	END_MESSAGE_MAP()

	void CPSRimEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		NMRIMCTRL		nm;	memset(&nm, 0, sizeof(NMRIMCTRL));
		SHORT			i2	= ::GetAsyncKeyState(VK_CONTROL);

		// Windows Issue Note:
		// - Windows either sends or misses SHIFT, CONTROL down/up frequently
		//   so we'll call GetKeyAsyncState() to check

		// Bit Flag Keys to process
		switch (nChar)
		{
		case VK_CONTROL:
		case VK_SHIFT:
			break;
		case VK_HOME:
			hkMap |= HK_HOME;
			break;
		case VK_UP:
			hkMap |= HK_UP;
			break;
		case VK_DOWN:
			hkMap |= HK_DOWN;
			break;
		case VK_END:
			hkMap |= HK_END;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		case VK_LEFT:
			hkMap |= HK_LEFT;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		case VK_RIGHT:
			hkMap |= HK_RIGHT;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		default:
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			break;
		}

		// Process Keys need @ Key Up
		switch (hkMap)
		{
		case (HK_CONTROL + HK_END):
		case (HK_CONTROL + HK_RIGHT):
		case (HK_CONTROL + HK_LEFT):
		case (HK_UP):
		case (HK_DOWN):
		case (HK_HOME):
		case (HK_END):
			nm.hdr.hwndFrom = m_hWnd;
			nm.hdr.idFrom = GetDlgCtrlID();
			nm.hdr.code = LVN_RIMCTRLKEYS;
			nm.rim.hwndFrom = m_hWnd;
			nm.rim.idFrom = GetDlgCtrlID();
			nm.rim.code = hkMap;
			if (hwHub != NULL)
			{
				::SendMessage(hwHub, WM_RIMCTRLKEYS, (WPARAM)m_hWnd, (LPARAM)&nm);
			}
			hkMap = 0;
			break;
		}
	}

	void CPSRimEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// Bit Flag Keys needed @ Key Up
		switch (nChar)
		{
		case VK_LEFT:
			hkMap &= ~HK_LEFT;
			break;
		case VK_UP:
			hkMap &= ~HK_UP;
			break;
		case VK_RIGHT:
			hkMap &= ~HK_RIGHT;
			break;
		case VK_DOWN:
			hkMap &= ~HK_DOWN;
			break;
		case VK_HOME:
			hkMap &= ~HK_HOME;
			break;
		case VK_END:
			hkMap &= ~HK_END;
			break;
		default:
			CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
		}
	}

	BOOL CPSRimEdit::OnSetFocus()
	{
		// AfxTrace(_T("RIM::OnSetFocus(%5d)\n"), GetDlgCtrlID());
		if (hwHub != NULL)
		{
			::SendMessage(hwHub, WM_RIMCTRLSETFOCUS, (WPARAM)0, (LPARAM)m_hWnd);
		}	
		return (FALSE);
	}

	BOOL CPSRimEdit::OnKillFocus()
	{
		// AfxTrace(_T("RIM::OnKillFocus(%5d)\n"), GetDlgCtrlID());
		if (hwHub != NULL)
		{
			::SendMessage(hwHub, WM_RIMCTRLKILLFOCUS, (WPARAM)0, (LPARAM)m_hWnd);
		}
		return (FALSE);
	}

	//
	// CPSRimButton
	//
	IMPLEMENT_DYNAMIC(CPSRimButton, CButton)

	CPSRimButton::CPSRimButton() : CButton(), hwHub(NULL), idHub(-1), hkMap(0)
	{
	}
	CPSRimButton::~CPSRimButton()
	{
	}

	BEGIN_MESSAGE_MAP(AFXCNTRLLIB::CPSRimButton, CButton)
		ON_WM_GETDLGCODE()
		ON_WM_KEYDOWN()
		ON_WM_KEYUP()
		ON_CONTROL_REFLECT_EX(BN_SETFOCUS, CPSRimButton::OnSetFocus)
		ON_CONTROL_REFLECT_EX(BN_KILLFOCUS, CPSRimButton::OnKillFocus)
	END_MESSAGE_MAP()

	UINT CPSRimButton::OnGetDlgCode()
	{
		if ((GetStyle() & BS_AUTORADIOBUTTON) == BS_AUTORADIOBUTTON)
		{
//			return (DLGC_WANTARROWS | DLGC_WANTMESSAGE | DLGC_RADIOBUTTON);
			return (DLGC_WANTARROWS | DLGC_RADIOBUTTON);
		}
		else
		{
			return (DLGC_WANTARROWS | DLGC_BUTTON);
//			return (DLGC_WANTARROWS | DLGC_WANTMESSAGE | DLGC_BUTTON);
		}
	}

	void CPSRimButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		NMRIMCTRL		nm;	memset(&nm, 0, sizeof(NMRIMCTRL));
		SHORT			i2	= ::GetAsyncKeyState(VK_CONTROL);

		// Windows Issue Note:
		// - Windows either sends or misses SHIFT, CONTROL down/up frequently
		//   so we'll call GetKeyAsyncState() to check

		// Bit Flag Keys to process
		switch (nChar)
		{
		case VK_CONTROL:
		case VK_SHIFT:
			break;
		case VK_HOME:
			hkMap |= HK_HOME;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		case VK_UP:
			hkMap |= HK_UP;
			break;
		case VK_DOWN:
			hkMap |= HK_DOWN;
			break;
		case VK_END:
			hkMap |= HK_END;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		case VK_LEFT:
			hkMap |= HK_LEFT;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		case VK_RIGHT:
			hkMap |= HK_RIGHT;
			if ((i2 & 0x8000) == 0x8000)
			{
				hkMap |= HK_CONTROL;
			}
			break;
		default:
			CButton::OnKeyDown(nChar, nRepCnt, nFlags);
			break;
		}

		// Process Keys need @ Key Up
		switch (hkMap)
		{
		case (HK_CONTROL + HK_RIGHT):
		case (HK_CONTROL + HK_LEFT):
		case (HK_UP):
		case (HK_DOWN):
		case (HK_HOME):
		case (HK_END):
			nm.hdr.hwndFrom = m_hWnd;
			nm.hdr.idFrom = GetDlgCtrlID();
			nm.hdr.code = LVN_RIMCTRLKEYS;
			nm.rim.hwndFrom = m_hWnd;
			nm.rim.idFrom = GetDlgCtrlID();
			nm.rim.code = hkMap;
			if (hwHub != NULL)
			{
				::SendMessage(hwHub, WM_RIMCTRLKEYS, (WPARAM)m_hWnd, (LPARAM)&nm);
			}
			hkMap = 0;
			break;
		}
	}

	void CPSRimButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// Bit Flag Keys needed @ Key Up
		switch (nChar)
		{
		case VK_LEFT:
			hkMap &= ~HK_LEFT;
			break;
		case VK_UP:
			hkMap &= ~HK_UP;
			break;
		case VK_RIGHT:
			hkMap &= ~HK_RIGHT;
			break;
		case VK_DOWN:
			hkMap &= ~HK_DOWN;
			break;
		case VK_HOME:
			hkMap &= ~HK_HOME;
			break;
		case VK_END:
			hkMap &= ~HK_END;
			break;
		default:
			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		}
	}

	BOOL CPSRimButton::OnSetFocus()
	{
		// AfxTrace(_T("RIM::OnSetFocus(%5d)\n"), GetDlgCtrlID());
		if (hwHub != NULL)
		{
			::SendMessage(hwHub, WM_RIMCTRLSETFOCUS, (WPARAM)0, (LPARAM)m_hWnd);

			CDC*	pDC			= GetDC();
			CRect	rcC;		GetClientRect(&rcC);

			pDC->DrawFocusRect(&rcC);
		}	
		return (FALSE);
	}

	BOOL CPSRimButton::OnKillFocus()
	{
		// AfxTrace(_T("RIM::OnKillFocus(%5d)\n"), GetDlgCtrlID());
		if (hwHub != NULL)
		{
			CDC*	pDC			= GetDC();
			CRect	rcC;		GetClientRect(&rcC);

			pDC->DrawFocusRect(&rcC);

			::SendMessage(hwHub, WM_RIMCTRLKILLFOCUS, (WPARAM)0, (LPARAM)m_hWnd);
		}
		return (FALSE);
	}
};
