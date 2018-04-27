//
//playlist.cpp : This file defines the data members of class "PlayList"
//
//



#include "stdafx.h"
#include "playlist.h"



//Constructor of PlayList class. It initialize i.e. clear list

PlayList::PlayList(void)
{
	playlistname="";
	playlist.clear();
}

PlayList::~PlayList(void)
{
}


//Create wew playlist and initialize the playlist

void PlayList::NewPlayList(void)
{
	playlistname="";
	playlist.clear();
}


//open PlayList file from a given location    
//playlstname - Path of the file to save playlist 
int PlayList::OpenPlayList(string playlstname)
{
	ifstream infile(playlstname.c_str());
	char str[MAX_SONGLENGTH];
	if(!infile)
	{
		//error occure in open file
		return 0;
	}
	playlistname=playlstname;
	playlist.clear();
	Song song;
	while(!infile.eof())
	{
		infile.getline(str,MAX_SONGLENGTH);
		if(str[0]==0)
			continue;
		song.OpenSong(str);
		playlist.push_back(song);
	}
	infile.close();
	return 1;
}



//Save PlayList in file at given location
//savefile - Path of the file to save playlist

void PlayList::SavePlayList(string savefile)
{
	
	ofstream outfile(savefile.c_str());
	if(!outfile)
	{
		//error occure in open file
		return;
	}
	playlistname=savefile;

	list<Song>::iterator iter;
	for(iter=playlist.begin();iter!=playlist.end();iter++)
	{
		outfile << iter->GetFilePath() << endl;
	}

}

//Get song by number from PlayList

//num - The index of playlist which we want to get.
//status - After executing this function if bool pointed by status is TRUE ,then it is obvious this function is successful in getting playlist otherwise not

//Return the song class of a song which have been specified by index in library

Song PlayList::GetSongByNumberFromPlayList(int num,bool* status)
{
	list<Song>::iterator iter;
	Song song;
	int countsong=0;
	iter=playlist.begin();
	*status=FALSE;
	while(iter!=playlist.end())
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



//Add Song in Playlist by specifying song class

//song - The song class of the song which have to add in li-brary.
//num - The positon i.e. sequence of the new song

void PlayList::AddSongInPlayList(Song song,int num)
{
	if(num==-1)
		playlist.push_back(song);
	else
	{
		list<Song>::iterator iter;
		iter=playlist.begin();
		int countsong;
		for(countsong=0;countsong<num;countsong++)
			iter++;
		playlist.insert(iter,song);
	}
}



//Modify a song details by specifying it's index in PlayList

//song - New song  which we wants to place.
//num - The index of song to be modified

void PlayList::ModifySongInPlayList(Song song,int num)
{
	list<Song>::iterator iter;
	iter=playlist.begin();
	int countsong;
	for(countsong=0;countsong<num;countsong++)
		iter++;
	playlist.insert(iter,song);
	playlist.erase(iter);
	
}


//Add Song in Playlist by specifying it's path

//songname - The path of the song which have to add in playlist.
//num -The positon i.e. sequence of the new song

// Return the song class of the file which have added in play-list

Song PlayList::AddSongInPlayList(char *songname,int num)
{
	Song song;
	if(GetFileAttributes(songname)!=FILE_ATTRIBUTE_DIRECTORY)
	{
		//If user selects one song at a time
		song.OpenSong(songname);
		AddSongInPlayList(song,num);
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
			AddSongInPlayList(song,num);
		}
	}
	return song;
}

//Delete a song from PlayList specified by index

//num (in): The index of the song which have to delete

void PlayList::DeleteSongFromPlayList(int num)
{
	list<Song>::iterator iter;
	iter=playlist.begin();
	int countsong;
	for(countsong=0;countsong<num;countsong++)
		iter++;
	playlist.erase(iter);
}


//Delete a song specified by name from PlayList

//name (in): The name of the song which have to delete

void PlayList::DeleteSongFromPlayList(string song)
{
	list<Song>::iterator iter;
	iter=playlist.begin();
	while(iter->GetFilePath()!=song&&iter!=playlist.end())
		iter++;
	playlist.erase(iter);
}

//Get the name of the playlist    
//playlistname - The name of playlist
string PlayList::GetPlayListName()
{
	return playlistname;
}

//Set the name of the playlist
//name - Name of the playlist to be set
void PlayList::SetPlayListName(string name)
{
	playlistname=name;
}
