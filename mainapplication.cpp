//
//mainapplication.cpp : This file defines the data members of class "MainApplication" which create graphical interface and 
//						process the message according to requirements
//
//


#include "stdafx.h"
#include "mainapplication.h"
#include "mp3player.h"
#include "menu.h"
#include "resource.h"
#include "error.h"


LRESULT CALLBACK	AboutProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	SetRatingProc(HWND, UINT, WPARAM, LPARAM);

void ShowLibraryForPlayList(ListView *cLibraryListView,MP3Player *cMp3Player);
void ShowLibraryForPlayListItem(ListView *cLibraryListView,MP3Player *cMp3Player,int num);
void ShowLibraryForLibrary(ListView *cLibraryListView,MP3Player *cMp3Player);
void ShowLibraryForLibraryItemsong(ListView *cLibraryListView,MP3Player *cMp3Player,int type,char name[]);
void ShowLibraryForLibraryItem(ListView *cLibraryListView,TreeView *cLibTree,HTREEITEM hitem);


char *sendsong;					//Used to send song data to setting procedure


//Constractor of MainApplication class.

MainApplication::MainApplication()
{
}


//This method create all object (like buttons, list view, tree view, slider) 
//of graphical interface. 

void MainApplication::InitApplication()
{
	cMp3Player=new MP3Player;
	cButtonPlay=new Button;
	cButtonStop=new Button;
	cButtonPrev=new Button;
	cButtonNext=new Button;
	cButtonMute=new Button;
	cSliderProgress=new Slider;
	cSliderVolume=new Slider;
	cPlayListView=new ListView;
	cLibraryListView=new ListView;
	cLibraryTree=new TreeView;
}

//Constractor of MainApplication class.This frees all the objects.

MainApplication::~MainApplication()
{
	delete cMp3Player;
	delete cButtonPlay;
	delete cButtonStop;
	delete cButtonPrev;
	delete cButtonNext;
	delete cButtonMute;
	delete cSliderProgress;
	delete cSliderVolume;
	delete cPlayListView;
	delete cLibraryListView;
	delete cLibraryTree;
}

//Process Message according to requirements.

//hWnd - This is the handle of the window.
//Message  - Message which should have to processed.
//wParam  - Extra data about message which are message dependent.
//lParam - Extra data about message which are message dependent.

