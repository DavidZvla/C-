/*
SNAKE! - code writer: David Zavala
 _____________________________________________________________________________________
|   ___    _____  _   _  _  ___       _______  _____  _   _  _____  _      _____      |
|  (  _`\ (  _  )( ) ( )(_)(  _`\    (_____  )(  _  )( ) ( )(  _  )( )    (  _  )     |
|  | | ) || (_) || | | || || | ) |        /'/'| (_) || | | || (_) || |    | (_) |     | 
|  | | | )|  _  || | | || || | | )      /'/'  |  _  || | | ||  _  || |  _ |  _  |     |
|  | |_) || | | || \_/ || || |_) |    /'/'___ | | | || \_/ || | | || |_( )| | | |     | 
|  (____/'(_) (_)`\___/'(_)(____/'   (_______)(_) (_)`\___/'(_) (_)(____/'(_) (_)     |
|_____________________________________________________________________________________|

SNAKE!

*/
//INCLUDES y Librerias.
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstdlib> 
#include <cstdio>  
#include <ctime>
#include <stdlib.h>

// definir controles. (Numero id de la tecla que se presionara)
#define ARRIBA     119 //w
#define ABAJO      115 //s
#define IZQUIERDA  97  //a
#define DERECHA    100 //d
#define ESC		   27  //esc

//VARIABLES
int cuerpo[200][2];
int n = 1;
int tam = 3;
int x = 10 , y = 12;
int dir = 3;
int cox = 30, coy = 15;
int speed = 100;
int score = 0;
int h = 1;
int rst = 0;
char tecla;

//FIN-VARIABLES

//FUNCIONES.
void gotoxy(int x, int y) //FUNCION PARA CREAR y UTILIZAR EL GOTOXY
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void pintar() // FUNCION PARA crear el escenario del juego.
{ 
	 
	 // Líneas dobles horizontales
     for(int i=2; i < 78; i++)
	 {
        gotoxy (i, 3); printf ("%c", 205);  // los ultimos números hacen referencia al código acsii
        gotoxy(i, 23); printf ("%c", 205);
     }
     //Líneas dobles verticales
     for(int v=4; v < 23; v++)
	 {
        gotoxy (2,v);  printf ("%c", 186);  // los ultimos números hacen referencia al código acsii
        gotoxy(77,v);  printf ("%c", 186);
     }
     // Esquinas dobles
     gotoxy  (2,3);    printf ("%c", 201);  // los ultimos números hacen referencia al código acsii
     gotoxy (2,23);    printf ("%c", 200);
     gotoxy (77,3);    printf ("%c", 187);
     gotoxy(77,23);    printf ("%c", 188);
}

void guardar_posicion()
{
	cuerpo [n][0] = x;
	cuerpo [n][1] = y;
	n++;
	if(n == tam) n = 1;
}

void dibujar_cuerpo() // funcion que dibuja el cuerpo en pantalla
{
	for(int i = 1 ;  i < tam ; i++)
	{
		gotoxy(cuerpo[i][0] , cuerpo[i][1]); printf("*");
	}
	
}

void borrar_cuerpo() // funcion que borra el cuerpo del sitio donde pasa...
{
	gotoxy(cuerpo[n][0] , cuerpo[n][1]); printf(" ");
}

void mover() // funcion que hace mover a la serpiente
{
	if(kbhit()) //kbhit = hot key hit. cuando se presiona una tecla
	{
		tecla = getch();
		switch(tecla)
		{
			case ARRIBA :
			if(dir != 2)
			dir = 1;
			break;
			case ABAJO :
			if(dir != 1)
			dir = 2;	
			break;
			case DERECHA :	
			if(dir != 4)
			dir = 3;
			break;
			case IZQUIERDA :
			if(dir != 3)
			dir = 4;
			break;	 
		}
	}
}

void crearcomida() // crea la comida para atrapar
{
	if(x == cox && y == coy)
	{
		cox = (rand()%73)+4; 
		coy = (rand()%19)+4;
		tam++;
		score += 10;
		gotoxy(cox,coy);
		printf("%c", 42);
	}
}

bool gameover() // funcion logica que retorna true o false
{
	if(y == 3 || y == 23 || x == 2 || x == 77) { rst = 3; return false; } // al tocar las coordenadas de las paredes el bucle del juego se detiene
	for(int j = tam -1 ; j > 0 ; j--) // for .. hace que si la serpiente se toca a si misma el bucle del juego se detiene
	{
		if(cuerpo[j][0] == x && cuerpo[j][1] == y)
		{
			rst =3;
			return false;
		}
		
	}
	return true;
}

bool Reiniciar()
{
	if(rst == 1 || rst == 0)
	{
		rst = 0;
		n = 1;
		tam = 3;
		x = 10; y = 12;
		dir = 3;
		cox = 30, coy = 15;
		speed = 100;
		score = 0;
		h = 1;
		return true;
	}
	else return false;
}

void puntaje()
{
	gotoxy(3,1); // coordenadas para imprimir el score
	printf("Score: %d", score); // esto imprime el score en pantalla
}

void creditos()
{
	gotoxy(3,25);
	printf("Escrito by David Zavala");
}

void change_speed()
{
	if(score == h*20)
	{
		speed -= 10;
		h++;
	}
}

int main() //Main
{	
	//setlocale(LC_ALL,"spanish"); // Esta funcion puede servir para mostrar caracteres en español. (en este juego no es necesaria)
		restart:
		pintar();
		gotoxy(cox,coy);
		printf("%c", 42);
		while(tecla != ESC && gameover())
		{
			borrar_cuerpo();
			guardar_posicion();
			dibujar_cuerpo();
			crearcomida();
			creditos();
			puntaje();
			change_speed();
			mover();
			mover();
			if(dir == 1) y--;
			if(dir == 2) y++;
			if(dir == 3) x++;
			if(dir == 4) x--;
			Sleep(speed);
		}
		if(!gameover() && !Reiniciar())
		{ 
			MessageBox(NULL,"Vaya... Parece que has perdido...\n\ncierra esta ventana para comenzar nuevamente o salir...","Perdiste!", MB_OK);
			gotoxy(3,28);
			printf("Deseas comenzar una nueva partida?\n\n1. si\n2. no\n\n> "); 
    		scanf("%i", &rst);
    		if(rst==1)
			{
				system("cls");
				rst = 0;
				Reiniciar();
				goto restart;
    		}
    		if(rst == 2)
    		{
    			system("cls");
    			gotoxy(3,28);
				printf("Puedes proceder a cerrar la ventana de juego.");
    		}
		}
		pintar();
		creditos();
		system("Pause>null");
		return 0;
}
