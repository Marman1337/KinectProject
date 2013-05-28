#pragma once


// CSkeletonDialog dialog

class CSkeletonDialog : public CDialog
{
	DECLARE_DYNAMIC(CSkeletonDialog)

public:
	CSkeletonDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSkeletonDialog();
	BOOL OnInitDialog();
	CString loadFileBox;
	CString loadFileBox2;
	CString loadFileBox3;
	CString loadFileBox4;
	bool m_check_loadFileBox;
	bool m_check_loadFileBox2;
	bool m_check_loadFileBox3;
	bool m_check_loadFileBox4;


// Dialog Data
	enum { IDD = IDD_SKELETON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBack_Skeleton();
	afx_msg void OnBnClickedLoadButtonskeleton();
	afx_msg void OnBnClickedLoadButtonskeleton2();
	afx_msg void OnBnClickedLoadButtonskeleton3();
	afx_msg void OnBnClickedLoadButtonskeleton4();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedButton2();
};