int MainApplication::SendApplicationMessage(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{

	hWnd=hwnd;


	RECT mainrect;
	Song song;
	char str[100];
	string strng;
	int count;
	bool status;
	switch (message) 
	{
	case WM_CREATE:
		cSliderProgress->Create(hWnd,IDC_PROGRESSSLIDER,100,100,100,20,HORIZONTAL);
		cSliderVolume->Create(hWnd,IDC_VOLUMESLIDER, 200,100,100,20 ,HORIZONTAL);
		
		cButtonPlay->Create(hWnd,"Play",ID_PLAY, 100,100 /* position*/,50,20/*size*/,PUSHBUTTON);
		cButtonStop->Create(hWnd,"Stop",ID_STOP, 100,130 /* position*/,50,20/*size*/,PUSHBUTTON);
		cButtonNext->Create(hWnd,"Next",ID_NEXT, 220,100 /* position*/,50,20/*size*/,PUSHBUTTON);
		cButtonPrev->Create(hWnd,"Prev",ID_PREV, 220,130 /* position*/,50,20/*size*/,PUSHBUTTON);
		cButtonMute->Create(hWnd,"Mute",ID_MUTE, 340,130 /* position*/,150,50/*size*/,CHECKBUTTON);
		
		cPlayListView->Create(hWnd,IDC_PLAYLISTVIEW,50,50,400,300);
		cLibraryListView->Create(hWnd,IDC_LIBRARYLISTVIEW,50,50,400,300);
		cLibraryTree->Create(hWnd,IDC_LIBRARYTREE,10,30,90,340);
		cLibraryTree->Initlize(cMp3Player);

		cPlayListView->AddColumn(0,200,"Song Title");
		cPlayListView->AddColumn(1,50,"Length");


		cButtonPlay->Enable_CheckButton(FALSE);
		cButtonStop->Enable_CheckButton(FALSE);
		cButtonPrev->Enable_CheckButton(FALSE);
		cButtonNext->Enable_CheckButton(FALSE);
		cButtonMute->Enable_CheckButton(FALSE);

		cSliderVolume->SetSliderRange(0, 1000); 
		cSliderVolume->SetSliderPageSize(20); 
		cSliderVolume->SetSliderFreq(cSliderVolume->GetSliderMaxRange());
	case WM_SIZE:
		{
			int height,width;
			GetClientRect(hWnd,&mainrect);
			height=mainrect.bottom-mainrect.top;
			width=mainrect.right-mainrect.left;

			cPlayListView->ResizeListView(mainrect.left+width*15/20,mainrect.top+10,width*5/20-10,height-80);
			cLibraryListView->ResizeListView(mainrect.left+width*3/20,mainrect.top+10,width*12/20-10,height-80);
			
			cLibraryTree->ResizeTreeView(mainrect.left+10,mainrect.top+10,width*3/20-20,height-80);

			cSliderProgress->ResizeSlider(mainrect.left+5,mainrect.bottom-60,mainrect.right-mainrect.left-10,20);
			cSliderVolume->ResizeSlider(mainrect.left+360,mainrect.bottom-40,100,20);
			
			cButtonStop->ResizeMoveButton(mainrect.left+5,mainrect.bottom-40,60,20);			
			cButtonPlay->ResizeMoveButton(mainrect.left+75,mainrect.bottom-40,60,20);			
			cButtonPrev->ResizeMoveButton(mainrect.left+145,mainrect.bottom-40,60,20);			
			cButtonNext->ResizeMoveButton(mainrect.left+215,mainrect.bottom-40,60,20);			
			cButtonMute->ResizeMoveButton(mainrect.left+300,mainrect.bottom-40,60,20);
		}
	case WM_REFRESHPLAYLIST:
		cPlayListView->DeleteAllItem();
		count=0;
		while(1)
		{
			int temp;
			song=cMp3Player->GetSongByNumberFromPlayList(count++,&status);
			if(status==FALSE)
				break;
			cPlayListView->InsertItem(count-1,song.GetTitle());
			temp=song.GetSongLengthinSecond();
			if(temp>=0)
				sprintf(str,"%d:%0.2d:%0.2d",temp/3600,temp/60,temp%60);
			else
				sprintf(str,"");
			cPlayListView->InsertSubItem(count-1,1,str);
		}
		if(cMp3Player->MuteAll(VALUEGET))
			cButtonMute->Enable_CheckButton(TRUE);
		else
			cButtonMute->Enable_CheckButton(FALSE);
		cSliderVolume->SetSliderPos(cMp3Player->VolumeAll(NULL,VALUEGET));
	
		break;
	case WM_REFRESHLIBRARYTREE:
		cLibraryTree->Initlize(cMp3Player);
		break;
	case WM_REFRESHLIBRARYLIST:
		cLibraryListView->DeleteAllItem();
		{
			HTREEITEM hitem=cLibraryTree->GetFocusedItem();
			if(hitem==NULL)
				break;
			LPARAM sel=cLibraryTree->GetItemLparamTreeView(hitem);
			if(HIWORD(sel)&TREE_PLAYLIST)
			{
				if(LOWORD(sel)==0)
					ShowLibraryForPlayList(cLibraryListView,cMp3Player);
				else
					ShowLibraryForPlayListItem(cLibraryListView,cMp3Player,LOWORD(sel)-1);        //As Tree view item start from 1
			}
			if(HIWORD(sel)&TREE_LIBRARY)
			{
				if((LOWORD(sel)==0)&&(!(HIWORD(sel)&TREE_ALBUM))&&(!(HIWORD(sel)&TREE_ARTIST))&&(!(HIWORD(sel)&TREE_RATING)))
					ShowLibraryForLibrary(cLibraryListView,cMp3Player);
				else if(LOWORD(sel)==0)
				{
					ShowLibraryForLibraryItem(cLibraryListView,cLibraryTree,hitem);
				}
				else
				{
					cLibraryTree->GetItemTextTreeView(hitem,str,100);
					ShowLibraryForLibraryItemsong(cLibraryListView,cMp3Player,HIWORD(sel),str);
				}
			}
		}
		break;
	case WM_NOTIFY:
		switch(LOWORD(wParam))
		{
		case IDC_PLAYLISTVIEW:
			return cPlayListView->SendListBoxMessage(lParam);
		case IDC_LIBRARYLISTVIEW:
			return cLibraryListView->SendListBoxMessage(lParam,cLibraryTree);
		case IDC_LIBRARYTREE:
			return cLibraryTree->SendTreeMessage(lParam);
		}
		break;
	case WM_OPENFILE:
		cMp3Player->Close();
		cMp3Player->NewPlayList();
		cMp3Player->AddSongInPlayList((char*)lParam,-1);
		SendMessage(hWnd,WM_REFRESHPLAYLIST,0,0);
		break;
	case WM_SAVEPLAYLIST:
		strng.assign((char*)lParam);
		if(strng.size()>0)
		{
			cMp3Player->SavePlayList(strng);
			cMp3Player->AddPlayListInLibrary(strng);
		}
		break;
	case WM_OPENPLAYLIST:
		strng.assign((char*)lParam);
		if(strng.size()>0)
			cMp3Player->OpenPlayList(strng);
		SendMessage(hWnd,WM_STARTPLAY,0,0);
		SendMessage(hWnd,WM_REFRESHPLAYLIST,0,0);
		break;
	case WM_SONGADDTOPLAYLIST:		
		cMp3Player->AddSongInPlayList((char*)lParam,-1);

		SendMessage(hWnd,WM_REFRESHPLAYLIST,0,0);
		break;
	case WM_SONGADDTOLIBRARY:
		cMp3Player->AddSongInLibrary((char*)lParam,-1);
		SendMessage(hWnd,WM_REFRESHLIBRARYTREE,0,0);
		SendMessage(hWnd,WM_REFRESHLIBRARYLIST,0,0);
		break;
	case WM_PLAYLISTADDTOLIBRARY:
		cMp3Player->AddPlayListInLibrary((char*)lParam);
		cLibraryTree->Initlize(cMp3Player);
		SendMessage(hWnd,WM_REFRESHLIBRARYLIST,0,0);
		break;
	case WM_STARTPLAY:
		if(wParam!=-1)
		{
			song=cMp3Player->GetSongByNumberFromPlayList(wParam,&status);
			if(status==FALSE)
				break;
			strng=song.GetFilePath();

			cMp3Player->Open(strng);
			cMp3Player->Play();
			count=cMp3Player->GetLastErrorCode();
			if(count!=0)
			{
				string s=GetErrorString(count);
				MessageBox(hWnd,s.c_str(),"Error...",MB_OK);
				break;
			}
			song.SetSongLengthinSecond(cMp3Player->AudioLength()/1000);
			cMp3Player->ModifySongInPlayList(song,wParam);

			cPlayListView->SetPlayItemNo(wParam);
			SendMessage(hWnd,WM_REFRESHPLAYLIST,0,0);
		}
		else
			break;
		
		
		cButtonPlay->Enable_CheckButton(TRUE);
		cButtonStop->Enable_CheckButton(TRUE);
		cButtonPrev->Enable_CheckButton(TRUE);
		cButtonNext->Enable_CheckButton(TRUE);
		cButtonPlay->SetButtonLabel("Pause");

		SetTimer(hWnd,WM_TIMER,1000,NULL);

		cSliderProgress->SetSliderRange(0, cMp3Player->AudioLength()/1000); 
		cSliderProgress->SetSliderPageSize(20); 
		cSliderProgress->SetSliderFreq(cSliderProgress->GetSliderMaxRange());
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		
		case IDM_FILEOPEN:
			OnFileOpen(hWnd);
			break;
		case IDM_OPENURLFILE:
			OnUrlFileOpen(hWnd);
			break;
		case IDM_OPENPLAYLIST:			
			OnPlayListOpen(hWnd);
			break;
		case IDM_SAVECURRENTPLAYLIST:		
			strng=cMp3Player->GetPlayListName();
			if(strng.size()>0)
				cMp3Player->SavePlayList(strng);
			else
				OnCurrentPlayListSaveAs(hWnd);
			break;
		case IDM_SAVECURRENTPLAYLISTAS:			
			OnCurrentPlayListSaveAs(hWnd);
			break;
		case IDM_ADDLIBRARYFILE:		//Click on the main menu for adding file to library 
			OnAddFileLibrary(hWnd);
			break;
		case IDM_ADDLIBRARYPLAYLIST:	//Click on the main menu for adding playlist to library 		
			OnAddPlaylistLibrary(hWnd);
			break;
		case IDM_PLAYPLAYLIST:			
			count=cLibraryListView->GetFocusedItemNo();
			if(count>=0)
			{
				cLibraryListView->GetItemText(count,1,str,100);
				SendMessage(hWnd,WM_OPENPLAYLIST,0,(LPARAM)str);
			}
			break;
		case IDM_DELETELIBRARYPLAYLIST:
			cMp3Player->DeletePlayListFromLibrary(cLibraryListView->GetFocusedItemNo());
			cLibraryTree->Initlize(cMp3Player);
			SendMessage(hWnd,WM_REFRESHLIBRARYLIST,0,0);
			break;
		
		
		case IDM_PLAYSONGFROMLIBRARY:
			count=cLibraryListView->GetFocusedItemNo();
			if(count>=0)
			{
				cLibraryListView->GetItemText(count,1,str,100);
				SendMessage(hWnd,WM_OPENFILE,0,(LPARAM)str);
				SendMessage(hWnd,WM_STARTPLAY,0,0);
			}
			break;
		case IDM_DELETELIBRARYFILE:
			count=cLibraryListView->GetFocusedItemNo();
			cMp3Player->DeleteSongFromLibrary(count);
			cLibraryTree->Initlize(cMp3Player);
			SendMessage(hWnd,WM_REFRESHLIBRARYLIST,0,0);
			break;

		case IDM_SETRATING:
			count=cLibraryListView->GetFocusedItemNo();
			if(count!=-1)
			{
				sendsong=(char*)malloc(MAX_SONGLENGTH*sizeof(char));
				cLibraryListView->GetItemText(count,1,sendsong,260);
				int rating=DialogBox(GetModuleHandle(NULL), (LPCTSTR)IDD_DIALOGSETRATINGS, hWnd, (DLGPROC)SetRatingProc);
				free(sendsong);
				cLibraryListView->GetItemText(count,1,str,MAX_SONGLENGTH);
				song.OpenSong(str);
				song.SetRating(rating);
				cMp3Player->ModifySongInLibrary(song,count);
				SendMessage(hWnd,WM_REFRESHLIBRARYLIST,0,0);
			}
			break;

		case IDM_PLAYENTER:
			SendMessage(hWnd,WM_STARTPLAY,cPlayListView->GetFocusedItemNo(),0);
			break;
		case IDM_ADDFILECURRENTPLAYLIST:
			OnAddFileInCurrentPlayList(hWnd);
			break;
		
		case IDM_DELETEFILECURRENTPLAYLIST:
			count=cPlayListView->GetFocusedItemNo();
			song=cMp3Player->GetSongByNumberFromPlayList(count,&status);
			if(status==FALSE)
				break;
			if(count<cPlayListView->GetPlayItemNo())
				cPlayListView->SetPlayItemNo(cPlayListView->GetPlayItemNo()-1);
			strng=song.GetFilePath();
			if(strng==cMp3Player->GetOpenedFileName()&&cMp3Player->IsOpened())
			{
				cMp3Player->Close();
				cPlayListView->SetPlayItemNo(-1);
			}
			cMp3Player->DeleteSongFromPlayList(count);
			SendMessage(hWnd,WM_REFRESHPLAYLIST,0,0);
			break;
		case IDM_ABOUT:
			DialogBox(GetModuleHandle(NULL), (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)AboutProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_PLAY:
			if(cMp3Player->IsStopped())
			{
				cButtonPlay->SetButtonLabel("Pause");
				cButtonStop->Enable_CheckButton(TRUE);
				cMp3Player->Play();
				
			}
			else if(cMp3Player->IsPaused())
			{
				cButtonPlay->SetButtonLabel("Pause");
				cMp3Player->Pause();
			}
			else
			{
				cButtonPlay->SetButtonLabel("Play");
				cMp3Player->Pause();
			}

			break;
		case ID_STOP:
			cMp3Player->Stop();
			cButtonStop->Enable_CheckButton(FALSE);
			cButtonPlay->SetButtonLabel("Play");
			break;
		case ID_NEXT:
			SendMessage(hWnd,WM_STARTPLAY,cPlayListView->GetPlayItemNo()+1,(LPARAM)((string)song.GetFilePath()).c_str());
			break;
		case ID_PREV:
			SendMessage(hWnd,WM_STARTPLAY,cPlayListView->GetPlayItemNo()-1,(LPARAM)((string)song.GetFilePath()).c_str());
			break;
		case ID_MUTE:
			if(cButtonMute->IsButtonChecked_Enabled())
				cMp3Player->MuteAll(VALUESET);
			else
				cMp3Player->MuteAll(VALUESET);
			break;
	
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		count=cMp3Player->CurrentPosition();
		if(count==cMp3Player->AudioLength())
		{
			SendMessage(hWnd,WM_COMMAND,ID_NEXT,0);
			break;
		}
		cSliderProgress->SetSliderPos(count/1000);
		break;
	case WM_HSCROLL:
		{
			switch(GetWindowLong((HWND) lParam,GWL_ID))
			{
			case IDC_PROGRESSSLIDER:
				cMp3Player->Seek(1000*cSliderProgress->GetSliderPos());
				break;
			case IDC_VOLUMESLIDER:
				cMp3Player->VolumeAll(1000*cSliderVolume->GetSliderPos()/cSliderVolume->GetSliderMaxRange(),VALUESET);
				break;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


// Mesage handler for about box.

//hWnd - This is the handle of the window.
//Message  - Message which should have to processed.
//wParam  - Extra data about message which are message dependent.
//lParam - Extra data about message which are message dependent.

LRESULT CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == ID_OK) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


// Mesage handler for set ratings.

//hWnd - This is the handle of the window.
//Message  - Message which should have to processed.
//wParam  - Extra data about message which are message dependent.
//lParam - Extra data about message which are message dependent.

LRESULT CALLBACK SetRatingProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case WM_INITDIALOG:
			if(strlen(sendsong)>0)
			{
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_ADDSTRING,0,(LPARAM)"Unknown");
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_ADDSTRING,1,(LPARAM)"*");
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_ADDSTRING,2,(LPARAM)"**");
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_ADDSTRING,3,(LPARAM)"***");
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_ADDSTRING,4,(LPARAM)"****");
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_ADDSTRING,5,(LPARAM)"*****");
				Song song;
				song.OpenSong(sendsong);
				SetWindowText(hDlg,((string)song.GetTitle()).c_str());
				SetDlgItemText(hDlg,IDC_STATICFILENAME,((string)song.GetFilePath()).c_str());
				SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_SETCURSEL,0,0);
			}
			return TRUE;
		case WM_CLOSE:
			EndDialog(hDlg,-1);
			return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == ID_OK) 
			{   
				int index=SendDlgItemMessage(hDlg,IDC_COMBORATINGS,CB_GETCURSEL,0,0);
				
				EndDialog(hDlg, index);
				return TRUE;
			}
			else if(LOWORD(wParam) == ID_CANCEL)
			{
				EndDialog(hDlg,-1);
				return TRUE;
			}
			break;
	}
    return FALSE;
}


