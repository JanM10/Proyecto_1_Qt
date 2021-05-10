#include "referencefloatdouble.h"

#include <sstream>

string referenceFloatDouble::get_nombreVariable(){
    return nombreVariable;
}

string referenceFloatDouble::get_valorVariable(){
    return valorVariable;
}

string referenceFloatDouble::get_direccionMem(){
    ostringstream get_the_address;
    get_the_address << &valorVariable;
    direccionMem = get_the_address.str();
    return direccionMem;
}

string referenceFloatDouble::get_tipoDeDato(){
    return tipoDeDato;
}
