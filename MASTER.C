#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//Release 1.1 is ready, but some bugs still remain unsolved... Some of them are:
//1. snake does not die when it clashes with his body
//2. Sometimes the game gets erratic where the first line grows indefinitely whereas the last line is drawn in a random manner
int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	int snakeStartX,snakeStartY,snakeEndX,snakeEndY;  //coordinates of the snake's start and end position
	int endGame = 0;  //set this flag if the game has ended
	int headDirection = 4;  //tells the direction in which the head of the snake is moving right now. 1=up, 2=down, 3=left, 4=right
	int tailDirection = 4;  //tells the direction in which the tail of the snake is moving right now. 1=up, 2=down, 3=left, 4=right
	int turnX[100],turnY[100];  //tells the coordinates at which the snake has started turning
	int turnDirection[100];  //tells the direction in which the turn is made
	int activeTurns = 0;  //tells the no. of turns active right now
	int foodX,foodY;  //tells coordinates of food
	int counter;  //acts as a counter for the loops
	int keyFlag=0;  //prevents rapid pressing of keys and facilitates processing
	unsigned long int score = 0;
	char playerName[20];
	char keyPress;  //logs the key pressed by the player
	clrscr();
	printf("\n Enter your name: ");
	gets(playerName);
	clrscr();
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}
	setcolor(getmaxcolor());
	//code_starts
	//next four lines depict the initial position of the snake
	snakeStartX = getmaxx() / 8;
	snakeStartY = getmaxy() / 2;
	snakeEndX = snakeStartX - 50;
	snakeEndY = snakeStartY;
	foodX = rand() % (getmaxx() - 40);
	foodY = rand() % (getmaxy() - 40);
	foodX += 20;
	foodY += 20;
	//above four lines get the coordinates of the food on the screen, leaving 20 pixels from the borders unused. This can be removed in the patches
	while(endGame == 0)
	{
		//the whole code of running the game goes in here
		//next three lines draw the snake's advancement from the initial position
		if(activeTurns == 0)
			line(snakeStartX,snakeStartY,snakeEndX,snakeEndY);
		else if(activeTurns > 2)
		{
			line(turnX[0],turnY[0],snakeEndX,snakeEndY);
			for(counter = 1 ; counter < activeTurns - 1 ; counter++)
			{
				line(turnX[counter],turnY[counter],turnX[counter - 1],turnY[counter - 1]);
				line(turnX[counter + 1],turnY[counter + 1],turnX[counter],turnY[counter]);
			}
			line(snakeStartX,snakeStartY,turnX[activeTurns - 1],turnY[activeTurns - 1]);
		}
		else if(activeTurns == 2)
		{
			line(turnX[0],turnY[0],snakeEndX,snakeEndY);
			line(snakeStartX,snakeStartY,turnX[1],turnY[1]);
			line(turnX[0],turnY[0],turnX[1],turnY[1]);
		}
		else if(activeTurns==1)
		{
			line(turnX[0],turnY[0],snakeEndX,snakeEndY);
			line(snakeStartX,snakeStartY,turnX[0],turnY[0]);
		}
		//next nine lines draw food for our snake
		putpixel(foodX-1,foodY-1,WHITE);
		putpixel(foodX+1,foodY-1,WHITE);
		putpixel(foodX+1,foodY+1,WHITE);
		putpixel(foodX-1,foodY+1,WHITE);
		putpixel(foodX,foodY-1,WHITE);
		putpixel(foodX,foodY+1,WHITE);
		putpixel(foodX-1,foodY,WHITE);
		putpixel(foodX+1,foodY,WHITE);
		putpixel(foodX,foodY,WHITE);
		//the else if ladder given below will update the score and increase the size of the snake. the break has been made to shorten the long condition
		if((snakeStartX==foodX && snakeStartY==foodY) || (snakeStartX==foodX && snakeStartY==foodY-1) || (snakeStartX==foodX && snakeStartY==foodY+1))
		{
			if(headDirection==1)
			{
				snakeStartY-=3;
			}
			else if(headDirection==2)
			{
				snakeStartY+=3;
			}
			else if(headDirection==3)
			{
				snakeStartX-=3;
			}
			else if(headDirection==4)
			{
				snakeStartX+=3;
			}
			score++;
			foodX = rand() % (getmaxx()-40);
			foodY = rand() % (getmaxy()-40);
			foodX += 20;
			foodY += 20;
			//above four lines get the coordinates of the food on the screen, leaving 20 pixels from the borders unused. This can be removed in the patches
		}
		else if((snakeStartX==foodX-1 && snakeStartY==foodY-1) || (snakeStartX==foodX-1 && snakeStartY==foodY+1) || (snakeStartX==foodX+1 && snakeStartY==foodY+1))
		{
			if(headDirection==1)
			{
				snakeStartY-=3;
			}
			else if(headDirection==2)
			{
				snakeStartY+=3;
			}
			else if(headDirection==3)
			{
				snakeStartX-=3;
			}
			else if(headDirection==4)
			{
				snakeStartX+=3;
			}
			score++;
			foodX = rand() % (getmaxx()-40);
			foodY = rand() % (getmaxy()-40);
			foodX += 20;
			foodY += 20;
			//above four lines get the coordinates of the food on the screen, leaving 20 pixels from the borders unused. This can be removed in the patches
		}
		else if((snakeStartX==foodX+1 && snakeStartY==foodY-1) || (snakeStartX==foodX+1 && snakeStartY==foodY) || (snakeStartX-1==foodX && snakeStartY==foodY))
		{
			if(headDirection==1)
			{
				snakeStartY-=3;
			}
			else if(headDirection==2)
			{
				snakeStartY+=3;
			}
			else if(headDirection==3)
			{
				snakeStartX-=3;
			}
			else if(headDirection==4)
			{
				snakeStartX+=3;
			}
			score++;
			foodX = rand() % (getmaxx()-40);
			foodY = rand() % (getmaxy()-40);
			foodX += 20;
			foodY += 20;
			//above four lines get the coordinates of the food on the screen, leaving 20 pixels from the borders unused. This can be removed in the patches
		}
		if(snakeStartX >= getmaxx() || snakeStartX<=0 || snakeStartY>=getmaxy() || snakeStartY<=0)
			endGame = 1;
		if(tailDirection==1)
		{
			snakeEndY--;
		}
		else if(tailDirection==2)
		{
			snakeEndY++;
		}
		else if(tailDirection==3)
		{
			snakeEndX--;
		}
		else if(tailDirection==4)
		{
			snakeEndX++;
		}
		if(headDirection==1)
		{
			snakeStartY--;
		}
		else if(headDirection==2)
		{
			snakeStartY++;
		}
		else if(headDirection==3)
		{
			snakeStartX--;
		}
		else if(headDirection==4)
		{
			snakeStartX++;
		}
		if(snakeEndX == turnX[0] && snakeEndY==turnY[0])
		{
			tailDirection=turnDirection[0];
			for(counter=1;counter<activeTurns;counter++)
			{
				turnDirection[counter-1]=turnDirection[counter];
				turnX[counter-1]=turnX[counter];
				turnY[counter-1]=turnY[counter];
			}
			activeTurns--;
		}
		if(kbhit() && keyFlag==0)  //a key has been pressed
		{
			keyFlag=1;
			keyPress = getch();
			if(keyPress == 27)
			{
				endGame = 1;
				continue;
			}
			if(keyPress == 0)  //it's an arrow key
			{
				keyPress = getch();
				activeTurns++;
				turnX[activeTurns-1]=snakeStartX;
				turnY[activeTurns-1]=snakeStartY;
				if(keyPress==72)
				{
					if(headDirection==2)
					{
						continue;
					}
					headDirection=1;
					turnDirection[activeTurns-1]=1;
				}
				else if(keyPress == 80)
				{
					if(headDirection==1)
					{
						continue;
					}
					headDirection=2;
					turnDirection[activeTurns-1]=2;
				}
				else if(keyPress == 75)
				{
					if(headDirection==4)
					{
						continue;
					}
					headDirection = 3;
					turnDirection[activeTurns - 1] = 3;
				}
				else if(keyPress == 77)
				{
					if(headDirection==3)
					{
						continue;
					}
					headDirection = 4;
					turnDirection[activeTurns - 1] = 4;
				}
			}
		}
		if(!kbhit())
		{
			keyFlag=0;
		}
		delay(10);  //can be kept dynamic incase we need to implement different difficulties of gameplay; will be included as a patch
		cleardevice();
	}
	closegraph();
	clrscr();
	printf("\n %s, your score is %lu",playerName,score);
	//code_ends
	getch();
	return 0;
}
