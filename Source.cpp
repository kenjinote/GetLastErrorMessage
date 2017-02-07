#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1;
	static HWND hEdit2;
	switch (msg)
	{
	case WM_CREATE:
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_NUMBER, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL  | ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SETFOCUS:
		SetFocus(hEdit1);
		break;
	case WM_SIZE:
		MoveWindow(hEdit1, 10, 10, 512, 32, TRUE);
		MoveWindow(hEdit2, 10, 50, LOWORD(lParam) - 20, HIWORD(lParam) - 10 - 10 - 10 -32, TRUE);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == EN_CHANGE && (HWND)lParam == hEdit1)
		{
			TCHAR szNumber[MAX_PATH];
			GetWindowText(hEdit1, szNumber, MAX_PATH);
			const DWORD dwError = _wtol(szNumber);
			TCHAR szErrorMessage[1024] = {0};
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, szErrorMessage, 1024, NULL);
			SetWindowText(hEdit2, szErrorMessage);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("GetLastErrorMessage"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
