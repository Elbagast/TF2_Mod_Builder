#ifndef ZZZ_REFACTORING_H
#define ZZZ_REFACTORING_H

/*
Thinking up the required interfaces, remember:
- No templates (so implementation can be isolated)
- minimally complete
*/

namespace saklib
{
    class Char;
    class Size_Type;
    class Index;

    class TypeID;

    class Bool;
    class Int;
    class Float;
    class String;
    class Path;

    // hmm
    template <typename T>
    class Read
    {
    public:
        T get_value() const;
        T const& get_cref() const;
    };

    template <typename T>
    class Read_Write
    {
    public:
        T get_value() const;
        T const& get_cref() const;
        void set_value(T const& a_value);
    };

    template <typename T>
    class Vector;


    class Project;

    class Element_Definition;
    class Element;
    class Element_Iterator; //hmmm
    class ElementID; // hmmm

    class Attribute_Definition;
    class Attribute_Definition_Iterator;

    class Attribute_Definition_Bool;
    class Attribute_Definition_Int;
    class Attribute_Definition_Float;
    class Attribute_Definition_String;
    class Attribute_Definition_Element;

    class Attribute_Definition_Vector_Bool;
    class Attribute_Definition_Vector_Int;
    class Attribute_Definition_Vector_Float;
    class Attribute_Definition_Vector_String;
    class Attribute_Definition_Vector_Element;

    class Attribute;
    class Attribute_Iterator;

    class Attribute_Bool;
    class Attribute_Int;
    class Attribute_Float;
    class Attribute_String;
    class Attribute_Element;

    class Attribute_Vector_Bool;
    class Attribute_Vector_Int;
    class Attribute_Vector_Float;
    class Attribute_Vector_String;
    class Attribute_Vector_Element;

    class AttributeID; // hmmm

    namespace gui
    {
        class Project_Widget;
        class Element_Definition_Widget;
        class Element_Widget;
        class Attribute_Widget;
        class Attribute_Name_Widget;
        class Attribute_Type_Widget;

        class Editor_Widget_Bool;
        class Editor_Widget_Int;
        //etc...

    } // namespace Widgets



    //
    class Element_Definition
    {
    public:
        String get_type_string() const;
        void set_type_string(String const& a_value);


        Attribute_Definition_Bool add_attribute_definition_bool();

        //
        bool is_edit_locked() const;
        void lock_editing();
        // Attempt to unlock this definition, return true if the operation succeeds.
        // This object cannot be unlocked if it is being used as a definition for Elements.
        bool unlock_editing();

        bool is_being_used() const;
        Size_Type count_of_dependent_elements() const;

    };

    class Element
    {
    public:
        String get_name() const;
        void set_name(String const& a_value);
        String get_type_string() const;


        // Does this have an Attribute with this index?
        bool has_attribute_at(Index a_index) const;

        // Does this have an Attribute with this name?
        bool has_attribute_named(String const& a_name) const;

        // Get an attribute by its index
        Attribute get_attribute_at(Index a_index) const;

        // Get an attribute by its name
        Attribute get_attribute_named(String const& a_name) const;

        // Typed Attribute gets?

        // The number of Attributes
        Size_Type get_attribute_count() const;

        // typed Attribute Counts?
        //Size_Type get_attribute_bool_count() const;

        // Get all the Attributes so they can be iterated over
        Vector<Attribute> get_all_attributes() const;

        // typed Attribute gets?
        //Vector<Attribute_Bool> get_all_attribute_bool() const;


        Size_Type get_child_element_count() const;
    };



    class Attribute_Definition
    {
    public:

        // Is this Attribute_Definition owned by an Element_Definition?
        bool has_parent_element_definition() const;
        // Get the Element_Definition that owns this Attribute_Definition
        Element_Definition get_parent_element_definition() const;
        // There is no setter for the parent, instead use Element_Definition::add_attribute_definition()
        // to set this to be owned by one

        // Does this Attribute_Definition have a valid index?
        // Only true if has_parent_element_definition() is true
        bool has_index() const;
        //
        Size_Type get_index() const;

        String get_name() const;
        void set_name(String const& a_value);