void ShowLibraryForPlayList(ListView *cLibraryListView,MP3Player *cMp3Player)
{
	cLibraryListView->DeleteAllItem();
	cLibraryListView->DeleteAllColumn();
	cLibraryListView->AddColumn(0,100,"PlayList Name");
	cLibraryListView->AddColumn(1,400,"Path");
	PlayList plst;
	int countplaylist=0;
	bool status;
	char str[MAX_SONGLENGTH];
	while(1)
	{
		plst=cMp3Player->GetPlaylistByNumberFromLibrary(countplaylist++,&status);
		if(status==FALSE)
			break;
		GetFileTitle(((string)plst.GetPlayListName()).c_str(),str,MAX_SONGLENGTH);
		cLibraryListView->InsertItem(countplaylist-1,str);
		cLibraryListView->InsertSubItem(countplaylist-1,1,plst.GetPlayListName());
	}
}


void ShowLibraryForLibrary(ListView *cLibraryListView,MP3Player *cMp3Player)
{
	cLibraryListView->DeleteAllItem();
	cLibraryListView->DeleteAllColumn();
	cLibraryListView->AddColumn(0,100,"Sort By");
	cLibraryListView->InsertItem(0,"Albums");
	cLibraryListView->InsertItem(1,"Artists");
	cLibraryListView->InsertItem(2,"Ratings");
}

