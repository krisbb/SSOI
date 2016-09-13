#pragma once

class HexUtil
{
	HexUtil();
	~HexUtil();
public:
	static CString IntToHex(int Number);
	static CString HexToText( unsigned char * Text , int Length );
	static int CStringToHex(unsigned char * c , CString str);
	static int CharValue( char c );
	static int CStringatoi( CString str );
	static CString MakeParity(CString Number , bool Front);
	static int GetLength(CString Number);
};