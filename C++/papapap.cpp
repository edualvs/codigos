#include <iostream>
#include <locale.h>
using namespace std;

int main(){
	setlocale(LC_ALL,"portuguese");
	string nome1="",nome2="";
	char sair=' ';
	int x=0,y=0,p1=0,p2=0,v=0;
	cout<<"==>Jogo da Velha<==\n";
	cout<<"Digite o nome do jogador 1(X): ";
	cin>>nome1;
	system("cls");
	cout<<"==>Jogo da Velha<==\n";
	cout<<"Jogador 1: "<<nome1<<endl;
	cout<<"Digite o nome do jogador 2(O): ";
	cin>>nome2;
	system("cls");
	cout<<"==>Jogo da Velha<==\n";
	cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
	cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
	char tabuleiro[3][3];
	for(int i=0;i<=2;i++){
			for(int j=0;j<=2;j++){
				tabuleiro[i][j]=' ';
			}
		}
	for(int i=0;i<=2;i++){
		cout<<endl<<"-";
		for(int l=0;l<=2;l++)cout<<"--";
		cout<<endl;
		cout<<"|";
		for(int j=0;j<=2;j++){
			cout<<tabuleiro[i][j]<<"|";
		}
	}
	cout<<endl<<"-";
	for(int l=0;l<=2;l++)cout<<"--";
	cout<<endl;
	
	//Começo da lógica do jogo.
	while(true){
		do{
		x=0,y=0;
		while((x<=0) || (x>=4)||(isalpha(x))){
			cout<<nome1<<", digite a linha da jogada(1 a 3): ";
			cin>>x;
		}
		while((y<=0)||(y>=4)||(isalpha(y))){
			cout<<nome1<<", digite a  coluna da jogada(1 a 3): ";
			cin>>y;
		}
	}	while(tabuleiro[x-1][y-1]!=' ');
		tabuleiro[x-1][y-1]='X';
		v++;
		if(v>=9){
			v=0;
			system("cls");
			cout<<"==>Jogo da Velha<==\n";
			cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
			cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
			for(int i=0;i<=2;i++){
				cout<<endl<<"-";
				for(int l=0;l<=2;l++)cout<<"--";
				cout<<endl;
				cout<<"|";
				for(int j=0;j<=2;j++){
					cout<<tabuleiro[i][j]<<"|";
				}
			}
			cout<<endl<<"-";
			for(int l=0;l<=2;l++)cout<<"--";
			cout<<endl;
			cout<<"O jogo deu velha!"<<endl;
			
			cout<<"Deseja continuar jogando? [S para sair]: ";
			cin>>sair;
			if(sair=='s'||sair=='S'){
				if(p1>p2){
					cout<<nome1<<" ganhou com "<<p1<<" pontos!";
					return 0;
				}
				else if(p2>p1){
					cout<<nome2<<" ganhou com "<<p2<<" pontos!";
					return 0;
				}
				else{
					cout<<nome1<<" e "<<nome2<<" empataram!";
					return 0;
				}
			}
			else{
				for(int i=0;i<=2;i++){
					for(int j=0;j<=2;j++){
					tabuleiro[i][j]=' ';
					}
				}
			}
		}
		if(tabuleiro[0][0]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[2][2]=='X'||tabuleiro[2][0]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[0][2]=='X'||tabuleiro[0][0]=='X'&&tabuleiro[0][1]=='X'&&tabuleiro[0][2]=='X'||tabuleiro[1][0]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[1][2]=='X'||tabuleiro[2][0]=='X'&&tabuleiro[2][1]=='X'&&tabuleiro[2][2]=='X'||tabuleiro[0][0]=='X'&&tabuleiro[1][0]=='X'&&tabuleiro[2][0]=='X'||tabuleiro[0][1]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[2][1]=='X'||tabuleiro[0][2]=='X'&&tabuleiro[1][2]=='X'&&tabuleiro[2][2]=='X'){
			p1++;
			system("cls");
			cout<<"==>Jogo da Velha<==\n";
			cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
			cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
			for(int i=0;i<=2;i++){
				cout<<endl<<"-";
				for(int l=0;l<=2;l++)cout<<"--";
				cout<<endl;
				cout<<"|";
				for(int j=0;j<=2;j++){
					cout<<tabuleiro[i][j]<<"|";
				}
			}
			cout<<endl<<"-";
			for(int l=0;l<=2;l++)cout<<"--";
			cout<<endl;
			cout<<nome1<<" ganhou a rodada!"<<endl;
			cout<<"Deseja continuar jogando? [S para sair]: ";
			cin>>sair;
			if(sair=='s'||sair=='S'){
				if(p1>p2){
					cout<<nome1<<" ganhou com "<<p1<<" pontos!";
					return 0;
				}
				else if(p2>p1){
					cout<<nome2<<" ganhou com "<<p2<<" pontos!";
					return 0;
				}
				else{
					cout<<nome1<<" e "<<nome2<<" empataram!";
					return 0;
				}
			}
			else{
				for(int i=0;i<=2;i++){
					for(int j=0;j<=2;j++){
					tabuleiro[i][j]=' ';
					}
				}
			}
			
		}	
		system("cls");
		cout<<"==>Jogo da Velha<==\n";
		cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
		cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
		for(int i=0;i<=2;i++){
			cout<<endl<<"-";
			for(int l=0;l<=2;l++)cout<<"--";
			cout<<endl;
			cout<<"|";
			for(int j=0;j<=2;j++){
				cout<<tabuleiro[i][j]<<"|";
			}
		}
		cout<<endl<<"-";
		for(int l=0;l<=2;l++)cout<<"--";
		cout<<endl;
		do{
		x=0,y=0;
		while(x<1||x>3||isalpha(x)){
			cout<<nome2<<", digite a linha da jogada(1 a 3): ";
			cin>>x;
		}
		while((y<1)||(y>3)||isalpha(y)){
			cout<<nome2<<", digite a  coluna da jogada(1 a 3): ";
			cin>>y;
		}
	}	while(tabuleiro[x-1][y-1]!=' ');
		tabuleiro[x-1][y-1]='O';
		v++;
		if(v>=9){
			v=0;
			system("cls");
			cout<<"==>Jogo da Velha<==\n";
			cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
			cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
			for(int i=0;i<=2;i++){
				cout<<endl<<"-";
				for(int l=0;l<=2;l++)cout<<"--";
				cout<<endl;
				cout<<"|";
				for(int j=0;j<=2;j++){
					cout<<tabuleiro[i][j]<<"|";
				}
			}
			cout<<endl<<"-";
			for(int l=0;l<=2;l++)cout<<"--";
			cout<<endl;
			cout<<"O jogo deu velha!"<<endl;
			
			cout<<"Deseja continuar jogando? [S para sair]: ";
			cin>>sair;
			if(sair=='s'||sair=='S'){
				if(p1>p2){
					cout<<nome1<<" ganhou com "<<p1<<" pontos!";
					return 0;
				}
				else if(p2>p1){
					cout<<nome2<<" ganhou com "<<p2<<" pontos!";
					return 0;
				}
				else{
					cout<<nome1<<" e "<<nome2<<" empataram!";
					return 0;
				}
			}
			else{
				for(int i=0;i<=2;i++){
					for(int j=0;j<=2;j++){
					tabuleiro[i][j]=' ';
					}
				}
			}
		}
		if(tabuleiro[0][0]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[2][2]=='O'||tabuleiro[2][0]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[0][2]=='O'||tabuleiro[0][0]=='O'&&tabuleiro[0][1]=='O'&&tabuleiro[0][2]=='O'||tabuleiro[1][0]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[1][2]=='O'||tabuleiro[2][0]=='O'&&tabuleiro[2][1]=='O'&&tabuleiro[2][2]=='O'||tabuleiro[0][0]=='O'&&tabuleiro[1][0]=='O'&&tabuleiro[2][0]=='O'||tabuleiro[0][1]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[2][1]=='O'||tabuleiro[0][2]=='O'&&tabuleiro[1][2]=='O'&&tabuleiro[2][2]=='O'){
			p2++;
			system("cls");
			cout<<"==>Jogo da Velha<==\n";
			cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
			cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
			for(int i=0;i<=2;i++){
				cout<<endl<<"-";
				for(int l=0;l<=2;l++)cout<<"--";
				cout<<endl;
				cout<<"|";
				for(int j=0;j<=2;j++){
					cout<<tabuleiro[i][j]<<"|";
				}
			}
			cout<<endl<<"-";
			for(int l=0;l<=2;l++)cout<<"--";
			cout<<endl;
			cout<<nome2<<" ganhou a rodada!"<<endl;
			cout<<"Deseja continuar jogando? [S para sair]: ";
			cin>>sair;
			if(sair=='s'||sair=='S'){
				if(p1>p2){
					cout<<nome1<<" ganhou com "<<p1<<" pontos!";
					return 0;
				}
				else if(p2>p1){
					cout<<nome2<<" ganhou com "<<p2<<" pontos!";
					return 0;
				}
				else{
					cout<<nome1<<" e "<<nome2<<" empataram!";
					return 0;
				}
			}
			else{
				for(int i=0;i<=2;i++){
					for(int j=0;j<=2;j++){
					tabuleiro[i][j]=' ';
					}
				}
			}
		}
		system("cls");
		cout<<"==>Jogo da Velha<==\n";
		cout<<"Jogador 1(X): "<<nome1<<" "<<p1<<" pontos."<<endl;
		cout<<"Jogador 2(O): "<<nome2<<" "<<p2<<" pontos."<<endl;
		for(int i=0;i<=2;i++){
			cout<<endl<<"-";
			for(int l=0;l<=2;l++)cout<<"--";
			cout<<endl;
			cout<<"|";
			for(int j=0;j<=2;j++){
				cout<<tabuleiro[i][j]<<"|";
			}
		}
		cout<<endl<<"-";
		for(int l=0;l<=2;l++)cout<<"--";
		cout<<endl;
}
	return 0;
}
