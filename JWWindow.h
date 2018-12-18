#pragma once
#include <Windows.h>
#include <vector>
#include "resource.h"

class JWWindow
{
private:
	HINSTANCE m_hInst;
	WNDCLASS m_WC;
	MSG m_MSG;
	HACCEL m_hAccel;
	HWND m_hWndMain;
	TCHAR m_szFile[260] = { 0 };
	OPENFILENAME m_OFN;
	
private:
	HWND JWWindow::AddControl(LPCWSTR ClassName, HWND hParentWnd, DWORD Style, int X, int Y, int W, int H);

public:
	JWWindow() {};
	~JWWindow() {};

	HWND JWWindow::Create(LPCWSTR Name, int X, int Y, int W, int H,
		COLORREF dwColor, WNDPROC pProc, DWORD WS);
	HWND JWWindow::AddChild(HWND hParentWnd, LPCWSTR Name, int X, int Y, int W, int H,
		COLORREF dwColor, WNDPROC pProc);
	int JWWindow::Run(HWND hMainWnd);

	HWND JWWindow::AddScrollbarH(HWND hParentWnd, int Min, int Max);
	HWND JWWindow::AddScrollbarV(HWND hParentWnd, int Min, int Max);

	BOOL JWWindow::OpenFile(LPCWSTR Filter);

	LRESULT CALLBACK JWWindow::BaseProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
};