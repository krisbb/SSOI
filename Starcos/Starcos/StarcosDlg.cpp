
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
	//Command.SetString( _T(" 00 A4 00 00"));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStarcosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1 , Command);
	//DDX_Text(pDX, IDC_EDIT2 , Response);
	DDX_Control(pDX, IDC_TREE1 , DlgDirTree);
	DDX_Control(pDX, IDC_EDIT1, CommandCtrl);
	DDX_Control(pDX, IDC_COMBO1, TermList);
	DDX_Control(pDX, IDC_RESP, ResponseCtrl);
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
	//ON_COMMAND(ID_FILE, &CStarcosDlg::SwitchToFileDlg)
	ON_COMMAND(ID_FILE_SELECT, &CStarcosDlg::OnFileSelect)
	ON_COMMAND(ID_FILE_READ, &CStarcosDlg::OnFileRead)
	ON_COMMAND(ID_FILE_UPDATE32774, &CStarcosDlg::OnFileUpdate)
	ON_COMMAND(ID_PIN, &CStarcosDlg::OnPIN)
	//ON_COMMAND(ID_CIPHER, &CStarcosDlg::OnCipher)
	ON_COMMAND(ID_CIPHER_ENC, &CStarcosDlg::OnCipherEnc)
	ON_COMMAND(ID_CIPHER_SETENV, &CStarcosDlg::OnCipherSetenv)
	ON_COMMAND(ID_KEY, &CStarcosDlg::OnSig)
	ON_BN_CLICKED(IDC_BRUTEF, &CStarcosDlg::OnBnClickedBrutef)
	ON_COMMAND(ID_AUTH, &CStarcosDlg::OnAuth)
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

	// na janusza tabcontrol
	/*DlgTabCtrl.InsertItem( 0 , _T("File"));
	DlgTabCtrl.InsertItem( 1 , _T("Auth"));
	DlgTabCtrl.InsertItem( 2 , _T("Cipher"));
	DlgTabCtrl.InsertItem( 3 , _T("Key"));*/

	//janusz treeview
	TVINSERTSTRUCT tvinsertstr;
	tvinsertstr.hParent = NULL;
	tvinsertstr.hInsertAfter = NULL;
	tvinsertstr.item.mask = TVIF_TEXT;
	tvinsertstr.item.pszText = _T("MF(3F00)");
	
	HTREEITEM MF = DlgDirTree.InsertItem(&tvinsertstr);
	HTREEITEM DF = DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("DF(3F02)") , 0 , 0 , 0 , 0, 0 , MF , NULL );
	DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("EF1(3F03)") , 0 , 0 , 0 , 0, 0 , MF , NULL );
	DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("EF2(3F04)") , 0 , 0 , 0 , 0, 0 , MF , NULL );
	DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("EF3(3F05)") , 0 , 0 , 0 , 0, 0 , MF , NULL );
	DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("EF1(4001)") , 0 , 0 , 0 , 0, 0 , DF , NULL );
	DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("EF2(4002)") , 0 , 0 , 0 , 0, 0 , DF , NULL );
	DlgDirTree.InsertItem(TVIF_TEXT ,
		_T("EF3(4003)") , 0 , 0 , 0 , 0, 0 , DF , NULL );

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
	
	//STM_InitializeLibrary(TRUE);
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

	//STM_DeinitializeLibrary();
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
	unsigned char Resp[400]; // test value 400 was 256 no idea why 
	unsigned char cmd [400]; //{ 0x00 , 0xA4 , 0x00 , 0x0C , 0x02 , 0x3F , 0x02 };
	
	unsigned HowManyToSend = HexUtil::CStringToHex(cmd, this->Command);
	unsigned HowManyReceived ;

	if(STM_SendCard(this->hCard, HowManyToSend, cmd , 400, &HowManyReceived , Resp , 0 , 9000 ,0 ) != STM_OK)
	{
		ShowError(this->hCard);
	}
	else
	{
		CString str = HexUtil::HexToText( Resp , HowManyReceived );
		
		///*for( int i=0; i<HowManyReceived;i++)
		//{
		//	if(Resp[i] != 0 )
		//		tmp.Format( _T("%x ") , Resp[i]);
		//	else
		//		tmp.Format( _T("0%x ") , Resp[i]);
		//
		//	str.Append(tmp);
		//}*/

		str.MakeUpper();
		this->ResponseCtrl.SetWindowTextW(str);
		this->MessageBox( str , _T("File window") , 0);
	}	//this->Response.Format(_T("%s") , Resp );
}

