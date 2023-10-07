// BdeTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BdeTest.h"
#include "BdeTestDlg.h"

#include "BdeDatabase.h"
#include "BdeException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBdeTestDlg dialog

CBdeTestDlg::CBdeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBdeTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBdeTestDlg)
	m_strBcd = _T("");
	m_strChar = _T("");
	m_strCurrency = _T("");
	m_strDate = _T("");
	m_strFloat = _T("");
	m_strLogical = _T("");
	m_strLong = _T("");
	m_strMemo = _T("");
	m_strShort = _T("");
	m_strTime = _T("");
	m_strTimeStamp = _T("");
	m_bLogical = FALSE;
	m_fBcd = 0.0;
	m_fCurrency = 0.0;
	m_dtDate = COleDateTime::GetCurrentTime();
	m_fFloat = 0.0;
	m_lLong = 0;
	m_nShort = 0;
	m_dtTime = COleDateTime::GetCurrentTime();
	m_dtTimeStamp = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pBdeDb = NULL;
	m_bParadox = TRUE;

}

void CBdeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBdeTestDlg)
	DDX_Text(pDX, ET_BCD, m_strBcd);
	DDX_Text(pDX, ET_CHAR, m_strChar);
	DDX_Text(pDX, ET_CURRENCY, m_strCurrency);
	DDX_Text(pDX, ET_DATE, m_strDate);
	DDX_Text(pDX, ET_FLOAT, m_strFloat);
	DDX_Text(pDX, ET_LOGICAL, m_strLogical);
	DDX_Text(pDX, ET_LONG, m_strLong);
	DDX_Text(pDX, ET_MEMO, m_strMemo);
	DDX_Text(pDX, ET_SHORT, m_strShort);
	DDX_Text(pDX, ET_TIME, m_strTime);
	DDX_Text(pDX, ET_TIMESTAMP, m_strTimeStamp);
	DDX_Check(pDX, CB_LOGICAL_TYPE, m_bLogical);
	DDX_Text(pDX, ET_BCD_TYPE, m_fBcd);
	DDX_Text(pDX, ET_CURRENCY_TYPE, m_fCurrency);
	DDX_Text(pDX, ET_DATE_TYPE, m_dtDate);
	DDX_Text(pDX, ET_FLOAT_TYPE, m_fFloat);
	DDX_Text(pDX, ET_LONG_TYPE, m_lLong);
	DDX_Text(pDX, ET_SHORT_TYPE, m_nShort);
	DDX_Text(pDX, ET_TIME_TYPE, m_dtTime);
	DDX_Text(pDX, ET_TIMESTAMP_TYPE, m_dtTimeStamp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBdeTestDlg, CDialog)
	//{{AFX_MSG_MAP(CBdeTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_TEST_CONNECTION, OnTestConnection)
	ON_BN_CLICKED(IDB_EDIT, OnEdit)
	ON_BN_CLICKED(IDB_APPEND, OnAppend)
	ON_BN_CLICKED(IDB_CONNECT, OnConnect)
	ON_BN_CLICKED(IDB_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDB_FIRST, OnFirst)
	ON_BN_CLICKED(IDB_PRIOR, OnPrior)
	ON_BN_CLICKED(IDB_NEXT, OnNext)
	ON_BN_CLICKED(IDB_LAST, OnLast)
	ON_BN_CLICKED(IDB_DELETE, OnDelete)
	ON_BN_CLICKED(IDB_INSERT, OnInsert)
	ON_BN_CLICKED(IDB_POST, OnPost)
	ON_BN_CLICKED(IDB_CANCEL_EDIT, OnCancelEdit)
	ON_BN_CLICKED(IDB_SET_BLANK, OnSetBlank)
	ON_BN_CLICKED(IDB_SET_TYPE_VALUES, OnSetTypeValues)
	ON_BN_CLICKED(IDB_CONNECT_DBASE, OnConnectDbase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBdeTestDlg message handlers

BOOL CBdeTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// get the directory in which the application is running
	char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
	const char *path = _pgmptr ;
  _splitpath(path, drive, dir, fname, ext );

	// get the Application path for the 
	m_strAppPath.Format("%s%s", drive, dir);




	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_pBdeDb = new CBdeDatabase();

	EnableControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBdeTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBdeTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CBdeTestDlg::OnCancel() 
{
	m_pBdeDb->CloseDatabase();
	m_pBdeDb->Uninitialize();

	delete m_pBdeDb;	
	
	CDialog::OnCancel();
}



void CBdeTestDlg::OnTestConnection() 
{
	try
	{
		if (m_pBdeDb->OpenDatabase(m_strAppPath + "Test.DB"))
			AfxMessageBox("Opened Database");
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;	
	}

	try
	{

		TRACE("%s\n", m_pBdeDb->GetFieldName(1));
		TRACE("%s\n", m_pBdeDb->GetFieldName(2));
		TRACE("%s\n", m_pBdeDb->GetFieldName(3));
		TRACE("%s\n", m_pBdeDb->GetFieldName(4));
		TRACE("%s\n", m_pBdeDb->GetFieldName(5));
		TRACE("%s\n", m_pBdeDb->GetFieldName(6));
		TRACE("%s\n", m_pBdeDb->GetFieldName(7));
		TRACE("%s\n", m_pBdeDb->GetFieldName(8));
		TRACE("%s\n", m_pBdeDb->GetFieldName(9));
		TRACE("%s\n", m_pBdeDb->GetFieldName(10));
		TRACE("%s\n", m_pBdeDb->GetFieldName(11));
		TRACE("%s\n", m_pBdeDb->GetFieldName(12));

		TRACE("\nField numbers\n");
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Char"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Float"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Long"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Short"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Currency"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Logical"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Date"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Time"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("TimeStamp"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Memo"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Formatted Memo"));
		TRACE("%d\n", m_pBdeDb->FieldNumberFromName("Graphic Blob"));

		
		BOOL bIsBlank;

		m_pBdeDb->MoveFirst();
		m_pBdeDb->MoveNext();
		while (m_pBdeDb->IsEOF() == FALSE)
		{
			TRACE("Char      %s\n", m_pBdeDb->GetFieldAsString(1, &bIsBlank));
			TRACE("Short     %g\n", m_pBdeDb->GetFieldAsFloat(2, &bIsBlank));
			TRACE("Long      %g\n", m_pBdeDb->GetFieldAsFloat(3, &bIsBlank));
			TRACE("Float     %g\n", m_pBdeDb->GetFieldAsFloat(4, &bIsBlank));
			TRACE("Currency  %g\n", m_pBdeDb->GetFieldAsFloat(5, &bIsBlank));
			TRACE("Logical   %s\n", m_pBdeDb->GetFieldAsString(6, &bIsBlank));
			TRACE("Date      %s\n", m_pBdeDb->GetFieldAsString(7, &bIsBlank));
			TRACE("Time      %s\n", m_pBdeDb->GetFieldAsString(8, &bIsBlank));
			TRACE("TimeStamp %s\n", m_pBdeDb->GetFieldAsString(9, &bIsBlank));
			TRACE("Memo      %s\n", m_pBdeDb->GetFieldAsString(10, &bIsBlank));
//			TRACE("FormMemo  %s\n", m_pBdeDb->GetFieldAsString(11, &bIsBlank));
//			TRACE("Graphic   %s\n", m_pBdeDb->GetFieldAsString(12, &bIsBlank));
			TRACE("BCD   %s\n---\n", m_pBdeDb->GetFieldAsString(13, &bIsBlank));

			TRACE("  Date      %s\n", m_pBdeDb->GetFieldAsDate(7, &bIsBlank).Format("%m-%d-%Y"));
			TRACE("  Time      %s\n", m_pBdeDb->GetFieldAsDate(8, &bIsBlank).Format("%H:%M:%S"));
			TRACE("  TimeStamp %s\n\n", m_pBdeDb->GetFieldAsDate(9, &bIsBlank).Format("%m-%d-%Y  %H:%M:%S"));
					
			m_pBdeDb->MoveNext();
		}

	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;	
	}
	
	if (m_pBdeDb->CloseDatabase())
		AfxMessageBox("Closed Database");
	EnableControls();
}


