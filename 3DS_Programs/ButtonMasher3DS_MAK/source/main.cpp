#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

//**************************************************************
// ButtonMasher3DS_MAK.cpp
//
// Purpose: Test your button mashing speed in this game by pressing spacebar as fast as you can. Your presses per second will be displayed upon completion.
//
// Note: To run this, make it in terminal after CD-ing into the directory and then run it in Citra 3DS emulator. Google Citra 3DS Emulator for download instructions. Make sure to bind inputs in order to play the game.
//
// R1: 26-Jan-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************

int main(int argc, char **argv)
{
	gfxInitDefault();

	consoleInit(GFX_TOP, NULL);

		hidScanInput();

		u32 kDown = hidKeysDown();
		int count = 0;
		double summary = 0;
		double timeSinceStart = 0;


		printf("\x1b[16;3HWelcome to my button masher! The button in ");
		printf("\x1b[17;3Hquestion is the A button. Press it as ");
		printf("\x1b[18;3Hfast as you can in the time allotted and see ");
		printf("\x1b[19;3Hhow fast you can go!");
		printf("\x1b[30;16HPress A to start the game...");


	while(true)
	{
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_A) break;
	}
	consoleClear();
	while(true)
	{
		hidScanInput();
			consoleClear();
				

				svcSleepThread(1000*1000000);
				printf("\x1b[16;3H3");
				svcSleepThread(1000*1000000);
				printf("\x1b[17;3H2");
				svcSleepThread(1000*1000000);
				printf("\x1b[18;3H1");
				svcSleepThread(1000*1000000);
				consoleClear();
				printf("\x1b[16;20HGo!!!");
				timeSinceStart =  svcGetSystemTick() / (SYSCLOCK_ARM11 / 1000.0);
				
				break;
	}
	

			while (true)
			{
				
				double evil =  (svcGetSystemTick() / (SYSCLOCK_ARM11 / 1000.0));
				printf("\x1b[19;3HMilliseconds since you started. Add 5000 to the ");
				std::cout << "\x1b[20;3Hinitial and the game will end: " << (evil) << std::endl; 
				hidScanInput();
				u32 kDown = hidKeysDown();
				if (kDown & KEY_A)
				{
					count++;
				}
				
				if (evil  > (timeSinceStart + 5000))
				{
					break;
				}
				
			}
			while (true)
			{
				consoleClear();
				summary = count / 5.0;
				printf("\x1b[16;3HGame Over!");
				std::cout << "\x1b[17;3HA Button Presses: " << count << std::endl;  
				std::cout << "\x1b[18;3HPresses per second:  " << summary << std::endl;
				printf("\x1b[30;16HPress Start to quit");
				break;
			}


			
while (aptMainLoop())
	{
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START) break; 
		gfxFlushBuffers();
		gfxSwapBuffers();

		gspWaitForVBlank();
		
	}

	gfxExit();
	return 0;
}