#ifndef CLASECHAR_H
#define CLASECHAR_H
#include <string>

using namespace std;


class claseChar
{
public:
    string nombreVariable;
    string valorVariable;
    string direccionMem;
    string valorBytes;

    string get_nombreVariable();


    string get_valorVariable();


    string get_direccionMem();

    string get_valorBytes();

};

#endif // CLASECHAR_H
