#ifndef SAK_GUI_ABSTRACT_STATE_CHANGER_HPP
#define SAK_GUI_ABSTRACT_STATE_CHANGER_HPP

namespace sak
{
  namespace gui
  {
    //---------------------------------------------------------------------------
    // Abstract_State_Changer
    //---------------------------------------------------------------------------
    // Change the state of an object to the valid or invalid state. This should
    // not change the data, only the cosmetic state of the object.
    template <typename T>
    class Abstract_State_Changer
    {
    public:
        virtual ~Abstract_State_Changer() = 0;

        virtual void set_to_valid(T& a_line_edit) = 0;
        virtual void set_to_invalid(T& a_line_edit) = 0;
    };
  }
}

template <typename T>
sak::gui::Abstract_State_Changer<T>::~Abstract_State_Changer() = default;

#endif // SAK_GUI_ABSTRACT_STATE_CHANGER_HPP
