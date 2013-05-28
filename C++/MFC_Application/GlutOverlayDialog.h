#pragma once
#include "OpenGLControl.h"
#include "SampleViewer.h"
#include "afxcmn.h"

// overlay dialog

class CGlutOverlayDialog : public CDialogEx
{

public:
	CGlutOverlayDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGlutOverlayDialog();

// Dialog Data
	enum { IDD = IDD_GLUT_OVERLAY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL CGlutOverlayDialog::OnInitDialog();
	COpenGLControl openGLControl;
	DECLARE_MESSAGE_MAP()
public:
	int h,w;
	afx_msg void OnBnClickedRadio18();
	afx_msg void OnBnClickedRadio19();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio15();
	afx_msg void OnBnClickedButton1();
private:
	CFont m_Font_button;
	CFont m_Font_text;
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
