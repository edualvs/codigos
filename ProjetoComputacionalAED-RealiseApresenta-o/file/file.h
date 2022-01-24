//Lê o arquivo da tabela hash
void le_arquivo_hash(Hash *tabela, list<maquina> &lista) {
	fstream arquivo;
	arquivo.open("file/hash.txt", fstream::in);

	Hash *tempHash = new Hash[256];
	string linha;
    int posicao;

	while(getline(arquivo,linha)){
        //Pega qual a maquina recebeu o pacote pelo ip
        for (list<maquina>::iterator ponteiro_lista = lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
            if (ponteiro_lista->ip == linha) {
                getline(arquivo,linha);
                //Atribui uma posição ao pacote
                posicao= tabela->registra_pacote(ponteiro_lista->ip, linha, lista);
                //Salva o pacote na tabela
				tabela[posicao].frase = linha;
                break;
            }
        }
	}
}

//Salva a tabela hash em um arquivo
void salva_arquivo_hash(Hash *tabela,list<maquina> &lista) {
	fstream arquivo;
	arquivo.open("file/hash.txt", fstream::trunc | fstream::out);

    //Pega todas a maquina do sistema
    for (list<maquina>::iterator ponteiro_lista= lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
        //Pra cada maquina verifica se existem e quantos são os pacotes recebidos
        for (int i=0; i != ponteiro_lista->pacotes.size(); i++) {
            //Coloca os pacotes e quem recebeu no arquivo
            if (ponteiro_lista == lista.end()) {
                arquivo << ponteiro_lista->ip << endl;
                arquivo << tabela[ponteiro_lista->pacotes[i]].frase;
            } 
            else {
                arquivo << ponteiro_lista->ip << endl;
                arquivo << tabela[ponteiro_lista->pacotes[i]].frase << endl;
            }
        }
	}
	arquivo.close();
}

//lê arquivos registrados no sistema de um arquivo txt
void le_arquivo(list<maquina> & lista, Network & rede) {

	fstream arquivo;
	arquivo.open("file/sistema.txt", fstream::in);

	string linha; 
	maquina temp;

    while(getline(arquivo, linha)) {
        //Verifica se é a linha com o identificador de iní­cio do grafo
        if(linha.compare("grafo") == 0) {

            //Salva as informações em variáveis temporárias
            while(getline(arquivo, linha)) {

                stringstream ss(linha);
                string token;
                int indice = 0, origem, destino, peso;

                while(ss >> token){
                    int i = stoi(token);

                    if(indice == 0){
                        origem = i;
                    } else if (indice == 1) {
                        destino = i;
                    } else {
                        peso = i;
                    }
                    
                    indice++;
                }

                rede.adiciona_aresta_definida(origem, destino, peso);
            }
            break;
        }else{
            //Coloca o nome no Arquivo
            temp.nome= linha;
            //Coloca o ip no Arquivo
            getline(arquivo, linha);
            temp.ip= linha;
            //Coloca se é o roteador no Arquivo
            getline(arquivo, linha);
            if (linha == "1") {
                temp.roteador= true;
                rede.roteador = pega_ip(temp.ip);
            }
            //Coloca a maquina na lista
            lista.push_back(temp);
        }
    }
	arquivo.close();
}

//salva maquinas registradas no sistema dentro de um arquivo txt
void salva_arquivo(list<maquina> & lista, Network & rede) {

	fstream arquivo;
	arquivo.open("file/sistema.txt", fstream::trunc | fstream::out);
	
    //Pega todas as maquinas do sistema e as salva no arquivo
	for (list<maquina>::iterator ponteiro_lista= lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
		if (ponteiro_lista == lista.end()) {
			arquivo << ponteiro_lista->nome << endl;
			arquivo << ponteiro_lista->ip << endl;
			arquivo << ponteiro_lista->roteador;
		} else {
			arquivo << ponteiro_lista->nome << endl;
			arquivo << ponteiro_lista->ip << endl;
            arquivo << ponteiro_lista->roteador << endl;
		}
	}
    //Coloca um identificador para quando o arquivo for lido sabermos que acabaram as maquinas e o grafo começou
	arquivo << "grafo" << endl;
    //Coloca o grafo no arquivo
	for(int i = 0;i<rede.tamanho_rede;i++){
	    if(rede.Grafo[i].size() > 0){
	        for(auto p : rede.Grafo[i]){
	            arquivo << i << " " << p.first << " " << p.second << endl;
	        }
	    }
	}
	arquivo.close();
}
