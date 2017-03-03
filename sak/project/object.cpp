#include "object.hpp"

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <cassert>
#include <algorithm>
#include <iterator>

#include "signalbox.hpp"
#include "signal_dispatcher.hpp"
#include <sak/exceptions/exception.hpp>
#include <sak/shared/manager.hpp>
#include <sak/shared/extended_manager.hpp>
#include <sak/shared/data_manager.hpp>
#include <sak/shared/project_access.hpp>
#include <sak/shared/signalbox.hpp>
#include <generic/command_history.hpp>
#include <sak/shared/command.hpp>
#include <sak/name_utilities.hpp>

#include <sak/shared/xml_traits.hpp>



//---------------------------------------------------------------------------
// project::object
//---------------------------------------------------------------------------
// Pimpl Data
//============================================================
namespace sak
{
  namespace project
  {
    class object::impl :
            public abstract::signalbox
    {
    public:
      QFileInfo m_filepath;
      QString m_message;
      QString m_data;

      signal_dispatcher m_dispatcher;
      file::data_manager m_file_manager;

      generic::Command_History m_command_history;

      impl(QString const& a_filepath, object* a_owner):
        abstract::signalbox(),
        m_filepath{a_filepath},
        m_dispatcher{this},
        m_file_manager{*a_owner},
        m_command_history{}
      {
      }
      ~impl() override = default;

      // Signalbox Interface
      //============================================================
      // Call these to call the signalbox functions in all dependents.

      // When a File has its data changed(anything but the name), this is called.
      void changed(file::extended_handle const& a_file) override final
      {
        // For each signal we:
        // - give debug info
        qDebug() << "\nProject::Implementation::changed " << a_file.id().get();

        // - inform the appropriate data manager.
        m_file_manager.changed(a_file);

        // - tell the dispatcher to inform everything else.
        m_dispatcher.changed(a_file);
      }
      // When a File has its data changed in a specific place, this is called.
      void changed_at(file::extended_handle const& a_file, std::size_t a_section) override final
      {
        qDebug() << "\nProject::Implementation::changed_at "<< a_file.id().get() << ", " << a_section;
        m_file_manager.changed_at(a_file,a_section);
        m_dispatcher.changed_at(a_file,a_section);
      }
      // When a File has been added, this is called.
      void added(file::extended_handle const& a_file) override final
      {
        qDebug() << "\nProject::Implementation::added" << a_file.id().get();
        m_file_manager.added(a_file);
        m_dispatcher.added(a_file);
      }
      // When a File has been removed, this is called.
      void removed(file::extended_handle const& a_file) override final
      {
        qDebug() << "\nProject::Implementation::removed" << a_file.id().get();
        m_file_manager.removed(a_file);
        m_dispatcher.removed(a_file);
      }
      // When a File requests an editor, this is called.
      void requests_editor(file::extended_handle const& a_file) override final
      {
        qDebug() << "\nProject::Implementation::requests_editor" << a_file.id().get();
        m_file_manager.requests_editor(a_file);
        m_dispatcher.requests_editor(a_file);
      }

      // When a File requests an editor, this is called.
      void requests_focus(file::extended_handle const& a_file) override final
      {
        qDebug() << "\nProject::Implementation::requests_focus" << a_file.id().get();
        m_file_manager.requests_focus(a_file);
        m_dispatcher.requests_focus(a_file);
      }

      //---------------------------------------------------------------------------
      // sak::project::object::impl::do_set<T,Index>
      //---------------------------------------------------------------------------
      // This object has access to project::object private members and wraps the
      // command issuing of editing shared::object members.

      template <typename T, std::size_t Index>
      struct do_set
      {
        using object_type = T;
        using signalbox_type = shared::abstract::signalbox<object_type>;
        using extended_handle_type = shared::extended_handle<object_type>;
        using member_type = shared::mf::object_member_t<object_type, Index>;
        using value_type = typename member_type::value_type;

        void operator()(object& a_project, extended_handle_type const& a_ehandle, value_type const& a_value)
        {
          if (a_value == a_ehandle.cget().cat<Index>().cget())
          {
              return;
          }
          a_project.imp().m_command_history.add_execute(shared::make_command_assign<object_type, Index>(a_project.imp(), a_ehandle, a_value));
        }
      };

      //---------------------------------------------------------------------------
      // sak::project::object::impl::do_set<file::object,0>
      //---------------------------------------------------------------------------
      // For each name member we make a specialisation that looks up the appropriate
      // names and corrects the input if needed.

      template <typename T>
      struct do_set<T,0>
      {
        using object_type = T;
        using signalbox_type = shared::abstract::signalbox<object_type>;
        using extended_handle_type = shared::extended_handle<object_type>;
        using member_type = shared::mf::object_member_t<object_type, 0>;
        using value_type = typename member_type::value_type;

        void operator()(object& a_project, extended_handle_type const& a_ehandle, value_type const& a_value)
        {
          static_assert(std::is_same<value_type, QString>::value, "Member 0 has a type that is not QString...");

          if (a_value == a_ehandle.cget().cat<0>().cget())
          {
              return;
          }
          // We must make sure the name does not already exist among the other names.
          auto l_names = shared::project_access<object_type>::get_all_names(a_project);
          // Get rid of the name of this one, since it is going to change.
          auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), a_ehandle.cget().cat<0>().cget());
          l_names.erase(l_old_name_found);

          QString l_final_name{a_value};
          uniqueify_name(l_final_name, l_names);
          a_project.imp().m_command_history.add_execute(shared::make_command_assign<object_type, 0>(a_project.imp(), a_ehandle, l_final_name));
        }
      };


