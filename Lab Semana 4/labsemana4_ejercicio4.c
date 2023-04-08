#include <stdio.h>
#include <stdlib.h>

// Estructura del tipo Temperature.
typedef struct temperature{
    float temperature;
    struct temperature *next;
} Temperature;

// Estructura del tipo Patient.
typedef struct patient{
    char name[50];
    int age;
    int room;
    Temperature *firstTemp;
    struct patient *next;
} Patient;

int menu();
void addPatient(Patient **first, Patient *newPAT);
Patient* createPatient();
void recordTemperature(Patient **first);
Patient* selectPatient(Patient **first);
void printPatients(Patient *first);
void dischargePatient(Patient **first);
void freePatients(Patient *first);
int intInput(char *msg, int min, int max);
float floatInput(char *msg, float min, float max);

int main(){
    Patient *first = NULL;
    Patient *newPatient;

    do{
        int opt = menu();
        if (opt == 1) addPatient(&first, newPatient); 
        else if (opt == 2) recordTemperature(&first);
        else if (opt == 3) dischargePatient(&first);
        else if (opt == 4) printPatients(first);
        else if (opt == 5) break;
    } while(1);
    freePatients(first);
    return 0;
}

// Imprime el menú de opciones.
int menu(){
    printf("\n\nSeleccione una opcion.");
    printf("\n\t1. Agregar paciente.");
    printf("\n\t2. Agregar temperatura a paciente.");
    printf("\n\t3. Dar de alta a un paciente.");
    printf("\n\t4. Imprimir informacion.");
    printf("\n\t5. Salir");
    return intInput("\nIndique el numero de la opcion: ", 1, 5);
}

// Añade un nuevo paciente a la lista.
void addPatient(Patient **first, Patient *newPAT){
    newPAT = createPatient();
    if (*first == NULL) *first = newPAT;
    else {
        Patient *current = *first;
        while (current->next != NULL) current = current->next;
        current->next = newPAT;
    }
}

// Crea un nuevo paciente.
Patient* createPatient(){
    Patient *newPAT = (Patient*)malloc(sizeof(Patient));
    Temperature *newTEMP = (Temperature*)malloc(sizeof(Temperature));

    printf("\n Nombre: ");
    scanf("%s", newPAT->name);
    newPAT->age = intInput(" Edad (0 - 100): ", 0, 100);
    newPAT->room = intInput(" Habitacion (1 - 100): ", 1, 100);
    newTEMP->temperature = floatInput(" Temperatura inicial (35 - 40): ", 35, 40);
    newTEMP->next = NULL;
    newPAT->firstTemp = newTEMP;
    newPAT->next = NULL;

    return newPAT;
}

// Añade una temperatura al paciente especificado.
void recordTemperature(Patient **first){
    Patient *pt = selectPatient(first);
    if (pt != NULL) {
        Temperature *newTEMP = (Temperature*)malloc(sizeof(Temperature));
        newTEMP->temperature = floatInput("\n Nueva temperatura (35 - 40): ", 35, 40);
        newTEMP->next = NULL;

        Temperature *currentTemp = pt->firstTemp;
        while (currentTemp->next != NULL) currentTemp = currentTemp->next;
        currentTemp->next = newTEMP;
    }
}

// Da de alta al paciente seleccionado.
void dischargePatient(Patient **first){
    Patient *pt = selectPatient(first);
    if (pt != NULL){
        printf("\n  El paciente %s ha sido dado de alta.", pt->name);
        if (pt == *first){
            *first = pt->next;
            free(pt);
        }
        else{
            Patient *aux = *first;
            while (aux->next != pt) aux = aux->next;
            aux->next = pt->next;
            free(pt);
        }
    }
}

// Selecciona a un paciente.
Patient* selectPatient(Patient **first){
    if (*first == NULL) {
        printf("\n  No hay pacientes ingresados.\n");
        return NULL;
    }
    else{
        Patient *current = *first;
        printf("\nElige el paciente al que deseas realizar al accion:");
        int aux = 1;
        do{
            printf("\n\t%d. %s.", aux, current->name);
            aux++;
            current = current->next;
        }while(current != NULL);
        printf("\n");
        aux = intInput("\nIndique el numero de la opcion: ", 1, (aux - 1));

        current = *first;
        int i;
        for (i = 0; i < (aux - 1); i++) current = current->next;
        return current;
    }
}

// Imprime la información de todos los pacientes.
void printPatients(Patient *first){
    if (first == NULL) printf("\n  No hay pacientes ingresados.\n");
    else{
        Patient *current = first;
        do{
            printf("\n********************");
            printf("\n %s", current->name);
            printf("\nEdad: %d", current->age);
            printf("\nHabitacion: %d", current->room);
            printf("\nTemperaturas:");
            Temperature *currentTemp = current->firstTemp;
            do{
                printf("\n\t%.1f", currentTemp->temperature);
                currentTemp = currentTemp->next;
            }while(currentTemp != NULL);
            current = current->next;
            printf("\n********************");
        }while(current != NULL);
    }
}

// Liberar recursos reservados para el programa.
void freePatients(Patient *first){
    while (first != NULL){
        Patient *aux = first;
        first = first->next;
        free(aux);
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