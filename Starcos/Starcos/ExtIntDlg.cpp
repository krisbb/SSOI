// ExtIntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "ExtIntDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

// ExtIntDlg dialog

IMPLEMENT_DYNAMIC(ExtIntDlg, CDialogEx)

ExtIntDlg::ExtIntDlg(CString * Str,CWnd* pParent /*=NULL*/)
	: CDialogEx(ExtIntDlg::IDD, pParent)
{
	this->PartCmd = Str;
}

ExtIntDlg::~ExtIntDlg()
{
}

void ExtIntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXTINTCOMBO, ExtIntChoice);
	DDX_Control(pDX, IDC_CHALLENGE, Challenge);
	DDX_Control(pDX, IDC_KEYNUM, KeyNum);
}


BEGIN_MESSAGE_MAP(ExtIntDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ExtIntDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL ExtIntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->ExtIntChoice.InsertString( 0 , L"Get Challenge");
	this->ExtIntChoice.InsertString( 1 , L"Internal Authenticate");
	this->ExtIntChoice.InsertString( 2 , L"External Authenticate");

	this->CheckRadioButton(IDC_RGLOB,IDC_RLOC, IDC_RLOC);

	this->KeyNum.SetWindowTextW(L"1");
	this->ExtIntChoice.SetCurSel(0);
	return TRUE;
}
// ExtIntDlg message handlers


void ExtIntDlg::OnBnClickedOk()
{
	CString Challenge , ExtIntChoice, KeyNum;
	CString ChallengeLength;

	this->ExtIntChoice.GetWindowTextW(ExtIntChoice);
	this->Challenge.GetWindowTextW(Challenge);
	this->KeyNum.GetWindowTextW(KeyNum);
	Challenge.MakeUpper();

	if( ExtIntChoice == "Get Challenge")
	{
		this->PartCmd->SetString(L"00 84 00 00 08");
	}
	else if(ExtIntChoice == "Internal Authenticate")
	{
		//key is global or local + key number 1-31
		this->PartCmd->SetString(L"00 88 00 ");
		int temp;

		if(this->IsDlgButtonChecked(IDC_RLOC))
			temp = 8*16;
		else
			temp = 0; //global has 000XXXXX where X - keynumber
			
		temp += HexUtil::CStringatoi(KeyNum);
		this->PartCmd->Append( HexUtil::IntToHex(temp) + L" ");
		
		ChallengeLength = HexUtil::IntToHex(HexUtil::GetLength(Challenge));
		this->PartCmd->Append( ChallengeLength + L" " + Challenge + L" 00");
		
	}
	else if(ExtIntChoice == "External Authenticate")
	{
		this->PartCmd->SetString(L"00 82 00 ");
		//key is global or local + key number 1-31
		
		int temp;
		if(this->IsDlgButtonChecked(IDC_RLOC))
			temp = 8*16;
		else
			temp = 0;
			
		temp += HexUtil::CStringatoi(KeyNum);
		this->PartCmd->Append( HexUtil::IntToHex(temp) + L" ");

		ChallengeLength = HexUtil::IntToHex(HexUtil::GetLength(Challenge));
		this->PartCmd->Append( ChallengeLength + L" " + Challenge);
	}

	CDialogEx::OnOK();
}
