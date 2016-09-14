
// StarcosDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starcos.h"
#include "StarcosDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <string>

#include "FileDlg.h"
#include "ReadDlg.h"
#include "UpdateDlg.h"
#include "AuthDlg.h"
#include "CipherDlg.h"
#include "EnvDlg.h"
#include "SigDlg.h"
#include "ExtIntDlg.h"
#include "HexUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStarcosDlg dialog


CStarcosDlg::CStarcosDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStarcosDlg::IDD, pParent) 
	, Command(_T(""))
	, Response(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStarcosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1 , Command);
	DDX_Control(pDX, IDC_EDIT1, CommandCtrl);
	DDX_Control(pDX, IDC_COMBO1, TermList);
	DDX_Control(pDX, IDC_RESP, ResponseCtrl);
}

void CStarcosDlg::OnOK()
{
	this->SendAPDU();
}

BEGIN_MESSAGE_MAP(CStarcosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1 , ButtonConnect )
	ON_BN_CLICKED(IDC_BUTTON2 , ButtonDisconnect )
	ON_BN_CLICKED(IDC_BUTTON3 , Request)
	ON_BN_CLICKED(IDC_BUTTON4, &CStarcosDlg::OpenExTerm)
	ON_BN_CLICKED(IDC_BUTTON5, &CStarcosDlg::SendAPDU)
	ON_BN_CLICKED(IDC_BUTTON6, &CStarcosDlg::getTermList)
	ON_BN_CLICKED(IDC_BUTTON7, &CStarcosDlg::GetATR)
	ON_COMMAND(ID_FILE_SELECT, &CStarcosDlg::OnFileSelect)
	ON_COMMAND(ID_FILE_READ, &CStarcosDlg::OnFileRead)
	ON_COMMAND(ID_FILE_UPDATE32774, &CStarcosDlg::OnFileUpdate)
	ON_COMMAND(ID_PIN, &CStarcosDlg::OnPIN)
	ON_COMMAND(ID_CIPHER_ENC, &CStarcosDlg::OnCipherEnc)
	ON_COMMAND(ID_CIPHER_SETENV, &CStarcosDlg::OnCipherSetenv)
	ON_COMMAND(ID_KEY, &CStarcosDlg::OnSig)
	ON_COMMAND(ID_AUTH, &CStarcosDlg::OnAuth)
	ON_BN_CLICKED(IDC_EJECT, &CStarcosDlg::OnBnClickedEject)
	ON_BN_CLICKED(IDC_TERMTYPE, &CStarcosDlg::OnBnClickedTermtype)
	ON_BN_CLICKED(IDC_TERMVERSION, &CStarcosDlg::OnBnClickedTermversion)
	ON_BN_CLICKED(IDC_LIBVERSION, &CStarcosDlg::OnBnClickedLibversion)
	ON_BN_CLICKED(IDC_CARDTYPE, &CStarcosDlg::OnBnClickedCardtype)
END_MESSAGE_MAP()


// CStarcosDlg message handlers

BOOL CStarcosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	STM_InitializeLibrary(TRUE);
	
	//Get Terminal List
	this->getTermList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStarcosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStarcosDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStarcosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CStarcosDlg::ShowError(stmHandle hCard )
{

  int   iDepth, iLevel, 
        iErrCode, iRet;
  wchar_t  sText[256];
  CString str1;

  //printf("Error-Stack:\n");
  /* Determine error-stack depth */
  if ((iRet=STM_GetErrorDepth(hCard, &iDepth)) != STM_OK)
  {
	 
	str1.Format(_T("STM_GetErrorDepth() faild with return code %d\n"), iRet);
	this->MessageBox( str1 , _T("File window") , 0);
    return;
  }
  
  for (iLevel=0; iLevel < iDepth; iLevel++)
  {
    /* Retrieve error code */
    if (STM_GetError(hCard, iLevel, &iErrCode, 0, NULL, NULL) == STM_OK)
	{
      str1.Format(_T("(%d) Code = %x  "), iLevel, iErrCode );
	  this->MessageBox( str1 , _T("File window") , 0);
	}
    /* Retrieve error message string */
    if (STM_GetMsg(iErrCode, STM_LANG_E, 256, sText ) == STM_OK)
		 this->MessageBox( sText , _T("File window") , 0);

  }

}

