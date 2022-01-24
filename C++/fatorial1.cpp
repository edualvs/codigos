#include <iostream>

using namespace std;

int main (){
	int fat;
	long long int res=1;
	cin >> fat;
	while (fat>=1){
		res=res*fat;
		fat--;
	}
	
	cout << "O fatorial e " << res;
	return 0;
}