      //---------------------------------------------------------------------------
      // sak::project::object::impl::runtime_change_at<T>
      //---------------------------------------------------------------------------
      // The only way to hide the command calls without requiring explicit
      // template instantiations for each member is to have a means of changing the
      // runtime call into a static call.

      template <typename T>
      struct runtime_change_at
      {
        using object_type = T;
        using signalbox_type = shared::abstract::signalbox<object_type>;
        using extended_handle_type = shared::extended_handle<object_type>;
        using member_value_variant = typename object_type::member_value_variant;

        template < std::size_t Index, std::size_t End = object_type::size()>
        struct do_loop
        {
          using member_type = shared::mf::object_member_t<object_type, Index>;
          using value_type = typename member_type::value_type;

          void operator()(object& a_project, extended_handle_type const& a_ehandle, std::size_t a_section, member_value_variant a_variant)
          {
            if (a_section == Index)
            {
              // variant type supplied should be this type...
              assert(a_variant.type().hash_code() == typeid(value_type).hash_code());

              do_set<object_type, Index>()(a_project, a_ehandle, boost::get<value_type>(a_variant));
            }
            else
            {
              do_loop<Index+1,End>()(a_project, a_ehandle, a_section, a_variant);
            }
          }
        };

        template <std::size_t End>
        struct do_loop<End,End>
        {
          void operator()(object&, extended_handle_type const&, std::size_t, member_value_variant)
          {
          }
        };

        void operator()(object& a_project, extended_handle_type const& a_ehandle, std::size_t a_section, member_value_variant a_variant)
        {
          if (a_section < object_type::size())
          {
            do_loop<0>()(a_project, a_ehandle, a_section, a_variant);
          }
        }
      };

    }; // project::object::impl
  } // namespace project
} // namespace sak

// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::project::object::object(QString const& a_filepath):
    m_data{std::make_unique<impl>(a_filepath, this)}
{
    // If the directory does not exist it will fail.
    if(!imp().m_filepath.dir().exists())
    {
        // Failure exception for directory not existing.
        throw Directory_Missing_Error(imp().m_filepath.absoluteDir().absolutePath());
        //data().m_message = u8"Failure exception for directory not existing.";
    }
    // if the file exists, load it
    if(cimp().m_filepath.exists())
    {
        load();
    }
    // else make a new file using the empty initialsed data.
    else
    {
        save();
    }
}
sak::project::object::~object() = default;

sak::project::object::object(object &&) = default;
sak::project::object& sak::project::object::operator=(object &&) = default;

