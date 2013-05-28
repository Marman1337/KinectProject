// RecordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "RecordDialog.h"
#include "afxdialogex.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include <string>
#include "ExitDialog.h"
#include "CheckFilesDialog.h"
#include "GlutRecordDialog.h"

using namespace std;

string userSkeletonDataFile_student_record;
string userOniRecordingFile_student_record;

// CRecordDialog dialog

IMPLEMENT_DYNAMIC(CRecordDialog, CDialog)

CRecordDialog::CRecordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordDialog::IDD, pParent)
{

}

CRecordDialog::~CRecordDialog()
{
}

void CRecordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_record, saveFileBox);
	DDX_Text(pDX, IDC_EDIT_record2, saveFileBox2);
}


BEGIN_MESSAGE_MAP(CRecordDialog, CDialog)
	ON_BN_CLICKED(IDBACK_Record, &CRecordDialog::OnBnClickedBack_Record)
	ON_BN_CLICKED(IDC_SAVE_BUTTON_record, &CRecordDialog::OnBnClickedSaveButtonrecord)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_SAVE_BUTTON_record2, &CRecordDialog::OnBnClickedSaveButtonrecord2)
	ON_BN_CLICKED(IDC_RECORD_BUTTON, &CRecordDialog::OnBnClickedRecordButton)
END_MESSAGE_MAP()


// CRecordDialog message handlers


// when the back button is clicked, return to the "IDD_STARTUP_DIALOG" Dialog Box
void CRecordDialog::OnBnClickedBack_Record()
{
	// TODO: Add your control notification handler code here
	CComputerizedDanceClassroomApplicationDlg Dlg;
	CDialog::OnCancel();
	Dlg.DoModal();
}

// Dialog.cpp
BOOL CRecordDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set font for record button
	m_Font.CreatePointFont(140, _T("MS Shell Dlg"));
	GetDlgItem(IDC_RECORD_BUTTON)->SetFont(&m_Font);

	m_check_saveFileBox = false;
	m_check_saveFileBox2 = false;

	return TRUE;
}

void CRecordDialog::OnBnClickedSaveButtonrecord()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(FALSE, L".oni", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"ONI File (*.oni)|*.oni||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Save Recording As";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	saveFileBox = fOpenDlg.GetPathName();
	}
	m_check_saveFileBox = true;
	UpdateData(FALSE);
}

void CRecordDialog::OnBnClickedSaveButtonrecord2()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(FALSE, L".txt", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"Normal Text file (*.txt)|*.txt||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Save Skeleton Data File As";

	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	saveFileBox2 = fOpenDlg.GetPathName();
	}
	m_check_saveFileBox2 = true;
	UpdateData(FALSE);
}

void CRecordDialog::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRecordDialog::OnBnClickedRecordButton()
{
	// TODO: Add your control notification handler code here
	if (m_check_saveFileBox == false || m_check_saveFileBox2 == false)
	{
		CCheckFilesDialog Dlg;
		Dlg.DoModal();
	}
	else
	{
		std::wstring ws(saveFileBox);
		userOniRecordingFile_student_record.assign(ws.begin(), ws.end());

		std::wstring ws2(saveFileBox2);
		userSkeletonDataFile_student_record.assign(ws2.begin(), ws2.end());

		// Start Recording Window
		CDialog::OnOK();
		CGlutRecordDialog Dlg;
		Dlg.DoModal();
	}
}