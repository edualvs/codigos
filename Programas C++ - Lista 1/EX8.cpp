//Luiz Eduardo Alves da Costa
//190112701
//Exerc�cio 8

#include<iostream>
1. int z=0; //Criando uma v�riavel inteira global z=0
2. void troca(int *x, int *y) {//Criando uma fun��o troca que n�o retorna nada, com argumentos *x e *y
3. int z;//Incluindo a vari�vel inteira global na fun��o troca
4. z=*x;//Passando o valor de z por refer�ncia a x, ou seja, dando outro nome a z
5. *x=*y;//Passando o valor de x por ref�ncia a y
6. *y=z;//Como x � outro nome para z e y � outro nome para x, consequentemente, y � um valor de refer�ncia para z.
}
int main() {
7. int a,b;//Criando v�riaveis inteiras a e b
8. std::cin >> a >> b >> z; //Pedindo ao usu�rio para escrever valores para a,b e z;
9. troca(&a,&b);//Chamando a fun��o troca com o argumentos de entrada a e b;
10. std::cout << a << b << z << std::endl;//As sa�das ser�o as mesma, no caso, o falo que o usu�rio selecionou para z, por causa, da fun��o troca
}
