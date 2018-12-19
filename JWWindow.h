#pragma once
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include "resource.h"

class JWWindow
{
private:
	HINSTANCE m_hInst;
	WNDCLASS m_WC;
	MSG m_MSG;
	HACCEL m_hAccel;
	HWND m_hWndMain;
	TCHAR m_FileName[260] = { 0 };
	OPENFILENAME m_OFN;
	std::wstring m_FileText;
	static const int FILELINELEN = 256;
	
private:
	HWND JWWindow::AddControl(LPCWSTR ClassName, HWND hParentWnd, DWORD Style, int X, int Y, int W, int H);
	int JWWindow::SetDlgBase();

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

	BOOL JWWindow::OpenFileDlg(LPCWSTR Filter);
	int JWWindow::OpenFileText(std::wstring FileName);
	BOOL JWWindow::SaveFileDlg(LPCWSTR Filter);
	int JWWindow::SaveFileText(std::wstring FileName);
	std::wstring JWWindow::GetDlgFileName();

	LRESULT CALLBACK JWWindow::BaseProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
};