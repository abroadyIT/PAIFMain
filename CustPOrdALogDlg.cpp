// CustPOrdALogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PAIFMain.h"
#include "CustPOrdALogDlg.h"


// CCustPOrdALogDlg dialog

IMPLEMENT_DYNAMIC(CCustPOrdALogDlg, CDialog)

CCustPOrdALogDlg::CCustPOrdALogDlg(CWnd* pParent, LPCTSTR lpCaption, LPCTSTR lpMessage, LPCTSTR lpComment, UINT roComment) : 
	CDialog(CCustPOrdALogDlg::IDD, pParent),
	m_pWCap(lpCaption),
	m_pAMsg(lpMessage),
	m_pCmnt(lpComment),
	m_roEdt(roComment)
{
}

CCustPOrdALogDlg::~CCustPOrdALogDlg()
{
}

void CCustPOrdALogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustPOrdALogDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CCustPOrdALogDlg::OnClickBtnOK)
END_MESSAGE_MAP()


void CCustPOrdALogDlg::AddActn(LPCTSTR tzActn)
{
	m_Actns.AddTail(tzActn);
}

// CCustPOrdALogDlg message handlers
BOOL CCustPOrdALogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_pWCap)
		SetWindowText(m_pWCap);
	if (m_pCmnt)
		GetDlgItem(IDC_EDT_CMNTSZ)->SetWindowText(m_pCmnt);

	((CEdit*)GetDlgItem(IDC_EDT_CMNTSZ))->SetReadOnly(m_roEdt);

	for (POSITION i = m_Actns.GetHeadPosition(); i != NULL; m_Actns.GetNext(i))
	{
		CString& s = m_Actns.GetAt(i);
		((CComboBox*)GetDlgItem(IDC_CBO_ACTNRG))->AddString((LPCTSTR)s);
	}

	return (FALSE);
}

void CCustPOrdALogDlg::OnClickBtnOK()
{
	GetDlgItem(IDC_EDT_CMNTSZ)->GetWindowText(m_tzBuf, 256);

	if ((m_roEdt == 0) && (_tcslen(m_tzBuf) == 0))
	{
		::MessageBox(m_hWnd, _T("One or more reasons for PO Update is required"), _T("Enter reason(s)"), MB_OK);
		return;
	}

	EndDialog(IDOK);
}
