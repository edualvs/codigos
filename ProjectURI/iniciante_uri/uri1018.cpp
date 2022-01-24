#include <iostream>
using namespace std;

int main (){
    int n,cont;
    cin >> n;
    cout << n << endl;

    cont=n/100;
    cout << cont << " nota(s) de R$ 100,00" << endl;
    n=n%100;

    cont=n/50;
    cout << cont << " nota(s) de R$ 50,00" << endl;
    n=n%50;

    cont=n/20;
    cout << cont << " nota(s) de R$ 20,00" << endl;
    n=n%20;

    cont=n/10;
    cout << cont << " nota(s) de R$ 10,00" << endl;
    n=n%10;

    cont=n/5;
    cout << cont << " nota(s) de R$ 5,00" << endl;
    n=n%5;

    cont=n/2;
    cout << cont << " nota(s) de R$ 2,00" << endl;
    n=n%2;

    cont=n/1;
    cout << cont << " nota(s) de R$ 1,00" << endl;
    n=n%1;  
    return 0;
}