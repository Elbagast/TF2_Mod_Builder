#ifndef SAKLIB_PROJECT_H
#define SAKLIB_PROJECT_H

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace saklib
{
    class Fixed_String;
    class String;
    class Element;
    class Index;
    class Attribute;

    template <typename T>
    class Vector;

    class Project
    {
    public:
        Element make_element(String const& type);

        Vector<Element> cget_all_elements() const;
        Vector<Element> cget_root_elements() const;
        Element cget_first_element() const;


    private:
        class Implementation;

        Implementation* get_implementation();
        Implementation const* cget_implementation() const;

        std::unique_ptr<Implementation> m_implementation;
    };

} // namespace saklib

#endif // PROJECT_H

