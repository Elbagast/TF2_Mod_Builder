#ifndef SAK_SHARED_INTERFACE_HPP
#define SAK_SHARED_INTERFACE_HPP

#include "fwd/interface.hpp"
#include "fwd/manager.hpp"
#include "fwd/data_manager.hpp"
#include <generic/fwd/command_history.hpp>
#include "object.hpp"

#include <vector>

namespace sak
{
  namespace shared
  {
    template <typename T, std::size_t Index>
    struct do_change_at
    {
      void operator()(
          data_manager<T>& a_data_manager,
          generic::Command_History& a_command_history,
          shared::handle<T> const& a_handle,
          typename flamingo::data_class_member_t<T,Index>::value_type const& a_value);
    };


    template <typename T>
    struct do_change_at<T,0>
    {
      void operator()(
          data_manager<T>& a_data_manager,
          generic::Command_History& a_command_history,
          shared::handle<T> const& a_handle,
          typename flamingo::data_class_member_t<T,0>::value_type const& a_value);
    };


    //---------------------------------------------------------------------------
    // shared::interface<T>
    //---------------------------------------------------------------------------
    // Supply an interface to send signals back to the Project. This allows us to
    // hide the signalling methods from the templates so we can have template
    // classes only expose things that need to be exposed.
    template <typename T>
    class interface
    {
    public:
      using object_type = T;
      using handle_type = handle<T>;

      template <std::size_t Index>
      using member_type = flamingo::data_class_member_t<object_type,Index>;

      // Special 6
      //============================================================
      interface(data_manager<object_type>& a_data_manager, generic::Command_History& a_command_history);

      // Interface
      //============================================================
      // Everything you can do with a data_class derived object.

      // Are there any objects in this Project?
      bool is_empty() const;
      bool not_empty() const;

      // How many objects are in this Project?
      std::size_t count() const;

      // Get the objects at this index
      handle_type get_at(std::size_t a_index) const;

      // Get all the objects
      std::vector<handle_type> get_all() const;

      // Get all the object names
      std::vector<QString> get_all_names() const;

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      handle_type make_default();

      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      handle_type make_emplace(object_type&& a_object);

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object.
      void add_default();

      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object.
      void add_emplace(object_type&& a_object);

      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. If this handle is invalid or already in the data then nothing happens.
      void add(handle_type const& a_handle);

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      void remove(handle_type const& a_handle);

      // Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
      template <std::size_t Index>
      void change_at(handle_type const& a_handle, typename member_type<Index>::value_type const& a_value)
      {
        do_change_at<T,Index>()(m_data_manager, m_command_history, a_handle, a_value);
      }

      // Request that the editor for this file be opened or switched to.
      void request_editor(handle_type const& a_handle);

      // Request that the focus change to this object.
      void request_focus(handle_type const& a_handle);

    private:
      // Data Members
      //============================================================
      data_manager<object_type>& m_data_manager;
      generic::Command_History& m_command_history;
    };
  }
}

#endif // SAK_SHARED_INTERFACE_HPP
