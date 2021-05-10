#include "referenceintlong.h"

#include <sstream>

string referenceIntLong::get_nombreVariable(){
    return nombreVariable;
}

string referenceIntLong::get_valorVariable(){
    return valorVariable;
}

string referenceIntLong::get_direccionMem(){
    ostringstream get_the_address;
    get_the_address << &valorVariable;
    direccionMem = get_the_address.str();
    return direccionMem;
}

string referenceIntLong::get_tipoDeDato(){
    return tipoDeDato;
}
