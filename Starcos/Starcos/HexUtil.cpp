
#include"stdafx.h"
#include"HexUtil.h"
#include"afxwin.h"

HexUtil::HexUtil()
{

}

HexUtil::~HexUtil()
{
}


// change char to Hex value
int HexUtil::CharValue( char c )
{
	CString chars = L"0123456789ABCDEF";
	for(int i=0;i<chars.GetLength() ;i++)
		if(chars.GetAt(i) == c )
			return i;

	return 0;
}

//change Cstring to String with hex values
int HexUtil::CStringToHex(unsigned char * c , CString str)
{
	int cnt = 0;

	str.Remove(' ');
	str.MakeUpper();
	
	for(int i=0; i< str.GetLength() ; i+=2)
	{
		c[cnt++] = CharValue(str.GetAt(0+i)) * 16 + CharValue(str.GetAt(1+i));
	}
	
	return str.GetLength()/2;
}

//Change Hex values to Hex
CString HexUtil::HexToText( unsigned char * Text , int Length )
{
	CString str;
	CString tmp;
	int val; 

	for ( int i=0; i < Length ; i++)
	{
		// jak jest wartoœæ od 0 - 15 to dodaje jeden znak
		val = Text[i];
			tmp.Format( _T("%x"), val);
			if( tmp.GetLength() == 1)
				str.Append(L"0"+tmp);
			else
				str.Append(tmp);

		str.AppendChar(' ');
	}

	return str;
}

// Podajemy liczbê int -> dostajemy stringa w Hex 
CString HexUtil::IntToHex(int Number)
{
	CString num;

	if(Number < 16 )
		num.Format( _T("0%x") , Number);
	else
		num.Format( _T("%x") , Number);
	
	num.MakeUpper();

	if(num.GetLength()%2 != 0)
		num.SetString(L"0" + num);
	
	return num;
}

int HexUtil::CStringatoi( CString str )
{
	int num = 0,i=0;

	while( str[i] != '\0')
	{
		num = num*10 + (str[i] - '0');
		i++;
	}

	return num;
}

CString HexUtil::MakeParity(CString Number , bool Front)
{
	CString tmp = Number;
	tmp.Remove(' ');
	
	if(tmp.GetLength()%2 != 0)
	{
		if(Front)
			Number.SetString( L"0" + Number);
		else
			Number.AppendChar('0');
	}

	return Number;
}

 int HexUtil::GetLength(CString Number)
 {
	 Number.Remove(' ');
	 return Number.GetLength()/2;
 }