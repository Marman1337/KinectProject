// OverlayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "OverlayDialog.h"
#include "afxdialogex.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "ExitDialog.h"
#include "CheckFilesDialog.h"
#include "GlutOverlayDialog.h"

string userSkeletonDataFile_teacher_overlay;
string userOniRecordingFile_student_overlay;

// COverlayDialog dialog

IMPLEMENT_DYNAMIC(COverlayDialog, CDialog)

COverlayDialog::COverlayDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COverlayDialog::IDD, pParent)
{
}

COverlayDialog::~COverlayDialog()
{
}

void COverlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_overlay, loadFileBox);
	DDX_Text(pDX, IDC_EDIT_overlay2, loadFileBox2);
}


BEGIN_MESSAGE_MAP(COverlayDialog, CDialog)
	ON_BN_CLICKED(IDBACK_Overlay, &COverlayDialog::OnBnClickedBack_Overlay)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_overlay, &COverlayDialog::OnBnClickedLoadButtonoverlay)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_overlay2, &COverlayDialog::OnBnClickedLoadButtonoverlay2)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_OVERLAY_BUTTON, &COverlayDialog::OnBnClickedOverlayButton)
END_MESSAGE_MAP()


// COverlayDialog message handlers

// when the back button is clicked, return to the "IDD_STARTUP_DIALOG" Dialog Box
void COverlayDialog::OnBnClickedBack_Overlay()
{
	// TODO: Add your control notification handler code here
	CComputerizedDanceClassroomApplicationDlg Dlg;
	CDialog::OnCancel();
	Dlg.DoModal();
}


void COverlayDialog::OnBnClickedLoadButtonoverlay()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(TRUE, L".oni", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"ONI file (*.oni)|*.oni||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Open Recording File";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	loadFileBox = fOpenDlg.GetPathName();
	}
	m_check_loadFileBox = true;
	UpdateData(FALSE);
}


void COverlayDialog::OnBnClickedLoadButtonoverlay2()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(TRUE, L".txt", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"Normal Text file (*.txt)|*.txt||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Open Skeleton Data File";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	loadFileBox2 = fOpenDlg.GetPathName();
	}
	m_check_loadFileBox2 = true;
	UpdateData(FALSE);
}


void COverlayDialog::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL COverlayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_check_loadFileBox = false;
	m_check_loadFileBox2 = false;

	return TRUE;
}

void COverlayDialog::OnBnClickedOverlayButton()
{
	// TODO: Add your control notification handler code here
	if (m_check_loadFileBox == false || m_check_loadFileBox2 == false)
	{
		CCheckFilesDialog Dlg;
		Dlg.DoModal();
	}
	else
	{
		std::wstring ws(loadFileBox);
		userOniRecordingFile_student_overlay.assign(ws.begin(), ws.end());

		std::wstring ws2(loadFileBox2);
		userSkeletonDataFile_teacher_overlay.assign(ws2.begin(), ws2.end());

		// Start Overlay Window
		CDialog::OnOK();
		CGlutOverlayDialog Dlg;
		Dlg.DoModal();
	}
}