void ShowLibraryForPlayListItem(ListView *cLibraryListView,MP3Player *cMp3Player,int num)
{
	cLibraryListView->DeleteAllItem();
	cLibraryListView->DeleteAllColumn();
	cLibraryListView->AddColumn(0,200,"Song Title");
	cLibraryListView->AddColumn(1,150,"Path");
	cLibraryListView->AddColumn(2,80,"Artist");
	cLibraryListView->AddColumn(3,80,"Album");
	cLibraryListView->AddColumn(4,40,"Year");
	cLibraryListView->AddColumn(5,50,"Length");
	PlayList plst;
	int countsong=0;
	bool status;
	char str[MAX_SONGLENGTH];
	plst=cMp3Player->GetPlaylistByNumberFromLibrary(num,&status);
	if(status==FALSE)
		return;
	Song song;
	while(1)
	{
		int temp;
		song=plst.GetSongByNumberFromPlayList(countsong++,&status);
		if(status==FALSE)
			break;
		cLibraryListView->InsertItem(countsong-1,song.GetTitle());
		
		cLibraryListView->InsertSubItem(countsong-1,1,song.GetFilePath());
		cLibraryListView->InsertSubItem(countsong-1,2,song.GetArtist());
		cLibraryListView->InsertSubItem(countsong-1,3,song.GetAlbumName());
		itoa(song.GetYear(),str,10);
		cLibraryListView->InsertSubItem(countsong-1,4,str);
		temp=song.GetSongLengthinSecond();
		if(temp>=0)
			sprintf(str,"%d:%0.2d:%0.2d",temp/3600,temp/60,temp%60);
		else
			sprintf(str,"");
		cLibraryListView->InsertSubItem(countsong-1,5,str);
		
	}
}

