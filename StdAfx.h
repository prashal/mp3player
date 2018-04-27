// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <Commdlg.h>
#include <mmsystem.h>
#include <CommCtrl.h>

// C++ RunTime Header Files
#include <string>
#include <iostream>
#include <fstream>
#include <list>

#define IDC_LIBRARYTREE			10001
#define IDC_PROGRESSSLIDER		10002
#define IDC_VOLUMESLIDER		10003
#define ID_PLAY					10004
#define ID_STOP					10005
#define ID_NEXT					10006
#define ID_PREV					10007
#define ID_MUTE					10008
#define IDC_PLAYLISTVIEW		10009
#define IDC_LIBRARYLISTVIEW		10010

#define WM_STARTPLAY			WM_USER+10
#define WM_OPENFILE				WM_USER+11
#define WM_OPENPLAYLIST			WM_USER+12
#define WM_SAVEPLAYLIST			WM_USER+13
#define WM_SONGADDTOPLAYLIST	WM_USER+14
#define WM_REFRESHPLAYLIST		WM_USER+15
#define WM_REFRESHLIBRARYLIST	WM_USER+16
#define WM_REFRESHTREEVIEW		WM_USER+17
#define WM_TREEVIEWDBCLK		WM_USER+18
#define WM_SONGADDTOLIBRARY		WM_USER+19
#define WM_PLAYLISTADDTOLIBRARY WM_USER+20
#define WM_TREEVIEWSELCHNG      WM_USER+21
#define WM_REFRESHLIBRARYTREE	WM_USER+22

enum RepeatSong 
{ 
	REPEATNONE=0,REPEATONE
};

enum 
{ 
	PLAYLIST=0,LIBRARY=1
};


#define VALUESET TRUE
#define VALUEGET FALSE
#define TREE_PLAYLIST 0x00001
#define TREE_LIBRARY  0x00002
#define TREE_ALBUM    0x00004
#define TREE_ARTIST   0x00008
#define TREE_RATING  0x00010


#endif 


#define MAX_SONGLENGTH			260
#define MAX_MULTISONGLENGTH		1600