#include <iostream>
using namespace std;

int factorial(int n);

int main(){
    int n;
    do{
        cout << "\nCalcular factorial del siguiente valor: ";
        cin >> n;
    } while(n < 0);

    cout << "Resultado: " << factorial(n);
    return 0;
}

int factorial(int n){
    if (n == 0) return 1;
    return n*factorial(n-1);
}