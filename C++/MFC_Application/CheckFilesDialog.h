#pragma once


// CCheckFilesDialog dialog

class CCheckFilesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckFilesDialog)

public:
	CCheckFilesDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckFilesDialog();
	BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_CHECK_FILES_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CFont m_Font;
};
