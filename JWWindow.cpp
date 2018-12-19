#include "JWWindow.h"

HWND JWWindow::Create(LPCWSTR Name, int X, int Y, int W, int H,
	COLORREF dwColor, WNDPROC pProc, DWORD WS) {

	HWND temphWnd;

	// �ܼ��� ���..!?��
	m_hInst = GetModuleHandle(NULL);

	// ������ Ŭ���� ���
	m_WC.cbClsExtra = 0;
	m_WC.cbWndExtra = 0;
	m_WC.hbrBackground = CreateSolidBrush(dwColor);
	m_WC.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WC.hInstance = m_hInst;
	m_WC.lpfnWndProc = pProc;
	m_WC.lpszClassName = Name;
	m_WC.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	m_WC.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&m_WC);

	// ������ ����
	temphWnd = CreateWindow(Name, Name, (DWORD)WS, X, Y, W, H, NULL, (HMENU)NULL, m_hInst, NULL);

	// ������ ǥ��
	ShowWindow(temphWnd, SW_SHOW);
	UpdateWindow(temphWnd);

	// ������ Ŭ���� ����
	//UnregisterClass(Name, m_hInst);

	m_hAccel = LoadAccelerators(m_hInst, MAKEINTRESOURCE(IDR_ACCELERATOR1)); // accelator load

	m_hWndMain = temphWnd;
	return temphWnd;
}

HWND JWWindow::AddChild(HWND hParentWnd, LPCWSTR Name, int X, int Y, int W, int H,
	COLORREF dwColor, WNDPROC pProc) {

	HWND temphWnd;

	// ������ Ŭ���� ���
	m_WC.hbrBackground = CreateSolidBrush(dwColor);
	m_WC.lpfnWndProc = pProc;
	m_WC.lpszClassName = Name;
	RegisterClass(&m_WC);

	// ������ ����
	temphWnd = CreateWindow(Name, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, X, Y, W, H, hParentWnd, 0, m_hInst, NULL);

	// ������ Ŭ���� ����
	UnregisterClass(Name, m_hInst);

	return temphWnd;
}

int JWWindow::Run(HWND hMainWnd) {
	//while (m_MSG.message != WM_QUIT) {
	while (GetMessage(&m_MSG, 0, 0, 0)) {
		if (!TranslateAccelerator(hMainWnd, m_hAccel, &m_MSG)) { // accelator�� ����� Ű ������ true �����ؼ� �Ʒ� �������� �ȵ�����
		//if (PeekMessage(&m_MSG, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&m_MSG);
			DispatchMessage(&m_MSG);
		}
	}
	return m_MSG.wParam;
}

HWND JWWindow::AddScrollbarH(HWND hParentWnd, int Min, int Max) {
	RECT tempRect;
	GetClientRect(hParentWnd, &tempRect);

	int x, y, w, h;
	x = 0;
	y = tempRect.bottom - 20;
	w = tempRect.right - 20;
	h = 20;

	HWND temphWnd = AddControl(L"scrollbar", hParentWnd, SBS_HORZ, x, y, w, h);
	SetScrollRange(temphWnd, SB_CTL, Min, Max, TRUE);
	return temphWnd;
}

HWND JWWindow::AddScrollbarV(HWND hParentWnd, int Min, int Max) {
	RECT tempRect;
	GetClientRect(hParentWnd, &tempRect);

	int x, y, w, h;
	x = tempRect.right - 20;
	y = 0;
	w = 20;
	h = tempRect.bottom - 20;

	HWND temphWnd = AddControl(L"scrollbar", hParentWnd, SBS_VERT, x, y, w, h);
	SetScrollRange(temphWnd, SB_CTL, Min, Max, TRUE);
	return temphWnd;
}

HWND JWWindow::AddControl(LPCWSTR ClassName, HWND hParentWnd, DWORD Style, int X, int Y, int W, int H) {
	HWND temphWnd = NULL;
	temphWnd = CreateWindow(ClassName, NULL, WS_CHILD | WS_VISIBLE | Style, X, Y, W, H, hParentWnd, (HMENU)100, m_hInst, NULL);
	return temphWnd;
}

