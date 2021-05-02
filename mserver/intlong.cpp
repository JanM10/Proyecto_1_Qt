#include "intlong.h"
#include "string.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

///
/// \brief intlong::get_nombreVariable
/// \return
///Regresa el nombre de la variable
string intlong::get_nombreVariable(){
    return nombreVariable;
}

///
/// \brief intlong::get_valorVariable
/// \return
///Regresa el valor de la variable
int intlong::get_valorVariable(){
    return valorVariable;
}

///
/// \brief intlong::get_direccionMem
/// \return
///Regresa la direccion de memoria de la variable
string intlong::get_direccionMem(){
    ostringstream get_the_address;
    get_the_address << &valorVariable;
    direccionMem = get_the_address.str();
    return direccionMem;
}
///
/// \brief intlong::get_valorBytes
/// \return
///Regresa el valor en bytes del tipo de dato de la variable
string intlong::get_valorBytes(){
    return valorBytes;
}



