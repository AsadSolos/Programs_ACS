#include <3ds.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

//**************************************************************
// Snake3DS
//
// Purpose: Popular game Snake but for the Nintendo 3DS
//
// Note: To run this, make it in terminal after CD-ing into the directory and then run it in Citra 3DS emulator. Google Citra 3DS Emulator for download instructions. Make sure to bind inputs in order to play the game.
//
// R1: 1-Apr-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************

int width = 400;
int height = 240;
int snakeHeadX, snakeHeadY;
int fruitCordX, fruitCordY;
int x, y, x1, y1;
int playerScore;
int snakeTailLength;
bool isGameOver;
int direction = 0; //0 not moving, 1 up, 2 down, 3 right, 4 left

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
void GameInit() //Initializes game
{
	isGameOver = false;
	snakeHeadX = width / 2;
	snakeHeadY = height / 2;
	time_t* rngSeed = (0);
	srand(time(rngSeed));
	fruitCordX = rand() % width;
	fruitCordY = rand() % height;
	x = fruitCordX + 1;
	y = fruitCordY + 1;
	x1 = fruitCordX - 1;
	y1 = fruitCordY - 1;
	playerScore = 0;
}
void UpdateGame()
{
	if ((snakeHeadX == fruitCordX || snakeHeadX == x || snakeHeadX == x1) && (snakeHeadY == fruitCordY || snakeHeadY == y || snakeHeadY == y1))
	{
		time_t* rngSeed = (0);
		srand(time(rngSeed));
		playerScore++;
		fruitCordX = rand() % width;
		fruitCordY = rand() % height;
		x = fruitCordX + 1;
		y = fruitCordY + 1;
		x1 = fruitCordX - 1;
		y1 = fruitCordY - 1;
		snakeTailLength++;
	}
}
/*	switch (sDir)
	{
		case LEFT:
			snakeHeadX--;
			break;
		case RIGHT:
			snakeHeadX++;
			break;
		case UP:
			snakeHeadY--;
			break;
		case DOWN:
			snakeHeadY++;
			break;
	}*/
int main(int argc, char **argv)
{
	gfxInitDefault(); //Initializes graphics service with default settings
	consoleInit(GFX_BOTTOM, NULL); //Initialize console on bottom screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	//The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns
	printf("\x1b[2;0H Snake for the 3DS!");
	printf("\x1b[3;0H Use the DPad to move the snake.");
	printf("\x1b[4;0H Press Start at any time to Exit.");
	consoleInit(GFX_TOP, NULL);



	// Main loop
	GameInit();
	while (aptMainLoop())
	{
		hidScanInput();//Scan all the inputs. This should be done once for each frame
		u32 kDown = hidKeysDown(); //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kHeld = hidKeysHeld();
		u8* topScreen = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL); //gets Frame Buffer for top screen each frame. GFX_LEFT doesn't matter, as using both GFX_RIGHT and GFX_LEFT would result in 3D which is not needed in this case
		/*for (int i = 0; i++; i<= width)
		{
			for (int j = 0; j++; j<= height)
			{

			}
		}*/
		if (kDown & KEY_START) 
		{
			break; // break in order to return to hbmenu
		}
		if (direction == 1)
		{
			snakeHeadY--;
		}
		if (direction == 2)
		{
			snakeHeadY++;
		}
		if (direction == 3)
		{
			snakeHeadX++;
		}
		if (direction == 4)
		{
			snakeHeadX--;
		}
			for(int i = 0; i < width + 1; i++)
			{
				thickPixel(topScreen, i, 0, 160, 32, 240); //Draws purple boundary on the top of screen
				thickPixel(topScreen, i, 237, 160, 32, 240); //Draws purple boundary on the bottom of screen
			}
			for(int i = 0; i <= height; i++)
			{
				for(int j = 0; j <= width; j++)
				{
					if(j == 0 || j == width - 3)
					{
						thickPixel(topScreen, j, i, 160, 32, 240); //Draws purple boundaries on sides of screen
					}
					if (i == snakeHeadY && j == snakeHeadX)
					{
						thickPixel(topScreen, j, i, 31, 171, 73); //Draws the snake's head
					}
					else if(i == fruitCordY && j == fruitCordX)
					{
						thickPixel(topScreen, j, i, 204, 10, 0);
					}
				}
			}
			for(int i = 0; i < width + 1; i++)
			{
				if(snakeHeadX == i && (snakeHeadY == 0 || snakeHeadY == 240))
				{
					snakeHeadX = 99999999999; //sends the snake really far away bc I'm too lazy to find a way to actually kill the snake
					snakeHeadY = 99999999999; // the snake lives on!!!
					printf("\x1b[2;0H You Lose!");
					printf("\x1b[3;0H Your score:"); //ask jacob how to fix this
					printf("\x1b[4;0H Press start to exit");
				}
			}
			for(int i = 0; i <= height; i++)
			{
				if((snakeHeadX == 0 || snakeHeadX == 400) && snakeHeadY == i)
				{
					snakeHeadX = 99999999999;
					snakeHeadY = 99999999999; 
					printf("\x1b[2;0H You Lose!");
					printf("\x1b[3;0H Your score:"); //ask jacob how to fix this
					printf("\x1b[4;0H Press start to exit");
				}
			}
		UpdateGame();
		hidScanInput();	
		if (kHeld & KEY_DLEFT)
		{
			if (direction != 3)
			{
				direction = 4;
			}
		}
		if(kHeld & KEY_DRIGHT)
		{
			if (direction !=4)
			{
				direction = 3;
			}
			
		}
		if(kHeld & KEY_DUP)
		{
			if (direction != 2)
			{
				direction = 1;
			}
			
		}
		if(kHeld & KEY_DDOWN)
		{
			if (direction != 1)
			{
				direction = 2;
			}
		}
		
			

		gfxFlushBuffers(); // Flush and swap framebuffers
		gfxSwapBuffers();
		gspWaitForVBlank(); //Wait for VBlank
	}

	gfxExit(); //Exits graphics service
	return 0;
}
