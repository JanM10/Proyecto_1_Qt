#include "floatdouble.h"
#include <string>
#include <sstream>
#include <iostream>

string floatdouble::get_nombreVariable(){
    return nombreVariable;
}

float floatdouble::get_valorVariable(){
    return valorVariable;
}

string floatdouble::get_direccionMem(){
    ostringstream get_the_address;
    get_the_address << &valorVariable;
    direccionMem = get_the_address.str();
    return direccionMem;
}

string floatdouble::get_valorBytes(){
    return valorBytes;
}
