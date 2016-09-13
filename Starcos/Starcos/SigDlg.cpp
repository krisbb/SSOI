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

	this->Choice.InsertString( 0 , L"Compute Signature From Buffer");
	this->Choice.InsertString( 1,  L"Compute Signature (Add Hash below)");
	this->Choice.InsertString( 2 , L"Pass Precomputed Hash");
	this->Choice.InsertString( 3 , L"Initialize Hash Calculation");
	//this->Choice.InsertString( 4 , L"Pass Computed Intermediate Value");
	this->Choice.InsertString( 4 , L"Pass Next Part Of Message");
	this->Choice.InsertString( 5 , L"Pass Last Part Of Message");
	

	//In next Version
	//this->Choice.InsertString( 2 , L"Verify Signature");
	this->Choice.SetCurSel(0);

	return TRUE;
}
// SigDlg message handlers


void SigDlg::OnBnClickedOk()
{
	CString Choice , Data , DataLength, HashLength;
	
	this->Choice.GetWindowTextW(Choice);
	this->DataValue.GetWindowTextW(Data);

	if( Choice == "Compute Signature From Buffer")
	{
		this->PartCmd->SetString( L"00 2A 9E 9A 00" );
	}
	else if(Choice == "Pass Precomputed Hash" )
	{
		// 00 2A 90 A0 16 90 14 6F 6D B0 48 26 F0 41 1F 68 54 3A B1 37 D5 61 11 3E C9 A4 6B 
		this->PartCmd->SetString( L"00 2A 90 A0 ");

		HashLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 2);
		this->PartCmd->Append( DataLength + L" 90 " + HashLength + L" " + Data);
	}
	else if(Choice == "Compute Signature (Add Hash below)")
	{ 
		//its good ? 
		this->PartCmd->SetString( L"00 2A 9E 9A " );

		HashLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 2);
		this->PartCmd->Append( HashLength + L" " + Data + L" 00");
	}
	else if(Choice == "Initialize Hash Calculation")
	{
		this->PartCmd->SetString( L"10 2A 90 A0 02 90 00");
	}
	else if(Choice == "Pass Next Part Of Message")
	{
		this->PartCmd->SetString( L"10 2A 90 A0 ");

		HashLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 2);
		this->PartCmd->Append( DataLength + L" 80 " + Data);
	}
	else if(Choice == "Pass Last Part Of Message" )
	{
		this->PartCmd->SetString( L"00 2A 90 A0 ");

		HashLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 2);
		this->PartCmd->Append( DataLength + L" 80 "+ HashLength + L" " + Data);
	}

	//In next Version
	//else if(Choice == "Verify Signature")
	
	CDialogEx::OnOK();
}
