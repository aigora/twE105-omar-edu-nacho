#include <stdio.h>
#include "GEC.h"
int main(){
	system("color 0f");
	int i,j;
	float t1,t2;
	for(j=1;j<=3;j++){
		printf("\n\n\n\n\n\n\t\t\t\t\t XXXXXX     XXXXXXX    XXXXX   \n\t\t\t\t\tXXXXXXXX    XXXXXXX   XXXXXXX  \n\t\t\t\t\tXX    XX    XX        XX   XX  \n\t\t\t\t\tXX          XXXX      XX\n\t\t\t\t\tXX  XXXX    XXXX      XX\n\t\t\t\t\tXX  XXXX    XX        XX\n\t\t\t\t\tXX    XX    XX        XX   XX\n\t\t\t\t\tXXXXXXXX    XXXXXXX   XXXXXXX\n\t\t\t\t\t XXXXX   X  XXXXXXX  X  XXXX   X\n");
		printf("\n\t\t\t\t\t\t    LOADING");
		for(i=1;i<=3;i++){
			printf(".");
			t2=t1=clock();
			while((t2-t1)/CLOCKS_PER_SEC<0.4)
			t2=clock();
		}
		system("cls");
	}	

	while(1){
		system("color 0f");
		printf("\n\n\n\n\n\n\t\t\t\t\t XXXXXX     XXXXXXX    XXXXX   \n\t\t\t\t\tXXXXXXXX    XXXXXXX   XXXXXXX  \n\t\t\t\t\tXX    XX    XX        XX   XX  \n\t\t\t\t\tXX          XXXX      XX\n\t\t\t\t\tXX  XXXX    XXXX      XX\n\t\t\t\t\tXX  XXXX    XX        XX\n\t\t\t\t\tXX    XX    XX        XX   XX\n\t\t\t\t\tXXXXXXXX    XXXXXXX   XXXXXXX\n\t\t\t\t\t XXXXX   X  XXXXXXX  X  XXXX   X\n");
		printf("\n\n\t\t\t\t\tQue te apetece jugar?\n\n\t\t\t\t\tL->Laberinto\n\n\t\t\t\t\tA->Ahorcado\n\n\t\t\t\t\tB->Buscamninas");
		switch(getch()){
			case 'L':
			case 'l':
				system("cls");
				Laberinto();
			break;
			case 'B':
			case 'b':
				system("cls");
				Buscaminas();
			break;
			case 'A':
			case 'a':
				system("cls");
				Ahorcado();
			break;
			default:
				system("cls");
					printf("\n\n\n\n\n\n\t\t\t\t\t XXXXXX     XXXXXXX    XXXXX   \n\t\t\t\t\tXXXXXXXX    XXXXXXX   XXXXXXX  \n\t\t\t\t\tXX    XX    XX        XX   XX  \n\t\t\t\t\tXX          XXXX      XX\n\t\t\t\t\tXX  XXXX    XXXX      XX\n\t\t\t\t\tXX  XXXX    XX        XX\n\t\t\t\t\tXX    XX    XX        XX   XX\n\t\t\t\t\tXXXXXXXX    XXXXXXX   XXXXXXX\n\t\t\t\t\t XXXXX   X  XXXXXXX  X  XXXX   X\n");
				printf("\n\n\t\t\t\t\t\tHasta la proxima\n\n");
				return 1;
		}
		system("cls");
	}
	return 0;
}

