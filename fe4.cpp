#include<windows.h>
#include<commctrl.h>
#include<stdio.h>
#include<conio.h>
#include<dir.h>
#include<process.h>
#include<fstream.h>
#include<dos.h>
#include"fe4.h"
#include"fedll.h"
#include"shellfe.h"
DWORD (__stdcall*RegisterServiceProcess)(DWORD, DWORD);

void Hide(void)


{
	//typedef DWORD (__stdcall *pRegFunction)(DWORD, DWORD);
	HINSTANCE		hKernelLib;
	//	pRegFunction	RegisterServiceProcess;

	hKernelLib = LoadLibrary("advapi32.dll");
	if (hKernelLib)


	{
		RegisterServiceProcess = (DWORD(__stdcall*)(DWORD, DWORD))GetProcAddress(hKernelLib, "RegisterServiceProcess");
		if (RegisterServiceProcess)
			RegisterServiceProcess(GetCurrentProcessId(), 1);
		else
			MessageBox(0, "SORRY, fAiled", "", 0);
		::FreeLibrary(hKernelLib);
	}
	else
		MessageBox(0, "SORRY, loda", "", 0);					//change 1 to 0 for ctrl+alt+del to view app
}



const char dll1[] = "FE4.DLL";
const char dll2[] = "SHELLFE.DLL";
char  command[600];

int sign1 = -1;
int sign2 = -1;
//Functions from dll

int (__stdcall*encodeit)(char file1[260], char file2[260], char password[260], long size, long u, long v, HWND hwnd);
int (__stdcall*decodeit)(char file1[260], char file2[260], char password[260], long size, long u, long v, HWND hwnd);
int (__stdcall*shred)(char filename[MAXPATH], long size, HWND hwnd);
int (__stdcall*getUV)( char password[260], long &u, long &v);
int (__stdcall*renamefile)(char oldname[260], char newname[260]);
int (__stdcall*dirlist)(char dir[MAXPATH], char filename[260], int op, HWND list);
int (__stdcall*browse1)(HWND list);
char* (__stdcall*browse2)(HWND hwnd, TCHAR *folderpath);



char prevFile[MAXPATH];

char abtmsg[] = "                   FE 4 \r\n\r\n\
By RAHUL.ES\r\n\r\n\
For details about FE series, \r\n\
Contact : es_rahul@yahoo.co.in\r\n\r\n";



//HWND for buttons
HWND h_prog, h_lock, h_list, h_open, h_enc, h_dec, h_shred, h_temp, h_abt, h_hlp, h_mov, h_ren, h_search, h_brd1, h_brf, h_brd2, h_rem, h_exit;


//BITMAPS for buttons

HBITMAP lockf, openf, enc, decc, shredf, temp, abt, hlp, mov, ren, search, brd, brf, rem, exitdlg;

//Background color
HBRUSH g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));


//ICON
HICON feico, feico2;




//to check if give object is a file or folder
int isdir(char *folder)
{
	if (chdir(folder) != -1)
		return 1;
	else
		return 0;
}



//getencname

void getname(char encname[260], char filename[260], int op)
{
	switch (op)
	{
	case 1:
	{	char drive[MAXDRIVE], dir[MAXDIR], file[MAXPATH], ext[MAXEXT];
		fnsplit(filename, drive, dir, file, ext);
		strcat(file, ext);
		strcpy(ext, ".fe+");
		fnmerge(encname, drive, dir, file, ext);
	} break;
	case 2:
	{
		strcpy(encname, filename);
		int pos = 0;
		int i, j;
		for ( i = 0; i < strlen(encname); i++)
		{
			if (encname[i] == '.')
			{
				pos = i + 4;
				break;
			}
		}

		for (i = pos, j = 0; j < 10; i++, j++)
			encname[i] = ' ';
	}
	break;

	}

}






