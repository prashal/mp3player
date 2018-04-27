//
//slider.h : This file declare the class "Slider" and its data member and function
//
//

#include <windows.h>
#include <string>

using namespace std;

#ifndef _SLIDER_CLASS
#define _SLIDER_CLASS

#define VERTICAL	0
#define HORIZONTAL	1

class Slider
{
	HWND hWnd;
	HWND hParent;
	DWORD WindowId;
	int Style;
public:

	void Create(HWND hParent,int WINDOW_ID,int x,int y,int cx,int cy,int style);
	unsigned long GetSliderPos(void);
	unsigned long GetSliderMaxRange(void);
	HWND GetWindowHandle(void);

	void SetSliderPos(unsigned long);
	void SetSliderRange(unsigned long min,unsigned long max);
	void SetSliderFreq(unsigned long freq);
	void SetSliderPageSize(unsigned long pagesize);
	
	void ResizeSlider(int x,int y,int cx,int cy);
	void ShowSlider(bool enable);
};
#endif