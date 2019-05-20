#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define filas_totales 8
#define columnas_totales 8



char tabla[filas_totales][columnas_totales];

int main (int argc,char **argv) {
  int jugador;
  int total_juegos;
  total_juegos = 0;
//iniciar tabla
	int i,j;
	for (i = 0 ; i <= filas_totales; i++){
		for (j = 0 ; j <= columnas_totales; j++){
			tabla[i][j]=' ';
		}
	}
		

  do {
    if (total_juegos % 2 == 0)
      jugador = 0;
    else
      jugador = 1;
   
    total_juegos++;
    
    mostrar_tablero();
   
    if (juego(jugador)==0) {
      printf("Jugada incorrecta.\n\n");
      system("pause");
    }
  } while(comprobar()==-1);

  mostrar_tablero();
  
  if (comprobar()==1)
  
    printf("Has ganado!!\n\n");
    
  else
  
  printf("El ordenador ha ganado!!\n\n");
  
  getchar();
}



int juego(int eleccion){
	int i;
	char posicion;
	int fila, columna;
	int resultado=1;
	
	if(eleccion==0){
		posicion='0';
		
	 do {
      if (resultado==0) printf("Jugada incorrecta.\n");
      printf("\n");
      printf("Introduce la columna: ");
      scanf("%i",&columna);
      
      i=filas_totales-1;
      
      if (tabla[filas_totales-1][columna]!=' ') {
        while (i < filas_totales && (tabla[i][columna]=='X' || tabla[i][columna]=='0'))
          i--;
      }
      
      fila=i;
      
      resultado=juego_correcto(fila,columna);
      
    } while(resultado==0);
	}else {
		
    posicion='X';
    do {
      columna=generar_numero();
      i = filas_totales-1;
      if (tabla[filas_totales-1][columna]!=' ') {
      	
        while (i < filas_totales && (tabla[i][columna]=='X' || tabla[i][columna]=='0'))
        
          i--;
      }
      
      fila=i;
      
      resultado=juego_correcto(fila,columna);
    } while(resultado==0);
  }

  if (resultado==1) tabla[fila][columna]=posicion;
  return resultado;
}

int mostrar_tablero() {
  int i,j;
  int posicion;

  system("cls");
  printf("\n");
  


  printf("\n");

  for(i=0;i<filas_totales;i++) {
    printf(" ");
    if (i==0)
      printf(" ");
    else if (i==1)
      printf(" ");
    else
      printf(" ");
     
    printf(" %d  ",i);
   
    for(j=0;j<columnas_totales;j++) {
      printf(" ");
      printf("%c",tabla[i][j]);
      printf("  ");
    }
    printf(" ");
    if (i==0) printf("\n  ");
    else if (i==1) printf("\n  ");
    else printf("\n  ");
   
    printf("  ");
    for(j=0;j<columnas_totales+1;j++) printf("    ");
    printf("\n");
  }
  printf("       ");
  for(j=0;j<columnas_totales;j++)
   printf("%d   ",j);
  
  printf("\n");
}

	
int juego_correcto(int fila, int columna) {
  int juego_correcto;
  juego_correcto = 1;
  if (fila >= filas_totales || fila < 0 || columna >= columnas_totales || columna < 0) juego_correcto = 0;
  if (juego_correcto==1) {
    if (tabla[fila][columna]=='0' || tabla[fila][columna]=='X') juego_correcto = 0;
  }

  if (juego_correcto == 1) {
  	
    if (fila!=filas_totales-1 && tabla[fila+1][columna]==' '){
    	
	juego_correcto=0;
	
	}
  }

  return juego_correcto;
}

int generar_numero() {
  int numero;

  srand(time(NULL));
  numero=rand() % columnas_totales; //Devuelve un número entre 0 y COLUMNAS-1, porque al devolver el resto, este nunca puede ser superior a COLUMNAS-1.
  return numero;
}

int comprobar() {
  int i,j; //Para el for, para recorrer el tablero
  int ganador; // -1: no gana nadie, 1: gana humano, 0: gana máquina
  ganador = -1;

  //Comprobar si hay cuatro en línea en horizontal
  for (i=0 ; i < filas_totales ; i++) {
    for (j=0 ; j < columnas_totales-3 ; j++) {
      if (tabla[i][j]=='X' && tabla[i][j+1]=='X' && tabla[i][j+2]=='X' && tabla[i][j+3]=='X'){
      	ganador=0;
	  }
        
      else if (tabla[i][j]=='0' && tabla[i][j+1]=='0' && tabla[i][j+2]=='0' && tabla[i][j+3]=='0'){
      	ganador=1;
	  }
        
    }
    
  }
  
  if (ganador == -1) {
    //Comprobar si hay cuatro en línea en vertical
    for (i = 0 ; i < filas_totales-3 ; i++) {
    	
      for( j = 0 ; j < columnas_totales ; j++) {
        if (tabla[i][j]=='X' && tabla[i+1][j]=='X' && tabla[i+2][j]=='X' && tabla[i+3][j]=='X'){
          ganador = 0;	
		}
          
        else if (tabla[i][j]=='0' && tabla[i+1][j]=='0' && tabla[i+2][j]=='0' && tabla[i+3][j]=='0'){
        	ganador = 1;
		}
          
      }
    }
  }

  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en diagonal 1
    for (i = 0 ; i< filas_totales ; i++) {
      for (j = 0 ; j < columnas_totales ; j++) {
        if (i+3 < filas_totales && j+3 < columnas_totales) {
          if (tabla[i][j]=='X' && tabla[i+1][j+1]=='X' && tabla[i+2][j+2]=='X' && tabla[i+3][j+3]=='X')
            ganador = 0;
          else if (tabla[i][j]=='0' && tabla[i+1][j+1]=='0' && tabla[i+2][j+2]=='0' && tabla[i+3][j+3]=='0')
            ganador = 1;
        }
        
      }
    }
    
  }

  if (ganador == -1) {
    //Comprobar si hay cuatro en línea en diagonal 2
    for (i = 0 ; i < filas_totales ; i++) {
      for (j = 0 ; j < columnas_totales ; j++) {
        if (i+3 < filas_totales && j-3 >= 0) {
          if (tabla[i][j]=='X' && tabla[i+1][j-1]=='X' && tabla[i+2][j-2]=='X' && tabla[i+3][j-3]=='X')
            ganador = 0;
          else if (tabla[i][j]=='0' && tabla[i+1][j-1]=='0' && tabla[i+2][j-2]=='0' && tabla[i+3][j-3]=='0')
            ganador = 1;
        }
      }
    }
  }
  return ganador;
}

