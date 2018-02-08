#include "test_project_signalbox_data.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/abstract_project_signalbox.hpp>
#include <sak/project_signalbox_data.hpp>
#include <sak/signal_source.hpp>

#include <iostream>
#include <cassert>
#include <type_traits>

namespace sak
{
  namespace
  {
    char const* do_source(Signal_Source a_source)
    {
      switch(a_source)
      {
        case Signal_Source::User: return "User";
        case Signal_Source::System: return "System";
        case Signal_Source::Undo: return "Undo";
        case Signal_Source::Redo: return "Redo";
        default: return "BAD SOURCE";
      }
    }

    template <typename T_Signalbox, typename T>
    class Do_Signals
    {
    public:
      using Type = T;
      using Signalbox_Type = T_Signalbox;
      using Typestring_Type = typename T::Typestring_Type;

      static void do_message(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<T> const& a_handle, std::size_t a_index, char const* a_funcname)
      {
        std::cout << "Project_Signalbox_Imp<T>::\"" << a_funcname
                  << "\": add=\"" << a_signalbox
                  << "\": source=\"" << do_source(a_source)
                  << "\" T=\"" << Typestring_Type::data()
                  <<"\" id=\"" << a_index
                  <<"\" index=\"" << a_handle.id()
                  << "\""
                  << std::endl;
      }

