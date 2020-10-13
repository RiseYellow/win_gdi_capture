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

	auto dc = CreateCompatibleDC(nullptr);
	auto src_dc = GetDC(nullptr);

	DWORD rop = SRCCOPY;
	BOOL bDwmEnable = TRUE;
	auto hr = DwmIsCompositionEnabled(&bDwmEnable);

	if (hr == S_OK && !bDwmEnable) {
		rop |= CAPTUREBLT;
	}

	int32_t width = 1920;
	int32_t heigh = 1080;

	BITMAP bm;
	HBITMAP__ *bmp = new HBITMAP__();

	GetObject(bmp, sizeof(BITMAP), &bm);
	BYTE *bits = static_cast<BYTE*>(bm.bmBits);
	BITMAPINFO bi = { 0 };
	BITMAPINFOHEADER *head = &bi.bmiHeader;
	head->biSize = sizeof(BITMAPINFOHEADER);
	head->biBitCount = 32;
	head->biWidth = width;
	head->biHeight =  -heigh;
	head->biPlanes = 1;
	bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, (void**)&bits, nullptr, 0);
	SelectObject(dc, bmp);

	BitBlt(dc, 0, 0, width, heigh, src_dc, 0, 0, rop);

	ImageHelper::SaveBitmapToFile(bmp, "bmp.bmp");
	std::cout << "Hello World End!\n";

}