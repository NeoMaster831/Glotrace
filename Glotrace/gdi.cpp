/*
* gdi.cpp: The implementation of gdi.h
*/

#include "gdi.h"

LRESULT CALLBACK gdiWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		
	case WM_DESTROY: {
		PostQuitMessage(0);
	} return 0;

	}

	return DefWindowProc(window, message, wParam, lParam);
}

Gdi::Gdi() {

	this->window = nullptr;
	this->windowClass = {};
	this->gdiToken = NULL;
}

bool Gdi::createWindow(LPCWSTR windowName, LPCWSTR className) {

	if (this->window != nullptr || this->gdiToken != NULL) {
		return false;
	}

	this->windowClass = {
		sizeof(WNDCLASSEXW),
		CS_HREDRAW | CS_VREDRAW,
		gdiWindowProc,
		0,
		0,
		GetModuleHandle(0),
		0,
		0,
		0,
		0,
		className,
		0
	};

	RegisterClassExW(&this->windowClass);

	this->window = CreateWindowExW(
		WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
		className,
		windowName,
		WS_POPUP,
		0,
		0,
		this->WIDTH,
		this->HEIGHT,
		NULL,
		NULL,
		this->windowClass.hInstance,
		NULL
	);

	SetWindowPos(this->window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	ShowWindow(this->window, SW_SHOW);

	if (IsWindowVisible(this->window)) {
		return true;
	}
	else {
		return false;
	}
}

void Gdi::destroyWindow() {

	DestroyWindow(this->window);

	UnregisterClassW(this->windowClass.lpszClassName, this->windowClass.hInstance);

	this->window = nullptr;
	this->windowClass = {};
}

bool Gdi::initGdi() {

	if (this->gdiToken != NULL) {
		return false;
	}

	Gdiplus::GdiplusStartupInput gpsi;

	Gdiplus::Status result = Gdiplus::GdiplusStartup(&this->gdiToken, &gpsi, NULL);

	if (result == Gdiplus::Status::Ok) {
		return true;
	}
	else {
		return false;
	}
}

void Gdi::shutdownGdi() {

	Gdiplus::GdiplusShutdown(this->gdiToken);

	this->gdiToken = NULL;
}

bool Gdi::beginGdi(LPCWSTR windowName, LPCWSTR className) {

	if (!createWindow(windowName, className)) {
		return false;
	}

	if (!initGdi()) {
		return false;
	}
	
	return true;
}

void Gdi::endGdi() {

	shutdownGdi();
	destroyWindow();
}

bool Gdi::renderGdi(Gdiplus::Bitmap* picture) {

	HDC dcScreen = GetDC(this->window);
	HDC dcMemory = CreateCompatibleDC(dcScreen);

	HBITMAP hBitmap;
	picture->GetHBITMAP(Gdiplus::Color::Black, &hBitmap);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(dcMemory, hBitmap);

	UINT width = picture->GetWidth();
	UINT height = picture->GetHeight();

	POINT ptZero = { 0, 0 };
	SIZE size = { (LONG)width, (LONG)height };
	POINT ptTopLeft = ptZero;

	BLENDFUNCTION blend = { 0 };
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	bool result = UpdateLayeredWindow(
		this->window,
		dcScreen,
		&ptTopLeft,
		&size,
		dcMemory,
		&ptZero,
		0,
		&blend,
		ULW_ALPHA
	);

	SelectObject(dcMemory, oldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(dcMemory);
	ReleaseDC(this->window, dcScreen);

	return result;
}