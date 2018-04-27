//
//treeview.cpp : This file defines the data members of class "TreeView" which handle with tree view control
//
//


#include "stdafx.h"
#include "treeview.h"
#include "resource.h"


//This function create a new tree view control window

//hParent - The handle of parent window.
//WINDOW_ID - The Id of tree view item.
//x - x-coordinate of top-left corner.
//y - y- coordinate of top-left corner.
//cx - width.
//cy - height;

void TreeView::Create(HWND hPrnt,int WINDOW_ID,int x,int y,int cx,int cy)
{
	DWORD dwStyle= WS_VISIBLE | WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |TVS_SHOWSELALWAYS;

	WindowId=WINDOW_ID;
	hParent=hPrnt;
	hWnd=CreateWindow(WC_TREEVIEW,"TreeView",dwStyle, x,y, cx,cy, hPrnt,  (HMENU) WINDOW_ID, GetModuleHandle(NULL),NULL);

}

//This function will initialize the item of tree view. 
  
//cmp3player - The reference of the MP3Player class object.
  
void TreeView::Initlize(MP3Player * cmp3player)
{
	//Initialize Tree View
	HTREEITEM hplay,hlib,hrat,harst,halbm;
	TreeView_DeleteAllItems(hWnd);
	hplay=AddItem("PlayLists",NULL,0,TREE_PLAYLIST);
	hlib=AddItem("Library",NULL,0,TREE_LIBRARY);
	int num=0;
	bool status=FALSE;
	PlayList plst;
	char str[100];
	while(1)
	{
		plst=cmp3player->GetPlaylistByNumberFromLibrary(num,&status);
		GetFileTitle(((string)plst.GetPlayListName()).c_str(),str,100);
		if(status==FALSE)
			break;
		AddItem(str,hplay,num+1,0);				//As tree item numbering start from 1
		num++;
	}

	halbm=AddItem("Albums",hlib,0,TREE_ALBUM);
	harst=AddItem("Artists",hlib,0,TREE_ARTIST);
	hrat=AddItem("Ratings",hlib,0,TREE_RATING);
	num=0;
	Song sng;
	while(1)
	{
		sng=cmp3player->GetSongByNumberFromLibrary(num,&status);
		if(status==FALSE)
			break;
		if(GetSearchString((char *)((string)sng.GetAlbumName()).c_str(),halbm)==0)
			AddItem((char *)((string)sng.GetAlbumName()).c_str(),halbm,num+1,0);				//As tree item numbering start from 1

		if(GetSearchString((char *)((string)sng.GetArtist()).c_str(),harst)==0)
			AddItem((char *)((string)sng.GetArtist()).c_str(),harst,num+1,0);				//As tree item numbering start from 1
		switch(sng.GetRating())
		{
		case 1:
			sprintf(str,"*");
			break;
		case 2:
			sprintf(str,"**");
			break;
		case 3:
			sprintf(str,"***");
			break;
		case 4:
			sprintf(str,"****");
			break;
		case 5:
			sprintf(str,"*****");
			break;
		default:
			sprintf(str,"Unknown");
			break;
		}
		if(GetSearchString(str,hrat)==0)
			AddItem(str,hrat,num+1,0);				//As tree item numbering start from 1
		
		num++;
	}
}


// Get tree view window handle  

HWND TreeView::GetWindowHandle(void)
{
	return hWnd;
}

//Resize Tree View control

//x - x-coordinate of top-left corner.
//y - y- coordinate of top-left corner.
//cx - width.
//cy - height;

void TreeView::ResizeTreeView(int x,int y,int cx,int cy)
{
	SetWindowPos(hWnd,HWND_TOP,x,y,cx,cy,SWP_SHOWWINDOW);
}

//Show or HideTree View control

//enable - if this is TRUE then the tree view will be in visible condition otherwise not
void TreeView::ShowTreeView(bool enable)
{
	if(enable)
		ShowWindow(hWnd,SW_SHOWNORMAL);
	else
		ShowWindow(hWnd,SW_HIDE);
}




//Get the handle of first child of a tree view item
//hRootItem - The handle of the item of which first child has to get.
//If successful ,it return the first child of the item specified ,otherwise NULL

HTREEITEM TreeView::GetFirstChildTreeView(HTREEITEM hRootItem)
{
	HTREEITEM h=TreeView_GetChild(hWnd,hRootItem);
	return h;
}



//Get the handle of next sibling of a tree view item
//hRootItem - The handle of the item of which sibling has to get. 
//If successful ,it return the next sibling of the item specified ,otherwise NULL  

HTREEITEM TreeView::GetNextsiblingTreeView(HTREEITEM hRootItem)
{
	HTREEITEM h=TreeView_GetNextSibling(hWnd,hRootItem);
	return h;
}

//Get title of a specified tree view item

//hRootItem - The handle of the item of which first child has to get.
//str - pointer to a character array in which the text have to save.
//len - Maximum possible length of "str".

