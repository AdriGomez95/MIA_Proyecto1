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
#include <fstream>


using namespace std;






Analiza::Analiza()
{
    string entrada;

    do{
        cout<<"\n\n"<<endl;
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
    else if(datos[0] == "fdisk")
    {
        FDISK(datos);
    }
    else if(datos[0] == "exec")
    {
        EXEC(datos);
    }
    else if(datos[0] == "rep")
    {
        REP(datos);
    }
    else
    {

    }


}


//****************************************************** EXEC ******************************************************
void Analiza::EXEC(vector<string> data)
{
    string pat_extra = "/home";
    string path_1 = "";

    if(data[1] == "-path")
    {
        //path_1 += pat_extra;
        if(data[2][0] == '\"')
        {
            path_1 += data[2].substr(1,data[2].capacity()-2);
        }
        else
        {
            path_1 += data[2];
            cout<<"aqui :)"<<endl;
        }

        ifstream ReadF;
        ReadF.open(path_1.c_str());
        char output[100];
        if(ReadF.is_open())
        {
            cout<<"en el if :)"<<endl;
            while(!ReadF.eof())
            {
            cout<<"en el while :o"<<endl;
                string salida;
                getline(ReadF, salida);
                analiza(salida);
            }
        }
        ReadF.close();
    }



}





//****************************************************** MKDISK ******************************************************

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

/*
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
*/
        RecorreRuta(path_mkdisk, size_mkdisk, fit_mkdisk, unidad_mkdisk, cantidad_Unidad);

        /*
        char* r = "/home/adri/Escritorio/prueba";
        if(opendir(r)==NULL)
        {
            mkdir(r,0777);
        }
        */

}


