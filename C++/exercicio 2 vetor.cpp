#include <iostream>
#include <locale.h>
#include <vector>
#include <cstring>
#include <math.h>
using namespace std;
int main (){
	vector<int>num;
	vector<int>:: iterator it;	
	for (int i=0;i<50;i++)
		num.push_back (i);
		cout << *it;
	while (!num.empty()){
		cout << ' ' << num.back();
		num.pop_back();
	}
	int valor=0;
	cin >> valor;
	it=num.begin();
	if (valor>30 && valor%2==0){
		for(it=num.begin();it!=num.end();it++){
			*it+valor;
		}
		for (int i=1;i<=50;i++)
		cout << "\n" << *it;
	}
	else if (valor<2 && valor%2!=0){
		for(it=num.begin();it!=num.end();it++){
			*it*(-1);
		for (int i=1;i<=50;i++)
		cout << "\n" << *it;
		}
	}
	else {
		for(it=num.begin();it!=num.end();it++){
			sqrt(*it);
		}	
		for (int i=1;i<=50;i++)
		cout << "\n" << *it;
	}
		 
	return 0;
}

