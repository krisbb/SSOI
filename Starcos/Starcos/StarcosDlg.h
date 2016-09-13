
// StarcosDlg.h : header file
//

#pragma once
#include "stm_api.h"
#include "afxwin.h"

// CStarcosDlg dialog
class CStarcosDlg : public CDialogEx
{
// Construction
public:
	CStarcosDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STARCOS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CString Command;
	CString Response;
	void ButtonConnect();
	void ButtonDisconnect();
	void Request();

	void ShowError(stmHandle hCard );
	stmHandle hCard;

	afx_msg void OpenExTerm();
	afx_msg void SendAPDU();
	CEdit CommandCtrl;
	afx_msg void getTermList();
	CComboBox TermList;
	afx_msg void GetATR();
	afx_msg void OnFileSelect();
	afx_msg void OnFileRead();
	afx_msg void OnFileUpdate();
	afx_msg void OnPIN();
	afx_msg void OnCipherEnc();
	afx_msg void OnCipherSetenv();
	afx_msg void OnSig();
	afx_msg void OnBnClickedBrutef();
	CEdit ResponseCtrl;
	afx_msg void OnAuth();
	afx_msg void OnBnClickedEject();
	afx_msg void OnBnClickedTermtype();
	afx_msg void OnBnClickedTermversion();
	afx_msg void OnBnClickedLibversion();
	afx_msg void OnBnClickedCardtype();
};
