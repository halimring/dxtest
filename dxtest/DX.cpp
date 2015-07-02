
#include "stdafx.h"

DirectXT* DirectX = new DirectXT();

bool DirectXT::Valid()
{
	if (DXDevice->TestCooperativeLevel() == D3D_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DirectXT::DrawLine(int X, int Y, int XX, int YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[2];
	Points[0] = D3DXVECTOR2(X, Y);
	Points[1] = D3DXVECTOR2(XX, YY);
	if (Outlined)
	{
		DXLine->SetWidth(OutlineWidth * 2 + LineWidth);
		DXLine->Draw(Points, 2, OutlineColor);
	}
	DXLine->SetWidth(LineWidth);
	DXLine->Draw(Points, 2, LineColor);
}

void DirectXT::DrawString(int X, int Y, std::wstring Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor)
{
	RECT Rect;
	Rect.top = Y;
	Rect.left = X;
	if (Outlined)
	{
		RECT OutlineRectTop;
		OutlineRectTop.top = Y - 1;
		OutlineRectTop.left = X;
		RECT OutlineRectLeft;
		OutlineRectLeft.top = Y;
		OutlineRectLeft.left = X - 1;
		RECT OutlineRectRight;
		OutlineRectRight.top = Y;
		OutlineRectRight.left = X + 1;
		RECT OutlineRectBottom;
		OutlineRectBottom.top = Y + 1;
		OutlineRectBottom.left = X;
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectTop, DT_NOCLIP, OutlineColor);
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectLeft, DT_NOCLIP, OutlineColor);
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectRight, DT_NOCLIP, OutlineColor);
		DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &OutlineRectBottom, DT_NOCLIP, OutlineColor);
	}
	DXFont->DrawTextW(NULL, Text.c_str(), wcslen(Text.c_str()), &Rect, DT_NOCLIP, TextColor);
}

void DirectXT::DrawRect(int X, int Y, int Width, int Height, float LineWidth, D3DCOLOR LineColor, bool Outlined, bool Filled, float OutlineWidth, D3DCOLOR OutlineColor)
{
	
	if (Filled)
	{
		if (Outlined)
		{
			DrawLine(X - OutlineWidth, Y + Height / 2, X + Width + OutlineWidth, Y + Height / 2, Height, OutlineColor, true, OutlineWidth, OutlineColor);
		}
		DrawLine(X, Y + Height / 2, X + Width, Y + Height / 2, Height, LineColor, false, 0, 0);
	}
	else
	{
		
		if (Outlined)
		{
			DrawLine(X, Y, X, Y + Height, LineWidth, LineColor, true, OutlineWidth, OutlineColor);
			DrawLine(X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, true, OutlineWidth, OutlineColor);
			DrawLine(X + Width, Y + Height, X + Width, Y,  LineWidth, LineColor, true, OutlineWidth, OutlineColor);
			DrawLine(X + Width, Y, X, Y, LineWidth, LineColor, true, OutlineWidth, OutlineColor);
		}
		else
		{
			DrawLine(X, Y, X, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine(X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, false, 0, 0);
			DrawLine(X + Width, Y + Height, X + Width, Y, LineWidth, LineColor, false, 0, 0);
			DrawLine(X + Width, Y, X, Y, LineWidth, LineColor, false, 0, 0);
		}
	}
}

void DirectXT::DrawCross(int X, int Y, int Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, int OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[4];
	if (Outlined)
	{
		DrawLine(X - Size / 2 - OutlineWidth, Y, X - 1, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine(X + Size / 2 + OutlineWidth, Y, X, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine(X, Y - Size / 2 - OutlineWidth, X, Y - 1, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
		DrawLine(X, Y + Size / 2 + OutlineWidth, X, Y, LineWidth, OutlineColor, true, OutlineWidth, OutlineColor);
	}
		DrawLine(X - Size / 2, Y, X - 1, Y, LineWidth, CrossColor, false, 0, 0);
		DrawLine(X + Size / 2, Y, X, Y, LineWidth, CrossColor, false, 0, 0);
		DrawLine(X, Y - Size / 2, X, Y - 1, LineWidth, CrossColor, false, 0, 0);
		DrawLine(X, Y + Size / 2, X, Y, LineWidth, CrossColor, false, 0, 0);
}

void DirectXT::Render()
{
	if (Valid())
	{
		DXDevice->Clear(NULL, NULL, D3DCLEAR_TARGET, NULL, 1, NULL);
		DXDevice->BeginScene();
		DrawCross(Overlay->Width / 2, Overlay->Height / 2, 15, 1, D3DCOLOR_RGBA(0, 255, 0, 255), true, 1, D3DCOLOR_RGBA(0, 0, 0, 255));
		if (Globals->DebugSettings.EnableDebugLog)
		{
			DrawString(Overlay->X, Overlay->Y, Debug->DebugLog, Globals->DebugSettings.TextColor, Globals->DebugSettings.DrawTextOutline,  Globals->DebugSettings.TextOutlineColor);
		}
		DXDevice->EndScene();
		DXDevice->PresentEx(NULL, NULL, NULL, NULL, NULL);
	}
}

bool DirectXT::SetupDirectX(HWND Handle, int Width, int Height)
{
	Debug->Log(L"Setting up DirectX...");
	Direct3DCreate9Ex(D3D_SDK_VERSION, &DX);
	if (DX)
	{
		ZeroMemory(&DXParams, sizeof(DXParams));
		DXParams.Windowed = TRUE;
		DXParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		DXParams.hDeviceWindow = Handle;
		DXParams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		DXParams.BackBufferFormat = D3DFMT_A8R8G8B8;
		DXParams.BackBufferWidth = Width;
		DXParams.BackBufferHeight = Height;
		DXParams.EnableAutoDepthStencil = TRUE;
		DXParams.AutoDepthStencilFormat = D3DFMT_D16;
		DX->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DXParams, 0, &DXDevice);
		if (DXDevice)
		{
			D3DXCreateLine(DXDevice, &DXLine);
			if (DXLine)
			{
				D3DXCreateFont(DXDevice, 16, NULL, FW_SEMIBOLD, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, L"Arial", &DXFont);
				if (DXFont)
				{
					Debug->Log(L"DirectX setup was successful.");
					return true;
				}
				else
				{
					MessageBoxW(NULL, L"D3DXCreateFont Failed!", L"Fatal Error", MB_OK);
					return false;
				}
			}
			else
			{
				MessageBoxW(NULL, L"D3DXCreateLine Failed!", L"Fatal Error", MB_OK);
				return false;
			}
		}
		else
		{
			MessageBoxW(NULL, L"CreateDeviceEx Failed!", L"Fatal Error", MB_OK);
			return false;
		}
	}
	else
	{
		MessageBoxW(NULL, L"Direct3DCreate9Ex Failed!", L"Fatal Error", MB_OK);
		return false;
	}
}