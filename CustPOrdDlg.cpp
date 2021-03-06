// CustPOrdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PAIFMain.h"

#include "CustPOrdDlg.h"

#include "PickDlg.h"
#include "DOrdDlg.h"
#include "CustPOrdALogDlg.h"

static bool b_nInit		= true;
static int	i_nMatl		= -1;
static int	i_nXOrd		= -1;

// CCustPOrdDlg dialog

IMPLEMENT_DYNAMIC(CCustPOrdDlg, CDialog)

CCustPOrdDlg::CCustPOrdDlg(CWnd* pParent, NODEMENUCONSTANT Task, LPCUST pCust, LPCUSTPORD pPOrd) : 
	CDialog(CCustPOrdDlg::IDD, pParent),
	m_Task(Task),
	m_POrd(*pPOrd),
	p_Cust(pCust),
	p_POrd(pPOrd),
	p_CustMatl(NULL),
	p_Matl(NULL),
	p_MSet(NULL),
	p_PSet(NULL),
	x_MSet(NULL),
	x_PSet(NULL),
	x_Fcsd(0),
	m_Col1(1),
	p_ReqdMN(NULL),
	p_ReqdMX(NULL),
	m_XAct(XA_NEDT)
{
	SYSTEMTIME		st;		memset(&st, 0, sizeof(st));

	::GetLocalTime(&st);
	st.wHour = st.wMinute = st.wSecond= st.wMilliseconds = 0;

	p_2Day = new CTime(st);
}

CCustPOrdDlg::CCustPOrdDlg(CWnd* pParent, NODEMENUCONSTANT Task, LPCUST pCust, LPCUSTPORD pPOrd, LPCUSTPORDMSET pMSet) : 
	CDialog(CCustPOrdDlg::IDD, pParent),
	m_Task(Task),
	m_POrd(*pPOrd),
	p_Cust(pCust),
	p_POrd(pPOrd),
	p_CustMatl(NULL),
	p_Matl(NULL),
	p_MSet(pMSet),
	p_PSet(NULL),
	x_MSet(NULL),
	x_PSet(NULL),
	x_Fcsd(0),
	m_Col1(1),
	p_ReqdMN(NULL),
	p_ReqdMX(NULL),
	m_XAct(XA_NEDT)
{
	SYSTEMTIME		st;		memset(&st, 0, sizeof(st));

	::GetLocalTime(&st);
	st.wHour = st.wMinute = st.wSecond= st.wMilliseconds = 0;

	p_2Day = new CTime(st);
}

	CCustPOrdDlg::~CCustPOrdDlg()
{
	if (p_2Day != NULL)
	{
		delete p_2Day;
		p_2Day = NULL;
	}
}

void CCustPOrdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDT_CUSTID, m_edtCustID);
	DDX_Control(pDX, IDC_EDT_CUSTSZ, m_edtCustSZ);
	DDX_Control(pDX, IDC_EDT_CUSTPO, m_edtCustPO);
	DDX_Control(pDX, IDC_DTP_CRTDDT, m_dtpCrtdDT);
	DDX_Control(pDX, IDC_DTP_OPNDDT, m_dtpOpndDT);
	DDX_Control(pDX, IDC_DTP_CLSDDT, m_dtpClsdDT);
	DDX_Control(pDX, IDC_LVW_MATL, m_lvwMatl);
	DDX_Control(pDX, IDC_EDT_CMPRCE, m_edtCMPrce);
	DDX_Control(pDX, IDC_EDT_SAPRCE, m_edtSAPrce);
	DDX_Control(pDX, IDC_EDT_PORDXQ, m_edtPOrdXQ);
	DDX_Control(pDX, IDC_EDT_XORDXS, m_edtXOrdXS);
	DDX_Control(pDX, IDC_EDT_XREMXS, m_edtXRemXS);
	DDX_Control(pDX, IDC_TAB_PORD, m_tabPOrd);
	DDX_Control(pDX, IDC_LVW_PSET, m_lvwPSet);
	DDX_Control(pDX, IDC_EDT_PADJXQ, m_edtPAdjXQ);
	DDX_Control(pDX, IDC_DTP_PSRCDT, m_dtpPSrcDT);
	DDX_Control(pDX, IDC_DTP_PDSTDT, m_dtpPDstDT);
	DDX_Control(pDX, IDC_EDT_XORGXS, m_edtXOrgXS);
	DDX_Control(pDX, IDC_EDT_XPRMXS, m_edtXPrmXS);
	DDX_Control(pDX, IDC_EDT_XSCNXS, m_edtXScnXS);
	DDX_Control(pDX, IDC_EDT_XSHPXS, m_edtXShpXS);
	DDX_Control(pDX, IDC_LVW_ALOG, m_lvwALog);
	DDX_Control(pDX, IDC_EDT_CMNTSZ, m_edtCmntSZ);
}

BEGIN_MESSAGE_MAP(CCustPOrdDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_SIZING()
	ON_EN_CHANGE(IDC_EDT_CUSTPO, &CCustPOrdDlg::OnChangeCustPO)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_CRTDDT, &CCustPOrdDlg::OnDateTimeChangeCrtdDT)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_OPNDDT, &CCustPOrdDlg::OnDateTimeChangeOpndDT)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_CLSDDT, &CCustPOrdDlg::OnDateTimeChangeClsdDT)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LVW_MATL, &CCustPOrdDlg::OnItemChangingMatl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LVW_MATL, &CCustPOrdDlg::OnItemChangedMatl)
	ON_NOTIFY(LVN_RIMCTRLMOVE, IDC_LVW_MATL, &CCustPOrdDlg::OnRimCtrlMoveMatl)
	ON_NOTIFY(LVN_GETINFOTIP, IDC_LVW_MATL, &CCustPOrdDlg::OnGetInfoTipMatl)
	ON_EN_SETFOCUS(IDC_EDT_CMPRCE, &CCustPOrdDlg::OnSetFocusCMPrce)
	ON_EN_UPDATE(IDC_EDT_CMPRCE, &CCustPOrdDlg::OnUpdateCMPrce)
	ON_EN_KILLFOCUS(IDC_EDT_CMPRCE, &CCustPOrdDlg::OnKillFocusCMPrce)
	ON_EN_SETFOCUS(IDC_EDT_SAPRCE, &CCustPOrdDlg::OnSetFocusSAPrce)
	ON_EN_UPDATE(IDC_EDT_SAPRCE, &CCustPOrdDlg::OnUpdateSAPrce)
	ON_EN_KILLFOCUS(IDC_EDT_SAPRCE, &CCustPOrdDlg::OnKillFocusSAPrce)
	ON_EN_SETFOCUS(IDC_EDT_PORDXQ, &CCustPOrdDlg::OnSetFocusPOrdXQ)
	ON_EN_UPDATE(IDC_EDT_PORDXQ, &CCustPOrdDlg::OnUpdatePOrdXQ)
	ON_EN_KILLFOCUS(IDC_EDT_PORDXQ, &CCustPOrdDlg::OnKillFocusPOrdXQ)
	ON_BN_CLICKED(IDC_OPT_PUOM, &CCustPOrdDlg::OnClickPUOM)
	ON_BN_CLICKED(IDC_OPT_SUOM, &CCustPOrdDlg::OnClickSUOM)
	ON_BN_CLICKED(IDC_OPT_UUOM, &CCustPOrdDlg::OnClickUUOM)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LVW_PSET, &CCustPOrdDlg::OnItemChangingPSet)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LVW_PSET, &CCustPOrdDlg::OnItemChangedPSet)
	ON_NOTIFY(LVN_RIMCTRLMOVE, IDC_LVW_PSET, &CCustPOrdDlg::OnRimCtrlMovePSet)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_PDSTDT, &CCustPOrdDlg::OnDateTimeChangePDstDT)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DTP_PSRCDT, &CCustPOrdDlg::OnDateTimeChangePSrcDT)
	ON_EN_SETFOCUS(IDC_EDT_PADJXQ, &CCustPOrdDlg::OnSetFocusPAdjXQ)
	ON_EN_UPDATE(IDC_EDT_PADJXQ, &CCustPOrdDlg::OnUpdatePAdjXQ)
	ON_EN_KILLFOCUS(IDC_EDT_PADJXQ, &CCustPOrdDlg::OnKillFocusPAdjXQ)
	ON_BN_CLICKED(IDC_BTN_NEW, &CCustPOrdDlg::OnClickNew)
	ON_BN_CLICKED(IDC_BTN_XFR, &CCustPOrdDlg::OnClickXfr)
	ON_BN_CLICKED(IDC_BTN_UNDO, &CCustPOrdDlg::OnClickUndo)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CCustPOrdDlg::OnClickSave)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LVW_MATL, &CCustPOrdDlg::OnColumnClickMatl)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PORD, &CCustPOrdDlg::OnSelChangePOrd)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LVW_ALOG, &CCustPOrdDlg::OnItemChangingALog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LVW_ALOG, &CCustPOrdDlg::OnItemChangedALog)
END_MESSAGE_MAP()

void CCustPOrdDlg::DoTest()
{
	//
	// Test to use bitmap, bitblt to change CDateTimeCtrl Background color
	//
	CRect	rc;			m_dtpPDstDT.GetClientRect(&rc);
	CDC*	pcDC		= m_dtpPDstDT.GetDC();
	CDC		imDC;		imDC.CreateCompatibleDC(pcDC);
	CBitmap	imBM;		imBM.CreateCompatibleBitmap(pcDC, rc.Width(), rc.Height());

	imDC.SelectObject(&imBM);
	imDC.BitBlt(0, 0, rc.Width(), rc.Height(), pcDC, 0, 0, SRCCOPY);

	int		cPix		= ((rc.Width() * 4) * rc.Height());
	LPBYTE	pPix		= new BYTE[cPix];

	imBM.GetBitmapBits((DWORD)cPix, (LPVOID)pPix);

	// Trace Quads for arbitrary line
	if (0)
	{
		int		r = rc.Height() / 2;
		LPBYTE	p = &pPix[(r * (rc.Width() * 4))];

		for (int c = 0, q = 0; c < rc.Width(); c++)
		{
			switch (c % 4)
			{
			case 0:
				AfxTrace(_T("\n%03d: [%02X]"), q, p[c]);
				q++;
				break;
			default:
				AfxTrace(_T("[%02X]"), p[c]);
			}
		}
		AfxTrace(_T("\n"));
	}

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

void CCustPOrdDlg::ShowMatlList(POSITION pos)
{
	TCHAR		tz[256];	memset(tz, 0, sizeof(tz));
	LPMATL		pM			= NULL;
	POSITION	xM			= x_MSet;
	int			ni			= 0;
	LVCOLUMN	lc;			memset(&lc, 0, sizeof(LVCOLUMN));

	int			exi			= (int)m_POrd.m_MSets.GetCount();
	int			tot			= m_lvwMatl.GetItemCount();

	if (pos == NULL)
	{
		lc.cchTextMax = 255;
		lc.pszText = &tz[0];
		lc.mask = LVCF_TEXT;

		if (tot != exi)
		{
			tot = 0;
			m_lvwMatl.DeleteAllItems();
		}

		_tcscpy_s<_countof(tz)>(tz, ((m_Col1 == 0) ? _T("Matl ID") : _T("Styl ID")));
		m_lvwMatl.SetColumn(0, &lc);

		switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			_tcscpy_s<_countof(tz)>(tz, _T("POrd SQ"));
			m_lvwMatl.SetColumn(2, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("PRem SQ"));
			m_lvwMatl.SetColumn(3, &lc);
			break;
		case IDC_OPT_UUOM:
			_tcscpy_s<_countof(tz)>(tz, _T("UOrd CT"));
			m_lvwMatl.SetColumn(2, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("URem CT"));
			m_lvwMatl.SetColumn(3, &lc);
			break;
		default:
			_tcscpy_s<_countof(tz)>(tz, _T("POrd PQ"));
			m_lvwMatl.SetColumn(2, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("PRem PQ"));
			m_lvwMatl.SetColumn(3, &lc);
		}

		for (POSITION x = m_POrd.m_MSets.GetHeadPosition(); x != NULL; m_POrd.m_MSets.GetNext(x))
		{
			CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x);

			if (tot == 0)
			{
				m_lvwMatl.InsertItem(ni, ((m_Col1 == 0) ? (LPCTSTR)ms.MatlID : (LPCTSTR)ms.StylID()));
				m_lvwMatl.SetItemData(ni, (DWORD_PTR)x);
			}
			else
			{
				m_lvwMatl.SetItemText(ni, 0, ((m_Col1 == 0) ? (LPCTSTR)ms.MatlID : (LPCTSTR)ms.StylID()));
			}

			if ( ((ms.F.StatID == (BYTE)0x10) && ((ms.m_DBOp & CCustPOrdMSet::DB_DELETE) != CCustPOrdMSet::DB_DELETE))
			||	 ((ms.F.StatID == (BYTE)0x00) && ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT))
			) 
			{
				m_lvwMatl.SetCheck(ni, 1);
			}

			m_lvwMatl.SetItemText(ni, 1, (LPCTSTR)ms.PartID);

			switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
			{
			case IDC_OPT_SUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ms.MRemPQ()));
				m_lvwMatl.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ms.MOrdPQ()));
				m_lvwMatl.SetItemText(ni, 2, tz);
				break;
			case IDC_OPT_UUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ms.MRemPQ()));
				m_lvwMatl.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ms.MOrdPQ()));
				m_lvwMatl.SetItemText(ni, 2, tz);
				break;
			default:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.MRemPQ());
				m_lvwMatl.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.MOrdPQ());
				m_lvwMatl.SetItemText(ni, 2, tz);
			}

			if (xM == x)
			{
				if (((GetFocus() != NULL) && (GetFocus()->m_hWnd != m_edtPOrdXQ.m_hWnd)) || (GetFocus() == NULL))
				{
					m_edtPOrdXQ.SetWindowText(tz);
				}

				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(xM);
				LPMATL			pM = MatlLRR(ms.MatlID);

				switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
				{
				case IDC_OPT_SUOM:
					_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->SQtyUID);
					GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);
					break;

				case IDC_OPT_UUOM:
					if (pM->PQtyUID == (LPCTSTR)_T("SlitYds"))
						_tcscpy_s<_countof(tz)>(tz, _T("Cases"));
					else if (pM->PQtyUID == (LPCTSTR)_T("WideYds"))
						_tcscpy_s<_countof(tz)>(tz, _T("Rolls"));
					else
						_tcscpy_s<_countof(tz)>(tz, _T("Units"));
					GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);
					break;

				default:
					_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->PQtyUID);
					GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);
				}

				if (tot == 0)
				{
					m_lvwMatl.SetItemState(ni, LVIS_SELECTED, LVIS_SELECTED);
					m_lvwMatl.EnsureVisible(ni, FALSE);
				}
			}

			ni++;
		}
	}
	else
	{
		for (ni = 0; ni < m_lvwMatl.GetItemCount(); ni++)
		{
			if (pos == (POSITION)m_lvwMatl.GetItemData(ni))
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(pos);
				LPMATL			pM = MatlLRR(ms.MatlID);

				switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
				{
				case IDC_OPT_SUOM:
					_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->SQtyUID);
					GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);

					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ms.MRemPQ()));
					m_lvwMatl.SetItemText(ni, 3, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ms.MOrdPQ()));
					m_lvwMatl.SetItemText(ni, 2, tz);
					break;
				
				case IDC_OPT_UUOM:
					if (pM->PQtyUID == (LPCTSTR)_T("SlitYds"))
						_tcscpy_s<_countof(tz)>(tz, _T("Cases"));
					else if (pM->PQtyUID == (LPCTSTR)_T("WideYds"))
						_tcscpy_s<_countof(tz)>(tz, _T("Rolls"));
					else
						_tcscpy_s<_countof(tz)>(tz, _T("Units"));
					GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);

					_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ms.MRemPQ()));
					m_lvwMatl.SetItemText(ni, 3, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ms.MOrdPQ()));
					m_lvwMatl.SetItemText(ni, 2, tz);
					break;
				
				default:
					_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->PQtyUID);
					GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);

					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.MRemPQ());
					m_lvwMatl.SetItemText(ni, 3, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.MOrdPQ());
					m_lvwMatl.SetItemText(ni, 2, tz);
				}

				if (((GetFocus() != NULL) && (GetFocus()->m_hWnd != m_edtPOrdXQ.m_hWnd)) || (GetFocus() == NULL))
				{
					m_edtPOrdXQ.SetWindowText(tz);
				}

				break;
			}
		}
	}

	if (1)
	{
		SqlNumeric<10, 2>	pq[2];
		SqlNumeric<10, 2>	sq[2];
		SqlSmallInt			ct[2];

		pq[0] = (double)0.0;
		pq[1] = (double)0.0;
		ct[0] = (short)0;
		ct[1] = (short)0;
		sq[0] = (double)0.0;
		sq[1] = (double)0.0;

		for (POSITION x = m_POrd.m_MSets.GetHeadPosition(); x != NULL; m_POrd.m_MSets.GetNext(x))
		{
			CCustPOrdMSet&		ms = m_POrd.m_MSets.GetAt(x);

			if ((ms.F.StatID == (BYTE)0x10) || ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT))
			{
				switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
				{
				case IDC_OPT_SUOM:
					sq[0] = (double)sq[0] + ms.DQtySQ(ms.MOrdPQ());
					sq[1] = (double)sq[1] + ms.DQtySQ(ms.MRemPQ());
					break;
				case IDC_OPT_UUOM:
					ct[0] = (short)ct[0] + ms.UQtyCT(ms.MOrdPQ());
					ct[1] = (short)ct[1] + ms.UQtyCT(ms.MRemPQ());
					break;
				default:
					pq[0] = (double)pq[0] + ms.MOrdPQ();
					pq[1] = (double)pq[1] + ms.MRemPQ();
				}
			}
		}
		switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)sq[0]);
			m_edtXOrdXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)sq[1]);
			m_edtXRemXS.SetWindowText(tz);
			break;
		case IDC_OPT_UUOM:
			_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ct[0]);
			m_edtXOrdXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ct[1]);
			m_edtXRemXS.SetWindowText(tz);
			break;
		default:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)pq[0]);
			m_edtXOrdXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)pq[1]);
			m_edtXRemXS.SetWindowText(tz);
		}
	}
}

