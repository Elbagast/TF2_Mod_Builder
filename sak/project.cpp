#include "project.hpp"

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

#include "project_signalbox.hpp"
#include "exceptions/exception.hpp"
#include "shared/manager.hpp"
#include "shared/extended_manager.hpp"
#include "../generic/command_history.hpp"
#include "name_utilities.hpp"

#include <sak/shared/xml_traits.hpp>

//---------------------------------------------------------------------------
// Project
//---------------------------------------------------------------------------
namespace
{
    template <typename T, typename... Args>
    void emit_signals_for(std::vector<T*>& a_vector, void(T::*a_func)(Args...), Args&&... a_args)
    {
        for (auto l_item : a_vector)
        {
            l_item.(*a_func)(std::forward<Args>(a_args)...);
        }
    }
}
/*

lets say...
class Imp : public project::inbox
{
public:
  virtuals send to the relevent members
private:
  file::imp m_files;
  texture::imp m_textures
  etc
};

*/


namespace test
{
  class A {};
  class B {};
  class C {};

  template <typename T>
  using interface_traits = generic::No_Interface_Traits<generic::Uint32ID_Manager, T>;
  template <typename T>
  using extended_manager = generic::Extended_Manager<generic::Uint32ID_Manager, T, interface_traits<T>>;
  template <typename T>
  using extended_handle = generic::Extended_Handle<generic::Uint32ID_Manager, T, interface_traits<T>>;

  template <typename T>
  class outbox
  {
  public:
    virtual ~outbox() = default;
    virtual void do_thing(extended_handle<T> const& a_ehandle) = 0;
  };

  class full_outbox :
      public outbox<A>,
      public outbox<B>,
      public outbox<C>
  {
  public:
    ~full_outbox() override = default;
    void do_thing(extended_handle<A> const& a_ehandle) = 0;
    void do_thing(extended_handle<B> const& a_ehandle) = 0;
    void do_thing(extended_handle<C> const& a_ehandle) = 0;
  };

  template <typename T>
  class inbox : public outbox<T>
  {
  public:
    ~inbox() override = default;
    virtual extended_handle<T> make() = 0;
  };
/*
  class full_inbox :
      public inbox<A>,
      public inbox<B>,
      public inbox<C>
  {
  public:
    ~full_inbox() override = default;
    void do_thing(extended_handle<A> const& a_ehandle) override = 0;
    void do_thing(extended_handle<B> const& a_ehandle) override = 0;
    void do_thing(extended_handle<C> const& a_ehandle) override = 0;

    extended_handle<A> make() override = 0;
    extended_handle<B> make() override = 0;
    extended_handle<C> make() override = 0;
  };
*/
  template <typename T>
  class inbox_imp : public inbox<T>
  {
  public:
    void do_thing(extended_handle<T> const& a_ehandle) override {}
    extended_handle<T> make() override { return m_manager.emplace_data(T()); }
  private:
    extended_manager<T> m_manager;
  };

  class Imp : public full_outbox
  {
  public:
    ~Imp() override = default;
    void do_thing(extended_handle<A> const& a_ehandle) override { m_imp_a.do_thing(a_ehandle );}
    void do_thing(extended_handle<B> const& a_ehandle) override { m_imp_b.do_thing(a_ehandle );}
    void do_thing(extended_handle<C> const& a_ehandle) override { m_imp_c.do_thing(a_ehandle );}

    extended_handle<A> make_a() { return m_imp_a.make();}
    extended_handle<B> make_b() { return m_imp_b.make();}
    extended_handle<C> make_c() { return m_imp_c.make();}

    inbox<A>& get_inbox_a() { return m_imp_a; }
    inbox<B>& get_inbox_b() { return m_imp_b; }
    inbox<C>& get_inbox_c() { return m_imp_c; }

  private:
    inbox_imp<A> m_imp_a;
    inbox_imp<B> m_imp_b;
    inbox_imp<C> m_imp_c;
  };

  template <typename T>
  struct access_inbox
  {
    static inbox<T>& get_inbox(Imp& a_imp);
  };

