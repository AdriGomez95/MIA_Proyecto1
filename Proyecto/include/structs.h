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



        typedef struct _EBR {
            char        name_ebr[16];
            int         next_ebr;
            int         size_ebr;
            int         start_ebr;
            char        fit_ebr;
            char        status_ebr;
        }EBR;

};



#endif // STRUCTS_H
