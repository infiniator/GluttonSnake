#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	int snakeStartX,snakeStartY,snakeEndX,snakeEndY;  //coordinates of the snake's start and end position
	int endGame = 0;  //set this flag if the game has ended
	int headDirection = 4;  //tells the direction in which the head of the snake is moving right now. 1=up, 2=down, 3=left, 4=right
	int tailDirection = 4;  //tells the direction in which the tail of the snake is moving right now. 1=up, 2=down, 3=left, 4=right
	int turnX[50],turnY[50];  //tells the coordinates at which the snake has started turning
	int turnDirection[50];  //tells the direction in which the turn is made
	int activeTurns=0;  //tells the no. of turns active right now
	int foodX,foodY;  //tells coordinates of food
	int counter;  //acts as a counter for the loops
	unsigned long int score = 0;
	char playerName[20];
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
	snakeStartX = getmaxx() / 2;
	snakeStartY = getmaxy() / 8;
	snakeEndX = snakeStartX - 25;
	snakeEndY = snakeStartY;
	foodX = rand() % 600;
	foodY = rand() % 320;
	foodX += 20;
	foodY += 20;
	//above four linesget the coordinates of the food on the screen, leaving 20 pixels from the borders unused. This can be removed in the patches
	while(endGame == 0)
	{
		//the whole code of running the game goes in here
		//next three lines draw the snake's advancement from the initial position
		if(activeTurns==0)
			line(snakeStartX,snakeStartY,snakeEndX,snakeEndY);
		else if(activeTurns>0)
		{
			line(turnX[0],turnY[0],snakeEndX,snakeEndY);
			for(counter = 1 ; counter < activeTurns - 1 ; counter++)
			{
				line(turnX[counter],turnY[counter],turnX[counter-1],turnY[counter-1]);
				line(turnX[counter+1],turnY[counter+1],turnX[counter],turnY[counter]);
			}
			line(snakeStartX,snakeStartY,turnX[activeTurns-1],turnY[activeTurns-1]);
		}
		snakeStartX += 3;
		snakeEndX += 3;
		putpixel(foodX-1,foodY-1,WHITE);
		putpixel(foodX+1,foodY-1,WHITE);
		putpixel(foodX+1,foodY+1,WHITE);
		putpixel(foodX-1,foodY+1,WHITE);
		putpixel(foodX,foodY-1,WHITE);
		putpixel(foodX,foodY+1,WHITE);
		putpixel(foodX-1,foodY,WHITE);
		putpixel(foodX+1,foodY,WHITE);
		putpixel(foodX,foodY,WHITE);
		if(snakeStartX >= getmaxx())
			endGame = 1;
		if(kbhit())  //a key has been pressed
		{
			char keyPress = getch();
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
					turnDirection[activeTurns-1]=1;
				else if(keyPress==80)
					turnDirection[activeTurns-1]=2;
				else if(keyPress==75)
					turnDirection[activeTurns-1]=3;
				else if(keyPress==77)
					turnDirection[activeTurns-1]=4;
			}
		}
		delay(50);  //can be kept dynamic incase we need to implement different difficulties of gameplay; will be included as a patch
		cleardevice();
	}
	closegraph();
	clrscr();
	printf("\n %s, your score is %lu",playerName,score);
	//code_ends
	getch();
	return 0;
}