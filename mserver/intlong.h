#ifndef INTLONG_H
#define INTLONG_H
#include <string>

using namespace std;

///
/// \brief The intlong class
///
class intlong
{
public:
    string nombreVariable;
    string valorVariable;
    string direccionMem;
    string valorBytes;

    ///
    /// \brief get_nombreVariable
    /// \return
    ///
    string get_nombreVariable();

    ///
    /// \brief get_valorVariable
    /// \return
    ///
    string get_valorVariable();

    ///
    /// \brief get_direccionMem
    /// \return
    ///
    string get_direccionMem();

    ///
    /// \brief get_valorBytes
    /// \return
    ///
    string get_valorBytes();
};

#endif // INTLONG_H