void Analiza::RecorreRuta(string ruta, int s, string f, string u, int uv)
{
    regex rule("[\\'\"']|[\\/]|[\\.]");
    vector<string> dat;
    dat = { sregex_token_iterator(ruta.begin(), ruta.end(), rule, -1), {} };
    string cadena;
    int posicion = 2;
    bool EsComilla = false;


    //*** crea carpetas
    if(dat[1] == "home" ) //sin comilla
    {
        cadena = "/home";

        for(int i = 2; i < dat.capacity()-2; i++)
        {
            //cout<<dat[i]<<endl;
            cadena = cadena + "/" + dat[i] ;
            //cout<<"esto: "<<cadena<<endl;
            posicion++;

            if(opendir(cadena.c_str())==NULL)
            {
                //cout<<"siuuuu  "<<cadena.c_str()<<endl;
                mkdir(cadena.c_str(),0777);
            }
        }
    }

    else if(dat[2] == "home") //con comilla
    {
        EsComilla = true;
        cadena = "/home";
        //cout<<"entro al 2"<<endl;

        for(int i = 3; i < dat.capacity()-2; i++)
        {
            //cout<<dat[i]<<endl;
            cadena = cadena + "/" + dat[i] ;
            //cout<<"esto: "<<cadena<<endl;
            posicion++;

            if(opendir(cadena.c_str())==NULL)
            {
                //cout<<"siuuuu  "<<cadena.c_str()<<endl;
                mkdir(cadena.c_str(),0777);
            }

        }
    }

    else
    {
        cout<<"\n\n*** INGRESE CORRECTAMENTE EL PATH ***"<<endl;
    }







    //*** crea disco
    //cout<<"actual: "<<dat[posicion]<<endl;            //imprime el nombre del archivo
    //cout<<"uno despues: "<<dat[posicion+1]<<endl;     //imprime el dk
    //cout<<"dos despues: "<<dat[posicion+2]<<endl;     //imprime el dk

    if(EsComilla == false)
    {
        if(dat[posicion + 1] == "dk" | dat[posicion + 1] == "disk")
        {
            cadena = cadena + "/" + dat[posicion] +"."+ dat[posicion + 1];
            //cout<<" completo: "<<cadena<<endl;

            cout<<"\n--> Valores del disco c:"<<endl;

            structs::MBR disk;

            disk.fecha_mbr = time(NULL);
            disk.fit_mbr = f[0];
            disk.size_mbr = s*uv;
            disk.signature_mbr = rand();

            cout<< "fecha: "<<disk.fecha_mbr <<endl;
            cout<< "tamanio: "<<disk.size_mbr<<endl;
            cout<< "unidad: "<<u<<endl;
            cout<< "fit: "<<disk.fit_mbr<<endl;

            structs::Particion P1;
            structs::Particion P2;
            structs::Particion P3;
            structs::Particion P4;

            P1 = disk.particion1_mbr;
            P2 = disk.particion2_mbr;
            P3 = disk.particion3_mbr;
            P4 = disk.particion4_mbr;

            P1.part_status = '.';  //de inactiva I
            P2.part_status = '.';	//*
            P3.part_status = '.';
            P4.part_status = '.';

            P1.part_type = '.';
            P2.part_type = '.';
            P3.part_type = '.';
            P4.part_type = '.';

            P1.part_fit = '.';
            P2.part_fit = '.';
            P3.part_fit = '.';
            P4.part_fit = '.';

            P1.part_size = 0;	//*
            P2.part_size = 0;
            P3.part_size = 0;
            P4.part_size = 0;

            P1.part_start = 0;	//*
            P2.part_start = 0;
            P3.part_start = 0;
            P4.part_start = 0;


            disk.particion1_mbr = P1;
            disk.particion2_mbr = P2;
            disk.particion3_mbr = P3;
            disk.particion4_mbr = P4;




            FILE *DISCO = fopen(cadena.c_str(), "w+b");  //crea o sobreescribe el archivo
            char nulos = '\0';

            //llena el disco
            for(int l=0; l<disk.size_mbr;l++)
            {
                //puntero a la zona de memoria donde se obtienenlos datos a escribir
                fwrite(&nulos,1,1,DISCO); //tamaño, cantidad, puntero a la estructura del archivo
            }

            //escribiendo el mbr
            fseek(DISCO,0,SEEK_SET); //puntero al fichero, desplazamiento, origen
            fwrite(&disk,sizeof(disk),1,DISCO);
            fclose(DISCO);

            cout<<"\n\n*** SE HA CREADO EL ARCHIVO CORRECTAMENTE ***"<<endl;

        }
        else
        {
            cout<<"\n\n*** EL ARCHIVO NO ES EXTENSION .DK o .DISK VERIFIQUE DE NUEVO ***"<<endl;
        }



    }
    else if(EsComilla == true)
    {
        if(dat[posicion + 2] == "dk" | dat[posicion + 2] == "disk")
        {
            cadena = cadena + "/" + dat[posicion + 1] +"."+ dat[posicion + 2];
            //cout<<" completo: "<<cadena<<endl;

            cout<<"\n--> Valores del disco c:"<<endl;

            structs::MBR disk;

            disk.fecha_mbr = time(NULL);
            disk.fit_mbr = f[0];
            disk.size_mbr = s*uv;
            disk.signature_mbr = rand();

            cout<< "fecha: "<<disk.fecha_mbr <<endl;
            cout<< "tamanio: "<<disk.size_mbr<<endl;
            cout<< "unidad: "<<u<<endl;
            cout<< "fit: "<<disk.fit_mbr<<endl;

            structs::Particion P1;
            structs::Particion P2;
            structs::Particion P3;
            structs::Particion P4;

            P1 = disk.particion1_mbr;
            P2 = disk.particion2_mbr;
            P3 = disk.particion3_mbr;
            P4 = disk.particion4_mbr;

            P1.part_status = '.';  //de inactiva I
            P2.part_status = '.';	//*
            P3.part_status = '.';
            P4.part_status = '.';

            P1.part_type = '.';
            P2.part_type = '.';
            P3.part_type = '.';
            P4.part_type = '.';

            P1.part_fit = '.';
            P2.part_fit = '.';
            P3.part_fit = '.';
            P4.part_fit = '.';

            P1.part_size = 0;	//*
            P2.part_size = 0;
            P3.part_size = 0;
            P4.part_size = 0;

            P1.part_start = 0;	//*
            P2.part_start = 0;
            P3.part_start = 0;
            P4.part_start = 0;


            disk.particion1_mbr = P1;
            disk.particion2_mbr = P2;
            disk.particion3_mbr = P3;
            disk.particion4_mbr = P4;




            FILE *DISCO = fopen(cadena.c_str(), "w+b");  //crea o sobreescribe el archivo
            char nulos = '\0';

            //llena el disco
            for(int l=0; l<disk.size_mbr;l++)
            {
                //puntero a la zona de memoria donde se obtienenlos datos a escribir
                fwrite(&nulos,1,1,DISCO); //tamaño, cantidad, puntero a la estructura del archivo
                //fwrite(&disk,sizeof(disk),1,DISCO);
            }

            //escribiendo el mbr
            fseek(DISCO,0,SEEK_SET); //puntero al fichero, desplazamiento, origen
            fwrite(&disk,sizeof(disk),1,DISCO);
            fclose(DISCO);

            cout<<"\n\n*** SE HA CREADO EL ARCHIVO CORRECTAMENTE ***"<<endl;

        }
        else
        {
            cout<<"\n\n*** EL ARCHIVO NO ES EXTENSION .DK o .DISK VERIFIQUE DE NUEVO ***"<<endl;
        }


    }




}






