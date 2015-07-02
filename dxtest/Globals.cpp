
#include "stdafx.h"

GlobalsT* Globals = new GlobalsT();

GlobalsT::GlobalsT()
{
	OverlaySettings.Name = L"PP-Overlay 0.0.1";
	OverlaySettings.RefreshRate = 10;
	OverlaySettings.ReferenceWindowName = L"Counter-Strike: Global Offensive";
	DebugSettings.DrawTextOutline = true;
	DebugSettings.EnableDebugLog = true;
	DebugSettings.TextColor = D3DCOLOR_RGBA(0, 255, 0, 255);
	DebugSettings.TextOutlineColor = D3DCOLOR_RGBA(0, 0, 0, 255);
	DebugSettings.MaxLines = 40;
}