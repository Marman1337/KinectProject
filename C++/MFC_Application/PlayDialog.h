#pragma once


// CPlayDialog dialog

class CPlayDialog : public CDialog
{
	DECLARE_DYNAMIC(CPlayDialog)

public:
	CPlayDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlayDialog();
	BOOL OnInitDialog();
	CString loadFileBox;
	bool m_check_loadFileBox;

// Dialog Data
	enum { IDD = IDD_PLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBack_Play();
	afx_msg void OnBnClickedLoadButtonplay();

private:
	CFont m_Font;
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedPlayButton();
};
