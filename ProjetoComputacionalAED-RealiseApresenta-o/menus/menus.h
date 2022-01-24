#include <iostream>
using namespace std;

void menu_principal(){
    system("cls");
	cout << "***************************************" << endl;
	cout << "   Digite o n�mero da op��o desejada" << endl;
	cout << "***************************************" << endl;
	cout << "   [1] Cadastrar m�quina na rede" << endl;
	cout << "   [2] Listar m�quinas cadastradas" << endl;
	cout << "   [3] Conectar a uma m�quina" << endl;
	cout << "   [4] Mostrar Grafo" << endl;
	cout << "   [5] Sair" << endl;
	cout << "***************************************" << endl;		
}

void menu_maquina(maquina escolhida){
    system("cls");
    cout << "***************************************" << endl;
    cout << "   Voc� est� conectado a: "<< escolhida.nome << endl;
    cout << "***************************************" << endl;
    cout << "   [1] Enviar Pacote" << endl;
    cout << "   [2] Listar Pacotes" << endl;
    cout << "   [3] Tornar esta m�quina o roteador" << endl;
    cout << "   [4] Remover m�quina do sistema" << endl;
    cout << "   [5] Voltar" << endl;
    cout << "***************************************" << endl;	
}
