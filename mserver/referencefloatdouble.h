#ifndef REFERENCEFLOATDOUBLE_H
#define REFERENCEFLOATDOUBLE_H

#include <string>

using namespace std;

class referenceFloatDouble
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

#endif // REFERENCEFLOATDOUBLE_H