        TypeID get_type() const;
        String get_type_string() const;
        void set_type(String const& a_value);

        void set_type_to_bool();
        void set_type_to_int();
        void set_type_to_float();
        void set_type_to_string();
        void set_type_to_element();

        bool is_bool() const;
        bool is_int() const;
        bool is_float() const;
        bool is_string() const;
        bool is_element() const;

        // Throw an exception if these are called for the wrong type ?
        // Or return a Null object?
        Attribute_Definition_Bool get_attribute_definition_bool() const;
        Attribute_Definition_Int get_attribute_definition_int() const;
        Attribute_Definition_Float get_attribute_definition_float() const;
        Attribute_Definition_String get_attribute_definition_string() const;
        Attribute_Definition_Element get_attribute_definition_element() const;

    private:
        class Implementation;

        Implementation* get_implementation()                { return mp_implementation.get(); }
        Implementation const* cget_implementation() const   { return mp_implementation.get(); }

        std::unique_ptr<Implementation> mp_implementation;
    };


    class Attribute
    {
    public:
        Attribute();
        Attribute(String const& a_name, TypeID a_type);
        Attribute(String const& a_name, String const& a_type);

        // explicit constructors for each type with all arguments...

        explicit Attribute(Attribute_Definition const& a_definition);

        ~Attribute();

        Attribute(Attribute const& a_other);
        Attribute& operator=(Attribute const& a_other);

        //Attribute(Attribute && a_other);
        //Attribute& operator=(Attribute && a_other);


        String get_name() const;

        TypeID get_type() const;
        String get_type_string() const;

        String get_value_string() const;

        bool is_bool() const;
        bool is_int() const;
        bool is_float() const;
        bool is_string() const;
        bool is_element() const;

        // Throw an exception if these are called for the wrong type

        Attribute_Bool& get_attribute_bool();
        Attribute_Int& get_attribute_int();
        Attribute_Float& get_attribute_float();
        Attribute_String& get_attribute_string();
        Attribute_Element& get_attribute_element();

        Attribute_Bool const& cget_attribute_bool() const;
        Attribute_Int const& cget_attribute_int() const;
        Attribute_Float const& cget_attribute_float() const;
        Attribute_String const& cget_attribute_string() const;
        Attribute_Element const& cget_attribute_element() const;
    };



    class Attribute_Definition_Bool
    {
    public:
        String get_name() const;
        void set_name(String const& a_value);

        TypeID get_type() const;
        String get_type_string() const;

        bool can_set_to_value(Bool a_value) const;

        Bool get_initial_value() const;
        void set_initial_value(Bool a_value);

        static Bool get_default_initial_value();
    };

    class Attribute_Bool
    {
    public:
        String get_name() const;

        TypeID get_type() const;
        String get_type_string() const;

        String get_value_string() const;
        Bool get_value() const;
        bool set_value(value_type a_value);

        bool can_set_to_value(Bool a_value) const;

        Bool get_initial_value() const;

        // Attribute_Definition_Bool const& m_definition;
    };



    class Attribute_Definition_Int
    {
    public:
        String get_name() const;
        void set_name(String const& a_value);

        TypeID get_type() const;
        String get_type_string() const;

        bool can_set_to_value(Int a_value) const;

        Int get_initial_value() const;
        void set_initial_value(Int a_value);

        static Int get_default_initial_value();

        Int get_minimum_value() const;
        void set_minimum_value(Int a_value);

        static Int get_default_minimum_value();

        Int get_maximum_value() const;
        void set_maximum_value(Int a_value);

        static Int get_default_maximum_value();

    };

    class Attribute_Int
    {
    public:
        String get_name() const;

        TypeID get_type() const;
        String get_type_string() const;

        String get_value_string() const;
        Int get_value() const;
        bool set_value(Int a_value);

        bool can_set_to_value(Int a_value) const;

        Int get_initial_value() const;
        Int get_minimum_value() const;
        Int get_maximum_value() const;
    };


    class Attribute_Definition_Float
    {
    public:
        String get_name() const;
        void set_name(String const& a_value);

        TypeID get_type() const;
        String get_type_string() const;

        bool can_set_to_value(Float a_value) const;

