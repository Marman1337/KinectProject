
// ComputerizedDanceClassroomApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "afxdialogex.h"
#include "RecordDialog.h"
#include "PlayDialog.h"
#include "SkeletonDialog.h"
#include "OverlayDialog.h"
#include "ExitDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT extern_nID;
LPARAM extern_lParam;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExitYesButton();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComputerizedDanceClassroomApplicationDlg dialog

CComputerizedDanceClassroomApplicationDlg::CComputerizedDanceClassroomApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComputerizedDanceClassroomApplicationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComputerizedDanceClassroomApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CComputerizedDanceClassroomApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDQUIT, &CComputerizedDanceClassroomApplicationDlg::OnBnClickedQuit)
	ON_BN_CLICKED(IDC_RECORD_BUTTON, &CComputerizedDanceClassroomApplicationDlg::OnBnClickedRecordButton)
	ON_BN_CLICKED(IDC_PLAY_BUTTON, &CComputerizedDanceClassroomApplicationDlg::OnBnClickedPlayButton)
	ON_BN_CLICKED(IDC_SKELETON_BUTTON, &CComputerizedDanceClassroomApplicationDlg::OnBnClickedSkeletonButton)
	ON_BN_CLICKED(IDC_OVERLAY_BUTTON, &CComputerizedDanceClassroomApplicationDlg::OnBnClickedOverlayButton)
END_MESSAGE_MAP()


// CComputerizedDanceClassroomApplicationDlg message handlers

BOOL CComputerizedDanceClassroomApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);

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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CComputerizedDanceClassroomApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE)
	{
		// add code so message pops up
		extern_nID = nID;
		extern_lParam = lParam;
		CExitDialog Dlg;
		Dlg.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComputerizedDanceClassroomApplicationDlg::OnPaint()
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
HCURSOR CComputerizedDanceClassroomApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// when the quit button is clicked, quit the application
void CComputerizedDanceClassroomApplicationDlg::OnBnClickedQuit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	PostQuitMessage(WM_QUIT);
}

// when the "Record from a live stream" button is clicked, go to "IDD_RECORD_DIALOG" Dialog Box
void CComputerizedDanceClassroomApplicationDlg::OnBnClickedRecordButton()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	CRecordDialog Dlg;
	Dlg.DoModal();
}

// when the "Record from a live stream" button is clicked, go to "IDD_PLAY_DIALOG" Dialog Box
void CComputerizedDanceClassroomApplicationDlg::OnBnClickedPlayButton()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	CPlayDialog Dlg;
	Dlg.DoModal();
}

// when the "Record from a live stream" button is clicked, go to "IDD_SKELETON_DIALOG" Dialog Box
void CComputerizedDanceClassroomApplicationDlg::OnBnClickedSkeletonButton()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	CSkeletonDialog Dlg;
	Dlg.DoModal();
}

// when the "Record from a live stream" button is clicked, go to "IDD_OVERLAY_DIALOG" Dialog Box
void CComputerizedDanceClassroomApplicationDlg::OnBnClickedOverlayButton()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	COverlayDialog Dlg;
	Dlg.DoModal();
}
