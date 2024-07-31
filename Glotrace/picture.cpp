/*
* picture.cpp: Implementation of picture.h
*/

#include "picture.h"

Gdiplus::Bitmap * Pic::getPictureBitmap(LPCWSTR path) {

	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(path);
	if (bitmap->GetLastStatus() != Gdiplus::Status::Ok) {
		delete bitmap;
		return nullptr;
	}

	return bitmap;
}

bool Pic::controlPictureAlpha(Gdiplus::Bitmap* picture, double alpha) {

	if (alpha < 0.0 || alpha > 1.0) {
		return false;
	}

	UINT width = picture->GetWidth();
	UINT height = picture->GetHeight();

	for (UINT y = 0; y < height; y++) {
		for (UINT x = 0; x < width; x++) {

			Gdiplus::Color oldColor;

			picture->GetPixel(x, y, &oldColor);

			auto red = oldColor.GetRed();
			auto green = oldColor.GetGreen();
			auto blue = oldColor.GetBlue();
			auto oldAlpha = oldColor.GetAlpha();
			
			auto newAlpha = (BYTE)((double)oldAlpha * alpha);

			Gdiplus::Color newColor(newAlpha, red, green, blue);
			
			picture->SetPixel(x, y, newColor);
		}
	}

	return true;
}