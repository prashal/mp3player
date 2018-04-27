//
//error.cpp : This file handle with error codes
//
//

#include "stdafx.h"
#include "error.h"

//This function take errorcode and returns the mci error string corresponds to the code.

//errorcode - The error code whose mci error string has to get.

//error - The string where the mci error string will be stored

string GetErrorString(int errorcode)
{
	string error;
	char str[260];
	mciGetErrorString(errorcode,str,260);
	error=str;
	return error;
}