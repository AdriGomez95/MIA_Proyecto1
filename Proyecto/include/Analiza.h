#ifndef ANALIZA_H
#define ANALIZA_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;




class Analiza
{
    public:
        Analiza();
        void analiza(string cadena);

        //del mkdisk
        void MKDISK(vector<string> datos);
        void RecorreRuta(string ruta);
        //void RecorreRuta(string ruta, int s, string f, string u, int uv);

        //del rmdisk
        void RMDISK(vector<string> datos);
        void EliminaRutaArchivo(string ruta);



    protected:

    private:
};

#endif // ANALIZA_H
