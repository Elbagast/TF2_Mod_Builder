#ifndef PROJECT_SIGNALBOX_HPP
#define PROJECT_SIGNALBOX_HPP

#include <cstddef>
#include "shared/signalbox.hpp"

namespace sak
{
    class Project_Signalbox :
            public file::abstract::signalbox
            //,public Handle_Signalbox<Texture_HPPandle> // etc. Same functions, different arg types.
    {
    public:
        ~Project_Signalbox() override = default;
    };

}

#endif // PROJECT_SIGNALBOX_HPP
