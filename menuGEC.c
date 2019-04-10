#include <stdio.h>
void main(){

	char opcion;
	system("COLOR 04");
	printf("Bienvenido a la Gaming Entertainment Center (GEC)\n");
	printf("Elige un juego para empezar:\n");
	
	printf("a. El Laberinto\n");
	printf("b. Ahorcado\n");
	printf("c. Hundir la flota\n");
	scanf("%c", &opcion);

	switch(opcion){

		case 'a': 
		case 'A':
			
		system("cls");
		printf("Bienvenido a El Laberinto\n");
		break;

		case 'b':
		case 'B':
		system("cls");
		printf("Bienvenido a Ahorcado\n");
		break;

	
		case 'c': 
		case 'C':
		system("cls");
		printf("Bienvenido a Hundir la flota\n");
		break;

		default:
		printf("Opcion incorrecta\n");

	}
	}
