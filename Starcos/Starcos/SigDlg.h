#pragma once
#include "afxwin.h"


// SigDlg dialog

class SigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SigDlg)

public:
	SigDlg(CString * Str, CWnd* pParent = NULL);   // standard constructor
	virtual ~SigDlg();

// Dialog Data
	enum { IDD = IDD_SIGNATURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CString * PartCmd;
	CComboBox Choice;
	CEdit DataValue;
	afx_msg void OnBnClickedOk();
};