void TreeView::GetItemTextTreeView(HTREEITEM hRootItem,char * str,int len)
{
	TVITEM ptitem={0};
	ptitem.hItem=hRootItem;
	ptitem.mask=TVIF_TEXT;
	ptitem.pszText =str;
	ptitem.cchTextMax=len;
	TreeView_GetItem(hWnd,&ptitem);
}

//Get lParam value of a specified tree view item

//pitem - The handle of the item of which lParam value  has to get.

//Return :lParam value of a specified tree view item

LPARAM TreeView::GetItemLparamTreeView(HTREEITEM pitem)
{
	TVITEM ptitem={0};
	ptitem.hItem=pitem;
	ptitem.mask=TVIF_PARAM;
	TreeView_GetItem(hWnd,&ptitem);
	return ptitem.lParam;
}

//Delete tree view item
//hRootItem -The handle of the item to delete.

void TreeView::DeleteItem(HTREEITEM hRootItem)
{
	TreeView_DeleteItem(hWnd,hRootItem);
}

//Get the handle of the focused tree view item
//If successful ,it return the handle of focused item ,otherwise NULL

HTREEITEM TreeView::GetFocusedItem(void)
{
	return TreeView_GetSelection(hWnd);	
}



//Search a string in the child items of a specific tree view item

//str - pointer of string which has to search in child items.  
//hroot - This is handle of root element .This function ser-ches the string in the child of this element

//If any child name matches with "str" content, then the func-tion returns 1 otherwise 0

int TreeView::GetSearchString(char *str,HTREEITEM hroot)
{
	HTREEITEM htvi;
	char temp[100];
	htvi=GetFirstChildTreeView(hroot);
	if(htvi==NULL)
		return 0;
	GetItemTextTreeView(htvi,temp,100);
	if(!strcmp(temp,str))
		return 1;
	while(1)
	{
		htvi=GetNextsiblingTreeView(htvi);
		if(htvi==NULL)
			return 0;
		GetItemTextTreeView(htvi,temp,100);
		if(!strcmp(temp,str))
			return 1;
	}
	return 0;
}

//Add new item in tree view control

//lpszItem (in) : The title of the tree view item.
//hPrevRootItem (in) :The handle of the root item under of which new item is going to create.
//Itemno (in): this is the item number.
//			Item (in): This is valid for basic item of Tree View.

//Viz.
//			TREE_PLAYLIST    	for playlist item
//			TREE_LIBRARY     	for library item
//			TREE_ALBUM  		for album item
//			TREE_ARTIST  		for artist item
//			TREE_RATING			for raring item

HTREEITEM TreeView::AddItem(char *lpszItem,HTREEITEM hPrevRootItem,long itemno,int item)
{
	TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
    static HTREEITEM hPrev;
 
    
	memset(&tvi,0,sizeof(tvi));
	tvi.mask = TVIF_PARAM;
	tvi.hItem=hPrevRootItem;
	TreeView_GetItem(hWnd,&tvi);
	itemno=MAKELONG(itemno,(HIWORD(tvi.lParam)|item));



	memset(&tvi,0,sizeof(tvi));
	tvi.mask = TVIF_TEXT|TVIF_PARAM; 

    // Set the text of the item. 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = lstrlen(lpszItem); 
 
 
	tvi.lParam=itemno;

    tvins.item = tvi; 
 
    // Set the parent item based on the specified level. 
    if (hPrevRootItem == NULL) 
        tvins.hParent = TVI_ROOT;
	else
        tvins.hParent = hPrevRootItem; 
 
    // Add the item to the tree view control. 
    hPrev = (HTREEITEM) SendMessage(hWnd, TVM_INSERTITEM, 0, 
         (LPARAM) (LPTVINSERTSTRUCT) &tvins); 
 
 
    return hPrev; 

}

//Process notification message of tree view control according to requirements
//message - Extra data about notification message.This is  a pointer to NMHDR type data
//Return value is FALSE if after execution of this function the program must run default window procedure. Otherwise re-turn value is TRUE

int TreeView::SendTreeMessage(LPARAM message)
{
	switch(((LPNMHDR)message)->code)
	{
	case NM_RETURN:
	case NM_DBLCLK:
		{
			HTREEITEM pitem=0;
			TVITEM ptitem={0};
			char str[MAX_SONGLENGTH];
			pitem=TreeView_GetSelection(hWnd);
			ptitem.hItem=pitem;
			ptitem.mask=TVIF_TEXT|TVIF_PARAM;
			ptitem.pszText =str;
			ptitem.cchTextMax=MAX_SONGLENGTH;
			TreeView_GetItem(hWnd,&ptitem);
			SendMessage(GetParent(hWnd),WM_TREEVIEWDBCLK,(WPARAM)pitem,(LPARAM)ptitem.lParam);
	
		}
		break;
	case TVN_SELCHANGED :
		SendMessage(GetParent(hWnd),WM_REFRESHLIBRARYLIST,0,0);
		break;
	}
	return 0;
}