void CCustPOrdDlg::ShowPSetList(POSITION pos)
{
	if (x_MSet == NULL)
		return;

	HRESULT			hr			= S_OK;
	TCHAR			tz[265];	memset(tz, 0, sizeof(tz));
	int				ni			= 0;
	CCustPOrdMSet&	ms			= m_POrd.m_MSets.GetAt(x_MSet);

	if ((ms.F.StatID == (BYTE)0x00) && ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) != CCustPOrdMSet::DB_INSERT))
		return;
	if ((ms.F.StatID == (BYTE)0x10) && ((ms.m_DBOp & CCustPOrdMSet::DB_DELETE) == CCustPOrdMSet::DB_DELETE))
		return;

	LVCOLUMN		lc;		memset(&lc, 0, sizeof(LVCOLUMN));
	BOOL			we		= m_lvwPSet.IsWindowEnabled();
	SYSTEMTIME		sd;		memset(&sd, 0, sizeof(SYSTEMTIME));
	SYSTEMTIME		dd;		memset(&dd, 0, sizeof(SYSTEMTIME));
	int				is		= -1;
	int				id		= -1;
	DWORD			vs		= m_dtpPSrcDT.GetTime(&sd);
	DWORD			vd		= m_dtpPDstDT.GetTime(&dd);

	int				ins		= ((((ms.F.StatID & 0x10) == 0x10) || ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT)) ? 1 : 0);
	int				exi		= (int)ms.m_PSets.GetCount();
	int				tot		= m_lvwPSet.GetItemCount();

	// lvwPSet can't process notifications disabled, so enable remembering initial state
	if (we == FALSE)
	{
		m_lvwPSet.EnableWindow(1);
	}

	// Default List/Show ALL
	if (pos == NULL)
	{
		lc.cchTextMax = 255;
		lc.pszText = &tz[0];
		lc.mask = LVCF_TEXT;

		// Make Sure tot == (ins + exi), else DeleteAllItems()
		if (tot != (ins + exi))
		{
			tot = 0;
			m_lvwPSet.DeleteAllItems();
		}

		switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			_tcscpy_s<_countof(tz)>(tz, _T("POrg SQ"));
			m_lvwPSet.SetColumn(1, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("PPrm SQ"));
			m_lvwPSet.SetColumn(2, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("DScn SQ"));
			m_lvwPSet.SetColumn(3, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("DShp SQ"));
			m_lvwPSet.SetColumn(4, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("PRem SQ"));
			m_lvwPSet.SetColumn(5, &lc);
			break;
		
		case IDC_OPT_UUOM:
			_tcscpy_s<_countof(tz)>(tz, _T("UOrg CT"));
			m_lvwPSet.SetColumn(1, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("UPrm CT"));
			m_lvwPSet.SetColumn(2, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("UScn CT"));
			m_lvwPSet.SetColumn(3, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("UShp CT"));
			m_lvwPSet.SetColumn(4, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("URem CT"));
			m_lvwPSet.SetColumn(5, &lc);
			break;
		
		default:
			_tcscpy_s<_countof(tz)>(tz, _T("POrg PQ"));
			m_lvwPSet.SetColumn(1, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("PPrm PQ"));
			m_lvwPSet.SetColumn(2, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("DScn PQ"));
			m_lvwPSet.SetColumn(3, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("DShp PQ"));
			m_lvwPSet.SetColumn(4, &lc);
			_tcscpy_s<_countof(tz)>(tz, _T("PRem PQ"));
			m_lvwPSet.SetColumn(5, &lc);
		}

		if (((ms.F.StatID & 0x10) == 0x10) || ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT))
		{
			//
			// Setup Cached "NEW" Promised Data (PSet)
			//
			CCustPOrdMSetPSet&	ps = ms.m_PSets.m_PNew;

			ps.m_PKNo = (size_t)(ms.m_PSets.GetCount() + 1);
			ps.m_Orig = ms.IsOrig();
			ps.m_DBOp = CCustPOrdMSetPSet::DB_NULLOP;
			ps.F.UOrgCT	= (short)0;
			ps.F.POrgPQ = (double)0.0;
			ps.F.POrgSQ	= (double)0.0;

			if (ps.F.PrmdDT == SqlNull)
			{
				_tcscpy_s<_countof(tz)>(tz, _T("<select>"));
			}
			else
			{
				_tcsncpy_s<_countof(tz)>(tz, (LPCTSTR)ps.F.PrmdDT, 10);
				
				if ((vd == GDT_VALID) && (ps.F.PrmdDT == dd))
				{
					id = ni;
				}
			}
			if (tot == 0)
			{
				m_lvwPSet.InsertItem(ni, tz);
				m_lvwPSet.SetItemData(ni, (DWORD_PTR)ms.m_PSets.x_PNew);
				AfxTrace(_T("[0.a] x_PNew=%08x\n"), m_lvwPSet.GetItemData(ni));
			}
			else
			{
				m_lvwPSet.SetItemText(ni, 0, tz);
			}

			if (ps.F.PrmdIX != SqlNull)
			{
				_stprintf_s<_countof(tz)>(tz, _T("%d"), (BYTE)ps.F.PrmdIX);
				m_lvwPSet.SetItemText(ni, 6, tz);
			}

			switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
			{
			case IDC_OPT_SUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FOrgPQ()));
				m_lvwPSet.SetItemText(ni, 1, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DScnSQ);
				m_lvwPSet.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DShpSQ);
				m_lvwPSet.SetItemText(ni, 4, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FRemPQ()));
				m_lvwPSet.SetItemText(ni, 5, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FPrmPQ()));
				m_lvwPSet.SetItemText(ni, 2, tz);
				break;

			case IDC_OPT_UUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FOrgPQ()));
				m_lvwPSet.SetItemText(ni, 1, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ps.F.UScnCT);
				m_lvwPSet.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ps.F.UShpCT);
				m_lvwPSet.SetItemText(ni, 4, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FRemPQ()));
				m_lvwPSet.SetItemText(ni, 5, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FPrmPQ()));
				m_lvwPSet.SetItemText(ni, 2, tz);
				break;

			default:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FOrgPQ());
				m_lvwPSet.SetItemText(ni, 1, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DScnPQ);
				m_lvwPSet.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DShpPQ);
				m_lvwPSet.SetItemText(ni, 4, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FRemPQ());
				m_lvwPSet.SetItemText(ni, 5, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FPrmPQ());
				m_lvwPSet.SetItemText(ni, 2, tz);
			}

			ni++;
		}
		
		for (POSITION x = ms.m_PSets.GetHeadPosition(); x != NULL; ms.m_PSets.GetNext(x))
		{
			CCustPOrdMSetPSet&	ps = ms.m_PSets.Get(x);
			double				xq = 0;
			short				ct = 0;

			_tcsncpy_s(tz, _countof(tz), (LPCTSTR)ps.F.PrmdDT, 10);

			if (tot == 0)
			{
				m_lvwPSet.InsertItem(ni, tz);
				m_lvwPSet.SetItemData(ni, (DWORD_PTR)x);
				AfxTrace(_T("[n.a] x_PNew=%08x\n"), m_lvwPSet.GetItemData(ni));
			}
			else
			{
				m_lvwPSet.SetItemText(ni, 0, tz);
			}

			if ((vd == GDT_VALID) && (ps.F.PrmdDT == dd))
			{
				id = ni;
			}
			else if ((vs == GDT_VALID) && (ps.F.PrmdDT == sd))
			{
				is = ni;
			}

			if (ps.F.PrmdIX != SqlNull)
			{
				_stprintf_s<_countof(tz)>(tz, _T("%d"), (BYTE)ps.F.PrmdIX);
				m_lvwPSet.SetItemText(ni, 6, tz);
			}

			switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
			{
			case IDC_OPT_SUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FOrgPQ()));
				m_lvwPSet.SetItemText(ni, 1, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DScnSQ);
				m_lvwPSet.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DShpSQ);
				m_lvwPSet.SetItemText(ni, 4, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FRemPQ()));
				m_lvwPSet.SetItemText(ni, 5, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FPrmPQ()));
				m_lvwPSet.SetItemText(ni, 2, tz);
				break;
			case IDC_OPT_UUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FOrgPQ()));
				m_lvwPSet.SetItemText(ni, 1, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ps.F.UScnCT);
				m_lvwPSet.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ps.F.UShpCT);
				m_lvwPSet.SetItemText(ni, 4, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FRemPQ()));
				m_lvwPSet.SetItemText(ni, 5, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FPrmPQ()));
				m_lvwPSet.SetItemText(ni, 2, tz);
				break;
			default:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FOrgPQ());
				m_lvwPSet.SetItemText(ni, 1, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DScnPQ);
				m_lvwPSet.SetItemText(ni, 3, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DShpPQ);
				m_lvwPSet.SetItemText(ni, 4, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FRemPQ());
				m_lvwPSet.SetItemText(ni, 5, tz);
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FPrmPQ());
				m_lvwPSet.SetItemText(ni, 2, tz);
			}

			ni++;
		}

		if ((m_XAct == XA_NNEW) || (m_XAct == XA_NXFR))
		{
			if (id > -1)
			{
				m_lvwPSet.SetItemState(id, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));
			}
			else
			{
				AfxTrace(_T("WARNING: No PDstDT in PSet List\n"));
			}
		}
		if (m_XAct == XA_NXFR)
		{
			if (is > -1)
			{
				m_lvwPSet.SetItemState(is, LVIS_SELECTED, LVIS_SELECTED);
			}
			else
			{
				AfxTrace(_T("WARNING: No PSrcDT in PSet List\n"));
			}
		}
	}
	else
	{
		for (ni = 0; ni < m_lvwPSet.GetItemCount(); ni++)
		{
			if (pos == (POSITION)m_lvwPSet.GetItemData(ni))
			{
				CCustPOrdMSet&		ms = m_POrd.m_MSets.GetAt(x_MSet);
				CCustPOrdMSetPSet&	ps = ms.m_PSets.Get(pos);

				if (ps.F.PrmdDT == SqlNull)
				{
					m_lvwPSet.SetItemText(ni, 0, _T("<select>"));
				}
				else
				{
					_tcsncpy_s<_countof(tz)>(tz, (LPCTSTR)ps.F.PrmdDT, 10);
					m_lvwPSet.SetItemText(ni, 0, tz);
				}

				switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
				{
				case IDC_OPT_SUOM:
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FOrgPQ()));
					m_lvwPSet.SetItemText(ni, 1, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DScnSQ);
					m_lvwPSet.SetItemText(ni, 3, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DShpSQ);
					m_lvwPSet.SetItemText(ni, 4, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FRemPQ()));
					m_lvwPSet.SetItemText(ni, 5, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FPrmPQ()));
					m_lvwPSet.SetItemText(ni, 2, tz);
					break;
				case IDC_OPT_UUOM:
					_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FOrgPQ()));
					m_lvwPSet.SetItemText(ni, 1, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ps.F.UScnCT);
					m_lvwPSet.SetItemText(ni, 3, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ps.F.UShpCT);
					m_lvwPSet.SetItemText(ni, 4, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FRemPQ()));
					m_lvwPSet.SetItemText(ni, 5, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FPrmPQ()));
					m_lvwPSet.SetItemText(ni, 2, tz);
					break;
				default:
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FOrgPQ());
					m_lvwPSet.SetItemText(ni, 1, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DScnPQ);
					m_lvwPSet.SetItemText(ni, 3, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ps.F.DShpPQ);
					m_lvwPSet.SetItemText(ni, 4, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FRemPQ());
					m_lvwPSet.SetItemText(ni, 5, tz);
					_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FPrmPQ());
					m_lvwPSet.SetItemText(ni, 2, tz);
				}
				break;
			}
		}
	}

	m_edtXOrgXS.SetWindowText(_T("0"));
	m_edtXPrmXS.SetWindowText(_T("0"));
	m_edtXScnXS.SetWindowText(_T("0"));
	m_edtXShpXS.SetWindowText(_T("0"));

	if (1)
	{
		SqlNumeric<10, 2>	pq[5];
		SqlNumeric<10, 2>	sq[5];
		SqlSmallInt			ct[5];

		pq[0] = (double)0.0;
		pq[1] = (double)0.0;
		pq[2] = (double)0.0;
		pq[3] = (double)0.0;
		pq[4] = (double)0.0;
		ct[0] = (short)0;
		ct[1] = (short)0;
		ct[2] = (short)0;
		ct[3] = (short)0;
		ct[4] = (short)0;
		sq[0] = (double)0.0;
		sq[1] = (double)0.0;
		sq[2] = (double)0.0;
		sq[3] = (double)0.0;
		sq[4] = (double)0.0;

		pq[0] = ms.m_PSets.m_PNew.FOrgPQ();
		pq[1] = ms.m_PSets.m_PNew.FPrmPQ();
		pq[2] = (double)0.0;
		pq[3] = (double)0.0;
		pq[4] = ms.m_PSets.m_PNew.FRemPQ();
		sq[0] = ms.DQtySQ(ms.m_PSets.m_PNew.FOrgPQ());
		sq[1] = ms.DQtySQ(ms.m_PSets.m_PNew.FPrmPQ());
		sq[2] = (double)0.0;
		sq[3] = (double)0.0;
		sq[4] = ms.DQtySQ(ms.m_PSets.m_PNew.FRemPQ());
		ct[0] = ms.UQtyCT(ms.m_PSets.m_PNew.FOrgPQ());
		ct[1] = ms.UQtyCT(ms.m_PSets.m_PNew.FPrmPQ());
		ct[2] = (short)0;
		ct[3] = (short)0;
		ct[4] = ms.UQtyCT(ms.m_PSets.m_PNew.FRemPQ());


		for (POSITION x = ms.m_PSets.GetHeadPosition(); x != NULL; ms.m_PSets.GetNext(x))
		{
			CCustPOrdMSetPSet&		ps = ms.m_PSets.Get(x);

			switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
			{
			case IDC_OPT_SUOM:
				sq[0] = (double)sq[0] + ms.DQtySQ(ps.FOrgPQ());
				sq[1] = (double)sq[1] + ms.DQtySQ(ps.FPrmPQ());
				sq[2] = (double)sq[2] + (double)ps.F.DScnSQ;
				sq[3] = (double)sq[3] + (double)ps.F.DShpSQ;
				sq[4] = (double)sq[4] + ms.DQtySQ(ps.FRemPQ());
				break;
			case IDC_OPT_UUOM:
				ct[0] = (short)ct[0] + ms.UQtyCT(ps.FOrgPQ());
				ct[1] = (short)ct[1] + ms.UQtyCT(ps.FPrmPQ());
				ct[2] = (short)ct[2] + (short)ps.F.UScnCT;
				ct[3] = (short)ct[3] + (short)ps.F.UShpCT;
				ct[4] = (short)ct[4] + ms.UQtyCT(ps.FRemPQ());
				break;
			default:
				pq[0] = (double)pq[0] + ps.FOrgPQ();
				pq[1] = (double)pq[1] + ps.FPrmPQ();
				pq[2] = (double)pq[2] + (double)ps.F.DScnPQ;
				pq[3] = (double)pq[3] + (double)ps.F.DShpPQ;
				pq[4] = (double)pq[4] + ps.FRemPQ();
			}
		}
		switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)sq[0]);
			m_edtXOrgXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)sq[1]);
			m_edtXPrmXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)sq[2]);
			m_edtXScnXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)sq[3]);
			m_edtXShpXS.SetWindowText(tz);
			break;
		case IDC_OPT_UUOM:
			_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ct[0]);
			m_edtXOrgXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ct[1]);
			m_edtXPrmXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ct[2]);
			m_edtXScnXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%d"), (short)ct[3]);
			m_edtXShpXS.SetWindowText(tz);
			break;
		default:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)pq[0]);
			m_edtXOrgXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)pq[1]);
			m_edtXPrmXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)pq[2]);
			m_edtXScnXS.SetWindowText(tz);
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)pq[3]);
			m_edtXShpXS.SetWindowText(tz);
		}
	}
	if (we == FALSE)
	{
		m_lvwPSet.EnableWindow(0);
	}
}

void CCustPOrdDlg::ShowALogList(LONG pos)
{
	if (x_MSet == NULL)
		return;

	HRESULT			hr			= S_OK;
	TCHAR			tz[265];	memset(tz, 0, sizeof(tz));
	int				ni			= 0;
	POSITION		xM			= x_MSet;
	CCustPOrdMSet&	ms			= m_POrd.m_MSets.GetAt(xM);
	POSITION		xP			= ms.x_PSet;
	LVCOLUMN		lc;			memset(&lc, 0, sizeof(LVCOLUMN));
	TCHAR			dd[11];		memset(dd, 0, sizeof(dd));
	TCHAR			sd[11];		memset(sd, 0, sizeof(sd));

	if (pos == -1)
	{
		lc.cchTextMax = 255;
		lc.pszText = &tz[0];
		lc.mask = LVCF_TEXT;

		m_lvwALog.DeleteAllItems();
		m_edtCmntSZ.SetWindowText(_T(""));

		switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			_tcscpy_s<_countof(tz)>(tz, _T("PAdj SQ"));
			m_lvwALog.SetColumn(2, &lc);
			break;
		case IDC_OPT_UUOM:
			_tcscpy_s<_countof(tz)>(tz, _T("UAdj CT"));
			m_lvwALog.SetColumn(2, &lc);
			break;
		default:
			_tcscpy_s<_countof(tz)>(tz, _T("PAdj PQ"));
			m_lvwALog.SetColumn(2, &lc);
		}

		for (LONG iA = 0; iA < ms.cALog; iA++)
		{
			_tcsncpy_s<_countof(tz)>(tz, (LPCTSTR)ms.pALog[iA].ALogDT, 16);
			m_lvwALog.InsertItem(iA, tz);

			m_lvwALog.SetItemData(iA, (DWORD_PTR)iA);

			if (ms.pALog[iA].ALogID == _T("CE"))
			{
				_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)ms.pALog[iA].PDstDT, 10);
				if (ms.pALog[iA].PAdjPQ < (double)0.0)
					_stprintf_s<_countof(tz)>(tz, _T("Create %s decreasing by"), dd);
				else
					_stprintf_s<_countof(tz)>(tz, _T("Create %s increasing by"), dd);
			}
			else if (ms.pALog[iA].ALogID == _T("UE"))
			{
				_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)ms.pALog[iA].PDstDT, 10);
				if (ms.pALog[iA].PAdjPQ < (double)0.0)
					_stprintf_s<_countof(tz)>(tz, _T("Update %s decreasing by"), dd);
				else
					_stprintf_s<_countof(tz)>(tz, _T("Update %s increasing by"), dd);
			}
			else if (ms.pALog[iA].ALogID == _T("CM"))
			{
				_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)ms.pALog[iA].PDstDT, 10);
				_tcsncpy_s<_countof(sd)>(sd, (LPCTSTR)ms.pALog[iA].PSrcDT, 10);
				_stprintf_s<_countof(tz)>(tz, _T("Create %s moving from %s"), dd, sd);
			}
			else if (ms.pALog[iA].ALogID == _T("UM"))
			{
				_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)ms.pALog[iA].PDstDT, 10);
				_tcsncpy_s<_countof(sd)>(sd, (LPCTSTR)ms.pALog[iA].PSrcDT, 10);
				_stprintf_s<_countof(tz)>(tz, _T("Update %s moving from %s"), dd, sd);
			}
			m_lvwALog.SetItemText(iA, 1, tz);

			switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
			{
			case IDC_OPT_SUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ms.pALog[iA].PAdjSQ);
				break;
			case IDC_OPT_UUOM:
				_stprintf_s<_countof(tz)>(tz, _T("%.2f"), (double)ms.pALog[iA].UAdjCT);
				break;
			default:
				_stprintf_s<_countof(tz)>(tz, _T("%.0f"), (double)ms.pALog[iA].PAdjPQ);
			}
			m_lvwALog.SetItemText(iA, 2, tz);
		}
	}
}

bool CCustPOrdDlg::Ok2Edt()
{
	return (((Ok2New() == false) && (Ok2Xfr() == false) ? true : false));
}

bool CCustPOrdDlg::InXEdt()
{
	return (((Ok2Edt() == true) && ((m_XAct & XA_NEDT) == XA_NEDT)) ? true : false);
}


bool CCustPOrdDlg::Ok2New()
{
	// NOTES:
	// - Really need to convert this to declaration instead of query
	//   so that if what's passed in && what's determined configure
	//   needed dialog controls
	// - EX: Ok2New(true) should enable dtpPDstDT and disable PAdjXQ
	// - Return value should be what's determined in case query still needed

	bool ok = false;

	if (x_MSet != NULL)
	{
		SYSTEMTIME		sd;	memset(&sd, 0, sizeof(SYSTEMTIME));
		SYSTEMTIME		dd;	memset(&dd, 0, sizeof(SYSTEMTIME));
		CCustPOrdMSet&	ms	= m_POrd.m_MSets.GetAt(x_MSet);
		UINT			cs	= ((ms.x_PSrc == NULL) ? ((ms.x_PDst == NULL) ? 0 : 1) : 2);

		if (cs == 1)
		{
			if (m_dtpPSrcDT.GetTime(&sd) == GDT_NONE)
			{
				if (m_dtpPDstDT.GetTime(&dd) == GDT_VALID)
				{
					if ((ms.m_PSets.x_PNew == ms.x_PDst) && ((ms.FindPSet(m_dtpPDstDT) == ms.m_PSets.x_PNew) || (ms.FindPSet(m_dtpPDstDT) == NULL)))
					{
						ok = true;
					}
				}
			}
		}
	}

	return (ok);
}

bool CCustPOrdDlg::InXNew() 
{
	return (((m_XAct & XA_NNEW) == XA_NNEW) ? true : false);
}