void ShowLibraryForLibraryItem(ListView *cLibraryListView,TreeView *cLibTree,HTREEITEM hitem)
{
	HTREEITEM htemp;
	char str[100];
	int j=0;
	long type=HIWORD(cLibTree->GetItemLparamTreeView(hitem));
	if(type&TREE_ALBUM)
	{
		cLibraryListView->DeleteAllItem();
		cLibraryListView->DeleteAllColumn();
		cLibraryListView->AddColumn(0,100,"Album Name");
		
	}
	
	if(type&TREE_ARTIST)
	{
		cLibraryListView->DeleteAllItem();
		cLibraryListView->DeleteAllColumn();
		cLibraryListView->AddColumn(0,100,"Artist Name");
		
	}
	if(type&TREE_RATING)
	{
		cLibraryListView->DeleteAllItem();
		cLibraryListView->DeleteAllColumn();
		cLibraryListView->AddColumn(0,100,"Ratings");
		
	}
	htemp=cLibTree->GetFirstChildTreeView(hitem);
	if(htemp==NULL)
			return;
	cLibTree->GetItemTextTreeView(htemp,str,100);
	cLibraryListView->InsertItem(j++,str);
	while(1)
	{
		htemp=cLibTree->GetNextsiblingTreeView(htemp);
		if(htemp==NULL)
			break;
		cLibTree->GetItemTextTreeView(htemp,str,100);
		cLibraryListView->InsertItem(j++,str);
	}
}

