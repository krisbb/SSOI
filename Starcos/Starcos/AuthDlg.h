#pragma once
#include "afxwin.h"


// AuthDlg dialog

class AuthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AuthDlg)

public:
	AuthDlg(CString * Str, CWnd* pParent = NULL);   // standard constructor
	virtual ~AuthDlg();

// Dialog Data
	enum { IDD = IDD_AUTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CString * PartCmd;
	DECLARE_MESSAGE_MAP()
public:
	CComboBox AuthType;
	CEdit PIN;
	CEdit NewPIN;
	CEdit KeyNum;
	afx_msg void OnBnClickedOk();
};
