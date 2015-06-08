#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	int snakeStartX,snakeStartY,snakeEndX,snakeEndY;  //coordinates of the snake's start and end position
	int endGame=0;  //set this flag if the game has ended
	int headDirection=4;  //tells the direction in which the head of the snake is moving right now. 1=up, 2=down, 3=left, 4=right
	int tailDirection=4;  //tells the direction in which the tail of the snake is moving right now. 1=up, 2=down, 3=left, 4=right
	int turnX[50],turnY[50];  //tells the coordinates at which the snake has started turning
	int activeTurns;  //tells the no. of turns active right now
	unsigned long int score=0;
	char playerName[20];
	clrscr();
	printf("\n Enter your name:");
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
	snakeStartX=getmaxx()/2;
	snakeStartY=getmaxy()/8;
	snakeEndX=snakeStartX-25;
	snakeEndY=snakeStartY;
	while(endGame==0)
	{
		//the whole code of running the game goes in here
		line(snakeStartX,snakeStartY,snakeEndX,snakeEndY);
		snakeStartX+=3;
		snakeEndX+=3;
		if(snakeStartX>=getmaxx())
			endGame=1;
		if(kbhit())  //a key has been pressed
		{
			char keyPress=getch();
			if(keyPress==27)
			{
				endGame=1;
				continue;
			}
			if(keyPress==0)  //it's an arrow key
			{
				keyPress=getch();

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