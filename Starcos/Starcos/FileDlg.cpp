// FileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "FileDlg.h"
#include "afxdialogex.h"
//#include "afxocc.h"

// FileDlg dialog

IMPLEMENT_DYNAMIC(FileDlg, CDialogEx)

FileDlg::FileDlg( CString * Str , CWnd* pParent /*=NULL*/)
	: CDialogEx(FileDlg::IDD, pParent)
{
	
	EnableAutomation();
	this->PartCmd = Str;
}

FileDlg::~FileDlg()
{
}

void FileDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void FileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, FileID);
}


BEGIN_MESSAGE_MAP(FileDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &FileDlg::OnBnClickedOk)
	//ON_EN_CHANGE(IDC_EDIT1, &FileDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(FileDlg, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IFileDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {C8A507A9-E5E2-444D-9204-59073BA4D6D6}
static const IID IID_IFileDlg =
{ 0xC8A507A9, 0xE5E2, 0x444D, { 0x92, 0x4, 0x59, 0x7, 0x3B, 0xA4, 0xD6, 0xD6 } };

BEGIN_INTERFACE_MAP(FileDlg, CDialogEx)
	INTERFACE_PART(FileDlg, IID_IFileDlg, Dispatch)
END_INTERFACE_MAP()


// FileDlg message handlers
BOOL FileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->CheckRadioButton(IDC_FID_EF , IDC_MF, IDC_FID_EF);

	return TRUE;
}

//All functions TestFID are unnecessary
//because response from card tells users what is wrong  
void FileDlg::OnBnClickedOk()
{
	this->PartCmd->SetString( L"00 A4" );
	CString FID;

	if(IsDlgButtonChecked( IDC_FID_EF )){
		this->PartCmd->Append(L" 02 0C 02 ");
		this->FileID.GetWindowTextW(FID);
		FID.MakeUpper();
		//if(!TestFID(FID,4))
			// return;

		this->PartCmd->Append(FID);
	}
	else if(IsDlgButtonChecked( IDC_FID_DF )){
		this->PartCmd->Append(L" 01 0C 02 ");
		this->FileID.GetWindowTextW(FID);
		FID.MakeUpper();
		//if(!TestFID(FID,4))
			// return;

		this->PartCmd->Append(FID);
	}
	else if(IsDlgButtonChecked( IDC_AID_DF )){
		this->PartCmd->Append(L" 04 0C 16 ");
		this->FileID.GetWindowTextW(FID);
		FID.MakeUpper();
		//if(!TestFID(FID,16))
			//return;

		this->PartCmd->Append(FID);
	}
	else if(IsDlgButtonChecked( IDC_PARENT_DF )){
		this->PartCmd->Append(L" 03 0C");
	}
	else if(IsDlgButtonChecked( IDC_MF )){
		this->PartCmd->Append(L" 00 0C 02 3F 00");
	}

	CDialogEx::OnOK();
}


bool FileDlg::TestFID( CString FID , int Maxcount)
{
	FID.Remove(' ');
		if( FID.GetLength() != Maxcount ){
			this->MessageBox(L"Nieodpowiednia dlugosc", _T("File Window"), 0);
			return false;
		}

	return true;
}

/* In next Version
void FileDlg::OnEnChangeEdit1()
{
	
	CString AllowedChars = L"0123456789ABCDEF ";
	CString FileID,tmp;
	
	this->FileID.GetWindowTextW(FileID);
	tmp = FileID;
	
	
	int LastAddedChar = this->FileID.GetWindowTextLengthW() - 1;
	for(int i=0;i<AllowedChars.GetLength();i++)
		if( FileID[LastAddedChar] != AllowedChars[i])
		{
			FileID.Remove("");
		}
	
}
*/