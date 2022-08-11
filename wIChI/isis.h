#ifndef __NISTCMN_ISIS_H__
#define __NISTCMN_ISIS_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



#ifdef __cplusplus
extern "C" {
#endif

BOOL __stdcall InitMDLClipBoard();
BOOL __stdcall IsMDLClipboardAvailable();
int  __stdcall GetMDLClipboardData( HWND hwnd, LPCTSTR Filename );
int  __stdcall SetMDLCTClipboardData( HWND hwnd, LPCTSTR Filename );


#ifdef __cplusplus
	}
#endif


#endif
