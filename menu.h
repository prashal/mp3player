//
//menu.h : This file contains the declaration of the prototype of functions which are called at menu event in main window
//
//

#include <string>
#include "mp3player.h"

void		OnFileOpen(HWND hParent);

void		OnUrlFileOpen(HWND hParent);

void		OnPlayListOpen(HWND hParent);

int			OnCurrentPlayListSaveAs(HWND hParent);

void OnAddFileInCurrentPlayList(HWND hParent);

int			OnAddFileLibrary(HWND hParent);

void		OnAddPlaylistLibrary(HWND hParent);
