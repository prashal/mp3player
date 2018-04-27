//
//song.h : This file declare the class "Song" and its data member and function
//
//

#include <string>


using namespace std;
#ifndef _SONG_CLASS
#define _SONG_CLASS

char *StrRTrim(char *lpstrString);

const float iVerTable[4] = 
	{
		2.5, 0.0, 2.0, 1.0
	};

const int iBitRateTable[2][3][16] = 
	{
		{         //MPEG 2 & 2.5
			{0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer III
			{0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer II
			{0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256,0}  //Layer I
		},
		{       //MPEG 1
			{0, 32, 40, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,0}, //Layer III
			{0, 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384,0}, //Layer II
			{0, 32, 64, 96,128,160,192,224,256,288,320,352,384,416,448,0}  //Layer I
		}
	};

class Song
{
	string SongTitle;
	string SongPath;
	string ArtistName;
	string AlbumName;
	int Rating,Year,songlengthinsecond;
public:
	Song(void);
	void OpenSong(string);
	void OpenSong(string,int);
	
	string GetTitle(void);
	string GetFilePath(void);
	int GetYear(void);
	int GetSongLengthinSecond(void);
	void SetSongLengthinSecond(int);
	int GetRating(void);
	void SetRating(int);

	string GetArtist(void);
	string GetAlbumName(void);
	
};
#endif
