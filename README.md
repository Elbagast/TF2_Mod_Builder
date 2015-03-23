TF2 Mod Builder
==============================
I've been obsessing over Elements and Attributes for so long I've forgotten why
I was playing around with them in the first place, but more importantly, I can't
really progress with them as I haven't figured out what I actually want from
them. So this is back to the drawing board - making the app that made me arrive
at needing that, but now with what I've learned since. Then I'll figure out what
will work.


Data
------------------------------
The base data structure is a dictionary of configured objects which contain a number of
objects that contain specific data types. This is built specifically to model the
data struture used in Valve's source engine as it's used in a lot of places in assets.

    class Element
    {
        string name;
        string type;
        vector<Attribute*> attributes;
    };

    abstract
    class Attribute
    {
        string name;
        type_id type; -> currently this is actually a virtual call to the derived class
    };
    
    template <typename T>
    class Attribute_Type:
        public Attribute
    {
        T data;
    };

Attribute's type identifier is used to determine the true type of an Attribute so that
data can be accessed appropriately. I want to disconnect classes that will edit the
data from the structure of the data, but largely this because writing code to parse
lots of different classes that are just different data configurations with any error
checking gets error prone and brittle incredibley fast (doing that directly led to
investigating this data structure more thoroughly).

In Valve's implementation Attribute has no derived types, the data is stored as `void*`
with a size value. I am avoiding this because I'd rather make use of the type system
as appropriate, and stops Attribute having a fat interface.


Configuring Data
------------------------------
Element is a class that exhibits polymorphism through its configuration rather than
through derived classes. As a result users must build a definition of the configuration
which is used to construct Elements of that type. This allows users to build or edit
Element configurations as needed - this is valuable as we don't have control over the
engine, so e.g. material shader definitions may change or need to be corrected.

    class Element_Definition
    {
        string type;
        vector<Attribute_Definition> attributes;
    };
    
    class Attribute_Definition
    {
        string name;
        type_id type;
    };
    
    Element::Element(Element_Definition const& definition) -> result in configured Element

This may change at a later date, it isn't yet clear how best it would be to implement
features such as making Elements use a different editor configuration.

Currently configurations are stored in a static manager inside class Element so there's
only one place for them and you must register configurations beforehand. This probably
needs to change later.


***
Constraining Data
------------------------------
I haven't figured out a good way of supplying configurable constraints to Attribute data,
it just seems to be a bit of a mess right now...

Want things along the lines of a float between `0.0` and `1.0`, but also complicated things like
ElementID that can only be Elements of given type(s), or string that can only be Attribute
names from another Element (this one applies to shader proxies).
***


Referencing Data
------------------------------
Since this is data that will be saved/loaded we need an abstraction other than raw
pointers to that relationships can be serialised properly, so there are ID classes that
encapsulate plain int values as identifiers:

    class ElementID
    {
        unsigned int value;
    };
    
    class AttributeID
    {
        ElementID element;
        unsigned int index; -> index location in the Element's Attribute vector
    };

These are meaningless without a class to manage them and provide access to the data,
so this disconnects Attributes that contain Elements from the actual interface of
that class, which moves ownership considerations elsewhere.

Valve's implementation is a little confusing in this respect. Saved data referencing specific
Elements contain UUIDs to identify them, but there is also a handle class for Elements.
This implies they switch to UUIDs when serialising but use a simpler system internally?..
Or both?...


Managing Data
------------------------------
A project the user works on has a pool of Elements that are relevant only to it. This
immediately implies to me that while a singleton implementation of a manager class would
make things a bit easier to think about, it's actually inaccurate and has its own issues.

    class Element_Manager
    {
        map<ElementID, Element> data; -> currently Elements aren't stored as pointers...
                                         this complicates cases where an ElementID was not
                                         found...
    };

Right now if you want to add extra things about Elements to be tracked you need to make
seperate managers for them. This seperates concerns but is a bit messy right now - its
not too clear how needed some of these concerns are...

    class Project_Manager
    {
        Element_Manager elements;
        Other_Managers other; -> things pertaining to reference counting etc. since that
                                 is potentially complicated with undoable commands
        ...
    };


Editing Data
------------------------------
It's all pointless without being able to do this, but we want the facility to undo edits
so things get a bit complicated. We use the command pattern to encapsulate changes and
references to everything that needs to be updated. If we're tracking ref counts then
Command subclasses need to know how to get to things that manage that.

    abstract
    class Command
    {
        virtual void execute() = 0;
        virtual void unexecute() = 0;
    };
    
    class Command_History
    {
        list<Command*> commands;
        iterator position;
    };

A big question is:
- does everything that issues commands know about a `Project_Manager` that contains a
Command_History,
    or
- does it know about a `Project_Manager` and a `Command_History` that is related to it?

The first one feels like it makes more sense from the perspective of what a project would
be, but this also means `Project_Manager` is going to become a monolithic class that
manages everything...especially if it's also keeping the visualisations of data in sync
too....


Visualising Data
------------------------------
`QWidget` classes to edit Elements and Attributes don't pose too much of a problem if they
know about the `Project_Manager`:

    class Project_Manager
    {
        ...
        Element_Widget_Manager element_widgets;
        ...
    };
    
    class Element_Widget_Manager
    {
        map<ElementID, Element_Widget*> widgets;
    };
    
    class Element_Widget
    {
        ElementID id;                                   -> encapsulate this pairing?
        Project_Manager& manager;                       -> or is it not worth it?
        vector<Attribute_Widget*> attribute_widgets;
    };
    
    etc.

Then the widgets issue commands based on user input, but also need to be updated via
commands/other edit locations if need be e.g. an Element is renamed in the outliner.



...there's probably loads more to put here
