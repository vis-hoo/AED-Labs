#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Longitud máxima de la línea del archivo txt.
#define MAX_LINE_LENGTH 35

// Estructura tipo Patient.
typedef struct patient{
    char name[25];
    int age;
    int room;
    float temperature;
    struct patient *next;
} Patient;

void initFromText(Patient **first);
int menu();
void createPatient(Patient **first);
void enqueue(Patient **first, Patient *newP);
void dequeue(Patient **first);
void getNextPatient(Patient *first);
void getQueueSize(Patient *first);
void getLeftPatients(Patient *first);
void printPatients(Patient *first);
int intInput(char *msg, int min, int max);
float floatInput(char *msg, float min, float max);
void clearConsole();

int main(){
    Patient *first = NULL;
    initFromText(&first);
    do{
        int opt = menu();
        if (opt == 1) createPatient(&first);
        else if (opt == 2) dequeue(&first);
        else if (opt == 3) getNextPatient(first);
        else if (opt == 4) getQueueSize(first);
        else if (opt == 5) getLeftPatients(first);
        else if (opt == 6) printPatients(first);
        else if (opt == 7) break;
    } while(1);
    return 0;
}

// Inicializar la cola de pacientes desde el archivo de texto.
void initFromText(Patient **first){
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) return;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, file)){
        Patient *newP = (Patient*)malloc(sizeof(Patient));
        char *name = strtok(line, ",");
        strcpy(newP->name, name);
        newP->age = atoi(strtok(NULL, ","));
        newP->room = atoi(strtok(NULL, ","));
        newP->temperature = atof(strtok(NULL, ","));
        newP->next = NULL;
        enqueue(first, newP);
    }
    fclose(file);
}

// Imprime el menú de opciones.
int menu(){
    clearConsole();
    printf("\n\nSeleccione una opcion.");
    printf("\n\t1. Agregar paciente.");
    printf("\n\t2. Atender al primer paciente.");
    printf("\n\t3. Imprimir informacion del siguiente paciente.");
    printf("\n\t4. Cuantos pacientes quedan por atender.");
    printf("\n\t5. Cuanto falta para un paciente.");
    printf("\n\t6. Imprimir informacion de todos los pacientes.");
    printf("\n\t7. Salir");
    return intInput("\nIndique el numero de la opcion: ", 1, 7);
}

// Crea un paciente con información entregada por el usuario.
void createPatient(Patient **first){
    clearConsole();
    Patient *newP = (Patient*)malloc(sizeof(Patient));
    printf("\n Nombre (sin apellido): ");
    scanf("%s", newP->name);
    newP->age = intInput(" Edad (0 - 100): ", 0, 100);
    newP->room = intInput(" Habitacion (1 - 100): ", 1, 100);
    newP->temperature = floatInput(" Temperatura (35 - 40): ", 35, 40);
    newP->next = NULL;
    enqueue(first, newP);
}

// Añadir un paciente a la cola.
void enqueue(Patient **first, Patient *newP){
    if (*first == NULL) *first = newP;
    else{
        Patient *current = *first;
        while (current->next != NULL) current = current->next;
        current->next = newP;
    }
}

// Eliminar al primer paciente de la cola.
void dequeue(Patient **first){
    clearConsole();
    if (*first == NULL) printf("\n *No hay pacientes ingresados.\n");
    else {
        Patient *aux = *first;
        *first = aux->next;
        printf("\n\tSe ha atendido al paciente %s", aux->name);
        free(aux);
    }
}

// Imprimir información del siguiente paciente.
void getNextPatient(Patient *first){
    clearConsole();
    if (first == NULL) printf("\n *No hay pacientes ingresados.\n");
    else if (first->next == NULL) printf("\n *No hay mas pacientes ingresados.\n");
    else{
        Patient *current = first;
        printf("\nPaciente actual: %s", current->name);
        printf("\n\nSiguiente paciente:");
        printf("\n  %s", current->next->name);
        printf("\nEdad: %d", current->next->age);
        printf("\nHabitacion: %d", current->next->room);
        printf("\nTemperatura: %.1f", current->next->temperature);
    }
}

// Entrega el tamaño de la cola.
void getQueueSize(Patient *first){
    clearConsole();
    int i = 0;
    Patient *aux = first;
    while(aux != NULL) {
        i++;
        aux = aux->next;
    }
    printf("\n\tHay %d pacientes en la cola.", i);
}

// Entrega la cantidad de pacientes que faltan para atender al paciente seleccionado.
void getLeftPatients(Patient *first){
    clearConsole();
    if (first == NULL) printf("\n *No hay pacientes ingresados.\n");
    else{
        Patient *current = first;
        printf("\nElige el paciente:");
        int aux = 1;
        do{
            printf("\n\t%d. %s.", aux, current->name);
            aux++;
            current = current->next;
        }while(current != NULL);
        printf("\n");
        aux = intInput("\nIndique el numero de la opcion: ", 1, (aux - 1));

        current = first;
        int i;
        for (i = 0; i < (aux - 1); i++) current = current->next;
        printf("\nSe deben atender %d pacientes antes de poder atender a %s.", (aux - 1), current->name);
    }
}

// Imprimir la cola completa de pacientes.
void printPatients(Patient *first){
    clearConsole();
    if (first == NULL) printf("\n *No hay pacientes ingresados.\n");
    else{
        Patient *current = first;
        do{
            printf("\n********************");
            printf("\n  %s", current->name);
            printf("\nEdad: %d", current->age);
            printf("\nHabitacion: %d", current->room);
            printf("\nTemperatura: %.1f", current->temperature);
            current = current->next;
        }while(current != NULL);
        printf("\n********************\n");
    }
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

// Valida que el decimal ingresado esté dentro de un rango.
float floatInput(char *msg, float min, float max){
    float aux;
    while(1){
        printf("%s", msg);
        scanf("%f", &aux);
        if (aux >= min && aux <= max) return aux;
        else printf("*Intenta con un valor dentro del rango.");
    }
}

// Crea una pausa y limpia la consola.
void clearConsole(){
    printf("\n\n");
    system("pause");
    system("cls");
}