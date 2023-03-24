#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int cantidadElementos();
void agregarElementos(int elementos[], int cantidad);
void imprimirArreglo(int elementos[], int cantidad);

int main(){
    
    int elementos[MAX] = {0};
    int cantidad = cantidadElementos();
    agregarElementos(elementos, cantidad);
    imprimirArreglo(elementos, cantidad);

    return 0;
}

int cantidadElementos(){

    int cantidad = 0;
    bool valido = false;
    do{
        printf("Ingrese la cantidad de elementos diferentes (maximo 100): ");
        scanf("%d", &cantidad);
        if (cantidad <= MAX && cantidad > 0) {
			valido = true;
		}
    } while(!valido);
    printf("\n");

    return cantidad;
}

void agregarElementos(int elementos[], int cantidad){
    int i;
    for (i = 0; i < cantidad; i++){
        printf("Elemento %d: ", i + 1);
        scanf("%d", &elementos[i]);
    }
    printf("\n");
}

void imprimirArreglo(int elementos[], int cantidad){
    int i;
    for (i = 0; i < cantidad; i++){
        printf("%d: %d\n", i + 1,elementos[i]);
    }
}
