// dxtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Debug->Log(L"Hack Initiated.");
	while (true)
	{
		Overlay->RefreshOverlay();
	}
	return 0;
}

