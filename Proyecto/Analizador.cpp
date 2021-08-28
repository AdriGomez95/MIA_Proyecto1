#include "Analizador.h"

Analizador::Analizador()
{
    this->size = 0;
    this->fit = 'bf';
    this->unidad = 'm';
}




void Analizador::Mkdisk(bool file)
{
    cout<< "   aquiiiii   en MKDISK"<< endl;

    size = 0; //obligatorio
    fit = 'b'; //opcional bf (->w)
    unidad = 'm'; //opcional m (->k)

    memset(direccion,0,100); //se llena el char de direccion de 0


    tokens = strtok(NULL," =");

    //recorre todos los tokens
    while(tokens!=NULL)
    {

        if(strcmp(tokens,"-size") == 0)
        {
            tokens=strtok(NULL," =");

            //el numero debe ser mayor a 0, si no, debe mostrar error
            int numero = atoi(tokens);
            size = numero;
        }

        else if(strcmp(tokens,"-f") == 0)
        {
            tokens = strtok(NULL," =");

            if(strcmp(tokens,"bf") == 0)
            {
                fit='b';
            }
            else if(strcmp(tokens,"ff") == 0)
            {
                fit='f';
            }
            else if(strcmp(tokens,"wf") == 0)
            {
                fit='w';
            }
        }

        else if(strcmp(tokens,"-u") == 0)
        {
            //Obtiene el valor seguido del . y avanza
            tokens=strtok(NULL," =");

            if(*tokens == 'k')
            {
                unidad = 'k';
            }
            else if(*tokens == 'm')
            {
                unidad = 'm';
            }

        }

        else if(strcmp(tokens,"-path") == 0)
        {
        }


        tokens = strtok(NULL," =");
    }


    cout<<"\nvamos a crear el archivo c:"<<endl;

    cout<< ""<<endl;
    cout<< "size: "<<size<<endl;
    cout<< "unidad: "<<unidad<<endl;
    cout<< "fit: "<<fit<<endl;


}


