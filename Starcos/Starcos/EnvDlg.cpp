// EnvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "EnvDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

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
	DDX_Control(pDX, IDC_EDIT1, AlgID);
	DDX_Control(pDX, IDC_EDIT2, KeyNum);
	DDX_Control(pDX, IDC_EDIT3, KeyVersion);
}

BOOL EnvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->EnvType.InsertString( 0 , L"Encipherment");
	this->EnvType.InsertString( 1 , L"Decipherement");
	this->EnvType.InsertString( 2 , L"Generate key pair");
	this->EnvType.InsertString( 3 , L"Compute Signature");
	
	

	this->EnvType.SetCurSel(0);
	this->KeyNum.SetWindowTextW(L"01");
	this->KeyVersion.SetWindowTextW(L"00");

	this->CheckRadioButton(IDC_RPUBKEY, IDC_RPRVKEY , IDC_RPRVKEY);
	
	//In next Version
	//this->EnvType.InsertString( 0 , L"Verify Signature");
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
	CString EnvType , Data , KeyVersion , KeyNum , AlgID;
	
	this->PartCmd->Append( L"00 22 ");
	this->EnvType.GetWindowTextW(EnvType);
	this->KeyNum.GetWindowTextW(KeyNum);
	this->KeyVersion.GetWindowTextW(KeyVersion);
	this->AlgID.GetWindowTextW(AlgID);

	CString AlgIDLength = HexUtil::IntToHex(HexUtil::GetLength(AlgID));

	if(KeyNum.GetLength()%2 != 0)
		KeyNum.SetString(L"0" + KeyNum);

	if(KeyVersion.GetLength()%2 != 0)
		KeyVersion.SetString(L"0" + KeyVersion);

	if(EnvType == "Encipherment")
	{
		this->PartCmd->Append(L"81 B8 ");

		if(this->IsDlgButtonChecked(IDC_RPRVKEY))
			Data.SetString(L"84");
		else
			Data.SetString(L"83");

		Data.Append(L" 03 80 " + KeyNum + L" " + KeyVersion);
		Data.Append(L" 89 " + AlgIDLength + L" " + AlgID);
		CString DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		this->PartCmd->Append( DataLength + L" " + Data);

	}
	else if(EnvType == "Decipherement")
	{
		this->PartCmd->Append(L"41 B8 ");

		if(this->IsDlgButtonChecked(IDC_RPRVKEY))
			Data.SetString(L"84");
		else
			Data.SetString(L"83");

		Data.Append(L" 03 80 " + KeyNum + L" " + KeyVersion);
		Data.Append(L" 89 " + AlgIDLength + L" " + AlgID);
		CString DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		this->PartCmd->Append( DataLength + L" " + Data);
	}
	else if(EnvType == "Generate key pair")
	{
		this->PartCmd->Append(L"41 B6 ");
		
		if(this->IsDlgButtonChecked(IDC_RPRVKEY))
			Data.SetString(L"84");
		else
			Data.SetString(L"83");

		Data.Append(L" 03 80 " + KeyNum + L" " + KeyVersion);
		Data.Append(L" 89 01 41" );
		CString DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		this->PartCmd->Append( DataLength + L" " + Data);

	}
	else if(EnvType == "Compute Signature")
	{
		//00 22 41 B6 0A 84 03 80 01 00 89 03 13 23 10 
		this->PartCmd->Append(L"41 B6 ");

		if(this->IsDlgButtonChecked(IDC_RPRVKEY))
			Data.SetString(L"84");
		else
			Data.SetString(L"83");

		Data.Append(L" 03 80 " + KeyNum + L" " + KeyVersion);
		Data.Append(L" 89 " + AlgIDLength + L" " + AlgID);
		CString DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		this->PartCmd->Append( DataLength + L" " + Data);
		
	}
	/*else if(EnvType == "Verify Signature")
	{
		this->PartCmd->Append(L"81 B6 ");
	}*/

	CDialogEx::OnOK();
}
