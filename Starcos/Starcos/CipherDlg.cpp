// CipherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "CipherDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

// CipherDlg dialog

IMPLEMENT_DYNAMIC(CipherDlg, CDialogEx)

CipherDlg::CipherDlg(CString * Str, CWnd* pParent /*=NULL*/)
	: CDialogEx(CipherDlg::IDD, pParent)
{
	this->PartCmd = Str;
}

CipherDlg::~CipherDlg()
{
}

void CipherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Mode);
	DDX_Control(pDX, IDC_EDIT1, DataValue);
	DDX_Control(pDX, IDC_PADDING, Padding);
}


BEGIN_MESSAGE_MAP(CipherDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CipherDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CipherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->Mode.AddString(L"Cipher");
	this->Mode.AddString(L"Decipher");
	this->Mode.SetCurSel(0);

	this->Padding.InsertString( 0 , L"None");
	this->Padding.InsertString( 1 , L"PKCS#1");
	this->Padding.InsertString( 2 , L"DINSIG");
	this->Padding.SetCurSel(0);

	return TRUE;
}

// CipherDlg message handlers


void CipherDlg::OnBnClickedOk()
{
	CString Mode, Padding, Data, DataLength;
	
	this->Mode.GetWindowTextW(Mode);
	this->Padding.GetWindowTextW(Padding);
	this->DataValue.GetWindowTextW(Data);
	
	if(Padding == "PKCS#1")
		Padding.SetString(L"81"); 
	else if(Padding == "DINSIG" )
		Padding.SetString(L"82"); 
	else
		Padding.SetString(L"00"); 


	if(Mode == "Cipher")
	{
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 1); //add 1 bcouse padding
		this->PartCmd->SetString( L"00 2A 86 80 ");
		this->PartCmd->Append(DataLength + L" "+ Padding + L" " + Data + L" 00");
	}
	else if (Mode == "Decipher")
	{
		/*00 2A 80 86 81 00 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 
                     11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 
                     11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 
                     11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 
                     11 11 11 11 11 11 00*/
		
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data) + 1 ); //add 1 bcouse padding
		this->PartCmd->SetString( L"00 2A 80 86 ");
		this->PartCmd->Append(DataLength + L" "+ Padding + L" " + Data + L" 00");
	}

	CDialogEx::OnOK();
}
