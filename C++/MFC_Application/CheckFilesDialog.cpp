// CheckFilesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "CheckFilesDialog.h"
#include "afxdialogex.h"


// CCheckFilesDialog dialog

IMPLEMENT_DYNAMIC(CCheckFilesDialog, CDialogEx)

CCheckFilesDialog::CCheckFilesDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckFilesDialog::IDD, pParent)
{

}

CCheckFilesDialog::~CCheckFilesDialog()
{
}

void CCheckFilesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckFilesDialog, CDialogEx)
END_MESSAGE_MAP()

BOOL CCheckFilesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set font for record button
	m_Font.CreatePointFont(140, _T("MS Shell Dlg"));
	GetDlgItem(IDC_STATIC_checkfiles)->SetFont(&m_Font);

	return TRUE;
}

// CCheckFilesDialog message handlers
