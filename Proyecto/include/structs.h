#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
//#include <ctime>
#include <time.h>

using namespace std;



class structs
{
    public:
        structs();

        typedef struct _Particion{
            char    part_status;
            char    part_type;
            char    part_fit;
            int     part_start;
            int     part_size;
            char    part_name[16];
        }Particion;



        typedef struct _MBR {
            int         size_mbr;
            int         signature_mbr;
            char        fit_mbr;
            time_t      fecha_mbr;
            Particion   particion1_mbr;
            Particion   particion2_mbr;
            Particion   particion3_mbr;
            Particion   particion4_mbr;
        }MBR;

};



#endif // STRUCTS_H