bool CCustPOrdDlg::Ok2Xfr()
{
	//
	// IDC_BTN_NEW, IDC_BTN_XFR & IDC_EDIT_PADJXQ enable mutually exclusively
	// - All calls to these controls' EnableWindow MUST use these
	//
	bool ok	= false;

	if (x_MSet != NULL)
	{
		SYSTEMTIME		sd;	memset(&sd, 0, sizeof(SYSTEMTIME));
		SYSTEMTIME		dd;	memset(&dd, 0, sizeof(SYSTEMTIME));
		CCustPOrdMSet&	ms	= m_POrd.m_MSets.GetAt(x_MSet);
		UINT			cs	= ((ms.x_PSrc == NULL) ? ((ms.x_PDst == NULL) ? 0 : 1) : 2);

		if (cs == 2)
		{
			if (m_dtpPSrcDT.GetTime(&sd) == GDT_VALID)
			{
				if (m_dtpPDstDT.GetTime(&dd) == GDT_VALID)
				{
					if ((ms.FindPSet(m_dtpPDstDT) != NULL) && (ms.FindPSet(m_dtpPSrcDT) != NULL))
					{
						if ((ms.m_PSets.x_PNew == ms.x_PDst) && (Ok2New() == true))
						{
							ok = true;
						}
						else if (ms.m_PSets.x_PNew != ms.x_PDst)
						{
							ok = true;
						}
					}
				}
			}
		}
	}

	return (ok);
}
bool CCustPOrdDlg::InXXfr()
{
	return (((m_XAct & XA_NXFR) == XA_NXFR) ? true : false);
}

int CCustPOrdDlg::MSetXActOK(CCustPOrdMSet& ms)
{
	// XActOK returns
	// -1: NOOP, user entered no quantity
	//  0: FAIL
	//  1: PASS
	TCHAR	tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR	dd[11];		memset(dd, 0, sizeof(dd));
	TCHAR	ds[11];		memset(ds, 0, sizeof(ds));
	TCHAR	um[9];		memset(um, 0, sizeof(um));
	LPMATL	pm			= MatlLRR(ms.MatlID);

	_tcscpy_s<_countof(um)>(um, (LPCTSTR)pm->PQtyUID);

	if (ms.InXAct() == 1)
	{
		// PDst validation/confirmation
		if (ms.x_PDst != NULL)
		{
			CCustPOrdMSetPSet&	pd	= ms.m_PSets.Get(ms.x_PDst);

			// Is PDst New?
			if (ms.x_PDst == ms.m_PSets.x_PNew)
			{
				if (pd.FPrmPQ() == 0.0)
				{
					return (-1);
				}
				else if (pd.F.PrmdDT == SqlNull)
				{
					_stprintf_s<_countof(tz)>(tz, _T("[%s] has no destination promise date!"), (LPCTSTR)ms.MatlID);
					::MessageBox(m_hWnd, tz, _T("Unable to add date"), MB_ICONEXCLAMATION | MB_OK);
					return (0);
				}
				else if ((ms.FindPSet((SYSTEMTIME)pd.F.PrmdDT) != NULL) && (ms.FindPSet((SYSTEMTIME)pd.F.PrmdDT) != ms.m_PSets.x_PNew))
				{
					_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)pd.F.PrmdDT, 10);
					_stprintf_s<_countof(tz)>(tz, _T("[%s] already has promise date [%s]!"), (LPCTSTR)ms.MatlID, dd);
					::MessageBox(m_hWnd, tz, _T("Unable to add date"), MB_ICONEXCLAMATION | MB_OK);
					return (0);
				}
			}

			if (pd.FPrmPQ() < pd.PMinPQ())
			{
				_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)pd.F.PrmdDT, 10);
				_stprintf_s<_countof(tz)>(tz, _T("For [%s], promised amount on [%s] must be >= [%.0f] [%s]"), (LPCTSTR)ms.MatlID, dd, pd.PMinPQ(), um);
				::MessageBox(m_hWnd, tz, _T("Unable to change date"), MB_ICONEXCLAMATION | MB_OK);
				return (0);				
			}
			else if (ms.MRemPQ() < 0.0)
			{
				_stprintf_s<_countof(tz)>(tz, _T("For [%s], promised amount is [%.0f] [%s]\nless than you have scheduled for delivery.\n\nContinue anyway?"), (LPCTSTR)ms.MatlID, ((double)-1.0 * ms.MRemPQ()), um);
				if (::MessageBox(m_hWnd, tz, _T("Confirm OK to overship PO (OSPO)"), MB_ICONEXCLAMATION | MB_YESNO) == IDNO)
				{
					return (-1);
				}
			}

			// PSrc validation/confirmation
			if (ms.x_PSrc != NULL)
			{
				CCustPOrdMSetPSet&	ps	= ms.m_PSets.Get(ms.x_PSrc);
				double				ma	= 0.0;

				if (ps.FPrmPQ() < ps.PMinPQ())
				{
					_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)pd.F.PrmdDT, 10);
					_tcsncpy_s<_countof(ds)>(ds, (LPCTSTR)ps.F.PrmdDT, 10);

					ma = ((double)-1.0 * ps.PAdjPQ()) + ps.FPrmPQ() - ps.PMinPQ();
					
					_stprintf_s<_countof(tz)>(
						tz, 
						_T("For [%s], promised amount remaining on [%s] after move to [%s] must be >= [%.0f] [%s].\nWould you like to move only [%.0f] [%s] instead?"),
						(LPCTSTR)ms.MatlID,
						ds, 
						dd, 
						ps.PMinPQ(), 
						um,
						ma,
						um
					);
					if (::MessageBox(m_hWnd, tz, _T("Unable to move this amount. OK to change (Y/N)?"), MB_ICONEXCLAMATION | MB_YESNO) == IDYES)
					{
						ms.DoMove(ps, pd, SqlNumeric<9, 2>(ps.PAdjPQ() - ma));
					}
					else
					{
						ms.UnMove(ps, pd);
						return (-1);
					}
				}
			}
		}
		else
		{
			return (-1);
		}
	}
	
	return (1);
}

int CCustPOrdDlg::MSetDoXAct(CCustPOrdMSet& ms)
{
	TCHAR	tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR	cz[256];	memset(cz, 0, sizeof(cz));
	TCHAR	dd[11];		memset(dd, 0, sizeof(dd));
	TCHAR	ds[11];		memset(ds, 0, sizeof(ds));
	TCHAR	um[9];		memset(um, 0, sizeof(um));
	LPMATL	pm			= MatlLRR(ms.MatlID);
	double	pq			= 0.0;

	if (ms.InXAct() == 1)
	{
		if (ms.x_PDst != NULL)
		{
			CCustPOrdMSetPSet&	pd = ms.m_PSets.Get(ms.x_PDst);

			// Sum Adjustments
			for (POSITION x = pd.m_PAdjs.GetHeadPosition(); x != NULL; pd.m_PAdjs.GetNext(x))
			{
				CCustPOrdMSetPSetPAdj&	pa	= pd.m_PAdjs.GetAt(x);

				if (pd.m_PKNo == pa.m_PKNo)
				{
					pq += (double)pa.PAdjPQ;
				}
			}

			// New?
			if (ms.x_PDst == ms.m_PSets.x_PNew)
			{
				CCustPOrdMSetPSet		ni;
				CCustPOrdMSetPSetPAdj&	pa	= pd.m_PAdjs.GetAt(ms.x_ADst);
				POSITION				xp	= NULL;

				ni.m_PKNo	= pd.m_PKNo;
				ni.m_Orig	= pd.m_Orig;
				ni.CustID	= ms.CustID;
				ni.MatlID	= ms.MatlID;
				ni.F.StatID = (BYTE)0x00;
				ni.F.CustPO	= m_POrd.CustPO;
				ni.F.IsOrig	= ms.IsOrig();
				ni.F.Active	= (BYTE)1;
				ni.F.PrmdDT = pd.F.PrmdDT;
				ni.F.UPrmCT = (short)0;							// ms.UQtyCT(pd.FPrmPQ());
				ni.F.PPrmPQ = (double)0.0;						// pd.FPrmPQ();
				ni.F.PPrmSQ = (double)0.0;						// ms.DQtySQ(pd.FPrmPQ());
				ni.m_DBOp	= CCustPOrdMSetPSet::DB_INSERT;

				ni.m_PAdjs.AddTailList(&pd.m_PAdjs);

				for (xp = ms.m_PSets.GetHeadPosition(); xp != NULL; ms.m_PSets.GetNext(xp))
				{
					CCustPOrdMSetPSet&	px = ms.m_PSets.GetAt(xp);

					if (ni.F.PrmdDT < px.F.PrmdDT)
					{
						ms.m_PSets.InsertBefore(xp, CCustPOrdMSetPSet(ni));
						break;
					}
				}
				if (xp == NULL)
				{
					ms.m_PSets.AddTail(CCustPOrdMSetPSet(ni));
				}

				pd.m_PAdjs.RemoveAll();

				pd.F.PrmdDT = SqlNull;
				pd.F.PPrmPQ = (double)0.0;
			}

			ms.m_XAct = 0;

			ms.x_ADst = (POSITION)NULL;
			ms.x_ASrc = (POSITION)NULL;
			
			ShowMatlList(x_MSet);
		}
	}

	return (1);
}

// CCustPOrd message handlers

