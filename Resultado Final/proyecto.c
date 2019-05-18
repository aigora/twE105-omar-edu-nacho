#include <stdio.h>
//#include "GEC.h"

int main(){
	system("color FD");
	int i;
	printf("\n\tBienvenido a GEC");
	getch();
	while(1){
		system("color FD");
		printf("\n\tQue te apetece jugar?\n\n\tL->Laberinto\n\tA->Ahorcado\n\tB->Buscamninas");
		switch(getch()){
			case 'L':
			case 'l':
				system("cls");
		//		Laberinto();
			break;
			case 'B':
			case 'b':
				system("cls");
		//		Buscaminas();
			break;
			case 'A':
			case 'a':
				system("cls");
		//		Ahorcado();
			break;
			default:
				return 1;
		}
		system("cls");
	}
	return 0;
}

