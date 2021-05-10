#ifndef REFERENCECHAR_H
#define REFERENCECHAR_H

#include <string>

using namespace std;

class referencechar
{
public:
    string nombreVariable;
    string valorVariable;
    string direccionMem;
    string tipoDeDato;

    string get_nombreVariable();

    string get_valorVariable();

    string get_direccionMem();

    string get_tipoDeDato();
};

#endif // REFERENCECHAR_H
