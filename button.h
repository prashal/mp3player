//
//button.h : This file declare the class "Button" and its data member and function
//
//


#include <windows.h>
#include <string>

using namespace std;

#ifndef _BUTTON_CLASS
#define _BUTTON_CLASS

#define CHECKBUTTON		0
#define PUSHBUTTON		1
class Button
{
	HWND hWnd;
	HWND hParent;
	DWORD WindowId;
	int buttonstyle;
public:

	void Create(HWND hParent,string label,int WINDOW_ID,int x,int y,int cx,int cy,int style);
	void SetButtonLabel(string label);
	void Enable_CheckButton(bool enable);
	void ResizeMoveButton(int x,int y,int cx,int cy);
	int IsButtonChecked_Enabled(void);
	HWND GetWindowHandle(void);

	void ShowButton(bool enable);
};
#endif