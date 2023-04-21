#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Longitud máxima de la línea del archivo de texto.
#define MAX_LINE_LENGTH 45

// Enum de los tipos de Guardián.
enum guardianType {Wizard, Viking, Necromancer, Beast};

// Estructura Guardián.
// Nombre, tipo, vida, ataque, defensa, y siguiente Guardián.
typedef struct guardian{
    char name[30];
    enum guardianType type;
    float health;
    int attack;
    float defense;
    struct guardian *next;
} Guardian;

// Estructura Historial.
// Dificultad del torneo, personaje elegido, si ganó o perdió, cantidad de enemigos derrotados, y siguiente Historial.
typedef struct history{
    int tournamentDifficulty;
    Guardian *player;
    bool won;
    int defeatedEnemies;
    struct history *next;
} History;

// Declaración de funciones
void initFromText(Guardian **first);
void menuOptions(Guardian **first, History **firstNode);
Guardian* createCharacter();
void addGuardian(Guardian **first, Guardian *newGuardian);
void startTournament(Guardian **first, History **firstNode);
Guardian* selectGuardian(Guardian **first);
Guardian* selectTournament(Guardian **first);
int getListSize(Guardian *first);
Guardian* getGuardian(Guardian **first, int index);
void startFight(Guardian **p, Guardian **e, History **fN);
int getRollResult();
void printHistory(History *firstNode);
void printList(Guardian *first);
void printCharacterStatus(Guardian *guardian);
char* typeToString(enum guardianType type);
int intInput(char *msg, int min, int max);
void clearConsole();

// Main.
int main(){
    srand(time(NULL));
    Guardian *first = NULL;
    History *firstNode = NULL;
    initFromText(&first);
    menuOptions(&first, &firstNode);
    return 0;
}

// Inicializa la lista de Guardianes desde un archivo de texto.
// Por cada línea del archivo, se espera que exista los datos para crear uno de los Guardianes.
void initFromText(Guardian **first){
    FILE *file = fopen("guardians_tournament_data.txt", "r");
    if (file == NULL) return;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, file)){
        Guardian *newGuardian = (Guardian*)malloc(sizeof(Guardian));
        char *name = strtok(line, ",");
        strcpy(newGuardian->name, name);
        newGuardian->type = atoi(strtok(NULL, ","));
        newGuardian->health = atof(strtok(NULL, ","));
        newGuardian->attack = atoi(strtok(NULL, ","));
        newGuardian->defense = atof(strtok(NULL, ","));
        newGuardian->next = NULL;
        // Se añade el Guardián creado a la lista existente.
        addGuardian(first, newGuardian);
    }
    fclose(file);
}

// Entrega el menú de opciones.
void menuOptions(Guardian **first, History **firstNode){
    do{
        clearConsole();
        printf("\n\tTHE GUARDIANS TOURNAMENT");
        printf("\n\nSeleccione una opcion.");
        printf("\n\t1. Crear un Guardian.");
        printf("\n\t2. Competir en un torneo.");
        printf("\n\t3. Historial del jugador.");
        printf("\n\t4. Imprimir lista de Guardianes.");
        printf("\n\t5. Salir del programa.");
        int opt = intInput("\nIngresa el numero de la opcion: ", 1, 5);
        if (opt == 1) addGuardian(first, createCharacter());
        else if (opt == 2) startTournament(first, firstNode);
        else if (opt == 3) printHistory(*firstNode);
        else if (opt == 4) printList(*first);
        else if (opt == 5) break;
    } while(1);
    printf("\n\tVUELVE PRONTO\n\n");
}

// Crea un Guardián con la información proporcionada por el usuario.
Guardian* createCharacter(){
    clearConsole();
    Guardian *newGuardian = (Guardian*)malloc(sizeof(Guardian));
    printf("\n Nombre: ");
    char temp;
    scanf("%c%[^\n]", &temp, newGuardian->name);
    printf(" Elige el tipo de Guardian:\n\t1. Mago.\n\t2. Vikingo.\n\t3. Nigromante.\n\t4. Bestia.");
    newGuardian->type = intInput("\nIngresa el numero de la opcion: ", 1, 4) - 1;
    // Los valores se generan de manera aleatoria en los siguientes rangos:
    // Vida: 600 - 400;
    // Ataque: 200 - 100;
    // Defensa: 100 - 30;
    newGuardian->health = (float)(rand() % 201) + 400;
    newGuardian->attack = (rand() % 101) + 100;
    newGuardian->defense = (float)(rand() % 71) + 30;
    newGuardian->next = NULL;
}

