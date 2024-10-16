#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

//**************************************************************
// Adventure3DS_MAK.cpp
//
// Purpose: Dig through the void to find the keys!
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

void fillScreen(u8* screen, u8 r, u8 g, u8 b)
{
	for(int i = 0; i <= 320; i++)
	{
		for(int p = 0; p <= 240; p++)
		{
			thickPixel(screen, i, p, r, g, b);
		}
	}
}

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	hidScanInput();
	u32 kDown = hidKeysDown();

	printf("\x1b[2;0HAdventure!");
	printf("\x1b[4;0HNavigating with the touch screen, find the hidden key and win!\n\nPress start to exit...");
	printf("\x1b[6;0HPress A to cheat");
	consoleInit(GFX_BOTTOM, NULL);

	u8* bottomScreen = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);
	u8 color = 255;
	fillScreen(bottomScreen, color, color, color);
	time_t* rngSeed = (0);
	srand(time(rngSeed));
	u32 kX = rand() % 319 + 1;
	u32 kY = rand() % 239 + 1;  

	while (aptMainLoop())
		{
			hidScanInput();
			u32 kDown = hidKeysDown();
			if (kDown & KEY_START) break; 
			gfxFlushBuffers();
			gfxSwapBuffers();
			gspWaitForVBlank();

			touchPosition touch;
			hidTouchRead(&touch);

			u32 xcoord = touch.px;
			u32 ycoord = touch.py;
			u8 touchColor = 0;
			thickPixel(bottomScreen, xcoord, ycoord, touchColor, touchColor, touchColor);
			
			if(kDown & KEY_A)
			{
				thickPixel(bottomScreen, kX, kY, 158, 224, 32);
			}

			if(xcoord == kX && ycoord == kY)
			{
				printf("\x1b[0;0 You win! Quitting in 5 seconds...");
				svcSleepThread(5000*1000000);
				gfxExit();
				return 0;
			}
		
			gfxFlushBuffers();
			gfxSwapBuffers();
			gspWaitForVBlank();
		}

	gfxExit();
	return 0;
}