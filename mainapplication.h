//
//mainapplication.h : This file declare the class "MainApplication" and its data member and function
//
//

#include <string>
#include <windows.h>
#include "song.h"
#include "library.h"
#include "playlist.h"
#include "button.h"
#include "slider.h"
#include "listview.h"
#include "treeview.h"

using namespace std;

extern string ApplicationDirectory;

#ifndef _MAINAPPLICATION_CLASS
#define _MAINAPPLICATION_CLASS

class MainApplication
{
private:	
	Button *cButtonPlay,*cButtonStop,*cButtonPrev,*cButtonNext,*cButtonMute;
	Slider *cSliderProgress,*cSliderVolume;
	ListView *cPlayListView,*cLibraryListView;	
	TreeView *cLibraryTree;
	MP3Player *cMp3Player;
	HWND hWnd;
public:
	void InitApplication();
	MainApplication();
	~MainApplication();
	int SendApplicationMessage(HWND,unsigned int , WPARAM , LPARAM);
	
};
#endif