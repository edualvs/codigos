//Luiz Eduardo Alves da Costa
//Matr�cula: 190112701
//Exerc�cio 20

int misterio(std::string nome1, std::string nome2) {
fstream fr, fw;
std::string b;
fr.open(nome1, ios::in);
fw.open(nome2, ios::out);
while (getline(fr, b))
fw << b << std::endl;
fr.close();
fw.close();
return 0;
}

/*
(a) Os par�metros passados para a fun��o s�o duas strings que ser�o os nomes dos dois arquivos criados.

(b) Em fr.open o primeiro par�metro passado � o nome do arquivo dado  pela string nome1 e este � um arquivo de input, ou seja, um arquivo de leitura. J� em fw.open al�m do nome que ser� dado pela string nome2
o outro par�metro indica um arquivo de output, ou seja, um arquivo para ser escrito.

(c) 
*/
