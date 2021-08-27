#ifndef MKDISK_H
#define MKDISK_H
#include <iostream>
#include <string>

using namespace std;

class mkdisk
{
    public:
        mkdisk();
        int size;
        string f;
        string u;
        string path;

        void dataShow(mkdisk *disco);
};

#endif // MKDISK_H
