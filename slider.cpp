//
//slider.cpp : This file defines the data members of class "Slider" which handle with slider control
//
//

#include "stdafx.h"
#include "slider.h"


//This function create a new slider window

//hParent - The handle of parent window.
//winid - The Id of tree view item.
//x - x-coordinate of top-left corner.
//y - y- coordinate of top-left corner.
//cx - width.
//cy - height;

void Slider::Create(HWND hPrnt,int WINDOW_ID,int x,int y,int cx,int cy,int style)
{
	DWORD Sliderstyle=WS_CHILD | WS_VISIBLE|TBS_AUTOTICKS;
	WindowId=WINDOW_ID;
	Style=style;
	hParent=hPrnt;

	if(Style==VERTICAL)
		Sliderstyle=Sliderstyle|TBS_VERT;
	else
		Sliderstyle=Sliderstyle|TBS_HORZ;
	
	hWnd=CreateWindow(TRACKBAR_CLASS,"slider",Sliderstyle, x,y,cx,cy,hParent ,(HMENU)WINDOW_ID,GetModuleHandle(NULL),NULL);
		
}

//Get slider's current logical position          
unsigned long Slider::GetSliderPos(void)
{
	return SendMessage(hWnd, TBM_GETPOS, FALSE, 0);
}

//Get slider's Maximum range         
unsigned long Slider::GetSliderMaxRange(void)
{
	return SendMessage(hWnd,TBM_GETRANGEMAX,0,0);
}

//Get slider window handle 
HWND Slider::GetWindowHandle(void)
{
	return hWnd;
}

//Get slider's current logical position          
void Slider::SetSliderPos(unsigned long pos)
{
	SendMessage(hWnd, TBM_SETPOS, TRUE, pos);
}


//Set slider's range 
 
//min - Value when slider logical position at beginning .  
//max - Value when slider logical position at end.  

void Slider::SetSliderRange(unsigned long min,unsigned long max)
{
	SendMessage(hWnd, TBM_SETRANGE,  TRUE,  MAKELONG(min, max)); 
}


//Set slider Tic frequency

void Slider::SetSliderFreq(unsigned long freq)
{
	SendMessage(hWnd, TBM_SETTICFREQ,freq, 0); 
}

//Set slider Page size

void Slider::SetSliderPageSize(unsigned long pagesize)
{
	SendMessage(hWnd, TBM_SETPAGESIZE, 0,  pagesize); 
}

//Resize i.e. modify size and position of slider 

//x - x-coordinate of top-left corner.
//y - y- coordinate of top-left corner.
//cx - width.
//cy - height;
	
void Slider::ResizeSlider(int x,int y,int cx,int cy)
{
	SetWindowPos(hWnd,HWND_TOP,x,y,cx,cy,SWP_SHOWWINDOW);
}

//Show or Hide Slider

//enable - if this is TRUE then the tree view will be in visible condition otherwise not.
void Slider::ShowSlider(bool enable)
{
	if(enable)
		ShowWindow(hWnd,SW_SHOWNORMAL);
	else
		ShowWindow(hWnd,SW_HIDE);
}
