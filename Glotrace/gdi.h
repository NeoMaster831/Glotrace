/*
* gdi.h: The provide for the GDI+
* Impl: It provides the easier access through GDI+.
*/

#pragma once
#include "common.h"

// Abstract: The callback function of GDI+ Windows.
// Detail: It just define some necessary events.
LRESULT CALLBACK gdiWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

// Abstract: GDI+ Class.
// Detail: It is the only-made for our project, so we don't implement unnecessary things.
// Notice:
//	- ONE window is corresponding to ONE class.
class Gdi {

private:

	// Width and height of the system.
	const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
	const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

	// The GDI+ window and the corresponding class
	// It is delivered by `createWindow` method.
	HWND window;
	WNDCLASSEXW windowClass;

	// GDI+ Token
	ULONG_PTR gdiToken;

	// Abstract: Create GDI+ homing window.
	// Detail: It creates the transparent window, top-most window.
	// Returns:
	//	- true: If it succeed.
	//	- false: If it failed.
	bool createWindow(LPCWSTR windowName, LPCWSTR className);

	// Abstract: Destroy GDI+ homing window.
	void destroyWindow();

	// Abstract: Init GDI+.
	// Returns:
	//	- true: If it succeed.
	//	- false: If it failed.
	bool initGdi();

	// Abstract: Shutdown GDI+.
	void shutdownGdi();

public:

	// Abstract: Creator.
	// Detail: initiates values.
	Gdi();

	// Abstract: Begin GDI Instance.
	// Detail: it performs `createWindow` and `initGdi`.
	// Param: Window Name, Class Name
	// Returns:
	//	- true: If it succeed.
	//	- false: If it failed.
	bool beginGdi(LPCWSTR windowName, LPCWSTR className);

	// Abstract: Render GDI.
	bool renderGdi(Gdiplus::Bitmap* picture);

	// Abstract: End GDI Instance.
	void endGdi();
};

// Global gdi object
inline Gdi g_Gdi;