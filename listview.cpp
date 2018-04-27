//
//listview.cpp : This file defines the data members of class "ListView" which handle with list view control
//
//

#include "stdafx.h"
#include "listview.h"
#include "resource.h"

LRESULT ProcessCustomDraw (long lParam,int iplay);


//This function create a new list view window 

//hParent - The handle of parent window.
//WINDOW_ID - The Id of list view item.
//x - x-coordinate of top-left corner.
//y - y- coordinate of top-left corner.
//cx - width.
//cy - height;

void ListView::Create(HWND hPrnt,int WINDOW_ID,int x,int y,int cx,int cy)
{
	DWORD Sliderstyle=WS_CHILD | WS_VISIBLE | LVS_REPORT ;
	WindowId=WINDOW_ID;
	hParent=hPrnt;
	iPlay=-1;
	hWnd=CreateWindow(WC_LISTVIEW,"listview",Sliderstyle, x,y,cx,cy,hParent ,(HMENU)WINDOW_ID,GetModuleHandle(NULL),NULL);
	ListView_SetExtendedListViewStyle(hWnd, LVS_EX_FULLROWSELECT);	
}

//Get list view window handle

//hWnd - The List view handle.
HWND ListView::GetWindowHandle(void)
{
	return hWnd;
}

//Resize i.e. modify size and position of list view

//x - x-coordinate of top-left corner.
//y - y- coordinate of top-left corner.
//cx - width.
//cy - height;

void ListView::ResizeListView(int x,int y,int cx,int cy)
{
	SetWindowPos(hWnd,HWND_TOP,x,y,cx,cy,SWP_SHOWWINDOW);
}

//Show or Hide list view

//enable - if this is TRUE then the tree view will be in visible condition otherwise not.

void ListView::ShowListView(bool enable)
{
	if(enable)
		ShowWindow(hWnd,SW_SHOWNORMAL);
	else
		ShowWindow(hWnd,SW_HIDE);
}

//Add new column in list view.

//columno -The index of the column to add.
//size - Length i.e. size of the column. 
//name - The title of the column to be added.

void ListView::AddColumn(int columnno,int size,string name)
{
	LVCOLUMN LvCol;										// Make Coluom struct for ListView
	memset(&LvCol, 0, sizeof(LvCol));					// Reset Coluom
	LvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM; // Type of mask
	LvCol.cx = size;									// width between each coloum
    LvCol.pszText=(char*)name.c_str();					 // First Header
	
	SendMessage(hWnd, LVM_INSERTCOLUMN, columnno, (LPARAM) &LvCol);
}

//Insert item in list view control.

//itemno - The index of item which would be inserted. 
//name - The title of the sub-item to be inserted.

void ListView::InsertItem(int itemno,string name)
{
	LVITEM LvItem;
	memset(&LvItem, 0, sizeof(LvItem));
	LvItem.mask = LVIF_TEXT;							// Text Style
    LvItem.cchTextMax = 256;							// Max size of test

	LvItem.iItem = itemno;								// choose item
	LvItem.iSubItem = 0;								// Put in first coluom
	LvItem.pszText=(char*)name.c_str();
    // Text to display (can be from a char variable) (Items)
	SendMessage(hWnd, LVM_INSERTITEM, 0, (LPARAM) &LvItem);
}

//Insert sub-item of specific item of list view control

//itemno - The index of item in which sub-item would be in-serted. 
//subitemno - The index of sub-item to be inserted.
//name - The title of the sub-item to be inserted.

void ListView::InsertSubItem(int itemno,int subitemno,string name)
{
	LVITEM LvItem;
	memset(&LvItem, 0, sizeof(LvItem));
	LvItem.mask = LVIF_TEXT;							// Text Style
    LvItem.cchTextMax = 256;							// Max size of test

	LvItem.iItem = itemno;								// choose item
	LvItem.iSubItem = subitemno;
    LvItem.pszText=(char*)name.c_str();
    SendMessage(hWnd, LVM_SETITEM, 0, (LPARAM) &LvItem);
}

//Delete all items of this list view.
void ListView::DeleteAllItem(void)
{
	SendMessage(hWnd, LVM_DELETEALLITEMS, 0, 0);
}

//Delete specified item. 
//idelete - The index of the item to delete