void ShowLibraryForLibraryItemsong(ListView *cLibraryListView,MP3Player *cMp3Player,int type,char name[])
{
	cLibraryListView->DeleteAllItem();
	cLibraryListView->DeleteAllColumn();
	cLibraryListView->AddColumn(0,200,"Song Title");
	cLibraryListView->AddColumn(1,150,"Path");
	cLibraryListView->AddColumn(2,80,"Artist");
	cLibraryListView->AddColumn(3,80,"Album");
	cLibraryListView->AddColumn(4,40,"Year");
	cLibraryListView->AddColumn(5,60,"ratings");
	cLibraryListView->AddColumn(6,50,"Length");
	int countsong=0,countlist=0;
	bool status;
	char str[MAX_SONGLENGTH];
	Song song;
	while(1)
	{
		int temp;
		song=cMp3Player->GetSongByNumberFromLibrary(countsong++,&status);
		if(status==FALSE)
			break;
		switch(song.GetRating())
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
		if(type&TREE_ALBUM)
		{
			if(((string)song.GetAlbumName()).compare(name))
				continue;
		}
		
		if(type&TREE_ARTIST)
		{
			if(((string)song.GetArtist()).compare(name))
				continue;
			
		}
		if(type&TREE_RATING)
		{
			if(strcmp(str,name))
				continue;
			
		}
	
		
		cLibraryListView->InsertItem(countlist,song.GetTitle());
		
		cLibraryListView->InsertSubItem(countlist,1,song.GetFilePath());
		cLibraryListView->InsertSubItem(countlist,2,song.GetArtist());
		cLibraryListView->InsertSubItem(countlist,3,song.GetAlbumName());

		cLibraryListView->InsertSubItem(countlist,5,str);

		itoa(song.GetYear(),str,10);
		cLibraryListView->InsertSubItem(countlist,4,str);
		temp=song.GetSongLengthinSecond();
		if(temp>=0)
			sprintf(str,"%d:%0.2d:%0.2d",temp/3600,temp/60,temp%60);
		else
			sprintf(str,"");
		cLibraryListView->InsertSubItem(countlist,6,str);
		countlist++;
	}
}