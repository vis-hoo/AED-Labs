#include <iostream>
using namespace std;

int fibonacci(int n);

int main(){
    int n;
    do{
        cout << "\nCalcular el valor de la secuencia Fibonacci en la siguiente posicion: ";
        cin >> n;
    } while(n < 0);

    cout << "Resultado: " << fibonacci(n);
    return 0;
}

int fibonacci(int n){
    if (n == 0) return 0;
    else if (n == 1) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}