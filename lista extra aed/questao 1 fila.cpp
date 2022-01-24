//Luiz Eduardo Alves da Costa
//190112701
//Lista 3 (Extra)
#include <iostream>
#include <deque>
using namespace std;

int main(){
	int n;
	deque<int> fila;
	deque<int> :: iterator it;
	while(true){//Menu
			system("cls");
			do{
				cout << "Escolha uma opção: " << endl;
				cout << "1- Inserir valor a fila." << endl;
				cout << "2- Remover primeiro elemento da fila." << endl;
				cout << "3- Mostrar primeiro elemento da fila." << endl;
				cout << "4- Limpar fila." << endl;
				cout << "5- Mostrar tamanho da fila." << endl;
				cout << "6- Exibir fila." << endl;
				cout << "7- Exibir fila invertida." << endl;
				cout << "8- Retirar elementos ímpares da fila." << endl;
				cout << "9- Inverter a fila." << endl;
				cout << "10- Sair." << endl;
				cin >> n;		
			}while(n<=0 || n>10);
		
			switch(n){
				case 1:
					int num;
					cout << "Valor -> ";
					cin >> num;
					fila.push_back(num);
					cout << "Valor adicionado a fila!" << endl;
					break;
				case 2:
					cout << "Valor retirado da fila "<< fila.front() << endl;
					fila.pop_front();
					break;
				case 3:
					cout << "Primeiro valor da fila: " << fila.front() << endl;
					break;
				case 4:
					fila.clear();
					cout << "A fila foi limpa!" << endl;
					break;
				case 5:
					cout << "A fila possui " << fila.size() << " elementos." << endl;
					break;
				case 6:
					cout << "Fila: ";
					for (it = fila.begin(); it != fila.end(); it++)
					{
						cout << *it << "  ";
					}
					cout << endl;
					break;
				case 7:
					cout << "Fila invertida: ";
					for (it = fila.end(); it != fila.begin(); it--)
					{
						cout << *it << "  ";
					}
					cout << endl;
					break;
				case 8:
					for (it = fila.begin(); it != fila.end(); it++)
					{
						if((*it%2)!=0){
							fila.erase(it);
						}
					}
					cout << "Elementos ímpares retirados!" << endl;
					break;
				case 9:
					for (it = fila.end()-1; it != fila.begin(); it--)
					{
						fila.push_back(*it);
					}
					for (int i = 0; i < fila.size()-1; i++){
						fila.pop_front();
					}
					
					break;
				default: 
					return 0;
			}
			system("pause");
		};
	return 0;
}