// Añade un Guardián a la lista.
void addGuardian(Guardian **first, Guardian *newGuardian){
    if (*first == NULL) *first = newGuardian;
    else{
        Guardian *current = *first;
        while (current->next != NULL) current = current->next;
        current->next = newGuardian;
    }
}

// Inicia el proceso completo de seleccionar un Torneo y luchar.
void startTournament(Guardian **first, History **firstNode){
    // El usuario elige el personaje que desea usar, y luego la dificultad del torneo.
    // Se crea una lista de enemigos, y luego un nuevo nodo en la lista del Historial.
    Guardian *player = selectGuardian(first);
    Guardian *firstEnemy = selectTournament(first);
    History *newHistory = (History*)malloc(sizeof(History));
    newHistory->tournamentDifficulty = getListSize(firstEnemy);
    newHistory->player = player;
    newHistory->won = true;
    newHistory->defeatedEnemies = 0;
    newHistory->next = NULL;
    if (*firstNode == NULL) *firstNode = newHistory;
    else {
        History *aux = *firstNode;
        while(aux->next != NULL) aux = aux->next;
        aux->next = newHistory;
    }
    // Se inicia la batalla entre el jugador y los enemigos.
    if (firstEnemy != NULL){
        clearConsole();
        printf("\tJUGADOR\n");
        printCharacterStatus(player);
        printList(firstEnemy);
        startFight(&player, &firstEnemy, &newHistory);
        while(firstEnemy != NULL){
            Guardian *aux = firstEnemy;
            firstEnemy = aux->next;
            free(aux);
        }
    }
}

// El usuario selecciona el Guardián con el que desea jugar.
Guardian* selectGuardian(Guardian **first){
    printList(*first);
    if (getListSize(*first) != 0){
        int listSize = getListSize(*first);
        int selection = intInput("\nIngresa el numero del Guardian que elijes: ", 1, listSize);
        return getGuardian(first, selection);
    }
    return NULL;
}

// El usuario elije la dificultad del Torneo.
Guardian* selectTournament(Guardian **first){
    clearConsole();
    int i, difficulty, enemies;
    printf("\n\nSelecciona la dificultad del Torneo.");
    printf("\n\t1. Principiante.");
    printf("\n\t2. Intermedio.");
    printf("\n\t3. Avanzado.");
    difficulty = intInput("\nIngresa el numero de la opcion: ", 1, 3);
    if (difficulty == 1) enemies = 3;
    else if (difficulty == 2) enemies = 5;
    else if (difficulty == 3) enemies = 7;
    if (getListSize(*first) < enemies) {
        printf("\nNo hay suficientes guardianes para este tipo de torneo.");
        if (difficulty == 1) return NULL;
    }
    // Los enemigos se eligen de manera aleatoria de entre los que están en la lista de Guardianes.
    Guardian *firstEnemy = NULL;
    for(i = 0; i < enemies; i++){
        int listSize = getListSize(*first);
        Guardian *enemy = getGuardian(first, (rand() % listSize) + 1);
        addGuardian(&firstEnemy, enemy);
    }
    return firstEnemy;
}

// Obtiene el tamaño actual de la lista.
int getListSize(Guardian *first){
    if (first == NULL) return 0;
    else {
        Guardian *current = first;
        int size = 1;
        while(current->next != NULL){
            current = current->next;
            size++;
        }
        return size;
    }
}

// Encuentra al Guardián en el índice específicado.
Guardian* getGuardian(Guardian **first, int index){
    Guardian *current = *first;
    Guardian *aux = current->next;
    if(index == 1){
        *first = aux;
        current->next = NULL;
        return current;
    } else {
        int i = 1;
        while(i != index - 1){
            current = current->next;
            aux = aux->next;
            i++;
        }
        current->next = aux->next;
        aux->next = NULL;
        return aux;
    }
}