//////////////////////////////////////////////////////////////////////////////////////////
///

void CBdeTestDlg::UpdateDialogData(BOOL bSaveAndValidate)
{
	BOOL bIsBlank = FALSE;
	if (bSaveAndValidate)
	{
		UpdateData(TRUE);
		try
		{
			m_pBdeDb->SetFieldAsString(1, m_strChar);
			m_pBdeDb->SetFieldAsString(2, m_strShort);
			m_pBdeDb->SetFieldAsString(3, m_strLong);
			m_pBdeDb->SetFieldAsString(4, m_strFloat);
			m_pBdeDb->SetFieldAsString(5, m_strCurrency);
			m_pBdeDb->SetFieldAsString(6, m_strLogical);
			m_pBdeDb->SetFieldAsString(7, m_strDate);
			m_pBdeDb->SetFieldAsString(8, m_strTime);
			m_pBdeDb->SetFieldAsString(9, m_strTimeStamp);
			m_pBdeDb->SetFieldAsString(10, m_strMemo);
			m_pBdeDb->SetFieldAsString(13, m_strBcd);
			m_pBdeDb->Post();
		}
		catch (CBdeException* e)
		{
			e->ReportError();
			e->Delete();	
		}
	}
	else
	{
		try
		{
			if (m_pBdeDb->GetRecordCount() > 0)
			{
				if (m_pBdeDb->IsActive())
				{
					if (m_pBdeDb->GetEditMode() == FALSE)
					{
						m_strChar = m_pBdeDb->GetFieldAsString(1, &bIsBlank);
						m_strShort = m_pBdeDb->GetFieldAsString(2, &bIsBlank);
						m_strLong = m_pBdeDb->GetFieldAsString(3, &bIsBlank);
						m_strFloat = m_pBdeDb->GetFieldAsString(4, &bIsBlank);
						m_strCurrency = m_pBdeDb->GetFieldAsString(5, &bIsBlank);
						m_strLogical = m_pBdeDb->GetFieldAsString(6, &bIsBlank);
						m_strDate = m_pBdeDb->GetFieldAsString(7, &bIsBlank);
						m_strTime = m_pBdeDb->GetFieldAsString(8, &bIsBlank);
						m_strTimeStamp = m_pBdeDb->GetFieldAsString(9, &bIsBlank);
						if (m_bParadox) m_strMemo = m_pBdeDb->GetFieldAsString(10, &bIsBlank);
					//	m_strFormMemo = m_pBdeDb->GetFieldAsString(11, &bIsBlank);
					//	m_strGraphic = m_pBdeDb->GetFieldAsString(12, &bIsBlank);
						m_strBcd = m_pBdeDb->GetFieldAsString(13, &bIsBlank);

						m_nShort = m_pBdeDb->GetFieldAsInteger(2, &bIsBlank);
						m_lLong = m_pBdeDb->GetFieldAsInteger(3, &bIsBlank);
						m_fFloat = m_pBdeDb->GetFieldAsFloat(4, &bIsBlank);
						m_fCurrency = m_pBdeDb->GetFieldAsFloat(5, &bIsBlank);
						m_bLogical = m_pBdeDb->GetFieldAsBoolean(6, &bIsBlank);
						m_dtDate = m_pBdeDb->GetFieldAsDate(7, &bIsBlank);
						m_dtTime = m_pBdeDb->GetFieldAsDate(8, &bIsBlank);
						m_dtTimeStamp = m_pBdeDb->GetFieldAsDate(9, &bIsBlank);
						m_fBcd = m_pBdeDb->GetFieldAsFloat(13, &bIsBlank);
					} // end if Not in edit mode
				} // end if DB is active
			} // end if table is not empty
		}
		catch (CBdeException* e)
		{
			e->ReportError();
			e->Delete();	
		}
		UpdateData(FALSE);
	}
}