//****************************************************** RMDISK ******************************************************

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
    bool EsComilla = false;


    //*** recorre las carpetas
    if(dat[1] == "home" ) //sin comilla
    {
        cadena = "/home";

        for(int i = 2; i < dat.capacity()-2; i++)
        {
            cadena = cadena + "/" + dat[i] ;
            posicion++;
        }
    }

    else if(dat[2] == "home") //con comilla
    {
        EsComilla = true;
        cadena = "/home";

        for(int i = 3; i < dat.capacity()-2; i++)
        {
            cadena = cadena + "/" + dat[i] ;
            posicion++;
        }
    }

    else
    {
        cout<<"\n\n*** INGRESE CORRECTAMENTE EL PATH ***"<<endl;
    }

    int aceptar = 0;
    cout<<"\n\n --> Desea eliminar? SI[1]/NO[0]"<<endl;
    cin>>aceptar;


    //*** elimina disco
    //cout<<"actual: "<<dat[posicion]<<endl;            //imprime el nombre del archivo
    //cout<<"uno despues: "<<dat[posicion+1]<<endl;     //imprime el dk
    //cout<<"dos despues: "<<dat[posicion+2]<<endl;     //imprime el dk
    if(aceptar == 1){
        if(EsComilla == false)
        {
            if(dat[posicion + 1] == "dk" | dat[posicion + 1] == "disk")
            {
                cadena = cadena + "/" + dat[posicion] + "." + dat[posicion + 1] ;
                remove(cadena.c_str());
                cout<<"\n\n*** SE HA ELIMINADO EL ARCHIVO CORRECTAMENTE ***"<<endl;

            }
            else
            {
                cout<<"\n\n*** EL ARCHIVO NO ES EXTENSION .DK VERIFIQUE DE NUEVO ***"<<endl;
            }

        }
        else if(EsComilla == true)
        {
            if(dat[posicion + 2] == "dk" | dat[posicion + 2] == "disk")
            {
                cadena = cadena + "/" + dat[posicion + 1] + "." + dat[posicion + 2] ;
                remove(cadena.c_str());
                cout<<"\n\n*** SE HA ELIMINADO EL ARCHIVO CORRECTAMENTE ***"<<endl;

            }
            else
            {
                cout<<"\n\n*** EL ARCHIVO NO ES EXTENSION .DK VERIFIQUE DE NUEVO***"<<endl;
            }

        }

    }
    else
    {
        cout<<"\n\n*** NO SE ELIMINO EL ARCHIVO ***"<<endl;
    }

}





//****************************************************** FDISK ******************************************************

