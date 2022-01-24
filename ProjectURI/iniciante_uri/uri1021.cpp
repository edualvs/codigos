#include <iostream>
using namespace std;

int main (){
    double valor;
    int nota;
    cin >> valor;
    cout << "NOTAS:" << endl;
    nota = valor/100;
    cout << nota << " nota(s) de R$ 100.00" << endl;
    valor = valor - nota*100;

    nota = valor/50;
    cout << nota << " nota(s) de R$ 50.00" << endl;
    valor = valor - nota*50;

    nota = valor/20;
    cout << nota << " nota(s) de R$ 20.00" << endl;
    valor = valor - nota*20;

    nota = valor/10;
    cout << nota << " nota(s) de R$ 10.00" << endl;
    valor = valor - nota*10;

    nota = valor/5;
    cout << nota << " nota(s) de R$ 5.00" << endl;
    valor = valor - nota*5;

    nota = valor/2;
    cout << nota << " nota(s) de R$ 2.00" << endl;
    valor = valor - nota*2;

    cout << "MOEDAS:" << endl;

    nota = valor/1;
    cout << nota << " moeda(s) de R$ 1.00" << endl;
    valor = valor - nota*1;

    nota = valor/0.50;
    cout << nota << " moeda(s) de R$ 0.50" << endl;
    valor = valor - nota*0.50;
    
    nota = valor/0.25;
    cout << nota << " moeda(s) de R$ 0.25" << endl;
    valor = valor - nota*0.25;

    nota = valor/0.10;
    cout << nota << " moeda(s) de R$ 0.10" << endl;
    valor = valor - nota*0.10;

    nota = valor/0.05;
    cout << nota << " moeda(s) de R$ 0.05" << endl;
    valor = valor - nota*0.05;

    nota = valor/0.01;
    cout << nota << " moeda(s) de R$ 0.01" << endl;

    return 0;
}