//
//mp3player.h : This file declare the class "MP3Player" and its data member and function
//
//

#include <string>
#include "song.h"
#include "library.h"
#include "playlist.h"


using namespace std;

extern string ApplicationDirectory;

#ifndef _MP3PLAYER_CLASS
#define _MP3PLAYER_CLASS

class MP3Player:public Library,public PlayList
{
private:
	string Pcommand,FName;
    bool Opened, Playing, Paused,Stopped, MutedAll;
    int aVolume;
	RepeatSong Loop;
    unsigned long FileLength;
    int Err;
	void CalculateLength(void);
public:
	MP3Player();
	~MP3Player();
	//For controlling volume
	bool MuteAll(bool);
	int  VolumeAll(int,bool);
	
	//Get getting current opened file name
	string GetOpenedFileName(void);
	
	//To get repeat song status
	int Looping(RepeatSong ,bool);

	//For seeking file 
	void Seek(unsigned long);

	//For getting length of opened song
	unsigned long AudioLength(void);
	
	//For closing current opened song
	void Close(void);

	//To open file
	void Open(string sFileName);
	bool IsOpened(void);

	//To play File
	void Play(void);
	void PlayInitialise(void);
	bool IsPlaying(void);
	//To pause & resume File
	void Pause(void);	
	bool IsPaused(void);

	//To stop playing file
	void Stop(void);
	bool IsStopped(void);

	//For getting current playing position
	unsigned long CurrentPosition(void);
	int GetLastErrorCode(void);
	
};
#endif