BOOL CCustPOrdDlg::OnInitDialog()
{
	HRESULT			hr			= S_OK;
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	SYSTEMTIME		st;			memset(&st, 0, sizeof(SYSTEMTIME)); ::GetLocalTime(&st);	// p_2Day->GetAsSystemTime(st);

	CDialog::OnInitDialog();

	if (p_Cust == NULL)
	{
		AfxMessageBox(_T("No Customer!"), MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
		return (FALSE);
	}
	if (p_POrd == NULL)
	{
		AfxMessageBox(_T("No Customer Purchase Order!"), MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
		return (FALSE);
	}

	// Reset UI
	m_dtpCrtdDT.SetFormat(_T(" yyyy/MM/dd"));
	m_dtpCrtdDT.SetTime(p_2Day);
	m_dtpOpndDT.SetFormat(_T("yyyy/MM/dd"));
	m_dtpOpndDT.SetTime(p_2Day);
	m_dtpClsdDT.SetFormat(_T("yyyy/MM/dd"));
	m_dtpClsdDT.SetTime((LPSYSTEMTIME)NULL);

	m_lvwMatl.DeleteAllItems();
	for (int i = 0, c = m_lvwMatl.GetHeaderCtrl()->GetItemCount(); i < c; i++) 
	{
		m_lvwMatl.DeleteColumn(0);
	}

	m_tabPOrd.DeleteAllItems();
	m_tabPOrd.InsertItem(0, _T("Transfers"));
	m_tabPOrd.InsertItem(1, _T("Audit Log"));

	m_tabPOrd.SetCurSel(0);

	for (int i = 0, c = m_lvwPSet.GetHeaderCtrl()->GetItemCount(); i < c; i++) 
	{
		m_lvwPSet.DeleteColumn(0);
	}

	// Setup UI
	m_edtCustID.SetWindowTextW((LPCTSTR)p_Cust->CustID);
	m_edtCustSZ.SetWindowTextW((LPCTSTR)p_Cust->CustName);
	m_edtCustPO.SetLimitText(15);

	// lvwMatl
	// MatlID PartID			   XOrdXQ XRemXQ
	//    125    113				   56     56
	//                             XOrdXS XRemXS
	//
	// lvwPSet
	// PrmdDT XOrgXQ XScnXQ XShpXQ XPrmXQ XRemXQ
	//     66     62     55     55     56     56
	//        XOrgXS XScnXS XShpXS XPrmXS 

	m_lvwMatl.SetExtendedStyle(m_lvwMatl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_INFOTIP);
	if (m_Col1 == 0)
	{
		m_lvwMatl.InsertColumn(0, _T("Matl ID"), LVCFMT_LEFT, 155, -1);
	}
	else
	{
		m_lvwMatl.InsertColumn(0, _T("Styl ID"), LVCFMT_LEFT, 155, -1);
	}
	m_lvwMatl.InsertColumn(1, _T("Part ID"), LVCFMT_LEFT, 100,  1);
	m_lvwMatl.InsertColumn(2, _T("POrd PQ"), LVCFMT_RIGHT, 55,  2);
	m_lvwMatl.InsertColumn(3, _T("PRem PQ"), LVCFMT_RIGHT, 56,  3);

	m_lvwMatl.AttachRimCtrl(m_edtCMPrce.m_hWnd);
	m_lvwMatl.AttachRimCtrl(m_edtSAPrce.m_hWnd);

	GetDlgItem(IDC_FRA_PRCE)->SetWindowTextW(_T("Price ($)"));
	m_edtCMPrce.SetWindowText(_T(""));
	m_edtCMPrce.EnableWindow(0);
	m_edtCMPrce.SetLimitText(7);
	m_edtSAPrce.SetWindowText(_T(""));
	m_edtSAPrce.EnableWindow(0);
	m_edtSAPrce.SetLimitText(7);
	GetDlgItem(IDC_LBL_SAPRCE)->ShowWindow((p_Cust->SAgt.SAgtID == (LPCTSTR)_T("0")) ? SW_SHOW : SW_HIDE);
	m_edtSAPrce.ShowWindow((p_Cust->SAgt.SAgtID == (LPCTSTR)_T("0")) ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_LBL_PORDXQ)->SetWindowTextW(_T(""));
	m_edtPOrdXQ.SetWindowText(_T(""));
	m_edtPOrdXQ.SetLimitText(12);

	((CButton*)GetDlgItem(IDC_OPT_PUOM))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_OPT_PUOM))->SetWindowTextW(_T(""));
	((CButton*)GetDlgItem(IDC_OPT_SUOM))->SetWindowTextW(_T(""));
	((CButton*)GetDlgItem(IDC_OPT_UUOM))->SetWindowTextW(_T(""));

	m_lvwPSet.SetExtendedStyle(m_lvwPSet.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_lvwPSet.InsertColumn(0, _T("Prmd DT"), LVCFMT_LEFT,  78, -1);
	m_lvwPSet.InsertColumn(1, _T("POrg PQ"), LVCFMT_RIGHT, 62,  1);
	m_lvwPSet.InsertColumn(2, _T("PPrm PQ"), LVCFMT_RIGHT, 56,  2);
	m_lvwPSet.InsertColumn(3, _T("DScn PQ"), LVCFMT_RIGHT, 55,  3);
	m_lvwPSet.InsertColumn(4, _T("DShp PQ"), LVCFMT_RIGHT, 55,  4);
	m_lvwPSet.InsertColumn(5, _T("PRem PQ"), LVCFMT_RIGHT, 56,  5);
	m_lvwPSet.InsertColumn(6, _T("#"), LVCFMT_RIGHT, 28,  6);

	m_lvwPSet.AttachRimCtrl(m_edtPAdjXQ.m_hWnd);

	m_lvwMatl.AttachHubCtrl(m_lvwPSet.m_hWnd);

	((CButton*)GetDlgItem(IDC_BTN_NEW))->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NEW_DATE)));
	((CButton*)GetDlgItem(IDC_BTN_XFR))->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_XFR_DATE)));
	((CButton*)GetDlgItem(IDC_BTN_UNDO))->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_UNDO)));
	((CButton*)GetDlgItem(IDC_BTN_SAVE))->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SAVE)));
	GetDlgItem(IDC_BTN_NEW)->EnableWindow(Ok2New());
	GetDlgItem(IDC_BTN_XFR)->EnableWindow(Ok2Xfr());
	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(0);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(0);

	GetDlgItem(IDC_FRA_XFER)->SetWindowText(_T("Ship"));
	m_dtpPDstDT.SetFormat(_T(" yyyy/MM/dd"));
	m_dtpPDstDT.SetTime(p_2Day);
	m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);
	m_dtpPDstDT.EnableWindow(0);
	m_dtpPSrcDT.SetFormat(_T(" yyyy/MM/dd"));
	m_dtpPSrcDT.SetTime(p_2Day);
	m_dtpPSrcDT.SetTime((LPSYSTEMTIME)NULL);
	m_dtpPSrcDT.EnableWindow(0);
	m_edtPAdjXQ.SetWindowText(_T(""));
	m_edtPAdjXQ.SetReadOnly(0);
	m_edtPAdjXQ.SetLimitText(12);

	m_lvwALog.SetExtendedStyle(m_lvwALog.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_lvwALog.InsertColumn(0, _T("ALog DT"), LVCFMT_LEFT,  98, -1);
	m_lvwALog.InsertColumn(1, _T("ALog ID"), LVCFMT_LEFT, 236,  1);
	m_lvwALog.InsertColumn(2, _T("PAdj PQ"), LVCFMT_RIGHT, 54,  2);
//	m_lvwALog.InsertColumn(3, _T("User ID"), LVCFMT_RIGHT, 85,  3);
//	m_lvwALog.InsertColumn(4, _T("WStn ID"), LVCFMT_RIGHT, 85,  4);

	m_lvwALog.InsertItem(0, _T("2018/12/32 09:14"));
	m_lvwALog.SetItemText(0, 1, _T("Create 2018/12/31 moving from 2018/12/31"));
	m_lvwALog.SetItemText(0, 2, _T("80"));
//	m_lvwALog.SetItemText(0, 3, _T("kefenters"));
//	m_lvwALog.SetItemText(0, 4, _T("latitudee6540"));

	m_lvwALog.ShowWindow(SW_HIDE);
	m_edtCmntSZ.ShowWindow(SW_HIDE);

	ShowMatlList();

	switch (m_Task)
	{
	case NODEMENU_INSERT:
		m_edtCustPO.SetReadOnly(0);
		m_dtpCrtdDT.SetTime(&st); m_POrd.CrtdDT = st;
		m_dtpOpndDT.SetTime(&st); m_POrd.OpndDT = st;

		SetWindowTextW(_T("Customer Purchase Order : Create"));
		break;

	default:
		m_edtCustPO.SetWindowTextW((LPCTSTR)m_POrd.CustPO); m_edtCustPO.SetReadOnly(1);
		m_dtpCrtdDT.SetTime((LPSYSTEMTIME)m_POrd.CrtdDT);
		m_dtpOpndDT.SetTime((LPSYSTEMTIME)m_POrd.OpndDT);

		if (m_POrd.ClsdDT == SqlNull)
			m_dtpClsdDT.SetTime((LPSYSTEMTIME)NULL);
		else
			m_dtpClsdDT.SetTime((LPSYSTEMTIME)m_POrd.ClsdDT);
		m_dtpClsdDT.EnableWindow(1);

		switch (m_Task)
		{
		case NODEMENU_UPDATE:
		case NODEMENU_BROWSE:
			SetWindowTextW(_T("Customer Purchase Order : Update"));
			break;
		case NODEMENU_DELETE:
			SetWindowTextW(_T("Customer Purchase Order : Delete"));
			break;
		}
		break;
	}

	// On first call, check p_MSet->MatlID match to auto-select
	if (p_MSet != NULL)
	{
		for (int i = 0, c = m_lvwMatl.GetItemCount(); i < c; i++)
		{
			POSITION		xM = (POSITION)m_lvwMatl.GetItemData(i);
			CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(xM);

			if (p_MSet->MatlID == (LPCTSTR)ms.MatlID)
			{
				m_lvwMatl.EnsureVisible(i, FALSE);
				m_lvwMatl.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
				m_lvwMatl.SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
				p_MSet = NULL;
				break;
			}
		}
	}

#ifdef _DEBUG
	{
	RECT	rc;	
	
	GetWindowRect(&rc);
	AfxTrace(_T("IDD_DLG_PORD	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_LVW_ALOG)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_LVW_ALOG	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_EDT_CMNTSZ)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_EDT_CMNTSZ	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_FRA_MATL)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_FRA_MATL	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	m_lvwMatl.GetWindowRect(&rc);
	AfxTrace(_T("IDC_LVW_MSET	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_EDT_XORDXS)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_EDT_XORDXS	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_TAB_PORD)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_TAB_PORD	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	m_lvwPSet.GetWindowRect(&rc);
	AfxTrace(_T("IDC_LVW_PSET	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_EDT_XORGXS)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_EDT_XORGXS	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_BTN_NEW)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_BTN_NEW	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_BTN_XFR)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_BTN_XFR	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_BTN_UNDO)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_BTN_UNDO	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_BTN_SAVE)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_BTN_SAVE	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_FRA_XFER)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_FRA_XFER	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_LBL_PSRC)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_LBL_PSRC	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_DTP_PSRCDT)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_DTP_PSRCDT	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_LBL_PDST)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_LBL_PDST	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_DTP_PDSTDT)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_DTP_PDSTDT	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_LBL_OPER)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_LBL_OPER	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);

	GetDlgItem(IDC_EDT_PADJXQ)->GetWindowRect(&rc);
	AfxTrace(_T("IDC_EDT_PADJXQ	(fwSide=%d, t=%d, l=%d, b=%d, r=%d\n"), 6, rc.top, rc.left, rc.bottom, rc.right);
	}
#endif

	return (TRUE);
}

void CCustPOrdDlg::OnOK()
{
	HRESULT				hr			= S_OK;
	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				cz[256];	memset(cz, 0, sizeof(cz));
	
	CCustPOrdALogDlg	ad(this, _T("Enter reason(s) for updating PO"), NULL, NULL, 0);

	for (POSITION xm = m_POrd.m_MSets.GetHeadPosition(); xm != NULL; m_POrd.m_MSets.GetNext(xm))
	{
		CCustPOrdMSet&	ms	= m_POrd.m_MSets.GetAt(xm);

		if (ms.InXAct() == 1)
		{
			_stprintf_s<_countof(tz)>(tz, _T("[%s] has an open transaction to complete"), (LPCTSTR)ms.MatlID);
			AfxMessageBox(tz, MB_ICONEXCLAMATION | MB_OK);
			return;
		}
		else
		{
			for (POSITION xp = ms.m_PSets.GetHeadPosition(); xp != NULL; ms.m_PSets.GetNext(xp))
			{
				CCustPOrdMSetPSet&	ps = ms.m_PSets.GetAt(xp);
				TCHAR				dd[11];		memset(dd, 0, sizeof(dd));
				TCHAR				ds[11];		memset(ds, 0, sizeof(ds));
				TCHAR				um[9];		memset(um, 0, sizeof(um));
				double				pq			= 0.0;

				_tcsncpy_s<_countof(dd)>(dd, (LPCTSTR)ps.F.PrmdDT, 10);

				for (POSITION xa = ps.m_PAdjs.GetHeadPosition(); xa != NULL; ps.m_PAdjs.GetNext(xa))
				{
					CCustPOrdMSetPSetPAdj&	pa = ps.m_PAdjs.GetAt(xa);
					
					if (ps.m_PKNo == pa.m_PKNo)
					{
						pq += (double)pa.PAdjPQ;
					}
				}

				for (POSITION xa = ps.m_PAdjs.GetHeadPosition(); xa != NULL; ps.m_PAdjs.GetNext(xa))
				{
					CCustPOrdMSetPSetPAdj&	pa	= ps.m_PAdjs.GetAt(xa);
					SqlDateTime				dt;

					if ((pa.m_DBOp & CCustPOrdMSetPSetPAdj::DB_ADJQTY) == CCustPOrdMSetPSetPAdj::DB_ADJQTY)
					{
						// Setup for ALog
						if (ps.F.PrmdIX == SqlNull)
						{
							// CREATE
							if (ps.m_PKNo == pa.m_PKNo)
							{
								// EDIT
								switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
								{
								case IDC_OPT_SUOM:
									GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. EDIT to [%.0f] %s"), (LPCTSTR)ms.MatlID, dd, ms.DQtySQ(pq), um);
									break;
								case IDC_OPT_UUOM:
									GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. EDIT to [%d] %s"), (LPCTSTR)ms.MatlID, dd, ms.UQtyCT(pq), um);
									break;
								default:
									GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. EDIT to [%.0f] %s"), (LPCTSTR)ms.MatlID, dd, pq, um);
								}
							}
							else if ((pa.PAdjPQ > (double)0.0) && (ms.m_PSets.PKToDT(pa.m_PKNo, dt)))
							{
								_tcsncpy_s<_countof(ds)>(ds, (LPCTSTR)dt, 10);

								// MOVE (Src->Dst)
								switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
								{
								case IDC_OPT_SUOM:
									GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.DQtySQ((double)pa.PAdjPQ), um, ds, dd);
									break;
								case IDC_OPT_UUOM:
									GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. MOVE [%d] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.UQtyCT((double)pa.PAdjPQ), um, ds, dd);
									break;
								default:
									GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, (double)pa.PAdjPQ, um, ds, dd);
								}
							}
							else if ((pa.PAdjPQ < (double)0.0) && (ms.m_PSets.PKToDT(pa.m_PKNo, dt)))
							{
								_tcsncpy_s<_countof(ds)>(ds, (LPCTSTR)dt, 10);

								// MOVE (Src<-Dst)
								switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
								{
								case IDC_OPT_SUOM:
									GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.DQtySQ((double)pa.PAdjPQ), um, dd, ds);
									break;
								case IDC_OPT_UUOM:
									GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. MOVE [%d] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.UQtyCT((double)pa.PAdjPQ), um, dd, ds);
									break;
								default:
									GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: CREATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, (double)pa.PAdjPQ, um, dd, ds);
								}
							}
						}
						else
						{
							// UPDATE
							if (ps.m_PKNo == pa.m_PKNo)
							{
								// EDIT
								switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
								{
								case IDC_OPT_SUOM:
									GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. EDIT to [%.0f] %s"), (LPCTSTR)ms.MatlID, dd, ms.DQtySQ(pq), um);
									break;
								case IDC_OPT_UUOM:
									GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. EDIT to [%.0f] %s"), (LPCTSTR)ms.MatlID, dd, ms.UQtyCT(pq), um);
									break;
								default:
									GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. EDIT to [%.0f] %s"), (LPCTSTR)ms.MatlID, dd, pq, um);
								}
							}
							else if ((pa.PAdjPQ > (double)0.0) && (ms.m_PSets.PKToDT(pa.m_PKNo, dt)))
							{
								_tcsncpy_s<_countof(ds)>(ds, (LPCTSTR)dt, 10);

								// MOVE (Src->Dst)
								switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
								{
								case IDC_OPT_SUOM:
									GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.DQtySQ((double)pa.PAdjPQ), um, ds, dd);
									break;
								case IDC_OPT_UUOM:
									GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.UQtyCT((double)pa.PAdjPQ), um, ds, dd);
									break;
								default:
									GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, (double)pa.PAdjPQ, um, ds, dd);
								}
							}
							else if ((pa.PAdjPQ < (double)0.0) && (ms.m_PSets.PKToDT(pa.m_PKNo, dt)))
							{
								_tcsncpy_s<_countof(ds)>(ds, (LPCTSTR)dt, 10);

								// MOVE (Src<-Dst)
								switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
								{
								case IDC_OPT_SUOM:
									GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.DQtySQ((double)pa.PAdjPQ), um, dd, ds);
									break;
								case IDC_OPT_UUOM:
									GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. MOVE [%d] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, ms.UQtyCT((double)pa.PAdjPQ), um, dd, ds);
									break;
								default:
									GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
									_stprintf_s<_countof(tz)>(tz, _T("[%s]: UPDATE [%s]. MOVE [%.0f] %s from [%s] to [%s]"), (LPCTSTR)ms.MatlID, dd, (double)pa.PAdjPQ, um, dd, ds);
								}
							}
						}

						ad.AddActn(tz);
					}
				}
			}
		}
	}

	if (m_Task == NODEMENU_INSERT)
	{
		if (m_POrd.CustPO == SqlNull)
		{
			::MessageBox(m_hWnd, _T("Please enter a Customer PO to create"), _T("Cannot create PO"), MB_ICONEXCLAMATION);
			return;
		}
	}
	else if (m_Task == NODEMENU_UPDATE)
	{
		if (ad.DoModal() != IDOK)
		{
			EndDialog(IDCANCEL);
			return;
		}
	}

	// Sequence
	//
	if (SUCCEEDED(hr = ((CPAIFMainApp*)AfxGetApp())->dbc.StartTransaction()))
	{
		CSrvrDateLookup		sd;

		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(hr = sd.Lookup(((CPAIFMainApp*)AfxGetApp())->dbc)))
			{
				sd.Close();
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::Insert
			if (m_Task == NODEMENU_INSERT)
			{
				CCustPOrdInsert		poi;

				poi.rec.CustID = m_POrd.CustID;
				poi.rec.CustPO = m_POrd.CustPO;
				poi.rec.CrtdDT = m_POrd.CrtdDT;
				poi.rec.OpndDT = m_POrd.OpndDT;
				poi.rec.ClsdDT = m_POrd.ClsdDT;

				if (SUCCEEDED(hr = poi.Insert(((CPAIFMainApp*)AfxGetApp())->dbc)))
				{
					poi.Close();
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::MSet::Inserts
			for (POSITION x = m_POrd.m_MSets.GetHeadPosition(); x != NULL; m_POrd.m_MSets.GetNext(x))
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x);

				ms.F.CustPO		= m_POrd.CustPO;

				if ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT)
				{
					CCustPOrdMSetDoOptn		mso;

					mso.rec.CustID		= ms.CustID;
					mso.rec.F.CustPO	= ms.F.CustPO;
					mso.rec.MatlID		= ms.MatlID;
					mso.prm.DBOptn		= (LONG)CCustPOrdMSet::DB_INSERT;
					mso.rec.PrceSA		= ms.PrceSA;
					mso.rec.PrceCM		= ms.PrceCM;
					mso.prm.IsOrig		= ms.IsOrig();

					if (SUCCEEDED(hr = mso.DoOptn(((CPAIFMainApp*)AfxGetApp())->dbc)))
					{
						mso.Close();
					}
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::MSet::PSet::Inserts
			for (POSITION x = m_POrd.m_MSets.GetHeadPosition(); x != NULL; m_POrd.m_MSets.GetNext(x))
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x);

				for (POSITION y = ms.m_PSets.GetHeadPosition(); y != NULL; ms.m_PSets.GetNext(y))
				{
					CCustPOrdMSetPSet&	ps = ms.m_PSets.GetAt(y);

					ps.F.CustPO		= ms.F.CustPO;

					if ((ps.m_DBOp & CCustPOrdMSetPSet::DB_INSERT) == CCustPOrdMSetPSet::DB_INSERT)
					{
						CCustPOrdMSetPSetDoOptn	pso;

						pso.rec.CustID		= ps.CustID;
						pso.rec.F.CustPO	= ps.F.CustPO;
						pso.rec.MatlID		= ps.MatlID;
						pso.rec.F.PrmdDT	= ps.F.PrmdDT;
						pso.prm.DBOptn		= (LONG)CCustPOrdMSetPSet::DB_INSERT;
						pso.prm.IsOrig		= ms.IsOrig();
						pso.prm.UserID		= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csUNam;
						pso.prm.WStnID		= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csWStn;

						if (SUCCEEDED(hr = pso.DoOptn(((CPAIFMainApp*)AfxGetApp())->dbc)))
						{
							pso.Close();
						}
					}
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::MSet::PSet::PAdj::AdjQtys
			for (POSITION xm = m_POrd.m_MSets.GetHeadPosition(); xm != NULL; m_POrd.m_MSets.GetNext(xm))
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(xm);

				for (POSITION xp = ms.m_PSets.GetHeadPosition(); xp != NULL; ms.m_PSets.GetNext(xp))
				{
					CCustPOrdMSetPSet&	ps = ms.m_PSets.GetAt(xp);

					for (POSITION xa = ps.m_PAdjs.GetHeadPosition(); xa != NULL; ps.m_PAdjs.GetNext(xa))
					{
						CCustPOrdMSetPSetPAdj&	pa = ps.m_PAdjs.GetAt(xa);

						if ((pa.m_DBOp & CCustPOrdMSetPSetPAdj::DB_ADJQTY) == CCustPOrdMSetPSetPAdj::DB_ADJQTY)
						{
							CCustPOrdMSetPSetDoPAdj	paa;
							SqlDateTime				sdt;

							paa.prm.CustID	= ps.CustID;
							paa.prm.CustPO	= ps.F.CustPO;
							paa.prm.MatlID	= ps.MatlID;
							paa.rec.PrmdDT	= ps.F.PrmdDT;
							paa.prm.DBOptn	= (LONG)CCustPOrdMSetPSetPAdj::DB_ADJQTY;
							paa.prm.IsOrig	= ms.IsOrig();

							// Setup for ALog
							if (ps.F.PrmdIX == SqlNull)
							{
								// CREATE
								if (ps.m_PKNo == pa.m_PKNo)
								{
									// EDIT
									paa.prm.PDstDT	= ps.F.PrmdDT;
									paa.prm.PSrcDT	= SqlNull;
									paa.rec.PAdjPQ	= pa.PAdjPQ;
									paa.prm.ALogID	= _T("CE");
								}
								else if ((pa.PAdjPQ > (double)0.0) && (ms.m_PSets.PKToDT(pa.m_PKNo, sdt)))
								{
									// MOVE (Src->Dst)
									paa.prm.PDstDT	= ps.F.PrmdDT;
									paa.prm.PSrcDT	= sdt;
									paa.rec.PAdjPQ	= pa.PAdjPQ;
									paa.prm.ALogID	= _T("CM");
								}
								else
								{
									// NULL
									paa.prm.PDstDT	= ps.F.PrmdDT;
									paa.prm.PSrcDT	= SqlNull;
									paa.rec.PAdjPQ	= pa.PAdjPQ;
									paa.prm.ALogID	= SqlNull;
								}
							}
							else
							{
								// UPDATE
								if (ps.m_PKNo == pa.m_PKNo)
								{
									// EDIT
									paa.prm.PDstDT	= ps.F.PrmdDT;
									paa.prm.PSrcDT	= SqlNull;
									paa.rec.PAdjPQ	= pa.PAdjPQ;
									paa.prm.ALogID	= _T("UE");
								}
								else if ((pa.PAdjPQ > (double)0.0) && (ms.m_PSets.PKToDT(pa.m_PKNo, sdt)))
								{
									// MOVE (Src->Dst)
									paa.prm.PDstDT	= ps.F.PrmdDT;
									paa.prm.PSrcDT	= sdt;
									paa.rec.PAdjPQ	= pa.PAdjPQ;
									paa.prm.ALogID	= _T("UM");
								}
								else
								{
									// NULL
									paa.prm.PDstDT	= ps.F.PrmdDT;
									paa.prm.PSrcDT	= SqlNull;
									paa.rec.PAdjPQ	= pa.PAdjPQ;
									paa.prm.ALogID	= SqlNull;
								}
							}

							paa.prm.ALogDT	= sd.gdt;
							paa.prm.UserID	= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csUNam;
							paa.prm.WStnID	= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csWStn;
							paa.rec.CmntSZ	= ad.GetCmnt();

							if (SUCCEEDED(hr = paa.DoPAdj(((CPAIFMainApp*)AfxGetApp())->dbc)))
							{
								paa.Close();
							}
						}
					}
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::MSet::PSet::Updates | POrd::MSet::PSet::Deletes
			for (POSITION x = m_POrd.m_MSets.GetHeadPosition(); x != NULL; m_POrd.m_MSets.GetNext(x))
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x);

				for (POSITION y = ms.m_PSets.GetHeadPosition(); y != NULL; ms.m_PSets.GetNext(y))
				{
					CCustPOrdMSetPSet&	ps = ms.m_PSets.GetAt(y);

					ps.F.CustPO		= ms.F.CustPO;

					if ((ps.m_DBOp & CCustPOrdMSetPSet::DB_UPDATE) == CCustPOrdMSetPSet::DB_UPDATE)
					{
						CCustPOrdMSetPSetDoOptn	pso;

						pso.rec.CustID		= ps.CustID;
						pso.rec.F.CustPO	= ps.F.CustPO;
						pso.rec.MatlID		= ps.MatlID;
						pso.rec.F.PrmdDT	= ps.F.PrmdDT;
						pso.prm.DBOptn		= (LONG)CCustPOrdMSetPSet::DB_UPDATE;
						pso.prm.UserID		= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csUNam;
						pso.prm.WStnID		= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csWStn;
						pso.prm.IsOrig		= ms.IsOrig();

						if (SUCCEEDED(hr = pso.DoOptn(((CPAIFMainApp*)AfxGetApp())->dbc)))
						{
							pso.Close();
						}
					}
					else if ((ps.m_DBOp & CCustPOrdMSetPSet::DB_DELETE) == CCustPOrdMSetPSet::DB_DELETE)
					{
						CCustPOrdMSetPSetDoOptn	pso;

						pso.rec.CustID		= ps.CustID;
						pso.rec.F.CustPO	= ps.F.CustPO;
						pso.rec.MatlID		= ps.MatlID;
						pso.rec.F.PrmdDT	= ps.F.PrmdDT;
						pso.prm.DBOptn		= (LONG)CCustPOrdMSetPSet::DB_DELETE;
						pso.prm.UserID		= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csUNam;
						pso.prm.WStnID		= (LPCTSTR)((CPAIFMainApp*)AfxGetApp())->csWStn;
						pso.prm.IsOrig		= ms.IsOrig();

						if (SUCCEEDED(hr = pso.DoOptn(((CPAIFMainApp*)AfxGetApp())->dbc)))
						{
							pso.Close();
						}
					}
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::MSet::Updates | POrd::MSet::Deletes
			for (POSITION x = m_POrd.m_MSets.GetHeadPosition(); x != NULL; m_POrd.m_MSets.GetNext(x))
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x);

				ms.F.CustPO		= m_POrd.CustPO;

				if ((ms.m_DBOp & CCustPOrdMSet::DB_UPDATE) == CCustPOrdMSet::DB_UPDATE)
				{
					CCustPOrdMSetDoOptn		mso;

					mso.rec.CustID		= ms.CustID;
					mso.rec.F.CustPO	= ms.F.CustPO;
					mso.rec.MatlID		= ms.MatlID;
					mso.prm.DBOptn		= (LONG)CCustPOrdMSet::DB_UPDATE;
					mso.rec.PrceSA		= ms.PrceSA;
					mso.rec.PrceCM		= ms.PrceCM;
					mso.prm.IsOrig		= ms.IsOrig();

					if (SUCCEEDED(hr = mso.DoOptn(((CPAIFMainApp*)AfxGetApp())->dbc)))
					{
						mso.Close();
					}
				}
				else if ((ms.m_DBOp & CCustPOrdMSet::DB_DELETE) == CCustPOrdMSet::DB_DELETE)
				{
					CCustPOrdMSetDoOptn		mso;

					mso.rec.CustID		= ms.CustID;
					mso.rec.F.CustPO	= ms.F.CustPO;
					mso.rec.MatlID		= ms.MatlID;
					mso.prm.DBOptn		= (LONG)CCustPOrdMSet::DB_DELETE;
					mso.rec.PrceSA		= ms.PrceSA;
					mso.rec.PrceCM		= ms.PrceCM;
					mso.prm.IsOrig		= ms.IsOrig();

					if (SUCCEEDED(hr = mso.DoOptn(((CPAIFMainApp*)AfxGetApp())->dbc)))
					{
						mso.Close();
					}
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			// POrd::Update | POrd::Delete
			if (m_Task == NODEMENU_UPDATE)
			{
				CCustPOrdUpdate		pou;

				pou.rec.CustID = m_POrd.CustID;
				pou.rec.CustPO = m_POrd.CustPO;
				pou.rec.CrtdDT = m_POrd.CrtdDT;
				pou.rec.OpndDT = m_POrd.OpndDT;
				pou.rec.ClsdDT = m_POrd.ClsdDT;

				if (SUCCEEDED(hr = pou.Update(((CPAIFMainApp*)AfxGetApp())->dbc)))
				{
					pou.Close();
				}
			}
			else if (m_Task == NODEMENU_DELETE)
			{
				CCustPOrdDelete		pod;

				pod.rec.CustID = m_POrd.CustID;
				pod.rec.CustPO = m_POrd.CustPO;

				if (SUCCEEDED(hr = pod.Delete(((CPAIFMainApp*)AfxGetApp())->dbc)))
				{
					pod.Close();
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			((CPAIFMainApp*)AfxGetApp())->dbc.Commit();
		}
		else
		{
			((CPAIFMainApp*)AfxGetApp())->dbc.Abort();
		}
	}

	if (SUCCEEDED(hr))
	{
		CDialog::OnOK();
	}
}

HBRUSH CCustPOrdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	static CBrush wht(RGB(255, 255, 255));

	if (0)
	{
	// Test
	pDC->SetTextColor(RGB(0, 0, 128));
	pDC->SetBkColor(RGB(255, 255, 255));
	return ((HBRUSH)wht);
	}

	// AtlTrace(_T("hCtl:%08X hOwn:%08X\n"), pWnd->m_hWnd, pWnd->m_hWndOwner);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		if ((pWnd->IsKindOf(RUNTIME_CLASS(CEdit))) || (pWnd->IsKindOf(RUNTIME_CLASS(AFXCNTRLLIB::CPSEdit))))
		{
			if ((pWnd->GetStyle() & ES_READONLY) == ES_READONLY)
			{
				pDC->SetTextColor(::GetSysColor(COLOR_INACTIVECAPTIONTEXT));
				pDC->SetBkColor(RGB(255, 255, 255));
				return ((HBRUSH)wht);
			}
			else if (pWnd->IsWindowEnabled())
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 255));
				return ((HBRUSH)wht);
			}
		}
		else if ((pWnd->IsKindOf(RUNTIME_CLASS(CComboBox))) || (pWnd->IsKindOf(RUNTIME_CLASS(AFXCNTRLLIB::CPSComboBox)))		)
		{
			if (pWnd->IsWindowEnabled())
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 255));
				return ((HBRUSH)wht);
			}
		}
		else if ((pWnd->IsKindOf(RUNTIME_CLASS(AFXCNTRLLIB::CPSDateTimeCtrl))))
		{
			if (pWnd->IsWindowEnabled())
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor(RGB(255, 255, 255));
				return ((HBRUSH)wht);
			}
		}
		break;
	}

	// Return default brush
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


void CCustPOrdDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	if ((pRect->right - pRect->left) != 651)
	{
		switch (fwSide)
		{
		case WMSZ_LEFT:
		case WMSZ_TOPLEFT:
		case WMSZ_BOTTOMLEFT:
			pRect->left = pRect->right - 651;
			break;
		case WMSZ_RIGHT:
		case WMSZ_TOPRIGHT:
		case WMSZ_BOTTOMRIGHT:
			pRect->right = pRect->left + 651;
			break;
		}
	}
	if ((pRect->bottom - pRect->top) < 561)
	{
		switch (fwSide)
		{
		case WMSZ_TOP:
		case WMSZ_TOPLEFT:
		case WMSZ_TOPRIGHT:
			pRect->top = pRect->bottom - 561;
			break;
		case WMSZ_BOTTOM:
		case WMSZ_BOTTOMLEFT:
		case WMSZ_BOTTOMRIGHT:
			pRect->bottom = pRect->top + 561;
			break;
		}
	}

	// Top/Bottom Adjustments ONLY
	if (fwSide > 2)
	{
		CDialog::OnSizing(fwSide, pRect);
	
		// Min Height
		if ((pRect->bottom - pRect->top) >= 561)
		{
			CRect	rcM;
			CRect	rcD;
			CRect	rcO;

			m_lvwMatl.GetWindowRect(&rcM);
			m_lvwPSet.GetWindowRect(&rcD);

			if (rcM.Height() >= 272)
			{
				fwSide = fwSide;
			}

			if ((pRect->bottom - pRect->top) < 821)
			{
				GetDlgItem(IDC_LVW_ALOG)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 152; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_LVW_ALOG)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_CMNTSZ)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 152; rcO.bottom = pRect->bottom - 19; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_CMNTSZ)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);

				GetDlgItem(IDC_FRA_MATL)->GetWindowRect(&rcO); rcO.bottom = pRect->bottom - 12; ScreenToClient(&rcO); GetDlgItem(IDC_FRA_MATL)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XORGXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XORGXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XPRMXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XPRMXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XSCNXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XSCNXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XSHPXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XSHPXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_FRA_XFER)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 149; rcO.bottom = pRect->bottom - 55; ScreenToClient(&rcO); GetDlgItem(IDC_FRA_XFER)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_LBL_PSRC)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 126; rcO.bottom = pRect->bottom - 113; ScreenToClient(&rcO); GetDlgItem(IDC_LBL_PSRC)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_DTP_PSRCDT)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 130; rcO.bottom = pRect->bottom - 109; ScreenToClient(&rcO); GetDlgItem(IDC_DTP_PSRCDT)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_LBL_PDST)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 104; rcO.bottom = pRect->bottom - 91; ScreenToClient(&rcO); GetDlgItem(IDC_LBL_PDST)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_DTP_PDSTDT)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 107; rcO.bottom = pRect->bottom - 86; ScreenToClient(&rcO); GetDlgItem(IDC_DTP_PDSTDT)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_LBL_OPER)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 78; rcO.bottom = pRect->bottom - 65; ScreenToClient(&rcO); GetDlgItem(IDC_LBL_OPER)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_PADJXQ)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 81; rcO.bottom = pRect->bottom - 61; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_PADJXQ)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_BTN_NEW)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 144; rcO.bottom = pRect->bottom - 120; ScreenToClient(&rcO); GetDlgItem(IDC_BTN_NEW)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_BTN_XFR)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 120; rcO.bottom = pRect->bottom - 96; ScreenToClient(&rcO); GetDlgItem(IDC_BTN_XFR)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_BTN_UNDO)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 95; rcO.bottom = pRect->bottom - 71; ScreenToClient(&rcO); GetDlgItem(IDC_BTN_UNDO)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_BTN_SAVE)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 71; rcO.bottom = pRect->bottom - 47; ScreenToClient(&rcO); GetDlgItem(IDC_BTN_SAVE)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_LVW_PSET)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 152; rcO.bottom = pRect->bottom - 41; ScreenToClient(&rcO); GetDlgItem(IDC_LVW_PSET)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_TAB_PORD)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 173; rcO.bottom = pRect->bottom - 153; ScreenToClient(&rcO); GetDlgItem(IDC_TAB_PORD)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XORDXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 199; rcO.bottom = pRect->bottom - 179; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XORDXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XREMXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 199; rcO.bottom = pRect->bottom - 179; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XREMXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_LVW_MATL)->GetWindowRect(&rcO); rcO.bottom = pRect->bottom - 201; ScreenToClient(&rcO); GetDlgItem(IDC_LVW_MATL)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
			}
			else
			{
				GetDlgItem(IDC_LVW_ALOG)->GetWindowRect(&rcO); rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_LVW_ALOG)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_CMNTSZ)->GetWindowRect(&rcO); rcO.bottom = pRect->bottom - 19; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_CMNTSZ)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);

				GetDlgItem(IDC_FRA_MATL)->GetWindowRect(&rcO); rcO.bottom = pRect->bottom - 12; ScreenToClient(&rcO); GetDlgItem(IDC_FRA_MATL)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XORGXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XORGXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XPRMXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XPRMXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XSCNXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XSCNXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_EDT_XSHPXS)->GetWindowRect(&rcO); rcO.top = pRect->bottom - 40; rcO.bottom = pRect->bottom - 20; ScreenToClient(&rcO); GetDlgItem(IDC_EDT_XSHPXS)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
				GetDlgItem(IDC_LVW_PSET)->GetWindowRect(&rcO); rcO.bottom = pRect->bottom - 41; ScreenToClient(&rcO); GetDlgItem(IDC_LVW_PSET)->MoveWindow(rcO.left, rcO.top, rcO.Width(), rcO.Height(), 1);
			}
		}
	}
}

void CCustPOrdDlg::OnChangeCustPO()
{
	TCHAR	tz[255];	memset(tz, 0, sizeof(tz));

	if (m_edtCustPO.GetWindowTextLength() > 0)
	{
		m_edtCustPO.GetWindowText(tz, 16);
		m_POrd.CustPO = tz;
	}
	else
	{
		m_POrd.CustPO = SqlNull;
	}
}

void CCustPOrdDlg::OnDateTimeChangeCrtdDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTC = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	switch (pDTC->dwFlags)
	{
	case GDT_NONE:
		m_POrd.CrtdDT = SqlNull;
		break;
	default:
		m_POrd.CrtdDT = pDTC->st;
		break;
	}
	*pResult = 0;
}

void CCustPOrdDlg::OnDateTimeChangeOpndDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTC = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	switch (pDTC->dwFlags)
	{
	case GDT_ERROR:
	case GDT_NONE:
		m_POrd.OpndDT = SqlNull;
		break;
	default:
		m_POrd.OpndDT = pDTC->st;
		break;
	}
	*pResult = 0;
}

void CCustPOrdDlg::OnDateTimeChangeClsdDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTC = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	switch (pDTC->dwFlags)
	{
	case GDT_ERROR:
	case GDT_NONE:
		m_POrd.ClsdDT = SqlNull;
		break;
	default:
		m_POrd.ClsdDT = pDTC->st;
		break;
	}
	*pResult = 0;
}

LRESULT CCustPOrdDlg::VerifyMSetChkState(int iItem, UINT uOldState, UINT uNewState)
{
	POSITION		xm			= NULL;
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR			um[256];	memset(um, 0, sizeof(um));

	if ((iItem <= -1) || (iItem >= m_lvwMatl.GetItemCount()))
		return (1);
	
	if ((xm = (POSITION)m_lvwMatl.GetItemData(iItem)) == NULL)
		return (1);

	CCustPOrdMSet&	ms			= m_POrd.m_MSets.GetAt(xm);
	LPMATL			pm			= MatlLRR(ms.MatlID);

	// Unchecked to Checked
	if (((uOldState & LVIS_CHECKED) != LVIS_CHECKED) && ((uNewState & LVIS_CHECKED) == LVIS_CHECKED))
	{
		// DB_INSERT

		// Absent (STAT) => Insert (DBOP)
		if ((ms.F.StatID == (BYTE)0x00) && ((ms.m_DBOp & (CCustPOrdMSet::DBOP)-1) == CCustPOrdMSet::DB_NULLOP))
		{
			ms.m_DBOp = CCustPOrdMSet::DB_INSERT;
		}
		// Exist (STAT) => Delete (DBOP)
		else if (ms.F.StatID == (BYTE)0x10)
		{
			ms.m_DBOp = CCustPOrdMSet::DB_NULLOP;
		}
		
		// UI
		m_edtPOrdXQ.EnableWindow(1);

		ms.m_PSets.m_PNew.m_Orig = 1;

		ShowPSetList();
		ShowALogList();

		return (0);
	}

	// Checked to Unchecked
	else if (((uOldState & LVIS_CHECKED) == LVIS_CHECKED) && ((uNewState & LVIS_CHECKED) != LVIS_CHECKED))
	{
		if (ms.MMinPQ() > 0.0)
		{
			if (m_POrd.CustPO == SqlNull)
			{
				_stprintf_s<_countof(tz)>(
					tz, 
					_T("Material [%s] cannot be removed from PO [<new>]! [%.0f] %s have been scanned or shipped"), 
					(LPCTSTR)ms.MatlID, ms.MMinPQ(), (LPCTSTR)pm->PQtyUID
				);
			}
			else
			{
				_stprintf_s<_countof(tz)>(
					tz, 
					_T("Material [%s] cannot be removed from PO [%s]! [%.0f] %s have been scanned or shipped"), 
					(LPCTSTR)ms.MatlID, (LPCTSTR)m_POrd.CustPO, ms.MMinPQ(), (LPCTSTR)pm->PQtyUID
				);
			}
			::MessageBox(m_hWnd, tz, _T("Warning"), MB_ICONEXCLAMATION | MB_OK);

			return (1);
		}

		// DB_DELETE

		// Undo All Activity
		ms.PAdjPQ = (double)0.0;

		for (POSITION x = ms.m_PSets.GetHeadPosition(); x != NULL; ms.m_PSets.GetNext(x))
		{
			CCustPOrdMSetPSet&	ps = ms.m_PSets.Get(x);

			ps.m_PAdjs.RemoveAll();

			// Absent (STAT) => NullOp (DBOP)
			if ((ps.F.StatID == (BYTE)0x00) && ((ps.m_DBOp & CCustPOrdMSetPSet::DB_INSERT) == CCustPOrdMSetPSet::DB_INSERT))
			{
				ps.m_DBOp = CCustPOrdMSetPSet::DB_NULLOP;
			}
			// Exist (STAT) => Delete (DBOP)
			else if (ps.F.StatID == (BYTE)0x10)
			{
				ps.m_DBOp = CCustPOrdMSetPSet::DB_DELETE;
			}
		}

		// Absent (STAT) => NullOp (DBOP)
		if ((ms.F.StatID == (BYTE)0x00) && ((ms.m_DBOp & CCustPOrdMSet::DB_INSERT) == CCustPOrdMSet::DB_INSERT))
		{
			ms.m_DBOp = CCustPOrdMSet::DB_NULLOP;
		}
		// Exist (STAT) => Delete (DBOP)
		else if (ms.F.StatID == (BYTE)0x10)
		{
			ms.m_DBOp = CCustPOrdMSet::DB_DELETE;
		}

		m_edtPOrdXQ.SetWindowText(_T(""));
		m_edtPOrdXQ.EnableWindow(0);

		if (m_lvwPSet.GetSelectedCount() > 0)
		{
			for (int i = 0; i < m_lvwPSet.GetItemCount(); i++)
			{
				if (m_lvwPSet.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
				{
					m_lvwPSet.SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);
					break;
				}
			}
		}

		return (0);
	}

	return (1);
}

int CCustPOrdDlg::SelectMSetsForXAct(XACT xa)
{
	// Returns
	// -1 No PDst
	// -2 No PSrc
	//  0 No ListItems
	// +n Number of Selected ListItems
	int				cs	= 1;
	SYSTEMTIME		st;	memset(&st, 0, sizeof(SYSTEMTIME));

	switch (xa)
	{
	case XA_NEDT:
		break;
	
	case XA_NNEW:
		//
		// Check PDst Date
		//
		if (m_dtpPDstDT.GetTime(&st) == GDT_NONE)
		{
			return (-1);
		}
		for (int i = 0, c = m_lvwMatl.GetItemCount(); i < c; i++)
		{
			// LVIS_FOCUSED is Item being assigned the new promise date
			if ((m_lvwMatl.GetItemState(i, LVIS_CHECKED) == LVIS_CHECKED) && (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) != LVIS_FOCUSED))
			{

				POSITION		xm = (POSITION)m_lvwMatl.GetItemData(i);
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(xm);
				POSITION		xp = ms.FindPSet(m_dtpPDstDT);

				if ((xp == NULL) || (xp == ms.m_PSets.x_PNew))
				{
					m_lvwMatl.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					ms.x_PSet = ms.m_PSets.x_PNew;
					ms.x_PDst = ms.m_PSets.x_PNew;
					ms.x_PSrc = (POSITION)NULL;
					ms.m_PSets.m_PNew.F.PrmdDT = (SYSTEMTIME)m_dtpPDstDT;
					cs++;
				}
				else
				{
					m_lvwMatl.SetItemState(i, 0, LVIS_SELECTED);
					ms.x_PSet = (POSITION)NULL;
					ms.x_PDst = (POSITION)NULL;
					ms.x_PSrc = (POSITION)NULL;
					ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
				}
			}
		}
		break;
	
	case XA_NXFR:
		//
		// Check PDst Date, PSrc Date
		//
		if (m_dtpPDstDT.GetTime(&st) == GDT_NONE)
		{
			return (-1);
		}
		if (m_dtpPSrcDT.GetTime(&st) == GDT_NONE)
		{
			return (-2);
		}
		for (int i = 0, c = m_lvwMatl.GetItemCount(); i < c; i++)
		{
			// LVIS_FOCUSED is Item being assigned the to/from promise dates
			if ((m_lvwMatl.GetItemState(i, LVIS_CHECKED) == LVIS_CHECKED) && (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) != LVIS_FOCUSED))
			{
				POSITION		xm = (POSITION)m_lvwMatl.GetItemData(i);
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(xm);
				POSITION		xd = ms.FindPSet(m_dtpPDstDT);
				POSITION		xs = ms.FindPSet(m_dtpPSrcDT);

				if ((xd != NULL) && (xs != NULL))
				{
					m_lvwMatl.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					ms.x_PSet = xd;
					ms.x_PDst = xd;
					ms.x_PSrc = xs;
					if (xd == ms.m_PSets.x_PNew)
					{
						ms.m_PSets.m_PNew.F.PrmdDT = (SYSTEMTIME)m_dtpPDstDT;
					}
					cs++;
				}
				else
				{
					m_lvwMatl.SetItemState(i, 0, LVIS_SELECTED);
					ms.x_PSet = (POSITION)NULL;
					ms.x_PDst = (POSITION)NULL;
					ms.x_PSrc = (POSITION)NULL;
					ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
				}
			}
		}
		break;
	}

	return (cs);
}

LRESULT CCustPOrdDlg::VerifyMSetSelState(int iItem, UINT uOldState, UINT uNewState)
{
	POSITION		xm			= NULL;
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR			um[256];	memset(um, 0, sizeof(um));
	SYSTEMTIME		nd;			memset(&nd, 0, sizeof(SYSTEMTIME));
	SYSTEMTIME		sd;			memset(&sd, 0, sizeof(SYSTEMTIME));
	SYSTEMTIME		dd;			memset(&dd, 0, sizeof(SYSTEMTIME));
	size_t			ct			= 0;

	// We're determining if a listitem in lvwMatl is valid to select if either
	// 1. The user is CTRL+LCLICK an item to select firing OnItemChangingMatl() notification, or
	// 2. We're scrolling list items via f() to auto-select based on criteria

	// NOTE: Must allow for...
	// - No MSet list item focused
	// - No MSet list item selected
	// NOTE: Must rely only on dates m_dtpPSrcDT & m_dtpPDstST
	

	if ((iItem <= -1) || (iItem >= m_lvwMatl.GetItemCount()))
		return (1);
	
	if ((xm = (POSITION)m_lvwMatl.GetItemData(iItem)) == NULL)
		return (1);
	

	CCustPOrdMSet&	ms			= m_POrd.m_MSets.GetAt(xm);
	LPMATL			pm			= MatlLRR(ms.MatlID);

	// Unselected to Selected
	if (((uOldState & LVIS_SELECTED) != LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) == LVIS_SELECTED))
	{
		// Extended style infers checked b/4 selected, if not checked => silent denial
		if (((m_lvwMatl.GetExtendedStyle() & LVS_EX_CHECKBOXES) == LVS_EX_CHECKBOXES) && (m_lvwMatl.GetItemState(iItem, LVIS_CHECKED) != LVIS_CHECKED))
		{
			return (1);
		}

		// Transaction Mode?

		// - NEW (Allow selected only if this material has no matching new promise date)
		// - DST Promise Date in m_dtPDstDT
		if (InXNew() == true)
		{
			return (((ms.FindPSet(m_dtpPDstDT) == NULL) || (ms.FindPSet(m_dtpPDstDT) == ms.m_PSets.x_PNew)) ? 0 : 1);
		}
		// - XFR (Allow selection only if this material has matching source/destination promise dates)
		// - SRC Promise Date in m_dtpPSrcDT
		// - DST Promise Date in m_dtpPDstDT
		else if (InXXfr() == true)
		{
			return (((ms.FindPSet(m_dtpPSrcDT) != NULL) && (ms.FindPSet(m_dtpPDstDT) != NULL)) ? 0 : 1);
		}
		// - UPD
		else
		{
			return (0);
		}
	}
	// Selected to Unselected
	else if (((uOldState & LVIS_SELECTED) == LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) != LVIS_SELECTED))
	{
		if (GetFocus() != NULL)
		{
			if ((GetFocus()->m_hWnd == m_lvwMatl.m_hWnd) && (m_lvwMatl.IsWindowEnabled() == TRUE))
			{
				return (0);
			}
		}
	}

	return (1);
}

