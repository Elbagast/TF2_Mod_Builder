#include "elementid_iostream.h"
#include "elementid.h"

std::ostream& Saklib::operator<<(std::ostream& stream, ElementID elementid)
{
    stream << elementid.value();
    return stream;
}

std::istream& Saklib::operator>>(std::istream& stream, ElementID /*elementid*/)
{
    return stream;
}
