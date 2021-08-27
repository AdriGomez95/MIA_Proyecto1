#include "Analizador.h"

Analizador::Analizador()
{
    this->Unity='k';
    this->Unidad=1;
    this->size=0;
    this->type='p';
    this->fit='w';
    this->fit_disk='f';
}




void Analizador::Mkdisk(bool file)
{
    cout<< "   aquiiiii   4"<< endl;
    printf("\nMKDISK\n");
    Unity='k';
    Unidad=1;
    type='p';
    fit='w';
    fit_disk='f';
    size=0;

    memset(direccion,0,100); //se llena el char de direccion de 0
    bool bandera_unit,bandera_path,bandera_size,bandera_name;
    bandera_unit=bandera_path=bandera_size=bandera_name=ver=prueba= false;
    tokens = strtok(NULL," =");

    while(tokens!=NULL)
    {
        if(strcmp(tokens,"-u") == 0)
        {
            bandera_unit=true;
            tokens=strtok(NULL," =");//Obtiene el valor seguido del . y avanza

            if(*tokens=='k')
            {
                Unidad=1024;
                Unity='k';
            }
            else if(*tokens=='m')
            {
                Unidad= 1024*1024;
                Unity='m';
            }
            else
            {
                if(file)
                {
                    printf("ERROR!! La unidad %s no esta definia, debe ser 'm' o 'k'.\nLINEA DEL ERROR: %d\n",tokens/*,contador*/);
                }
                else
                {
                    printf("ERROR!! La unidad %s no esta definia, debe ser 'm' o 'k'\n",tokens);
                }

                ver = true;
                break;
            }
        }
        else if(strcmp(tokens,"-f")==0)
        {
        }
        else if(strcmp(tokens,"-path") == 0)
        {
        }
        else if(strcmp(tokens,"-size") == 0)
        {
        }
        else
        {
            printf("Error mkdisk: %s", tokens);
            prueba=true;
            break;
        }

        tokens = strtok(NULL," =");
    }

    if(prueba)
    {
        if(file)
        {
            printf("***** Comando invalido ingresado en Mkdisk *****\n***** LINEA DEL ERROR: %d\n"/*,contador*/);
        }
        else
        {
            printf("***** Comando invalido ingresado en Mkdisk *****\n");
        }
    }
    else
    {
        //CrearArchivo(bandera_path,bandera_size,bandera_unit);
        printf("vamos a crear el archivo c:");
    }

}


