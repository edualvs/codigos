#include <iostream>

int main (){
	int m;
	printf ("Digite um valor em metros: ");
	scanf ("%d", &m);
	printf ("\nEste valor em decimetros eh %d", m*10);
	printf ("\nEste valor em centimetros eh %d", m*100);
	printf ("\nEste valor em milimetros eh %d", m*1000);
	
	return 0;
}
