#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
//**************************************************************
// RNGMAP3DS_MAK
//
// Purpose: Tests RNG function map at different RNG start values (0,1,2,3)
//
// Note: To run this, make it in terminal after CD-ing into the directory and then run it in Citra 3DS emulator. Google Citra 3DS Emulator for download instructions. Make sure to bind inputs in order to play the game.
//
// R1: 1-Apr-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************
void drawPixel(u8* screen, u32 x,u32 y,u8 r,u8 g, u8 b) //renders a pixel
{
	u32 color = RGB8_to_565(r, g, b); //convert rgb from 8 to 565 as 3DS uses 565
	int idx = (x * 240) + (239 - y);
	((u16*)screen)[idx] = (u16)color;
}
void thickPixel(u8* screen, u32 x,u32 y,u8 r,u8 g, u8 b) //renders a thick pixel (4x4)
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
int fruitCordX, fruitCordY;
int width = 400;
int height = 240;
u8* topScreen = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
int main(int argc, char **argv)
{
	gfxInitDefault();
	u8* topScreen = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_BOTTOM, NULL);

	printf("\x1b[2;0H RNG Map Tester");
	printf("\x1b[3;0H Press Start to exit");
	//The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns
	consoleInit(GFX_TOP, NULL);
	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		time_t* rngSeed = (0);
		srand(time(rngSeed));
		fruitCordX = rand() % width;
		fruitCordY = rand() % height;
		thickPixel(topScreen, fruitCordX, fruitCordY, 204, 10, 0);
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		
		

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
