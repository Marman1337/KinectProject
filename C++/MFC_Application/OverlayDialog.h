#pragma once


// COverlayDialog dialog

class COverlayDialog : public CDialog
{
	DECLARE_DYNAMIC(COverlayDialog)

public:
	COverlayDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~COverlayDialog();
	BOOL OnInitDialog();
	CString loadFileBox;
	CString loadFileBox2;
	bool m_check_loadFileBox;
	bool m_check_loadFileBox2;

// Dialog Data
	enum { IDD = IDD_OVERLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBack_Overlay();
	afx_msg void OnBnClickedLoadButtonoverlay();
	afx_msg void OnBnClickedLoadButtonoverlay2();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedOverlayButton();
};
