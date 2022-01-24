#include <iostream>
#include <locale.h>
#include <vector>
#include <cstring>
using namespace std;
int main (){
	setlocale(LC_ALL, "Portuguese");
	vector<int> vetor;
	vector<int>::iterator it;
	vetor.push_back (1); 
	vetor.push_back (0);
	vetor.push_back (5);
	vetor.push_back (-2);
	vetor.push_back (-5);
	vetor.push_back (7);	
	cout << "O vetor possui os seguintes valores: \n";
	for (it=vetor.begin();it!=vetor.end();it++)
		cout << *it << "\n";
	int soma;
	it=vetor.begin();
	soma=*it+*(it+1)+*(it+5);
	cout << "\n A soma das posições 0, 1 e 5 do vetor é: " << soma;
	++it;
	++it;
	++it;
	cout << "\n\n\nRetirando o número -2 do vetor \n";
	it=vetor.erase(it);
	cout << "\n";
	for (it=vetor.begin();it!=vetor.end();it++)
		cout << *it << "\n";
	cout << "\n";
	cout << "\nAdicionando o número 100 no vetor \n";
	--it;
	--it;
	vetor.insert(it,100) ;
	for (it=vetor.begin();it!=vetor.end();it++)
		cout << *it << "\n";
	return 0;
	
}