int JWWindow::SetDlgBase() {
	ZeroMemory(&m_OFN, sizeof(m_OFN));
	m_OFN.lStructSize = sizeof(m_OFN);
	m_OFN.hwndOwner = m_hWndMain;
	m_OFN.lpstrFile = m_FileName;
	m_OFN.nMaxFile = sizeof(m_FileName);
	m_OFN.nFilterIndex = 1;
	m_OFN.lpstrFileTitle = NULL;
	m_OFN.nMaxFileTitle = 0;
	m_OFN.lpstrInitialDir = NULL;
	m_OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return 0;
}

BOOL JWWindow::OpenFileDlg(LPCWSTR Filter) {
	SetDlgBase();
	m_OFN.lpstrFilter = Filter;

	return GetOpenFileName(&m_OFN);
}

BOOL JWWindow::SaveFileDlg(LPCWSTR Filter) {
	SetDlgBase();
	m_OFN.lpstrFilter = Filter;

	return GetSaveFileName(&m_OFN);
}

int JWWindow::OpenFileText(std::wstring FileName) {
	std::wifstream filein;
	filein.open(FileName, std::wifstream::in);
	if (!filein.is_open()) return -1;
	
	wchar_t tempText[FILELINELEN];
	m_FileText.clear();
	while (!filein.eof()) {
		filein.getline(tempText, FILELINELEN);
		m_FileText += tempText;
		m_FileText += '\n';
	}
	m_FileText = m_FileText.substr(0, m_FileText.size() - 1);

	return 0;
}

int JWWindow::SaveFileText(std::wstring FileName) {
	std::wofstream fileout;
	fileout.open(FileName, std::wofstream::out);
	if (!fileout.is_open()) return -1;

	fileout.write(m_FileText.c_str(), m_FileText.size());
	return 0;
}

std::wstring JWWindow::GetDlgFileName() {
	return m_FileName;
}

LRESULT CALLBACK JWWindow::BaseProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	int tempScrPos;
	int tempScrMin;
	int tempScrMax;

	switch (Message)
	{
	case WM_CREATE:
		break;
	case WM_HSCROLL:
		GetScrollRange((HWND)lParam, SB_CTL, &tempScrMin, &tempScrMax);
		tempScrPos = GetScrollPos((HWND)lParam, SB_CTL);

		switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			tempScrPos = max(tempScrMin, tempScrPos - 1);
			break;
		case SB_LINERIGHT:
			tempScrPos = min(tempScrMax, tempScrPos + 1);
			break;
		case SB_PAGELEFT:
			tempScrPos = max(tempScrMin, tempScrPos - 10);
			break;
		case SB_PAGERIGHT:
			tempScrPos = min(tempScrMax, tempScrPos + 10);
			break;
		case SB_THUMBTRACK:
			tempScrPos = HIWORD(wParam);
			break;
		}
		SetScrollPos((HWND)lParam, SB_CTL, tempScrPos, TRUE);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_VSCROLL:
		GetScrollRange((HWND)lParam, SB_CTL, &tempScrMin, &tempScrMax);
		tempScrPos = GetScrollPos((HWND)lParam, SB_CTL);

		switch (LOWORD(wParam)) {
		case SB_LINEUP:
			tempScrPos = max(tempScrMin, tempScrPos - 1);
			break;
		case SB_LINEDOWN:
			tempScrPos = min(tempScrMax, tempScrPos + 1);
			break;
		case SB_PAGEUP:
			tempScrPos = max(tempScrMin, tempScrPos - 10);
			break;
		case SB_PAGEDOWN:
			tempScrPos = min(tempScrMax, tempScrPos + 10);
			break;
		case SB_THUMBTRACK:
			tempScrPos = HIWORD(wParam);
			break;
		}
		SetScrollPos((HWND)lParam, SB_CTL, tempScrPos, TRUE);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return 0;
}