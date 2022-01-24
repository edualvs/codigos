// Luiz Eduardo Alves da Costa
// Matrícula: 190112701
// Exercício 24
#include <iostream>

using namespace std;

class Retangulo {
	private:
	int lado,altura;
	public:		
	void setLado(int aLado){
			lado = aLado;
		}
	void setAltura(int aAltura){
			altura = aAltura;
		}
	int getLado (){
			return lado;
		}
	int getAltura (){
			return altura;
		}
	int Area (){
		int area;
		area = getLado() * getAltura();
		return area;
	}
};

int main (){
	return 0;
}





















