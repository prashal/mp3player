//
//mp3player.cpp : This file defines the data members of class "MP3Player"
//
//


#include "stdafx.h"
#include "mp3player.h"



//This is the constructor of MP3Player .This will used to load volume,mute condition,and
// last opened playlist name from file "setting.ini" in current directory.

MP3Player::MP3Player(void)
{
	char str[MAX_SONGLENGTH];
	sprintf(str,"%s\\setting.ini",ApplicationDirectory.c_str());
	ifstream setting(str);
	
	if(setting)
	{
		while(!setting.eof())
		{
			setting >> str ;
			if(!strcmp(str,"ALLVOLUME"))
			{
				setting >> str ;
				aVolume=atoi(str);
				continue;
			}
			else if(!strcmp(str,"MUTEALL"))
			{
				setting >> str ;
				MutedAll=atoi(str)==0?false:true;
				continue;
			}
			else if(!strcmp(str,"PLAYLIST"))
			{
				setting.get();
				setting.getline(str,MAX_SONGLENGTH);
				char s[50];
				GetFileTitle(str,s,50);
				if(str[0]==0)
					continue;
				else if(!strcmp(s,"default"))
				{
					OpenPlayList(str);
					SetPlayListName("");
				}
				else
					OpenPlayList(str);
				

				continue;
			}
		}
		setting.close();
		Opened = false;
		Pcommand = "";
		FName = "";
		Playing = false;
		Paused = false;
		Loop = REPEATNONE;
		FileLength = 0;
	}
	else
	{
		Opened = false;
		Pcommand = "";
		FName = "";
		Playing = false;
		Paused = false;
		Loop = REPEATNONE;
		MutedAll = false;
		aVolume = 1000;
		FileLength = 0;
	}
    Err = 0;
	

}

//This is the destructor of MP3Player .This will used to save volume,mute condition,and
// last opened playlist name from file "setting.ini" in current directory.

MP3Player::~MP3Player(void)
{
	char str[MAX_SONGLENGTH];
	sprintf(str,"%s\\setting.ini",ApplicationDirectory.c_str());
	ofstream setting(str);
	if(setting)
	{
		setting << "ALLVOLUME " << aVolume << endl;;
		setting << "MUTEALL " << MutedAll << endl;
		setting << "LOOP " << Loop << endl;
		if(((string)GetPlayListName()).size()>0)
			setting << "PLAYLIST " << GetPlayListName() << endl;
		else
		{
			sprintf(str,"%s\\default",ApplicationDirectory.c_str());
			SavePlayList(str);
			setting << "PLAYLIST " << str << endl;
		}
		setting.close();
	}
}



//This function Get mute condition or change mute condition.

//type - If type is equals to VALUESET then the SMP complement the mute condition and 
//return the mute condition.Otherwise, this function only returns the mute condition..

