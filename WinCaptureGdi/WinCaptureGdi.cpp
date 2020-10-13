// WinCaptureGdi.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <dwmapi.h>
#include <wingdi.h>
#include <Windows.h>

#include "ImageHelper.h"

#pragma comment(lib,"Dwmapi.lib")

int main()
{
    std::cout << "Hello World!\n";

	// creates a memory device context (DC) 
	auto dc = CreateCompatibleDC(nullptr);

	// get device context (DC) 
	auto src_dc = GetDC(nullptr);

	// 	SRCCOPY : Copies the source rectangle directly to the destination rectangle.
	DWORD rop = SRCCOPY;
	BOOL bDwmEnable = TRUE;

	// indicates whether Desktop Window Manager (DWM) composition is enabled
	auto hr = DwmIsCompositionEnabled(&bDwmEnable);

	if (hr == S_OK && !bDwmEnable) {
		// Includes any windows that are layered on top of your window in the resulting image. 
		// By default, the image only contains your window. 
		// Note that this generally cannot be used for printing device contexts.
		rop |= CAPTUREBLT;
	}

	int32_t width = 1920;
	int32_t heigh = 1080;

	BITMAP bm;
	HBITMAP__ *bmp = NULL;

	// retrieves information for the specified graphics object.
	GetObject(bmp, sizeof(BITMAP), &bm);
	BYTE *bits = static_cast<BYTE*>(bm.bmBits);
	BITMAPINFO bi = { 0 };
	BITMAPINFOHEADER *head = &bi.bmiHeader;
	head->biSize = sizeof(BITMAPINFOHEADER);
	head->biBitCount = 32;
	head->biWidth = width;
	head->biHeight =  -heigh;
	head->biPlanes = 1;
	// creates a DIB that applications can write to directly. 
	// The function gives you a pointer to the location of the bitmap bit values. 
	bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, (void**)&bits, nullptr, 0);

	// selects an object into the specified device context (DC).
	SelectObject(dc, bmp);

	// performs a bit-block transfer of the color data corresponding to a rectangle of pixels from the specified source device context into a destination device context.
	BitBlt(dc, 0, 0, width, heigh, src_dc, 0, 0, rop);

	ImageHelper::SaveBitmapToFile(bmp, "bmp.bmp");

	// release dc
	DeleteDC(dc);
	ReleaseDC(NULL, src_dc);

	std::cout << "Hello World End!\n";

}