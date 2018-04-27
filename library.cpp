//
//library.cpp : This file defines the data members of class "Library"
//
//
#include "stdafx.h"
#include "library.h"


//The constractor of class Library.It reload the list of playlist and list song in library.
Library::Library()
{
	ReloadLibrary();
}

//The destructor of class Library.It saves the list of playlist and list song in library.
Library::~Library(void)
{
	SaveLibrary();
}

//It reload the list song in library and list of playlist from file "libraryfiles.txt" 
//and "Libraryplaylists.txt" respectively.
void Library::ReloadLibrary(void)
{
	char str[MAX_SONGLENGTH];
	sprintf(str,"%s\\libraryfiles.txt",ApplicationDirectory.c_str());
	ifstream libraryfiles(str);
	if(libraryfiles)
	{
		LibraryFiles.clear();
		Song song;
		char rat[10];
		while(!libraryfiles.eof())
		{
			libraryfiles.getline(str,MAX_SONGLENGTH);
			libraryfiles.getline(rat,MAX_SONGLENGTH);
			if(str[0]==0)
				continue;
			song.OpenSong(str,atoi(rat));
			LibraryFiles.push_back(song);
		}
		libraryfiles.close();
	}
	sprintf(str,"%s\\Libraryplaylists.txt",ApplicationDirectory.c_str());
	ifstream Libraryplaylists(str);
	if(Libraryplaylists)
	{
		LibraryPlaylists.clear();
		PlayList playlist;
		while(!Libraryplaylists.eof())
		{
			Libraryplaylists.getline(str,MAX_SONGLENGTH);
			if(str[0]==0)
				continue;
			if(playlist.OpenPlayList(str)==1)
				LibraryPlaylists.push_back(playlist);
		}
		Libraryplaylists.close();
	}
}


//It saves all the playlist name and song name in file.
void Library::SaveLibrary(void)
{
	SaveListOfPlayList();
	SaveListOfSong();
}

//It save the list of playlist in file "Libraryplaylists.txt".
void Library::SaveListOfPlayList(void)
{
	char str[MAX_SONGLENGTH];
	sprintf(str,"%s\\Libraryplaylists.txt",ApplicationDirectory.c_str());
	ofstream outfile(str);
	if(!outfile)
	{
		//error occure in open file
		return;
	}

	list<PlayList>::iterator iter;
	for(iter=LibraryPlaylists.begin();iter!=LibraryPlaylists.end();iter++)
	{
		strcpy(str,(iter->GetPlayListName()).c_str());
		outfile << str << endl;
	}
	outfile.close();
}


//It save the list of songs in file "libraryfiles.txt".
void Library::SaveListOfSong(void)
{
	char str[MAX_SONGLENGTH];
	sprintf(str,"%s\\libraryfiles.txt",ApplicationDirectory.c_str());
	ofstream outfile(str);
	if(!outfile)
	{
		//error occure in open file
		return;
	}

	list<Song>::iterator iter;
	for(iter=LibraryFiles.begin();iter!=LibraryFiles.end();iter++)
	{
		outfile << iter->GetFilePath() << endl;
		outfile << iter->GetRating() << endl;
	}
	outfile.close();
}

//This returns the playlist with given index.

//num - the index of playlist. 
//status -The reference of a bool in which success status will be stored.

//playlist - Here the playlist will be stored

PlayList Library::GetPlaylistByNumberFromLibrary(int num,bool* status)
{
	list<PlayList>::iterator iter;
	PlayList playlist;
	int countplaylist=0;
	iter=LibraryPlaylists.begin();
	*status=FALSE;
	while(iter!=LibraryPlaylists.end())
	{		
		if(countplaylist==num)
		{
			*status=TRUE;
			playlist=*iter;
			break;
		}
		iter++;
		countplaylist++;
	}
	return playlist;
}

//This returns the song with given index.

//num - the index of song. 
//status -The reference of a bool in which success status will be stored.

//song - Here the song will be stored

