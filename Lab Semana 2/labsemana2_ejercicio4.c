#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXPACIENTES 100
#define FIEBRE 37.5

int cantPacientes();
int celsiusFahrenheit();
void intAleatorio(int edades[], int cant, int min, int max);
void floatAleatorio(float temperaturas[MAXPACIENTES][8], int cant);
void tieneFiebre(float temperaturas[MAXPACIENTES][8], bool fiebre[], int cant);
void imprimirInfo(int edades[], float temperaturas[MAXPACIENTES][8], bool fiebre[], int cant, bool celsius);
float Fahrenheit(float celsius);

int main(){
    srand(time(NULL));

    int cant = cantPacientes();
    bool celsius = (bool)celsiusFahrenheit();

    int edades[MAXPACIENTES] = {0};
    float temperaturas[MAXPACIENTES][8] = {0};
    bool fiebre[MAXPACIENTES] = {false};
    intAleatorio(edades, cant, 18, 66);
    floatAleatorio(temperaturas, cant);
    tieneFiebre(temperaturas, fiebre, cant);

    imprimirInfo(edades, temperaturas, fiebre, cant, celsius);

    return 0;
}

int cantPacientes(){
    int cant = 0;
    bool valido = false;
    do{
        printf("\n Indique la cantidad de pacientes que desea ingresar (maximo 100): ");
        scanf("%d", &cant);
        if (cant <= MAXPACIENTES && cant > 0) valido = true;
    } while(!valido);
    printf("\n");
    return cant;
}

int celsiusFahrenheit(){
    int escala = 0;
    bool valido = false;
    do{
        printf("\n Indique la escala que desea ver:\n0. Fahrenheit\n1. Celsius\n Ingresa el numero de la opcion: ");
        scanf("%d", &escala);
        if (escala == 0 || escala == 1) valido = true;
    } while(!valido);
    printf("\n");
    return escala;
}

void intAleatorio(int edades[], int cant, int min, int max){
    int i;
    for (i = 0; i < cant; i++) edades[i] = (rand() % (max - min)) + min;
}

void floatAleatorio(float temperaturas[MAXPACIENTES][8], int cant){
    int i, j;
    float sum;
    for (i = 0; i < cant; i++){
        sum = 0;
        for (j = 0; j < 7; j++){
            temperaturas[i][j] = 36.5 + (((float)rand()/(float)(RAND_MAX)) * 2);
            sum += temperaturas[i][j];
        }
        temperaturas[i][7] = sum / 7;
    }
}

void tieneFiebre(float temperaturas[MAXPACIENTES][8], bool fiebre[], int cant){
    int i, j;
    int aux;
    for (i = 0; i < cant; i++){
        aux = 0;
        for (j = 0; j < 7; j++){
            if (temperaturas[i][j] >= 37.5){
                aux++;
                if (aux == 3){
                    fiebre[i] = true;
                    break;
                }
            }
            else aux = 0;
        }
    }
}

void imprimirInfo(int edades[], float temperaturas[MAXPACIENTES][8], bool fiebre[], int cant, bool celsius){
    int i, j;
    for (i = 0; i < cant; i++){
        printf("\nHabitacion %d: Edad - %d.", i, edades[i]);
        for (j = 0; j < 8; j++){
            if (j == 7){
                if (celsius) printf("\n\tPromedio: %.1f°C", temperaturas[i][j]);
                else printf("\n\tPromedio: %.1f°F", Fahrenheit(temperaturas[i][j]));
            } else {
                if (celsius) printf("\n\t%.1f°C", temperaturas[i][j]);
                else printf("\n\t%.1f°F", Fahrenheit(temperaturas[i][j]));
            }
        }
        printf("\n Fiebre 3 dias seguidos: %s.\n", fiebre[i] ? "Verdadero" : "Falso");
    }
}

float Fahrenheit(float celsius){
    return ((celsius * (1.8)) + 32);
}