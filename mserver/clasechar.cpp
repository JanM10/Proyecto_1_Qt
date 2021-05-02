#include "clasechar.h"
#include <string>
#include <sstream>
#include <iostream>

string claseChar::get_nombreVariable(){
    return nombreVariable;
}

string claseChar::get_valorVariable(){
    return valorVariable;
}

string claseChar::get_direccionMem(){
    ostringstream get_the_address;
    get_the_address << &valorVariable;
    direccionMem = get_the_address.str();
    return direccionMem;
}

string claseChar::get_valorBytes(){
    return valorBytes;
}

