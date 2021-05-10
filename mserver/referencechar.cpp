#include "referencechar.h"

#include <sstream>

string referencechar::get_nombreVariable(){
    return nombreVariable;
}

string referencechar::get_valorVariable(){
    return valorVariable;
}

string referencechar::get_direccionMem(){
    ostringstream get_the_address;
    get_the_address << &valorVariable;
    direccionMem = get_the_address.str();
    return direccionMem;
}

string referencechar::get_tipoDeDato(){
    return tipoDeDato;
}
