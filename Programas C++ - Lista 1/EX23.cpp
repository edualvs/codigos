//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Exercício 23
#include <iostream>
using namespace std;

class Retangulo {
	private:
		int lado;
		int altura;
	public:
		Retangulo(){};
		Retangulo(int iLado, int iAltura){
			lado = iLado;
			altura = iAltura;
		};
		int getLado(){
			return lado;
		}
		int getAltura (){
			return altura;
		}
		int CalcArea(){
			int area = getLado()*getAltura();
			return area;
		}	
};



int main (){
	Retangulo retangulo(5,5);
	cout << "A area do retangulo e igual a: " <<retangulo.CalcArea();
	return 0;
}