        Float get_initial_value() const;
        void set_initial_value(Float a_value);
        static Float get_default_initial_value();

        Float get_minimum_value() const;
        void set_minimum_value(Float a_value);
        static Float get_default_minimum_value();

        Float get_maximum_value() const;
        void set_maximum_value(Float a_value);
        static Float get_default_maximum_value();

        // other stuff...
    };


    class Attribute_Float
    {
    public:
        String get_name() const;

        TypeID get_type() const;
        String get_type_string() const;

        String get_value_string() const;
        Int get_value() const;
        bool set_value(Int a_value);

        bool can_set_to_value(Float a_value) const;

        Float get_initial_value() const;
        Float get_minimum_value() const;
        Float get_maximum_value() const;

        // other stuff...
    };


    class Attribute_Definition_String
    {
    public:
        String get_name() const;
        void set_name(String const& a_value);

        TypeID get_type() const;
        String get_type_string() const;

        bool can_set_to_value(String const& a_value) const;

        String get_initial_value() const;
        void set_initial_value(String const& a_value);
        static String get_default_initial_value();

        Size_Type get_maximum_length() const;
        void set_maximum_length(Size_Type a_value);
        static Size_Type get_default_maximum_length();

        bool can_have_char(Char a_char) const;
        bool has_char_constraints() const;

        bool has_char_whitelist() const;
        bool char_is_in_whitelist(Char a_char) const;
        String get_char_whitelist() const;
        void set_char_whitelist(String const& a_value);
        void add_char_to_whitelist(Char a_value);
        void remove_char_from_whitelist(Char a_value);

        bool has_char_blacklist() const;
        bool char_is_in_blacklist(Char a_char) const;
        String get_char_blacklist() const;
        void set_char_blacklist(String const& a_value);
        void add_char_to_blacklist(Char a_value);
        void remove_char_from_blacklist(Char a_value);
    };


    class Attribute_String
    {
    public:
        String get_name() const;

        TypeID get_type() const;
        String get_type_string() const;

        String get_value_string() const; //uh
        String get_value() const;
        bool set_value(String a_value);

        bool can_set_to_value(String a_value) const;

        String get_initial_value() const;

        Size get_maximum_length() const;

        bool can_have_char(Char a_char) const;
        bool has_char_constraints() const;

        bool has_char_whitelist() const;
        bool char_is_in_whitelist(Char a_char) const;
        String get_char_whitelist() const;

        bool has_char_blacklist() const;
        bool char_is_in_blacklist(Char a_char) const;
        String get_char_blacklist() const;
    };

    class Attribute_Definition_Element
    {
    public:
        String get_name() const;
        void set_name(String const& a_value);

        TypeID get_type() const;
        String get_type_string() const;

        bool can_set_to_element(Element const& a_value) const;
        bool can_set_to_element_type(String const& a_value) const;

        String get_initial_value() const;
        void set_initial_value(String const& a_value);
        static String get_default_initial_value();

        String get_initial_element_type() const;
        void set_initial_element_type(String a_value);
        static String get_default_initial_element_type();

        bool has_element_type_constraints() const;
        Vector<String> get_valid_element_types() const;
        void set_valid_element_types(Vector<String> const& a_value);

        bool is_valid_element_type(String const& a_value) const;
        void add_valid_element_type(String const& a_value);
        void remove_valid_element_type(String const& a_value);
    };

    class Attribute_Element
    {
    public:
        String get_name() const;

        TypeID get_type() const;
        String get_type_string() const;

        String get_value_string() const; //uh
        Element get_value() const;
        bool set_value(Element const& a_value);

        bool can_set_to_value(Element const& a_value) const;

        String get_initial_element_type() const;
        void set_initial_element_type(String a_value);
        static String get_default_initial_element_type();

        bool has_element_type_constraints() const;
        Vector<String> get_valid_element_types() const;
        void set_valid_element_types(Vector<String> const& a_value);

        bool is_valid_element(Element const& a_value) const;
        bool is_valid_element_type(String const& a_value) const;
        void add_valid_element_type(String const& a_value);
        void remove_valid_element_type(String const& a_value);
    };

} // namespace saklib

#endif // ZZZ_REFACTORING_H