// Interface
//============================================================
// Save the current data to the file.
void sak::project::object::save() const
{
 QFile l_file{(cimp().m_filepath.absoluteFilePath())};
 if (l_file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
 {
   //qDebug() << "File opened";

   //QTextStream out_stream(&file);

   //qDebug() << static_cast<QFile*>(out_stream.device())->fileName();
   QXmlStreamWriter l_stream{&l_file};
   l_stream.setAutoFormatting(true);
   l_stream.writeStartDocument();

   // start the element that contains all the data
   l_stream.writeStartElement("Project");

   cimp().m_file_manager.to_xmlstream(l_stream);

   // end the element that contains all the data
   l_stream.writeEndElement();

   l_stream.writeEndDocument();

   l_file.close();
 }
 else
 {
    throw File_Write_Error(cimp().m_filepath.absoluteFilePath());
 }
}

// Get the data from the file and discard the current data.
void sak::project::object::load()
{
  // Initialise new data
  auto l_data{std::make_unique<impl>(cimp().m_filepath.absoluteFilePath(),this)};

  // Create a file object
  QFile l_file{cimp().m_filepath.absoluteFilePath()};

  // Attempt to open the file to read it
  if (l_file.exists() && l_file.open(QFile::ReadOnly | QFile::Text))
  {
    // make an xml stream
    QXmlStreamReader l_stream{&l_file};

    // <Project>
    if (l_stream.readNextStartElement() && l_stream.name().toString() == "Project")
    {
      l_data->m_file_manager.from_xmlstream(l_stream);

      // </Project>
      l_stream.readNext();
    }
    else
    {
        // Bad file structure
        qDebug() << "Didn't find Project";
    }

    l_file.close();

    // Replace the current data and consign it to oblivion. The data
    // is now that which has been loaded.
    std::swap(m_data, l_data);
  }
  else
  {
    // Failure exception for file loading.
    throw File_Read_Error(imp().m_filepath.absoluteFilePath());
  }
}

QString sak::project::object::name() const
{
  return cimp().m_filepath.baseName();
}

QString sak::project::object::location() const
{
  return cimp().m_filepath.absolutePath();
}

QString sak::project::object::filepath() const
{
  return cimp().m_filepath.absoluteFilePath();
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::project::object::add_signalbox(abstract::signalbox* a_signalbox)
{
  imp().m_dispatcher.add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::project::object::remove_signalbox(abstract::signalbox* a_signalbox)
{
  imp().m_dispatcher.remove_signalbox(a_signalbox);
}

// Can we currently call undo?
bool sak::project::object::can_undo() const
{
  return cimp().m_command_history.can_undo();
}

// Can we currently call redo?
bool sak::project::object::can_redo() const
{
  return cimp().m_command_history.can_redo();
}

// How many times can undo() be called?
std::size_t sak::project::object::undo_count() const
{
  return cimp().m_command_history.undo_count();
}

// How many times can redo() be called?
std::size_t sak::project::object::redo_count() const
{
  return cimp().m_command_history.redo_count();
}

// Undo the last command issued.
void sak::project::object::undo()
{
  imp().m_command_history.undo();
}

// Redo the last undone command in the command history
void sak::project::object::redo()
{
  imp().m_command_history.redo();
}

// Clear the undo/redo history.
void sak::project::object::clear_history()
{
  imp().m_command_history.clear();
}

// File Interface
//============================================================

// Are there any Files in this Project?
bool sak::project::object::has_files() const
{
  return !(cimp().m_file_manager.empty());
}

// How many any Files are in this Project?
std::size_t sak::project::object::file_count() const
{
  return cimp().m_file_manager.count();
}

// Get the file at this index, asssuming the Files are alphabetically sorted by name
sak::file::extended_handle sak::project::object::get_file_at(std::size_t a_index) const
{
  return cimp().m_file_manager.get_at(a_index);
}

// Get all the Files alphabetically sorted by name
std::vector<sak::file::extended_handle> sak::project::object::get_all_files() const
{
  return cimp().m_file_manager.get_all();
}


// Get all the Files alphabetically sorted names
std::vector<QString> sak::project::object::get_all_file_names() const
{
   return cimp().m_file_manager.get_all_names();
}

// You may create new Files using these two functions. Files created in this way
// are part of the Project's data management system but have not yet been added to the
// Project properly. That will only happen when the Project recieves a signal via its
// Project_Signalbox that it should be addeed.

// Make a new file using the supplied data. Project's data management system owns it but
// it is not part of the Proeject.
sak::file::extended_handle sak::project::object::make_emplace_file(file::object&& a_file)
{
  return imp().m_file_manager.make_emplace(std::move(a_file));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
sak::file::extended_handle sak::project::object::make_file()
{
  return imp().m_file_manager.make();
}

// Create a new default file and add it.
void sak::project::object::file_add_new()
{
  imp().m_command_history.add_execute(shared::make_command_added(imp(), imp().m_file_manager.make()));
}

// Add a new file using the supplied data.
void sak::project::object::file_add_emplace(file::object&& a_file)
{
  imp().m_command_history.add_execute(shared::make_command_added(imp(), imp().m_file_manager.make_emplace(std::move(a_file))));
}

// Add a new file using the supplied handle. If this handle is invalid or already in the data
// then nothing happens.
void sak::project::object::file_add(file::extended_handle const& a_ehandle)
{
  if (a_ehandle.is_valid() && !(cimp().m_file_manager.has_handle(a_ehandle)))
  {
    imp().m_command_history.add_execute(shared::make_command_added(imp(), a_ehandle));
  }
}

// Remove this file. It is removed from the file list and the data of anything that references it.
// Data is not deleted until the last reference is deleted.
void sak::project::object::file_remove(file::extended_handle const& a_ehandle)
{
  if (a_ehandle.is_valid() && cimp().m_file_manager.has_handle(a_ehandle))
  {
    imp().m_command_history.add_execute(shared::make_command_removed(imp(), a_ehandle));
  }
}

// Change a file's member value.
void sak::project::object::file_change_at(file::extended_handle const& a_ehandle, std::size_t a_section, typename file::object::member_value_variant const& a_variant)
{
  // here we have to turn a runtime command into a compiletime one...or switch the object type to runtime so we can use that interface
  if (a_ehandle.is_valid() && cimp().m_file_manager.has_handle(a_ehandle))
  {
    impl::runtime_change_at<file::object>()(*this, a_ehandle, a_section, a_variant);
  }
}

// Request that the focus change to this file.
void sak::project::object::file_request_focus(file::extended_handle const& a_ehandle)
{
  if (a_ehandle.is_valid() && cimp().m_file_manager.has_handle(a_ehandle))
  {
    imp().requests_focus(a_ehandle);
  }
}

// Request that the editor for this file be opened or switched to.
void sak::project::object::file_request_editor(file::extended_handle const& a_ehandle)
{
  if (a_ehandle.is_valid() && cimp().m_file_manager.has_handle(a_ehandle))
  {
    imp().requests_editor(a_ehandle);
  }
}


