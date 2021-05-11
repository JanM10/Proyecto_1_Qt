#ifndef FLOATDOUBLE_H
#define FLOATDOUBLE_H
#include <string>

using namespace std;

class floatdouble
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

#endif // FLOATDOUBLE_H
