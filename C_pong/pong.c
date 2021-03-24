#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

void refresh(int posL, int ballPosX, int ballPosY, int moveUp, int moveDown, int moveRight, int moveLeft, int posR, int MinusY, int PlusY, int MinusX, int PlusX){
	usleep(100000); //microseconds
	int i,j;
	
	system("@cls||clear");
	
	for(i=0;i<=31;i++){
		for(j=0;j<=70;j++){
			//Add left bar
			if(i==posL-2 || i==posL-1 || i==posL || i==posL+1 || i==posL+2){
				if(j==0)
					printf("*");
			}
			//Check if second bar is at the same row with the ball
			if(i!=ballPosY){
				if(i==posR-2 || i==posR-1 || i==posR || i==posR+1 || i==posR+2){
					if(j==65){
						printf("*");
					}
					else{
						printf(" ");
					}
					if(i==posL-2 || i==posL-1 || i==posL || i==posL+1 || i==posL+2){
						if(j==2)
							printf("\b");
					}
				}
			}
			else if(i==ballPosY){
				if(i==posR-2 || i==posR-1 || i==posR || i==posR+1 || i==posR+2){
					if(j<ballPosX){
						printf(" ");
					}
					else if(j>ballPosX){
						if(j<65)
							printf(" ");
						else if(j==65)
							printf("*");
					}
					else if(j==ballPosX){
						printf("*");
					}
					if(i==posL-2 || i==posL-1 || i==posL || i==posL+1 || i==posL+2){
						if(j==ballPosX+1)
							printf("\b");
					}
				}
				else{
					if(j==ballPosX)
						printf("*");
					else
						printf(" ");
				}
			}
			
			if(i==31){
				printf("-");
			}
/*			if(i==ballPosY && j==ballPosX){
				if(i==posL-1 || i==posL || i==posL+1)
					printf("\b%c",'*');
				else
					printf("%c",'*');
			}
			else
				printf("%c", ' ');
*/		}
		printf("\n");
	}
	if(ballPosX<=0)
		printf("Left Player Lost.");
	else if(ballPosX>=65)
		printf("Right Player Lost.");
	//MOVEMENT
	if(moveUp){
		ballPosY=ballPosY-MinusY;
	}
	else if(moveDown){
		ballPosY=ballPosY+PlusY;
	}
	if(moveRight){
		ballPosX=ballPosX+PlusX;
	}
	else if(moveLeft){
		ballPosX=ballPosX-MinusX;
	}
	
	if(ballPosY==0 || ballPosY==1){
		moveUp=0;
		moveDown=1;
	}
	else if(ballPosY==28 || ballPosY == 29){
		moveUp=1;
		moveDown=0;
	}
	
	if(ballPosX<=2 && (posL==ballPosY-2 || posL==ballPosY-1 || posL==ballPosY || posL==ballPosY+1 || posL==ballPosY+2)){
		moveLeft = 0;
		moveRight = 1;
		if(posL==ballPosY-2){
			MinusY = 2;
			PlusY = 2;
			
			moveUp = 0;
			moveDown = 1;
		}
		else if(posL==ballPosY-1){
			MinusY = 1;
			PlusY = 1;
			
			moveUp = 0;
			moveDown = 1;
		}
		else if(posL==ballPosY){
			MinusY = 0;
			PlusY = 0;
			
			moveUp = 0;
			moveDown = 0;
		}
		else if(posL==ballPosY+1){
			MinusY = 1;
			PlusY = 1;
			
			moveUp = 1;
			moveDown = 0;
		}
		else if(posL==ballPosY+2){
			MinusY = 2;
			PlusY = 2;
			
			moveUp = 1;
			moveDown = 0;
		}
	}
	if(ballPosX>=62 && (posR==ballPosY-2 || posR==ballPosY-1 || posR==ballPosY || posR==ballPosY+1 || posR==ballPosY+2)){
		moveLeft = 1;
		moveRight = 0;
		if(posR==ballPosY-2){
			MinusY = 2;
			PlusY = 2;
			
			moveUp = 0;
			moveDown = 1;
		}
		else if(posR==ballPosY-1){
			MinusY = 1;
			PlusY = 1;
			
			moveUp = 0;
			moveDown = 1;
		}
		else if(posR==ballPosY){
			MinusY = 0;
			PlusY = 0;
			
			moveUp = 0;
			moveDown = 0;
		}
		else if(posR==ballPosY+1){
			MinusY = 1;
			PlusY = 1;
			
			moveUp = 1;
			moveDown = 0;
		}
		else if(posR==ballPosY+2){
			MinusY = 2;
			PlusY = 2;
			
			moveUp = 1;
			moveDown = 0;
		}
	}
	printf("%d %d", ballPosX, ballPosY);
	//END OF MOVEMENT
	while(!kbhit()){
		refresh(posL, ballPosX, ballPosY, moveUp, moveDown, moveRight, moveLeft, posR, MinusY, PlusY, MinusX, PlusX);
	}
	int ch = getch();
	if(ch==97){
		if(posL>2)
			posL-=1;
	}
	else if(ch==115){
		if(posL>2)
			posL-=2;
	}
	else if(ch==122){
		if(posL<27)
			posL+=1;
	}
	else if(ch==120){
		if(posL<27)
			posL+=2;
	}
	if(ch==39){
		if(posR>2)
			posR-=1;
	}
	else if(ch==59){
		if(posR>2)
			posR-=2;
	}
	else if(ch==46){
		if(posR<27)
			posR+=2;
	}
	else if(ch==47){
		if(posR<27)
			posR+=1;
	}
//	printf("%d",ch);
	refresh(posL, ballPosX, ballPosY, moveUp, moveDown, moveRight, moveLeft, posR, MinusY, PlusY, MinusX, PlusX);
}

int main(int argc, char** argv){
	char pixels[30][70];
	int posL; //2-27
	int posR; //2-27
	int ballPosX;
	int ballPosY;
	
	posL = 2;
	posR = 2;
	ballPosX = 16;
	ballPosY = 26;
	
	char c;
	printf("Type s and press enter to begin.\n\n\n");
	printf("Controls:\n\n");
	printf("Left Player:\t\tRight Player:\n");
	printf("Up: a, Down: z\t\tUp: \', Down: /\n\n");
	while((c=getchar())!='s'){
		
	}
	refresh(posL, ballPosX, ballPosY, 1,0,0,1, posR, 1, 1, 1, 1);
}