#ifndef INODE_SECTION_H
#define INODE_SECTION_H

namespace Saklib
{
    /*
    INode_Section
    ====================================================================================================
    Class which describes the interface that allows editors of Node data to access a given section in a
    generic fashion.
    */
    template <typename T>
    class INode_Section
    {
    public:
        virtual ~INode_Section() = default;

        // Virtual Interface
        //============================================================

        // Name
        //------------------------------------------------------------
        virtual String const& name() const = 0;
        virtual void set_name(String const& new_name) = 0;
        virtual bool user_can_set_name() const = 0;
        virtual bool user_set_name(String const& new_name) = 0;
        virtual void set_user_can_set_name(bool state) = 0;
    };


} // namespace Saklib

#endif // INODE_SECTION_H

