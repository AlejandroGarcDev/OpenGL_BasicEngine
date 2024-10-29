#include "OGL3D/Graphics/OGraphicsEngine.h"
#include "vendor/glad/include/glad/glad.h"
#include "vendor/glad/include/glad/glad_wgl.h"
#include "assert.h"
#include "stdexcept"


OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc = {}; //Clase con funciones-atributos para windows
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DDummyWINDOW";
	wc.lpfnWndProc = DefWindowProc;

	auto classId = (RegisterClassEx(&wc));
	assert(classId);

	// WS_OVERLAPPED = overlapped window
	// WS_CAPTION = title bar
	// WS_SYSMENU = window menu (when you click on title bar icon)

	auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), L"OpenGL 3D Game", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

	assert(dummyWindow);

	//Get device context
	auto dummyDC = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion = 1;
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDesc.cColorBits = 32;
	pixelFormatDesc.cAlphaBits = 8;
	pixelFormatDesc.cDepthBits = 24;
	pixelFormatDesc.cStencilBits = 8;
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

	auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

	auto dummyContext = wglCreateContext(dummyDC);
	assert(dummyContext);

	wglMakeCurrent(dummyDC, dummyContext);

	if (!gladLoadWGL(dummyDC))
	{
		throw std::runtime_error("OGraphicsEngine - Error - gladLoadlWGL failed");
	}

	if (!gladLoadGL())
	{
		throw std::runtime_error("OGraphicsEngine - Error - gladLoadlGL failed");
	}

	wglMakeCurrent(dummyDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);

}

OGraphicsEngine::~OGraphicsEngine()
{

}
