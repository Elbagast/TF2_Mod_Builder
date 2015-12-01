#include "elementid_iostream.h"
#include "elementid.h"

std::ostream& saklib::operator<<(std::ostream& stream, ElementID elementid)
{
    stream << elementid.value();
    return stream;
}

std::istream& saklib::operator>>(std::istream& stream, ElementID /*elementid*/)
{
    return stream;
}
