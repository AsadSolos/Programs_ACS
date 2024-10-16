#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

//**************************************************************
// Paint3DS_MAK.cpp
//
// Purpose: Fun drawing tool. Only has draw, erase, and clear screen. 
//
// Note: To run this, make it in terminal after CD-ing into the directory and then run it in Citra 3DS emulator. Google Citra 3DS Emulator for download instructions. Make sure to bind inputs in order to play the game.
//
// R1: 1-Apr-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************

void drawPixel(u8* screen, u32 x,u32 y,u8 r,u8 g, u8 b)
{
	u32 color = RGB8_to_565(r, g, b);
	int idx = (x * 240) + (239 - y);
	((u16*)screen)[idx] = (u16)color;
}

void thickPixel(u8* screen, u32 x,u32 y,u8 r,u8 g, u8 b)
{
	if (x != 0 || y != 0)
	{
		drawPixel(screen, x, y, r, g, b);
		drawPixel(screen, x + 1, y + 1, r, g, b);
		drawPixel(screen, x, y + 1, r, g, b);
		drawPixel(screen, x + 1, y, r, g, b);
		drawPixel(screen, x + 2, y + 2, r, g, b);
		drawPixel(screen, x, y + 2, r, g, b);
		drawPixel(screen, x + 2, y, r, g, b);
		drawPixel(screen, x + 1, y + 2, r, g, b);
		drawPixel(screen, x + 2, y + 1, r, g, b);
	}

}

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	hidScanInput();

	printf("\x1b[2;0HDraw!");
	printf("\x1b[4;0HPress L and R to clear the canvas.");

	consoleInit(GFX_BOTTOM, NULL);

	while (aptMainLoop())
		{
			hidScanInput();
			u32 kDown = hidKeysDown();
			if (kDown & KEY_START) break; 
			gfxFlushBuffers();
			gfxSwapBuffers();
			gspWaitForVBlank();
			//gfxSetDoubleBuffering(GFX_BOTTOM, true);
	
			touchPosition touch;
			hidTouchRead(&touch);
		
			u8* bottomScreen = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
			u32 xcoord = touch.px;
			u32 ycoord = touch.py;
			u8 color = 255;
			
			thickPixel(bottomScreen, xcoord, ycoord, color, color, color);
			
			if ((kDown & KEY_L) && (kDown & KEY_R))
			{
				consoleClear();
			}

			gfxFlushBuffers();
			gfxSwapBuffers();
			gspWaitForVBlank();
		}

	gfxExit();
	return 0;
}