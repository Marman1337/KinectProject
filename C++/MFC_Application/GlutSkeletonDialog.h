
// GlutSkeletonDialog.h : header file
//

#pragma once

#include "OpenGLControl.h"
#include "SampleViewer.h"
#include "afxcmn.h"

// CGlutSkeletonDialog dialog

class CGlutSkeletonDialog : public CDialogEx
{
// Construction
public:
	CGlutSkeletonDialog(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_GLUT_SKELETON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;
	COpenGLControl openGLControl;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
private:
	CFont m_Font_button;
	CFont m_Font_text;
	
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
