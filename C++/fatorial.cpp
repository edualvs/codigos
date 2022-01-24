#include <iostream>
using namespace std;

int main() {
	cout << "Digite um numero inteiro para calcular o fatorial\n";
	int fat;
	cin >> fat;
	long long int res=1;
	while (fat >=1) {
		res=res*fat;
		fat--;
	}
	cout << "O fatorial e " << res;
	return 0;
}
