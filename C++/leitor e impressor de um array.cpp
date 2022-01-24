#include <iostream>

using namespace std;
int main (){
	int array[10];
	cout << "*************************************\n";
	cout << "Escreva 10 numeros: \n";
	cout << "*************************************\n";
	for (int i=0;i<10;i++){
		cin >> array[i];
	}
	cout << "*************************************\n";	
	cout << "Os 10 numeros digitados foram: \n";		
	cout << "*************************************\n";
	for (int i=0;i<10;i++){
		cout << "\n" <<array[i];	
	}
	return 0;
}
