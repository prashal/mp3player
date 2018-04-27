//
//menu.cpp : This file contains the defination of the functions which are called at menu event in main window
//
//

#include "stdafx.h"
#include "resource.h"
#include "playlist.h"
#include "menu.h"

LRESULT CALLBACK OpenUrlProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);



//It shows Windows file open dialog
// hParent - Handle of parent window

void OnFileOpen(HWND hParent)
{
	// Declare
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_MULTISONGLENGTH];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParent;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = MAX_MULTISONGLENGTH;
	ofn.lpstrFilter = "MP3 Files (*.mp3)\0*.mp3\0All Files  (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	
	if (GetOpenFileName(&ofn)==TRUE) 
	{
		SendMessage(hParent,WM_OPENFILE,0,(LPARAM)szFile);
	}
}



void OnUrlFileOpen(HWND hParent)
{
	DialogBox(GetModuleHandle(NULL), (LPCTSTR)IDD_DIALOGOPENURL, hParent, (DLGPROC)OpenUrlProc);
}



void OnPlayListOpen(HWND hParent)
{
	// Declare
	string openplaylist;
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_SONGLENGTH];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParent;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = MAX_SONGLENGTH;
	ofn.lpstrFilter = "MP3 Playlist Files (*.mpl)\0*.mpl\0All Files  (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_EXPLORER;
	
	if (GetOpenFileName(&ofn)==TRUE) 
	{
		SendMessage(hParent,WM_OPENPLAYLIST,0,(LPARAM)szFile);
	}
}


int	OnCurrentPlayListSaveAs(HWND hParent)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_SONGLENGTH];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParent;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = MAX_SONGLENGTH;
	ofn.lpstrFilter = "MP3 Playlist Files (*.mpl)\0*.mpl\0All Files  (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_EXPLORER;
	
	if (GetSaveFileName(&ofn)==TRUE) 
	{
		if(ofn.nFileExtension==NULL)
			strcat(szFile,".mpl");
		SendMessage(hParent,WM_SAVEPLAYLIST,0,(LPARAM)szFile);
		return 1;
	}
	return 0;
}





int	OnAddFileLibrary(HWND hParent)
{
	// Declare
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_MULTISONGLENGTH];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParent;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = MAX_MULTISONGLENGTH;
	ofn.lpstrFilter = "MP3 Files (*.mp3)\0*.mp3\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	
	if (GetOpenFileName(&ofn)==TRUE) 
	{
		SendMessage(hParent,WM_SONGADDTOLIBRARY,0,(LPARAM)szFile);
	}
	return 1;
}


void OnAddPlaylistLibrary(HWND hParent)
{
	// Declare
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_SONGLENGTH];       // buffer for file name
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParent;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = MAX_SONGLENGTH;
	ofn.lpstrFilter = "PlayList Files (*.mpl)\0*.mpl\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_EXPLORER ;
	
	if (GetOpenFileName(&ofn)==TRUE) 
	{
		SendMessage(hParent,WM_PLAYLISTADDTOLIBRARY,0,(LPARAM)szFile);
	}
}


// Mesage handler for open url dialog.

//hWnd - This is the handle of the window.
//Message  - Message which should have to processed.
//wParam  - Extra data about message which are message dependent.
//lParam - Extra data about message which are message dependent.


LRESULT CALLBACK OpenUrlProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	string Filepath;
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case ID_CANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			case ID_OK:
				{
					char str[MAX_SONGLENGTH];
					GetDlgItemText(hDlg,IDC_URLFILENAME,str,MAX_SONGLENGTH);
					Filepath=str;
					if(Filepath.size()==0)
						return 0;
					EndDialog(hDlg,LOWORD(wParam));
					SendMessage(GetParent(hDlg),WM_OPENFILE,0,(LPARAM)&Filepath);
				}
				break;
			case ID_BROWSEURLFILE:
				EndDialog(hDlg, LOWORD(wParam));
				OnFileOpen(GetParent(hDlg));
				break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

	}
    return FALSE;
}




void OnAddFileInCurrentPlayList(HWND hParent)
{

	OPENFILENAME ofn;       // common dialog box structure
	char szFile[MAX_MULTISONGLENGTH];       // buffer for file name
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParent;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = MAX_MULTISONGLENGTH;
	ofn.lpstrFilter = "MP3 Files (*.mp3)\0*.mp3\0All Files  (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	
	if (GetOpenFileName(&ofn)==TRUE) 
	{
 		SendMessage(hParent,WM_SONGADDTOPLAYLIST,0,(LPARAM)szFile);
	}
}
















