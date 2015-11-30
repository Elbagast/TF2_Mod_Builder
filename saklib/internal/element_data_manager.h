#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER__FWD_H
#include "element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_H
#include "element_data.h"
#endif

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H
#include "smart_handle_manager.h"
#endif

#ifndef INCLUDE_STD_MAP
#define INCLUDE_STD_MAP
#include <map>
#endif

/*
Hmmmmmm.... It might be best to put methods for observing the data in here since all
actions that are intercepted for undoing have to go through here anyway.
 */
namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Element_Definition_Data_Manager
        //---------------------------------------------------------------------------

        class Element_Definition_Data_Manager
        {
        public:
            // Interface
            //============================================================
            // Attempt to add this definition. If a definition with a type the same as the
            // new one already exists, this will not be added and returns false. If it is
            // added, it returns true. Definitions can have the same configuration, so long
            // as they have different types.
            bool add_definition(Element_Data_Definition const& a_definition);

            // Is there a definition with this type?
            bool has_definition(std::string const& a_type) const;

            // Get a definition, throw an exception if there isn't one
            Element_Data_Definition const& cget_definition(std::string const& a_type) const;

            // The number of Elements that have been made using this definition.
            std::size_t get_definition_usage_count(std::string const& a_type) const;

            // Can this definition corresponding to this type be removed? A definition can
            // only be removed if it exists and it has a usage count of 0. If these are
            // both true then true is returned. If there is no such definition or it has
            // a usage count above 0 then false is returned.
            bool can_remove_definition(std::string const& a_type) const;

            // Try and remove the definition corresponding to this type. This function
            // calls can_remove_definition() and only removes the definition if the result
            // of that is true. If the remove cannot happen or fails then this function
            // return false, otherwise the definition corresponding to this type is
            // removed.
            bool remove_definition(std::string const& a_type);

            std::vector<std::string> get_definition_types() const;

            void increment_usage_count(std::string const& a_type);
            void decrement_usage_count(std::string const& a_type);

        private:
            using tuple_type = std::tuple<Element_Data_Definition, std::size_t>;
            using map_type = std::map<std::string, tuple_type >;

            Element_Data_Definition& get_iterator_data(map_type::iterator a_iterator);

            Element_Data_Definition const& cget_iterator_data(map_type::const_iterator a_iterator) const;

            std::size_t& get_iterator_usage_count(map_type::iterator a_iterator);

            std::size_t const& cget_iterator_usage_count(map_type::const_iterator a_iterator) const;

            // Data Members
            //============================================================
            map_type m_map;
        };


        //---------------------------------------------------------------------------
        // Element_Definition_Data_Release
        //---------------------------------------------------------------------------

        class Element_Definition_Data_Release
        {
        public:
            explicit Element_Definition_Data_Release(Element_Definition_Data_Manager& ar_element_definition_manager);

            void operator()(Element_Data& a_about_to_destruct);

        private:
            // Data Members
            //============================================================
            Element_Definition_Data_Manager* mp_element_definition_manager;
        };

        //---------------------------------------------------------------------------
        // Element_Data_Observer
        //---------------------------------------------------------------------------

        class Element_Data_Observer
        {
        public:
            virtual ~Element_Data_Observer() = 0;

            virtual void notify_set_name(Element_Data_Handle const& a_data_handle) = 0;
        };


        //---------------------------------------------------------------------------
        // Element_Data_Manager
        //---------------------------------------------------------------------------

        class Element_Data_Manager
        {
        public:
            // Typedefs
            //============================================================
            using smart_handle_type = Smart_Handle_Manager<Element_Data, Element_Definition_Data_Release>::smart_handle_type;

            // Special 6
            //============================================================
            Element_Data_Manager();

            // Interface
            //============================================================
            bool add_definition(Element_Data_Definition const& a_definition);

            bool has_definition(std::string const& a_type) const;

            Element_Data_Definition const& cget_definition(std::string const& a_type) const;

            std::size_t get_definition_usage_count(std::string const& a_type) const;

            bool can_remove_definition(std::string const& a_type) const;

            bool remove_definition(std::string const& a_type);

            std::vector<std::string> get_definition_types() const;

            Element_Data_Handle make_null_handle() const;
            Element_Data_Handle make_element_handle(std::string const& a_type);

            std::vector<Element_Data_Handle> make_all_element_handles();

        private:
            // Data Members
            //============================================================
            Element_Definition_Data_Manager m_element_definition_manager;
            Smart_Handle_Manager<Element_Data, Element_Definition_Data_Release> m_manager;
            // Name unique tracking stuff...
        };


        //---------------------------------------------------------------------------
        // Element_Data_Handle
        //---------------------------------------------------------------------------

        class Attribute_Data_Handle;

        // undo support has to go in here or in an object that holds this...
        class Element_Data_Handle
        {
            friend class Element_Data_Manager;
        public:
            // Typedefs
            //============================================================
            using smart_handle_type = Element_Data_Manager::smart_handle_type;
            using handle_type = smart_handle_type::handle_type;
            using reference_count_type = smart_handle_type::reference_count_type;

            // Special 6
            //============================================================
        private:
            Element_Data_Handle(Element_Data_Manager& ar_manager, smart_handle_type&& a_smart_handle);
        public:
            Element_Data_Handle();
            ~Element_Data_Handle();

            Element_Data_Handle(Element_Data_Handle const& other);
            Element_Data_Handle& operator=(Element_Data_Handle const& other);

            Element_Data_Handle(Element_Data_Handle && other);
            Element_Data_Handle& operator=(Element_Data_Handle && other);


            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type get_handle() const;

            Handle_Value_Type get_handle_value() const;

            reference_count_type get_reference_count() const;

            // probably don't want to expose the Element here...
            // need to supply wrapper handles for Attributes....
            Element_Data& get_element();
            Element_Data const& cget_element() const;

            // probably don't want to expose this either?..
            Element_Data_Manager* get_manager();
            Element_Data_Manager const* cget_manager() const;



            // Element_Data Wrapper Interface
            //============================================================
            std::string const& cget_type() const;

            std::string const& cget_name() const;
            void set_name(std::string const& a_name);

            std::size_t get_attribute_count() const;

            Attribute_Data_Handle get_attribute_at(std::size_t a_index);

            std::vector<Attribute_Data_Handle> get_attributes();


        private:
            // Data Members
            //============================================================
            Element_Data_Manager* mp_manager;
            smart_handle_type m_smart_handle;
        };

    } // namespace internal
} // namespace saklib


#endif // ELEMENT_DATA_MANAGER_H
