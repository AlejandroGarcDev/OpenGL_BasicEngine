#include "OGL3D/Window/OWindow.h"
#include <Windows.h>
#include <assert.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return NULL;
}


OWindow::OWindow()
{
	WNDCLASSEX wc = {}; //Clase con funciones-atributos para windows
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DWINDOW";
	wc.lpfnWndProc = &WndProc;

	auto classId = (RegisterClassEx(&wc));
	assert(classId);

	// {top,left,right,bottom}
	RECT rc = { 0,0,1024,768 };

	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);


	// WS_OVERLAPPED = overlapped window
	// WS_CAPTION = title bar
	// WS_SYSMENU = window menu (when you click on title bar icon)

	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), L"OpenGL 3D Game", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);
}

OWindow::~OWindow()
{
	DestroyWindow((HWND)m_handle);
}