
// ComputerizedDanceClassroomApplicationDlg.h : header file
//

#pragma once

#define STARTUP_SIZE_X 320
#define STARTUP_SIZE_Y 200

extern UINT extern_nID;
extern LPARAM extern_lParam;

// CComputerizedDanceClassroomApplicationDlg dialog
class CComputerizedDanceClassroomApplicationDlg : public CDialogEx
{
// Construction
public:
	CComputerizedDanceClassroomApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COMPUTERIZEDDANCECLASSROOMAPPLICATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRecordButton();
	afx_msg void OnBnClickedPlayButton();
	afx_msg void OnBnClickedSkeletonButton();
	afx_msg void OnBnClickedOverlayButton();
};
