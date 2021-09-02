#include <iostream>
#include <Analiza.h>
//#include "Analizador.h"


using namespace std;


/*
Adriana Gomez
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMM88OD8MMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMM88~===DNMMMMMMMMMMMMMMMMM
MMMMMMMMMMM888D===8D8D~N88NMMMMMMMMMMMMM
MMMMMMMMN8D===============I8DMMMMMMMMMMM
MMMMMMM8D===================D8MMMMMMMMMM
MMMMMM8I============8+=======~8MMMMMMMMM
MMMMM8I===========77IID===DD==D8MMMMMMMM
MMMMM8======N8~===+D8O====88~~=8D8DDMMMM
MMMM8D====~~D8~====ZI======~~~~DD==~88MM
MMMM8O===~~~~~=====NI7N=====~~~7D===O8MM
MMMM87===~~~~=======DD~=========D~==8MMM
MMMM8===========================~8D8MMMM
MMMM8============================88MMMMM
MMD8D~============================8MMMMM
MDDDD=============================N8MMMM
MN88======8?======================I8MMMM
MM88=====DN=======================O8MMMM
MMN8==~D8I========================8MMMMM
MMM8DNI==========================88MMMMM
MMMM88==========================8DMMMMMM
MMMMMD8I======================D8MMMMMMMM
MMMMMMM88O================~D88MMMMMMMMMM
MMMMMMMMMN888DI~~=~~+OD888DIDMMMMMMMMMMM
MMMMMMMMMMM8II8MNNNMMMMMM8DZ8MMMMMMMMMMM
MMMMMMMMMMMM88MMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
*/





int main()
{
    /*
    cout << "prueba \n";
    Analizador *analisis = new Analizador();

    //leeEntrada(entrada());

    do
    {

        cout<< "            *****************************"<< endl;
        cout<< "            ***     Adriana Gomez     ***"<< endl;
        cout<< "            ***       201504236       ***"<< endl;
        cout<< "            ***      MIA 2S 2021      ***"<< endl;
        cout<< "            *****************************"<< endl;

        //lee la entrada en el teclado
        fgets(analisis->entrada,100,stdin);
        analisis->entrada[strlen(analisis->entrada) - 1] = '\0';

        //pasa la cadena a minuscula
        for(int i = 0; analisis->entrada[i]; i++) analisis->entrada[i] = tolower(analisis->entrada[i]);

        analisis->tokens=strtok(analisis->entrada, " ");

        //revisa si es la palabra mkdisk
        if(strcmp(analisis->tokens,"mkdisk") == 0)
        {
            analisis->Mkdisk(false);
        }
        else if(strcmp(analisis->tokens,"0") == 0)
        {

            cout<< "            *****************************"<< endl;
            cout<< "            ***  Fin de la ejecucion  ***"<< endl;
            cout<< "            *****************************"<< endl;
            break;
        }
        else
        {
            printf("***** Comando incorrecto *****\n***** ERROR : %s\n",analisis->tokens);
        }

    }
    while(analisis->comando!=0);

    delete(analisis);*/

    Analiza inicio;

    return 0;
}


/*
string entrada(){
    cout<< "\n-> ";
    getline(cin, cadena);
    return cadena;
}



void leeEntrada(string Entrada){

    string delimitador = " ";
    size_t pos = 0;
    string token;

    cout<< "\n TODO CORRECTO!!! "<<cadena<<endl;

    while((pos = cadena.find(delimitador)) != std::string::npos)
    {
        token = cadena.substr(0,pos);
        cout<<token<<endl;
        cadena.erase(0,pos+delimitador.length());
    }
    cout<<cadena<<endl;
}
*/

