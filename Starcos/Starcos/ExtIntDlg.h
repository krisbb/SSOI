#pragma once
#include "afxwin.h"


// ExtIntDlg dialog

class ExtIntDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExtIntDlg)

public:
	ExtIntDlg(CString * Str,CWnd* pParent = NULL);   // standard constructor
	virtual ~ExtIntDlg();

// Dialog Data
	enum { IDD = IDD_EXTINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CString * PartCmd;
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox ExtIntChoice;
	CEdit Challenge;
	afx_msg void OnBnClickedOk();
	CEdit KeyNum;
};
