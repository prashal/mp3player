//
//listview.h : This file declare the class "ListView" and its data member and function
//
//

#include <windows.h>
#include <string>
#include "treeview.h"
using namespace std;

#ifndef _LISTVIEW_CLASS
#define _LISTVIEW_CLASS

class ListView
{
	HWND hWnd;
	HWND hParent;
	DWORD WindowId;
	int iPlay;
public:
	void Create(HWND hParent,int WINDOW_ID,int x,int y,int cx,int cy);
	
	HWND GetWindowHandle(void);
	void ResizeListView(int x,int y,int cx,int cy);
	void ShowListView(bool enable);

	void AddColumn(int columnno,int size,string name);

	void InsertItem(int itemno,string name);
	void InsertSubItem(int itemno,int subitemno,string name);

	void DeleteAllItem(void);
	void DeleteItem(int idelete);

	void DeleteColumn(int idelete);
	void DeleteAllColumn(void);

	int GetFocusedItemNo(void);
	void SetPlayItemNo(int);
	int GetPlayItemNo(void);
	int GetTotalItemNo(void);
	char* GetItemText(int iNum,int subitemno, char * temp,int maxsize);
	int SendListBoxMessage(LPARAM message);
	int SendListBoxMessage(LPARAM message,TreeView *cLibTree);
};
#endif
