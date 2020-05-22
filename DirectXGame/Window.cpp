#include "Window.h"

//Window* window = nullptr;

Window::Window()
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{ 
			Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(window));
			window->SetHWND(hWnd);
			// Event fired when window will be created
			window->onCreate();
			break;
		}

		case WM_DESTROY:
		{
			// Event fired when window will be destroyed
			Window* window = reinterpret_cast<Window*>(GetWindowLong(hWnd, GWLP_USERDATA));
			window->onDestroy();
			::PostQuitMessage(NULL);
			break;
		}

		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

bool Window::InitWindow()
{
	// Setting up WNDCLASSEX object
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) // If the registration of class will fail, the function will return false
		return false;

	/*if (!window)
		window = this;*/

	// Creation of the window
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);
	
	if (!m_hwnd)	// If creation fail return false
		return false;

	// Show up the window
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	// Set this flag to indicate that the window is initialized and running
	this->m_isRun = true;

	return true;
}

bool Window::BroadCast()
{
	MSG msg;

	this->onUpdate();

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(0);

	return true;
}

bool Window::ReleaseWindow()
{
	// Destroy the window
	if (!::DestroyWindow(m_hwnd))
		false;

	return false;
}

bool Window::isRunning()
{
	return this->m_isRun;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{

}

void Window::onDestroy()
{
	this->m_isRun = false;
}

Window::~Window()
{

}
