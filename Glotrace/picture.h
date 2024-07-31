/*
* picture.h: Process pictures to GDI bitmap Object
* Impl: Various things about picture
*/

#pragma once
#include "common.h"

// Abstract: Picture Manager Namespace.
namespace Pic {

	// Abstract: Get Picture Bitmap
	// Param: File Path
	// Returns: Picture Bitmap Pointer. Make sure we should free the pointer.
	Gdiplus::Bitmap* getPictureBitmap(LPCWSTR path);
	
	// Abstract: Control Alpha Value of Picture
	// Param: Picture Bitmap Pointer, Alpha (0~1)
	// Returns:
	//	- true: if it succeed
	//	- flase: if it failed
	bool controlPictureAlpha(Gdiplus::Bitmap* picture, double alpha);
}