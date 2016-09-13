#pragma once
#include "afxwin.h"


// CipherDlg dialog

class CipherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CipherDlg)

public:
	CipherDlg(CString * Str , CWnd* pParent = NULL);   // standard constructor
	virtual ~CipherDlg();

// Dialog Data
	enum { IDD = IDD_CIPHER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CString * PartCmd;
	DECLARE_MESSAGE_MAP()
public:
	CComboBox Mode;
	CEdit KeyNum;
	CEdit DataValue;
	afx_msg void OnBnClickedOk();
};