void CCustPOrdDlg::OnItemChangingMatl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW	pN			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR			um[256];	memset(um, 0, sizeof(um));
	UINT			is			= 0;

	*pResult = 0;

	AfxTrace(_T("MATL:CHNG [%2d] [%08x] [%08x->%08x]\n"), pN->iItem, pN->uChanged, pN->uOldState, pN->uNewState);

	// New logic
	// - lvwMatl rim controls : CMPrce & SMPrce allows user to VK_UP | VK_DOWN to modify prices
	// - lvwPSet rim controls : PAdjPQ allows user to VK_UP | VK_DOWN to modify quantity adjustments based on transaction mode
	// - lvwPSet should go locked during NEW & XFR but not locked during EDT
	// - lvwMatl should 
	//
	if (pN->iItem > -1)
	{
		if (((pN->uChanged & LVIF_STATE) == LVIF_STATE) || ((pN->uChanged & LVIF_IMAGE) == LVIF_IMAGE))
		{
			if ((pN->uOldState & LVIS_FOCUSED) != (pN->uNewState & LVIS_FOCUSED))
			{
				if ((pN->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED)
				{
					if (m_lvwMatl.GetItemState(pN->iItem, LVIS_CHECKED) != LVIS_CHECKED)
					{
						*pResult = 1;
					}
				}
			}
			if ((pN->uOldState & LVIS_CHECKED) != (pN->uNewState & LVIS_CHECKED))
			{
				*pResult = VerifyMSetChkState(pN->iItem, pN->uOldState, pN->uNewState);
			}
			if ((pN->uOldState & LVIS_SELECTED) != (pN->uNewState & LVIS_SELECTED))
			{
				*pResult = VerifyMSetSelState(pN->iItem, pN->uOldState, pN->uNewState);
			}

			return;
		}
	}
	else
	{
		x_PSet = NULL;
		x_MSet = NULL;
	}
}

void CCustPOrdDlg::OnItemChangedMatl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW	pN			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR			um[256];	memset(um, 0, sizeof(um));
	UINT			is			= 0;

	AfxTrace(_T("MATL:CHND [%2d] [%08x] [%08x->%08x]\n"), pN->iItem, pN->uChanged, pN->uOldState, pN->uNewState);

	if (pN->iItem > -1)
	{
		if ((pN->uOldState & LVIS_FOCUSED) != (pN->uNewState & LVIS_FOCUSED))
		{
			if ((pN->uOldState & LVIS_FOCUSED) == LVIS_FOCUSED)
			{
				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x_MSet);
				LPMATL			pM = MatlLRR(ms.MatlID);

				x_PSet = (POSITION)NULL;
				x_MSet = (POSITION)NULL;

				if (m_XAct == XA_NEDT)
				{
					ms.x_PSrc = (POSITION)NULL;
					ms.x_PDst = (POSITION)NULL;
				}

				PAdjXQUpdate(_T(""));
				m_lvwPSet.DeleteAllItems();

				m_edtCMPrce.SetWindowText(_T(""));
				m_edtCMPrce.SetReadOnly(1);
				m_edtSAPrce.SetWindowText(_T(""));
				m_edtSAPrce.SetReadOnly(1);

				m_edtPOrdXQ.SetWindowText(_T(""));

				GetDlgItem(IDC_OPT_PUOM)->SetWindowText(_T(""));;
				GetDlgItem(IDC_OPT_SUOM)->SetWindowText(_T(""));
				GetDlgItem(IDC_OPT_SUOM)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_OPT_UUOM)->SetWindowText(_T(""));

				// UI Void|Hide|Disable
				GetDlgItem(IDC_FRA_XFER)->SetWindowText(_T(""));
			}
			else if ((pN->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED)
			{
				x_MSet = (POSITION)pN->lParam;
				x_PSet = (POSITION)NULL;

				CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(x_MSet);
				LPMATL			pM = MatlLRR(ms.MatlID);

				if (pM != NULL)
				{
					_stprintf_s<_countof(um)>(um, _T("%s"), (LPCTSTR)ms.PrceUM);
					um[_tcslen(um) - 1] = ((um[_tcslen(um) - 1] == _T('s')) ? _T('\0') : um[_tcslen(um) - 1]);

					_stprintf_s<_countof(tz)>(tz, _T("Price ($ / %s)"), um);
					GetDlgItem(IDC_FRA_PRCE)->SetWindowText(tz);

					m_edtCMPrce.SetWindowText((LPCTSTR)ms.PrceCM);
					m_edtCMPrce.SetReadOnly(ms.IsUsed() ? 0 : 1);
					m_edtSAPrce.SetWindowText((LPCTSTR)ms.PrceSA);
					m_edtSAPrce.SetReadOnly(((ms.IsUsed()) && (p_Cust->SAgt.SAgtID == (LPCTSTR)_T("0"))) ? 0 : 1);

					GetDlgItem(IDC_OPT_PUOM)->SetWindowText((LPCTSTR)pM->PQtyUID);
					GetDlgItem(IDC_OPT_PUOM)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_OPT_SUOM)->SetWindowText((LPCTSTR)pM->SQtyUID);
					GetDlgItem(IDC_OPT_SUOM)->ShowWindow((pM->SQtyUID != SqlNull) ? SW_SHOW : SW_HIDE);

					if (pM->PQtyUID == (LPCTSTR)_T("SlitYds"))
						GetDlgItem(IDC_OPT_UUOM)->SetWindowTextW(_T("Cases"));
					else if (pM->PQtyUID == (LPCTSTR)_T("WideYds"))
						GetDlgItem(IDC_OPT_UUOM)->SetWindowTextW(_T("Rolls"));
					else
						GetDlgItem(IDC_OPT_UUOM)->SetWindowTextW(_T("Units"));

					GetDlgItem(IDC_OPT_UUOM)->ShowWindow(SW_SHOW);

					switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
					{
					case IDC_OPT_SUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->SQtyUID);
						GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);
						
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ms.MOrdPQ()));
						m_edtPOrdXQ.SetWindowText(tz);

						if (InXXfr() == true)
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [XFR]"), (LPCTSTR)pM->SQtyUID);
						else if (InXNew() == true)
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [NEW]"), (LPCTSTR)pM->SQtyUID);
						else if ((GetFocus() != NULL) && (GetFocus()->m_hWnd == m_edtPAdjXQ.m_hWnd))
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [ADJ]"), (LPCTSTR)pM->SQtyUID);
						else
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s)"), (LPCTSTR)pM->SQtyUID);
						GetDlgItem(IDC_FRA_XFER)->SetWindowText(tz);
						break;
					case IDC_OPT_UUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->SQtyUID);
						GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);
						
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.UQtyCT(ms.MOrdPQ()));
						m_edtPOrdXQ.SetWindowText(tz);

						if (pM->PQtyUID == (LPCTSTR)_T("SlitYds"))
						{
							_tcscpy_s<_countof(tz)>(tz, _T("Cases"));
							GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);

							if (InXXfr() == true)
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Cases) [XFR]"));
							if (InXNew() == true)
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Cases) [NEW]"));
							else if ((GetFocus() != NULL) && (GetFocus()->m_hWnd == m_edtPAdjXQ.m_hWnd))
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Cases) [ADJ]"));
							else
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Cases)"));
						}
						else if (pM->PQtyUID == (LPCTSTR)_T("WideYds"))
						{
							_tcscpy_s<_countof(tz)>(tz, _T("Rolls"));
							GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);

							if (InXXfr() == true)
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Rolls) [XFR]"));
							else if (InXNew() == true)
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Rolls) [NEW]"));
							else if ((GetFocus() != NULL) && (GetFocus()->m_hWnd == m_edtPAdjXQ.m_hWnd))
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Rolls) [ADJ]"));
							else
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Rolls)"));
						}
						else
						{
							_tcscpy_s<_countof(tz)>(tz, _T("Units"));
							GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);

							if (InXXfr() == true)
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Units) [XFR]"));
							else if (InXNew() == true)
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Units) [NEW]"));
							else if ((GetFocus() != NULL) && (GetFocus()->m_hWnd == m_edtPAdjXQ.m_hWnd))
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Units) [ADJ]"));
							else
								_tcscpy_s<_countof(tz)>(tz, _T("Ship (Units)"));
						}
						break;
					default:
						_stprintf_s<_countof(tz)>(tz, _T("%s"), (LPCTSTR)pM->PQtyUID);
						GetDlgItem(IDC_LBL_PORDXQ)->SetWindowText(tz);
						
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.MOrdPQ());
						m_edtPOrdXQ.SetWindowText(tz);

						if (InXXfr() == true)
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [XFR]"), (LPCTSTR)pM->PQtyUID);
						else if (InXNew() == true)
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [NEW]"), (LPCTSTR)pM->PQtyUID);
						else if ((GetFocus() != NULL) && (GetFocus()->m_hWnd == m_edtPAdjXQ.m_hWnd))
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [ADJ]"), (LPCTSTR)pM->PQtyUID);
						else
							_stprintf_s<_countof(tz)>(tz, _T("Ship (%s)"), (LPCTSTR)pM->PQtyUID);

					}
					GetDlgItem(IDC_FRA_XFER)->SetWindowText(tz);

					ms.m_PSets.m_PNew.F.IsOrig = ms.IsOrig();

					if (m_lvwMatl.GetCheck(pN->iItem) == TRUE)
					{
						m_edtPOrdXQ.EnableWindow(1);
					}
				}

				ShowPSetList();
				ShowALogList();
			}
		}
	}
	*pResult = 0;
}

void CCustPOrdDlg::OnRimCtrlMoveMatl(NMHDR *pNMHDR, LRESULT *pResult)
{
}

void CCustPOrdDlg::OnGetInfoTipMatl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVGETINFOTIP pNMIT = reinterpret_cast<LPNMLVGETINFOTIP>(pNMHDR);

	if (pNMIT->iItem > -1)
	{
		SqlVarChar<15>	mid;	mid = (LPCTSTR)m_lvwMatl.GetItemText(pNMIT->iItem, -1);
		LPMATL			pM		= MatlLRR(mid);

		if ((pM != NULL) && (pNMIT->pszText != NULL))
		{
			wcscpy_s(pNMIT->pszText, (rsize_t)pNMIT->cchTextMax, (LPCWSTR)pM->MatlName);
		}
	}

	*pResult = 0;
}

void CCustPOrdDlg::OnColumnClickMatl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW	pN		= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pN->iSubItem == 0)
	{
		TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
		LVCOLUMN		lc;			memset(&lc, 0, sizeof(LVCOLUMN));

		m_Col1 = ((m_Col1 == 0) ? 1 : 0);

		lc.cx = 155;
		lc.cchTextMax = 255;
		lc.pszText = &tz[0];
		lc.mask = LVCF_TEXT | LVCF_WIDTH;

		if (m_Col1 == 0)
		{
			_tcscpy_s<_countof(tz)>(tz, _T("Matl ID"));
			m_lvwMatl.SetColumn(0, &lc);
		}
		else
		{
			_tcscpy_s<_countof(tz)>(tz, _T("Styl NM"));
			m_lvwMatl.SetColumn(0, &lc);
		}

		for (int ni = 0, nc = m_lvwMatl.GetItemCount(); ni < nc; ni++)
		{
			CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt((POSITION)m_lvwMatl.GetItemData(ni));

			if (m_Col1 == 0)
			{
				m_lvwMatl.SetItemText(ni, 0, (LPCTSTR)ms.MatlID);
			}
			else
			{
				m_lvwMatl.SetItemText(ni, 0, (LPCTSTR)ms.StylID());
			}
		}
	}
	else
	{
		DoTest();
	}

	*pResult = 0;
}

void CCustPOrdDlg::OnSetFocusCMPrce()
{
	m_edtCMPrce.SetSel(0, -1, 0);
}

void CCustPOrdDlg::OnUpdateCMPrce()
{
	if (x_MSet == NULL)
		return;

	CCustPOrdMSet	ms	= m_POrd.m_MSets.GetAt(x_MSet);
	CString			v;	m_edtCMPrce.GetWindowTextW(v);

	if (v.GetLength() > 0)
	{
		for (int i = 0, p = 0, s = 0, d = 0; i < v.GetLength(); i++)
		{
			switch (v.GetAt(i))
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				p++;
				s += ((d == 1) ? 1 : 0);
				break;
			case '.':
				d++;
				break;
			default:
				AfxMessageBox(_T("Invalid Character in Value"), MB_ICONEXCLAMATION);
				ms.PrceCM = p_CustMatl->CMPrce;
				m_edtCMPrce.SetWindowTextW((LPCTSTR)ms.PrceCM);
				m_edtCMPrce.SetFocus();
				return;
			}
			if (p > (int)ms.PrceCM.Value.precision)
			{
				AfxMessageBox(_T("Too Many Numbers in Value"), MB_ICONEXCLAMATION);
				ms.PrceCM = p_CustMatl->CMPrce;
				m_edtCMPrce.SetWindowTextW((LPCTSTR)ms.PrceCM);
				m_edtCMPrce.SetFocus();
				return;
			}
			if (s > (int)ms.PrceCM.Value.scale)
			{
				AfxMessageBox(_T("Too Many Numbers in Value"), MB_ICONEXCLAMATION);
				ms.PrceCM = p_CustMatl->CMPrce;
				m_edtCMPrce.SetWindowTextW((LPCTSTR)ms.PrceCM);
				m_edtCMPrce.SetFocus();
				return;
			}
			if (d > 1)
			{
				AfxMessageBox(_T("Too Many Decimals in Value"), MB_ICONEXCLAMATION);
				ms.PrceCM = p_CustMatl->CMPrce;
				m_edtCMPrce.SetWindowTextW((LPCTSTR)ms.PrceCM);
				m_edtCMPrce.SetFocus();
				return;
			}
		}
		ms.PrceCM = (LPCTSTR)v;
		
		if ((p_Cust->SAgt.SAgtID == (LPCTSTR)_T("0")) && (ms.PrceCM != SqlNull))
		{
			ms.PrceSA = (double)ms.PrceCM;
			m_edtSAPrce.SetWindowTextW((LPCTSTR)ms.PrceSA);
		}
	}
	else
	{
		ms.PrceCM = SqlNull;

		if ((p_Cust->SAgt.SAgtID == (LPCTSTR)_T("0")))
		{
			ms.PrceSA = SqlNull;
			m_edtSAPrce.SetWindowTextW((LPCTSTR)ms.PrceSA);
		}
	}
}

void CCustPOrdDlg::OnKillFocusCMPrce()
{
	OnUpdateCMPrce();
}

void CCustPOrdDlg::OnSetFocusSAPrce()
{
	m_edtSAPrce.SetSel(0, -1, 0);
}

void CCustPOrdDlg::OnUpdateSAPrce()
{
	if (x_MSet == NULL)
		return;

	CCustPOrdMSet	ms	= m_POrd.m_MSets.GetAt(x_MSet);
	CString			v;	m_edtCMPrce.GetWindowTextW(v);

	if (v.GetLength() > 0)
	{
		for (int i = 0, p = 0, s = 0, d = 0; i < v.GetLength(); i++)
		{
			switch (v.GetAt(i))
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				p++;
				s += ((d == 1) ? 1 : 0);
				break;
			case '.':
				d++;
				break;
			default:
				AfxMessageBox(_T("Invalid Character in Value"), MB_ICONEXCLAMATION);
				ms.PrceSA = p_CustMatl->SAPrce;
				m_edtSAPrce.SetWindowTextW((LPCTSTR)ms.PrceSA);
				m_edtSAPrce.SetFocus();
				return;
			}
			if (p > (int)ms.PrceSA.Value.precision)
			{
				AfxMessageBox(_T("Too Many Numbers in Value"), MB_ICONEXCLAMATION);
				ms.PrceSA = p_CustMatl->SAPrce;
				m_edtSAPrce.SetWindowTextW((LPCTSTR)ms.PrceSA);
				m_edtSAPrce.SetFocus();
				return;
			}
			if (s > (int)ms.PrceSA.Value.scale)
			{
				AfxMessageBox(_T("Too Many Numbers in Value"), MB_ICONEXCLAMATION);
				ms.PrceSA = p_CustMatl->SAPrce;
				m_edtSAPrce.SetWindowTextW((LPCTSTR)ms.PrceSA);
				m_edtSAPrce.SetFocus();
				return;
			}
			if (d > 1)
			{
				AfxMessageBox(_T("Too Many Decimals in Value"), MB_ICONEXCLAMATION);
				ms.PrceSA = p_CustMatl->SAPrce;
				m_edtSAPrce.SetWindowTextW((LPCTSTR)ms.PrceSA);
				m_edtSAPrce.SetFocus();
				return;
			}
		}
		ms.PrceSA = (LPCTSTR)v;
	}
	else
	{
		ms.PrceSA = SqlNull;
	}
}

void CCustPOrdDlg::OnKillFocusSAPrce()
{
	OnUpdateSAPrce();
}

void CCustPOrdDlg::OnSetFocusPOrdXQ()
{
	return;

	m_edtPOrdXQ.SetSel(0, -1, 0);
}

void CCustPOrdDlg::OnUpdatePOrdXQ()
{
	return;

	if (GetFocus() == NULL)
		return;
	if (GetFocus()->m_hWnd != m_edtPOrdXQ.m_hWnd)
		return;
	if (x_MSet == NULL)
		return;
	if (m_edtPOrdXQ.GetWindowTextLength() == 0)
		return;

	CCustPOrdMSet		ms	= m_POrd.m_MSets.GetAt(x_MSet);
	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				nv[256];	memset(nv, 0, sizeof(nv));
	TCHAR				ov[256];	memset(ov, 0, sizeof(ov));
	SqlNumeric<10, 2>	pq;			pq = (double)0.0;
	SqlNumeric<10, 2>	sq;			sq = (double)0.0;
	SqlSmallInt			ct;			ct = (short)0;
	HRESULT				hr			= S_OK;

	switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
	{
	case IDC_OPT_SUOM:
		_stprintf_s<_countof(ov)>(ov, _T("%.2f"), ms.DQtySQ(ms.MOrdPQ()));
		break;
	case IDC_OPT_UUOM:
		_stprintf_s<_countof(ov)>(ov, _T("%d"), ms.UQtyCT(ms.MOrdPQ()));
		break;
	default:
		_stprintf_s<_countof(ov)>(ov, _T("%.2f"), ms.MOrdPQ());
		break;
	}

	m_edtPOrdXQ.GetWindowText(tz, 255);

	for (size_t i = 0, j = 0, d = 0, c = _tcslen(tz); i < c; i++)
	{
		switch (tz[i])
		{
		case _T('0'):
		case _T('1'):
		case _T('2'):
		case _T('3'):
		case _T('4'):
		case _T('5'):
		case _T('6'):
		case _T('7'):
		case _T('8'):
		case _T('9'):
			nv[j++] = tz[i];
			break;
		case _T('.'):
			if (++d > 1)
			{
				::MessageBox(m_hWnd, _T("Too many decimals in value"), _T("POrdXQ Entry Error"), MB_ICONEXCLAMATION | MB_OK);
				hr = E_FAIL;
			}
			nv[j++] = tz[i];
			break;
		default:
			::MessageBox(m_hWnd, _T("Invalid character in value"), _T("POrdXQ Entry Error"), MB_ICONEXCLAMATION | MB_OK);
			hr = E_FAIL;
		}
	}

	if (SUCCEEDED(hr))
	{
		switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			sq = _tcstod(nv, NULL);
			pq = ms.DQtyPQ(sq);
			ct = ms.UQtyCT(pq);
			break;
		case IDC_OPT_UUOM:
			ct = (short)_tcstol(nv, NULL, 10);
			pq = ms.DQtyPQ(ct);
			sq = ms.DQtySQ(pq);
			break;
		default:
			pq = _tcstod(nv, NULL);
			sq = ms.DQtySQ(pq);
			ct = ms.UQtyCT(pq);
		}

		ms.PAdjPQ = (double)pq - (double)ms.MOrdPQ();
	}
	else
	{
		m_edtPOrdXQ.SetWindowText(ov);
	}

	ShowMatlList(x_MSet);
}

