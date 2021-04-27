#include "intlong.h"
#include "string.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

intlong::intlong(string nV, string vV, string vB){
    nombreVariable = nV;
    valorVariable = vV;
    ostringstream get_the_address;
    get_the_address << &vV;
    direccionMem = get_the_address.str();
    valorBytes = vB;
}

string intlong::get_nombreVariable(){
    return nombreVariable;
}

string intlong::get_valorVariable(){
    return valorVariable;
}

string intlong::get_direccionMem(){
    return direccionMem;
}

string intlong::get_valorBytes(){
    return valorBytes;
}



