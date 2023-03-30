#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

#pragma region Declaración de las funciones
int playersPerTeam();
void initPlayer(Player *ptr, int i);
void printTeams(Player team[MAXPLAYERS], int ppt, int t);
void gameLoop(Player team1[MAXPLAYERS], Player team2[MAXPLAYERS], Player *ptr, int ppt);
int intInput(char *msg, int min, int max);
Player * selectPlayer(Player team[MAXPLAYERS], int ppt, int t);
int playerMenu();
void printStats(Player *ptr);
void winner(Player team1[MAXPLAYERS], Player team2[MAXPLAYERS], int ppt);
#pragma endregion

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
    printf("\n\n*******************************************************\n");
    printTeams(team1, ppt, 1);
    printTeams(team2, ppt, 2);
    printf("\n\n*******************************************************\n");

    gameLoop(team1, team2, ptr, ppt);

    printf("*******************************************************\n");
    printTeams(team1, ppt, 1);
    printTeams(team2, ppt, 2);
    printf("\n\n*******************************************************\n");

    winner(team1, team2, ppt);
    return 0;
}

// Determina la cantidad de jugadores que habrá por equipo (de 1 a 5).
int playersPerTeam(){
    int a;
    printf("\nIngrese la cantidad de jugadores por equipo (maximo 5): ");
    while(1){
        scanf("%d", &a);
        if (a > 0 && a <= MAXPLAYERS) return a;
        else printf("*Intenta con un valor dentro del rango: ");
    }
}

// Inicializa los datos del jugador especificado en la posición del arreglo.
void initPlayer(Player *ptr, int i){
    printf("Nombre Jugador %d: ", i + 1);
    scanf("%s", ptr->name);
    ptr->health = (rand() % 76) + 75;
    ptr->level = (rand() % 3) + 1;
    ptr->strength = (rand() % 10) + 1;
    ptr->score = 0;
}

// Imprime en pantalla la información de los jugadores.
void printTeams(Player team[MAXPLAYERS], int ppt, int t){
    printf("\n\tEquipo %d", t);
    int i;
    for (i = 0; i < ppt; i++){
        printf("\n%d. %s - Vida: %d - Nivel: %d - Fuerza: %d - Puntaje: %d", i + 1, team[i].name, team[i].health,
            team[i].level, team[i].strength, team[i].score);
        if (i == ppt - 1) printf("\n");
    }
}

// Una vez creados los jugadores, se inicia el juego.
void gameLoop(Player team1[MAXPLAYERS], Player team2[MAXPLAYERS], Player *ptr, int ppt){
    bool firstTeamTurn = true;
    do {
        if (firstTeamTurn){
            printf("\nSeleccione una opcion.\n 1. Jugar.\n 2. Salir.");
            if (intInput("\nIngrese el numero de la opcion: ", 1, 2) == 2) break;
            ptr = selectPlayer(team1, ppt, 1);
            if (playerMenu() == 1) printStats(ptr);
            else{
                int damage = ptr->strength * ptr->level;
                ptr->score += 5;
                ptr = selectPlayer(team2, ppt, 2);
                ptr->health -= damage;
            }
            firstTeamTurn = false;
        } else {
            ptr = selectPlayer(team2, ppt, 2);
            if (playerMenu() == 1) printStats(ptr);
            else{
                int damage = ptr->strength * ptr->level;
                ptr->score += 5;
                ptr = selectPlayer(team1, ppt, 1);
                ptr->health -= damage;
            }
            firstTeamTurn = true;
        }
        printf("\n\n*******************************************************\n");
    } while(1);
    printf("\n\n");
}

// Valida que el entero ingresado esté dentro de un rango.
int intInput(char *msg, int min, int max){
    int aux;
    while(1){
        printf("%s", msg);
        scanf("%d", &aux);
        if (aux >= min && aux <= max) return aux;
        else printf("*Intenta con un valor dentro del rango.");
    }
}

// Selecciona un jugador para desplegar el menú de acciones.
Player * selectPlayer(Player team[MAXPLAYERS], int ppt, int t){
    printf("\nSelecciona uno de los siguientes jugadores.");
    printTeams(team, ppt, t);
    return &team[intInput("Ingresa el numero del jugador: ", 1, ppt) - 1];
}

// Selecciona una acción para realizar con el jugador.
int playerMenu(){
    printf("\nSeleccione una opcion.\n 1. Ver estadisticas.\n 2. Atacar.");
    return intInput("\nIngrese el numero de la opcion: ", 1, 2);
}

// Imprime en pantalla las estadísticas del jugador solicitado.
void printStats(Player *ptr){
    printf("\n  %s\n Vida: %d\n Nivel: %d\n Fuerza: %d\n Puntaje: %d", ptr->name, ptr->health,
            ptr->level, ptr->strength, ptr->score);
}

// Compara los puntajes de los equipos y determina el ganador.
void winner(Player team1[MAXPLAYERS], Player team2[MAXPLAYERS], int ppt){
    int i, score1 = 0, score2 = 0;
    for (i = 0; i < ppt; i++) {
        score1 += team1[i].score;
        score2 += team2[i].score;
    }
    if (score1 > score2) printf("\n\tHa ganado el equipo 1. Puntaje total: %d.", score1);
    else if (score1 == score2) printf("\n\tLos equipos han empatado con %d puntos.", score1);
    else printf("\n\tHa ganado el equipo 2. Puntaje total: %d.", score2);
    printf("\n\n");
}
