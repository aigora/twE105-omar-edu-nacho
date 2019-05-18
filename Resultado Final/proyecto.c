#include <stdio.h>
#include "GEC.h"
void pintar_espacio(int veces);
int main(){
	system("color FD");
	int i,j;
	float t1,t2;
	//////Letrero////////
	for(i=1,j=0;i<70;i++){

		printf("\n\n\n\n\n\n\n\n"); 
		pintar_espacio(j); 
		printf(" XXXXXX     XXXXXXX    XXXXX\n");
		pintar_espacio(j);
		printf("XXXXXXXX    XXXXXXX   XXXXXXX  \n");
		pintar_espacio(j);
		printf("XX    XX    XX        XX   XX  \n");
		pintar_espacio(j);
		printf("XX          XXXX      XX\n");
		pintar_espacio(j);
		printf("XX  XXXX    XXXX      XX\n");
		pintar_espacio(j);
		printf("XX  XXXX    XX        XX\n");
		pintar_espacio(j);
		printf("XX    XX    XX        XX   XX\n");
		pintar_espacio(j);
		printf("XXXXXXXX    XXXXXXX   XXXXXXX\n");
		pintar_espacio(j);
		printf(" XXXXX   X  XXXXXXX  X  XXXX   X\n");
		t2=t1=clock();
		j++;
		while((t2-t1)/CLOCKS_PER_SEC<0.1){
			t2=clock();
		}
		system("cls");
	}
	
	getch();
	while(1){
		system("color FD");
		printf("\n\tQue te apetece jugar?\n\n\tL->Laberinto\n\tA->Ahorcado\n\tB->Buscamninas");
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
				printf("\n\nHasta la proxima");
				return 1;
		}
		system("cls");
	}
	return 0;
}
void pintar_espacio(int veces){
	int i;
	for(i=1;i<=veces;i++)
		printf(" ");
}

