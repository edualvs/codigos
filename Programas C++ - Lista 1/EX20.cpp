//Luiz Eduardo Alves da Costa
//Matrícula: 190112701
//Exercício 20

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
(a) Os parâmetros passados para a função são duas strings que serão os nomes dos dois arquivos criados.

(b) Em fr.open o primeiro parâmetro passado é o nome do arquivo dado  pela string nome1 e este é um arquivo de input, ou seja, um arquivo de leitura. Já em fw.open além do nome que será dado pela string nome2
o outro parâmetro indica um arquivo de output, ou seja, um arquivo para ser escrito.

(c) 
*/
