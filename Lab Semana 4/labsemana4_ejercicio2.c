#include <stdio.h>

// Cantidad máxima de pacientes.
#define MAX 10

// Estructura del tipo Patient.
typedef struct {
    char name[50];
    int age;
    int room;
    float temperature;
} Patient;

void addPatient(Patient * pt);
void printPatients(Patient * pt);
int intInput(char *msg, int min, int max);
float floatInput(char *msg, float min, float max);

int main(){
    Patient patients[MAX];
    int numPatients = intInput("\nIngrese la cantidad de pacientes que desea (1 - 10): ", 1, MAX);
    int i;
    for (i = 0; i < numPatients; i++) addPatient(&patients[i]);

    int opt;
    do{
        printf("\nSeleccione una opcion.\n\t1. Agregar paciente.\n\t2. Imprimir informacion.\n\t3. Salir.");
        opt = intInput("\nIndique el numero de la opcion: ", 1, 3);
        if (opt == 1){
            if (numPatients == MAX) printf("\nNo se pueden agregar mas pacientes.\n");
            else{
                numPatients++;
                addPatient(&patients[numPatients - 1]);
            }
        }
        else if (opt == 2) for (i = 0; i < numPatients; i++) printPatients(&patients[i]);
        else if (opt == 3) break;
    } while(1);
    return 0;
}

// Añade un paciente en la posición del arreglo especificada.
void addPatient(Patient * pt){
    printf("\n Nombre: ");
    scanf("%s", pt->name);
    pt->age = intInput(" Edad (0 - 100): ", 0, 100);
    pt->room = intInput(" Habitacion (1 - 100): ", 1, 100);
    pt->temperature = floatInput(" Temperatura (35 - 40): ", 35, 40);
}

// Imprime los datos del paciente en la posición del arreglo especificada.
void printPatients(Patient * pt){
    printf("\n********************");
    printf("\n\nNombre: %s", pt->name);
    printf("\nEdad: %d", pt->age);
    printf("\nHabitacion: %d", pt->room);
    printf("\nTemperatura: %.1f\n", pt->temperature);
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