void CStarcosDlg::ButtonConnect()
{
	int iErr; 
	
	// STM_OPEN_PCSC
	iErr= STM_Open( &this->hCard, STM_OPEN_PCSC, STM_SHARED );
	
	CString str1;
	str1.Format(_T("Open return %x"), iErr);
		
	//355 - bad terminal
	
	this->MessageBox( str1 , _T("File window") , 0);
}

void CStarcosDlg::Request()
{
	if(STM_Request( this->hCard, STM_ICC1 , STM_EXCL ) != STM_OK )
	{
		ShowError(this->hCard);
	}
	else
		this->MessageBox( _T("Request") , _T("File window") , 0);
}

void CStarcosDlg::ButtonDisconnect()
{
	int iErr;
	iErr = STM_Close(this->hCard);
	
	CString str1;
	str1.Format(_T("Close return %x"), iErr);

	STM_DeinitializeLibrary();
	this->MessageBox( str1 , _T("File window") , 0);
}

void CStarcosDlg::OpenExTerm()
{
	int iErr;
	CString TermName;

	// Close less T0 shared works
	//"OMNIKEY CardMan 5x21-CL 0"
	int index = this->TermList.GetCurSel();
	if(index == -1){
		this->MessageBox( L"Choose Terminal from the List" , _T("File window") , 0);
		return;
	}

	int Length = this->TermList.GetLBTextLen(index);
	this->TermList.GetLBText(index , TermName.GetBuffer(Length)); 
	iErr = STM_OpenEx( &this->hCard, TermName , STM_SHARED );
	
		CString str1;
		str1.Format(_T("OpenEx return %x"), iErr);

		this->MessageBox( str1 , _T("File window") , 0);
}

void CStarcosDlg::SendAPDU()
{
	this->CommandCtrl.GetWindowTextW(this->Command);
	unsigned char Resp[400]; 
	unsigned char cmd [400];
	
	unsigned HowManyToSend = HexUtil::CStringToHex(cmd, this->Command);
	unsigned HowManyReceived ;

	if(STM_SendCard(this->hCard, HowManyToSend, cmd , 400, &HowManyReceived , Resp , 0 , 9000 ,0 ) != STM_OK)
	{
		ShowError(this->hCard);
	}
	else
	{
		CString str = HexUtil::HexToText( Resp , HowManyReceived );

		str.MakeUpper();
		this->ResponseCtrl.SetWindowTextW(str);
		//this->MessageBox( str , _T("File window") , 0);
	}	
}

void CStarcosDlg::getTermList()
{
	unsigned Buflen = 255, OutputSize;
	wchar_t * TermList = new wchar_t[Buflen];

	if( STM_GetTermList( STM_LIST_ALL , Buflen , &OutputSize , TermList) != STM_OK )
	{
		this->MessageBox( L"Error in GetTermList" , _T("File Window") , 0);
		return;
	}

	if(OutputSize < 2 ){
		delete [] TermList;
		return;
	}

	std::vector <LPCTSTR> readers;
	readers.push_back( TermList );

	for( int i=0 ; i< OutputSize; i++ )
	{
		if( TermList[i] == 0)
		{
			if(( i < OutputSize+1) && ( TermList[i+1] == 0 )) break;
			readers.push_back((LPCTSTR)&TermList[i+1]);
		}
	}

	this->TermList.ResetContent();

	for( int i = 0; i < readers.size() ; i++ )
		this->TermList.AddString(readers.at(i));

		//this->MessageBox( readers.at(i) , _T("File window") , 0);

	this->TermList.SetCurSel(0);

	delete [] TermList;
}

void CStarcosDlg::GetATR()
{
	//Czyta dobrze ale jakby litery by³y wielkie
	unsigned LenATR = 33, Receive = 0;
	unsigned char * ATR = new unsigned char[LenATR];
	CString StringATR;

	STM_GetATR( this->hCard , LenATR, &Receive , ATR );
	StringATR = HexUtil::HexToText( ATR , Receive );
	StringATR.MakeUpper();

	if(Receive != 0 )
		this->ResponseCtrl.SetWindowTextW(StringATR);
	//this->MessageBox( StringATR  , _T("File window") , 0);
	
	delete [] ATR;
}

void CStarcosDlg::OnFileSelect()
{
	CString Output;
	FileDlg dlg(&Output);
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}

void CStarcosDlg::OnFileRead()
{
	CString Output;
	CReadDlg dlg(&Output);
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}

void CStarcosDlg::OnFileUpdate()
{
	CString Output;
	UpdateDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}

void CStarcosDlg::OnPIN()
{
	CString Output;
	AuthDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}

