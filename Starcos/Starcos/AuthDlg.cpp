// AuthDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "AuthDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

// AuthDlg dialog

IMPLEMENT_DYNAMIC(AuthDlg, CDialogEx)

AuthDlg::AuthDlg(CString * Str, CWnd* pParent /*=NULL*/)
	: CDialogEx(AuthDlg::IDD, pParent)
{
	this->PartCmd = Str;
}

AuthDlg::~AuthDlg()
{
}

void AuthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, AuthType);
	DDX_Control(pDX, IDC_EDIT1, PIN);
	DDX_Control(pDX, IDC_EDIT4, NewPIN);
	DDX_Control(pDX, IDC_EDIT2, KeyNum);
}


BEGIN_MESSAGE_MAP(AuthDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AuthDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AuthDlg message handlers

BOOL AuthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	this->AuthType.InsertString( 0 , L"VERIFY WITH PIN");
	this->AuthType.InsertString( 1 , L"CHANGE PIN");

	//In next Version
	//this->AuthType.AddString(L"External");
	//this->AuthType.AddString(L"Internal");
	this->AuthType.SetCurSel(0);

	this->KeyNum.SetWindowTextW(L"1");

	return TRUE;
}

void AuthDlg::OnBnClickedOk()
{
	CString AuthType, KeyNum, /*ResKey,*/ PIN ,NewPIN;

	this->AuthType.GetWindowTextW(AuthType);
	this->PIN.GetWindowTextW(PIN);
	//this->ResKey.GetWindowTextW(ResKey);
	this->NewPIN.GetWindowTextW(NewPIN);
	this->KeyNum.GetWindowTextW(KeyNum);
	
	PIN.SetString(HexUtil::MakeParity(PIN,false));
	NewPIN.SetString(HexUtil::MakeParity(NewPIN,false));

	//KeyNum.SetString(HexUtil::MakeParity(KeyNum,true));
	//ResKey.SetString(HexUtil::MakeParity(ResKey,true));

	if(AuthType == "VERIFY WITH PIN")
	{
		this->PartCmd->Append(L"00 20 00 8");
		this->PartCmd->Append(KeyNum + L" ");
		this->PartCmd->Append(HexUtil::IntToHex(HexUtil::GetLength(PIN)));
		this->PartCmd->Append(L" " + PIN);
	}
	else if(AuthType == "CHANGE PIN")
	{
		this->PartCmd->Append(L"00 24 00 8");
		this->PartCmd->Append(KeyNum + L" ");
		this->PartCmd->Append(HexUtil::IntToHex(HexUtil::GetLength(PIN + NewPIN)));
		this->PartCmd->Append(L" " + PIN + L" " + NewPIN );
	}
	else
	{
		return;
	}

	CDialogEx::OnOK();
}