void CCustPOrdDlg::OnKillFocusPOrdXQ()
{
}

void CCustPOrdDlg::OnClickPUOM()
{
	ShowMatlList();
	ShowPSetList();
	ShowALogList();
}

void CCustPOrdDlg::OnClickSUOM()
{
	ShowMatlList();
	ShowPSetList();
	ShowALogList();
}

void CCustPOrdDlg::OnClickUUOM()
{
	ShowMatlList();
	ShowPSetList();
	ShowALogList();
}

LRESULT CCustPOrdDlg::VerifyPSetSelState(int iItem, UINT uOldState, UINT uNewState)
{
	// We're determining if a listitem in lvwPSet is valid to select if either
	// 1. The user is CTRL+LCLICK an item to select firing OnItemChangingPSet() notification, or
	// 2. We're scrolling list items via f() to auto-select based on criteria
	if ((iItem <= -1) || (iItem >= m_lvwPSet.GetItemCount()))
		return (1);

	if (x_MSet == NULL)
		return (1);

	if ((POSITION)m_lvwPSet.GetItemData(iItem) == NULL)
		return (1);

	CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
	UINT				cs			= ((ms.x_PSrc == NULL) ? ((ms.x_PDst == NULL) ? 0 : 1) : 2);
	int					is			= -1;
	int					id			= -1;

	// Can always re-select, never de-select existing selection when not in edit
	if (m_XAct != XA_NEDT)
	{
		if ((ms.x_PDst != NULL) && ((POSITION)m_lvwPSet.GetItemData(iItem) == ms.x_PDst))
		{
			if (((uOldState & LVIS_SELECTED) == LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) != LVIS_SELECTED))
			{
				return (1);
			}
			if (((uOldState & LVIS_SELECTED) != LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) == LVIS_SELECTED))
			{
				return (0);
			}
		}
		if ((ms.x_PSrc != NULL) && ((POSITION)m_lvwPSet.GetItemData(iItem) == ms.x_PSrc))
		{
			if (((uOldState & LVIS_SELECTED) == LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) != LVIS_SELECTED))
			{
				return (1);
			}
			if (((uOldState & LVIS_SELECTED) != LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) == LVIS_SELECTED))
			{
				return (0);
			}
		}
		return (1);
	}

	//
	// At this point, we're handling up/down navigation in XA_NEDT mode
	//
	if (((uOldState & LVIS_SELECTED) == LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) != LVIS_SELECTED))
	{
		// If 2 items selected, PSrc must be first item unselected
		if (cs == 2)
		{
			AfxTrace(_T("VRFY:PSET: If 2 items selected, PSrc must be first item unselected\n"));
			return (1);
		}
	}
	else if (((uOldState & LVIS_SELECTED) != LVIS_SELECTED) && ((uNewState & LVIS_SELECTED) == LVIS_SELECTED))
	{
		// No more than 2 items may be selected
		if (cs == 2)
		{
			AfxTrace(_T("VRFY:PSET: No more than 2 items may be selected\n"));
			return (1);
		}
		// NEW cannot be 2nd item selected
		else if (cs == 1)
		{
			if ((POSITION)m_lvwPSet.GetItemData(iItem) == ms.m_PSets.x_PNew)
			{
				AfxTrace(_T("VRFY:PSET: NEW cannot be 2nd item selected\n"));
				return (1);
			}
		}
	}

	return (0);
}

void CCustPOrdDlg::OnItemChangingPSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (x_MSet == NULL)
		return;

	LPNMLISTVIEW	pN			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	UINT			is			= 0;
	CCustPOrdMSet&	ms			= m_POrd.m_MSets.GetAt(x_MSet);

	*pResult = 0;

	AfxTrace(_T("PSET:CHNG [%2d] [%08x] [%08x->%08x]\n"), pN->iItem, pN->uChanged, pN->uOldState, pN->uNewState);

	if (pN->iItem > -1)
	{
		if ((pN->uChanged & LVIF_STATE) == LVIF_STATE)
		{
			if ((pN->uOldState & LVIS_FOCUSED) != (pN->uNewState & LVIS_FOCUSED))
			{
				if ((pN->uOldState & LVIS_FOCUSED) == LVIS_FOCUSED)
				{
					// What did we lose focus to?
					// - During testing while in navigation, LVN_ITEMCHANGING preceeded BTN_CLICK notifications
					if (GetFocus() != NULL)
					{
						switch (GetFocus()->GetDlgCtrlID())
						{
						case IDC_OPT_PUOM:
						case IDC_OPT_SUOM:
						case IDC_OPT_UUOM:
						case IDC_BTN_NEW:
						case IDC_BTN_XFR:
						case IDC_DTP_PDSTDT:
							*pResult = 1;
							break;
						default:
							*pResult = 0;
						}
					}
				}
			}
			if ((pN->uOldState & LVIS_SELECTED) != (pN->uNewState & LVIS_SELECTED))
			{
				if ((pN->uOldState & LVIS_SELECTED) == LVIS_SELECTED)
				{
					// What did we lose selection to?
					// - During testing while in navigation, LVN_ITEMCHANGING preceeded BTN_CLICK notifications
					if (GetFocus() != NULL)
					{
						switch (GetFocus()->GetDlgCtrlID())
						{
						case IDC_OPT_PUOM:
						case IDC_OPT_SUOM:
						case IDC_OPT_UUOM:
						case IDC_BTN_NEW:
						case IDC_BTN_XFR:
						case IDC_DTP_PDSTDT:
							*pResult = 1;
							break;
						default:
							*pResult = 0;
						}
					}
				}
				*pResult = ((*pResult == 0) ? VerifyPSetSelState(pN->iItem, pN->uOldState, pN->uNewState) : *pResult);
			}
		}
	}
}

void CCustPOrdDlg::OnItemChangedPSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (x_MSet == NULL)
		return;

	LPNMLISTVIEW	pN			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	CCustPOrdMSet&	ms			= m_POrd.m_MSets.GetAt(x_MSet);
	UINT			cs			= ((ms.x_PSrc == NULL) ? ((ms.x_PDst == NULL) ? 0 : 1) : 2);
	SYSTEMTIME		sd;			memset(&sd, 0, sizeof(SYSTEMTIME));
	SYSTEMTIME		dd;			memset(&dd, 0, sizeof(SYSTEMTIME));
	DATE			vt			= 0;

	// NOTES
	// - User can select up to 2 promise dates. Focused implies selected via VerifyPSetSelState
	// - On any non-new selection, write promise date to PDst or PSrc based on selected count
	// - On new selection (must be first!), write NULL to PDstDT and enable
	// - ShowPSetList should...
	//   - Insert PSet ListItems for MSet
	//   - Select ListItems for PSrc and/or PDst Dates (not set dates)
	// - OnItemChangedPSet should set controls based on selection count and contains new (ALWAYS @0!!!)

	AfxTrace(_T("PSET:CHND [%2d] [%08x] [%08x->%08x]\n"), pN->iItem, pN->uChanged, pN->uOldState, pN->uNewState);

	if (pN->iItem > -1)
	{
		CCustPOrdMSetPSet&	ps = ms.m_PSets.Get((POSITION)m_lvwPSet.GetItemData(pN->iItem));

		if ((pN->uChanged & LVIF_STATE) == LVIF_STATE)
		{
			if ((pN->uOldState & LVIS_FOCUSED) != (pN->uNewState & LVIS_FOCUSED))
			{
				if ((pN->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED)
				{
					x_PSet = (POSITION)m_lvwPSet.GetItemData(pN->iItem);
					ms.x_PSet = (POSITION)m_lvwPSet.GetItemData(pN->iItem);

					switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
					{
					case IDC_OPT_SUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ps.FPrmPQ()));
						m_lvwPSet.SetItemText(pN->iItem, 2, tz);
						break;

					case IDC_OPT_UUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(ps.FPrmPQ()));
						m_lvwPSet.SetItemText(pN->iItem, 2, tz);
						break;

					default:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ps.FPrmPQ());
						m_lvwPSet.SetItemText(pN->iItem, 2, tz);
					}

					// PDstDT enabled on PNew focus gain - if PrmdDT is NULL
					if ((POSITION)m_lvwPSet.GetItemData(pN->iItem) == ms.m_PSets.x_PNew)
					{
						if (ms.m_PSets.m_PNew.F.PrmdDT != SqlNull)
						{
							m_edtPAdjXQ.SetReadOnly(((cs == 1) ? 0 : 1));
						}
						else
						{
							m_edtPAdjXQ.SetReadOnly(1);
						}
					}
					else
					{
						m_edtPAdjXQ.SetReadOnly(((cs == 1) ? 0 : 1));
					}

					PAdjXQUpdate(tz);
					m_edtPAdjXQ.SetSel(0, -1, 0);
				}
				else if ((pN->uNewState & LVIS_FOCUSED) != LVIS_FOCUSED)
				{
					// PDstDT disabled on PNew focus loss
					if ((POSITION)m_lvwPSet.GetItemData(pN->iItem) == ms.m_PSets.x_PNew)
					{
						m_dtpPDstDT.EnableWindow(0);
					}
					// PSet must always keep PDst in Focus
					if ((m_XAct != XA_NEDT) && (ms.x_PDst != NULL) && (ms.x_PDst == (POSITION)m_lvwPSet.GetItemData(pN->iItem)))
					{
						AfxTrace(_T("REFOCUS PDst @ %d\n"), pN->iItem);
						m_lvwPSet.SetItemState(pN->iItem, LVIS_FOCUSED, LVIS_FOCUSED);
					}
				}
			}

			if ((pN->uOldState & LVIS_SELECTED) != (pN->uNewState & LVIS_SELECTED))
			{
				if ((pN->uNewState & LVIS_SELECTED) != LVIS_SELECTED)
				{
					// If 2 items selected, PSrc must be first item unselected
					if (cs == 2)
					{
						if (m_XAct == XA_NEDT)
						{
							// Selection Loss
							--cs;
							AfxTrace(_T("CHGD:PSET: If 2 items selected, PSrc will be first item unselected\n"));
							ms.x_PSrc = (POSITION)NULL;
						}
						m_dtpPSrcDT.SetTime(p_2Day);
						m_dtpPSrcDT.SetTime((LPSYSTEMTIME)NULL);
					}
					// If 1 item selected, PDst must be second item unselected
					else if (cs == 1)
					{
						if ((POSITION)m_lvwPSet.GetItemData(pN->iItem) == ms.m_PSets.x_PNew)
						{
							if (m_XAct == XA_NEDT)
							{
								// Selection Loss
								--cs;
								AfxTrace(_T("CHGD:PNEW: If 1 item selected, PDst will be second item unselected\n"));
								ms.x_PDst = (POSITION)NULL;
								ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
								m_lvwPSet.SetItemText(0, 0, _T("<select>"));
							}
							m_dtpPDstDT.SetTime(p_2Day);
							m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);
						}
						else
						{
							if (m_XAct == XA_NEDT)
							{
								// Selection Loss
								--cs;
								AfxTrace(_T("CHGD:PEXI: If 1 item selected, PDst will be second item unselected\n"));
								ms.x_PDst = (POSITION)NULL;
							}
							m_dtpPDstDT.SetTime(p_2Day);
							m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);
						}
					}
				}
				else if ((pN->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
				{
					// If 0 items selected, PDst must be first item selected
					if (cs == 0)
					{
						if ((POSITION)m_lvwPSet.GetItemData(pN->iItem) == ms.m_PSets.x_PNew)
						{
							if (m_XAct == XA_NEDT)
							{
								// Selection Gain
								++cs;
								AfxTrace(_T("CHGD:PNEW: If 0 items selected, PDst will be first item selected\n"));
								ms.x_PDst = (POSITION)m_lvwPSet.GetItemData(pN->iItem);
							}
							if (ps.F.PrmdDT != SqlNull)
							{
								m_dtpPDstDT.SetTime((LPSYSTEMTIME)ps.F.PrmdDT);
							}
							else
							{
								m_dtpPDstDT.SetTime(p_2Day);
								m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);
							}
						}
						else
						{
							if (m_XAct == XA_NEDT)
							{
								// Selection Gain
								++cs;
								AfxTrace(_T("CHGD:PEXI: If 0 items selected, PDst will be first item selected\n"));
								ms.x_PDst = (POSITION)m_lvwPSet.GetItemData(pN->iItem);
							}
							m_dtpPDstDT.SetTime((LPSYSTEMTIME)ps.F.PrmdDT);
						}
					}
					else if ((cs == 1) && ((POSITION)m_lvwPSet.GetItemData(pN->iItem) != ms.x_PDst))
					{
						if (m_XAct == XA_NEDT)
						{
							AfxTrace(_T("CHGD:PEXI: If 1 item selected, PSrc will be second item selected\n"));
							ms.x_PSrc = (POSITION)m_lvwPSet.GetItemData(pN->iItem);
						}
						m_dtpPSrcDT.SetTime((LPSYSTEMTIME)ps.F.PrmdDT);
						// Selection Gain
						++cs;
					}
				}

				// Configure Controls (Edit Mode)
				if (m_XAct == XA_NEDT)
				{
					m_edtPAdjXQ.SetReadOnly(((cs == 1) ? 0 : 1));

					if ((cs == 1) && (ms.x_PDst == ms.m_PSets.x_PNew))
					{
						GetDlgItem(IDC_BTN_NEW)->EnableWindow(1);
						GetDlgItem(IDC_BTN_XFR)->EnableWindow(0);
					}
					else if (cs == 2)
					{
						GetDlgItem(IDC_BTN_NEW)->EnableWindow(0);
						GetDlgItem(IDC_BTN_XFR)->EnableWindow(1);
					}
					else
					{
						GetDlgItem(IDC_BTN_NEW)->EnableWindow(0);
						GetDlgItem(IDC_BTN_XFR)->EnableWindow(0);
					}
				}
			}
		}
	}

	*pResult = 0;
}

void CCustPOrdDlg::OnRimCtrlMovePSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW	pN			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));

	*pResult = 0;
}


void CCustPOrdDlg::OnDateTimeChangePSrcDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pC		= reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	*pResult = 0;
}

void CCustPOrdDlg::OnDateTimeDropDownPDstDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (x_MSet == NULL)
		return;
	if (x_PSet == NULL)
		return;

	m_POrd.m_PDst.Opened = true;

	*pResult = 0;
}

void CCustPOrdDlg::OnDateTimeChangePDstDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (x_MSet == NULL)
		return;
	if (x_PSet == NULL)
		return;

	// User is selecting PrmdDT for NEW only
	if (m_dtpPDstDT.IsWindowEnabled() == TRUE)
	{ 
		LPNMDATETIMECHANGE	pC			= reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
		TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
		TCHAR				pr[11];		memset(pr, 0, sizeof(pr));
		CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
		SYSTEMTIME			st;			memset(&st, 0, sizeof(SYSTEMTIME));
		DATE				vt			= 0;
		int					cs			= 0;

		::SystemTimeToVariantTime(&pC->st, &vt);
		vt =  floor(vt);
		::VariantTimeToSystemTime(vt, &st);

		if (m_POrd.m_PDst.Opened == true)
		{
			m_POrd.m_PDst.PrmdDT = st;
		}
		else
		{
			if ((ms.FindPSet(st) == NULL) || (ms.FindPSet(st) == ms.m_PSets.x_PNew))
			{
				ms.m_PSets.m_PNew.F.PrmdDT = st;

				ShowPSetList(ms.m_PSets.x_PNew);

				if (m_XAct == XA_NNEW)
				{
					if (Ok2New() == true)
					{
						if (SelectMSetsForXAct(XA_NNEW) > 0)
						{
							m_edtPAdjXQ.SetReadOnly(0);
							m_edtPAdjXQ.SetFocus();
						}
						else
						{
							::MessageBox(m_hWnd, _T("No materials found to add this promise date"), _T("Select another promise date"), MB_ICONEXCLAMATION | MB_OK);
						}
					}
				}
				else if (m_XAct == XA_NXFR)
				{
					if (Ok2Xfr() == true)
					{
						if (SelectMSetsForXAct(XA_NXFR) > 0)
						{
							m_edtPAdjXQ.SetReadOnly(0);
							m_edtPAdjXQ.SetFocus();
						}
						else
						{
							::MessageBox(m_hWnd, _T("No materials found to move from this promise date"), _T("Select another promise date"), MB_ICONEXCLAMATION | MB_OK);
						}
					}
				}
			}
			else
			{
				_stprintf_s<_countof(tz)>(tz, _T("Promise date [%4d/%02d/%02d] has already been created for [%s] and cannot be selected"), st.wYear, st.wMonth, st.wDay, (LPCTSTR)ms.MatlID);
				::MessageBox(m_hWnd, tz, _T("Unable to create promise date"), MB_ICONEXCLAMATION | MB_OK);

				m_dtpPDstDT.SetFocus();

				*pResult = 1;
			}
		}
	}
}

void CCustPOrdDlg::OnDateTimeCloseUpPDstDT(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMDATETIMECHANGE	sC;		memset(&sC, 0, sizeof(NMDATETIMECHANGE));
	
	if (m_POrd.m_PDst.PrmdDT != SqlNull)
	{
		sC.nmhdr	= *pNMHDR;
		sC.dwFlags	= 0;
		sC.st		= m_POrd.m_PDst.PrmdDT;

		m_POrd.m_PDst.Opened = false;

		OnDateTimeChangePDstDT(&sC.nmhdr, pResult);

		m_POrd.m_PDst.PrmdDT = SqlNull;
	}

	*pResult = 0;
}

void CCustPOrdDlg::PAdjXQUpdate(LPCTSTR tz)
{
	if (m_edtPAdjXQ.IsWindowEnabled() == FALSE)
	{
		m_edtPAdjXQ.SetWindowTextW(tz);
	}
	else if ((m_edtPAdjXQ.GetStyle() & ES_READONLY) == ES_READONLY)
	{
		m_edtPAdjXQ.SetWindowTextW(tz);
	}
	else if ((InXXfr() == true) || (InXNew() == true) || ((InXEdt() == true) && (GetFocus() != NULL) && (GetFocus()->m_hWnd == m_edtPAdjXQ.m_hWnd)))
	{
		m_edtPAdjXQ.SetReadOnly(1);
		m_edtPAdjXQ.SetWindowText(tz);
		m_edtPAdjXQ.SetReadOnly(0);
//		m_edtPAdjXQ.SetSel(0, -1, 0);
	}
}

void CCustPOrdDlg::OnSetFocusPAdjXQ()
{
	m_edtPAdjXQ.SetSel(0, -1, 0);
	AfxTrace(_T("CCustPOrdDlg::OnSetFocusPAdjXQ()\n"));
}

