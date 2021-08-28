#include "Analiza.h"
#include <structs.h>

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <algorithm>

using namespace std;






Analiza::Analiza()
{
    string entrada;

    do{
        cout<< "            *****************************"<< endl;
        cout<< "            ***     Adriana Gomez     ***"<< endl;
        cout<< "            ***       201504236       ***"<< endl;
        cout<< "            ***      MIA 2S 2021      ***"<< endl;
        cout<< "            *****************************"<< endl;
        getline(cin,entrada);
        analiza(entrada);

    }while(entrada != "0");
}





void Analiza::analiza(string cadena)
{
    regex rule("[\\s+]|[\\=]");
    vector<string> datos;
    datos = { sregex_token_iterator(cadena.begin(), cadena.end(), rule, -1), {} };

    if(datos[0] == "mkdisk")
    {
        MKDISK(datos);
    }


}




void Analiza::MKDISK(vector<string> data)
{
        int size_mdisk = 0;
        string fit_mdisk = "bf";
        string unidad_mdisk = "m";
        string path_mdisk = "";


        for(int i = 0; i < data.capacity(); i++)
        {
            if(i != 0)
            {
                if(i % 2 != 0)
                {
                    if(data[i] == "-size")
                    {
                        size_mdisk = stoi(data[i + 1]);
                    }
                    else if(data[i] == "-f")
                    {
                        fit_mdisk = data[i +1 ];
                    }
                    else if(data[i] == "-u")
                    {
                        unidad_mdisk = data[i +1 ];
                    }
                    else if(data[i] == "-path")
                    {
                        path_mdisk = data[i + 1];
                    }
                }
            }
        }


        cout<<"\nvamos a crear el archivo c:"<<endl;


        structs::MBR disk;
        disk.fecha_mbr = time(nullptr);
        cout<< "fecha: "<<disk.fecha_mbr <<endl;

        disk.size_mbr = size_mdisk;
        cout<< "size: "<<disk.size_mbr<<endl;

        cout<< "unidad: "<<unidad_mdisk<<endl;
        cout<< "path: "<<path_mdisk<<endl;

        disk.fit_mbr = fit_mdisk[0];
        cout<< "fit: "<<disk.fit_mbr<<endl;



}








