#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int cantidadElementos();
void valoresAleatorios(int inventario[], int cantidad, int min, int max);
void combinarInventarios(int invJ1[], int invJ2[], int invComb[], int cantidad);
void imprimirInventario(int inventario[], int cantidad, int jugador);

int main(){
    srand(time(NULL));

    int cantidad = cantidadElementos();

    int inventarioMaximo[MAX] = {0};
    valoresAleatorios(inventarioMaximo, cantidad, 10, 21);

    int inventarioJugador1[MAX] = {0};
    valoresAleatorios(inventarioJugador1, cantidad, 0, 6);

    int inventarioJugador2[MAX] = {0};
    valoresAleatorios(inventarioJugador2, cantidad, 0, 6);

    int inventarioCombinado[MAX] = {0};
    combinarInventarios(inventarioJugador1, inventarioJugador2, inventarioCombinado, cantidad);

    imprimirInventario(inventarioJugador1, cantidad, 1);
    imprimirInventario(inventarioJugador2, cantidad, 2);
    imprimirInventario(inventarioCombinado, cantidad, 0);
}

int cantidadElementos(){
    int cantidad = 0;
    bool valido = false;
    do{
        printf("Indique la cantidad de elementos que desea ingresar (maximo 100): ");
        scanf("%d", &cantidad);
        if (cantidad <= MAX && cantidad > 0) valido = true;
    } while(!valido);
    printf("\n");

    return cantidad;
}

void valoresAleatorios(int inventario[], int cantidad, int min, int max){
    int i;
    for (i = 0; i < cantidad; i++) inventario[i] = (rand() % (max - min)) + min;
}

void combinarInventarios(int invJ1[], int invJ2[], int invComb[], int cantidad){
    int i;
    for (i = 0; i < cantidad; i++) invComb[i] = invJ1[i] + invJ2[i];
}

void imprimirInventario(int inventario[], int cantidad, int jugador){
    switch (jugador){
        case 0:
            printf("\n\tInventario Combinado\n");
            break;
        case 1:
            printf("\n\tInventario Jugador 1\n");
            break;
        case 2:
            printf("\n\tInventario Jugador 2\n");
            break;
    }
    int i;
    for (i = 0; i < cantidad; i++) printf("%d: %d\n", i + 1, inventario[i]);
}