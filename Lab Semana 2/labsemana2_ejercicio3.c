#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int cantElementos();
void valoresAleatorios(int inventario[], int cant, int min, int max);
void combinarInventarios(int invJug1[], int invJug2[], int invComb[], int cant);
void imprimirInventario(int inventario[], int cant, int jugador);
void actualizarInventarios(int invJug1[], int invJug2[], int invComb[], int invMax, int cant);
void agregarElemento(int inv[], int invComb[], int invMax[], int indice);
void eliminarElemento(int inv[], int indice);

int main(){
    srand(time(NULL));

    int cant = cantElementos();
    int invMax[MAX] = {0};
    int invJug1[MAX] = {0};
    int invJug2[MAX] = {0};
    int invComb[MAX] = {0};
    valoresAleatorios(invMax, cant, 10, 16);
    valoresAleatorios(invJug1, cant, 0, 6);
    valoresAleatorios(invJug2, cant, 0, 6);

    bool fin = false;
    do {
        actualizarInventarios(invJug1, invJug2, invComb, invMax, cant);
        
        int opcion = 0;
        do{
            printf("\n 1. Agregar elemento.");
            printf("\n 2. Eliminar elemento.");
            printf("\n 3. Terminar programa.");
            printf("\nSeleccione una opcion (ingrese el numero): ");
            scanf("%d", &opcion);
        } while(opcion < 1 || opcion > 3);

        int inv = 0;
        int indice = 0;
        if (opcion == 3) fin = true;
        else{
            do {
                printf("\n 1. Inventario Jugador 1.");
                printf("\n 2. Inventario Jugador 2.");
                printf("\nSeleccione una opcion (ingrese el numero): ");
                scanf("%d", &inv);
            } while(inv != 1 && inv != 2);
            
            do {
                printf("\nIngrese el indice del elemento: ");
                scanf("%d", &indice);
            } while(indice > cant - 1 || indice < 0);

            if (opcion == 1 && inv == 1) agregarElemento(invJug1, invComb, invMax, indice);
            else if (opcion == 1 && inv == 2) agregarElemento(invJug2, invComb, invMax, indice);
            else if (opcion == 2 && inv == 1) eliminarElemento(invJug1, indice);
            else if (opcion == 2 && inv == 2) eliminarElemento(invJug2, indice);
        }
    } while(!fin);
}

int cantElementos(){
    int cant = 0;
    bool valido = false;
    do{
        printf("\n\nIndique la cantidad de elementos que desea ingresar (maximo 100): ");
        scanf("%d", &cant);
        if (cant <= MAX && cant > 0) valido = true;
    } while(!valido);
    printf("\n");
    return cant;
}

void valoresAleatorios(int inventario[], int cant, int min, int max){
    int i;
    for (i = 0; i < cant; i++) inventario[i] = (rand() % (max - min)) + min;
}

void combinarInventarios(int invJug1[], int invJug2[], int invComb[], int cant){
    int i;
    for (i = 0; i < cant; i++) invComb[i] = invJug1[i] + invJug2[i];
}

void imprimirInventario(int inventario[], int cant, int jugador){
    switch (jugador){
        case -1:
            printf("\n\tInventario Maximo\n");
            break;
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
    for (i = 0; i < cant; i++) printf("%d: %d\n", i, inventario[i]);
}

void actualizarInventarios(int invJug1[], int invJug2[], int invComb[], int invMax, int cant){
    combinarInventarios(invJug1, invJug2, invComb, cant);
    imprimirInventario(invJug1, cant, 1);
    imprimirInventario(invJug2, cant, 2);
    imprimirInventario(invComb, cant, 0);
    imprimirInventario(invMax, cant, -1);
}

void agregarElemento(int inv[], int invComb[], int invMax[], int indice){
    if (invComb[indice] == invMax[indice]) printf("\nNo se puede agregar otro elemento.\n");
    else inv[indice]++;
}

void eliminarElemento(int inv[], int indice){
    if (inv[indice] == 0) printf("\nEl inventario ya esta vacio.\n");
    else inv[indice]--;
}
