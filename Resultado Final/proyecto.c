
#include "GEC.h"
int main(){
	system("color FD");
	int i;
	printf("\nBienvenido a GEC");
	getch();
	while(1){
		printf("\nQue te apetece jugar?\n\nL->Laberinto\nA->Ahorcado\nB->Buscamninas");
		switch(getch()){
			case 'L':
			case 'l':
				system("cls");
				laberinto();
			break;
			case 'B':
			case 'b':
				system("cls");
				buscaminas();
			break;
			case 'A':
			case 'a':
				system("cls");
				Ahorcado();
			break;
			default:
				return 0;
		}
		system("cls");
	}
	return 0;
}
