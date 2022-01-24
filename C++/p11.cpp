#include <iostream>

using namespace std;
int main (){
	int num=0,quad=0,i=0;
	cout << "Digite um numero: \n";
	cin >> num;
	for (int i=0;i<=num*2;i++){
		if (i%2!=0)
		quad=quad+i;
	}
	cout << quad;
	return 0;
}
