# Source Army Knife Sub-Library
Implements the core data storage and manipulation of a collection of Entities,
which are made up of seperate component parts.

## Public Interface
The following components are available for use:


'class Entity_Manager' in 'entity_manager.hpp'
The user supplies a collection of 'Abstract_Entity_Maker' objects that this
class will use as the available Entity types. The user can then manipulate
the collection by adding or removing Entities, editing Entity data and undoing
or redoing edits to the collection. 'Entity_Manager' keeps the state of all
Entities valid for all edits and undos made and informs any 'Abstract_Observer'
objects that have been added to it via 'Signal' objects or subclasses.
