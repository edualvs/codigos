#include <iostream>

using namespace std;
int main (){
	int soma,n,i;
	cout << "Digite 10 numeros inteiros:\n";
	for (i=0;i<10;i++){
		cin >> n;
		soma=soma+n;
		
	}
	cout << "A soma de todos os numeros digitados eh " << soma ;
	
	return 0;
}

