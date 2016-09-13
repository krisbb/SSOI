// ReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "ReadDlg.h"
#include "afxdialogex.h"
#include "HexUtil.h"

// CReadDlg dialog

IMPLEMENT_DYNAMIC(CReadDlg, CDialogEx)

CReadDlg::CReadDlg(CString * Str , CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadDlg::IDD, pParent)
{
	EnableAutomation();
	this->PartCmd = Str;
}

BOOL CReadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	this->CheckRadioButton(IDC_RHEX , IDC_RDEC , IDC_RDEC);
	this->init();
	
	return TRUE;
}

CReadDlg::~CReadDlg()
{
}

void CReadDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void CReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_TYPE, FileType);
	DDX_Control(pDX, IDC_LENGTHBOX, FileLength);
	DDX_Control(pDX, IDC_READ_NRECORD, RecordNum);
	DDX_Control(pDX, IDC_EDIT1, Offset);
}

void CReadDlg::init()
{
	this->FileType.InsertString(0,L"Transparent");
	this->FileType.InsertString(1,L"Linear fixed");
	this->FileType.InsertString(2,L"Linear variable");
	this->FileType.InsertString(3,L"Cyclic");
	
	this->FileType.SetCurSel(0);
	
	this->Offset.SetWindowTextW(L"00 00");
	this->FileLength.SetWindowTextW(L"08");
	this->RecordNum.SetWindowTextW(L"1");
}

BEGIN_MESSAGE_MAP(CReadDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CReadDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CReadDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IReadDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {5CA351BD-8798-483D-874E-B5EC3B9696CC}
static const IID IID_IReadDlg =
{ 0x5CA351BD, 0x8798, 0x483D, { 0x87, 0x4E, 0xB5, 0xEC, 0x3B, 0x96, 0x96, 0xCC } };

BEGIN_INTERFACE_MAP(CReadDlg, CDialogEx)
	INTERFACE_PART(CReadDlg, IID_IReadDlg, Dispatch)
END_INTERFACE_MAP()

// CReadDlg message handlers

void CReadDlg::OnBnClickedOk()
{
	CString ChoosenFileType, RecordNum, FileLength, Offset;
	CString Number;
	//int num;
	
	int index = this->FileType.GetCurSel();
	int Length = this->FileType.GetLBTextLen(index);
	this->FileType.GetLBText(index , ChoosenFileType.GetBuffer(Length)); 
	this->FileLength.GetWindowTextW(FileLength);

	/* Maybe in the next version
	   requirement was dinamically switching beetwen hex and dec -> aborted for that reason
	if(this->IsDlgButtonChecked(IDC_RDEC))
		{
			num = HexUtil::CStringatoi(FileLength);
			CString tmp = HexUtil::IntToHex(num);
			FileLength.SetString(tmp);
			//this->PartCmd->Append(tmp);
		}
		*/

	if( ChoosenFileType == "Transparent"){
		
		this->PartCmd->SetString(L"00 B0 ");
		this->Offset.GetWindowTextW(Offset);
		this->PartCmd->Append(Offset + L" ");
		this->PartCmd->Append(FileLength);
	}
	else
	{
		this->PartCmd->SetString(L"00 B2 ");
		
		if( ChoosenFileType == "Cyclic"){
			//czyta ca³y rekord
			this->RecordNum.GetWindowTextW(RecordNum);
		}
		else if(ChoosenFileType == "Linear variable"){
			this->RecordNum.GetWindowTextW(RecordNum);
		}
		else if(ChoosenFileType == "Linear fixed"){
			this->RecordNum.GetWindowTextW(RecordNum);
		}

		if(RecordNum.GetLength()%2 != 0)
			RecordNum.SetString(L"0" + RecordNum);

		this->PartCmd->Append(RecordNum + L" 04 ");
		this->PartCmd->Append(FileLength);
	}

	CDialogEx::OnOK();
}

