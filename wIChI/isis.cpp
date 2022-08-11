#include "stdafx.h"
#include "isis.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////////////////////////////// ISIS Clipboard ///////////////////////
static UINT ctFormat;
static UINT skFormat;

BOOL __stdcall InitMDLClipBoard()
{
    ctFormat = RegisterClipboardFormat("MDLCT");
	skFormat = RegisterClipboardFormat("MDLSK");
	return (ctFormat != 0) || (skFormat != 0);
}


static BOOL IsChemSiteClipboardAvailable()
{

	BOOL bRet = FALSE;
	HWND hwnd;


	if( IsClipboardFormatAvailable(CF_TEXT) && (hwnd = GetClipboardOwner()) )
	{
		TCHAR OwnerName[_MAX_PATH];
		int ret = GetClassName( hwnd,           // handle to window
								OwnerName,  // class name
								_MAX_PATH        // size of class name buffer
								);
		bRet = (ret < _MAX_PATH) && (lstrcmp( OwnerName, _T("ChemSite")) == 0 );
	}
	return bRet;
}


BOOL __stdcall IsMDLClipboardAvailable()
{
    return	( ctFormat && IsClipboardFormatAvailable(ctFormat) ) ||
			( skFormat && IsClipboardFormatAvailable(skFormat) && IsClipboardFormatAvailable(CF_TEXT) ) ||
			IsChemSiteClipboardAvailable();
}


static int SaveMDLCT( LPCTSTR Filename, const char* p, int nSize )
{							 
    int i, len, nLine, the_rest, nAtoms, nBonds;
    const char *q; 
	char szVal[4];
    static char szEnd[]      = "M  END";
    static char szRXN_Flag[] = "$RXN";
    static char szRGF_Flag[] = "$MDL";
	FILE *f;
	f = _tfopen( Filename, _T("wt") );
	if( f == NULL )
		return 1;

#define FLAG_LEN   4	
    for ( i = nLine = 0; i < nSize && i+(len=(int)(unsigned char)p[i]) < nSize; i += len+1, nLine ++ ) 
	{
		// check if it is a MOLfile
		if ( nLine == 0 && len >= FLAG_LEN ) 
		{
			for ( q = &p[i+1], the_rest=len; NULL != (q = (const char *) memchr( q, '$', the_rest ) ) && FLAG_LEN <= (the_rest = len-(q-&p[i+1]) ); q++ ) 
			{
                if ( 0 == memcmp( q, szRXN_Flag, FLAG_LEN ) || 0 == memcmp( q, szRGF_Flag, FLAG_LEN ) ) 
				{
					fclose(f);
                    return 2; // not a MOLfile
                }
            }
        }       
        if ( len )
            fwrite( &p[i+1], 1, len, f );
        fwrite( "\n", 1, 1, f );
        // extract number of atoms and bonds
        if ( 3 == nLine && len > 3 ) 
		{
            strncpy( szVal, &p[i+1], 3 );
            szVal[3] = '\0';
            nAtoms = (int)strtol(szVal, NULL, 10);
            strncpy( szVal, &p[i+1]+3, 3 );
            szVal[3] = '\0';
            nBonds = (int)strtol(&p[i+1]+3, NULL, 10);
        }
        // check if it is the last line
        if ( nLine >= 4 + nAtoms + nBonds &&  len >= sizeof( szEnd ) - 1 && 0 == memcmp(&p[i+1], szEnd, len ) ) 
			break;
	}
	fclose(f);
	return  (nLine <= 4) ? 3 : 0;  // MOLfile should have at least 5 lines
}


