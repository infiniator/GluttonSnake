#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
//Release 1.2 is ready, but some bugs still remain unsolved... Some of them are:
//Sometimes the game gets erratic where the first line grows indefinitely whereas the last line is drawn in a random manner
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
char playerName[20];
char keyPress;  //logs the key pressed by the player
unsigned long int score = 0;
void scoreCalc();
void gameOver();
void moveSnake();
void drawSnake();
void drawFood();
void keyListener();
int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
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
		drawSnake();
		drawFood();
		scoreCalc();
		moveSnake();
		keyListener();
		gameOver();
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
void gameOver()
{
	if(headDirection==1)
	{
		if(getpixel(snakeStartX,snakeStartY-1)==WHITE)
		{
			endGame=1;
			return;
		}
	}
	else if(headDirection==2)
	{
		if(getpixel(snakeStartX,snakeStartY+1)==WHITE)
		{
			endGame=1;
			return;
		}
	}
	else if(headDirection==3)
	{
		if(getpixel(snakeStartX-1,snakeStartY)==WHITE)
		{
			endGame=1;
			return;
		}
	}
	else if(headDirection==4)
	{
		if(getpixel(snakeStartX+1,snakeStartY)==WHITE)
		{
			endGame=1;
			return;
		}
	}
	if(snakeStartX >= getmaxx() || snakeStartX<=0 || snakeStartY>=getmaxy() || snakeStartY<=0)
	{
		endGame = 1;
		return;
	}
}
void moveSnake()
{
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
}
void scoreCalc()
{
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
}
void drawSnake()
{
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
}
void keyListener()
{
	if(kbhit() && keyFlag==0)  //a key has been pressed
	{
		keyFlag=1;
		keyPress = getch();
		if(keyPress == 27)
		{
			endGame = 1;
			return;
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
					return;
				}
				headDirection=1;
				turnDirection[activeTurns-1]=1;
			}
			else if(keyPress == 80)
			{
				if(headDirection==1)
				{
					return;
				}
				headDirection=2;
				turnDirection[activeTurns-1]=2;
			}
			else if(keyPress == 75)
			{
				if(headDirection==4)
				{
					return;
				}
				headDirection = 3;
				turnDirection[activeTurns - 1] = 3;
			}
			else if(keyPress == 77)
			{
				if(headDirection==3)
				{
					return;
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
}
void drawFood()
{
	//next nine lines draw food for our snake
	putpixel(foodX-1,foodY-1,BLUE);
	putpixel(foodX+1,foodY-1,BLUE);
	putpixel(foodX+1,foodY+1,BLUE);
	putpixel(foodX-1,foodY+1,BLUE);
	putpixel(foodX,foodY-1,BLUE);
	putpixel(foodX,foodY+1,BLUE);
	putpixel(foodX-1,foodY,BLUE);
	putpixel(foodX+1,foodY,BLUE);
	putpixel(foodX,foodY,BLUE);
}