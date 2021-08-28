#ifndef ANALIZADOR_H
#define ANALIZADOR_H


#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

using namespace std;


class Analizador
{
    public:
        Analizador();
        int comando;
        char entrada[100];
        char *tokens;
        char direccion[100];

        //para el mkdisk
        int size;
        char fit;
        char unidad;


        //****** ADMINISTRADOR DE DISCOS ******
        void Mkdisk(bool file);

};

#endif // ANALIZADOR_H
