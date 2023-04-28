#include <iostream>
#include <string>
using namespace std;

int stringLength(string s);

int main(){
    string palabra;
    cout << "\n Ingresa una palabra: ";
    cin >> palabra;

    cout << "\n Palabra ingresada: " << palabra << ".\n Largo de la palabra: " << stringLength(palabra) << ".";
    return 0;
}

int stringLength(string s){
    int i = 0;
    while (s[i] != 0) i++;
    return i;
}