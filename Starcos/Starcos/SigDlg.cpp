// SigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "SigDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

// SigDlg dialog

IMPLEMENT_DYNAMIC(SigDlg, CDialogEx)

SigDlg::SigDlg(CString * Str, CWnd* pParent /*=NULL*/)
	: CDialogEx(SigDlg::IDD, pParent)
{
	this->PartCmd = Str;
}

SigDlg::~SigDlg()
{
}

void SigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHOICE, Choice);
	DDX_Control(pDX, IDC_EDIT1, DataValue);
}


BEGIN_MESSAGE_MAP(SigDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SigDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL SigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->Choice.InsertString( 0 , L"Compute Signature");
	this->Choice.InsertString( 1 , L"Compute Hash");
	this->Choice.InsertString( 2 , L"Verify Signature");
	this->Choice.SetCurSel(0);

	return TRUE;
}
// SigDlg message handlers


void SigDlg::OnBnClickedOk()
{
	CString Choice , Data , DataLength, HashLength;
	
	this->Choice.GetWindowTextW(Choice);
	this->DataValue.GetWindowTextW(Data);

	if( Choice == "Compute Signature")
	{
		//00 2A 9E 9A 00
		this->PartCmd->SetString( L"00 2A 9E 9A 00" );
	}
	else if(Choice == "Compute Hash")
	{
		// 00 2A 90 A0 16 90 14 6F 6D B0 48 26 F0 41 1F 68 54 3A B1 37 D5 61 11 3E C9 A4 6B 
		this->PartCmd->SetString( L"00 2A 90 A0 ");

		HashLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 2);
		this->PartCmd->Append( DataLength + L" 90 " + HashLength + L" " + Data);
	}
	//else if(Choice == "Verify Signature")
	
	CDialogEx::OnOK();
}
