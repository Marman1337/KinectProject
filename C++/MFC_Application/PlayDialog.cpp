// PlayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "PlayDialog.h"
#include "afxdialogex.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include "ExitDialog.h"
#include "CheckFilesDialog.h"
#include "GlutPlayDialog.h"

string userOniRecordingFile_student_play;

// CPlayDialog dialog

IMPLEMENT_DYNAMIC(CPlayDialog, CDialog)

CPlayDialog::CPlayDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayDialog::IDD, pParent)
{

}

CPlayDialog::~CPlayDialog()
{
}

void CPlayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_play, loadFileBox);
}


BEGIN_MESSAGE_MAP(CPlayDialog, CDialog)
	ON_BN_CLICKED(IDBACK_Play, &CPlayDialog::OnBnClickedBack_Play)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_play, &CPlayDialog::OnBnClickedLoadButtonplay)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_PLAY_BUTTON, &CPlayDialog::OnBnClickedPlayButton)
END_MESSAGE_MAP()


// CPlayDialog message handlers

// when the back button is clicked, return to the "IDD_STARTUP_DIALOG" Dialog Box
void CPlayDialog::OnBnClickedBack_Play()
{
	// TODO: Add your control notification handler code here
	CComputerizedDanceClassroomApplicationDlg Dlg;
	CDialog::OnCancel();
	Dlg.DoModal();
}

BOOL CPlayDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_check_loadFileBox = false;

	// set font for record button
	m_Font.CreatePointFont(140, _T("MS Shell Dlg"));
	GetDlgItem(IDC_PLAY_BUTTON)->SetFont(&m_Font);

	return TRUE;
}


void CPlayDialog::OnBnClickedLoadButtonplay()
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


void CPlayDialog::OnSysCommand(UINT nID, LPARAM lParam)
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

// if "play" button is clicked
void CPlayDialog::OnBnClickedPlayButton()
{
	// TODO: Add your control notification handler code here
	if (m_check_loadFileBox == false)
	{
		CCheckFilesDialog Dlg;
		Dlg.DoModal();
	}
	else
	{
		std::wstring ws(loadFileBox);
		userOniRecordingFile_student_play.assign(ws.begin(), ws.end());
		// Start Play Window
		CDialog::OnOK();
		CGlutPlayDialog Dlg;
		Dlg.DoModal();
	}
}