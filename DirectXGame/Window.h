#pragma once
#include <Windows.h>

class Window
{
public:
	Window();

	// Initialize the window
	bool InitWindow();

	// Translate & Dispatch messages
	bool BroadCast();

	// Release the window
	bool ReleaseWindow();

	// 
	bool isRunning();

	RECT GetClientWindowRect();

	void SetHWND(HWND hwnd);

	// EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();

protected:
	HWND m_hwnd;
	bool m_isRun;
};