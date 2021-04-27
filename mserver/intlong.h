#ifndef INTLONG_H
#define INTLONG_H
#include <string>

using namespace std;

class intlong
{
public:
    string nombreVariable;
    string valorVariable;
    string direccionMem;
    string valorBytes;
    intlong(string nV, string vV, string vB);

    string get_nombreVariable();
    string get_valorVariable();
    string get_direccionMem();
    string get_valorBytes();
};

#endif // INTLONG_H
