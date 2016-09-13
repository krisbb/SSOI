#pragma once
#include "afxwin.h"


// UpdateDlg dialog

class UpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpdateDlg)

public:
	UpdateDlg(CString * Str, CWnd* pParent = NULL);   // standard constructor
	virtual ~UpdateDlg();
	
// Dialog Data
	enum { IDD = IDD_UPDATEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString * PartCmd;
	CComboBox FileOpt;
	afx_msg void OnBnClickedOk();
	CEdit DataValue;
	CEdit RecordNum;
	CEdit Offset;
};
