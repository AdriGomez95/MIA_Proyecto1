#include "mkdisk.h"

#include <fstream>
#include <list>
#include <stdlib.h>

mkdisk::mkdisk()
{
    //ctor
}



void dataShow(mkdisk *disco)
{
    //disco->path.remove(char('"'));

    //pregunta si el tamaño esta vacio
    if(disco->size < 0)
    {
        cout<<" Tamaño 0 no existe "<<endl;
    }
    else
    {
        //pregunta si el path esta vacio

        cout<<" Tamaño si existe "<<endl;
    }


}
