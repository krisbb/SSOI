#pragma once
#include "afxwin.h"


// CReadDlg dialog

class CReadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadDlg)

public:
	CReadDlg(CString * Str, CWnd* pParent = NULL);   // standard constructor
	virtual ~CReadDlg();

	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_READDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	CString * PartCmd;
public:
	virtual BOOL OnInitDialog();
	void init();
	CComboBox FileType;
	afx_msg void OnBnClickedOk();
	CEdit FileLength;
	CEdit RecordNum;
	CEdit Offset;
};
