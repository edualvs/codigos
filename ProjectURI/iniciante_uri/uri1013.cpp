#include <iostream>
#include <stdlib.h> 
using namespace std;

float maiorAB (int a, int b)
{
    float maior;
    maior = (a+b+abs(a-b))/2;
    return maior;
}

int main ()
{
    int a,b,c;
    cin >> a >> b >> c;
    if (maiorAB(a,b) == a){
            if(maiorAB(a,c) == a)
            {
                cout << a << " eh o maior" << endl;
            }
            else 
            {
                cout << c << " eh o maior" << endl;
            } 
    }
    else
    {
            if(maiorAB(b,c)== b)
            {
                cout << b << " eh o maior" << endl;
            }     
            else
            { 
                cout << c << " eh o maior" << endl;
            }   
            
    }
    return 0;
}