#ifndef SAKLIB_IELEMENT_DEFINITION_STORAGE_H
#define SAKLIB_IELEMENT_DEFINITION_STORAGE_H

#include <vector>
#include <memory>

namespace saklib
{
    class IAttribute_Base;
    class IAttribute_Definition_Base;
    /*
    IElement_Definition_Storage
    ====================================================================================================
    */
    class IElement_Definition_Storage
    {
    public:
        using attribute_storage_type = std::vector<std::unique_ptr<IAttribute_Base>>;
        using attribute_definition_storage_type = std::vector<std::unique_ptr<IAttribute_Definition_Base>>;

        virtual ~IElement_Definition_Storage() = default;

        attribute_storage_type make_attributes() const { return v_make_attributes(); }
    protected:
        virtual attribute_storage_type v_make_attributes() const = 0;
    };

} // namespace saklib

#endif // SAKLIB_IELEMENT_DEFINITION_STORAGE_H

