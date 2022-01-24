// Luiz Eduardo Alves da Costa
// Matrícula: 190112701
// Exercício 26
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
	Retangulo ret1;
	Retangulo ret2;
	Retangulo ret3;
	ret1.setLado(3);
	ret1.setAltura(3);
	ret2.setLado(4);
	ret2.setAltura(4);
	ret3.setLado(5);
	ret3.setAltura(5);
	cout << ret1.Area() << endl;
	cout << ret2.Area() << endl;
	cout << ret3.Area() << endl;
	return 0;
}
