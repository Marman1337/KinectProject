// CGlutRecordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "GlutRecordDialog.h"
#include "afxdialogex.h"
#include "RecordDialog.h"
#include "ErrorDialog.h"
#include "NiTE.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "ExitDialog.h"

// CGlutRecordDialog dialog

//IMPLEMENT_DYNAMIC(CGlutRecordDialog, CDialogEx)

CGlutRecordDialog::CGlutRecordDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGlutRecordDialog::IDD, pParent)
{

}

CGlutRecordDialog::~CGlutRecordDialog()
{
}

void CGlutRecordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGlutRecordDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO18, &CGlutRecordDialog::OnBnClickedRadio18)
	ON_BN_CLICKED(IDC_RADIO19, &CGlutRecordDialog::OnBnClickedRadio19)
	ON_BN_CLICKED(IDC_RADIO1, &CGlutRecordDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGlutRecordDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO12, &CGlutRecordDialog::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CGlutRecordDialog::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CGlutRecordDialog::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CGlutRecordDialog::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_BUTTON2_START_RECORDING, &CGlutRecordDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4_STOP_RECORDING, &CGlutRecordDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1_GLUT_BACK, &CGlutRecordDialog::OnBnClickedButton1)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CGlutRecordDialog message handlers
BOOL CGlutRecordDialog::OnInitDialog()
{	
	OptionSelect = 0;

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

	m_Font_button.CreatePointFont(100, _T("MS Shell Dlg"));
	GetDlgItem(IDC_BUTTON1_GLUT_BACK)->SetFont(&m_Font_button);
	GetDlgItem(IDC_BUTTON2_START_RECORDING)->SetFont(&m_Font_button);
	GetDlgItem(IDC_BUTTON4_STOP_RECORDING)->SetFont(&m_Font_button);
	m_Font_text.CreatePointFont(100, _T("MS Shell Dlg"));
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_Font_text);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_Font_text);
	CheckRadioButton(IDC_RADIO18,IDC_RADIO19,IDC_RADIO18);
	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);
	CheckRadioButton(IDC_RADIO10,IDC_RADIO11,IDC_RADIO10);
	CheckRadioButton(IDC_RADIO12,IDC_RADIO13,IDC_RADIO12);
	CheckRadioButton(IDC_RADIO14,IDC_RADIO15,IDC_RADIO14);

	CRect rect;
	GetDlgItem(opengl_win)->GetWindowRect(rect);

	ScreenToClient(rect);

	openGLControl.Create(rect, this);

	return TRUE;
}

void CGlutRecordDialog::OnBnClickedRadio18()
{
	// TODO: Add your control notification handler code here
	g_drawStudentSkeleton = true;
}

void CGlutRecordDialog::OnBnClickedRadio19()
{
	// TODO: Add your control notification handler code here
	g_drawStudentSkeleton = false;
}

void CGlutRecordDialog::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	g_drawLiveFrameId = true;
}

void CGlutRecordDialog::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	g_drawLiveFrameId = false;
}

void CGlutRecordDialog::OnBnClickedRadio12()
{
	// TODO: Add your control notification handler code here
	g_drawLiveBackground = true;
}

void CGlutRecordDialog::OnBnClickedRadio13()
{
	// TODO: Add your control notification handler code here
	g_drawLiveBackground = false;
}

void CGlutRecordDialog::OnBnClickedRadio14()
{
	// TODO: Add your control notification handler code here
	g_drawLiveDepth = true;
}

void CGlutRecordDialog::OnBnClickedRadio15()
{
	// TODO: Add your control notification handler code here
	g_drawLiveDepth = false;
}

void CGlutRecordDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	/*g_startRecording = true;
	g_rPressed = true;*/
	g_rPressed = true;
}

void CGlutRecordDialog::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	/*g_stopRecording = true;
	g_pPressed = true;*/
	g_stopRecording = true;
}

void CGlutRecordDialog::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	sampleViewer.~SampleViewer();
	CDialogEx::OnCancel();
	CRecordDialog dlg;
	dlg.DoModal();
}

void CGlutRecordDialog::OnSysCommand(UINT nID, LPARAM lParam)
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