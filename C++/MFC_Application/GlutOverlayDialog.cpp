// CGlutOverlayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "GlutOverlayDialog.h"
#include "afxdialogex.h"
#include "OverlayDialog.h"
#include "NiTE.h"
#include "ErrorDialog.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "ExitDialog.h"

// CGlutOverlayDialog dialog

//IMPLEMENT_DYNAMIC(CGlutOverlayDialog, CDialogEx)

CGlutOverlayDialog::CGlutOverlayDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGlutOverlayDialog::IDD, pParent)
{

}

CGlutOverlayDialog::~CGlutOverlayDialog()
{
}

void CGlutOverlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGlutOverlayDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO18, &CGlutOverlayDialog::OnBnClickedRadio18)
	ON_BN_CLICKED(IDC_RADIO19, &CGlutOverlayDialog::OnBnClickedRadio19)
	ON_BN_CLICKED(IDC_RADIO1, &CGlutOverlayDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGlutOverlayDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO12, &CGlutOverlayDialog::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CGlutOverlayDialog::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CGlutOverlayDialog::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CGlutOverlayDialog::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_BUTTON1_GLUT_BACK, &CGlutOverlayDialog::OnBnClickedButton1)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CGlutOverlayDialog message handlers
BOOL CGlutOverlayDialog::OnInitDialog()
{
	m_Font_button.CreatePointFont(100, _T("MS Shell Dlg"));
	GetDlgItem(IDC_BUTTON1_GLUT_BACK)->SetFont(&m_Font_button);
	m_Font_text.CreatePointFont(100, _T("MS Shell Dlg"));
	GetDlgItem(IDC_STATIC1)->SetFont(& m_Font_text);
	GetDlgItem(IDC_STATIC2)->SetFont(& m_Font_text);
	GetDlgItem(IDC_STATIC4)->SetFont(& m_Font_text);
	GetDlgItem(IDC_STATIC5)->SetFont(& m_Font_text);

	CheckRadioButton(IDC_RADIO18,IDC_RADIO19,IDC_RADIO18);
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	CheckRadioButton(IDC_RADIO12,IDC_RADIO13,IDC_RADIO12);
	CheckRadioButton(IDC_RADIO14,IDC_RADIO15,IDC_RADIO14);

	OptionSelect = 3;
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
	h = rect.Height();
	w = rect.Width();

	openGLControl.Create(rect, this);

	return TRUE;
}

void CGlutOverlayDialog::OnBnClickedRadio18()
{
	// TODO: Add your control notification handler code here
	g_drawTeacherSkeleton = true;
}

void CGlutOverlayDialog::OnBnClickedRadio19()
{
	// TODO: Add your control notification handler code here
	g_drawTeacherSkeleton = false;
}

void CGlutOverlayDialog::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingFrameId = true;
}

void CGlutOverlayDialog::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingFrameId = false;
}

void CGlutOverlayDialog::OnBnClickedRadio12()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingBackground = true;
}

void CGlutOverlayDialog::OnBnClickedRadio13()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingBackground = false;
}

void CGlutOverlayDialog::OnBnClickedRadio14()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingDepth = true;
}

void CGlutOverlayDialog::OnBnClickedRadio15()
{
	// TODO: Add your control notification handler code here
	g_drawRecordingDepth = false;
}

void CGlutOverlayDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	sampleViewer.~SampleViewer();
	CDialogEx::OnCancel();
	COverlayDialog dlg;
	dlg.DoModal();
}


void CGlutOverlayDialog::OnSysCommand(UINT nID, LPARAM lParam)
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