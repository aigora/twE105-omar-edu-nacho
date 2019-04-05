#include <stdio.h>
#include <stdlib.h>

void main(){
		int opcion;
	printf("Bienvenido a la Gaming Entertainment Center (GEC)\n");
	
printf("1. El Laberinto\n");
	printf("2. Ahorcado\n");
	printf("3. Undir la flota\n");
	
	printf("Elige un juego para empezar: ");
	scanf("%i", &opcion);

	printf("1. El Laberinto\n");
	printf("2. Ahorcado\n");
	printf("3. Undir la flota\n");
	
	
	switch(opcion){
		
		case '1': 
		system("cls");
		printf("Bienvenido a El Laberinto\n");
		break;
		
		case '2':
		system("cls");
		printf("Bienvenido a Ahorcado\n");
		break;
		
		case '3': 
		system("cls");
		printf("Bienvenido a Undir la flota\n");
		break;
		default:
		printf("Opcion incorrecta\n");
	}
	
	
	
	
}
