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
}


BEGIN_MESSAGE_MAP(CipherDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CipherDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CipherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->Mode.AddString(L"Encipher");
	this->Mode.AddString(L"Decipher");
	this->Mode.SetCurSel(0);

	return TRUE;
}

// CipherDlg message handlers


void CipherDlg::OnBnClickedOk()
{
	CString Mode, Data, DataLength;
	
	this->Mode.GetWindowTextW(Mode);
	this->DataValue.GetWindowTextW(Data);
	

	if(Mode == "Encipher")
	{
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		this->PartCmd->SetString( L"00 2A 86 80 ");
		this->PartCmd->Append(DataLength + L" " + Data + L" 00");
	}
	else if (Mode == "Decipher")
	{
		DataLength = HexUtil::IntToHex(HexUtil::GetLength(Data));
		this->PartCmd->SetString( L"00 2A 80 86 ");
		this->PartCmd->Append(DataLength + L" " + Data + L" 00");
	}

	CDialogEx::OnOK();
}