// Comienza el combate entre el usuario y la lista de enemigos.
void startFight(Guardian **p, Guardian **e, History **nH){
    Guardian *player = *p;
    Guardian *enemy = *e;
    History *newHistory = *nH;
    bool attacking;
    int rollResult;
    // Este ciclo do-while representa los turnos. Finaliza cuando todos los enemigos mueren o el jugador muere.
    do{
        int i = 0;
        bool canRepeat = true;
        float finalAttack = 0, finalDefense = 0, defenseReduction = 0;
        // Este ciclo do-while controla si el jugador puede volver a realizar una acción después de haber
        // sacado un 6 en el dado por primera vez.
        do{
            // Se selecciona la acción que se desea realizar.
            clearConsole();
            printf("\n\nSelecciona la accion.");
            printf("\n\t1. Atacar.");
            printf("\n\t2. Defender.");
            if (intInput("\nIngresa el numero de la opcion: ", 1, 2) == 1) attacking = true;
            else attacking = false;

            // Se lanza el dado y se realiza el cálculo de cuánto ataque o defensa se aplica.
            clearConsole();
            rollResult = getRollResult();
            printf("\n Lanzas el dado. Obtienes un %d.", rollResult);
            if (attacking){
                if (rollResult == 2 || rollResult == 4 || rollResult == 6) printf("\nTu ataque ha sido bloqueado.");
                else if (rollResult == 1) finalAttack = player->attack * 0.8;
                else if (rollResult == 3) finalAttack = player->attack;
                else if (rollResult == 5) finalAttack = player->attack * 1.3;
            } else {
                if (rollResult == 1 || rollResult == 3 || rollResult == 5) {
                    printf("\nTu defensa ha fallado. Se aplica un desgaste.");
                    defenseReduction = player->defense * 0.05;
                }
                else if (rollResult == 2) finalDefense = player->defense * 0.5;
                else if (rollResult == 4) finalDefense = player->defense;
                else if (rollResult == 6) finalDefense += player->defense * 1.2;
            }
            if (rollResult == 6 && canRepeat) {
                if (i == 1) canRepeat = false;
                else printf("\n Has lanzado un 6. Puedes seleccionar una accion extra.");
            }
            else if (rollResult != 6) canRepeat = false;
            i++;
        } while (canRepeat);
        
        // Al terminar la selección de acciones, se aplican los daños y defensas calculados.
        enemy->health -= finalAttack;
        if (enemy->health < 0) enemy->health = 0;
        player->health += finalDefense;
        if (player->defense > 30) player->defense -= defenseReduction;
        if (player->defense < 30) player->defense = 30;
        player->health -= enemy->attack * 0.2;
        if (player->health < 0) player->health = 0;

        // Se muestra el estado de los personajes.
        printf("\n\n");
        printCharacterStatus(player);
        printf("\n\n********************\n");
        printCharacterStatus(enemy);

        // Si el enemigo muere, se pasa al siguiente. Se suma 1 a la cantidad de enemigos derrotados en el historial.
        if (enemy->health == 0) {
            enemy = enemy->next;
            newHistory->defeatedEnemies++;
        }

        // Si el jugador o todos los enemigos han muerto, se termina el torneo.
        if (player->health == 0 || enemy == NULL) {
            if (player->health == 0) newHistory->won = false;
            break;
        }
    } while (1);
}

// Entrega el resultado del lanzamiento del dado.
int getRollResult() { return (rand() % 6) + 1; }

// Muestra el historial del jugador.
void printHistory(History *firstNode){
    clearConsole();
    History *current = firstNode;
    if (current == NULL) printf("\n Aun no hay batallas.");
    while(current != NULL){
        printf("\n********************");
        printf("\n\tTorneo: ");
        if (current->tournamentDifficulty == 3) printf("Principiante.\n");
        else if (current->tournamentDifficulty == 5) printf("Intermedio.\n");
        else if (current->tournamentDifficulty == 7) printf("Avanzado.\n");
        printCharacterStatus(current->player);
        printf("\n\n Resultado: ");
        if (current->won) printf("Victoria.");
        else if (!current->won) printf("Derrota.");
        printf("\n Enemigos derrotados: %d.", current->defeatedEnemies);
        current = current->next;
        printf("\n********************\n");
    }
}

// Imprime la lista completa de Guardianes.
void printList(Guardian *first){
    clearConsole();
    Guardian *current = first;
    int index = 1;
    while(current != NULL){
        printf("\n********************\n\t%d", index);
        printCharacterStatus(current);
        current = current->next;
        index++;
        printf("\n********************\n");
    }
}

// Imprime la información del Guardián especificado.
void printCharacterStatus(Guardian *guardian){
    printf("\n  %s", guardian->name);
    printf("\nTipo: %s", typeToString(guardian->type));
    printf("\nVida: %.1f", guardian->health);
    printf("\nAtaque: %d", guardian->attack);
    printf("\nDefensa: %.1f", guardian->defense);
}

// Entrega el tipo de Guardián en string basandose en el Enum.
char* typeToString(enum guardianType type){
    switch (type){
        case Wizard: return "Mago";
        case Viking: return "Vikingo";
        case Necromancer: return "Nigromante";
        case Beast: return "Bestia";
    }
}

// Valida que el entero ingresado esté dentro de un rango.
int intInput(char *msg, int min, int max){
    int opt;
    while(1){
        printf("%s", msg);
        scanf("%d", &opt);
        if (opt >= min && opt <= max) return opt;
        else printf("*Ingresa un valor dentro del rango.");
    }
}

// Crea una pausa y limpia la consola.
void clearConsole(){
    printf("\n\n");
    system("pause");
    system("cls");
}