  template <>
  struct access_inbox<A>
  {
    static inbox<A>& get_inbox(Imp& a_imp) { return a_imp.get_inbox_a(); }
  };
  template <>
  struct access_inbox<B>
  {
    static inbox<B>& get_inbox(Imp& a_imp) { return a_imp.get_inbox_b(); }
  };
  template <>
  struct access_inbox<C>
  {
    static inbox<C>& get_inbox(Imp& a_imp) { return a_imp.get_inbox_c(); }
  };


  Imp test_imp{};
}





// Pimpl Data
//============================================================

namespace sak
{
  template <typename T, typename... Args>
  void do_signals_for(std::vector<T*>& a_vector, void(T::*a_func)(Args...), Args&&... a_args)
  {
    for (auto l_item : a_vector)
    {
      l_item->*a_func(std::forward<Args>(a_args)...);
    }
  }

  class signal_dispatcher :
      public Project_Signalbox
  {
  public:
    ~signal_dispatcher() override = default;

    // When a File has its data changed(anything but the name), this is called.
    void changed(file::extended_handle const& a_ehandle) override final
    {
      qDebug() << "sak::shared::signal_dispatcher::changed "<< a_ehandle.id().get();
      for (auto l_item : m_dependents) l_item->changed(a_ehandle);
    }
    // When a File has its data changed in a specific place, this is called.
    void changed_at(file::extended_handle const& a_ehandle, std::size_t a_section) override final
    {
      qDebug() << "sak::shared::signal_dispatcher::changed_at "<< a_ehandle.id().get() << ", " << a_section;
      for (auto l_item : m_dependents) l_item->changed_at(a_ehandle, a_section);
    }
    // When a File has been added, this is called.
    void added(file::extended_handle const& a_ehandle) override final
    {
      qDebug() << "sak::shared::signal_dispatcher::added "<< a_ehandle.id().get();
      for (auto l_item : m_dependents) l_item->added(a_ehandle);
    }
    // When a File has been removed, this is called.
    void removed(file::extended_handle const& a_ehandle) override final
    {
      qDebug() << "sak::shared::signal_dispatcher::removed "<< a_ehandle.id().get();
      for (auto l_item : m_dependents) l_item->removed(a_ehandle);
    }
    // When a File requests an editor, this is called.
    void requests_editor(file::extended_handle const& a_ehandle) override final
    {
      qDebug() << "sak::shared::signal_dispatcher::requests_editor "<< a_ehandle.id().get();
      for (auto l_item : m_dependents) l_item->requests_editor(a_ehandle);
    }

    // When a File requests an editor, this is called.
    void requests_focus(file::extended_handle const& a_ehandle) override final
    {
      qDebug() << "sak::shared::signal_dispatcher::requests_focus "<< a_ehandle.id().get();
      for (auto l_item : m_dependents) l_item->requests_focus(a_ehandle);
    }

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Project_Signalbox* a_signalbox)
    {
      if (a_signalbox != nullptr
          //&& a_signalbox != m_data.get()
          && std::find(m_dependents.cbegin(), m_dependents.cend(), a_signalbox) == m_dependents.cend())
      {
        m_dependents.push_back(a_signalbox);
      }
    }

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Project_Signalbox* a_signalbox)
    {
      auto l_found = std::find(m_dependents.cbegin(), m_dependents.cend(), a_signalbox);
      if (l_found != m_dependents.cend())
      {
        m_dependents.erase(l_found);
      }
    }
  private:
    //Project_Signalbox* m_forbidden;
    std::vector<Project_Signalbox*> m_dependents;
  };



  namespace shared
  {
    //---------------------------------------------------------------------------
    // sak::shared::data_manager<T>
    //---------------------------------------------------------------------------
    // Splitting out the repeated backend management system for project...

    template <typename T>
    class data_manager :
        public shared::abstract::signalbox<T>
    {
    public:
      using object_type = T;
      using extended_manager_type = shared::extended_manager<object_type>;
      using extended_handle_type = shared::extended_handle<object_type>;
      using interface_traits_type = typename extended_manager_type::interface_traits_type;

      data_manager(interface_traits_type&& a_interface_traits, signal_dispatcher& a_dispatcher):
        m_dispatcher{a_dispatcher},
        m_emanager{std::move(a_interface_traits)},
        m_ehandles{}
      {}


      void changed(extended_handle_type const& a_ehandle) override final
      {
        qDebug() << "sak::shared::data_manager<T>::changed "<< a_ehandle.id().get();
        // This thing must exist
        assert(a_ehandle.is_valid());
        assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());

        m_dispatcher.changed(a_ehandle);
      }
      // When a File has its data changed in a specific place, this is called.
      void changed_at(extended_handle_type const& a_ehandle, std::size_t a_section) override final
      {
        qDebug() << "sak::shared::data_manager<T>::changed_at "<< a_ehandle.id().get() << ", " << a_section;
        // This thing must exist
        assert(a_ehandle.is_valid());
        assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());

        m_dispatcher.changed_at(a_ehandle,a_section);
      }
      // When a File has been added, this is called.
      void added(extended_handle_type const& a_ehandle) override final
      {
        qDebug() << "sak::shared::data_manager<T>::added "<< a_ehandle.id().get();
        // This thing must exist
        assert(a_ehandle.is_valid());
        // but not yet be part of the Project
        assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) == m_ehandles.cend());
        m_ehandles.push_back(a_ehandle);

        m_dispatcher.added(a_ehandle);
      }
      // When a File has been removed, this is called.
      void removed(extended_handle_type const& a_ehandle) override final
      {
        qDebug() << "sak::shared::data_manager<T>::removed "<< a_ehandle.id().get();
        assert(a_ehandle.is_valid());
        auto l_found = std::find(m_ehandles.begin(), m_ehandles.end(), a_ehandle);
        assert(l_found != m_ehandles.cend());
        assert(std::addressof(a_ehandle) != std::addressof(*l_found));

        // Copy the file::extended_handle locally. We don't know where it came from and have to propagate
        // the signal from here rather than who knows where to insure the signal reference stays
        // valid for all that need it.
        file::extended_handle l_ehandle = a_ehandle;

        // Now kill it, because if it's still in the project the signal will call back to find it
        // is still present.
        m_ehandles.erase(l_found);

        m_dispatcher.removed(l_ehandle);
      }
      // When a File requests an editor, this is called.
      void requests_editor(extended_handle_type const& a_ehandle) override final
      {
        qDebug() << "sak::shared::data_manager<T>::requests_editor "<< a_ehandle.id().get();
        // This thing must exist
        assert(a_ehandle.is_valid());
        assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());
        m_dispatcher.requests_editor(a_ehandle);
      }

      // When a File requests an editor, this is called.
      void requests_focus(extended_handle_type const& a_ehandle) override final
      {
        qDebug() << "sak::shared::data_manager<T>::requests_focus "<< a_ehandle.id().get();
        // This thing must exist
        assert(a_ehandle.is_valid());
        assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());
        m_dispatcher.requests_focus(a_ehandle);
      }

