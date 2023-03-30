#include <stdio.h>

// Estructura del tipo Player.
typedef struct{
    char name[20];
    int level;
    int health;
    int score;
} Player;

void initPlayer(Player *ptr, int i);
int intInput(char *msg, int min, int max);
void printInfo(Player players[3]);

int main(){
    Player players[3];
    Player *ptr;

    int i;
    for (i = 0; i < 3; i++){
        ptr = &players[i];
        initPlayer(ptr, i);
    }
    printInfo(players);
    
    return 0;
}

// Inicializa los datos del jugador especificado en la posición del arreglo.
void initPlayer(Player *ptr, int i){
    printf("\n\tJugador %d\n", i + 1);
    printf(" Nombre: ");
    scanf("%s", ptr->name);
    ptr->level = intInput(" Nivel (1 - 5): ", 1, 5);
    ptr->health = intInput(" Salud (20 - 150): ", 20, 150);
    ptr->score = intInput(" Puntaje (0 - 1000): ", 0, 1000);
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

// Imprime en pantalla la información de los jugadores.
void printInfo(Player players[3]){
    printf("\n\n*********************************************\n");
    int i;
    for (i = 0; i < 3; i++){
        printf("\n\n\tJugador %d", i + 1);
        printf("\nNombre - %s", players[i].name);
        printf("\nNivel - %d", players[i].level);
        printf("\nSalud - %d", players[i].health);
        printf("\nPuntaje - %d", players[i].score);
    }
}