// ExitDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "ExitDialog.h"
#include "afxdialogex.h"

#include "ComputerizedDanceClassroomApplicationDlg.h"

// CExitDialog dialog

IMPLEMENT_DYNAMIC(CExitDialog, CDialogEx)

CExitDialog::CExitDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExitDialog::IDD, pParent)
{

}

CExitDialog::~CExitDialog()
{
}

void CExitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExitDialog, CDialogEx)
	ON_BN_CLICKED(IDC_EXIT_YES_BUTTON, &CExitDialog::OnBnClickedExitYesButton)
	ON_BN_CLICKED(IDC_EXIT_NO_BUTTON, &CExitDialog::OnBnClickedExitNoButton)
END_MESSAGE_MAP()

BOOL CExitDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set font for buttons and text
	m_Font.CreatePointFont(140, _T("MS Shell Dlg"));
	GetDlgItem(IDC_STATIC_exit)->SetFont(&m_Font);
	GetDlgItem(IDC_EXIT_YES_BUTTON)->SetFont(&m_Font);
	GetDlgItem(IDC_EXIT_NO_BUTTON)->SetFont(&m_Font);

	return TRUE;
}


// CExitDialog message handlers

void CExitDialog::OnBnClickedExitYesButton()
{
	// TODO: Add your control notification handler code here
	// Exit the application
	exit(1);
}


void CExitDialog::OnBnClickedExitNoButton()
{
	// TODO: Add your control notification handler code here
	// Return
	CDialog::OnCancel();
}