      static void do_message(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<T> const& a_handle, std::size_t a_i1, std::size_t a_i2, char const* a_funcname)
      {
        std::cout << "Project_Signalbox_Imp<T>::\"" << a_funcname
                  << "\": add=\"" << a_signalbox
                  << "\": source=\"" << do_source(a_source)
                  << "\" T=\"" << Typestring_Type::data()
                  <<"\" id=\"" << a_handle.id()
                  <<"\" i1=\"" << a_i1
                  <<"\" i1=\"" << a_i2
                  << "\""
                  << std::endl;
      }
      // When a handle has been added at a given index.
      static void added(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, "added()");
      }
      // When a handle has been removed from a given index.
      static void removed(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, "removed()");
      }
      // When a handle at a given index has been moved to another index.
      static void moved(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to)
      {
        do_message(a_signalbox, a_source, a_handle, a_from, a_to, "moved()");
      }
      // When a handle at a given index has its name changed.
      static void changed_name(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, "changed_name()");
      }
      // When a handle at a given index has all of its data changed.
      static void changed_data(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, "changed_data()");
      }
      // When a handle at a given index has its data changed in a specific place.
      static void changed_data_at(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index, std::size_t a_member)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, a_member, "changed_data_at()");
      }
      // When a handle at a given index requests its editor be opened/brought to the top.
      static void requests_editor(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, "requests_editor()");
      }
      // When a handle at a given index requests focus in the outliner.
      static void requests_outliner(Signalbox_Type* a_signalbox, Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index)
      {
        do_message(a_signalbox, a_source, a_handle, a_index, "requests_outliner()");
      }
    };

    //---------------------------------------------------------------------------
    // Project_Signalbox_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t Index = 0,
      std::size_t End = (flamingo::typelist_size_v<T_List> - 1)
    >
    class Project_Signalbox_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalbox_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t Index, std::size_t End, typename...Args>
    class Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index,End> :
        public Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index+1,End>
    {
      using Inh = Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,Index+1,End>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
      using Base = Abstract_Project_Signalbox_Imp<Args...>;
    public:
      // Special 6
      //============================================================
      Project_Signalbox_Part_Imp() = default;
      ~Project_Signalbox_Part_Imp() override = default;

      // Interface
      //============================================================
      // When a handle has been added at a given index.
      void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::added(this,a_source,a_handle,a_index);
      }
      // When a handle has been removed from a given index.
      void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::removed(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index has been moved to another index.
      void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to) override final
      {
        Do_Signals<Base,Type>::moved(this,a_source,a_handle,a_from,a_to);
      }
      // When a handle at a given index has its name changed.
      void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::changed_name(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index has all of its data changed.
      void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::changed_data(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index has its data changed in a specific place.
      void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index, std::size_t a_member) override final
      {
        Do_Signals<Base,Type>::changed_data_at(this,a_source,a_handle,a_index,a_member);
      }
      // When a handle at a given index requests its editor be opened/brought to the top.
      void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::requests_editor(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index requests focus in the outliner.
      void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::requests_outliner(this,a_source,a_handle,a_index);
      }

      using Inh::added;
      using Inh::removed;
      using Inh::moved;
      using Inh::changed_name;
      using Inh::changed_data;
      using Inh::changed_data_at;
      using Inh::requests_editor;
      using Inh::requests_outliner;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalbox_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For the last type in the list
    template <std::size_t End, typename...Args>
    class Project_Signalbox_Part_Imp<flamingo::typelist<Args...>,End,End> :
        public Abstract_Project_Signalbox_Imp<Args...>
    {
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
      using Base = Abstract_Project_Signalbox_Imp<Args...>;
    public:

      // Special 6
      //============================================================
      Project_Signalbox_Part_Imp() = default;
      ~Project_Signalbox_Part_Imp() override = default;

      // Interface
      //============================================================
      // When a handle has been added at a given index.
      void added(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::added(this,a_source,a_handle,a_index);
      }
      // When a handle has been removed from a given index.
      void removed(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::removed(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index has been moved to another index.
      void moved(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_from, std::size_t a_to) override final
      {
        Do_Signals<Base,Type>::moved(this,a_source,a_handle,a_from,a_to);
      }
      // When a handle at a given index has its name changed.
      void changed_name(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::changed_name(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index has all of its data changed.
      void changed_data(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::changed_data(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index has its data changed in a specific place.
      void changed_data_at(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index, std::size_t a_member) override final
      {
        Do_Signals<Base,Type>::changed_data_at(this,a_source,a_handle,a_index,a_member);
      }
      // When a handle at a given index requests its editor be opened/brought to the top.
      void requests_editor(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::requests_editor(this,a_source,a_handle,a_index);
      }
      // When a handle at a given index requests focus in the outliner.
      void requests_outliner(Signal_Source a_source, Handle<Type> const& a_handle, std::size_t a_index) override final
      {
        Do_Signals<Base,Type>::requests_outliner(this,a_source,a_handle,a_index);
      }
    };


    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Signalbox_Imp<T,Args...>
    //---------------------------------------------------------------------------
    // The top class of the template chain, where we gather and cleanup
    // everything. Also the requirement of at least one type stops bad template
    // instantiations.
    template <typename T, typename...Args>
    class Project_Signalbox_Imp :
        public Project_Signalbox_Part_Imp<flamingo::typelist<T,Args...>>
    {
      using Inh = Project_Signalbox_Part_Imp<flamingo::typelist<T,Args...>>;
    public:
      // Special 6
      //============================================================
      Project_Signalbox_Imp() = default;
      ~Project_Signalbox_Imp() override = default;

      // Interface
      //============================================================
      using Inh::added;
      using Inh::removed;
      using Inh::moved;
      using Inh::changed_name;
      using Inh::changed_data;
      using Inh::changed_data_at;
      using Inh::requests_editor;
      using Inh::requests_outliner;
    };

    using Project_Signalbox = Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;

    using Project_Signalbox_Data = Project_Signalbox_Data_Imp<File_Definition,Texture_Definition,Material_Definition>;

    template <typename T>
    void do_project_signalbox_test(Project_Signalbox_Data& a_project)
    {
      using namespace sak;

      std::cout << "-------------------------" << std::endl;

      Handle<T> l_handle{};
      std::size_t l_index{7};

      Signal_Source l_source{Signal_Source::System};

      a_project.added(l_source,l_handle,l_index);
      a_project.removed(l_source,l_handle,l_index);
      a_project.moved(l_source,l_handle,l_index,8);
      a_project.changed_name(l_source,l_handle,l_index);
      a_project.changed_data(l_source,l_handle,l_index);
      a_project.changed_data_at(l_source,l_handle,l_index,3);
      a_project.requests_editor(l_source,l_handle,l_index);
      a_project.requests_outliner(l_source,l_handle,l_index);


      std::cout << "-------------------------" << std::endl;
    }
  }

  class A{};
  class B{};
  class C{};
  class D{};
}


void sak::testing::test_project_signalbox_data()
{
  std::cout << "Testing sak::Project_Signalbox_Data" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  Project_Signalbox_Data l_psd{};

  Project_Signalbox l_ps1{};
  Project_Signalbox l_ps2{};
  Project_Signalbox l_ps3{};

  std::cout << "sizeof(void*)                       = " << sizeof(void*) <<  std::endl;
  std::cout << "sizeof(Abstract_Project_Signalbox_Imp<A>)       = " << sizeof(Abstract_Project_Signalbox_Imp<A>) <<  std::endl;
  std::cout << "sizeof(Abstract_Project_Signalbox_Imp<A,B>)     = " << sizeof(Abstract_Project_Signalbox_Imp<A,B>) <<  std::endl;
  std::cout << "sizeof(Abstract_Project_Signalbox_Imp<A,B,C>)   = " << sizeof(Abstract_Project_Signalbox_Imp<A,B,C>) <<  std::endl;
  std::cout << "sizeof(Abstract_Project_Signalbox_Imp<A,B,C,D>) = " << sizeof(Abstract_Project_Signalbox_Imp<A,B,C,D>) <<  std::endl;

  std::cout << "sizeof(Abstract_Project_Signalbox) = " << sizeof(Abstract_Project_Signalbox) <<  std::endl;
  std::cout << "sizeof(Project_Signalbox) = " << sizeof(Project_Signalbox) <<  std::endl;

  std::cout << "sizeof(Project_Signalbox_Data) = " << sizeof(Project_Signalbox_Data) <<  std::endl;

  std::cout << "add some signalboxes:" << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps1) <<  std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps2) << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps3) << std::endl;

  l_psd.add_signalbox(nullptr);
  l_psd.add_signalbox(&l_ps1);
  l_psd.add_signalbox(&l_ps2);
  l_psd.add_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);

  std::cout << "remove some signalboxes:" << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps2) << std::endl;
  std::cout << "address = " << dynamic_cast<Project_Signalbox*>(&l_ps3) << std::endl;

  l_psd.remove_signalbox(nullptr);
  l_psd.remove_signalbox(&l_ps2);
  l_psd.remove_signalbox(&l_ps3);

  do_project_signalbox_test<File_Definition>(l_psd);
  do_project_signalbox_test<Texture_Definition>(l_psd);
  do_project_signalbox_test<Material_Definition>(l_psd);

  std::cout << "==============================" << std::endl;
}
