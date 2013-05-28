#pragma once

#include "OpenGLControl.h"
#include "SampleViewer.h"
#include "afxcmn.h"

// CGlutPlayDialog dialog

class CGlutPlayDialog : public CDialogEx
{

public:
	CGlutPlayDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGlutPlayDialog();
	 
// Dialog Data
	enum { IDD = IDD_GLUT_PLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	COpenGLControl openGLControl;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio15();
	afx_msg void OnBnClickedRadio18();
	afx_msg void OnBnClickedRadio19();
private:
	CFont m_Font_button;
	CFont m_Font_text;
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
