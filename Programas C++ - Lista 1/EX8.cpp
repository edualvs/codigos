//Luiz Eduardo Alves da Costa
//190112701
//Exercício 8

#include<iostream>
1. int z=0; //Criando uma váriavel inteira global z=0
2. void troca(int *x, int *y) {//Criando uma função troca que não retorna nada, com argumentos *x e *y
3. int z;//Incluindo a variável inteira global na função troca
4. z=*x;//Passando o valor de z por referência a x, ou seja, dando outro nome a z
5. *x=*y;//Passando o valor de x por refência a y
6. *y=z;//Como x é outro nome para z e y é outro nome para x, consequentemente, y é um valor de referência para z.
}
int main() {
7. int a,b;//Criando váriaveis inteiras a e b
8. std::cin >> a >> b >> z; //Pedindo ao usuário para escrever valores para a,b e z;
9. troca(&a,&b);//Chamando a função troca com o argumentos de entrada a e b;
10. std::cout << a << b << z << std::endl;//As saídas serão as mesma, no caso, o falo que o usuário selecionou para z, por causa, da função troca
}