// Connect to paradox tables
void CBdeTestDlg::OnConnect() 
{
	try
	{
		if (m_pBdeDb->OpenDatabase(m_strAppPath + "Test.DB"))
			AfxMessageBox("Opened Database");
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	m_bParadox = TRUE;
	UpdateDialogData(FALSE);
	EnableControls();
}


// Connect to dBase tables
void CBdeTestDlg::OnConnectDbase() 
{
	try
	{
		if (m_pBdeDb->OpenDatabase(m_strAppPath + "Test.DBF"))
			AfxMessageBox("Opened Database");
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	m_bParadox = FALSE;
	UpdateDialogData(FALSE);
	EnableControls();
}


void CBdeTestDlg::OnDisconnect() 
{
	if (m_pBdeDb->CloseDatabase())
		AfxMessageBox("Closed Database");
	EnableControls();
}

void CBdeTestDlg::OnFirst() 
{
	try
	{
		m_pBdeDb->MoveFirst();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	UpdateDialogData(FALSE);
	EnableControls();
}

void CBdeTestDlg::OnPrior() 
{
	try
	{
		m_pBdeDb->MovePrior();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	UpdateDialogData(FALSE);
	EnableControls();
}

void CBdeTestDlg::OnNext() 
{
	try
	{
		m_pBdeDb->MoveNext();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	UpdateDialogData(FALSE);
	EnableControls();
}

void CBdeTestDlg::OnLast() 
{
	try
	{
		m_pBdeDb->MoveLast();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	UpdateDialogData(FALSE);
	EnableControls();
}

void CBdeTestDlg::OnDelete() 
{
	try
	{
		m_pBdeDb->DeleteRecord();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	UpdateDialogData(FALSE);
	EnableControls();
}


//////////////////////////////////////////////////////////////////////////////
//  Editing buttons commands


void CBdeTestDlg::OnCancelEdit() 
{
	try
	{
		m_pBdeDb->Cancel();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
	}
	UpdateDialogData(FALSE);
	EnableControls();
}


void CBdeTestDlg::OnEdit() 
{
	try
	{
		m_pBdeDb->Edit();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
	}
	EnableControls();
}

void CBdeTestDlg::OnAppend() 
{
	try
	{
		m_pBdeDb->Append();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
	}
	m_strBcd = _T("");
	m_strChar = _T("");
	m_strCurrency = _T("");
	m_strDate = _T("");
	m_strFloat = _T("");
	m_strLogical = _T("");
	m_strLong = _T("");
	m_strMemo = _T("");
	m_strShort = _T("");
	m_strTime = _T("");
	m_strTimeStamp = _T("");
	UpdateDialogData(FALSE);
	EnableControls();
}


void CBdeTestDlg::OnInsert() 
{
	try
	{
		m_pBdeDb->Insert();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
		return;
	}
	m_strBcd = _T("");
	m_strChar = _T("");
	m_strCurrency = _T("");
	m_strDate = _T("");
	m_strFloat = _T("");
	m_strLogical = _T("");
	m_strLong = _T("");
	m_strMemo = _T("");
	m_strShort = _T("");
	m_strTime = _T("");
	m_strTimeStamp = _T("");
	UpdateDialogData(FALSE);
	EnableControls();
}

void CBdeTestDlg::OnPost() 
{
	UpdateDialogData(TRUE);	
	EnableControls();
}


void CBdeTestDlg::EnableControls()
{
	GetDlgItem(IDB_TEST_CONNECTION)->EnableWindow(CBdeDatabase::EnableOpen(m_pBdeDb));
	GetDlgItem(IDB_EDIT)->EnableWindow(CBdeDatabase::EnableEdit(m_pBdeDb));
	GetDlgItem(IDB_APPEND)->EnableWindow(CBdeDatabase::EnableAppend(m_pBdeDb));
	GetDlgItem(IDB_CONNECT)->EnableWindow(CBdeDatabase::EnableOpen(m_pBdeDb));
	GetDlgItem(IDB_DISCONNECT)->EnableWindow(CBdeDatabase::EnableClose(m_pBdeDb));
	GetDlgItem(IDB_FIRST)->EnableWindow(CBdeDatabase::EnableFirst(m_pBdeDb));
	GetDlgItem(IDB_PRIOR)->EnableWindow(CBdeDatabase::EnablePrior(m_pBdeDb));
	GetDlgItem(IDB_NEXT)->EnableWindow(CBdeDatabase::EnableNext(m_pBdeDb));
	GetDlgItem(IDB_LAST)->EnableWindow(CBdeDatabase::EnableLast(m_pBdeDb));
	GetDlgItem(IDB_DELETE)->EnableWindow(CBdeDatabase::EnableDelete(m_pBdeDb));
	GetDlgItem(IDB_INSERT)->EnableWindow(CBdeDatabase::EnableInsert(m_pBdeDb));
	GetDlgItem(IDB_POST)->EnableWindow(CBdeDatabase::EnablePost(m_pBdeDb));
	GetDlgItem(IDB_SET_TYPE_VALUES)->EnableWindow(CBdeDatabase::EnablePost(m_pBdeDb));
	GetDlgItem(IDB_SET_BLANK)->EnableWindow(CBdeDatabase::EnablePost(m_pBdeDb));
	GetDlgItem(IDB_CANCEL_EDIT)->EnableWindow(CBdeDatabase::EnableCancel(m_pBdeDb));


	((CEdit*)GetDlgItem(ET_BCD))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_CHAR))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_CURRENCY))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_DATE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_FLOAT))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_LOGICAL))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_LONG))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_MEMO))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_SHORT))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_TIME))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_TIMESTAMP))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));

	((CEdit*)GetDlgItem(ET_BCD_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_CURRENCY_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_DATE_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_FLOAT_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(CB_LOGICAL_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_LONG_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_SHORT_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_TIME_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));
	((CEdit*)GetDlgItem(ET_TIMESTAMP_TYPE))->SetReadOnly(!CBdeDatabase::EnablePost(m_pBdeDb));

}