Song Library::GetSongByNumberFromLibrary(int num,bool* status)
{
	list<Song>::iterator iter;
	Song song;
	int countsong=0;
	iter=LibraryFiles.begin();
	*status=FALSE;
	while(iter!=LibraryFiles.end())
	{		
		if(countsong==num)
		{
			*status=TRUE;
			song=*iter;
			break;
		}
		iter++;
		countsong++;
	}
	return song;
}

//This adds the song with given song class.

//song - The song which has to add. 
//num -The index at which the song has to insert.

	
void Library::AddSongInLibrary(Song song,int num)
{
	if(num==-1)
		LibraryFiles.push_back(song);
	else
	{
		list<Song>::iterator iter;
		iter=LibraryFiles.begin();
		int countsong;
		for(countsong=0;countsong<num;countsong++)
			iter++;
		LibraryFiles.insert(iter,song);
	}
}

//This adds the song with given song path.

//songname - The path of song which has to add. 
//num -The index at which the song has to insert.

Song Library::AddSongInLibrary(char * songname,int num)
{


	Song song;

	
	if(GetFileAttributes(songname)!=FILE_ATTRIBUTE_DIRECTORY)
	{
		//If user selects one song at a time
		song.OpenSong(songname);
		AddSongInLibrary(song,num);
	}
	else
	{
		//If user selects many songs symultaneously
		char directory[MAX_SONGLENGTH],file[MAX_SONGLENGTH];
		int countchar;
		string name;
		countchar=0;
		while(1)
		{
			directory[countchar]=*songname;
			if(*songname=='\0')
				break;
			songname++;
			countchar++;
		}
		while(1)
		{
			countchar=0;
			songname++;
			if(*songname=='\0')
				break;
			while(1)
			{
				file[countchar]=*songname;
				if(*songname=='\0')
					break;
				songname++;
				countchar++;
			}
			name=directory;
			name.append("\\");
			name.append(file);
			song.OpenSong(name);
			AddSongInLibrary(song,num);
		}
	}
	return song;
}

//This modify the song with given index.

//songname - The new song. 
//num -The index of song which have to modify.

void Library::ModifySongInLibrary(Song song,int num)
{
	list<Song>::iterator iter;
	iter=LibraryFiles.begin();
	int countsong;
	for(countsong=0;countsong<num;countsong++)
		iter++;
	LibraryFiles.insert(iter,song);
	LibraryFiles.erase(iter);
}


//This adds the playlist in library with given playlist name.

//playlistname - The playlist which has to add. 

PlayList Library::AddPlayListInLibrary(string playlistname)
{
	PlayList playlist;
	playlist.OpenPlayList(playlistname);
	LibraryPlaylists.push_back(playlist);
	return playlist;
}

//This deletes the song from library with given index.

//num - The index of the song which has to delete. 

void Library::DeleteSongFromLibrary(int num)
{
	list<Song>::iterator iter;
	iter=LibraryFiles.begin();
	int countsong;
	for(countsong=0;countsong<num&&iter!=LibraryFiles.end();countsong++)
		iter++;
	LibraryFiles.erase(iter);
}

//This deletes the song from library with given song name.

//song - The name of the song which has to delete. 

void Library::DeleteSongFromLibrary(string song)
{
	list<Song>::iterator iter;
	iter=LibraryFiles.begin();
	while(iter->GetTitle()!=song&&iter!=LibraryFiles.end())
		iter++;
	LibraryFiles.erase(iter);
}

//This deletes the playlist from library with given index.

//num - The index of playlist which has to delete. 


void Library::DeletePlayListFromLibrary(int num)
{
	list<PlayList>::iterator iter;
	iter=LibraryPlaylists.begin();
	int countsong;
	for(countsong=0;countsong<num&&iter!=LibraryPlaylists.end();countsong++)
		iter++;
	LibraryPlaylists.erase(iter);
}

//This deletes the playlist from library with given playlist name.

//playlist - The name of playlist which has to delete. 

void Library::DeletePlayListFromLibrary(string playlist)
{
	list<PlayList>::iterator iter;
	iter=LibraryPlaylists.begin();
	while(iter->GetPlayListName()!=playlist&&iter!=LibraryPlaylists.end())
		iter++;
	LibraryPlaylists.erase(iter);
}