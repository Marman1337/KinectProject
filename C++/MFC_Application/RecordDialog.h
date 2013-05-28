#pragma once


// CRecordDialog dialog

class CRecordDialog : public CDialog
{
	DECLARE_DYNAMIC(CRecordDialog)

public:
	CRecordDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecordDialog();
	CString saveFileBox;
	CString saveFileBox2;
	bool m_check_saveFileBox;
	bool m_check_saveFileBox2;

// Dialog Data
	enum { IDD = IDD_RECORD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBack_Record();
	BOOL OnInitDialog();

private:
	CFont m_Font;
public:
	afx_msg void OnBnClickedSaveButtonrecord();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedSaveButtonrecord2();
	afx_msg void OnBnClickedRecordButton();
};
