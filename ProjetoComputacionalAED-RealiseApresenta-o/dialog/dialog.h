void message(int type){
    switch(type){
        case 1:
        	cout << endl << "-------------------------------------" << endl;
			cout << "   Digite o Ip da máquina desejada" << endl;
			cout << "-------------------------------------" << endl << endl;
			cout << " > 192.168.0.";
        break;
        case 2:
        	system("cls");
			cout << "-----------------------------------------------------" << endl;
			cout << "   Existe apenas uma máquina registrada no sistema" << endl;
			cout << "-----------------------------------------------------" << endl;
        break;
        case 3:
			system("cls");
			cout << "------------------------------------" << endl;
			cout << "   Digite uma frase a ser enviada" << endl;
			cout << "------------------------------------" << endl << endl;
			cout << " > ";
        break;
        case 4:
			cout << endl << "---------------------------------------" << endl;
			cout << "   Digite o Ip da máquina de destino" << endl;
			cout << "---------------------------------------" << endl << endl;
		    cout << " > 192.168.0.";
        break;
        case 5:
			system("cls");
			cout << "-------------------------------" << endl;
			cout << "   Você tem certeza que quer" << endl;
			cout << "   remover esta máquina? <S/N>" << endl;
			cout << "-------------------------------" << endl << endl;
			cout << " > ";
        break;
    }
}