int  __stdcall GetMDLClipboardData( HWND hwnd, LPCTSTR Filename )
{
    DWORD dwSize;
	LPVOID p;
	int ret = -1;
    HANDLE hCTBuffer = 0;
	UINT nFormat = 0;

    if(IsClipboardFormatAvailable(ctFormat)) 
		nFormat = ctFormat;
	else if( (IsClipboardFormatAvailable(skFormat) && IsClipboardFormatAvailable(CF_TEXT)) || IsChemSiteClipboardAvailable() )
		nFormat = CF_TEXT;
	if( nFormat == 0 )
		return ret;
	
	if (OpenClipboard(hwnd)) 
	{
            hCTBuffer = GetClipboardData(nFormat);
            CloseClipboard();
	}
	if( (GlobalFlags(hCTBuffer) & GMEM_DISCARDED) != GMEM_DISCARDED )
	{
		dwSize = GlobalSize(hCTBuffer);
		if( dwSize )
		{
			p = GlobalLock(hCTBuffer);
			if ( p ) 
			{
				if( nFormat == ctFormat )
					ret = SaveMDLCT( Filename, (const char *)p, dwSize );
				else
				{
					FILE * f = _tfopen( Filename, _T("wb") );
					if( f != NULL )
					{
						fputs( (char *)p, f );
						fclose( f ) ;
						ret = 0;
					}
				}
			}
			GlobalUnlock(hCTBuffer);
		}
	}
	return ret;
}

static HANDLE ReadMDLCT( LPCTSTR Filename )
{
	DWORD dwSize;
	char line[256];
	char * p, * end;
	char * buf = NULL;
	int len;
	FILE *f = NULL;
	HANDLE hCTBuffer = 0;

	f = _tfopen( Filename, _T("rt") );
	if( f == NULL )
		goto _cleanup;

	dwSize = _filelength(_fileno(f));
	if( dwSize == 0 )
		goto _cleanup;


	buf = (char *)calloc( dwSize + 1, 1 );
	if( buf == NULL )
		goto _cleanup;

	p = buf;

	while( fgets(line,sizeof(line),f) )
	{ 
		if( (end = strchr(line,'\n')) == NULL )
			goto _cleanup;
		*end = 0;
		len = strlen(line);
		*p++ = (char)len;
		if( len )
		{
			strcpy(p,line);
			p+=len;
		}
	}

	dwSize = p - buf +1;
	hCTBuffer = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, dwSize ); 
	memmove( GlobalLock( hCTBuffer ), buf, dwSize );
	GlobalUnlock( hCTBuffer );
_cleanup:
	if( f )
		fclose(f);
	if( buf )
		free(buf);

	return hCTBuffer;
}

static HANDLE ReadCFTXT( LPCTSTR Filename )
{
	DWORD dwSize;
	FILE *f = NULL;
	HANDLE hCFTBuffer = 0;
	char * buf = NULL;

	f = _tfopen( Filename, _T("rb") );
	if( f == NULL )
		goto _cleanup;

	dwSize = _filelength(_fileno(f));
	if( dwSize == 0 )
		goto _cleanup;


	buf = (char *)calloc( dwSize + 1, 1 );
	if( buf == NULL )
		goto _cleanup;

	fread(buf, dwSize, 1, f);
	dwSize++;
	hCFTBuffer = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, dwSize  ); 
	memmove( GlobalLock( hCFTBuffer ), buf, dwSize );
	GlobalUnlock( hCFTBuffer );

_cleanup:
	if( f )
		fclose(f);
	if( buf )
		free(buf);

	return hCFTBuffer;
}



int  __stdcall SetMDLCTClipboardData( HWND hwnd, LPCTSTR Filename )
{
	HANDLE hCTBuffer = NULL, hTextBuffer = NULL;
	int ret = -1;

	if( ctFormat )
		hCTBuffer = ReadMDLCT(Filename);

	hTextBuffer = ReadCFTXT(Filename);

	if( hCTBuffer || hTextBuffer )
	{
		if (OpenClipboard(hwnd)) 
		{
			EmptyClipboard();
			SetClipboardData(ctFormat, hCTBuffer);
			SetClipboardData(CF_TEXT, hTextBuffer);
			CloseClipboard();
			ret = 0;
		}
		else
		{
			if( hCTBuffer )
				GlobalFree(hCTBuffer);
			if( hTextBuffer )
				GlobalFree(hTextBuffer);
		}
	}
	return ret;
}


