#ifndef SAKLIB_IELEMENT_MAKER_H
#define SAKLIB_IELEMENT_MAKER_H

#include <memory>
#include "../types.h"

namespace saklib
{
    class IElement;
    /*
    IElement_Maker
    ====================================================================================================
    */
    class IElement_Maker
    {
    public:
        virtual ~IElement_Maker() = default;

        std::unique_ptr<IElement> make_element(String const& ar_name) const { return v_make_element(ar_name); }
    protected:
        virtual std::unique_ptr<IElement> v_make_element(String const& ar_name) const = 0;
    };

} // namespace saklib

#endif // SAKLIB_IELEMENT_MAKER_H

