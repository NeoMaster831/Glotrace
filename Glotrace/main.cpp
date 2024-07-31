/*
* main.cpp: The main entrypoint of the program.
* Impl: It is the main entry. It processes the main system routine.
* TODO: main.cpp is gonna be just using for the transferring the system cycle to other parts.
*	It doesn't need that right now because our program is small enough.
*/

#include "common.h"
#include "picture.h"
#include "gdi.h"

#define HOTKEY_ID 1337

#define TEST_PICTURE L"C:\\Users\\wane\\Desktop\\anime.jpg"
#define TEST_ALPHA 0.45

INT APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT) {

	if (!g_Gdi.beginGdi(L"GlotraceGdi", L"GlotraceGdiClass")) {

		ErrBox(L"Failed to initialize GDI+.");
		return 1;
	}

	auto picture = Pic::getPictureBitmap(TEST_PICTURE);
	if (picture == nullptr) {

		ErrBox(L"Failed to load Picture");
		return 1;
	}

	if (!Pic::controlPictureAlpha(picture, TEST_ALPHA)) {

		ErrBox(L"Failed to control alpha");
		return 1;
	}

	if (!g_Gdi.renderGdi(picture)) {

		ErrBox(L"Failed to render GDI+.");
		return 1;
	}

	// The routine that traps the program to do not exit

	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessageW(&msg, NULL, 0, 0)) != 0) {

		if (bRet == -1) {
			ErrBox(L"Unexpected Error occured when translating message.");
			return 1;
		}

		TranslateMessage(&msg);
		DispatchMessageW(&msg);

	}

	delete picture;
	g_Gdi.endGdi();

	return 0;
}