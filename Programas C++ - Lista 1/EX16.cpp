/*
Luiz Eduardo Alves da Costa
190112701
Exercício 16

16. Considere o trecho de programa abaixo. Depois de executado o trecho inteiro, quais os valores
associados aos itens de (a) a (i)? Suponha que os endere¸cos das vari´aveis a, b e c s˜ao 1000, 1004
e 1008, respectivamente.

float a,b;				 (a)&a
float c, *pa, *pb; 		 (b)&b
a=0.001;  			   	 (c)&c
b=0.003;  				 (d)pa
pa = &a;; 				 (e)*pa
*pa = 2 * a; 			 (f)&(*pa)
pb = &b; 				 (g)pb
c = 3 * (*pa + *pb); 	 (h)&(*pb)
						 (i)c

Respostas:
(a) 1000
(b) 1004
(c) 1008
(d) 1000
(e) 0.002
(f) 1000
(g) 1004
(h) 1004
(i) 0.015
*/