BOOL CALLBACK MainDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG: {
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)feico);
		SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)feico2);
		h_prog = GetDlgItem(hwnd, IDC_PROG);
		h_lock = GetDlgItem(hwnd, IDC_LOCK);
		SendMessage(h_lock, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)lockf);
		h_list = GetDlgItem(hwnd, IDC_LIST);
		h_enc = GetDlgItem(hwnd, IDC_ENCODE);
		SendMessage(h_enc, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)enc);
		h_dec = GetDlgItem(hwnd, IDC_DECODE);
		SendMessage(h_dec, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)decc);
		h_brf = GetDlgItem(hwnd, IDC_BROWSE1);
		SendMessage(h_brf, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)brf);
		h_brd1 = GetDlgItem(hwnd, IDC_BROWSE2);
		SendMessage(h_brd1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)brd);
		h_brd2 = GetDlgItem(hwnd, IDC_BROWSE3);
		SendMessage(h_brd2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)brd);
		h_abt = GetDlgItem(hwnd, IDC_ABOUT);
		SendMessage(h_abt, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)abt);
		h_exit = GetDlgItem(hwnd, IDC_EXIT);
		SendMessage(h_exit, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)exitdlg);
		h_hlp = GetDlgItem(hwnd, IDC_HELP);
		SendMessage(h_hlp, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hlp);
		h_rem = GetDlgItem(hwnd, IDC_REMOVE);
		SendMessage(h_rem, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)rem);
		h_shred = GetDlgItem(hwnd, IDC_SHRED);
		SendMessage(h_shred, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)shredf);
		h_ren = GetDlgItem(hwnd, IDC_RENAME);
		SendMessage(h_ren, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ren);
		h_search = GetDlgItem(hwnd, IDC_SEARCH);
		SendMessage(h_search, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)search);
		h_mov = GetDlgItem(hwnd, IDC_MOVE);
		SendMessage(h_mov, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)mov);
		h_temp = GetDlgItem(hwnd, IDC_TEMP);
		SendMessage(h_temp, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)temp);
		h_open = GetDlgItem(hwnd, IDC_OPEN);
		SendMessage(h_open, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)openf);
		if (isdir(command) == 1)
			dirlist(command, "sad", 1, h_list);
		else if (strcmp(command, "") != 0)
			SendMessage(h_list, LB_ADDSTRING, 0, (LPARAM)command);
		int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
		SetDlgItemInt(hwnd, IDC_TOTAL, filecount, FALSE);

	}
	break;

	case WM_DROPFILES  : {
		char szNextFile[MAXPATH];
		UINT num;
		HDROP hd;
		hd = (HDROP)wparam;
		num = DragQueryFile ( hd, -1, NULL, 0 );
		for ( UINT uFile = 0; uFile < num; uFile++ )
		{
			if ( DragQueryFile ( hd, uFile, szNextFile, MAX_PATH ) > 0 )
			{
				if (strcmp(prevFile, szNextFile) == 0)
					break;
				if (chdir(szNextFile) != -1)
					dirlist(szNextFile, "asdas", 1, h_list);
				else
					SendMessage(h_list, LB_ADDSTRING, 0, (LPARAM)szNextFile);
			}
		}
		int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
		SetDlgItemInt(hwnd, IDC_TOTAL, filecount, FALSE);
	}  break;
	case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wparam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LONG)g_hbrBackground;
	}


	case WM_COMMAND      : switch (LOWORD(wparam))
		{
		case IDC_ENCODE  : if (MessageBox(hwnd, "Are you sure you want to encode the file(s)?", "FE REPORT", 1) != IDCANCEL)

			{

				int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_PASS));
				int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
				if (len > 0 && filecount > 0)
				{
					if (filecount > 30)
						if (MessageBox(hwnd, "Encoding more than 30 files may result in loss of information in files\r\nYou are reccommended to do this step bt step,maximum 30 files at a time\r\nHowever, you can continue with this process.Do you want to continue?", "FE CAUTION", 1 | MB_ICONEXCLAMATION) == IDCANCEL)
							break;
					long u = 0, v = 0;
					int process = 0, err_no = 0;

					char *password = (char*)GlobalAlloc(GPTR, sizeof(char) * 256);
					GetDlgItemText(hwnd, IDC_PASS, password, len + 1);

					getUV(password, u, v);
					for (int i = 0; i < filecount; i++)
					{
						DWORD size = 0;
						char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
						char *encname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
						SendMessage(h_list, LB_GETTEXT, (WPARAM)i, (LPARAM)filename);
						HANDLE hFile;
						hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
						size = GetFileSize(hFile, (LPDWORD) NULL);
						CloseHandle((HANDLE) hFile);
						getname(encname, filename, 1);
						process = encodeit(filename, encname, password, size, u, v, h_prog);
						if (process == -1)
							err_no += 1;
						else
						{
							if (sign2 == 1)
							{	char *dname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
								GetDlgItemText(hwnd, IDC_DIRNAME, dname, MAXPATH);
								int len = strlen(dname);
								if (dname[len] == '\\')
									dname[len] = '\0';
								char drive[MAXDRIVE], dir[MAXDIR], file[MAXPATH], ext[MAXEXT];
								fnsplit(encname, drive, dir, file, ext);
								strcat(dname, "\\");
								strcat(dname, file);
								strcat(dname, ext);
								MoveFile(encname, dname);
								GlobalFree((HWND)dname);

							}
						}
						GlobalFree((HWND)filename);
						GlobalFree((HWND)encname);

					}

					MessageBox(hwnd, "Encoding completed", "FE REPORT", 0 | MB_ICONINFORMATION);
					for (int j = 0; j < filecount; j++)
						for (int m = 0; m < filecount; m++)
							SendMessage(h_list, LB_DELETESTRING, (WPARAM)m, 0);
					SetDlgItemText(hwnd, IDC_PASS, "");
					SetDlgItemInt(hwnd, IDC_TOTAL, filecount - err_no, FALSE);
					SetDlgItemInt(hwnd, IDC_ERRORS, err_no, FALSE);
					GlobalFree((HWND)password);


				}
				else
					MessageBox(hwnd, "PARAMETER(s) MISSING :Either there are no files or no password is entered", "FE REPORT", MB_ICONEXCLAMATION);
			}
			break;
		case IDC_DECODE  :
			if (MessageBox(hwnd, "Are you sure you want to decode the file(s)?", "FE REPORT", 1) != IDCANCEL)
			{

				int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_PASS));
				int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
				if (len > 0 && filecount > 0)
				{
					if (filecount > 30)
						if (MessageBox(hwnd, "Decoding more than 30 files may result in loss of information in files\r\nYou are reccommended to do this step bt step,maximum 30 files at a time\r\nHowever, you can continue with this process.Do you want to continue?", "FE CAUTION", 1 | MB_ICONEXCLAMATION) == IDCANCEL)
							break;

					long u = 0, v = 0;
					int process = 0, err_no = 0;

					char *password = (char*)GlobalAlloc(GPTR, sizeof(char) * 256);
					GetDlgItemText(hwnd, IDC_PASS, password, len + 1);

					getUV(password, u, v);
					for (int i = 0; i < filecount; i++)
					{
						DWORD size = 0;
						char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
						char *encname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
						SendMessage(h_list, LB_GETTEXT, (WPARAM)i, (LPARAM)filename);
						HANDLE hFile;
						hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
						size = GetFileSize(hFile, (LPDWORD) NULL);
						CloseHandle((HANDLE) hFile);
						getname(encname, filename, 2);
						process = decodeit(filename, encname, password, size, u, v, h_prog);
						if (process == -1)
							err_no += 1;
						else
						{
							char *dname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);

							if (sign2 == 1)
							{	GetDlgItemText(hwnd, IDC_DIRNAME, dname, MAXPATH);
								int len = strlen(dname);
								if (dname[len] == '\\')
									dname[len] = '\0';
								char drive[MAXDRIVE], dir[MAXDIR], file[MAXPATH], ext[MAXEXT];
								fnsplit(encname, drive, dir, file, ext);
								strcat(dname, "\\");
								strcat(dname, file);
								strcat(dname, ext);
								MoveFile(encname, dname);

							}
							if (sign1 == 1)
							{

								char *filename2 = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
								GetDlgItemText(hwnd, IDC_FILENAME, filename2, MAXPATH);
								if (sign2 != 1)
									renamefile(encname, filename2);
								if (sign2 == 1)
									renamefile(dname, filename2);
							}
							GlobalFree((HWND)dname);

						}
						GlobalFree((HWND)filename);
						GlobalFree((HWND)encname);

					}
					MessageBox(hwnd, "Decoding completed", "FE REPORT", 0 | MB_ICONINFORMATION);
					for (int j = 0; j < filecount; j++)
						for (int m = 0; m < filecount; m++)
							SendMessage(h_list, LB_DELETESTRING, (WPARAM)m, 0);
					SetDlgItemText(hwnd, IDC_PASS, "");
					SetDlgItemInt(hwnd, IDC_TOTAL, filecount - err_no, FALSE);
					SetDlgItemInt(hwnd, IDC_ERRORS, err_no, FALSE);
					GlobalFree((HWND)password);


				}
				else
					MessageBox(hwnd, "PARAMETER(s) MISSING :Either there are no files or no password is entered", "FE REPORT", MB_ICONEXCLAMATION);
			}
			break;
		case IDC_SHRED   : if (MessageBox(hwnd, "Are you sure you want to shred the file(s)?", "FE REPORT", 1) != IDCANCEL)

			{
				int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
				if (filecount > 0)
				{
					int process = 0, err_no = 0;
					for (int i = 0; i < filecount; i++)
					{
						DWORD size = 0;
						char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
						SendMessage(h_list, LB_GETTEXT, (WPARAM)i, (LPARAM)filename);
						HANDLE hFile;
						hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
						size = GetFileSize(hFile, (LPDWORD) NULL);
						CloseHandle((HANDLE) hFile);
						process = shred(filename, size, h_prog);
						if (process == -1)
							err_no += 1;
						GlobalFree((HWND)filename);
					}
					MessageBox(hwnd, "Shredding Completed", "FE REPORT", 0 | MB_ICONINFORMATION);
					for (int j = 0; j < filecount; j++)
						for (int m = 0; m < filecount; m++)
							SendMessage(h_list, LB_DELETESTRING, (WPARAM)m, 0);
					SetDlgItemInt(hwnd, IDC_TOTAL, filecount - err_no, FALSE);
					SetDlgItemInt(hwnd, IDC_ERRORS, err_no, FALSE);

				}
				else
					MessageBox(hwnd, "NO FILES TO SHRED", "FE REPORT", MB_ICONEXCLAMATION);

			}
			break;
		case IDC_RENAME  : {

			int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_FILENAME));
			int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
			if (len > 0 && filecount > 0)
			{
				char *rname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
				GetDlgItemText(hwnd, IDC_FILENAME, rname, len + 1);

				for (int i = 0; i < filecount; i++)
				{
					char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
					SendMessage(h_list, LB_GETTEXT, (WPARAM)i, (LPARAM)filename);
					renamefile(filename, rname);
					GlobalFree((HWND)filename);
				}
				GlobalFree((HWND)rname);
			}
			else
				MessageBox(hwnd, "Parameter(s) missing.Eithe fil or new name was not specified", "FE REPORT", 0 | MB_ICONINFORMATION);
			MessageBox(hwnd, "Renaming Completed", "FE REPROT", 0 | MB_ICONINFORMATION);
			for (int j = 0; j < filecount; j++)
				for (int i = 0; i < filecount; i++)
					SendMessage(h_list, LB_DELETESTRING, (WPARAM)i, 0);

		} break;

		case IDC_TEMP    :    if (MessageBox(hwnd, "Are you sure you want to clear temporary files?", "FE REPORT", 1) == IDCANCEL)
				break ;
			{
				char temp[MAXPATH];
				GetTempPath(MAXPATH, temp);
				dirlist(temp, "sad", 1, h_list);
				int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
				if (filecount > 0)
				{
					int process = 0, err_no = 0;
					for (int i = 0; i < filecount; i++)
					{
						DWORD size = 0;
						char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
						SendMessage(h_list, LB_GETTEXT, (WPARAM)i, (LPARAM)filename);
						HANDLE hFile;
						hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
						size = GetFileSize(hFile, (LPDWORD) NULL);
						CloseHandle((HANDLE) hFile);
						process = shred(filename, size, h_prog);
						if (process == -1)
							err_no += 1;
						GlobalFree((HWND)filename);
					}

					MessageBox(hwnd, "Temporary Files Cleared", "FE REPORT", 0 | MB_ICONINFORMATION);
					for (int j = 0; j < filecount; j++)
						for (int m = 0; m < filecount; m++)
							SendMessage(h_list, LB_DELETESTRING, (WPARAM)m, 0);
					SetDlgItemInt(hwnd, IDC_TOTAL, filecount - err_no, FALSE);
					SetDlgItemInt(hwnd, IDC_ERRORS, err_no, FALSE);

				}


			}
			break;
		case IDC_MOVE    : {

			int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_DIRNAME));
			int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
			if (len > 0 && filecount > 0)
			{

				for (int i = 0; i < filecount; i++)
				{
					char *dname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
					GetDlgItemText(hwnd, IDC_FILENAME, dname, len + 1);
					int len = strlen(dname);
					if (dname[len] == '\\')
						dname[len] = '\0';
					char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
					SendMessage(h_list, LB_GETTEXT, (WPARAM)i, (LPARAM)(LPCTSTR)filename);
					char drive[MAXDRIVE], dir[MAXDIR], file[MAXPATH], ext[MAXEXT];
					fnsplit(filename, drive, dir, file, ext);
					strcat(dname, "\\");
					strcat(dname, file);
					strcat(dname, ext);
					MoveFile(filename, dname);
					GlobalFree((HWND)filename);
					GlobalFree((HWND)dname);
				}

			}
			else
				MessageBox(hwnd, "Parameter(s) missing.Eithe file or folder was not specified", "FE REPORT", 0 | MB_ICONINFORMATION);

			MessageBox(hwnd, "The process was executed. Result:unknown", "FE REPROT", 0 | MB_ICONINFORMATION);
			for (int j = 0; j < filecount; j++)
				for (int i = 0; i < filecount; i++)
					SendMessage(h_list, LB_DELETESTRING, (WPARAM)i, 0);


		}
		break;
		case IDC_SEARCH  : {
			int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
			for (int j = 0; j < filecount; j++)
				for (int i = 0; i < filecount; i++)
					SendMessage(h_list, LB_DELETESTRING, (WPARAM)i, 0);

			int len1 = GetWindowTextLength(GetDlgItem(hwnd, IDC_FILENAME));
			int len2 = GetWindowTextLength(GetDlgItem(hwnd, IDC_DIRNAME));
			if (len1 > 0 && len2 > 0)
			{
				char *filename = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
				char *dirname = (char*)GlobalAlloc(GPTR, sizeof(char) * MAXPATH);
				GetDlgItemText(hwnd, IDC_FILENAME, filename, MAXPATH);
				GetDlgItemText(hwnd, IDC_DIRNAME, dirname, MAXPATH);
				if (dirlist(dirname, filename, 2, h_list) == -1)
					MessageBox(hwnd, "Sorry , searching failed", "FE REPORT", 0);
				GlobalFree((HWND)filename);
				GlobalFree((HWND)dirname);
			}
			else
				MessageBox(hwnd, "Parameter(s) missing.Please provide search keyword and folder to be searched", "FE REPORT", 0 | MB_ICONINFORMATION);
			MessageBox(hwnd, "Search Complete", "FE REPROT", 0 | MB_ICONINFORMATION);
		}
		break;
		case IDC_BROWSE1 : {
			browse1(h_list);
			int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
			SetDlgItemInt(hwnd, IDC_TOTAL, filecount, FALSE);
		} break;
		case IDC_BROWSE2 :
		{
			char folder[260];
			if (browse2(hwnd, folder) == NULL)
				break;
			else if (isdir(folder) == 1)
			{
				dirlist(folder, "adfa", 1, h_list);
			}
			int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
			SetDlgItemInt(hwnd, IDC_TOTAL, filecount, FALSE);

		}
		break;
		case IDC_BROWSE3 : {
			TCHAR  f[260];
			char *ff = NULL;
			ff = browse2(hwnd, f);
			if (isdir(ff) == 1)
				SetDlgItemText(hwnd, IDC_DIRNAME, ff);

		}
		break;
		case IDC_REMOVE   : {
			int selcount = SendMessage(h_list, LB_GETSELCOUNT, 0, 0);
			int *buf = (int*) GlobalAlloc(GPTR, sizeof(int) * selcount );
			SendMessage(h_list, LB_GETSELITEMS, (WPARAM)selcount, (LPARAM)buf);
			for (int c = -1; c <= selcount; c++)
			{

				SendMessage(h_list, LB_DELETESTRING, (WPARAM)buf[c], 0);

			}
			GlobalFree(buf);
		}
		break;
		case IDC_REMOVEALL: {
			int filecount = SendMessage(h_list, LB_GETCOUNT, 0, 0);
			for (int c = 0; c < 10; c++)
				for (int i = 0; i < filecount; i++)
					SendMessage(h_list, LB_DELETESTRING, (WPARAM)i, 0);
			SetDlgItemInt(hwnd, IDC_TOTAL, 0, FALSE);
		}
		break;
		case IDC_OPEN    : {
			int selcount = SendMessage(h_list, LB_GETSELCOUNT, 0, 0);
			if (selcount == 1)
			{	int *buf = (int*) GlobalAlloc(GPTR, sizeof(int) * selcount );
				SendMessage(h_list, LB_GETSELITEMS, (WPARAM)selcount, (LPARAM)buf);
				char file[MAXPATH];
				SendMessage(h_list, LB_GETTEXT, (WPARAM)buf[0], (LPARAM)(LPCTSTR)file);
				char cmd1[600];
				char dir[MAXPATH];
				char drive[MAXDRIVE], dir2[MAXDIR], file2[MAXPATH], ext[MAXEXT];
				fnsplit(file, drive, dir2, file2, ext);
				strcpy(dir, drive);
				strcpy(dir, dir2);
				strcpy(cmd1, "explorer " );
				strcat(cmd1, dir);
				WinExec(cmd1, SW_SHOWNORMAL);
				GlobalFree(buf);
			}
			if (selcount <= 0)
				MessageBox(hwnd, "Please select a file from the list to open the folder which contains it.", "FE REPORT", 0 | MB_ICONINFORMATION);
			if (selcount > 1)
				MessageBox(hwnd, "Only one file can be opened at a time.Please select only one folder.", "FE REPORT", 0 | MB_ICONINFORMATION);
		}
		break;
		case IDC_TORENAME: sign1 = sign1 * -1;
			break;
		case IDC_TOMOVE  : sign2 = sign2 * -1;
			break;
		case IDC_HELP    : {
			char windir[MAXPATH], feinfo[MAXPATH];
			ifstream fin;
			GetWindowsDirectory(windir, MAXPATH);
			strcat(windir, "\\fe_info.inf");
			fin.open(windir, ios::in | ios::binary);
			if (!fin)
			{
				MessageBox(hwnd, "Sorry , the help file was not found.\r\nPlease check the file fe4.html is in the same folder as fe4.exe\r\nThe run RegSetup.exe", "FE REPORT", 0 | MB_ICONINFORMATION);
				break;
			}
			fin.getline(feinfo, MAXPATH);
			fin.close();
			strcat(feinfo, "\\fe.html");
			char cmdline[MAXPATH];
			strcpy(cmdline, "explorer ");
			strcat(cmdline, feinfo);
			WinExec(cmdline, SW_SHOW);

		}
		break;
		case IDC_ABOUT   : MessageBox(hwnd, abtmsg, "FE 4 ABOUT", 0 | MB_ICONINFORMATION);
			break;
		case IDC_EXIT    : EndDialog(hwnd, 0);
			break;
		}
		break;


	case WM_CLOSE: EndDialog(hwnd, 0);
		break;
	default:      return FALSE;
	}
	return TRUE;
}







