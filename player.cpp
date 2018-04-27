//
// player.cpp : Defines the entry point for the application. 
// This file contains the The WinMain function from where execution will start
//


#include "stdafx.h"
#include "resource.h"
#include "mainapplication.h"



// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

MainApplication *cMainApplication;
string ApplicationDirectory;


//Win main start here.

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//Execution will start from here
	MSG msg;
	HACCEL hAccelTable;
    InitCommonControls();
	MyRegisterClass(hInstance);
	char *str;
	str=(char*)malloc(MAX_SONGLENGTH*sizeof(char));
	GetCurrentDirectory(MAX_SONGLENGTH,str);
	ApplicationDirectory=str;
	free(str);
	cMainApplication=new MainApplication;
	cMainApplication->InitApplication();
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PLAYER);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	delete cMainApplication;
	return msg.wParam;
}



// Registers the window class.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PLAYER);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(16);
	wcex.lpszMenuName	= (LPCSTR)IDC_PLAYER;
	wcex.lpszClassName	= "PlayerClass";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)0);

	return RegisterClassEx(&wcex);
}

//  Saves instance handle and creates main window

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
 // Store instance handle in our global variable

	hWnd = CreateWindow("PlayerClass", "Simple MP3 Player ...", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, 700, 500, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

//Processes messages for the main window.

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 	cMainApplication->SendApplicationMessage(hWnd,message,wParam,lParam);
}
