#include "Analiza.h"
#include <structs.h>

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

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
    else if(datos[0] == "rmdisk")
    {
        RMDISK(datos);
    }
    else
    {

    }


}




void Analiza::MKDISK(vector<string> data)
{
        int size_mkdisk = 0;         //obligatorio
        string fit_mkdisk = "ff";    //opcional (f por defecto)
        string unidad_mkdisk = "m";  //opcional (M por defecto)
        string path_mkdisk = "";     //obligatorio


        for(int i = 0; i < data.capacity(); i++)
        {
            if(i != 0)
            {
                if(i % 2 != 0)
                {
                    if(data[i] == "-size")
                    {
                        size_mkdisk = stoi(data[i + 1]);
                    }
                    else if(data[i] == "-f")
                    {
                        fit_mkdisk = data[i + 1];
                    }
                    else if(data[i] == "-u")
                    {
                        unidad_mkdisk = data[i + 1];
                    }
                    else if(data[i] == "-path")
                    {
                        path_mkdisk = data[i + 1];
                    }
                }
            }
        }


        //cantidad de unidad 1024 es k
        int cantidad_Unidad = 1024;
        if(unidad_mkdisk=="m")  //pero si detecta que por defecto es m, la cantidad cambia
        {
            cantidad_Unidad = 1024*1024;
        }





        cout<<"\n-> Valores del disco c:"<<endl;

        structs::MBR disk;
        disk.fecha_mbr = time(nullptr);
        disk.fit_mbr = fit_mkdisk[0];
        disk.size_mbr = size_mkdisk;

        cout<< "fecha: "<<disk.fecha_mbr <<endl;
        cout<< "size: "<<disk.size_mbr<<endl;
        cout<< "unidad: "<<unidad_mkdisk<<endl;
        cout<< "valor de unidad: "<<cantidad_Unidad<<endl;
        cout<< "path: "<<path_mkdisk<<endl;
        cout<< "fit: "<<disk.fit_mbr<<endl;

        RecorreRuta(path_mkdisk);

        /*
        char* r = "/home/adri/Escritorio/prueba";
        if(opendir(r)==NULL)
        {
            mkdir(r,0777);
        }
        */

}


void Analiza::RecorreRuta(string ruta)
{
    regex rule("[\\'\"']|[\\/]|[\\.]");
    vector<string> dat;
    dat = { sregex_token_iterator(ruta.begin(), ruta.end(), rule, -1), {} };
    string cadena;
    int posicion = 2;


    //*** crea carpetas
    if(dat[1] == "home" )
    {
        cadena = "/home";
        cout<<"\n\n entro al 1"<<endl;

        for(int i = 2; i < dat.capacity()-2; i++)
        {
            cout<<dat[i]<<endl;
            cadena = cadena + "/" + dat[i] ;
            cout<<"esto: "<<cadena<<endl;
            posicion++;

            if(opendir(cadena.c_str())==NULL)
            {
                cout<<"siuuuu  "<<cadena.c_str()<<endl;
                mkdir(cadena.c_str(),0777);
            }
        }
    }

    else if(dat[2] == "home")
    {
        cadena = "/home";
        cout<<"entro al 2"<<endl;

        for(int i = 3; i < dat.capacity()-1; i++)
        {
            cout<<dat[i]<<endl;
            cadena = cadena + "/" + dat[i] ;
            cout<<"esto: "<<cadena<<endl;

            if(opendir(cadena.c_str())==NULL)
            {
                cout<<"siuuuu  "<<cadena.c_str()<<endl;
                mkdir(cadena.c_str(),0777);
            }

        }
    }

    else
    {
        cout<<"*** INGRESE CORRECTAMENTE EL PATH ***"<<endl;
    }



        structs::MBR disk;


    //*** crea disco
    //cout<<"actual: "<<dat[posicion]<<endl;            imprime el nombre del archivo
    //cout<<"uno despues: "<<dat[posicion+1]<<endl;     imprime el dk
    if(dat[posicion + 1] == "dk")
    {
        cadena = cadena + "/" + dat[posicion] + ".dk";
        cout<<" completo: "<<cadena<<endl;

        FILE *DISCO = fopen(cadena.c_str(), "w+b");  //crea o sobreescribe el archivo
        char nulos = '\0';
        //llena el disco
        for(int l=0; l<disk.size_mbr;l++)
        {
            fwrite(&nulos,1,1,DISCO);
        }
        //escribiendo el mbr
        fseek(DISCO,0,SEEK_SET);
        fwrite(&disk,sizeof(disk),1,DISCO);
        fclose(DISCO);


    }
    else
    {
        cout<<"*** EL ARCHIVO NO ES EXTENSION .DK VERIFIQUE DE NUEVO***"<<endl;
    }







}




void Analiza::RMDISK(vector<string> data)
{
        string path_rmdisk = "";     //obligatorio


        for(int i = 0; i < data.capacity(); i++)
        {
            if(i != 0)
            {
                if(i % 2 != 0)
                {
                    if(data[i] == "-path")
                    {
                        path_rmdisk = data[i + 1];
                    }
                }
            }
        }
        EliminaRutaArchivo(path_rmdisk);
}




void Analiza::EliminaRutaArchivo(string ruta)
{
    regex rule("[\\'\"']|[\\/]|[\\.]");
    vector<string> dat;
    dat = { sregex_token_iterator(ruta.begin(), ruta.end(), rule, -1), {} };
    string cadena;
    int posicion = 2;

    //*** recorre las carpetas
    if(dat[1] == "home" )
    {
        cadena = "/home";

        for(int i = 2; i < dat.capacity()-2; i++)
        {
            cadena = cadena + "/" + dat[i] ;
            posicion++;
        }
    }

    else if(dat[2] == "home")
    {
        cadena = "/home";

        for(int i = 3; i < dat.capacity()-1; i++)
        {
            cadena = cadena + "/" + dat[i] ;
        }
    }

    else
    {
        cout<<"*** INGRESE CORRECTAMENTE EL PATH ***"<<endl;
    }



    //*** elimina disco
    if(dat[posicion + 1] == "dk")
    {
        cadena = cadena + "/" + dat[posicion] + ".dk";
        remove(cadena.c_str());

    }
    else
    {
        cout<<"*** EL ARCHIVO NO ES EXTENSION .DK VERIFIQUE DE NUEVO***"<<endl;
    }



}