void Analiza::FDISK(vector<string> data)
{
    int size_fdisk;
    string u_fdisk = "k";           //opcional (k por defecto)
    string path_fdisk;
    string type_fdisk = "p";        //opcional (p por defecto)
    string f_fdisk = "wf";          //opcional (wf por defecto)
    string delete_fdisk;            //opcional
    string name_fdisk;
    int add_fdisk;                  //opcional
    int cantidad_Unidad = 1024;     //cantidad de unidad 1024 es k por defecto

    bool size_ingresado = false;    //* obligatorio
    bool u_diferente = false;
    bool path_ingresado = false;    //*
    bool type_diferente = false;
    bool f_diferente = false;
    bool delete_inexistente = false;
    bool name_ingresado = false;    //*


    for(int i = 0; i < data.capacity(); i++)
    {
        if(i != 0)
        {
            if(i % 2 != 0)
            {
                if(data[i] == "-size")
                {
                    size_fdisk = stoi(data[i + 1]);
                    size_ingresado = true;
                }
                else if(data[i] == "-u")
                {
                    u_fdisk = data[i + 1];
                }
                else if(data[i] == "-path")
                {
                    path_fdisk = data[i + 1];
                    path_ingresado = true;
                }
                else if(data[i] == "-type")
                {
                    type_fdisk = data[i + 1];
                }
                else if(data[i] == "-f")
                {
                    f_fdisk = data[i + 1];
                }
                else if(data[i] == "-delete")
                {
                    delete_fdisk = data[i + 1];
                }
                else if(data[i] == "-name")
                {
                    name_fdisk = data[i + 1];
                    name_ingresado = true;
                }
                else if(data[i] == "-add")
                {
                    add_fdisk = stoi(data[i + 1]);
                }
            }
        }
    }



    //verifica si alguno de los campos obligatorios no existe
    if((size_ingresado == false) | (path_ingresado == false) | (name_ingresado == false))
    {
        cout<<"\n\n*** ALGUNO DE LOS CAMPOS OBLIGATORIOS NO FUE INGRESADO, VERIFIQUE DE NUEVO ***"<<endl;
    }
    else
    {
        //verifica si el size es positivo y mayor a cero para proceder
        if(size_fdisk > 0)
        {


            //verifica si el path existe
            if(path_ingresado == true)
            {

                regex rule("[\\'\"']|[\\/]|[\\.]");
                vector<string> dat;
                dat = { sregex_token_iterator(path_fdisk.begin(), path_fdisk.end(), rule, -1), {} };
                string cadena;
                string nombreArchivo;
                int posicion = 2;
                bool EsComilla = false;
                bool ExisteCarpeta = true; //para ver si las carpetas del path son correctas
                bool PathCorrecto = false; //cuando abre todas las carpetas y archivo .disk del path sin error


                //*** recorre las carpetas
                if(dat[1] == "home" ) //sin comilla
                {
                    cadena = "/home";
                    for(int i = 2; i < dat.capacity()-2; i++)
                    {
                        cadena = cadena + "/" + dat[i] ;
                        posicion++;
                        if(opendir(cadena.c_str())==NULL)
                        {
                            cout<<"\n\n*** LA CARPETA DEL PATH NO EXISTE: "<<cadena<<" ***"<<endl;
                            ExisteCarpeta = false;
                            break;
                        }
                    }
                }

                else if(dat[2] == "home") //con comilla
                {
                    EsComilla = true;
                    cadena = "/home";
                    for(int i = 3; i < dat.capacity()-2; i++)
                    {
                        cadena = cadena + "/" + dat[i] ;
                        posicion++;
                        if(opendir(cadena.c_str())==NULL)
                        {
                            cout<<"\n\n*** LA CARPETA DEL PATH NO EXISTE: "<<cadena<<" ***"<<endl;
                            ExisteCarpeta = false;
                            break;
                        }
                    }
                }

                else
                {
                    cout<<"\n\n*** INGRESE CORRECTAMENTE EL PATH ***"<<endl;
                }


                //*** abre el archivo
                if(ExisteCarpeta)
                {
                    if(EsComilla == false)
                    {
                        if(dat[posicion + 1] == "dk" | dat[posicion + 1] == "disk")
                        {
                            cadena = cadena + "/" + dat[posicion] +"."+ dat[posicion + 1];
                            nombreArchivo = dat[posicion];

                            FILE *archivito = NULL;
                            archivito = fopen(cadena.c_str(),"r+b");

                            if(archivito != NULL)
                            {
                                PathCorrecto = true;
                                //cout<<"\n\n*** EL ARCHIVO "<<dat[posicion] <<"."<< dat[posicion + 1]<<" SI EXISTE ***"<<endl;
                            }
                            else
                            {
                                cout<<"\n\n*** EL ARCHIVO "<<dat[posicion] <<"."<< dat[posicion + 1]<<" NO EXISTE ***"<<endl;
                            }

                        }
                    }
                    else if(EsComilla == true)
                    {
                        if(dat[posicion + 2] == "dk" | dat[posicion + 2] == "disk")
                        {
                            cadena = cadena + "/" + dat[posicion + 1] +"."+ dat[posicion + 2];
                            nombreArchivo = dat[posicion + 1];

                            FILE *archivito = NULL;
                            archivito = fopen(cadena.c_str(),"r+b");

                            if(archivito != NULL)
                            {
                                PathCorrecto = true;
                                //cout<<"\n\n*** EL ARCHIVO "<<dat[posicion + 1] <<"."<< dat[posicion + 2]<<" SI EXISTE ***"<<endl;
                            }
                            else
                            {
                                cout<<"\n\n*** EL ARCHIVO "<<dat[posicion + 1] <<"."<< dat[posicion + 2]<<" NO EXISTE ***"<<endl;
                            }

                        }
                    }

                }
                else
                {
                    cout<<"\n\n*** NO SE PUDO LEER EL ARCHIVO, YA QUE EL PATH NO EXISTE ***"<<endl;

                }





                //si encontro todo bien en el path, aqui sigue su flujo
                if(PathCorrecto == true)
                {
                    //obtiene el mbr del disco
                    FILE *Disco = fopen(cadena.c_str(), "rb+");
                    fseek(Disco,0,SEEK_SET);
                    structs::MBR mbr;
                    fread(&mbr,sizeof(mbr),1,Disco);
                    fseek(Disco,0,SEEK_SET);
                    fclose(Disco);

                    structs::Particion particion1;
                    structs::Particion particion2;
                    structs::Particion particion3;
                    structs::Particion particion4;
                    particion1 = mbr.particion1_mbr;
                    particion2 = mbr.particion2_mbr;
                    particion3 = mbr.particion3_mbr;
                    particion4 = mbr.particion4_mbr;
                    char EsExtendida[] = {'.','.','.','.'};


                    if((type_fdisk == "e") | (type_fdisk == "p") | (type_fdisk == "E") | (type_fdisk == "P"))
                    {
                        //hace conteo de cuantas extendidas hay para usar mas adelante
                        if(particion1.part_type != '.')
                        {
                            if((type_fdisk != "p") | (type_fdisk != "P"))
                            {
                                EsExtendida[0] = 'e';
                            }
                            else
                            {
                                EsExtendida[0] = 'p';
                            }

                        }
                        else if(particion2.part_type != '.')
                        {
                            if((type_fdisk != "p") | (type_fdisk != "P"))
                            {
                                EsExtendida[1] = 'e';
                            }
                            else
                            {
                                EsExtendida[1] = 'p';
                            }

                        }
                        else if(particion3.part_type != '.')
                        {
                            if((type_fdisk != "p") | (type_fdisk != "P"))
                            {
                                EsExtendida[2] = 'e';
                            }
                            else
                            {
                                EsExtendida[2] = 'p';
                            }

                        }
                        else if(particion4.part_type != '.')
                        {
                            if((type_fdisk != "p") | (type_fdisk != "P"))
                            {
                                EsExtendida[3] = 'e';
                            }
                            else
                            {
                                EsExtendida[3] = 'p';
                            }

                        }


                        int NumeroDeExtendidas = 0;
                        if((type_fdisk == "e") | (type_fdisk == "E"))
                        {
                            NumeroDeExtendidas++;
                        }
                        for(int s=0; s<4; s++)
                        {
                            if(EsExtendida[s] == 'e')
                            {
                                NumeroDeExtendidas++;
                            }
                        }


                        //verifica si el name no existe en alguna de las particiones
                        if((name_fdisk != particion1.part_name) && (name_fdisk != particion2.part_name) && (name_fdisk != particion3.part_name) && (name_fdisk != particion4.part_name))
                        {

                            //verifica si hay particiones libres con el array de chars de arriba
                            if((EsExtendida[0] == '.') | (EsExtendida[1] == '.') | (EsExtendida[2] == '.') | (EsExtendida[3] == '.'))
                            {
                                //verifica que solo haya 1 particion extendida
                                if(NumeroDeExtendidas<=1)
                                {

                                    //variables para verificar el espacio libre de la particion a crear
                                    int tamMBR = sizeof(mbr);
                                    int tamDisco = mbr.size_mbr;
                                    int espacio = 0;
                                    int p1 = particion1.part_size;
                                    int p2 = particion2.part_size;
                                    int p3 = particion3.part_size;
                                    int p4 = particion4.part_size;


                                    if((u_fdisk != "k") | (u_fdisk != "K"))
                                    {
                                        if((u_fdisk == "m") | (u_fdisk != "M"))
                                        {
                                            espacio = size_fdisk * 1024 *1024;
                                        }
                                        else if((u_fdisk == "b") | (u_fdisk != "B"))
                                        {
                                            espacio = size_fdisk;
                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL COMANDO DE U EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                            cout<<"*** PERO SE CREO CON KILOBYTES PARA NO AFECTAR EL PROCESO ***"<<endl;
                                            espacio = size_fdisk * 1024;

                                        }
                                    }
                                    else
                                    {
                                        espacio = size_fdisk * 1024;
                                    }


                                    //verifica que en el array esten inactivas las particiones
                                    if((EsExtendida[0] == '.') && (EsExtendida[1] == '.') && (EsExtendida[2] == '.') && (EsExtendida[3] == '.'))
                                    {
                                        //verifica que el tamaño sea correcto para ingresar la particion
                                        if((tamMBR - tamDisco - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);

                                            /* DISCO : es el apuntador file
                                               disk : es el MBR struct
                                            //escribiendo el mbr
                                            fseek(DISCO,0,SEEK_SET); //puntero al fichero, desplazamiento, origen
                                            fwrite(&disk,sizeof(disk),1,DISCO);
                                            fclose(DISCO);
                                            */

                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 1
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] == '.') && (EsExtendida[2] == '.') && (EsExtendida[3] == '.'))
                                    {
                                        if((tamDisco - tamMBR - p1 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion2.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion2.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion2.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion2.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion2.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion2.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion2.part_status = 'N';
                                            particion2.part_start = tamMBR + p1;
                                            particion2.part_size = espacio;
                                            memset(particion2.part_name,0,16);
                                            strcpy(particion2.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion2.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion2.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 2
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] != '.') && (EsExtendida[2] == '.') && (EsExtendida[3] == '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion2.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        //ingresa particion al archivo fisico
                                        else if((tamDisco - tamMBR - p1 - p2 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion3.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion3.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion3.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion3.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion3.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion3.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion3.part_status = 'N';
                                            particion3.part_start = tamMBR;
                                            particion3.part_size = espacio;
                                            memset(particion3.part_name,0,16);
                                            strcpy(particion3.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion3.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 3
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] == '.') && (EsExtendida[2] != '.') && (EsExtendida[3] == '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion3.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        //ingresa particion al archivo fisico
                                        else if((tamDisco - tamMBR - p1 - p2 - p3 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion4.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion4.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion4.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion4.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion4.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion4.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion4.part_status = 'N';
                                            particion4.part_start = tamMBR + p1 + p2 + p3;
                                            particion4.part_size = espacio;
                                            memset(particion4.part_name,0,16);
                                            strcpy(particion4.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion4.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion4.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }

                                    }

                                    //verifica que este ocupada la particion 4
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] == '.') && (EsExtendida[2] == '.') && (EsExtendida[3] != '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion4.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 1 y 2
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] != '.') && (EsExtendida[2] == '.') && (EsExtendida[3] == '.'))
                                    {
                                        if((tamDisco - tamMBR - p1 - p2 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion3.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion3.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion3.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion3.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion3.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion3.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion3.part_status = 'N';
                                            particion3.part_start = tamMBR + p1 + p2;
                                            particion3.part_size = espacio;
                                            memset(particion3.part_name,0,16);
                                            strcpy(particion3.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion3.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion3.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }

                                    }

                                    //verifica que este ocupada la particion 1 y 3
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] == '.') && (EsExtendida[2] != '.') && (EsExtendida[3] == '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion3.part_start - tamMBR - p1) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion2.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion2.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion2.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion2.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion2.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion2.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion2.part_status = 'N';
                                            particion2.part_start = tamMBR + p1;
                                            particion2.part_size = espacio;
                                            memset(particion2.part_name,0,16);
                                            strcpy(particion2.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion2.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion2.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        //ingresa particion al archivo fisico
                                        else if((tamDisco - tamMBR - p1 - p2 - p3 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion4.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion4.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion4.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion4.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion4.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion4.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion4.part_status = 'N';
                                            particion4.part_start = tamMBR + p1 + p2 + p3;
                                            particion4.part_size = espacio;
                                            memset(particion4.part_name,0,16);
                                            strcpy(particion4.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion4.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion4.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 1 y 4
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] == '.') && (EsExtendida[2] == '.') && (EsExtendida[3] != '.'))
                                    {
                                        if((particion4.part_start - tamMBR - p1) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion2.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion2.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion2.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion2.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion2.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion2.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion2.part_status = 'N';
                                            particion2.part_start = tamMBR + p1;
                                            particion2.part_size = espacio;
                                            memset(particion2.part_name,0,16);
                                            strcpy(particion2.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion2.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion2.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 2 y 3
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] != '.') && (EsExtendida[2] != '.') && (EsExtendida[3] == '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion2.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        //ingresa particion al archivo fisico
                                        else if((tamDisco - tamMBR - p1 - p2 - p3 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion4.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion4.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion4.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion4.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion4.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion4.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion4.part_status = 'N';
                                            particion4.part_start = tamMBR + p1 + p2 + p3;
                                            particion4.part_size = espacio;
                                            memset(particion4.part_name,0,16);
                                            strcpy(particion4.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion4.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion4.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }

                                    }

                                    //verifica que este ocupada la particion 2 y 4
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] != '.') && (EsExtendida[2] == '.') && (EsExtendida[3] != '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion2.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        //ingresa particion al archivo fisico
                                        else if((particion4.part_start - tamMBR - p1 - p2 ) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion3.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion3.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion3.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion3.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion3.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion3.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion3.part_status = 'N';
                                            particion3.part_start = tamMBR + p1 + p2;
                                            particion3.part_size = espacio;
                                            memset(particion3.part_name,0,16);
                                            strcpy(particion3.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion3.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion3.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 3 y 4
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] == '.') && (EsExtendida[2] != '.') && (EsExtendida[3] != '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion3.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 1, 2 y 3
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] != '.') && (EsExtendida[2] != '.') && (EsExtendida[3] == '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((tamDisco - tamMBR - p1 - p2 - p3 - espacio) > 0)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion4.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion4.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion4.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion4.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion4.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion4.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion4.part_status = 'N';
                                            particion4.part_start = tamMBR + p1 + p2 + p3;
                                            particion4.part_size = espacio;
                                            memset(particion4.part_name,0,16);
                                            strcpy(particion4.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion4.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion4.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 1, 2 y 4
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] != '.') && (EsExtendida[2] == '.') && (EsExtendida[3] != '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion4.part_start - tamMBR - p1 - p2) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion3.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion3.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion3.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion3.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion3.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion3.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion3.part_status = 'N';
                                            particion3.part_start = tamMBR + p1 + p2;
                                            particion3.part_size = espacio;
                                            memset(particion3.part_name,0,16);
                                            strcpy(particion3.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion3.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion3.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 1, 3 y 4
                                    else if((EsExtendida[0] != '.') && (EsExtendida[1] == '.') && (EsExtendida[2] != '.') && (EsExtendida[3] != '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion3.part_start - tamMBR - p1) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion2.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion2.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion2.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion2.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion2.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion2.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion2.part_status = 'N';
                                            particion2.part_start = tamMBR + p1;
                                            particion2.part_size = espacio;
                                            memset(particion2.part_name,0,16);
                                            strcpy(particion2.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion2.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion2.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                    //verifica que este ocupada la particion 2, 3 y 4
                                    else if((EsExtendida[0] == '.') && (EsExtendida[1] != '.') && (EsExtendida[2] != '.') && (EsExtendida[3] != '.'))
                                    {
                                        //ingresa particion al archivo fisico
                                        if((particion2.part_start - tamMBR) > espacio)
                                        {
                                            bool EsPrimaria = true;

                                            if((type_fdisk != "p") | (type_fdisk != "P"))
                                            {
                                                particion1.part_type = 'E';
                                                EsPrimaria = false;
                                            }
                                            else
                                            {
                                                particion1.part_type = 'P';
                                            }




                                            if((f_fdisk != "wf") | (f_fdisk != "WF"))
                                            {
                                                if((f_fdisk == "bf") | (f_fdisk != "BF"))
                                                {
                                                    particion1.part_fit = 'B';
                                                }
                                                else if((f_fdisk == "ff") | (f_fdisk != "FF"))
                                                {
                                                    particion1.part_fit = 'F';
                                                }
                                                else
                                                {
                                                    cout<<"\n\n*** EL COMANDO DE F EN FDISK NO COINCIDE CON NINGUNO DE LOS REGISTRADOS ***"<<endl;
                                                    cout<<"*** PERO SE CREO CON EL PEOR AJUSTE 'W' PARA NO AFECTAR EL PROCESO ***"<<endl;
                                                    particion1.part_fit = 'W';
                                                }
                                            }
                                            else
                                            {
                                                particion1.part_fit = 'W';
                                            }



                                            //aqui van los cambios nuevos para el disco
                                            particion1.part_status = 'N';
                                            particion1.part_start = tamMBR;
                                            particion1.part_size = espacio;
                                            memset(particion1.part_name,0,16);
                                            strcpy(particion1.part_name,name_fdisk.c_str());
                                            //strcpy(particion1.part_name,name_fdisk.toStdString().c_str());

                                            mbr.particion1_mbr = particion1;
                                            mbr.particion2_mbr = particion2;
                                            mbr.particion3_mbr = particion3;
                                            mbr.particion4_mbr = particion4;

                                            Disco = fopen(cadena.c_str(), "rb+");
                                            fseek(Disco,0,SEEK_SET);
                                            fwrite(&mbr,sizeof(mbr),1,Disco);
                                            fseek(Disco,0,SEEK_SET);
                                            fclose(Disco);


                                            //ebr inicial de extendida
                                            if((type_fdisk == "e") | (type_fdisk == "E"))
                                            {
                                                structs::EBR ebr;
                                                ebr.fit_ebr = '.';
                                                ebr.next_ebr = -1;
                                                ebr.size_ebr = 0;
                                                ebr.start_ebr = particion1.part_start;
                                                ebr.status_ebr = '.';

                                                Disco = fopen(cadena.c_str(), "rb+");
                                                fseek(Disco,particion1.part_start,SEEK_SET);
                                                fwrite(&ebr,sizeof(ebr),1,Disco);
                                                fseek(Disco,0,SEEK_SET);
                                                fclose(Disco);
                                            }



                                            if(EsPrimaria)
                                            {
                                                cout<<"\n\n*** PARTICION PRIMARIA CREADA CON EXITO ***"<<endl;

                                            }
                                            else
                                            {
                                                cout<<"\n\n*** PARTICION EXTENDIDA CREADA CON EXITO ***"<<endl;
                                            }

                                        }
                                        else
                                        {
                                            cout<<"\n\n*** EL ESPACIO SOLICITADO PARA LA PARTICION SUPERA EL TAMANIO DEL DISCO ***"<<endl;
                                        }
                                    }

                                }
                                //************************ SALIO DE LA VERIFICACION DE PARTICIONES EXTENDIDAS
                                else
                                {
                                    cout<<"\n\n*** YA EXISTE UNA PARTICION EXTENDIDA, NO SE PUDO PROCEDER ***"<<endl;

                                }

                            }
                            //************************ SALIO DE LA VERIFICACION DE PARTICIONES LIBRES
                            else
                            {
                                cout<<"\n\n*** NO SE PUEDEN CREAR 2 PARTICIONES EXTENDIDAS EN EL DISCO ***"<<endl;
                            }

                        }
                        //************************ SALIO DE LA VERIFICACION DE NAME EN LAS PARTICIONES
                        else
                        {
                            cout<<"\n\n*** EL NAME YA EXISTE, NO SE PUDO PROCEDER ***"<<endl;

                        }

                    }

                    //************************ CUANDO YA EXISTE UNA EXTENDIDA, ENTRA AQUI 1351
                    //else
                    //{
                    //}

                }
                //************************ SALIO DEL FLUJO CORRECTO DEL PATH

            }
            //************************ SALIO DE LA VERIFICACION DE PATH

        }
        //************************ SALIO DE LA VERIFICACION DE SIZE
        else
        {
            cout<<"\n\n*** NO SE PUDIERON ADMINISTRAR LAS PARTICIONES PORQUE EL SIZE ES NEGATIVO, INGRESE DE NUEVO ***"<<endl;
        }

    }






}





//****************************************************** REP ******************************************************
void Analiza::REP(vector<string> data)
{
    string path_rep = "";   //ruta donde se creara el reporte
    string name_rep = "";   //nombre del reporte a generar
    string id_rep = "";
    string cadena_de_carpetas;
    string nombre_del_dot = "";

    for(int i = 0; i < data.capacity(); i++)
    {
        if(i != 0)
        {
            if(i % 2 != 0)
            {
                if(data[i] == "-name")
                {
                    name_rep = data[i + 1];
                }
                else if(data[i] == "-path")
                {
                    path_rep = data[i + 1];
                }
                else if(data[i] == "-id")
                {
                    id_rep = data[i + 1];
                }
            }
        }
    }


    if(name_rep != "")
    {
        if(path_rep != "")
        {
            regex rule("[\\'\"']|[\\/]|[\\.]");
            vector<string> dat;
            dat = { sregex_token_iterator(path_rep.begin(), path_rep.end(), rule, -1), {} };

            int posicion = 2;
            bool EsComilla = false;


            //*** crea carpetas
            if(dat[1] == "home" ) //sin comilla
            {
                cadena_de_carpetas = "/home";

                for(int i = 2; i < dat.capacity()-2; i++)
                {
                    cadena_de_carpetas = cadena_de_carpetas + "/" + dat[i] ;
                    nombre_del_dot = cadena_de_carpetas + "/" + dat[i] ;
                    posicion++;

                    if(opendir(cadena_de_carpetas.c_str())==NULL)
                    {
                        mkdir(cadena_de_carpetas.c_str(),0777);
                    }
                }
            }

            else if(dat[2] == "home") //con comilla
            {
                EsComilla = true;
                cadena_de_carpetas = "/home";

                for(int i = 3; i < dat.capacity()-2; i++)
                {
                    cadena_de_carpetas = cadena_de_carpetas + "/" + dat[i] ;
                    nombre_del_dot = cadena_de_carpetas + "/" + dat[i] ;
                    posicion++;

                    if(opendir(cadena_de_carpetas.c_str())==NULL)
                    {
                        mkdir(cadena_de_carpetas.c_str(),0777);
                    }

                }
            }

            else
            {
                cout<<"\n\n*** INGRESE CORRECTAMENTE EL PATH ***"<<endl;
            }



            //nombre_del_dot += "/" + dat[dat.capacity()-2];
            nombre_del_dot += "/" + dat[posicion];
            nombre_del_dot += ".dot";




        }
        else
        {
            cout<<"\n\n*** DEBE INGRESAR EL PATH PARA PODER MOSTRAR EL REPORTE ***"<<endl;

        }
    }
    else
    {
        cout<<"\n\n*** DEBE INGRESAR EL NOMBRE PARA PODER MOSTRAR EL REPORTE ***"<<endl;
    }


}