void ListView::DeleteItem(int idelete)
{
	SendMessage(hWnd, LVM_DELETEITEM, idelete, 0);
}

//Delete specified column. 
//idelete (in):The index of the column to delete

void ListView::DeleteColumn(int idelete)
{
	SendMessage(hWnd, LVM_DELETECOLUMN, idelete, 0);
}

//Delete all columns of this list view

void ListView::DeleteAllColumn()
{
	while(1)
	{
		if(SendMessage(hWnd, LVM_DELETECOLUMN, 0, 0)==FALSE)
			break;
	}
}

//In the case of playlist/library ,this function gives the index of current focused and selected song. 
//focusedcount - This is the index of focused item.

int ListView::GetFocusedItemNo(void)
{
	int focusedcount=SendMessage(hWnd,LVM_GETNEXTITEM,-1,LVNI_SELECTED|LVIS_FOCUSED);
	return focusedcount;	
}


//In the case of playlist,this function sets the index of current playing song.
//playitemcount - The index of current playing song

void ListView::SetPlayItemNo(int playitemcount)
{
	iPlay=playitemcount;
}


//In the case of playlist,this function gets the index of current playing song.
//iPlay - The index of current playing song

int ListView::GetPlayItemNo(void)
{
	return iPlay;
}


//Get the number of total item of this list view.

int ListView::GetTotalItemNo(void)
{
	return SendMessage(hWnd,LVM_GETITEMCOUNT,0,0);
}


//Get the text of specified item of listview

//iNum - item number of which text has to get.Value of iN-um is 0 for first item.
//subitemno - sub-item number of which text has to get.Value of subitemno is 0 for for getting the text of an item.
//temp - Pointer to the string in which the item/sub-item text will be saved.
//maxsize - Maximum length of string which temp can ac-commodate.

char* ListView::GetItemText(int iNum,int subitemno, char * temp,int maxsize)
{
	ListView_GetItemText(hWnd, iNum, subitemno, temp,maxsize);
	return temp;
}

//Process notification message of list view control according to requirements (This is designed for Playlist).

//message - Extra data about notification message.This is  a pointer to NMHDR type data.

int ListView::SendListBoxMessage(LPARAM message)
{
	switch(((LPNMHDR)message)->code)
	{
	case NM_CUSTOMDRAW:
		if(((LPNMLISTVIEW)message)->hdr.hwndFrom==this->hWnd)
			return ProcessCustomDraw((long)message,iPlay);
		break;
	case NM_RETURN:
	case NM_DBLCLK:
		if(this->GetFocusedItemNo()!=-1)
			SendMessage(GetParent(hWnd),WM_STARTPLAY,this->GetFocusedItemNo(),0);
		break;
	case NM_RCLICK:
		{
			HMENU hMenu = LoadMenu (NULL, MAKEINTRESOURCE (IDR_CURRENTPLAYLISTPOPUP));
			HMENU hPopupMenu = GetSubMenu (hMenu, 0);
			POINT pt;
			SetMenuDefaultItem (hPopupMenu, -1, TRUE);
			GetCursorPos (&pt);
			SetForegroundWindow (hWnd);
			if(this->GetFocusedItemNo()==-1)
			{
				EnableMenuItem(hPopupMenu,IDM_DELETEFILECURRENTPLAYLIST,MF_GRAYED);
				EnableMenuItem(hPopupMenu,IDM_PLAYENTER,MF_GRAYED);
			}
			DWORD iSelect=TrackPopupMenu (hPopupMenu,TPM_LEFTALIGN, pt.x, pt.y, 0, hParent, NULL);
			SetForegroundWindow (hWnd);
			DestroyMenu (hPopupMenu);
			DestroyMenu (hMenu);
		}
		break;
		
	}
	return 0;
}

//Process notification message of list view control according to requirements (This is designed for Library).

//message - Extra data about notification message.This is  a pointer to NMHDR type data.

