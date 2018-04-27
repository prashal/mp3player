//
//library.h : This file declare the class "Library" and its data member and function
//
//

#include <list>
#include <string>

#include "stdafx.h"
#include "song.h"
#include "playlist.h"

using namespace std;

extern string ApplicationDirectory;

#ifndef _LIBRARY_CLASS
#define _LIBRARY_CLASS


class Library
{
	list<Song> LibraryFiles;
	list<PlayList> LibraryPlaylists;
public:
	Library();
	~Library();

	void ReloadLibrary(void);
	void SaveLibrary(void);
	void SaveListOfPlayList(void);
	void SaveListOfSong(void);

	PlayList GetPlaylistByNumberFromLibrary(int,bool*);
	Song GetSongByNumberFromLibrary(int,bool* );
	
	void AddSongInLibrary(Song,int);
	Song AddSongInLibrary(char *,int);
	void ModifySongInLibrary(Song song,int num);

	PlayList AddPlayListInLibrary(string playlistname);
	
	void DeleteSongFromLibrary(int);
	void DeleteSongFromLibrary(string);

	void DeletePlayListFromLibrary(int);
	void DeletePlayListFromLibrary(string);
};

#endif 