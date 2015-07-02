
#pragma once
#include "stdafx.h"

struct DirectXT
{
	IDirect3D9Ex* DX;
	IDirect3DDevice9Ex* DXDevice;
	D3DPRESENT_PARAMETERS DXParams;
	ID3DXLine* DXLine;
	ID3DXFont* DXFont;
	void DrawRect(int X, int Y, int Width, int Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawLine(int X, int Y, int XX, int YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
	void DrawCross(int X, int Y, int Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, int OutlineWidth, D3DCOLOR OutlineColor);
	void DrawString(int X, int Y, std::wstring Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor);
	bool SetupDirectX(HWND Handle, int Width, int Height);
	bool Valid();
	void Render();
};

extern DirectXT* DirectX;