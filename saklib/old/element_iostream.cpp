#include "element_iostream.h"
#include "types.h"
#include "element.h"
#include "all_attributes.h"
#include "elementid_iostream.h"

std::ostream& saklib::operator<<(std::ostream& stream, Element const& element)
{
    stream << "N: \"" << element.name() << "\" T: " << element.type() << std::endl;
    for (size_type attribute_index = 0, end = element.attribute_count(); attribute_index != end; ++attribute_index)
    {
        auto lp_attribute = element.cattribute(attribute_index);

        stream << " N: \"" << lp_attribute->name() << "\" T: \"" << lp_attribute->type_string() << "\" V: \"";
        switch (lp_attribute->type_enum())
        {
        case Type_Enum::Bool:
            stream << attribute_enum_cast<Type_Enum::Bool>(lp_attribute)->value();
            break;
        case Type_Enum::Int:
            stream << attribute_enum_cast<Type_Enum::Int>(lp_attribute)->value();
            break;
        case Type_Enum::Double:
            stream << attribute_enum_cast<Type_Enum::Double>(lp_attribute)->value();
            break;
        case Type_Enum::String:
            stream << attribute_enum_cast<Type_Enum::String>(lp_attribute)->value();
            break;
        case Type_Enum::Path:
            stream << attribute_enum_cast<Type_Enum::Path>(lp_attribute)->value().string();
            break;
        case Type_Enum::ElementID:
            stream << attribute_enum_cast<Type_Enum::ElementID>(lp_attribute)->value();
            break;

        case Type_Enum::Vector_Bool:
            stream << "[ ";
            for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Bool>(lp_attribute)->vector())
                stream << "\"" << item << "\", ";
            stream << " ]";
            break;
        case Type_Enum::Vector_Int:
            stream << "[ ";
            for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Int>(lp_attribute)->vector())
                stream << "\"" << item << "\", ";
            stream << " ]";
            break;
        case Type_Enum::Vector_Double:
            stream << "[ ";
            for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Double>(lp_attribute)->vector())
                stream << "\"" << item << "\", ";
            stream << " ]";
            break;
        case Type_Enum::Vector_String:
            stream << "[ ";
            for (auto const& item : attribute_enum_cast<Type_Enum::Vector_String>(lp_attribute)->vector())
                stream << "\"" << item << "\", ";
            stream << " ]";
            break;
        case Type_Enum::Vector_Path:
            stream << "[ ";
            for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Path>(lp_attribute)->vector())
                stream << "\"" << item.string() << "\", ";
            stream << " ]";
            break;
        case Type_Enum::Vector_ElementID:
            stream << "[ ";
            for (auto const& item : attribute_enum_cast<Type_Enum::Vector_ElementID>(lp_attribute)->vector())
                stream << "\"" << item << "\", ";
            stream << " ]";
            break;
        case Type_Enum::Undefined:
        default:
            break;
        }

        stream << "\"" << std::endl;
    }
    return stream;
}

std::istream& saklib::operator>>(std::istream& stream, Element& /*element*/)
{
    return stream;
}


std::ostream& saklib::serialise_Element_as_key_values(std::ostream& stream, Element const& element, std::size_t indent_level, std::string const& indent)
{
    auto lamda_indent = [&stream, &indent](std::size_t i)
    {
        for (std::size_t count = 0; count != i; ++count)
            stream << indent;
    };

    lamda_indent(indent_level);
    stream << "\"" << element.type() << "\" \"" << element.name() << "\"" << std::endl;
    lamda_indent(indent_level);
    stream << "{" << std::endl;
    auto attribute_indent_level = indent_level + 1;
    for (size_type attribute_index = 0, end = element.attribute_count(); attribute_index != end; ++attribute_index)
    {
        auto lp_attribute = element.cattribute(attribute_index);
        serialise_Attribute_as_key_values(stream, lp_attribute, attribute_indent_level, indent);
        stream << std::endl;
    }
    lamda_indent(indent_level);
    stream << "}" << std::endl;
    return stream;
}

std::ostream& saklib::serialise_Attribute_as_key_values(std::ostream& stream, Attribute const* attribute, std::size_t indent_level, std::string const& indent)
{
    auto lamda_indent = [&stream, &indent](std::size_t i)
    {
        for (std::size_t count = 0; count != i; ++count)
            stream << indent;
    };

    lamda_indent(indent_level);
    stream << "\"" << attribute->type_string() << "\" \"" << attribute->name() << "\" = ";
    switch (attribute->type_enum())
    {
    case Type_Enum::Bool:
        stream << "\"" << attribute_enum_cast<Type_Enum::Bool>(attribute)->value() << "\"";
        break;
    case Type_Enum::Int:
        stream << "\"" << attribute_enum_cast<Type_Enum::Int>(attribute)->value() << "\"";
        break;
    case Type_Enum::Double:
        stream << "\"" << attribute_enum_cast<Type_Enum::Double>(attribute)->value() << "\"";
        break;
    case Type_Enum::String:
        stream << "\"" << attribute_enum_cast<Type_Enum::String>(attribute)->value() << "\"";
        break;
    case Type_Enum::Path:
        stream << "\"" << attribute_enum_cast<Type_Enum::Path>(attribute)->value().string() << "\"";
        break;
    case Type_Enum::ElementID:
        stream << "\"" << attribute_enum_cast<Type_Enum::ElementID>(attribute)->value().value() << "\"";
        break;

    case Type_Enum::Vector_Bool:
        stream << "[ ";
        for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Bool>(attribute)->vector())
            stream << "\"" << item << "\", ";
        stream << " ]";
        break;
    case Type_Enum::Vector_Int:
        stream << "[ ";
        for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Int>(attribute)->vector())
            stream << "\"" << item << "\", ";
        stream << " ]";
        break;
    case Type_Enum::Vector_Double:
        stream << "[ ";
        for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Double>(attribute)->vector())
            stream << "\"" << item << "\", ";
        stream << " ]";
        break;
    case Type_Enum::Vector_String:
        stream << "[ ";
        for (auto const& item : attribute_enum_cast<Type_Enum::Vector_String>(attribute)->vector())
            stream << "\"" << item << "\", ";
        stream << " ]";
        break;
    case Type_Enum::Vector_Path:
        stream << "[ ";
        for (auto const& item : attribute_enum_cast<Type_Enum::Vector_Path>(attribute)->vector())
            stream << "\"" << item.string() << "\", ";
        stream << " ]";
        break;
    case Type_Enum::Vector_ElementID:
        stream << "[ ";
        for (auto const& item : attribute_enum_cast<Type_Enum::Vector_ElementID>(attribute)->vector())
            stream << "\"" << item << "\", ";
        stream << " ]";
        break;
    case Type_Enum::Undefined:
    default:
        break;
    }
    return stream;
}
