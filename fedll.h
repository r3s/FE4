//----------------------------------------------------------------------------
// Mixing BC++ built 32-bit DLL's with non-BC applications.
// Copyright (c) 1996 by Borland International, All Rights Reserved
//----------------------------------------------------------------------------
#ifndef FEDLL_H
#define FEDLL_H

#if defined( __cplusplus)
#define CFUNC extern "C"
#endif

//
// Functions are exported from the DLL and imported to the calling application.
// Visual C++ 4.1 does not support the __import keyword.
//
#if defined(FEDLL_BLD)
# define FEDLL_EXP __export
#else
# if defined(__BORLANDC__)
#  define FEDLL_EXP __import
# else
#  define FEDLL_EXP
# endif
#endif

//
// Visual C++ 4.1 does not support the C++ bool type nor its predefined values.
//

CFUNC int     FEDLL_EXP      __stdcall  Encode(char file1[260],char file2[260],char password[260],long size,long u,long v,HWND hwnd);
CFUNC int     FEDLL_EXP      __stdcall  Decode(char file1[260],char file2[260],char password[260],long size,long u,long v,HWND hwnd);
CFUNC int     FEDLL_EXP      __stdcall  Shred(char filename[260],long size,HWND hwnd);
CFUNC int     FEDLL_EXP      __stdcall  GetUV(char password[260],long &u,long &v);
CFUNC int     FEDLL_EXP      __stdcall  Getname(char name[260]);
CFUNC int     FEDLL_EXP      __stdcall   RenameFile(char oldname[260],char newname[260]); 
CFUNC int     FEDLL_EXP      __stdcall   DirList(char dir[260],char file1[260],int op,HWND list);

 
#endif  // FEDLL_H
