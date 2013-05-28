// SkeletonDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "SkeletonDialog.h"
#include "afxdialogex.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"
#include <fstream>
#include <string>
#include "ExitDialog.h"
#include "CheckFilesDialog.h"
#include "GlutSkeletonDialog.h"

using namespace std;

string userSkeletonDataFile_student_skeleton;
string userSkeletonDataFile_teacher_skeleton;
string userOniRecordingFile_student_skeleton;
string userOniRecordingFile_teacher_skeleton;

// CSkeletonDialog dialog

IMPLEMENT_DYNAMIC(CSkeletonDialog, CDialog)

CSkeletonDialog::CSkeletonDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSkeletonDialog::IDD, pParent)
{
}

CSkeletonDialog::~CSkeletonDialog()
{
}

void CSkeletonDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_skeleton, loadFileBox);
	DDX_Text(pDX, IDC_EDIT_skeleton2, loadFileBox2);
	DDX_Text(pDX, IDC_EDIT_skeleton3, loadFileBox3);
	DDX_Text(pDX, IDC_EDIT_skeleton4, loadFileBox4);
}


BEGIN_MESSAGE_MAP(CSkeletonDialog, CDialog)
	ON_BN_CLICKED(IDBACK_Skeleton, &CSkeletonDialog::OnBnClickedBack_Skeleton)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_skeleton, &CSkeletonDialog::OnBnClickedLoadButtonskeleton)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_skeleton2, &CSkeletonDialog::OnBnClickedLoadButtonskeleton2)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_skeleton3, &CSkeletonDialog::OnBnClickedLoadButtonskeleton3)
	ON_BN_CLICKED(IDC_LOAD_BUTTON_skeleton4, &CSkeletonDialog::OnBnClickedLoadButtonskeleton4)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON2, &CSkeletonDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSkeletonDialog message handlers

// when the back button is clicked, return to the "IDD_STARTUP_DIALOG" Dialog Box
void CSkeletonDialog::OnBnClickedBack_Skeleton()
{
	// TODO: Add your control notification handler code here
	CComputerizedDanceClassroomApplicationDlg Dlg;
	CDialog::OnCancel();
	Dlg.DoModal();
}


void CSkeletonDialog::OnBnClickedLoadButtonskeleton()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(TRUE, L".oni", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"ONI file (*.oni)|*.oni||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Open Student Recording File";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	loadFileBox = fOpenDlg.GetPathName();
	}
	m_check_loadFileBox = true;
	UpdateData(FALSE);
}

void CSkeletonDialog::OnBnClickedLoadButtonskeleton2()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(TRUE, L".oni", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"ONI file (*.oni)|*.oni||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Open Teacher Recording File";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	loadFileBox2 = fOpenDlg.GetPathName();
	}
	m_check_loadFileBox2 = true;
	UpdateData(FALSE);
}


void CSkeletonDialog::OnBnClickedLoadButtonskeleton3()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(TRUE, L".txt", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"Normal Text file (*.txt)|*.txt||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Open Student Skeleton Data File";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	loadFileBox3 = fOpenDlg.GetPathName();
	}
	m_check_loadFileBox3 = true;
	UpdateData(FALSE);
}


void CSkeletonDialog::OnBnClickedLoadButtonskeleton4()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog fOpenDlg(TRUE, L".txt", NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_CREATEPROMPT|OFN_ENABLESIZING, L"Normal Text file (*.txt)|*.txt||", this);
  
	fOpenDlg.m_pOFN->lpstrTitle = L"Open Teacher Skeleton Data File";
  
	// if user selected "Ok" button
	if (fOpenDlg.DoModal() == IDOK)
	{
       	loadFileBox4 = fOpenDlg.GetPathName();
	}
	m_check_loadFileBox4 = true;
	UpdateData(FALSE);
}

void CSkeletonDialog::OnSysCommand(UINT nID, LPARAM lParam)
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

// if "compare skeletons" button is clicked
void CSkeletonDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if (m_check_loadFileBox == false || m_check_loadFileBox2 == false || m_check_loadFileBox3 == false || m_check_loadFileBox4 == false)
	{
		CCheckFilesDialog Dlg;
		Dlg.DoModal();
	}
	else
	{
		std::wstring ws(loadFileBox3);
		userSkeletonDataFile_student_skeleton.assign(ws.begin(), ws.end());

		std::wstring ws2(loadFileBox4);
		userSkeletonDataFile_teacher_skeleton.assign(ws2.begin(), ws2.end());

		std::wstring ws3(loadFileBox);
		userOniRecordingFile_student_skeleton.assign(ws3.begin(), ws3.end());

		std::wstring ws4(loadFileBox2);
		userOniRecordingFile_teacher_skeleton.assign(ws4.begin(), ws4.end());

		// Start Skeleton Window
		CDialog::OnOK();
		CGlutSkeletonDialog Dlg;
		Dlg.DoModal();
	}
}

BOOL CSkeletonDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_check_loadFileBox = false;
	m_check_loadFileBox2 = false;
	m_check_loadFileBox3 = false;
	m_check_loadFileBox4 = false;

	return TRUE;
}