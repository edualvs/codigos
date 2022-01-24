#include <iostream>
using namespace std;

int main (){
    int i,ano,mes,dia;
    cin >> i;
    ano=i/365;
    i=i-365*ano;
    mes=i/30;
    dia=i%30;
    cout << ano << " ano(s)" << endl;
    cout << mes << " mes(es)" << endl;
    cout << dia << " dia(s)" << endl;

    return 0;
}