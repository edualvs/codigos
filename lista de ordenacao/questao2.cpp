//Luiz Eduardo Alves da Costa
//190112701
//Lista de ordenação - Questão 2 - Quick Sort
#include <iostream>
using namespace std;

//Quick Sort
void quickSort(string &str, int begin, int end) {
    int i = begin, j = end;
    int middle = str[(begin + end) / 2];
    while(i<=j){
        while(str[i]>middle)
            i++;
        while(str[j]<middle)
            j--;
        if(i<=j){
            swap(str[i], str[j]);
            i++; j--;
        }
	};
        if(begin<j)
            quickSort(str, begin, j);
        if(i<end)
        	quickSort(str, i, end);
} 
    
int main (){
	string str;
    cout << "Digite uma frase:" << endl;
    //Lendo a frase
    getline(cin,str);
    //Chamando a função de ordenação
    quickSort(str, 0, str.size()-1);
    //Imprimindo a string ordenada
    cout << "Frase ordenada: "<< str << endl;
	return 0;
}
