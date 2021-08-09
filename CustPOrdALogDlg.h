#pragma once


// CCustPOrdALogDlg dialog

class CCustPOrdALogDlg : public CDialog
{
	DECLARE_DYNAMIC(CCustPOrdALogDlg)

public:
	CCustPOrdALogDlg(CWnd* pParent, LPCTSTR lpCaption, LPCTSTR lpMessage, LPCTSTR lpComment = NULL, UINT roComment = 0);   // standard constructor
	virtual ~CCustPOrdALogDlg();

	LPCTSTR GetCmnt()
	{
		return ((LPCTSTR)m_tzBuf);
	}

public:
	void AddActn(LPCTSTR tzActn);

private:
	LPCTSTR			m_pWCap;
	LPCTSTR			m_pAMsg;
	LPCTSTR			m_pCmnt;
	TCHAR			m_tzBuf[256];
	UINT			m_roEdt;
	CStringList		m_Actns;

// Dialog Data
	enum { IDD = IDD_DLG_CUSTPORDALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnClickBtnOK();
	afx_msg void OnClickBtnXX();
};
