#include <iostream>
using namespace std;

void menu_principal(){
    system("cls");
	cout << "***************************************" << endl;
	cout << "   Digite o número da opção desejada" << endl;
	cout << "***************************************" << endl;
	cout << "   [1] Cadastrar máquina na rede" << endl;
	cout << "   [2] Listar máquinas cadastradas" << endl;
	cout << "   [3] Conectar a uma máquina" << endl;
	cout << "   [4] Mostrar Grafo" << endl;
	cout << "   [5] Sair" << endl;
	cout << "***************************************" << endl;		
}

void menu_maquina(maquina escolhida){
    system("cls");
    cout << "***************************************" << endl;
    cout << "   Você está conectado a: "<< escolhida.nome << endl;
    cout << "***************************************" << endl;
    cout << "   [1] Enviar Pacote" << endl;
    cout << "   [2] Listar Pacotes" << endl;
    cout << "   [3] Tornar esta máquina o roteador" << endl;
    cout << "   [4] Remover máquina do sistema" << endl;
    cout << "   [5] Voltar" << endl;
    cout << "***************************************" << endl;	
}