void CStarcosDlg::OnCipherEnc()
{
	CString Output;
	CipherDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}


void CStarcosDlg::OnCipherSetenv()
{
	CString Output;
	EnvDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}


void CStarcosDlg::OnSig()
{
	CString Output;
	SigDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}


void CStarcosDlg::OnAuth()
{
	CString Output;
	ExtIntDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}

void CStarcosDlg::OnBnClickedEject()
{
	if(STM_Eject(this->hCard) != STM_OK)
	{
		ShowError(this->hCard);
	}
	else
	{
		CString str;
		str.Format(_T("Eject Successfully"));

		this->MessageBox( str , _T("File window") , 0);
	}
}

void CStarcosDlg::OnBnClickedTermtype()
{
	unsigned uipType;

	if( STM_GetTermType( this->hCard, &uipType) != STM_OK)
	{
		ShowError(this->hCard);
	}
	else
	{
		CString str;
		
		switch(uipType)
		{
			case STM_CT :
				str.Format(_T("CT type not defined"));
				break;
			case STM_CT_MKT :
				str.Format(_T("MultiFunctional card Terminal (MKT)"));
				break;
			case STM_CT_MKT_D :
				str.Format(_T("MKT with display"));
				break;
			case STM_CT_MKT_K :
				str.Format(_T("MKT with keypad"));
				break;
			case STM_CT_MKT_DK :
				str.Format(_T("MKT with display and keypad"));
				break;
			default:
				str.Format(_T("TermType doesn't recognise"));
				break;
		}

		this->MessageBox( str , _T("File window") , 0);
	}
}

void CStarcosDlg::OnBnClickedTermversion()
{
	TCHAR szVerTxt[96];
	
	if(STM_TermVersion( this->hCard, szVerTxt) != STM_OK)
	{
			ShowError(this->hCard);
	}
	else
	{
		this->MessageBox( szVerTxt ,  _T("File window") , 0);
	}
}

void CStarcosDlg::OnBnClickedLibversion()
{
	TCHAR szVerTxt[151];
	
	if( STM_LibVersion(szVerTxt)  != STM_OK)
	{
			this->MessageBox( L"Doesn't recognise Library Version" ,  _T("File window") , 0);
	}
	else
	{
		this->MessageBox( szVerTxt ,  _T("File window") , 0);
	}
}

void CStarcosDlg::OnBnClickedCardtype()
{
	unsigned uipType;

	if( STM_GetCardType( this->hCard, &uipType) != STM_OK )
	{
		ShowError(this->hCard);
	}
	else
	{
		CString str;
		switch(uipType)
		{
			case STM_CARD :
				str.Format(_T("smart card type not defined"));
				break;
			case STM_CARD_ISO :
				str.Format(_T("smart card according to ISO/IEC 7816-4"));
				break;
			case STM_CARD_S11 :
				str.Format(_T("STARCOS S 1.1 card"));
				break;
			case STM_CARD_S12 :
				str.Format(_T("STARCOS S 1.2 card"));
				break;
			case STM_CARD_S21 :
				str.Format(_T("STARCOS S 2.1 card"));
				break;
			case STM_CARD_S25 :
				str.Format(_T("STARCOS S 2.5 card"));
				break;
			case STM_CARD_S3 :
				str.Format(_T("STARCOS 3.x card(default)"));
				break;
			case STM_CARD_SPK21 :
				str.Format(_T("STARCOS SPK 2.1 card"));
				break;
			case STM_CARD_SPK22 :
				str.Format(_T("STARCOS SPK 2.2 card"));
				break;
			case STM_CARD_SPK23 :
				str.Format(_T("STARCOS SPK 2.3 card"));
				break;
			case STM_CARD_SPK24 :
				str.Format(_T("STARCOS SPK 2.4 card"));
				break;
			case STM_CARD_SPK25 :
				str.Format(_T("STARCOS SPK 2.5 card"));
				break;
			case STM_CARD_AIR10 :
				str.Format(_T("STARCOS Air 1.0 card"));
				break;
			case STM_CARD_SV10 :
				str.Format(_T("STARCOS StarVisa 1.0"));
				break;
			case STM_CARD_GSM2 :
				str.Format(_T("GSM Phase 2 card"));
				break;
			case STM_CARD_OP201 :
				str.Format(_T("Open Platform 2.0.1' compatible card"));
				break;
			default:
				str.Format(_T( "CardType doesn't recognise" ));
				break;
		}

		this->MessageBox( str , _T("File window") , 0);
	}
}
