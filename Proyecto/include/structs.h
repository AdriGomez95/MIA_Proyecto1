#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <ctime>

using namespace std;



class structs
{
    public:
        structs();

        //estructuras
        typedef struct _MBR {
            int size_mbr;
            int asignacion_mbr;
            char fit_mbr;
            time_t fecha_mbr;

        }MBR;

    protected:

    private:
};

#endif // STRUCTS_H