/*
      void reserve(std::size_t a_count)
      {
        m_ehandles.reserve(a_count);
      }*/

      // Are there any Files in this Project?
      bool empty() const
      {
        return m_ehandles.empty();
      }

      // How many any Files are in this Project?
      std::size_t count() const
      {
        return m_ehandles.size();
      }

      // Get the file at this index, asssuming the Files are alphabetically sorted by name
      extended_handle_type get_at(std::size_t a_index) const
      {
        return m_ehandles.at(a_index);
      }

      // Get all the Files alphabetically sorted by name
      std::vector<extended_handle_type> get_all() const
      {
        return m_ehandles;
      }


      // Get all the Files alphabetically sorted names
      std::vector<QString> get_all_names() const
      {
        std::vector<QString> l_result{};
        l_result.reserve(m_ehandles.size());
        for (auto const& l_ehandle : m_ehandles)
        {
          l_result.push_back(l_ehandle.cget().cat<0>().cget());
        }
        return l_result;
      }

      // You may create new Files using these two functions. Files created in this way
      // are part of the Project's data management system but have not yet been added to the
      // Project properly. That will only happen when the Project recieves a signal via its
      // Project_Signalbox that it should be addeed.

      // Make a new file using the supplied data. Project's data management system owns it but
      // it is not part of the Proeject.
      extended_handle_type make_emplace(object_type&& a_object)
      {
        return m_emanager.emplace_data(std::move(a_object));
      }

      // Make a new file using the default parameters. Project's data management system owns it
      // but it is not part of the Project.
      extended_handle_type make()
      {
        // uniqueify the name.
        QString l_name{u8"New " + QString::fromStdString(object_type::type())};
        uniqueify_name(l_name, get_all_names());
        file::object l_object{};
        l_object.at<0>().get() = l_name;
        return make_emplace(std::move(l_object));
      }
      /*
      void push_back(extended_handle_type const& a_ehandle)
      {
        m_ehandles.push_back(a_ehandle);
      }
      void push_back(extended_handle_type && a_ehandle)
      {
        m_ehandles.push_back(std::move(a_ehandle));
      }*/

      void to_xmlstream(QXmlStreamWriter& a_stream) const
      {
        // Start the Files block
        a_stream.writeStartElement(blockname());
        a_stream.writeTextElement(countname(), QString::number(count()));

        for (auto const& l_ehandle : m_ehandles)
        {
          sak::shared::xml_traits<object_type>::to_stream(a_stream, l_ehandle.cget());
        }

        // End the Files block
        a_stream.writeEndElement();
      }

      void from_xmlstream(QXmlStreamReader& a_stream)
      {
        // Read the Files
        if (a_stream.readNextStartElement() && a_stream.name().toString() == blockname())
        {
          //qDebug() << "Files:";
          int l_count {0};

          // <Count>
          if (a_stream.readNextStartElement() && a_stream.name().toString() == countname())
          {
            l_count = a_stream.readElementText().toInt();
            //qDebug() << "Count = " << l_count;

            // </Count>
            a_stream.readNext();
          }
          else
          {
            qDebug() << "Didn't find File Count";
            // file format error
          }

          m_ehandles.reserve(l_count);
          // read the files
          for (int l_index = 0; l_index != l_count; ++l_index)
          {
            object_type l_object{};
            sak::shared::xml_traits<object_type>::from_stream(a_stream, l_object);

            auto l_handle = make_emplace(std::move(l_object));
            m_ehandles.push_back(std::move(l_handle));
          }
          // </Files>
          a_stream.readNext();

        }
        else
        {
          // Bad file structure
          qDebug() << "Didn't find Filepath";
        }
      }



    private:
      static QString blockname() { return QString{ QString::fromStdString(object_type::type()) + u8"s" }; }
      static QString countname() { return QString{ u8"Count" }; }


      signal_dispatcher& m_dispatcher;
      extended_manager_type m_emanager;
      std::vector<extended_handle_type> m_ehandles;
    };
  }
}


