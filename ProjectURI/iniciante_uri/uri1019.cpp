#include <iostream>
using namespace std;

int main (){
    int t,hora,minutos,segundos;
    cin >> t;

    hora = t/3600;
    t=t-hora*3600;
    minutos = t/60;

    if (t>=60)
        segundos = t%60;

    else
        segundos = t;
    
    cout << hora << ":" << minutos << ":" << segundos << endl;
    return 0;
}