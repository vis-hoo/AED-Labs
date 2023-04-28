#include <iostream>
#include <string>
using namespace std;

struct Num{
    float data;
    Num *next;
};

int menu();
Num* createNum();
void addNum(Num **first, Num *newNum);
void printList(Num *first);
float getSum(Num *first);
float getProduct(Num *first);
float getProm(Num *first);
int intInput(string s, int min, int max);

int main(){
    Num *first = nullptr;
    do {
        int opt = menu();
        if (opt == 1) addNum(&first, createNum());
        else if (opt == 2) {
            if (first == nullptr) cout << "\n No se ingresaron numeros.";
            else{
                printList(first);
                cout << "\n Suma de los valores: " << getSum(first);
                cout << "\n Producto de los valores: " << getProduct(first);
                cout << "\n Promedio de los valores: " << getProm(first);
            }
            break;
        }
    } while(1);
    return 0;
}

int menu(){
    cout << "\n 1. Agregar numero.";
    cout << "\n 2. Terminar lista." << endl;
    return intInput("\nIngresa el numero de la opcion: ", 1, 2);
}

Num* createNum(){
    Num *newNum = new Num;
    cout << "\n Ingresa un valor: ";
    cin >> newNum->data;
    newNum->next = nullptr;
    return newNum;
}

void addNum(Num **first, Num *newNum){
    if (*first == nullptr) *first = newNum;
    else {
        Num *aux = *first;
        while (aux->next != nullptr) aux = aux->next;
        aux->next = newNum;
    }
}

void printList(Num *first){
    Num *aux = first;
    cout << "\nValores: ";
    while (aux != nullptr){
        if (aux->next == nullptr) cout << aux->data << ".";
        else cout << aux->data << ", ";
        aux = aux->next;
    }
}

float getSum(Num *first){
    Num *aux = first;
    float sum = 0;
    while (aux != nullptr){
        sum += aux->data;
        aux = aux->next;
    }
    return sum;
}

float getProduct(Num *first){
    Num *aux = first;
    float prod = 1;
    while (aux != nullptr){
        prod *= aux->data;
        aux = aux->next;
    }
    return prod;
}

float getProm(Num *first){
    Num *aux = first;
    float prom = 0;
    int i = 0;
    while (aux != nullptr){
        i++;
        prom += aux->data;
        aux = aux->next;
    }
    prom /= i;
    return prom;
}

int intInput(string s, int min, int max){
    int n;
    do {
        cout << s;
        cin >> n;
        if (n < min || n > max) cout << " *FUERA DEL RANGO*" << endl;
    } while (n < min || n > max);
    return n;
}