void CStarcosDlg::BruteForce()
{
	unsigned char Resp[400]; // test value 400 was 256 no idea why 
	unsigned char cmd [400]; //{ 0x00 , 0xA4 , 0x00 , 0x0C , 0x02 , 0x3F , 0x02 };
	unsigned char firstPartAPDU[] = { 0x00 , 0x2A , 0x00 , 0xA8 };//{ 0x00 , 0x2A , 0x86 , 0x80 };
	int firstPartAPDULength = 4;
	//unsigned char constValue = 0x82; //PADDING // I tried 81 ,00, 82

	for(int i=0;i<firstPartAPDULength;i++)
	{
		cmd[i] = firstPartAPDU[i];
	}

	//openfile
	//openFileHandle("bruteForce.txt");

	//beginLoop
	for(int i=1;i<255;i++)
	{
		//build dynamically APDU
		//----BEGIN BUILD------

		//cmd[firstPartAPDULength-2] = i + 2;
		cmd[firstPartAPDULength] = i; // LC of APDU
		//cmd[firstPartAPDULength+1] = constValue; //for example 81 for padding

		//GENERATE DATA
		
		for(int j=0;j<i;j++)
		{
			cmd[firstPartAPDULength+1+j] = 0x11; // const value to encrypt
		}

		//add at the end 00 Le to receive all message
		//cmd[firstPartAPDULength+i+1] = 0x00; //added 2 bcouse LC + LE 
		//-----END BUILD -----

		unsigned HowManyToSend = firstPartAPDULength+i+1;
		unsigned HowManyReceived;
		//send correctly APDU
		if(STM_SendCard(this->hCard, HowManyToSend, cmd , 400, &HowManyReceived , Resp , 0 , 9000 ,0 ) != STM_OK)
		{
			ShowError(this->hCard);
			//return;
		}
		else
		{

			//check if response is 9000 write APDU to file
			//or if HowManyReceived is gt 2 
			if(HowManyReceived > 2 )
			{
				//convert cmd to String and write to file
				CString str = HexUtil::HexToText( cmd , HowManyToSend );
				
				printf("%s" , str);
				//AppendToFile(str + "\n");
			}
			else if( HowManyReceived == 2 && Resp[0] != 106)
			{
				CString str = HexUtil::HexToText( cmd , HowManyToSend );
				printf("%s" , str);
				
			}

			//if length of data is FF break the loop
		}	

		//for(int k=0;k<HowManyToSend;k++)
		//	printf("%x" ,cmd[k]);

	//sleep for 1 second ?
	Sleep(1000);

	//endOfLoop 
	}

	//closeFileHandle();
	//closeFileHandle
}



//void CStarcosDlg::BruteForce() to cipher .....
//{
//	unsigned char Resp[400]; // test value 400 was 256 no idea why 
//	unsigned char cmd [400]; //{ 0x00 , 0xA4 , 0x00 , 0x0C , 0x02 , 0x3F , 0x02 };
//	unsigned char firstPartAPDU[] = { 0x00 , 0x2A , 0x86 , 0x80 };
//	int firstPartAPDULength = 6;
//	unsigned char constValue = 0x82; //PADDING // I tried 81 ,00, 82
//
//	for(int i=0;i<firstPartAPDULength;i++)
//	{
//		cmd[i] = firstPartAPDU[i];
//	}
//
//	//openfile
//	//openFileHandle("bruteForce.txt");
//
//	//beginLoop
//	for(int i=2;i<255;i++)
//	{
//		//build dynamically APDU
//		//----BEGIN BUILD------
//		cmd[firstPartAPDULength] = i; // LC of APDU
//		cmd[firstPartAPDULength+1] = constValue; //for example 81 for padding
//
//		//GENERATE DATA
//		
//		for(int j=0;j<i-1;j++)
//		{
//			cmd[firstPartAPDULength+2+j] = 0x11; // const value to encrypt
//		}
//
//		//add at the end 00 Le to receive all message
//		cmd[firstPartAPDULength+i+1] = 0x00; //added 2 bcouse LC + LE 
//		//-----END BUILD -----
//
//		unsigned HowManyToSend = firstPartAPDULength+i+2;
//		unsigned HowManyReceived;
//		//send correctly APDU
//		if(STM_SendCard(this->hCard, HowManyToSend, cmd , 400, &HowManyReceived , Resp , 0 , 9000 ,0 ) != STM_OK)
//		{
//			ShowError(this->hCard);
//			//return;
//		}
//		else
//		{
//
//			//check if response is 9000 write APDU to file
//			//or if HowManyReceived is gt 2 
//			if(HowManyReceived > 2 )
//			{
//				//convert cmd to String and write to file
//				CString str,tmp;
//				for( int i=0; i<HowManyToSend;i++)
//				{
//					if(cmd[i] != 0 )
//						tmp.Format( _T("%x ") , cmd[i]);
//					else
//						tmp.Format( _T("0%x ") , cmd[i]);
//		
//					str.Append(tmp);
//				}
//
//				printf("%s" , str);
//				//AppendToFile(str + "\n");
//			}
//
//			//if length of data is FF break the loop
//		}	
//
//		//for(int k=0;k<HowManyToSend;k++)
//		//	printf("%x" ,cmd[k]);
//
//	//sleep for 1 second ?
//	Sleep(1000);
//
//	//endOfLoop 
//	}
//
//	//closeFileHandle();
//	//closeFileHandle
//}

void CStarcosDlg::getTermList()
{
	unsigned Buflen = 255, OutputSize;
	wchar_t * TermList = new wchar_t[Buflen];

	STM_GetTermList( STM_LIST_ALL , Buflen , &OutputSize , TermList);

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

	if(Receive != 0 )
	this->MessageBox( StringATR  , _T("File window") , 0);
	
	delete [] ATR;
}

/*void CStarcosDlg::SwitchToFileDlg()
{
	
	//??
}
*/

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

//this doesn't work
/*void CStarcosDlg::OnCipher()
{
	CString Output;
	CipherDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}*/



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


void CStarcosDlg::OnBnClickedBrutef()
{
	this->BruteForce();
	// TODO: Add your control notification handler code here
}


void CStarcosDlg::OnAuth()
{
	CString Output;
	ExtIntDlg dlg(&Output);;
	INT_PTR Response = dlg.DoModal();

	if(Response == IDOK)
		this->CommandCtrl.SetWindowTextW(Output);
}
