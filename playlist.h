//
//playlist.h : This file declare the class "PlayList" and its data member and function
//
//

#include "stdafx.h"
#include "song.h"

#ifndef _PLAYLIST_CLASS
#define _PLAYLIST_CLASS

using namespace std;


class PlayList
{
	string playlistname;
	list<Song> playlist;
public:
	PlayList(void);
	~PlayList(void);
	void NewPlayList(void);
	int OpenPlayList(string);

	void SavePlayList(string);
	Song GetSongByNumberFromPlayList(int,bool*);

	void AddSongInPlayList(Song,int);
	Song AddSongInPlayList(char *,int);
	void ModifySongInPlayList(Song song,int num);

	void DeleteSongFromPlayList(int);
	void DeleteSongFromPlayList(string);
	string GetPlayListName();
	void SetPlayListName(string name);
};

#endif