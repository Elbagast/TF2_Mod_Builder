#ifndef STATE_CHANGER_H
#define STATE_CHANGER_H

namespace qtlib
{
    namespace abstract
    {
        //---------------------------------------------------------------------------
        // State_Changer
        //---------------------------------------------------------------------------
        // Change the state of an object to the valid or invalid state. This should
        // not change the data, only the cosmetic state of the object.
        template <typename T>
        class State_Changer
        {
        public:
            virtual ~State_Changer() = 0;

            virtual void set_to_valid(T& a_line_edit) = 0;
            virtual void set_to_invalid(T& a_line_edit) = 0;
        };
    }
}

template <typename T>
qtlib::abstract::State_Changer<T>::~State_Changer() = default;

#endif // STATE_CHANGER_H
