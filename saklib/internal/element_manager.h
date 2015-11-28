#ifndef SAKLIB_INTERNAL_ELEMENT_MANAGER_H
#define SAKLIB_INTERNAL_ELEMENT_MANAGER_H

#ifndef SAKLIB_INTERNAL_ELEMENT_H
#include "element.h"
#endif

#include "smart_handle_manager.h"


#include <map>

namespace saklib
{
    namespace internal
    {
        class Element_Definition_Manager
        {
        public:

            // Attempt to add this definition. If a definition with a type the same as the
            // new one already exists, this will not be added and returns false. If it is
            // added, it returns true. Definitions can have the same configuration, so long
            // as they have different types.
            bool add_definition(Element_Definition const& a_definition);

            // Is there a definition with this type?
            bool has_definition(String const& a_type) const;

            // Get a definition, throw an exception if there isn't one
            Element_Definition const& cget_definition(String const& a_type) const;

            // The number of Elements that have been made using this definition.
            Size_Type get_definition_usage_count(String const& a_type) const;

            // Can this definition corresponding to this type be removed? A definition can
            // only be removed if it exists and it has a usage count of 0. If these are
            // both true then true is returned. If there is no such definition or it has
            // a usage count above 0 then false is returned.
            bool can_remove_definition(String const& a_type) const;

            // Try and remove the definition corresponding to this type. This function
            // calls can_remove_definition() and only removes the definition if the result
            // of that is true. If the remove cannot happen or fails then this function
            // return false, otherwise the definition corresponding to this type is
            // removed.
            bool remove_definition(String const& a_type);

            std::vector<String> get_definition_types() const;

            void increment_usage_count(String const& a_type);
            void decrement_usage_count(String const& a_type);

        private:
            using map_type = std::map<String, std::tuple<Element_Definition, Size_Type> >;

            // Data Members
            //============================================================
            map_type m_map;
        };


        class Element_Definition_Release
        {
        public:
            explicit Element_Definition_Release(Element_Definition_Manager& ar_element_definition_manager);

            void operator()(Element& a_about_to_destruct);

        private:
            // Data Members
            //============================================================
            Element_Definition_Manager* mr_element_definition_manager;
        };


        class Element_Manager
        {
        public:
            // Typedefs
            //============================================================
            using smart_handle_type = Smart_Handle_Manager<Element, Element_Definition_Release>::smart_handle_type;

            // Special 6
            //============================================================
            Element_Manager();

            // Interface
            //============================================================
            bool add_definition(Element_Definition const& a_definition);

            bool has_definition(String const& a_type) const;

            Element_Definition const& cget_definition(String const& a_type) const;

            Size_Type get_definition_usage_count(String const& a_type) const;

            bool can_remove_definition(String const& a_type) const;

            bool remove_definition(String const& a_type);

            std::vector<String> get_definition_types() const;

            Element_Handle make_null_element() const;
            Element_Handle make_element(String const& a_type);

        private:
            // Data Members
            //============================================================
            Element_Definition_Manager m_element_definition_manager;
            Smart_Handle_Manager<Element, Element_Definition_Release> m_manager;
            // Name unique tracking stuff...
        };


        // undo support has to go in here or in an object that holds this...
        class Element_Handle
        {
            friend class Element_Manager;
        public:
            // Typedefs
            //============================================================
            using smart_handle_type = Element_Manager::smart_handle_type;
            using handle_type = smart_handle_type::handle_type;
            using reference_count_type = smart_handle_type::reference_count_type;

            // Special 6
            //============================================================
            Element_Handle();
        private:
            Element_Handle(Element_Manager& ar_manager, smart_handle_type&& a_smart_handle);
        public:

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type get_handle() const;

            Handle_Value_Type get_handle_value() const;

            reference_count_type get_reference_count() const;

            Element& get_element();
            Element const& cget_element() const;

            Element_Manager* get_manager();
            Element_Manager const* cget_manager() const;
        private:
            // Data Members
            //============================================================
            Element_Manager* mr_manager;
            smart_handle_type m_smart_handle;
        };

    } // namespace internal
} // namespace saklib


#endif // ELEMENT_MANAGER_H
