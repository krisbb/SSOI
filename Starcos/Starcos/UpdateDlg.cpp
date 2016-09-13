// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "UpdateDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

// UpdateDlg dialog

IMPLEMENT_DYNAMIC(UpdateDlg, CDialogEx)

UpdateDlg::UpdateDlg(CString * Str , CWnd* pParent /*=NULL*/)
	: CDialogEx(UpdateDlg::IDD, pParent)
{
	this->PartCmd = Str;
}

UpdateDlg::~UpdateDlg()
{
}

void UpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_TYPE, FileOpt);
	DDX_Control(pDX, IDC_EDIT1, DataValue);
	DDX_Control(pDX, IDC_EDIT3, RecordNum);
	DDX_Control(pDX, IDC_EDIT2, Offset);
}


BEGIN_MESSAGE_MAP(UpdateDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UpdateDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL UpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->FileOpt.InsertString(0, L"Transparent" );
	this->FileOpt.InsertString(1, L"Record File" );
	this->FileOpt.InsertString(2, L"Append Record" );
	this->FileOpt.SetCurSel(0);

	this->RecordNum.SetWindowTextW(L"1");
	this->Offset.SetWindowTextW(L"00 00");

	return TRUE;
}

// UpdateDlg message handlers

void UpdateDlg::OnBnClickedOk()
{
	CString Filetype , RecordNum , Offset , Data;
	CString DataLength;
	bool Padding = false;

	this->FileOpt.GetWindowTextW(Filetype);
	this->Offset.GetWindowTextW(Offset);
	this->RecordNum.GetWindowTextW(RecordNum);
	if(RecordNum.GetLength()%2 != 0)
		RecordNum.SetString(L"0" + RecordNum);

	this->DataValue.GetWindowTextW(Data);
	Data.Remove(' ');
	if(Data.GetLength()%2 != 0){
		Data.AppendChar('0');
		Padding = true;
	}

	//if(Data.GetLength()/2 > 256)
	//	this->MessageBox(L"Za du¿o wartoœci do wys³ania",_T("File Window" ),0);
	
	DataLength = HexUtil::IntToHex(Data.GetLength()/2);
	
	this->DataValue.GetWindowTextW(Data);
	if(Padding)
		Data.AppendChar('0');

	if( Filetype == "Transparent")
	{
		this->PartCmd->SetString(L"00 D6 ");
		this->PartCmd->Append(Offset + L" ");
		this->PartCmd->Append(DataLength + L" ");
		this->PartCmd->Append(Data);
	}
	else if( Filetype == "Append Record")
	{
		this->PartCmd->SetString(L"00 E2 00 00");
		this->PartCmd->Append(DataLength + L" ");
		this->PartCmd->Append(Data);
	}
	else
	{ //Record File
		this->PartCmd->SetString(L"00 DC ");
		this->PartCmd->Append(RecordNum + L" 04 ");
		this->PartCmd->Append(DataLength + L" ");
		this->PartCmd->Append(Data);
	}

	CDialogEx::OnOK();
}
