#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

//**************************************************************
// BattleSimulator3DS_MAK.cpp
//
// Purpose: Fight for survival in this battle simulator. Press A to attack and hope you can win.
//
// Note: To run this, make it in terminal after CD-ing into the directory and then run it in Citra 3DS emulator. Google Citra 3DS Emulator for download instructions. Make sure to bind inputs in order to play the game.
//
// R1: 26-Jan-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************

int playerHp = 20;
int enemyHp = 20;

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	

		printf("\x1b[16;5HWelcome to the battle simulator. Fight to win.");
		printf("\x1b[30;16HPress A to begin...");

		while(true)
		{
			hidScanInput(); // scans for input
			u32 kDown = hidKeysDown(); // kDown = the keys that have been pressed down
			if (kDown & KEY_A) break; // breaks if a is pressed 		
		}
		
		consoleClear();
		
		while (true) 
		{
			if (playerHp <= 0 || enemyHp <= 0) break; 
			std::cout << "\x1b[2;5HYour HP: " << playerHp << std::endl;  
			std::cout << "\x1b[3;5HEnemy HP: " << enemyHp << std::endl; 
			printf("\x1b[16;20HPress A to Attack!"); 

			hidScanInput();
			u32 kDown = hidKeysDown();
			
			if (kDown & KEY_A)
			{	
				consoleClear();
				int playerAtk = rand() % 10;
				int enemyAtk = rand() % 10; 
			
				playerHp -= enemyAtk; 
				enemyHp -= playerAtk; 
		
				std::cout << "\x1b[27;16HYou lost " << enemyAtk << " HP"; 
				std::cout << "\x1b[29;16HThe enemy lost " << playerAtk << " HP"; 
			}		
		}
		
		consoleClear();
		std::cout << "\x1b[2;5HYour HP: " << playerHp << std::endl;  
		std::cout << "\x1b[3;5HEnemy HP: " << enemyHp << std::endl; 
		
		if (playerHp <= 0)
		{
			std::cout <<"\x1b[16;20HEnemy won!" <<"\x1b[30;16HPress Start to exit";
			printf("\x1b[30;16HPress Start to exit");
		} 
		else if (enemyHp <= 0)
		{
			std::cout <<"\x1b[16;20HYou Won!" <<"\x1b[30;16HPress A to continue";
			printf("\x1b[30;16HPress Start to exit");
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
