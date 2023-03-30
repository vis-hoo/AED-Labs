#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPLAYERS 5

// Estructura del tipo Player.
typedef struct{
    char name[20];
    int health, level, strength, score;
} Player;
/*
* Health = Vida del jugador. Generados de manera aleatoria en un rango de 75 a 150.
* Level = Nivel del jugador. Generado de manera aleatoria en un rango de 1 a 3. Funcionaría
*    como un multiplicador del ataque. Es decir, si el ataque de un jugador es 10, y su nivel
*    es 3, entonces el daño causado es 30.
* Strength = Ataque del jugador. Generado de manera aleatoria en un rango de 1 a 10.
* Score = Puntaje del jugador. Inicia en 0 siempre, y se va sumando un valor dependiendo de
*    los ataques que haga y de los enemigos que mate. Por ejemplo, al atacar a otro jugador
*    se suma 5 puntos, pero si el ataque mató al jugador enemigo, entonces se suman 15.
*/

int playersPerTeam();
void initPlayer(Player *ptr, int i);
void printInfo(Player team[MAXPLAYERS], int ppt, int t);

int main(){
    srand(time(NULL));

    Player team1[MAXPLAYERS];
    Player team2[MAXPLAYERS];
    Player *ptr;

    int ppt = playersPerTeam();

    int i, j;
    for (i = 0; i < 2; i++){
        printf("\n\tEquipo %d\n", i + 1);
        for (j = 0; j < ppt; j++){
            if (i == 0) ptr = &team1[j];
            if (i == 1) ptr = &team2[j];
            initPlayer(ptr, j);
        }
    }
    printInfo(team1, ppt, 1);
    printInfo(team2, ppt, 2);

    return 0;
}

// Determina la cantidad de jugadores que habrá por equipo (de 1 a 5).
int playersPerTeam(){
    int a;
    printf("\n  Ingrese la cantidad de jugadores por equipo (maximo 5): ");
    while(1){
        scanf("%d", &a);
        if (a > 0 && a <= MAXPLAYERS) return a;
        else printf("*Intenta con un valor dentro del rango: ");
    }
}

// Inicializa los datos del jugador especificado en la posición del arreglo.
void initPlayer(Player *ptr, int i){
    printf("\n  Jugador %d\n", i + 1);
    printf(" Nombre: ");
    scanf("%s", ptr->name);
    ptr->health = (rand() % 76) + 75;
    ptr->level = (rand() % 3) + 1;
    ptr->strength = (rand() % 10) + 1;
    ptr->score = 0;
}

// Imprime en pantalla la información de los jugadores.
void printInfo(Player team[MAXPLAYERS], int ppt, int t){
    printf("\n\n*********************************************\n");
    printf("\n\tEquipo %d", t);
    int i;
    for (i = 0; i < ppt; i++){
        printf("\n\n\tJugador %d", i + 1);
        printf("\nNombre - %s", team[i].name);
        printf("\nSalud - %d", team[i].health);
        printf("\nNivel - %d", team[i].level);
        printf("\nFuerza - %d", team[i].strength);
        printf("\nPuntaje - %d", team[i].score);
    }
}