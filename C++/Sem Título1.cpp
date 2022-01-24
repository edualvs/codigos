#include <iostream>
using namespace std;

int main(){
	cout << "Digite um numero: " << endl;
	int n=0;
	long long int f=1;
	cin >> n;
	while (n>=1){
		f=f*n;
		n--;
	}
		cout << "O Fatorial deste numero e: " << f << endl;
	
	return 0;	
}
