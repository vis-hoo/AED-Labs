#include <stdio.h>

// Cantidad máxima de pacientes y de temperaturas por paciente.
#define MAXPAT 10
#define MAXTEMP 5

// Estructura del tipo Patient.
typedef struct {
    char name[50];
    int age;
    int room;
    float temperature[MAXTEMP];
} Patient;

void addPatient(Patient * pt);
void recordTemperature(Patient * pt);
void printPatients(Patient * pt);
int intInput(char *msg, int min, int max);
float floatInput(char *msg, float min, float max);

int main(){
    Patient patients[MAXPAT];
    int numPatients = intInput("\nIngrese la cantidad de pacientes que desea (1 - 10): ", 1, MAXPAT);
    int i;
    for (i = 0; i < numPatients; i++) addPatient(&patients[i]);

    int opt;
    do{
        printf("\n\nSeleccione una opcion.\n\t1. Agregar paciente.\n\t2. Agregar temperatura a paciente.\n\t3. Imprimir informacion.\n\t4. Salir.");
        opt = intInput("\nIndique el numero de la opcion: ", 1, 4);
        if (opt == 1){
            if (numPatients == MAXPAT) printf("\nNo se pueden agregar mas pacientes.\n");
            else{
                numPatients++;
                addPatient(&patients[numPatients - 1]);
            }
        }
        else if (opt == 2){
            printf("\nSeleccione el paciente al que desea agregar la temperatura.");
            for(i = 0; i < numPatients; i++) printf("\n\t%d. %s.", i + 1, patients[i].name);
            int pt = intInput("\nIndique el numero de la opcion: ", 1, numPatients);
            recordTemperature(&patients[pt - 1]);
        }
        else if (opt == 3) for (i = 0; i < numPatients; i++) printPatients(&patients[i]);
        else if (opt == 4) break;
    } while(1);
    return 0;
}

// Añade un paciente en la posición del arreglo especificada.
void addPatient(Patient * pt){
    printf("\n Nombre: ");
    scanf("%s", pt->name);
    pt->age = intInput(" Edad (0 - 100): ", 0, 100);
    pt->room = intInput(" Habitacion (1 - 100): ", 1, 100);
    
    int i;
    for (i = 0; i < MAXTEMP; i++) pt->temperature[i] = 0;
    pt->temperature[0] = floatInput(" Temperatura inicial (35 - 40): ", 35, 40);
}

// Añade una nueva temperatura al paciente especificado.
void recordTemperature(Patient * pt){
    int i;
    for (i = 0; i < MAXTEMP; i++){
        if (i == (MAXTEMP - 1) && pt->temperature[i] != 0) printf("\nNo se pueden agregar mas temperaturas a este paciente.");
        if (pt->temperature[i] == 0){
            pt->temperature[i] = floatInput(" Nueva temperatura (35 - 40): ", 35, 40);
            break;
        }
    }
}

// Imprime los datos del paciente en la posición del arreglo especificada.
void printPatients(Patient * pt){
    printf("\n********************");
    printf("\n\nNombre: %s", pt->name);
    printf("\nEdad: %d", pt->age);
    printf("\nHabitacion: %d", pt->room);
    printf("\nTemperaturas:");
    int i;
    for(i = 0; i < MAXTEMP; i++) if (pt->temperature[i] != 0) printf("\n\t%d. %.1f", i + 1, pt->temperature[i]);
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