void CBdeTestDlg::OnSetBlank() 
{
	try
	{
		m_pBdeDb->SetFieldAsString(1, "blank", TRUE);
		m_pBdeDb->SetFieldAsInteger(2, 100, TRUE);
		m_pBdeDb->SetFieldAsInteger(3, 100, TRUE);
		m_pBdeDb->SetFieldAsFloat(4, 3.14158, TRUE);
		m_pBdeDb->SetFieldAsFloat(5, 3.14158, TRUE);
		m_pBdeDb->SetFieldAsBoolean(6, TRUE, TRUE);
		m_pBdeDb->SetFieldAsDate(7, COleDateTime::GetCurrentTime(), TRUE);
		m_pBdeDb->SetFieldAsDate(8, COleDateTime::GetCurrentTime(), TRUE);
		m_pBdeDb->SetFieldAsDate(9, COleDateTime::GetCurrentTime(), TRUE);
		m_pBdeDb->SetFieldAsString(10, "blank memo", TRUE);
		m_pBdeDb->Post();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
	}
	EnableControls();
	UpdateDialogData(FALSE);
}


void CBdeTestDlg::OnSetTypeValues() 
{
	try
	{
		m_pBdeDb->SetFieldAsString(1, "blank2", FALSE);
		m_pBdeDb->SetFieldAsInteger(2, 100, FALSE);
		m_pBdeDb->SetFieldAsInteger(3, 100, FALSE);
		m_pBdeDb->SetFieldAsFloat(4, 3.14158, FALSE);
		m_pBdeDb->SetFieldAsFloat(5, 3.14158, FALSE);
		m_pBdeDb->SetFieldAsBoolean(6, TRUE, FALSE);
		m_pBdeDb->SetFieldAsDate(7, COleDateTime::GetCurrentTime(), FALSE);
		m_pBdeDb->SetFieldAsDate(8, COleDateTime::GetCurrentTime(), FALSE);
		m_pBdeDb->SetFieldAsDate(9, COleDateTime::GetCurrentTime(), FALSE);
		m_pBdeDb->SetFieldAsString(10, "blank memo", FALSE);
		m_pBdeDb->Post();
	}
	catch (CBdeException* e)
	{
		e->ReportError();
		e->Delete();	
	}
	EnableControls();
	UpdateDialogData(FALSE);
}


