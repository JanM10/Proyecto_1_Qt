#ifndef REFERENCEINTLONG_H
#define REFERENCEINTLONG_H

#include <string>

using namespace std;

class referenceIntLong
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

#endif // REFERENCEINTLONG_H
