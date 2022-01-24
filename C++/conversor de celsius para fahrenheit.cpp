#include <iostream>

using namespace std;
int main (){
	float celsius,fahrenheit;
	cout << "Digite uma temperatura em graus celsius: ";
	cin >> celsius;
	fahrenheit = celsius*1.8 + 32;
	cout << "A temperatura em fahrenheit eh " << fahrenheit;
	
	return 0;
}
