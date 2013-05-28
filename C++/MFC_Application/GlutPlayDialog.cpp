// CGlutPlayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "GlutPlayDialog.h"
#include "afxdialogex.h"
#include "SampleViewer.h"
#include "PlayDialog.h"
#include "NiTE.h"
#include "ErrorDialog.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "ExitDialog.h"

//IMPLEMENT_DYNAMIC(CGlutPlayDialog, CDialogEx)

CGlutPlayDialog::CGlutPlayDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGlutPlayDialog::IDD, pParent)
{

}

CGlutPlayDialog::~CGlutPlayDialog()
{
}

void CGlutPlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGlutPlayDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1_GLUT_BACK, &CGlutPlayDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CGlutPlayDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGlutPlayDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO12, &CGlutPlayDialog::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CGlutPlayDialog::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CGlutPlayDialog::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CGlutPlayDialog::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_RADIO18, &CGlutPlayDialog::OnBnClickedRadio18)
	ON_BN_CLICKED(IDC_RADIO19, &CGlutPlayDialog::OnBnClickedRadio19)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CGlutPlayDialog message handlers
BOOL CGlutPlayDialog::OnInitDialog()
{
	m_Font_button.CreatePointFont(100, _T("MS Shell Dlg"));
	GetDlgItem(IDC_BUTTON1_GLUT_BACK)->SetFont(&m_Font_button);
	m_Font_text.CreatePointFont(100, _T("MS Shell Dlg"));

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_Font_text);

	CheckRadioButton(IDC_RADIO18,IDC_RADIO19,IDC_RADIO18);
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	CheckRadioButton(IDC_RADIO12,IDC_RADIO13,IDC_RADIO12);
	CheckRadioButton(IDC_RADIO14,IDC_RADIO15,IDC_RADIO14);

	OptionSelect = 1;
	skeletonFrameIndex = 0;

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

	return TRUE;
}

void CGlutPlayDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	sampleViewer.~SampleViewer();
	CDialogEx::OnCancel();
	CPlayDialog dlg;
	dlg.DoModal();
}

void CGlutPlayDialog::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingFrameId = true;
}

void CGlutPlayDialog::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingFrameId = false;
}

void CGlutPlayDialog::OnBnClickedRadio12()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingBackground = true;
}

void CGlutPlayDialog::OnBnClickedRadio13()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingBackground = false;
}

void CGlutPlayDialog::OnBnClickedRadio14()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingDepth = true;
}

void CGlutPlayDialog::OnBnClickedRadio15()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingDepth = false;
}

void CGlutPlayDialog::OnBnClickedRadio18()
{
	// TODO: Add your control notification handler code here
	g_drawStudentSkeleton = true;
}

void CGlutPlayDialog::OnBnClickedRadio19()
{
	// TODO: Add your control notification handler code here
	g_drawStudentSkeleton = false;
}


void CGlutPlayDialog::OnSysCommand(UINT nID, LPARAM lParam)
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