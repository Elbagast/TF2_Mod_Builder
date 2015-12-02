TF2 Mod Builder - in development
==============================
Goal: Application to manage the development, deployment and maintenance of mods for Source engine games,
specifically Team Fortress 2.


Source Army Knife Library
------------------------------
namespace saklib
Front end API classes that have simple interfaces and require no knowledge of how they work in order 
to use them. 

class Project_Manager
Contains an arbitrary collection of Projects and holds information shared between all of them.

class Project
Root object containing a collection of Element trees. (Project has a type which indicates a specific configuration?) This
class is responsible for managing its data, undo capabilities for changes to that data, and saving it
to a file.

class Element
Contains a key-values dictionary of Attributes. An Element has a type that is defined in a 
definition that determines the number, names and types of Attributes. All Elements have a unique ID
that is not user editable, and a unique name that is. An Element's name must be unique among all 
the Elements present within the Project that it is part of.

class Attribute
Represents a named editable data value of a fixed type that has constraints. This class
only gives access to generic data common to all attribute types, and does not allow editing the data 
value, but you can get a typed Attribute (e.g. Attribute_Bool) from it that will be associated with 
the data and supply the full interface.

class Attribute_Bool
class Attribute_Int
...
class Attribute_Element

class Attribute_Vector_Bool
class Attribute_Vector_Int
...
class Attribute_Vector_Element
Typed attributes that give full access to the data and its constraints, whatever those may be.

to define:
- Classes and mechanism for navigating the data (iterators etc.) unless these classes contain that capability?
- Mechanism of Element_Definitions, does it have its own class or is it part of the Project_Manager 
and/or Project?


Internal Library
------------------------------
namespace saklib::internal
All of the implementation classes etc. go here

Not going to bother describing any of this yet.