
// GuiprojectDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "GlutSkeletonDialog.h"
#include "afxdialogex.h"
#include "NiTE.h"
#include "SkeletonDialog.h"
#include "ErrorDialog.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "ExitDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int userInput;
int OptionSelect;

SampleViewer sampleViewer;

CGlutSkeletonDialog::CGlutSkeletonDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGlutSkeletonDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlutSkeletonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


}

BEGIN_MESSAGE_MAP(CGlutSkeletonDialog, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1_GLUT_BACK, &CGlutSkeletonDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CGlutSkeletonDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGlutSkeletonDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CGlutSkeletonDialog::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CGlutSkeletonDialog::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CGlutSkeletonDialog::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CGlutSkeletonDialog::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CGlutSkeletonDialog::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CGlutSkeletonDialog::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CGlutSkeletonDialog::OnBnClickedRadio9)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CGlutSkeletonDialog message handlers

BOOL CGlutSkeletonDialog::OnInitDialog()
{
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Font_button.CreatePointFont(100, _T("MS Shell Dlg"));
	GetDlgItem(IDC_BUTTON1_GLUT_BACK)->SetFont(&m_Font_button);
	m_Font_text.CreatePointFont(100, _T("MS Shell Dlg"));

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_Font_text);
	CheckRadioButton(IDC_RADIO8,IDC_RADIO9,IDC_RADIO8);
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	CheckRadioButton(IDC_RADIO3,IDC_RADIO4,IDC_RADIO3);
	CheckRadioButton(IDC_RADIO5,IDC_RADIO6,IDC_RADIO5);

	skeletonFrameIndex = 0;

	OptionSelect = 2;
	openni::Status rc = openni::STATUS_OK;

	rc = sampleViewer.Init(0, NULL);
	if (rc != openni::STATUS_OK)
	{
		sampleViewer.~SampleViewer();
		CDialogEx::OnCancel();
		//CErrorDialog dlg;
		//dlg.DoModal();
		exit(1);
	}

	CRect rect;
	GetDlgItem(opengl_win)->GetWindowRect(rect);

	ScreenToClient(rect);

	openGLControl.Create(rect, this);
	// TODO: Add extra initialization here

	return TRUE;
}

void CGlutSkeletonDialog::OnPaint()
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
HCURSOR CGlutSkeletonDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGlutSkeletonDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	//PostQuitMessage(WM_QUIT);
	//sampleViewer2.Finalize();
	sampleViewer.~SampleViewer();
	CDialogEx::OnCancel();
	CSkeletonDialog dlg;
	dlg.DoModal();

}


void CGlutSkeletonDialog::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	 g_drawStudentSkeleton = true ;
}


void CGlutSkeletonDialog::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	g_drawStudentSkeleton = false ;
}


void CGlutSkeletonDialog::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	g_drawTeacherSkeleton = true;
}


void CGlutSkeletonDialog::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	g_drawTeacherSkeleton = false;
}


void CGlutSkeletonDialog::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	g_drawLiveFrameId = true;
}


void CGlutSkeletonDialog::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here
	g_drawLiveFrameId = false;
}

void CGlutSkeletonDialog::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here
	 skeletonMode = 0;
}


void CGlutSkeletonDialog::OnBnClickedRadio8()
{
	// TODO: Add your control notification handler code here
	 skeletonMode = 1;
}


void CGlutSkeletonDialog::OnBnClickedRadio9()
{
	// TODO: Add your control notification handler code here
	 skeletonMode = 2;
}

void CGlutSkeletonDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	if (nID == SC_CLOSE)
	{
		// add code so message pops up
		extern_nID = nID;
		extern_lParam = lParam;
		CExitDialog Dlg;
		Dlg.DoModal();
	}
}