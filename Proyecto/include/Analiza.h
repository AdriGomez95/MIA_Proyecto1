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
        void MKDISK(vector<string> datos);
        void RecorreRuta(string ruta);







    protected:

    private:
};

#endif // ANALIZA_H
