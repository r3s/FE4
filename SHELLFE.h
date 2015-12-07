#ifndef SHELLFE_H
#define SHELLFE_H

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


CFUNC int FEDLL_EXP __stdcall Browse1(HWND list);
CFUNC char* FEDLL_EXP __stdcall Browse2(HWND hwnd,TCHAR *folderpath);

#endif

