//cadastra máquina no sistema
void cadastro(list<maquina> & lista, Network & rede){
	maquina novo;
	
	//Recebe o nome da máquina
	system("cls");
	cout << "-------------------------------" << endl;
	cout << "   Atribua um nome a máquina" << endl;
	cout << "-------------------------------" << endl << endl;
	cout << " > ";
	cin >> novo.nome;
	
	//Atribui IP para a maquina
	int id = 0;
	for (int i=1; i <= 255; i++) {
		bool ocupado= false;
		string padrao= "192.168.0.";
		string ip_atual= padrao + to_string(i);
		//verifica se o ip está sendo ocupado atualmente
		for (list<maquina>::iterator ponteiro_lista = lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
			maquina temp;
			temp= *ponteiro_lista;
			if (temp.ip == ip_atual) {
				ocupado = true;
				break;
			}
		}

		//Caso não tenha nenhuma maquina cadastrada ele cadastra a primeira como roteador
		if (lista.empty()) {
			novo.roteador = true;
			rede.roteador = pega_ip(ip_atual);
		}

		//caso ip livre atribui para a maquina
		if (!(ocupado == true)) {
			novo.ip= ip_atual;
			id = i;
			break;
		}
	}
	
	lista.push_back(novo);
	rede.adiciona_aresta(id, lista);
}

//remove uma máquina do sistema
void remover(list<maquina> & lista, string ip_atual) {
	for (list<maquina>::iterator ponteiro_lista= lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
		if (ponteiro_lista->ip == ip_atual) {
			if (ponteiro_lista->roteador == true) {
				system("cls");
				cout << "-------------------------------" << endl;
				cout << "   Não foi possí­vel remover" << endl;
				cout << "   esta máquina, atualmente" << endl;
				cout << "   ela é o roteador do sistema" << endl;
				cout << "-------------------------------" << endl << endl;
				system("pause");
			} else
				lista.erase(ponteiro_lista);
			break;
		}
	}	
}

//Lista o nome e Ip de todas as maquinas do sistema
void listar(list<maquina> & lista) {
	
	for (list<maquina>::iterator ponteiro_lista = lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
		maquina temp;
		temp= *ponteiro_lista;
		cout << "-------------------------------" << endl;
		cout << "   Nome: " << temp.nome << endl;
		cout << "   Ip: " << temp.ip << endl;
	}
	
}

//Altera qual maquina atua como roteador
bool muda_roteador(string ip, list<maquina> & lista, Network & rede) {
	for (list<maquina>::iterator ponteiro_lista = lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
		if (ponteiro_lista->roteador == true) {
			ponteiro_lista->roteador= false;
		}
		if (ponteiro_lista->ip == ip) {
			ponteiro_lista->roteador= true;
			rede.roteador= pega_ip(ponteiro_lista->ip);
		}
	}
	return true;
}