#include <iostream>

using namespace std;

//int main(){
//	int number,square;
//	cout << "Digite um numero: ";
//	cin >> number;
//	for (;number!=0;number--){
//		square=number*number;
//		cout << "\nO quadrado de " << number << " e " << square;
//	}
//	return 0;
//}

int main(){	int number,square;
	cout << "Digite um numero: ";
	int numero,quadrado;
	cin >> numero;
	
	while (numero!=0){
		quadrado=numero*numero;
		cout << "\nO quadrado do numero " << numero << " e " << quadrado << "\n";
		cin >> numero; 
	}	
	return 0;
}
	


