#include "source.h"
//Projeto Computacional - AED
//Guilherme Leal de Medeiros - 190136049
//Luiz Eduardo Alves - 190112701
//Maria Eloisa - 130124958
//Vitor Coêlho - 190118270

int main() {
	setlocale(LC_ALL, "Portuguese");
	bool menu2= true, existe=false;
	//objeto da maquina escolhida
	maquina escolhida;
	//recebe input para os menus
	int tecla;
	//receve ip da maquina escolhida
	int ip=0, posicao=0;
	string ip_escolhido, ip_destino, padrao= "192.168.0.";
	//recebe a frase a ser envidada
	string pacote="";
	//recebe confirmação de remoção de maquina
	char escolha;
	//loop de execução do menu inicial

	list<maquina> lista;
	Network rede(256);
	Hash *tabela = new Hash[256];

	//Lê arquivos com o sistema salvo
	le_arquivo(lista, rede);
	le_arquivo_hash(tabela, lista);

	while (true) {
        menu_principal();
		tecla= getch();
		
		switch (tecla) {
			case 49:
				cadastro(lista, rede);
				break;
			case 50:
				listar(lista);
				//pausa para o usuário ler a lista entes dela ser apagada
				system("pause");
				break;
			case 51:
				do {
					do {
						system("cls");
						
						//lista todas as maquinas do sistema
						listar(lista);
						
						//recebe a entrada da escolha da maquina após o listar
						message(1);
						cin >> ip;
					} while (ip < 1 || ip > 255);

					//faz a conversão de int para string e salva o ip
					ip_escolhido= padrao + to_string(ip);
					
					//procura as informações da maquina escolhida
					for (list<maquina>::iterator ponteiro_lista= lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
						if (ponteiro_lista->ip == ip_escolhido) {
							existe= true;
							escolhida= *ponteiro_lista;
							break;
						}
					}
				} while (existe == false);
				
				menu2= true;
				while (menu2) {
                    menu_maquina(escolhida);
					tecla= getch();
					
					switch (tecla) {
						case 49:
							//Caso o número de maquinas cadastradas seja menor que 2
							if (lista.size() < 2) {
                                message(2);
								break;
							}
							
							//Recebe a frase a ser enviada
                            message(3);
							cin.ignore();
							getline(cin, pacote);
							
							do {
								do {
									existe= false;
									system("cls");	
									//lista todas as maquinas do sistema
									listar(lista);
									
									//recebe a entrada da escolha da maquina após o listar
                                    message(4);
									cin >> ip;
								} while (ip < 1 || ip > 255);
								//faz a conversão de int para string e salva o ip
								ip_destino= padrao + to_string(ip);
								
								//verifica se a maquina exite
								for (list<maquina>::iterator ponteiro_lista = lista.begin(); ponteiro_lista != lista.end(); ponteiro_lista++) {
									if (ponteiro_lista->ip == ip_destino) {
										if (ponteiro_lista->ip != ip_escolhido) {
											existe= true;
											break;
										}
									}
								}
							} while (existe == false);
							
							//Inicia as funções de "envio" do pacote
							posicao= tabela->registra_pacote(ip_destino, pacote, lista);
							tabela[posicao].frase = pacote;
							rede.menor_distancia(pega_ip(ip_escolhido), pega_ip(ip_destino));
							break;
						case 50:
							//Imprime Todos os pacotes recebidos pela maquina ( Posição na tabela Hash e depois conteúdo)
							printf(" posição | pacote \n\n");
							for (int i=0; i !=escolhida.pacotes.size(); i++) {
								printf(" %7d | ", escolhida.pacotes[i]);
								cout << tabela[escolhida.pacotes[i]].frase << endl;
							}
            				system("pause");
            				break;
						case 51:
							//Troca de maquina que age como roteador
							system("cls");
							cout << "-----------------------------------------" << endl;
							if (muda_roteador(escolhida.ip, lista, rede)) {
								cout << "   O Roteador foi alterado com sucesso" << endl;
							} else {
								cout << "   Não foi possÃ­vel alterar o roteador" << endl;
							}
							cout << "-----------------------------------------" << endl << endl;
							system("pause");
							break;
						case 52:
							//confirma a opção
							do {
                                message(5);
								cin >> escolha;
							} while (escolha != 'S' && escolha != 's' && escolha != 'n' && escolha != 'N');
							
							//caso a resposta seja sim apaga a maquina
							if (escolha == 'S' || escolha == 's') {
								remover(lista, escolhida.ip);
								menu2= false;	
							}
							
							break;
						case 53:
							menu2= false;
							break;
					}
				}
				break;
			case 52:
				//Imprime todo o grafo na tela
				rede.listagem_grafo();
				system("pause");
				break;
			case 53:
				//Salva o sistema nos arquivos
				salva_arquivo(lista, rede);
				salva_arquivo_hash(tabela, lista);
				return 0;
				break;
		}
	}
	//Salva o sistema nos arquivos
	salva_arquivo(lista, rede);
	salva_arquivo_hash(tabela, lista);
	return 0;
}