int ListView::SendListBoxMessage(LPARAM message,TreeView *cLibTree)
{
	HTREEITEM hitem=cLibTree->GetFocusedItem();
	if(hitem==NULL)
		return 0;
	LPARAM sel=cLibTree->GetItemLparamTreeView(hitem);
	if(HIWORD(sel)&TREE_PLAYLIST)
	{
		if(LOWORD(sel)==0)
		{
			switch(((LPNMHDR)message)->code)
			{
			case NM_RETURN:
			case NM_DBLCLK:
				if(this->GetFocusedItemNo()!=-1)
					SendMessage(GetParent(hWnd),WM_COMMAND,IDM_PLAYPLAYLIST,0);
				break;
			case NM_RCLICK:
				{
					HMENU hMenu = LoadMenu (NULL, MAKEINTRESOURCE (IDR_PLAYLISTPOPUP));
					HMENU hPopupMenu = GetSubMenu (hMenu, 0);
					POINT pt;
					SetMenuDefaultItem (hPopupMenu, -1, TRUE);
					GetCursorPos (&pt);
					SetForegroundWindow (hWnd);
					if(this->GetFocusedItemNo()==-1)
					{
						EnableMenuItem(hPopupMenu,IDM_DELETELIBRARYPLAYLIST,MF_GRAYED);
						EnableMenuItem(hPopupMenu,IDM_PLAYPLAYLIST,MF_GRAYED);
					}
					DWORD iSelect=TrackPopupMenu (hPopupMenu,TPM_LEFTALIGN, pt.x, pt.y, 0, hParent, NULL);
					SetForegroundWindow (hWnd);
					DestroyMenu (hPopupMenu);
					DestroyMenu (hMenu);
				}
				break;
				
			}
		}
		else
		{
			switch(((LPNMHDR)message)->code)
			{
			case NM_RETURN:
			case NM_DBLCLK:
				if(this->GetFocusedItemNo()!=-1)
				{
					SendMessage(GetParent(hWnd),WM_COMMAND,IDM_PLAYSONGFROMLIBRARY,0);
				}
				break;
			}
		}
	}
	else if(HIWORD(sel)&TREE_LIBRARY)
	{
		if(LOWORD(sel)!=0)
		{
			switch(((LPNMHDR)message)->code)
			{
			case NM_RETURN:
			case NM_DBLCLK:
				if(this->GetFocusedItemNo()!=-1)
				{
					SendMessage(GetParent(hWnd),WM_COMMAND,IDM_PLAYSONGFROMLIBRARY,0);
				}
				break;
			case NM_RCLICK:
				{
					HMENU hMenu = LoadMenu (NULL, MAKEINTRESOURCE (IDR_LIBRARYPOPUP));
					HMENU hPopupMenu = GetSubMenu (hMenu, 0);
					POINT pt;
					SetMenuDefaultItem (hPopupMenu, -1, TRUE);
					GetCursorPos (&pt);
					SetForegroundWindow (hWnd);
					if(this->GetFocusedItemNo()==-1)
					{
						EnableMenuItem(hPopupMenu,IDM_DELETELIBRARYFILE,MF_GRAYED);
						EnableMenuItem(hPopupMenu,IDM_PLAYSONGFROMLIBRARY,MF_GRAYED);
						EnableMenuItem(hPopupMenu,IDM_SETRATING,MF_GRAYED);
					}
					DWORD iSelect=TrackPopupMenu (hPopupMenu,TPM_LEFTALIGN, pt.x, pt.y, 0, hParent, NULL);
					SetForegroundWindow (hWnd);
					DestroyMenu (hPopupMenu);
					DestroyMenu (hMenu);
				}
				break;
				
			}
		}
	}

	return 0;
}


//Process custom redraw message of list view control.(This is designed for Playlist).

//lParam - The custom redraw message.
//iplay - The index of playing item

LRESULT ProcessCustomDraw (LPARAM lParam,int iplay)
{
    LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)lParam;
    switch(lplvcd->nmcd.dwDrawStage) 
    {
        case CDDS_PREPAINT : //Before the paint cycle begins
            //request notifications for individual listview items
            return CDRF_NOTIFYITEMDRAW;
            
        case CDDS_ITEMPREPAINT: //Before an item is drawn
            {
				

				if(lplvcd->nmcd.dwItemSpec==iplay)
				{
					lplvcd->clrText = RGB(0,0,255);
					lplvcd->clrTextBk   = RGB(255,255,255);      
				}
				else
				{
					lplvcd->clrText = RGB(100,55,23);
					lplvcd->clrTextBk   = RGB(255,255,255);       
				}
                return CDRF_NEWFONT;
            }
            break;
    }
    return CDRF_DODEFAULT;
}