#pragma once

// CExitDialog dialog

class CExitDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CExitDialog)

public:
	CExitDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExitDialog();
	BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CFont m_Font;
public:
	afx_msg void OnBnClickedExitYesButton();
	afx_msg void OnBnClickedExitNoButton();
};
