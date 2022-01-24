// Luiz Eduardo Alves da Costa
// Matrícula: 190112701
// Exercício 27
#include <iostream>
#include <vector>
using namespace std;

class MinhaString {
	private:
	vector <char> v;
	public:
		
	MinhaString (vector<char> vtemp){
		
	}
	
	int tamanho (){
		return v.size();
	}
	
	bool compara (vector<char> x,vector<char> y){
		if (x.size()==y.size()){
		for (int i=0; i<x.size();i++){
			if (x[i]==y[i])
			return true;
			}
		}
		else
		return false;
	}
	
	void printMe(vector<char> x){
		for (int i=0; i<x.size();i++)
			cout << x[i] << endl; 
	}
};

int main (){
	
	vector <string> v;
	return 0;
}
