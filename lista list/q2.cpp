// Luiz Eduardo Alves da Costa
// 190112701
// Questão 2
#include <iostream>
#include <stack>
#include <locale.h>
using namespace std;

int main (){
	setlocale (LC_ALL, "Portuguese");
	int confere=1;
	char n;
	stack <char> pilha,pilha2,pilhaaux,pilhainvertida,pilhainvertida2;
	cout << "Digite uma sequência de caractéres" << endl << "Quando não quiser para digite 0" << endl;
	while (1){ //Loop
		cin >> n;
		if (n == '0')//Se n=0 quebra o loop
			break;
		pilha.push(n);
		pilha2.push(n);
		pilhaaux.push(n);
	}
		while (!pilhaaux.empty()){
			pilhainvertida.push(pilhaaux.top());
			pilhainvertida2.push(pilhaaux.top());
			pilhaaux.pop();
		}
		
			cout << "Pilha:" << endl;
			
			while (!pilha.empty()){
				cout << pilha.top();
				pilha.pop();
		}
			cout << endl;
			
		cout << "Pilha Invertida:" << endl;
			while (!pilhainvertida.empty()){
				cout << pilhainvertida.top();
				pilhainvertida.pop();
		}
		cout << endl;
		while (!pilha2.empty() && !pilhainvertida2.empty()){
			if  (!(pilha2.top()==pilhainvertida2.top()))
				confere=0;
				pilha2.pop();
				pilhainvertida2.pop();
			}
		if (confere==1){
			cout << "A pilha e a pilha invertida são palíndromos" << endl;
		}
		else 
			cout << "A pilha e a pilha invertida não são palíndromos" << endl;
	return 0;
}
