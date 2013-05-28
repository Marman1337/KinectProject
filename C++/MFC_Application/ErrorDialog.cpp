// ErrorDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "ErrorDialog.h"
#include "afxdialogex.h"
#include "ExitDialog.h"
#include "ComputerizedDanceClassroomApplicationDlg.h"

// CErrorDialog dialog

IMPLEMENT_DYNAMIC(CErrorDialog, CDialogEx)

CErrorDialog::CErrorDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorDialog::IDD, pParent)
{

}

CErrorDialog::~CErrorDialog()
{
}

void CErrorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CErrorDialog, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BACK_BUTTON_error, &CErrorDialog::OnBnClickedBackButtonerror)
END_MESSAGE_MAP()


// CErrorDialog message handlers


void CErrorDialog::OnSysCommand(UINT nID, LPARAM lParam)
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

BOOL CErrorDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set font for back button
	m_Font.CreatePointFont(140, _T("MS Shell Dlg"));
	GetDlgItem(IDC_BACK_BUTTON_error)->SetFont(&m_Font);
	m_Font.CreatePointFont(140, _T("MS Shell Dlg"));
	GetDlgItem(IDC_STATIC_error)->SetFont(&m_Font);

	return TRUE;
}

void CErrorDialog::OnBnClickedBackButtonerror()
{
	// TODO: Add your control notification handler code here
	CComputerizedDanceClassroomApplicationDlg Dlg;
	CDialog::OnCancel();
	Dlg.DoModal();
}
