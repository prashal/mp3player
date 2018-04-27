//
//treeview.h : This file declare the class "TreeView" and its data member and function
//
//

#include <windows.h>
#include <CommCtrl.h>
#include <string>
#include "mp3player.h"
#include "playlist.h"
using namespace std;

#ifndef _TREEVIEW_CLASS
#define _TREEVIEW_CLASS

class TreeView
{
	HWND hWnd;
	HWND hParent;
	DWORD WindowId;
	int iPlay;
public:
	void Create(HWND hParent,int WINDOW_ID,int x,int y,int cx,int cy);
	void TreeView::Initlize(MP3Player * cmp3player);

	HWND GetWindowHandle(void);
	void ResizeTreeView(int x,int y,int cx,int cy);
	void ShowTreeView(bool enable);

	HTREEITEM AddItem(char* lpszItem,HTREEITEM hPrevRootItem,long itemno,int item);
	void GetItemTextTreeView(HTREEITEM hRootItem,char * str,int len);
	LPARAM GetItemLparamTreeView(HTREEITEM pitem);

	void DeleteItem(HTREEITEM hRootItem);
	HTREEITEM GetFocusedItem(void);

	HTREEITEM GetFirstChildTreeView(HTREEITEM hRootItem);
	HTREEITEM GetNextsiblingTreeView(HTREEITEM hRootItem);
	int GetSearchString(char *str,HTREEITEM);

	int SendTreeMessage(LPARAM message);
};
#endif
