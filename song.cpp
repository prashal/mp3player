//
//song.cpp : This file defines the data members of class "Song"
//
//

#include "stdafx.h"
#include "song.h"

#define EXTRACT_BITS_RL(the_val, bits_start, bits_len) ((the_val >> (bits_start - 1)) & ((1 << bits_len) - 1))


// Constractor

Song::Song(void)
{
}


//Open song by specifing path.

//MP3File - The path of the song to be opened

void Song::OpenSong(string MP3File)
{
	OpenSong(MP3File,0);
}


//Open song by specifing path and rating.

//MP3File - The path of the song to be opened.
//rat - The rating of the song.

void Song::OpenSong(string MP3File,int rat)
{
	HFILE hMP3File;
	char szBuffer[MAX_SONGLENGTH];
	DWORD dwNumofBytes;				
	
	hMP3File = (HFILE)CreateFile(MP3File.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	SetFilePointer((void *)hMP3File, 0, 0, FILE_BEGIN);
	ReadFile((void *)hMP3File, &szBuffer, 4, &dwNumofBytes, NULL);
	
	DWORD dwMP3Info = (DWORD)(	((szBuffer[0] & 255) << 24) |	
								((szBuffer[1] & 255) << 16) |
								((szBuffer[2] & 255) << 8 ) |
								((szBuffer[3] & 255)      )
							 );
	int iVersionIndex			= EXTRACT_BITS_RL(dwMP3Info, 20, 2);
	int iLayerIndex				= EXTRACT_BITS_RL(dwMP3Info, 18, 2);
	
	int iBitrateIndex			= EXTRACT_BITS_RL(dwMP3Info, 13, 4);
	
	//File path
	SongPath=MP3File;
						
	
	//KBPS
	sprintf(szBuffer, "%d Kbit", iBitRateTable[iVersionIndex & 1][iLayerIndex - 1][iBitrateIndex]);
    //SetWindowText(Handles_Ctl_Static_KBit_T, szBuffer);

	SetFilePointer((void *)hMP3File, -128, 0, FILE_END);
	ReadFile((void *)hMP3File, szBuffer, 3, &dwNumofBytes, NULL);
	szBuffer[3] = '\0';
	
	if(!(strcmp(szBuffer, "TAG")))
	{
		//Get Title
		ReadFile((void *)hMP3File, szBuffer, 30, &dwNumofBytes, NULL);
		szBuffer[30] = '\0';
		StrRTrim(szBuffer);	
		if(szBuffer[0]==0)
		{
			GetFileTitle(MP3File.c_str(),szBuffer,MAX_SONGLENGTH);
			SongTitle.assign(szBuffer);
		}
		else
			SongTitle.assign(szBuffer);
			
		//Get Artist
		ReadFile((void *)hMP3File, szBuffer, 30, &dwNumofBytes, NULL);
		szBuffer[30] = '\0';
		StrRTrim(szBuffer);
		if(szBuffer[0]==0)
			ArtistName.assign("Unknown");
		else
			ArtistName.assign(szBuffer);

		//Get Album
		ReadFile((void *)hMP3File, szBuffer, 30, &dwNumofBytes, NULL);
		szBuffer[30] = '\0';
		StrRTrim(szBuffer);
		if(szBuffer[0]==0)
			AlbumName.assign("Unknown");
		else
			AlbumName.assign(szBuffer);

		//Get Year
		ReadFile((void *)hMP3File, szBuffer, 4, &dwNumofBytes, NULL);
		szBuffer[4] = '\0';
		StrRTrim(szBuffer);
		Year=atoi(szBuffer);

		//Set Rating
		Rating=rat;


	}
	else
	{
		GetFileTitle(MP3File.c_str(),szBuffer,MAX_SONGLENGTH);
		SongTitle.assign(szBuffer);
		ArtistName.assign("Unknown");
		AlbumName.assign("Unknown");
		Year=2000;
		Rating=rat;
	}
	songlengthinsecond=-1;
	CloseHandle((void *)hMP3File);
}

//Get the title of the song.
//SongTitle - title of the song.
string Song::GetTitle(void)
{
	return SongTitle;
}

//Get the year of song 
int Song::GetYear(void)
{
	return Year;
}


//Get the path of the song.
string Song::GetFilePath(void)
{
	return SongPath;
}

//Get rating of a song
int Song::GetRating(void)
{
	return Rating;
}

//Set rating of a song
void Song::SetRating(int rat)
{
	Rating=rat;
}

string Song::GetArtist(void)
{
	return ArtistName;
}


//Get album name of song

string Song::GetAlbumName(void)
{
	return AlbumName;
}

//This function is used to get song length in milisecond.
int Song::GetSongLengthinSecond(void)
{
	return songlengthinsecond;
}

//This function is used to set song length in milisecond.
void Song::SetSongLengthinSecond(int time)
{
	songlengthinsecond=time;
}

char *StrRTrim(char *lpstrString)
{
    int I = strlen(lpstrString); 

		while ((--I)>0 && isspace(lpstrString[I])) 
			{
				lpstrString[I] = '\0';
			}

    return(lpstrString);
}