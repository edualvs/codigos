#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main (){
	vector<string> v;
	vector<string>::iterator p;
	string str;
	cout << "Digite qualquer palavra que quiser!";
	cout << "\nQuando quiser parar digite: fim\n";
	while (cin >> str){
		v.push_back(str);
		if (str=="fim"){
			system ("cls");
			cout << "Em ordem alfabetiva, as palavras que voce digitou foram :";
			sort(v.begin(),v.end());
			cout << "\n";
			for (p=v.begin();p!=v.end();++p)
				cout << *p << endl;
		}		
	}
	return 0;
}

