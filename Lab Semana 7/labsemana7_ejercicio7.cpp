#include <iostream>
#include <string>
using namespace std;

string modifyString(string s);
bool isPalindrome(string s);

int main(){
    string str;
    cout << "\nIngrese texto: ";
    getline(cin, str);

    string modStr = modifyString(str);
    cout << modStr << endl;

    if (isPalindrome(modStr)) cout << str << " es palindromo.";
    else cout << str << " no es palindromo.";
    return 0;
}

// Elimina los espacios del string y convierte de mayúsculas a minúsculas.
string modifyString(string s){
    string modStr;
    for (int i = 0; i < s.length(); i++){
        char c = s[i];
        if (c == ' ') continue;
        if (isupper(c)) c = tolower(c);
        modStr += c;
    }
    return modStr;
}

bool isPalindrome(string s){
    if (s.length() <= 1) return true;
    if (s[0] == s.back()) return isPalindrome(s.substr(1, s.length()-2));
    return false;
}