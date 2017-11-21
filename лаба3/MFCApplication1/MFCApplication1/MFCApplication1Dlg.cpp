
// MFCApplication1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_U(0)
	, m_FREQ(0)
	, m_L(0)
	, m_Ant(TRUE)
	, m_res(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROB, m_P);
	DDX_Text(pDX, IDC_EDIT_MARK, m_U);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_FREQ);
	DDV_MinMaxInt(pDX, m_FREQ, 1, 365);
	DDX_Text(pDX, IDC_EDIT_SEQ, m_L);
	DDV_MinMaxFloat(pDX, m_L, 0, 1);

	DDX_Check(pDX, IDC_CHECK_ANTIVIR, m_Ant);
	DDX_Text(pDX, ID_STATIC_SUMMA, m_res);
	DDX_Control(pDX, IDC_EDIT_SEQ, m_Sq);
	DDV_MinMaxFloat(pDX, m_P, 0, 1);
	DDV_MinMaxInt(pDX, m_U, 0, INT_MAX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_ANTIVIR, &CMFCApplication1Dlg::OnBnClickedCheckAntivir)
	ON_BN_CLICKED(ID_BUTTON_CALCULATE, &CMFCApplication1Dlg::OnBnClickedButtonCalculate)
	ON_STN_CLICKED(IDC_STATIC_PROB2, &CMFCApplication1Dlg::OnStnClickedStaticProb2)
	ON_EN_CHANGE(IDC_EDIT_SEQ, &CMFCApplication1Dlg::OnEnChangeEditSeq)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_P = 0.3;
	m_FREQ = 25;
	m_U = 2000;
	m_L = 0.2;
	m_Sq.EnableWindow(TRUE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedCheckAntivir()
{
	nrClicks++;
	if (nrClicks % 2 == 0)
	{
		m_Sq.EnableWindow(TRUE);
	}
	else
	{
		m_Sq.EnableWindow(FALSE);
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonCalculate()
{
	UpdateData(TRUE);//берем данные с окна

	if ((m_P >= 0 && m_P <= 1) && (m_L >= 0 && m_L <= 1) && (m_FREQ >= 1 && m_FREQ <= 365) && m_U >= 0)
	{
		m_res = m_P * (1 - m_L) * m_U * 365 / m_FREQ; /// не знаю какой знак поставить с * сдишком большие числа
	}
	UpdateData(FALSE); //кидаем инфу в окно
}


void CMFCApplication1Dlg::OnStnClickedStaticProb2()
{
	// TODO: Add your control notification handler code here
}


void CMFCApplication1Dlg::OnEnChangeEditSeq()
{
	
	

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
