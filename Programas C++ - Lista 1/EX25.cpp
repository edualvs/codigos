// Luiz Eduardo Alves da Costa
// Matrícula: 190112701
// Exercício 25
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

class Paralelepipedo : public Retangulo {
	private:
		
	int lado,altura,profundidade;
	public:
		void setLado(int aLado){
			lado = aLado;
		}
		void setAltura(int aAltura){
			altura = aAltura;
		}
		void setProfundidade(int aProfundidade){
			profundidade = aProfundidade;
		}
		int getLado() {
			return lado;
		}
		int getAltura() {
			return altura;
		}
		int getProfundidade() {
			return profundidade;
		}
		int Volume (){
			int volume;
			volume = getLado() * getAltura() * getProfundidade();
			return volume;
		}
};

int main (){
	Paralelepipedo para1;
	para1.setLado(5);
	para1.setAltura(5);
	para1.setProfundidade(5);
	cout << "Volume: " << para1.Volume() << endl;
	return 0;
}



