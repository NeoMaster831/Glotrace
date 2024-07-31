/*
* common.h: Common Functions.
* Impl: Common Functions.
*/

#pragma once
#include <Windows.h>
#include <vector>
#include <gdiplus.h>

// Abstract: Error Box
#define ErrBox(content) MessageBox(NULL, content, L"Error", MB_ICONERROR | MB_OK)