namespace sak
{
  class Project::Implementation :
          public Project_Signalbox
  {
  public:
    QFileInfo m_filepath;
    QString m_message;
    QString m_data;

    signal_dispatcher m_dispatcher;
    shared::data_manager<file::object> m_file_manager;

    generic::Command_History m_command_history;

    Implementation(QString const& a_filepath, Project* a_owner):
      Project_Signalbox(),
      m_filepath{a_filepath},
      m_dispatcher{},
      m_file_manager{file::interface_traits(a_owner),m_dispatcher},
      m_command_history{}
    {
    }
    ~Implementation() = default;

    // Signalbox Interface
    //============================================================
    // Call these to call the signalbox functions in all dependents.

    // When a File has its data changed(anything but the name), this is called.
    void changed(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::changed " << a_file.id().get();
      m_file_manager.changed(a_file);
    }
    // When a File has its data changed in a specific place, this is called.
    void changed_at(file::extended_handle const& a_file, std::size_t a_section) override final
    {
      qDebug() << "\nProject::Implementation::changed_at "<< a_file.id().get() << ", " << a_section;
      m_file_manager.changed_at(a_file,a_section);
    }
    // When a File has been added, this is called.
    void added(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::added" << a_file.id().get();
      m_file_manager.added(a_file);
    }
    // When a File has been removed, this is called.
    void removed(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::removed" << a_file.id().get();
      m_file_manager.removed(a_file);
    }
    // When a File requests an editor, this is called.
    void requests_editor(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::requests_editor" << a_file.id().get();
      m_file_manager.requests_editor(a_file);
    }

    // When a File requests an editor, this is called.
    void requests_focus(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::requests_focus" << a_file.id().get();
      m_file_manager.requests_focus(a_file);
    }
  };