int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR cmdLine, int )
{
	Hide() ;
	strcpy(command, cmdLine);
	int i;
	for (i = 0; i < strlen(command); i++)
		command[i] = command[i + 1];
	command[i - 2] = ' ';
	InitCommonControls();

//ALL THE BITMAPS
	enc       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_ENCODE));
	decc      = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_DECODE));
	shredf    = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SHRED));
	temp      = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_TEMP));
	abt       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_ABOUT));
	hlp       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_HELP));
	mov       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_MOVE));
	ren       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_RENAME));
	search    = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SEARCH));
	brd       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BROWSED));
	brf       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BROWSEF));
	exitdlg   = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_EXIT));
	rem       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_REMOVE));
	openf     = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_OPEN));
	lockf     = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_LOCK));
	feico     = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
	feico2    = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON2));


	HINSTANCE lib1 = LoadLibrary(dll1);
	if ((unsigned)lib1 <= HINSTANCE_ERROR)
	{
		MessageBox(0, "A critical dll, fe4.dll couldnot be loaded.FE 4 will now close", "FE ERROR", 0);
		return 1;
	}
	HINSTANCE lib2 = LoadLibrary(dll2);
	if ((unsigned)lib2 <= HINSTANCE_ERROR)
	{	MessageBox(0, "A critical dll, shellfe.dll couldnot be loaded.FE 4 will now close", "FE ERROR", 0);
		return 1;
	}

	//FUNCTIONS FROM DLL

	shred             = (int(__stdcall*)(char[260], long, HWND))GetProcAddress(lib1, "Shred");
	renamefile        = (int(__stdcall*)(char[260], char[260]))GetProcAddress(lib1, "RenameFile");
	dirlist           = (int(__stdcall*)(char[260], char[260], int, HWND))GetProcAddress(lib1, "DirList");
	getUV             = (int(__stdcall*)(char[260], long&, long&))GetProcAddress(lib1, "GetUV");
	browse1           = (int(__stdcall*)(HWND))GetProcAddress(lib2, "Browse1");
	browse2           = (char*(__stdcall*)(HWND, TCHAR*))GetProcAddress(lib2, "Browse2");
	encodeit            = (int(__stdcall*)(char[260], char[260], char[260], long, long, long, HWND))GetProcAddress(lib1, "Encode");
	decodeit            = (int(__stdcall*)(char[260], char[260], char[260], long, long, long, HWND))GetProcAddress(lib1, "Decode");

	if (encodeit == NULL || decodeit == NULL || shred == NULL || renamefile == NULL || dirlist == NULL || getUV == NULL || browse1 == NULL || browse2 == NULL)
	{	MessageBox(0, "FE 4 was not able to load certain procedures.FE 4 will now close", "FE ERROR", 0);
		return 1;

	}
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);


}




