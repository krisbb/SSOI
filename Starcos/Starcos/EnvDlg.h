#pragma once
#include "afxwin.h"


// EnvDlg dialog

class EnvDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EnvDlg)

public:
	EnvDlg(CString * Str, CWnd* pParent = NULL);   // standard constructor
	virtual ~EnvDlg();

// Dialog Data
	enum { IDD = IDD_ENVDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
public:
	CString * PartCmd;
	CComboBox EnvType;
	afx_msg void OnBnClickedOk();
};
