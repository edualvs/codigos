// Luiz Eduardo Alves da Costa
// Matr�cula: 190112701
// Exerc�cio 24
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





