void CCustPOrdDlg::OnUpdatePAdjXQ()
{
	if (m_edtPAdjXQ.IsWindowEnabled() == FALSE)
		return;
	if ((m_edtPAdjXQ.GetStyle() & ES_READONLY) == ES_READONLY)
		return;
	if (m_edtPAdjXQ.GetWindowTextLength() == 0)
		return;
	if (GetFocus() == NULL)
		return;
	if (GetFocus()->m_hWnd != m_edtPAdjXQ.m_hWnd)
		return;
	if (x_MSet == NULL)
		return;
	if (x_PSet == NULL)
		return;
	
	CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				nv[256];	memset(nv, 0, sizeof(nv));
	TCHAR				ov[256];	memset(ov, 0, sizeof(ov));
	SqlNumeric<9, 2>	pa;			pa = (double)0.0;
	SqlNumeric<10, 2>	pq;			pq = (double)0.0;
	SqlNumeric<10, 2>	sq;			sq = (double)0.0;
	SqlSmallInt			ct;			ct = (short)0;
	HRESULT				hr			= S_OK;

	m_edtPAdjXQ.GetWindowText(tz, 255);

 	for (size_t i = 0, j = 0, d = 0, c = _tcslen(tz); i < c; i++)
	{
		switch (tz[i])
		{
		case _T('0'):
		case _T('1'):
		case _T('2'):
		case _T('3'):
		case _T('4'):
		case _T('5'):
		case _T('6'):
		case _T('7'):
		case _T('8'):
		case _T('9'):
			nv[j++] = tz[i];
			break;
		case _T('.'):
			if (++d > 1)
			{
				::MessageBox(m_hWnd, _T("Too many decimals in value"), _T("PrmdXQ Entry Error"), MB_ICONEXCLAMATION | MB_OK);
				hr = E_FAIL;
			}
			nv[j++] = tz[i];
			break;
		default:
			::MessageBox(m_hWnd, _T("Invalid character in value"), _T("PrmdXQ Entry Error"), MB_ICONEXCLAMATION | MB_OK);
			hr = E_FAIL;
		}
	}

	if (SUCCEEDED(hr))
	{
		switch (GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			sq = _tcstod(nv, NULL);
			pq = ms.DQtyPQ(sq);
			ct = ms.UQtyCT(pq);
			break;
		case IDC_OPT_UUOM:
			ct = (short)_tcstol(nv, NULL, 10);
			pq = ms.DQtyPQ(ct);
			sq = ms.DQtySQ(pq);
			break;
		default:
			pq = _tcstod(nv, NULL);
			sq = ms.DQtySQ(pq);
			ct = ms.UQtyCT(pq);
		}

		if (InXXfr() == true)
		{
			if (ms.x_PDst == NULL)
			{
				_tcscpy_s<_countof(tz)>(tz, _T("Please select a target (=>) promise date to move adjustment to."));
				::MessageBox(m_hWnd, tz, _T("Missing target promise date"), MB_ICONEXCLAMATION | MB_OK);
				return;
			}
			if (ms.x_PSrc == NULL)
			{
				_tcscpy_s<_countof(tz)>(tz, _T("Please select a source (<=) promise date to move adjustment from."));
				::MessageBox(m_hWnd, tz, _T("Missing source promise date"), MB_ICONEXCLAMATION | MB_OK);
				return;
			}

			CCustPOrdMSetPSet&	ps	= ms.m_PSets.Get(ms.x_PSrc);
			CCustPOrdMSetPSet&	pd	= ms.m_PSets.Get(ms.x_PDst);

			if ((pa = (double)pq - (double)pd.FPrmPQ()) != (double)0.0)
			{
				ms.DoMove(ps, pd, pa);

				ShowPSetList(ms.x_PSrc);
				ShowPSetList(ms.x_PDst);

				pd.Dump(_T("DoMove::Dst"));
				ps.Dump(_T("DoMove::Src"));
			}
		}
		else
		{
			if (ms.x_PDst == NULL)
			{
				_tcscpy_s<_countof(tz)>(tz, _T("Please select a target (=>) promise date to edit."));
				::MessageBox(m_hWnd, tz, _T("Missing target promise date"), MB_ICONEXCLAMATION | MB_OK);
				return;
			}
			CCustPOrdMSetPSet&	pd	= ms.m_PSets.Get(ms.x_PDst);

			if ((pa = (double)pq - (double)pd.FPrmPQ()) != (double)0.0)
			{
				ms.DoEdit(pd, pa);

				ShowPSetList(ms.x_PDst);

				pd.Dump(_T("DoEdit::Dst"));
			}
		}

		ShowMatlList(x_MSet);

		switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(ms.MOrdPQ()));
			m_edtPOrdXQ.SetWindowText(tz);
			break;

		case IDC_OPT_UUOM:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.UQtyCT(ms.MOrdPQ()));
			m_edtPOrdXQ.SetWindowText(tz);
			break;

		default:
			_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.MOrdPQ());
			m_edtPOrdXQ.SetWindowText(tz);
		}
	}
}

void CCustPOrdDlg::OnKillFocusPAdjXQ()
{
	AfxTrace(_T("CCustPOrdDlg::OnKillFocusPAdjXQ(%d): "), ((CButton*)GetDlgItem(IDC_BTN_NEW))->GetCheck());

	if (GetFocus() != NULL)
	{
		switch (GetFocus()->GetDlgCtrlID())
		{
		case IDC_BTN_NEW:
			AfxTrace(_T("BTN.New\n"));
			break;
		case IDC_BTN_XFR:
			AfxTrace(_T("BTN.Xfr\n"));
			break;
		default:
			AfxTrace(_T("Default\n"));
		}
	}

}

void CCustPOrdDlg::OnClickNew()
{
	// Flow (from edit mode)
	// - User focuses LI in lvwMatl
	// - ShowPSetList builds lvwPSet LIs
	// - User focuses PSets.PNew -> dtpPDstDT is unchecked but enabled, btnNew is disabled
	// - User selects a date, validation must exist that focused MSet doesn't have date and select ALL MSets not having date
	// - If validation succeeds, btnNew enabled
	//
	// - Ok2New validates a date is selected
	// - SelectMSetsForXAct sets x_PDst & x_PSrc
	if (x_MSet == NULL)
		return;
	if ((((CButton*)GetDlgItem(IDC_BTN_NEW))->GetCheck() == 1) && (m_XAct == XA_NNEW))
	{
		OnClickUndo();
		return;
	}

	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				um[10];		memset(um, 0, sizeof(um));
	CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
	LPMATL				pm			= MatlLRR(ms.MatlID);
	int					cs			= 0;

	if ((cs = m_lvwPSet.GetSelectedCount()) == 1)
	{
		switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
			_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [NEW]"), um);
			break;
		case IDC_OPT_UUOM:
			GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
			_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [NEW]"), um);
			break;
		default:
			GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
			_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [NEW]"), um);
		}
		GetDlgItem(IDC_FRA_XFER)->SetWindowTextW(tz);

		GetDlgItem(IDC_LBL_PSRC)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_LBL_PDST)->SetWindowTextW(_T("on"));

		m_XAct = XA_NNEW;

		m_lvwPSet.UpDownEnable(false);
		GetDlgItem(IDC_BTN_UNDO)->EnableWindow(1);
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(1);

		m_dtpPDstDT.EnableWindow(1);
		m_dtpPDstDT.SetFocus();
	}
}

void CCustPOrdDlg::OnClickXfr()
{
	// Flow (from edit mode)
	// - User focuses LI in lvwMatl
	// - ShowPSetList builds lvwPSet LIs
	// - User focuses PSets.PNew -> dtpPDstDT is unchecked but enabled, btnNew is disabled
	// - User selects a date, validation must exist that focused MSet doesn't have date and select ALL MSets not having date
	// - If validation succeeds, btnNew enabled
	//
	// - Ok2New validates a date is selected
	// - SelectMSetsForXAct sets x_PDst & x_PSrc
	if (x_MSet == NULL)
		return;
	
	if ((((CButton*)GetDlgItem(IDC_BTN_XFR))->GetCheck() == 0) && (m_XAct == XA_NXFR))
	{
		OnClickUndo();
		return;
	}

	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				um[10];		memset(um, 0, sizeof(um));
	CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
	LPMATL				pm			= MatlLRR(ms.MatlID);
	int					cs			= 0;
	LVFINDINFO			fi;			memset(&fi, 0, sizeof(LVFINDINFO));
	int					id			= -1;

	// First, find first selected with lParan == ms.x_PDst
	if (ms.x_PDst != NULL)
	{
		fi.flags	= LVFI_PARAM;
		fi.lParam	= (DWORD_PTR)ms.x_PDst;

		id = m_lvwPSet.FindItem(&fi, -1);
	}
	else
	{
		return;
	}

	if ((id > -1) && ((cs = m_lvwPSet.GetSelectedCount()) == 2))
	{
		m_XAct = XA_NXFR;

		m_lvwPSet.SetItemState(id, (LVIS_FOCUSED | LVIS_SELECTED), (LVIS_FOCUSED | LVIS_SELECTED));

		switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
		{
		case IDC_OPT_SUOM:
			GetDlgItem(IDC_OPT_SUOM)->GetWindowText(um, 9);
			_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [XFR]"), um);
			break;
		case IDC_OPT_UUOM:
			GetDlgItem(IDC_OPT_UUOM)->GetWindowText(um, 9);
			_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [XFR]"), um);
			break;
		default:
			GetDlgItem(IDC_OPT_PUOM)->GetWindowText(um, 9);
			_stprintf_s<_countof(tz)>(tz, _T("Ship (%s) [XFR]"), um);
		}
		GetDlgItem(IDC_FRA_XFER)->SetWindowTextW(tz);

		GetDlgItem(IDC_LBL_PSRC)->SetWindowTextW(_T("from"));
		GetDlgItem(IDC_LBL_PDST)->SetWindowTextW(_T("to"));

		m_lvwPSet.UpDownEnable(false);
		GetDlgItem(IDC_BTN_UNDO)->EnableWindow(1);
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(1);

		// Next step is to select new promise date
		if (ms.x_PDst == ms.m_PSets.x_PNew)
		{
			m_dtpPDstDT.EnableWindow(1);
			m_dtpPDstDT.SetFocus();
		}
		// Else, next step is to edit quantities
		else
		{
			if (Ok2Xfr() == true)
			{
				if (SelectMSetsForXAct(XA_NXFR) > 0)
				{
					m_edtPAdjXQ.SetReadOnly(0);
					m_edtPAdjXQ.SetFocus();
				}
				else
				{
					::MessageBox(m_hWnd, _T("No materials found to move from this promise date"), _T("Select another promise date"), MB_ICONEXCLAMATION | MB_OK);
				}
			}
		}
	}
}

void CCustPOrdDlg::OnClickSave()
{
	if (x_MSet == NULL)
		return;
	if ((InXXfr() == false) && (InXNew() == false))
		return;

	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				um[10];		memset(um, 0, sizeof(um));
	CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
	LPMATL				pm			= MatlLRR(ms.MatlID);
	int					cs			= 0;

	// Verify Loop
	for (int i = 0, c = m_lvwMatl.GetItemCount(); i < c; i++)
	{
		if (m_lvwMatl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt((POSITION)m_lvwMatl.GetItemData(i));

			m_lvwMatl.SetItemState(i, LVIS_FOCUSED, LVIS_FOCUSED);

			switch (MSetXActOK(ms))
			{
			// NoOp
			case -1:
				break;
			case 0:
				return;
			}
		}
	}
	
	// DoXAct Loop
	for (int i = 0, c = m_lvwMatl.GetItemCount(); i < c; i++)
	{
		if (m_lvwMatl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			POSITION		xm = (POSITION)m_lvwMatl.GetItemData(i);
			CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt((POSITION)m_lvwMatl.GetItemData(i));

			MSetDoXAct(ms);

			if (ms.x_PDst != NULL)
			{
				CCustPOrdMSetPSet&	pd = ms.m_PSets.Get(ms.x_PDst);

				if (ms.x_PSrc != NULL)
				{
					CCustPOrdMSetPSet&	ps = ms.m_PSets.Get(ms.x_PSrc);

					if (ms.x_PDst == ms.m_PSets.x_PNew)
					{
						ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
					}
					ms.x_PSrc = (POSITION)NULL;
					m_dtpPSrcDT.SetTime(p_2Day);
					m_dtpPSrcDT.SetTime((LPSYSTEMTIME)NULL);
					ms.x_PDst = (POSITION)NULL;
					m_dtpPDstDT.SetTime(p_2Day);
					m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);

					if (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) == LVIS_FOCUSED)
					{
						ShowPSetList();
					}

					switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
					{
					case IDC_OPT_SUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(pd.FPrmPQ()));
						break;
					case IDC_OPT_UUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(pd.FPrmPQ()));
						break;
					default:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), pd.FPrmPQ());
					}
					PAdjXQUpdate(tz);

					((CButton*)GetDlgItem(IDC_BTN_XFR))->SetCheck(0);
					GetDlgItem(IDC_BTN_XFR)->EnableWindow(0);
					ms.m_XAct = 0;

					ShowMatlList(xm);
				}
				else
				{
					if (ms.x_PDst == ms.m_PSets.x_PNew)
					{
						ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
					}
					ms.x_PDst = (POSITION)NULL;
					m_dtpPDstDT.SetTime(p_2Day);
					m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);

					if (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) == LVIS_FOCUSED)
					{
						ShowPSetList();
					}

					switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
					{
					case IDC_OPT_SUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(pd.FPrmPQ()));
						break;
					case IDC_OPT_UUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(pd.FPrmPQ()));
						break;
					default:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), pd.FPrmPQ());
					}
					PAdjXQUpdate(tz);

					((CButton*)GetDlgItem(IDC_BTN_NEW))->SetCheck(0);
					GetDlgItem(IDC_BTN_NEW)->EnableWindow(0);
					ms.m_XAct = 0;

					ShowMatlList(xm);
				}
			}


		}
	}

	GetDlgItem(IDC_LBL_PSRC)->SetWindowTextW(_T("from"));
	GetDlgItem(IDC_LBL_PDST)->SetWindowTextW(_T("to"));

	m_XAct = XA_NEDT;

	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(0);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(0);
	m_lvwPSet.UpDownEnable(true);

	m_edtPAdjXQ.SetReadOnly(1);

	ShowPSetList();
}

void CCustPOrdDlg::OnClickUndo()
{
	if (x_MSet == NULL)
		return;
	if ((InXXfr() == false) && (InXNew() == false))
		return;

	TCHAR				tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR				um[10];		memset(um, 0, sizeof(um));
	CCustPOrdMSet&		ms			= m_POrd.m_MSets.GetAt(x_MSet);
	LPMATL				pm			= MatlLRR(ms.MatlID);
	int					cs			= 0;

	for (int i = 0, c = m_lvwMatl.GetItemCount(); i < c; i++)
	{
		if (m_lvwMatl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			POSITION		xm = (POSITION)m_lvwMatl.GetItemData(i);
			CCustPOrdMSet&	ms = m_POrd.m_MSets.GetAt(xm);

			if (ms.x_PDst != NULL)
			{
				CCustPOrdMSetPSet&	pd = ms.m_PSets.Get(ms.x_PDst);

				if (ms.x_PSrc != NULL)
				{
					CCustPOrdMSetPSet&	ps = ms.m_PSets.Get(ms.x_PSrc);

					ms.UnMove(ps, pd);

					if (ms.x_PDst == ms.m_PSets.x_PNew)
					{
						ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
					}
					ms.x_PSrc = (POSITION)NULL;
					m_dtpPSrcDT.SetTime(p_2Day);
					m_dtpPSrcDT.SetTime((LPSYSTEMTIME)NULL);
					ms.x_PDst = (POSITION)NULL;
					m_dtpPDstDT.SetTime(p_2Day);
					m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);

					if (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) == LVIS_FOCUSED)
					{
						ShowPSetList();
					}

					pd.Dump(_T("UnMove::Dst"));
					ps.Dump(_T("UnMove::Src"));

					switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
					{
					case IDC_OPT_SUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(pd.FPrmPQ()));
						break;
					case IDC_OPT_UUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(pd.FPrmPQ()));
						break;
					default:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), pd.FPrmPQ());
					}
					PAdjXQUpdate(tz);

					((CButton*)GetDlgItem(IDC_BTN_XFR))->SetCheck(0);
					GetDlgItem(IDC_BTN_XFR)->EnableWindow(0);
					ms.m_XAct = 0;

					ShowMatlList(xm);
				}
				else
				{
					ms.UnEdit(pd);
					
					if (ms.x_PDst == ms.m_PSets.x_PNew)
					{
						ms.m_PSets.m_PNew.F.PrmdDT = SqlNull;
					}
					ms.x_PDst = (POSITION)NULL;
					m_dtpPDstDT.SetTime(p_2Day);
					m_dtpPDstDT.SetTime((LPSYSTEMTIME)NULL);

					if (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) == LVIS_FOCUSED)
					{
						ShowPSetList();
					}

					pd.Dump(_T("UnEdit::Dst"));

					switch(GetCheckedRadioButton(IDC_OPT_PUOM, IDC_OPT_UUOM))
					{
					case IDC_OPT_SUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), ms.DQtySQ(pd.FPrmPQ()));
						break;
					case IDC_OPT_UUOM:
						_stprintf_s<_countof(tz)>(tz, _T("%d"), ms.UQtyCT(pd.FPrmPQ()));
						break;
					default:
						_stprintf_s<_countof(tz)>(tz, _T("%.0f"), pd.FPrmPQ());
					}
					PAdjXQUpdate(tz);

					((CButton*)GetDlgItem(IDC_BTN_NEW))->SetCheck(0);
					GetDlgItem(IDC_BTN_NEW)->EnableWindow(0);
					ms.m_XAct = 0;

					ShowMatlList(xm);
				}
			}

			m_lvwMatl.SetItemState(i, 0, LVIS_SELECTED);

			if (m_lvwMatl.GetItemState(i, LVIS_FOCUSED) == LVIS_FOCUSED)
			{
				m_lvwMatl.SetItemState(i, 0, LVIS_FOCUSED);
			}
		}
	}

	GetDlgItem(IDC_LBL_PSRC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LBL_PSRC)->SetWindowTextW(_T("from"));
	GetDlgItem(IDC_LBL_PDST)->SetWindowTextW(_T("to"));

	m_XAct = XA_NEDT;

	GetDlgItem(IDC_BTN_UNDO)->EnableWindow(0);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(0);
	m_lvwPSet.UpDownEnable(true);

	m_edtPAdjXQ.SetReadOnly(1);

	ShowPSetList();
}

void CCustPOrdDlg::OnSelChangePOrd(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_tabPOrd.GetCurSel())
	{
	case 0:
		m_lvwALog.ShowWindow(SW_HIDE);
		m_edtCmntSZ.ShowWindow(SW_HIDE);

		m_lvwPSet.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_NEW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_XFR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRA_XFER)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBL_PSRC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DTP_PSRCDT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBL_PDST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DTP_PDSTDT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LBL_OPER)->ShowWindow(SW_SHOW);
		m_edtPAdjXQ.ShowWindow(SW_SHOW);
		m_edtXOrgXS.ShowWindow(SW_SHOW);
		m_edtXPrmXS.ShowWindow(SW_SHOW);
		m_edtXScnXS.ShowWindow(SW_SHOW);
		m_edtXShpXS.ShowWindow(SW_SHOW);

		break;

	case 1:
		m_lvwPSet.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_NEW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_XFR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_UNDO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SAVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRA_XFER)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBL_PSRC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DTP_PSRCDT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBL_PDST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DTP_PDSTDT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LBL_OPER)->ShowWindow(SW_HIDE);
		m_edtPAdjXQ.ShowWindow(SW_HIDE);
		m_edtXOrgXS.ShowWindow(SW_HIDE);
		m_edtXPrmXS.ShowWindow(SW_HIDE);
		m_edtXScnXS.ShowWindow(SW_HIDE);
		m_edtXShpXS.ShowWindow(SW_HIDE);

		m_lvwALog.ShowWindow(SW_SHOW);
		m_edtCmntSZ.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CCustPOrdDlg::OnItemChangingALog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW	pN			= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	TCHAR			tz[256];	memset(tz, 0, sizeof(tz));
	TCHAR			um[256];	memset(um, 0, sizeof(um));

	*pResult = 0;

	if (pN->iItem > -1)
	{
		if (x_MSet != NULL)
		{
			if (pN->uOldState == pN->uNewState)
			{
				return;
			}
			if ((pN->uOldState & LVIS_SELECTED) == LVIS_SELECTED)
			{
				m_edtCmntSZ.SetWindowTextW(_T(""));
			}
			if (((pN->uNewState & LVIS_SELECTED) == LVIS_SELECTED) || ((pN->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED))
			{
				LONG				iA = (LONG)pN->lParam;
				CCustPOrdMSet&		ms = m_POrd.m_MSets.GetAt(x_MSet);

				if (ms.pALog != NULL)
				{
					m_edtCmntSZ.SetWindowText((LPCTSTR)ms.pALog[iA].CmntSZ);
				}
			}
		}
	}
}

void CCustPOrdDlg::OnItemChangedALog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;
}
