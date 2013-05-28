#pragma once


// CErrorDialog dialog

class CErrorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CErrorDialog)

public:
	CErrorDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CErrorDialog();

// Dialog Data
	enum { IDD = IDD_ERROR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	BOOL OnInitDialog();

private:
	CFont m_Font;
public:
	afx_msg void OnBnClickedBackButtonerror();
};
