// EnvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "EnvDlg.h"
#include "afxdialogex.h"


// EnvDlg dialog

IMPLEMENT_DYNAMIC(EnvDlg, CDialogEx)

EnvDlg::EnvDlg(CString * Str , CWnd* pParent /*=NULL*/)
	: CDialogEx(EnvDlg::IDD, pParent)
{
	this->PartCmd = Str;
}

EnvDlg::~EnvDlg()
{
}

void EnvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, EnvType);
}

BOOL EnvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->EnvType.InsertString( 0 , L"Encipherment");
	this->EnvType.InsertString( 1 , L"Decipherement");
	this->EnvType.InsertString( 2 , L"Generate key pair");
	this->EnvType.InsertString( 3 , L"Compute Signature");
	this->EnvType.InsertString( 4 , L"Verify Signature");
	this->EnvType.InsertString( 5 , L"External Auth");
	this->EnvType.InsertString( 6 , L"Internal Auth");

	this->EnvType.SetCurSel(0);

	//this->EnvType.InsertString( 0 , L"Calc Hash");
	//this->EnvType.InsertString( 0 , L"SM response");
	//this->EnvType.InsertString( 0 , L"SM command");

	return TRUE;
}

BEGIN_MESSAGE_MAP(EnvDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &EnvDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// EnvDlg message handlers


void EnvDlg::OnBnClickedOk()
{
	CString EnvType;
	this->PartCmd->Append( L"00 22 ");

	this->EnvType.GetWindowTextW(EnvType);
	
	if(EnvType == "Encipherment")
	{
		this->PartCmd->Append(L"81 B8 ");
		//add to str tag 83 || 84 public or private key 
		// key num reference tag 80 or 40
		// algorithm ID tag 89

	}
	else if(EnvType == "Decipherement")
	{
		//00 22 41 B8 05 84 03 80 01 00 
		this->PartCmd->Append(L"41 B8 ");
	}
	else if(EnvType == "Generate key pair")
	{
		// 00 22 41 B6 08 84 03 80 01 00 89 01 41 
		this->PartCmd->Append(L"41 B8 ");
	}
	else if(EnvType == "Compute Signature")
	{
		//00 22 41 B6 0A 84 03 80 01 00 89 03 13 23 10 
		this->PartCmd->Append(L"41 B6 ");
	}
	else if(EnvType == "Verify Signature")
	{
		this->PartCmd->Append(L"81 B6 ");
	}
	else if(EnvType == "External Auth")
	{
		this->PartCmd->Append(L"81 A4 ");
	}
	else if(EnvType == "Internal Auth")
	{
		this->PartCmd->Append(L"41 A4 ");
	}

	CDialogEx::OnOK();
}
