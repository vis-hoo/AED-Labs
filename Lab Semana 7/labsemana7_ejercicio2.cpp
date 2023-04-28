#include <iostream>
using namespace std;

int main(){
    float num1, num2, num3, prom;

    cout << "\n\tCalculo de promedio\n\n Ingrese un valor: ";
    cin >> num1;
    cout << " Ingrese el segundo valor: ";
    cin >> num2;
    cout << " Ingrese el tercer valor: ";
    cin >> num3;

    prom = (num1 + num2 + num3) / 3;
    cout << "\n\tEl promedio [(" << num1 << "+" << num2 << "+" << num3 << ")/3] es igual a " << prom << "." << endl;
}