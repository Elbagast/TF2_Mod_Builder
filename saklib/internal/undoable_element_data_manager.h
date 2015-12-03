#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H
#define SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H

#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER__FWD_H
#include "undoable_element_data_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_HANDLE__FWD_H
#include "undoable_element_data_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_MANAGER_H
#include "element_data_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_COMMAND_HISTORY_H
#include "command_history.h"
#endif

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#include "element_data_handle.h"
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Undoable_Element_Data_Manager
        //---------------------------------------------------------------------------

        class Undoable_Element_Data_Manager
        {
        public:
            // Typedefs
            //============================================================
            using handle_type = Element_Data_Manager::handle_type;

            // Interface
            //============================================================
            bool has_element(handle_type const& a_handle) const;
            Undoable_Element_Data_Handle make_element_handle(handle_type const& a_handle);
            Undoable_Element_Data_Handle make_element(Element_Data_Definition_Handle && a_definition_handle); // issues command?

            std::vector<handle_type> cget_all_handles() const;
            std::vector<Undoable_Element_Data_Handle> make_all_element_handles();

            // Will calling undo do anything?
            bool can_undo() const;
            // Will calling redo do anything?
            bool can_redo() const;

            // How many commands are stored?
            std::size_t cget_command_count() const;
            // Is the container empty?
            bool has_commands() const;

            // How many times can undo() be called?
            std::size_t cget_undo_count() const;
            // How many times can redo() be called?
            std::size_t cget_redo_count() const;

            //std::size_t cget_undo_count_maximum() const;

            // Call unexecute() in the current command and step back one in the history.
            bool undo();
            // Step forward one in the history and call execute() on that command.
            bool redo();

            // Clear all stored commands.
            void clear();

        private:
            Element_Data_Manager m_data_manager;
            Command_History m_command_history;
        };
    } // namespace internal
} // namespace saklib

#endif // SAKLIB_INTERNAL_UNDOABLE_ELEMENT_DATA_MANAGER_H
