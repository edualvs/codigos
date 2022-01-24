#include <iostream>

using namespace std;
int main (){
	int n1,n2;
	cout << "Digite 2 numeros inteiros:\n";
	cin >> n1;
	cin >> n2;
	if (n1>n2){
		cout << "O primeiro numero que voce digitou eh maior.";
	}
		else if (n2>n1)
		cout << "O segundo numero que voce digitou eh maior.";
		else
		cout << "Os numeros sao iguais.";
		
	
	
	
	return 0;
}

