#include <iostream>

using namespace std;
int main (){
	int n,soma;
	float media;
	cout << "Digite 10 entradas:\n";
	for(int i=1;i<=10;i++){
		cin >> n;
		soma=soma+n;
	}
	media=soma/10;
	cout << "A media das 10 entradas eh " << media;
	return 0;
}
	
