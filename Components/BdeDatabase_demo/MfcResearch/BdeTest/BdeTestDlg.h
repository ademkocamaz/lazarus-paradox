// BdeTestDlg.h : header file
//

#if !defined(AFX_BDETESTDLG_H__58669A66_0071_11D3_BA25_F6AA00F7CD7C__INCLUDED_)
#define AFX_BDETESTDLG_H__58669A66_0071_11D3_BA25_F6AA00F7CD7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBdeTestDlg dialog

class CBdeDatabase;

class CBdeTestDlg : public CDialog
{
// Construction
public:
	CBdeTestDlg(CWnd* pParent = NULL);	// standard constructor

	CBdeDatabase* m_pBdeDb;

	void UpdateDialogData(BOOL bSaveAndValidate = TRUE);
	void EnableControls();

	CString m_strAppPath;
	BOOL m_bParadox;

// Dialog Data
	//{{AFX_DATA(CBdeTestDlg)
	enum { IDD = IDD_BDETEST_DIALOG };
	CString	m_strBcd;
	CString	m_strChar;
	CString	m_strCurrency;
	CString	m_strDate;
	CString	m_strFloat;
	CString	m_strLogical;
	CString	m_strLong;
	CString	m_strMemo;
	CString	m_strShort;
	CString	m_strTime;
	CString	m_strTimeStamp;
	BOOL	m_bLogical;
	double	m_fBcd;
	double	m_fCurrency;
	COleDateTime	m_dtDate;
	double	m_fFloat;
	long	m_lLong;
	int		m_nShort;
	COleDateTime	m_dtTime;
	COleDateTime	m_dtTimeStamp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBdeTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBdeTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTestConnection();
	afx_msg void OnEdit();
	afx_msg void OnAppend();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnFirst();
	afx_msg void OnPrior();
	afx_msg void OnNext();
	afx_msg void OnLast();
	afx_msg void OnDelete();
	afx_msg void OnInsert();
	afx_msg void OnPost();
	afx_msg void OnCancelEdit();
	virtual void OnCancel();
	afx_msg void OnSetBlank();
	afx_msg void OnSetTypeValues();
	afx_msg void OnConnectDbase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BDETESTDLG_H__58669A66_0071_11D3_BA25_F6AA00F7CD7C__INCLUDED_)
