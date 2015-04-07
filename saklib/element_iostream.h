#ifndef ELEMENT_IOSTREAM_H
#define ELEMENT_IOSTREAM_H

#include <iosfwd>
#include <string>

namespace Saklib
{
    class Element;
    class Attribute;

    std::ostream& operator<<(std::ostream& stream, Element const& element);
    std::istream& operator>>(std::istream& stream, Element& element);

    // this probably makes more sense to do on the ElementID
    std::ostream& serialise_Element_as_key_values(std::ostream& stream, Element const& element, std::size_t indent_level = 0, std::string const& indent = std::string("  "));
    std::ostream& serialise_Attribute_as_key_values(std::ostream& stream, Attribute const* attribute, std::size_t indent_level = 0, std::string const& indent = std::string("  "));

} // namespace Saklib

#endif // ELEMENT_IOSTREAM_H