//MutedAll -  mute condition of this player.
bool MP3Player::MuteAll(bool type)
{
    if(type==VALUESET)
	{
		if(!Opened)
		{
			MutedAll = (MutedAll?FALSE:TRUE);
		}
		else
		{
			MutedAll = (MutedAll?FALSE:TRUE);
			if (MutedAll)
			{
				Pcommand = "setaudio MediaFile off";
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
			else
			{
				Pcommand = "setaudio MediaFile on";
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
		}
	}
	return MutedAll;
}

//Set or Get volume of SMP.

//Value - If type equals to VALUESET ,then this parameter is valid and value will be settled as volume of SMP.
//Type - This determines whether the value parameter is valid i.e. whether volume have to set or get. If type=VALUESET ,value will be settled as volume of SMP.

//aVolume - The volume
 
int MP3Player::VolumeAll(int value,bool type)
{
    if(type==VALUESET)
	{
		if (value >= 0 && value <= 1000)
		{
			if(!Opened)
				aVolume = value;
			else 
			{
				aVolume = value;
				char str[10];
				sprintf(str,"%d",aVolume);
				Pcommand = "setaudio MediaFile volume to ";
				Pcommand.append(str);
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
		}
    }
	return aVolume;
}


//Get current open file name.

//FName - The opened file name 

string MP3Player::GetOpenedFileName(void)
{
	return FName;
}
//Set or Get repeat condition of SMP

//loop - If type equals to VALUESET ,then this parameter is valid and.
//type - This determines whether the value parameter is va-lid. If type=VALUESET , repeat condition will be changed as new condition.

int MP3Player::Looping(RepeatSong value,bool type)
{
	if(type==VALUESET)           
		Loop = value;
	return Loop;
}


//Seek mp3 file to a specified position.

//pos (in): The new position of the mp3 file.

void MP3Player::Seek(unsigned long Millisecs)
{
	if (Opened && Millisecs <= FileLength)
	{
		if (Playing)
		{
			if (Paused)
			{
				char str[20];
				sprintf(str,"%lu",Millisecs);
				Pcommand = "seek MediaFile to ";
				Pcommand.append(str);
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
			else
			{
				char str[20];
				sprintf(str,"%lu",Millisecs);
				Pcommand = "seek MediaFile to ";
				Pcommand.append(str);
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
				Pcommand = "play MediaFile";
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
		}
	}
}

//Returns the audio length in milisecond.
        
//FileLength - Length in milisecond
unsigned long MP3Player::AudioLength(void)
{
	if (Opened) 
		return FileLength;
	else return 0;
}

//Close audio file
void MP3Player::Close(void)
{
	if (Opened)
	{
		Pcommand = "close MediaFile";
		Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		Opened = false;
		Playing = false;
		Paused = false;
	}
}



//Open specified mp3 file.
//sFileName - The path of file to be opened.

void MP3Player::Open(string sFileName)
{
	if (!Opened)
	{
		Pcommand = "open \""+ sFileName +"\" type mpegvideo alias MediaFile";
		Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		FName = sFileName;
		Opened = true;
        Playing = false;
		Paused = false;
		Pcommand = "set MediaFile time format milliseconds";
		Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		Pcommand = "set MediaFile seek exactly on";
		Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		CalculateLength();
	}
	else
	{
		this->Close();
		this->Open(sFileName);
	}
	PlayInitialise();
	
}



//It initialize the volume mute condition before start playing.

void MP3Player::PlayInitialise(void)
{
	if (Opened)
	{
	
		MutedAll = (MutedAll?FALSE:TRUE);
		MuteAll(VALUESET);

		VolumeAll(aVolume,VALUESET);
	}
}


//Start playing file.

void MP3Player::Play(void)
{
	if (Opened)
	{
		if (!Playing)
		{
			Playing = true;
			Stopped =false;
			Paused = false;
			Pcommand = "play MediaFile";
			if (Loop==REPEATONE) 
				Pcommand += " REPEAT";
			Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		}
		else
		{
			if (!Paused)
			{
				Playing = true;
				Stopped =false;
				Paused = false;
				Pcommand = "seek MediaFile to start";
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
				Pcommand = "play MediaFile";
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
			else
			{
				Playing = true;
				Stopped =false;
				Paused = false;
				Pcommand = "play MediaFile";
				Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
			}
		}
	}
}


//Get opened status of SMP

bool MP3Player::IsOpened(void)
{
	return Opened;
}

//Get playing status of SMP.

bool MP3Player::IsPlaying(void)
{
	return Playing;
}

//Get stopped status of SMP.

bool MP3Player::IsStopped(void)
{
	return Stopped;
}

//Get pause status of SMP.

bool MP3Player::IsPaused(void)
{
	return Paused;
}

//Pause or resume playing. If the SMP is in playing state then after calling this function the SMP will be paused.
//And if the SMP is in pause state then after calling this function the SMP will resume playing.
void MP3Player::Pause(void)
{
	if (Opened)
	{
		if (!Paused)
		{
			Paused = true;
			Pcommand = "pause MediaFile";
			mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		}
		else
		{
			Paused = false;
			Playing = true;
			Pcommand = "resume MediaFile";
			mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		}
	}
}


//Stop playing

void MP3Player::Stop(void)
{
	if (Opened && Playing)
	{
		Playing = false;
		Paused = false;
		Stopped=true;
		Pcommand = "seek MediaFile to start";
		Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
		Pcommand = "stop MediaFile";
		Err=mciSendString(Pcommand.c_str(), NULL, 0, (HWND)0);
	}
}


//Get current position of playing song .
//Returns the current position of playing song
unsigned long MP3Player::CurrentPosition(void)
{
	if (Opened && Playing)
	{
		char s[130];
		Pcommand = "status MediaFile position";
		Err=mciSendString(Pcommand.c_str(),s, 128, (HWND)0);
		return atol(s);
	}
	else 
		return 0;
}

//Calculate the length of mp3 file and store in FileLength
void MP3Player::CalculateLength(void)
{
	char s[130];
	Err=mciSendString("status MediaFile length",s, 128, (HWND)0);
	FileLength = atol(s);
}

// Get error code 
int MP3Player::GetLastErrorCode(void)
{
	return Err;
}
