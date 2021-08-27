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
        int opcion;
        char entrada[100];
        char *tokens;
        char Unity;
        int Unidad;
        int size;
        char type;
        char fit;
        char fit_disk;
        char direccion[100];
        bool prueba;
        bool ver;

        //****** ADMINISTRADOR DE DISCOS ******
        void Mkdisk(bool file);
        //void CrearArchivo(bool bandera_path, bool bandera_size, bool bandera_unit);

};

#endif // ANALIZADOR_H