 /*

  class Project::Implementation :
          public Project_Signalbox
  {
  public:
    QFileInfo m_filepath;
    QString m_message;
    QString m_data;
    file::extended_manager m_file_manager;

    std::vector<file::extended_handle> m_files;

    std::vector<Project_Signalbox*> m_dependents;
    generic::Command_History m_command_history;

    Implementation(QString const& a_filepath, Project* a_owner):
      Project_Signalbox(),
      m_filepath{a_filepath},
      m_file_manager{file::interface_traits(a_owner)},
      m_files{},
      m_dependents{},
      m_command_history{}
    {
    }
    ~Implementation() = default;

    // Signalbox Interface
    //============================================================
    // Call these to call the signalbox functions in all dependents.

    // When a File has its data changed(anything but the name), this is called.
    void changed(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::change";
      // This thing must exist
      assert(a_file.is_valid());
      assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
      for (auto l_item : m_dependents)
      {
        l_item->changed(a_file);
      }
    }
    // When a File has its data changed in a specific place, this is called.
    void changed_at(file::extended_handle const& a_file, std::size_t a_section) override final
    {
      qDebug() << "\nProject::Implementation::changed_at " << a_section;
      // This thing must exist
      assert(a_file.is_valid());
      assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
      for (auto l_item : m_dependents)
      {
        l_item->changed_at(a_file, a_section);
      }
    }
    // When a File has been added, this is called.
    void added(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::added";
      // This thing must exist
      assert(a_file.is_valid());
      // but not yet be part of the Project
      assert(std::find(m_files.cbegin(), m_files.cend(), a_file) == m_files.cend());
      m_files.push_back(a_file);

      for (auto l_item : m_dependents)
      {
        l_item->added(a_file);
      }
    }
    // When a File has been removed, this is called.
    void removed(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::removed";
      assert(a_file.is_valid());
      auto l_found = std::find(m_files.begin(), m_files.end(), a_file);
      assert(l_found != m_files.cend());
      assert(std::addressof(a_file) != std::addressof(*l_found));

      // Copy the file::extended_handle locally. We don't know where it came from and have to propagate
      // the signal from here rather than who knows where to insure the signal reference stays
      // valid for all that need it.
      file::extended_handle l_file = a_file;
      // Now kill it, because if it's still in the project the signal will call back to find it
      // is still present.
      m_files.erase(l_found);

      // Now signal with the copy we made.
      for (auto l_item : m_dependents)
      {
        l_item->removed(l_file);
      }
    }
    // When a File requests an editor, this is called.
    void requests_editor(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::requests_editor";
      // This thing must exist
      assert(a_file.is_valid());
      assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
      for (auto l_item : m_dependents)
      {
        l_item->requests_editor(a_file);
      }
    }

    // When a File requests an editor, this is called.
    void requests_focus(file::extended_handle const& a_file) override final
    {
      qDebug() << "\nProject::Implementation::requests_focus";
      // This thing must exist
      assert(a_file.is_valid());
      assert(std::find(m_files.cbegin(), m_files.cend(), a_file) != m_files.cend());
      for (auto l_item : m_dependents)
      {
        l_item->requests_focus(a_file);
      }
    }
  };*/
}

// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::Project::Project(QString const& a_filepath):
    m_data{std::make_unique<Implementation>(a_filepath, this)}
{
    // If the directory does not exist it will fail.
    if(!imp().m_filepath.dir().exists())
    {
        // Failure exception for directory not existing.
        throw Directory_Missing_Error(imp().m_filepath.absoluteDir().absolutePath());
        //data().m_message = u8"Failure exception for directory not existing.";
    }
    /*
    if(!data().m_filepath.dir().isReadable())
    {
        // Failure exception for directory access.
        data().m_message = u8"Failure exception for directory access.";
    }
    */
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
/*
    this->add_file(File("dummy1", "poop"));
    this->add_file(File("dummy2", "pee"));
    this->add_file(File("dummy3", "pee"));
    this->add_file(File("dummy4", "pee"));

    auto l_temp = this->get_file_at(0);
    assert(l_temp.ref_count() == 2);
    {
        auto l_temp2 = l_temp;
        assert(l_temp.ref_count() == 3);
    }
    assert(l_temp.ref_count() == 2);
    assert(cimp().m_files.size() == 4);*/
}
sak::Project::~Project() = default;

sak::Project::Project(Project &&) = default;
sak::Project& sak::Project::operator=(Project &&) = default;

// Interface
//============================================================
// Save the current data to the file.
void sak::Project::save() const
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
void sak::Project::load()
{
  // Initialise new data
  auto l_data{std::make_unique<Implementation>(cimp().m_filepath.absoluteFilePath(),this)};

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

QString sak::Project::name() const
{
  return cimp().m_filepath.baseName();
}

QString sak::Project::location() const
{
  return cimp().m_filepath.absolutePath();
}

QString sak::Project::filepath() const
{
  return cimp().m_filepath.absoluteFilePath();
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project::add_signalbox(Project_Signalbox* a_signalbox)
{
  imp().m_dispatcher.add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project::remove_signalbox(Project_Signalbox* a_signalbox)
{
  imp().m_dispatcher.remove_signalbox(a_signalbox);
}

// Can we currently call undo?
bool sak::Project::can_undo() const
{
  return cimp().m_command_history.can_undo();
}

// Can we currently call redo?
bool sak::Project::can_redo() const
{
  return cimp().m_command_history.can_redo();
}

// How many times can undo() be called?
std::size_t sak::Project::undo_count() const
{
  return cimp().m_command_history.undo_count();
}

// How many times can redo() be called?
std::size_t sak::Project::redo_count() const
{
  return cimp().m_command_history.redo_count();
}

// Undo the last command issued.
void sak::Project::undo()
{
  imp().m_command_history.undo();
}

// Redo the last undone command in the command history
void sak::Project::redo()
{
  imp().m_command_history.redo();
}

// Commands get sent here.
void sak::Project::emplace_execute(std::unique_ptr<command_type>&& a_command)
{
  if (a_command != nullptr)
  {
    imp().m_command_history.add_execute(std::move(a_command));
  }
}

// Clear the undo/redo history.
void sak::Project::clear_history()
{
  imp().m_command_history.clear();
}

// File Interface
//============================================================

// Are there any Files in this Project?
bool sak::Project::has_files() const
{
  return !(cimp().m_file_manager.empty());
}

// How many any Files are in this Project?
std::size_t sak::Project::file_count() const
{
  return cimp().m_file_manager.count();
}

// Get the file at this index, asssuming the Files are alphabetically sorted by name
sak::file::extended_handle sak::Project::get_file_at(std::size_t a_index) const
{
  return cimp().m_file_manager.get_at(a_index);
}

// Get all the Files alphabetically sorted by name
std::vector<sak::file::extended_handle> sak::Project::get_all_files() const
{
  return cimp().m_file_manager.get_all();
}


// Get all the Files alphabetically sorted names
std::vector<QString> sak::Project::get_all_file_names() const
{
   return cimp().m_file_manager.get_all_names();
}

// You may create new Files using these two functions. Files created in this way
// are part of the Project's data management system but have not yet been added to the
// Project properly. That will only happen when the Project recieves a signal via its
// Project_Signalbox that it should be addeed.

// Make a new file using the supplied data. Project's data management system owns it but
// it is not part of the Proeject.
sak::file::extended_handle sak::Project::make_emplace_file(file::object&& a_file)
{
  return imp().m_file_manager.make_emplace(std::move(a_file));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
sak::file::extended_handle sak::Project::make_file()
{
  return imp().m_file_manager.make();
}

// To signal that something should be done to the project, you may access the signalbox
// for a specific type, then call the signals to make and propagate changes.
sak::Project_Signalbox* sak::Project::get_signalbox() const
{
  return m_data.get();
}


