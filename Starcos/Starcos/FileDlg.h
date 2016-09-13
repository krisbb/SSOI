#pragma once
#include "afxwin.h"


// FileDlg dialog

class FileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileDlg)

public:
	FileDlg( CString * Str, CWnd* pParent = NULL);   // standard constructor
	virtual ~FileDlg();

	virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_FILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString * PartCmd;
	bool TestFID( CString FID , int Maxcount);
	afx_msg void OnBnClickedOk();
	CEdit FileID;
	//afx_msg void OnEnChangeEdit1(); function control what is passed to edit control 
};
