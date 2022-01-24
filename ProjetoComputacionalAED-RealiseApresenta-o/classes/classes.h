//Máquinas do Sistema
class maquina {
	public: 
		string nome;
		string ip;
        bool roteador= false;
        vector<int> pacotes;
};

//Rede (Onde o Dijkstra é feito)
class Network {
    public:
        vector<set<pair<int, int>>> Grafo;
        int roteador, tamanho_rede;

        //Construtor da classe
        Network(int tamanho){
            Grafo.assign(tamanho, set<pair<int, int>>());
            roteador =  -1;
            tamanho_rede = tamanho;
            srand(time(NULL));
        }

        //Recupera caminho do Dijkstra
        void print_path(vector<int> parent, int destino, vector<string> & caminho){
            if(parent[destino] == -1)
                return;
            print_path(parent, parent[destino], caminho);
            caminho.push_back(to_string(destino));
        }

        //Algoritmo de Dijkstra (Acha o menor caminho)
        int dijkstra(int origem, int destino, vector<string> & caminho){
            vector<int> dist(tamanho_rede, INT_MAX);
            vector<int> parent(tamanho_rede, -1);
            priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
            dist[origem] = 0;
            pq.push(make_pair(origem, 0));

            while(!pq.empty()) {
                int u = pq.top().first, w = pq.top().second;
                pq.pop();
                if(w > dist[u])
                    continue;

                for(pair<int, int> p : Grafo[u]){
                    int v = p.first, w = p.second;
                    if(dist[u] + w < dist[v]){
                        dist[v] = dist[u]+w;
                        parent[v] = u;
                        pq.push(make_pair(v, dist[v]));
                    }
                }
            }
            caminho.push_back(to_string(origem));
            print_path(parent, destino, caminho);
            return dist[destino];
        }

        //Lê grafo salvo no arquivo
        void adiciona_aresta_definida(int origem, int destino, int peso) {
            Grafo[origem].insert(make_pair(destino, peso));
            Grafo[destino].insert(make_pair(origem, peso));
        }

        //Cria as arestas de uma maquina que foi criada
        void adiciona_aresta(int indice, list<maquina> & lista) {
            for(list<maquina>::iterator it = lista.begin(); it!=lista.end() ; it++) {
                int peso = (rand()%100)+1;
                string ip = (*it).ip;
                int vertice = pega_ip(ip);
                if(vertice != indice){
                    Grafo[indice].insert(make_pair(vertice, peso));
                    Grafo[vertice].insert(make_pair(indice, peso));
                }
            }
        }

        //Remove aresta de maquinas removidas do sistema
        void remove_aresta(int indice) {
            Grafo[indice].clear();
            for(int i= 0; i < tamanho_rede; i++) {
                if(Grafo[i].size() > 0) {
                    set<pair<int, int>>::iterator it;

                    for(it= Grafo[i].begin(); it != Grafo[i].end(); it++) {
                        if((*it).first == indice)
                            break;
                    }
                    if(it != Grafo[i].end())
                        Grafo[i].erase(it);
                }

            }
        }

        //Imprime o menor caminho percorrido até o destino passando pelo roteador
        void menor_distancia(int origem, int destino) {
            if(roteador == -1) {
                cout << "---------------------------" << endl;
                cout << "   Roteador não definido" << endl;
                cout << "---------------------------" << endl;
            } else {
                vector<string> caminho;
                int peso= dijkstra(origem, roteador, caminho);
                //Remoção do roteador duplicado por conta da função
                caminho.pop_back();
                peso= peso + dijkstra(roteador, destino, caminho);

                system("cls");
                cout << "---------------------------" << endl;
                cout << "   Origem: 192.168.0." << origem << endl;
                cout << "   Destino: 192.168.0." << destino << endl;
                cout << "   Roteador: 192.168.0." << roteador << endl;
                cout << "---------------------------" << endl << endl;
                cout << " Caminho percorrido: " << endl;
                cout << "    ";
                for (int i=0; i < caminho.size(); i++) {
                    if (i == caminho.size()-1)
                        cout << caminho[i] << endl << endl;
                    else
                        cout << caminho[i] << " -> ";
                }
                cout << "Distância total percorrida: " << peso << endl;
				system("pause");
            }
        }

        //Imprime todos os vértices e arestas do grafo
        void listagem_grafo() {
            //Percorre o grafo
            for(int i=0;i<tamanho_rede;i++) {
                if(Grafo[i].size() > 0) {
                    for(auto x : Grafo[i]) {
                        printf("Origem: %3d -> Destino: %3d | Peso: %3d \n", i, x.first, x.second);
                        //cout << "Origem: " << i << " -> Destino: " << x.first << " | Peso: " << x.second << endl;
                    }
                }
            }
        }
};

//Tabela Hash
class Hash {
    public:
	string frase;

    //Salva a posição na maquina que recebeu o pacote e retorna a posição
    int registra_pacote(string destino, string pacote, list<maquina> & lista) {
        int ipdestino= pega_ip(destino);
        int posicao = passa_hash(pacote, 256);
        
        //procura as informações da maquina escolhida
        for (list<maquina>::iterator ponteiro_lista= lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
            if (ponteiro_lista->ip == destino) {
                //salva a posição do pacote no objeto
                ponteiro_lista->pacotes.push_back(posicao);
                break;
            }
        }
        return posicao;
    }

    //Passa o pacote pela tabela Hash
    int passa_hash(string pacote, int tamanho) {
        //atribui uma posição do pacote na hash
        unsigned h = 0;
        for (int i = 0; i < pacote.length(); i++) {
            h = (h * 131 + pacote[i]);
        }
        return h % tamanho; 
    }
};