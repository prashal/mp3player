//
//button.cpp : This file defines the data members of class "Button"
//
//



#include "stdafx.h"
#include "button.h"

//This function will be used to create a new push button or check buton 
//with given parent handle, window id,label and style.

//hParent:The handle of parent window.
//winid:The Id of tree view item.
//x : x-coordinate of top-left corner.
//y : y- coordinate of top-left corner.
//cx: width.
//cy :height;

void Button::Create(HWND hPrnt,string label,int WINDOW_ID,int x,int y,int cx,int cy,int style)
{
	DWORD winstyle=WS_CHILD | WS_VISIBLE;
	if(style==CHECKBUTTON)
		winstyle=winstyle|BS_AUTOCHECKBOX;
	hParent=hPrnt;
	WindowId=WINDOW_ID;
	buttonstyle=style;
	hWnd=CreateWindow("BUTTON",label.c_str(), winstyle , x,y ,cx,cy,hParent,(HMENU)WINDOW_ID,GetModuleHandle(NULL),NULL);
}

//Set the button enable/disable (For push but-ton),check/uncheck (For check button)  status.

//enable (in): For push button, if it equals to TRUE, the button will be enabled otherwise disabled. 
//For check button, if it equals to TRUE ,the button will be checked, otherwise un-checked.

void Button::Enable_CheckButton(bool enable)
{
	if(buttonstyle==CHECKBUTTON)
		CheckDlgButton(hParent,WindowId,enable);
	else
		EnableWindow(hWnd,enable);
}


//Resize or move button.

//x : x-coordinate of top-left corner.
//y : y- coordinate of top-left corner.
//cx : width.
//cy :height.

void Button::ResizeMoveButton(int x,int y,int cx,int cy)
{
	SetWindowPos(hWnd,HWND_TOP,x,y,cx,cy,SWP_SHOWWINDOW);
}

//Get the button enable/disable (For push but-ton),check/uncheck (For check button)  status.

int Button::IsButtonChecked_Enabled(void)
{
	if(buttonstyle==CHECKBUTTON)
		return(IsDlgButtonChecked(hParent,WindowId));
	else
		return(IsWindowEnabled(hWnd));
}

//Get button window handle 

//hWnd - The handle of the button

HWND Button::GetWindowHandle(void)
{
	return hWnd;
}

//Show or Hide button.

//enable - if this is TRUE then the tree view will be in visible condition otherwise not.
void Button::ShowButton(bool enable)
{
	if(enable)
		ShowWindow(hWnd,SW_SHOWNORMAL);
	else
		ShowWindow(hWnd,SW_HIDE);
}

//Change or set button label.

//label - The string which will be the new label of this button.

void Button::SetButtonLabel(string label)
{
	SetWindowText(hWnd,label.c_str());
}
