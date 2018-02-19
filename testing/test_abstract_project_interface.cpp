#include "test_abstract_project_interface.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/abstract_project_interface.hpp>
#include <sak/signal_source.hpp>

#include <iostream>
#include <cassert>

#include <QString>

#include <flamingo/typelist.hpp>

/*
Virtual inheritance creates a massive overhead, and this class is to be used in
only one place. So how do we remove it?

if
A has 3 members
B has 1 members
C has 2 members

Top<A,B,C>
  - cannot use types with no members
  - rest of the interface
  - using part interface
  - using member interface
  Part<List<A,B,C>,0,2,0,2> - List index LI, List size-1 LL, member index MI, member count-1 ML
    - A<0> interface
    - using part interface
    - using member interface
    Part<List<A,B,C>,0,2,1,2>
      - A<1> interface
      - using part interface
      - using member interface
      Part<List<A,B,C>,0,2,2,2> - MI==ML
        - A<2> interface - last one
        - A part interface
        - using part interface
        - using member interface
        Part<List<A,B,C>,1,2,0,0> - MI==ML
          - B<0> interface - last one
          - B part interface
          - using part interface
          - using member interface
          Part<List<A,B,C>,2,2,0,1>
            - C<0> interface
            - using part interface
            - using member interface
            Part<List<A,B,C>,2,2,1,1> - LI==LL AND MI=ML
              - C<1> interface - last one
              - C part interface - last one
*/

namespace sak
{
  template <typename T>
  class Inherit :
      public T
  {
  protected:
    using Inherited_Type = T;
  public:
    using Inherited_Type::Inherited_Type;
    ~Inherit() = default;
  };


  template
  <
      typename T_List,
      std::size_t LI = 0,
      std::size_t LL = (flamingo::typelist_size_v<T_List> - 1),
      std::size_t MI = 0,
      std::size_t ML = (Data_Size_v<Data<flamingo::typelist_at_t<T_List,0>>> - 1)
  >
  class Part;

  // for any member that isn't at the end of a type
  template <std::size_t LI, std::size_t LL, std::size_t MI, std::size_t ML, typename...Args>
  class Part<flamingo::typelist<Args...>,LI,LL,MI,ML> :
      public Part<flamingo::typelist<Args...>,LI,LL,MI+1,ML>
  {
    using Inh = Part<flamingo::typelist<Args...>,LI,LL,MI+1,ML>;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    static constexpr std::size_t index = MI;
  public:
    Part()
    {
      std::cout << "(1)Part<List," << LI << "," << LL << "," << MI << "," << ML << ">::Part" << std::endl;
    }
    ~Part() override = default;

    virtual void member(Index_Tag<index>&&, Handle<Type> const&)
    {
      std::cout << "(1)Part<List," << LI << "," << LL << "," << MI << "," << ML << ">::member" << std::endl;
    }

    using Inh::member;
    using Inh::other;
  };

  //  the last member of a type not at the end
  template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
  class Part<flamingo::typelist<Args...>,LI,LL,ML,ML> :
      public Part
      <
        flamingo::typelist<Args...>,
        LI+1,
        LL,
        0,
        (Data_Size_v<Data<flamingo::typelist_at_t<flamingo::typelist<Args...>,LI+1>>> - 1) // last member of next
      >
  {
    using Inh = Part
    <
      flamingo::typelist<Args...>,
      LI+1,
      LL,
      0,
      (Data_Size_v<Data<flamingo::typelist_at_t<flamingo::typelist<Args...>,LI+1>>> - 1) // last member of next
    >;

    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    static constexpr std::size_t index = ML;
  public:
    Part()
    {
      std::cout << "(2)Part<List," << LI << "," << LL << "," << ML << "," << ML << ">::Part" << std::endl;
    }
    ~Part() override = default;

    virtual void member(Index_Tag<index>&&, Handle<Type> const&)
    {
      std::cout << "(2)Part<List," << LI << "," << LL << "," << ML << "," << ML << ">::member" << std::endl;
    }
    virtual void other(Handle<Type> const&)
    {
      std::cout << "(2)Part<List," << LI << "," <<LL << "," << ML << "," << ML << ">::other" << std::endl;
    }

    using Inh::member;
    using Inh::other;
  };

  // the last member of the last type
  template <std::size_t LL, std::size_t ML, typename...Args>
  class Part<flamingo::typelist<Args...>,LL,LL,ML,ML>
  {
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LL>;
    static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    static constexpr std::size_t index = ML;
  public:
    Part()
    {
      std::cout << "(3)Part<List," << LL << "," << LL << "," << ML << "," << ML << ">::Part" << std::endl;
    }
    virtual ~Part() = default;
    virtual void member(Index_Tag<index>&&, Handle<Type> const&)
    {
      std::cout << "(3)Part<List," << LL << "," << LL << "," << ML << "," << ML << ">::member" << std::endl;
    }
    virtual void other(Handle<Type> const&)
    {
      std::cout << "(3)Part<List," << LL << "," << LL << "," << ML << "," << ML << ">::other" << std::endl;
    }
  };


  template <typename T, typename...Args>
  class Top :
      protected Part<flamingo::typelist<T,Args...>>
  {
    using Inh = Part<flamingo::typelist<T,Args...>>;
  public:
    ~Top() override = default;

    using Inh::member;
    using Inh::other;
  };
  // And thus proof of concept of non-virtual inheritance. Too bad about the repeat function declarations.
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  // alternative architecture:

  namespace test
  {
    enum class Member_Type
    {
      Simple,
      Alternative
    };

    template
    <
        typename T_List,
        std::size_t LI = 0,
        std::size_t MI = 0,
        std::size_t LE = (flamingo::typelist_size_v<T_List> - 1),
        std::size_t ME = (Data_Size_v<Data<flamingo::typelist_at_t<T_List,LI>>>)
        //,Member_Type MT = [determine member type of the class member]
    >
    class Member;


    // for any member that isn't at the end of a type
    template <std::size_t LI, std::size_t MI, std::size_t LE, std::size_t ME, typename...Args>
    class Member<flamingo::typelist<Args...>,LI,MI,LE,ME> :
        protected Member<flamingo::typelist<Args...>,LI,MI+1,LE,ME>
    {
      using Inh = Member<flamingo::typelist<Args...>,LI,MI+1,LE,ME>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

      static constexpr std::size_t index = MI;
    public:
      Member()
      {
        std::cout << "(1)Member<List," << LI << "," << MI << "," << LE << "," << ME << ">::Member" << std::endl;
      }
      ~Member() override = default;

      virtual void func(Tag<Type>&&,Index_Tag<index>&&)//Index_Tag<index>&&, Handle<Type> const&)
      {
        std::cout << "(1)Member<List," << LI << "," << MI << "," << LE << "," << ME << ">::func" << std::endl;
      }

    };


    // for any member that is at the end of a type
    template <std::size_t LI, std::size_t LE, std::size_t ME, typename...Args>
    class Member<flamingo::typelist<Args...>,LI,ME,LE,ME> :
        protected Member<flamingo::typelist<Args...>,LI+1>
    {
      using Inh = Member<flamingo::typelist<Args...>,LI+1>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Member()
      {
        std::cout << "(2)Member<List," << LI << "," << ME << "," << LE << "," << ME << ">::Member" << std::endl;
      }
      ~Member() override = default;

    };

    // for any member that is the end of the last type
    template <std::size_t LE, std::size_t ME, typename...Args>
    class Member<flamingo::typelist<Args...>,LE,ME,LE,ME>
    {
      //static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Member()
      {
        std::cout << "(3)Member<List," << LE << "," << ME << "," << LE << "," << ME << ">::Member" << std::endl;
      }
      virtual ~Member() = default;
    };


    template
    <
        typename T_List,
        std::size_t LI = 0,
        std::size_t LE = (flamingo::typelist_size_v<T_List>)
    >
    class Section;

    // for any type that isn't at the end of the list
    template <std::size_t LI, std::size_t LE, typename...Args>
    class Section<flamingo::typelist<Args...>,LI,LE> :
        protected Section<flamingo::typelist<Args...>,LI+1,LE>
    {
      using Inh = Section<flamingo::typelist<Args...>,LI+1,LE>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Section()
      {
        std::cout << "(1)Section<List," << LI << "," << LE << ">::Section" << std::endl;
      }
      ~Section() override = default;

      virtual void other(Tag<Type>&&)
      {
        std::cout << "(1)Section<List," << LI << "," << LE << ">::other" << std::endl;
      }

    };

    // for the type at the end of the list, just continue the inheritance chain
    template <std::size_t LE, typename...Args>
    class Section<flamingo::typelist<Args...>,LE,LE> :
        protected Member<flamingo::typelist<Args...>>
    {
      using Inh = Member<flamingo::typelist<Args...>>;

      //using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      //static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Section()
      {
        std::cout << "(2)Section<List," << LE << "," << LE << ">::Section" << std::endl;
      }
      ~Section() override = default;

    };

    template <typename T, typename...Args>
    class Top :
        protected Section<flamingo::typelist<T,Args...>>
    {
      using Inh = Section<flamingo::typelist<T,Args...>>;


      template <typename T1>
      using Section_Type = Section<flamingo::typelist<T,Args...>,flamingo::typelist_find_v<flamingo::typelist<T,Args...>,T1>>;

      template <typename T1, std::size_t I>
      using Member_Type = Member<flamingo::typelist<T,Args...>,flamingo::typelist_find_v<flamingo::typelist<T,Args...>,T1>,I>;
    public:
      Top()
      {
        std::cout << "Top<T,Args...>::Top" << std::endl;
      }
      ~Top() override = default;

      virtual void thing()
      {
        std::cout << "Top<T,Args...>::thing" << std::endl;
      }


      template <typename T1>
      Section_Type<T1>* get_section() { return this; }

      template <typename T1, std::size_t I>
      Member_Type<T1,I>* get_member() { return this; }

    };

    template
    <
        typename T_List,
        std::size_t LI = 0,
        std::size_t MI = 0,
        std::size_t LE = (flamingo::typelist_size_v<T_List> - 1),
        std::size_t ME = (Data_Size_v<Data<flamingo::typelist_at_t<T_List,LI>>>)
        //,Member_Type MT = [determine member type of the class member]
    >
    class Member_Imp;


    // for any member that isn't at the end of a type
    template <std::size_t LI, std::size_t MI, std::size_t LE, std::size_t ME, typename...Args>
    class Member_Imp<flamingo::typelist<Args...>,LI,MI,LE,ME> :
        public Member_Imp<flamingo::typelist<Args...>,LI,MI+1,LE,ME>
    {
      using Inh = Member_Imp<flamingo::typelist<Args...>,LI,MI+1,LE,ME>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

      static constexpr std::size_t index = MI;
    public:
      Member_Imp()
      {
        std::cout << "(1)Member_Imp<List," << LI << "," << MI << "," << LE << "," << ME << ">::Member_Imp" << std::endl;
      }
      ~Member_Imp() override = default;

      void func(Tag<Type>&&,Index_Tag<index>&&) override
      {
        std::cout << "(1)Member_Imp<List," << LI << "," << MI << "," << LE << "," << ME << ">::func" << std::endl;
      }

    };


    // for any member that is at the end of a type
    template <std::size_t LI, std::size_t LE, std::size_t ME, typename...Args>
    class Member_Imp<flamingo::typelist<Args...>,LI,ME,LE,ME> :
        public Member_Imp<flamingo::typelist<Args...>,LI+1>
    {
      using Inh = Member_Imp<flamingo::typelist<Args...>,LI+1>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Member_Imp()
      {
        std::cout << "(2)Member_Imp<List," << LI << "," << ME << "," << LE << "," << ME << ">::Member_Imp" << std::endl;
      }
      ~Member_Imp() override = default;

    };

    // for any member that is the end of the last type
    template <std::size_t LE, std::size_t ME, typename...Args>
    class Member_Imp<flamingo::typelist<Args...>,LE,ME,LE,ME> :
        public Top<Args...>
    {
      //static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Member_Imp()
      {
        std::cout << "(3)Member_Imp<List," << LE << "," << ME << "," << LE << "," << ME << ">::Member_Imp" << std::endl;
      }
      ~Member_Imp() override = default;
    };


    template
    <
        typename T_List,
        std::size_t LI = 0,
        std::size_t LE = (flamingo::typelist_size_v<T_List>)
    >
    class Section_Imp;

    // for any type that isn't at the end of the list
    template <std::size_t LI, std::size_t LE, typename...Args>
    class Section_Imp<flamingo::typelist<Args...>,LI,LE> :
        public Section_Imp<flamingo::typelist<Args...>,LI+1,LE>
    {
      using Inh = Section_Imp<flamingo::typelist<Args...>,LI+1,LE>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Section_Imp()
      {
        std::cout << "(1)Section_Imp<List," << LI << "," << LE << ">::Section_Imp" << std::endl;
      }
      ~Section_Imp() override = default;

      void other(Tag<Type>&&) override
      {
        std::cout << "(1)Section_Imp<List," << LI << "," << LE << ">::other" << std::endl;
      }

    };

    // for the type at the end of the list, just continue the inheritance chain
    template <std::size_t LE, typename...Args>
    class Section_Imp<flamingo::typelist<Args...>,LE,LE> :
        public Member_Imp<flamingo::typelist<Args...>>
    {
      using Inh = Member_Imp<flamingo::typelist<Args...>>;

      //using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      //static_assert(Data_Size_v<Data<Type>> != 0 ,"can't have no members.");

    public:
      Section_Imp()
      {
        std::cout << "(2)Section_Imp<List," << LE << "," << LE << ">::Section_Imp" << std::endl;
      }
      ~Section_Imp() override = default;

    };

    template <typename T, typename...Args>
    class Top_Imp :
        public Section_Imp<flamingo::typelist<T,Args...>>
    {
      using Inh = Section_Imp<flamingo::typelist<T,Args...>>;

    public:
      Top_Imp()
      {
        std::cout << "Top_Imp<T,Args...>::Top" << std::endl;
      }
      ~Top_Imp() override = default;

      void thing() override
      {
        std::cout << "Top_Imp<T,Args...>::thing" << std::endl;
      }


    };

  }


/*

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Project_Interface_Part_Imp<List,LI,LL,MI,ML>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t T_List_Index = 0,
      std::size_t T_List_Last = (flamingo::typelist_size_v<T_List> - 1 ),
      std::size_t T_Member_Index = 0,
      std::size_t T_Member_Last = (Data_Size_v<Data<flamingo::typelist_at_t<T_List,T_List_Index>>> - 1 )
    >
    class Project_Interface_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Interface_Part_Imp<List,LI,LL,MI,ML>
    //---------------------------------------------------------------------------
    // For a member that isn't the last in a type that isn't the last in the list.
    template <std::size_t LI, std::size_t LL, std::size_t MI, std::size_t ML, typename...Args>
    class Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI,ML> :
        public Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI+1,ML>
    {
      using Inh = Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,MI+1,ML>;
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;

      static constexpr std::size_t const list_index = LI;
      static constexpr std::size_t const list_last = LL;
      static constexpr std::size_t const member_index = MI;
      static constexpr std::size_t const member_last = ML;

      using Index_Tag_Type = Index_Tag<member_index>;
      using Member_Value_Type = Data_Member_Value_Type<member_index,Data_Type>;

      static_assert(Data_Size_v<Data_Type> != 0, "Cannot use data with no members.");
      static_assert(Data_Size_v<Data_Type> == (ML+1), "Bad last index.");
    public:

      // Special 6
      //============================================================
      Project_Interface_Part_Imp() = default;
      ~Project_Interface_Part_Imp() override = default;

      // Interface
      //============================================================

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::change_data_at()" << std::endl;
        return true;
      }

      using Inh::is_empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_named;
      using Inh::get_handle_at;
      using Inh::get_handle_named;
      using Inh::get_handles;
      using Inh::get_names;
      using Inh::make_default;
      using Inh::make_emplace;
      using Inh::add_default;
      using Inh::add_emplace;
      using Inh::add;
      using Inh::remove;
      using Inh::change_name;
      using Inh::change_data_at;
      using Inh::request_editor;
      using Inh::request_outliner;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Interface_Part_Imp<List,LI,LL,ML,ML>
    //---------------------------------------------------------------------------
    // For the last member in a type that isn't the last in the list.
    template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
    class Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI,LL,ML,ML> :
        public Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI+1>
        // The rest of the parameters should default correctly
    {
      using Inh = Project_Interface_Part_Imp<flamingo::typelist<Args...>,LI+1>;
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

      static constexpr std::size_t const list_index = LI;
      static constexpr std::size_t const list_last = LL;
      static constexpr std::size_t const member_index = ML;
      static constexpr std::size_t const member_last = ML;

      using Index_Tag_Type = Index_Tag<member_index>;
      using Member_Value_Type = Data_Member_Value_Type<member_index,Data_Type>;

      static_assert(Data_Size_v<Data_Type> != 0, "Cannot use data with no members.");
      static_assert(Data_Size_v<Data_Type> == (ML+1), "Bad last index.");
    public:

      // Special 6
      //============================================================
      Project_Interface_Part_Imp() = default;
      ~Project_Interface_Part_Imp() override = default;

      // Interface
      //============================================================


      // Are there any objects in this Project?
      bool is_empty(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::is_empty()" << std::endl;
        return true;
      }
      // How many objects are in this Project?
      std::size_t count(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::count()" << std::endl;
        return 0;
      }

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::save()" << std::endl;
        return true;
      }
      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::has_handle_named()" << std::endl;
        return true;
      }

      // Get the handle at this index. If the index is invalid a null handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_handle_at()" << std::endl;
        return Handle_Type{};
      }
      // Get the handle with this name. If the name is invalid a null handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_handle_named()" << std::endl;
        return Handle_Type{};
      }

      // Get all the handles in data order
      std::vector<Handle_Type> get_handles(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_handles()" << std::endl;
        return std::vector<Handle_Type>{};
      }
      // Get all the handles names in data order
      std::vector<QString> get_names(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_names()" << std::endl;
        return std::vector<QString>{};
      }

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      Handle_Type make_default(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::make_default()" << std::endl;
        return Handle_Type{};
      }
      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      Handle_Type make_emplace(Data_Type&& a_data) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::make_emplace()" << std::endl;
        return Handle_Type{};
      }

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object. Return true if the operation resulted in an undoable command.
      bool add_default(Tag_Type&&, Signal_Source a_source) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::add_default()" << std::endl;
        return true;
      }
      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
      bool add_emplace(Signal_Source a_source, Data_Type&& a_data) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::add_emplace()" << std::endl;
        return true;
      }
      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      bool add(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::add()" << std::endl;
        return true;
      }
      // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
      // until the last handle for it is deleted.
      bool remove(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::remove()" << std::endl;
        return true;
      }

      // Undoable change a handles name. Returns true if this call results in a change being made.
      // If the name supplied is already in use then the supplied name will be altered.
      bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::change_name()" << std::endl;
        return true;
      }

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::change_data_at()" << std::endl;
        return true;
      }

      // Request that the editor for this file be opened or switched to.
      void request_editor(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::request_editor()" << std::endl;
      }
      // Request that the focus change to this object.
      void request_outliner(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::request_outliner()" << std::endl;
      }

      using Inh::is_empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_named;
      using Inh::get_handle_at;
      using Inh::get_handle_named;
      using Inh::get_handles;
      using Inh::get_names;
      using Inh::make_default;
      using Inh::make_emplace;
      using Inh::add_default;
      using Inh::add_emplace;
      using Inh::add;
      using Inh::remove;
      using Inh::change_name;
      using Inh::change_data_at;
      using Inh::request_editor;
      using Inh::request_outliner;
    };
    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Project_Interface_Part_Imp<List,LL,LL,ML,ML>
    //---------------------------------------------------------------------------
    // For the last member in the last type.
    template <std::size_t LL, std::size_t ML, typename...Args>
    class Project_Interface_Part_Imp<flamingo::typelist<Args...>,LL,LL,ML,ML> :
        public Abstract_Project_Interface_Imp<Args...>
    {
      using Inh = Abstract_Project_Interface_Imp<Args...>;
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LL>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

      static constexpr std::size_t const list_index = LL;
      static constexpr std::size_t const list_last = LL;
      static constexpr std::size_t const member_index = ML;
      static constexpr std::size_t const member_last = ML;

      using Index_Tag_Type = Index_Tag<member_index>;
      using Member_Value_Type = Data_Member_Value_Type<member_index,Data_Type>;

      static_assert(Data_Size_v<Data_Type> != 0, "Cannot use data with no members.");
      static_assert(Data_Size_v<Data_Type> == (ML+1), "Bad last index.");
    public:

      // Special 6
      //============================================================
      Project_Interface_Part_Imp() = default;
      ~Project_Interface_Part_Imp() override = default;

      // Interface
      //============================================================

      // Are there any objects in this Project?
      bool is_empty(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::is_empty()" << std::endl;
        return true;
      }
      // How many objects are in this Project?
      std::size_t count(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::count()" << std::endl;
        return 0;
      }

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::save()" << std::endl;
        return true;
      }
      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::has_handle_named()" << std::endl;
        return true;
      }

      // Get the handle at this index. If the index is invalid a null handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_handle_at()" << std::endl;
        return Handle_Type{};
      }
      // Get the handle with this name. If the name is invalid a null handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_handle_named()" << std::endl;
        return Handle_Type{};
      }

      // Get all the handles in data order
      std::vector<Handle_Type> get_handles(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_handles()" << std::endl;
        return std::vector<Handle_Type>{};
      }
      // Get all the handles names in data order
      std::vector<QString> get_names(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::get_names()" << std::endl;
        return std::vector<QString>{};
      }

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      Handle_Type make_default(Tag_Type&&) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::make_default()" << std::endl;
        return Handle_Type{};
      }
      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      Handle_Type make_emplace(Data_Type&& a_data) const override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::make_emplace()" << std::endl;
        return Handle_Type{};
      }

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object. Return true if the operation resulted in an undoable command.
      bool add_default(Tag_Type&&, Signal_Source a_source) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::add_default()" << std::endl;
        return true;
      }
      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object. Return true if the operationn resulted in an undoable command.
      bool add_emplace(Signal_Source a_source, Data_Type&& a_data) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::add_emplace()" << std::endl;
        return true;
      }
      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false.
      bool add(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::add()" << std::endl;
        return true;
      }
      // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
      // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
      // until the last handle for it is deleted.
      bool remove(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::remove()" << std::endl;
        return true;
      }

      // Undoable change a handles name. Returns true if this call results in a change being made.
      // If the name supplied is already in use then the supplied name will be altered.
      bool change_name(Signal_Source a_source, Handle_Type const& a_handle, QString const& a_name) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::change_name()" << std::endl;
        return true;
      }

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_data_at(Index_Tag_Type&&, Signal_Source a_source, Handle_Type const& a_handle, Member_Value_Type const& a_value) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::change_data_at()" << std::endl;
        return true;
      }

      // Request that the editor for this file be opened or switched to.
      void request_editor(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::request_editor()" << std::endl;
      }
      // Request that the focus change to this object.
      void request_outliner(Signal_Source a_source, Handle_Type const& a_handle) override final
      {
        std::cout << "Project_Interface_Imp<List,"<<list_index<<","<<list_last<<","<<member_index<<","<<member_last
                  <<">::request_outliner()" << std::endl;
      }


      using Inh::is_empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_named;
      using Inh::get_handle_at;
      using Inh::get_handle_named;
      using Inh::get_handles;
      using Inh::get_names;
      using Inh::make_default;
      using Inh::make_emplace;
      using Inh::add_default;
      using Inh::add_emplace;
      using Inh::add;
      using Inh::remove;
      using Inh::change_name;
      using Inh::change_data_at;
      using Inh::request_editor;
      using Inh::request_outliner;
    };

  } // namespace internal

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  template <typename T, typename...Args>
  class Project_Interface_Imp :
      public internal::Project_Interface_Part_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = internal::Project_Interface_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Typedefs
    //============================================================
    using Typelist_Type = flamingo::typelist<T,Args...>;
    using Signalbox_Type = Abstract_Project_Signalbox_Imp<T,Args...>;

    // Special 6
    //============================================================
    Project_Interface_Imp() = default;
    ~Project_Interface_Imp() override = default;

    // Virtuals
    //============================================================
    void save() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::save()" << std::endl;
    }
    void load() override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::load()" << std::endl;
    }

    // Data that is fixed on contruction.
    QString name() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::name()" << std::endl;
      return QString{};
    }

    QString location() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::location()" << std::endl;
      return QString{};
    }
    QString filepath() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::filepath()" << std::endl;
      return QString{};
    }

    // Can we currently call undo?
    bool can_undo() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::can_undo()" << std::endl;
      return true;
    }
    // Can we currently call redo?
    bool can_redo() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::can_redo()" << std::endl;
      return true;
    }
    // How many times can undo() be called?
    std::size_t undo_count() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::undo_count()" << std::endl;
      return 0;
    }
    // How many times can redo() be called?
    std::size_t redo_count() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::redo_count()" << std::endl;
      return 0;
    }
    // Undo the last command issued.
    void undo() override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::undo()" << std::endl;
    }
    // Redo the last undone command in the command history
    void redo() override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::redo()" << std::endl;
    }
    // Clear the undo/redo history.
    void clear_history() override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::clear_history()" << std::endl;
    }

    // Does this name appear in the data?
    bool has_name(QString const&) const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::has_name()" << std::endl;
      return true;
    }
    // Get all the objects names in data order
    std::vector<QString> get_all_names() const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::get_all_names()" << std::endl;
      return std::vector<QString>{};
    }
    // Alter the supplied name so that it is unique among the existing data names
    void fix_name(QString&) const override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::fix_name()" << std::endl;
    }

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Abstract_Project_Signalbox_Imp<T,Args...>* a_signalbox) override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::add_signalbox()" << std::endl;
    }
    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Abstract_Project_Signalbox_Imp<T,Args...>* a_signalbox) override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::remove_signalbox()" << std::endl;
    }
    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes() override final
    {
      std::cout << "Project_Interface_Imp<T...Args>::clear_signalboxes()" << std::endl;
    }

    using Inh::is_empty;
    using Inh::count;
    using Inh::has_handle;
    using Inh::has_handle_named;
    using Inh::get_handle_at;
    using Inh::get_handle_named;
    using Inh::get_handles;
    using Inh::get_names;
    using Inh::make_default;
    using Inh::make_emplace;
    using Inh::add_default;
    using Inh::add_emplace;
    using Inh::add;
    using Inh::remove;
    using Inh::change_name;
    using Inh::change_data_at;
    using Inh::request_editor;
    using Inh::request_outliner;
  };

  template <typename T>
  class Do_Project_Interface
  {
    using Type = T;
    using Data_Type = Data<Type>;
    using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

    template <std::size_t Index = 0, std::size_t End = Data_Size_v<Data_Type>>
    class Do_Members
    {
      using Member_Value_Type =Data_Member_Value_Type<Index,Data_Type>;
    public:
      void operator ()(Abstract_Project_Interface* a_api)
      {
        a_api->change_data_at(Index_Tag<Index>(),Signal_Source::System, Handle_Type(), Member_Value_Type());
        Do_Members<Index+1>()(a_api);
      }
    };
    template <std::size_t End>
    class Do_Members<End,End>
    {
    public:
      void operator ()(Abstract_Project_Interface*)
      {
      }
    };

  public:
    void operator()(Abstract_Project_Interface* a_api)
    {
      a_api->is_empty(Tag_Type());
      a_api->count(Tag_Type());

      Handle_Type l_handle{};
      a_api->has_handle(l_handle);

      QString l_name{};
      a_api->has_handle_named(Tag_Type(),l_name);
      a_api->get_handle_at(Tag_Type(),0);

      a_api->get_handles(Tag_Type());
      a_api->get_names(Tag_Type());

      a_api->make_default(Tag_Type());
      a_api->make_emplace(Data_Type());

      Signal_Source l_source{Signal_Source::System};
      a_api->add_default(Tag_Type(), l_source);
      a_api->add_emplace(l_source, Data_Type());

      a_api->add(l_source, l_handle);
      a_api->remove(l_source, l_handle);

      a_api->change_name(l_source, l_handle, l_name);

      Do_Members<>()(a_api);

      a_api->request_editor(l_source, l_handle);
      a_api->request_outliner(l_source, l_handle);
    }
  };
*/
}


void sak::testing::test_abstract_project_interface()
{
  std::cout << "Testing sak::Abstract_Project_Interface" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;


  using Top_Type = Top<File_Definition,Texture_Definition,Material_Definition>;

  std::cout << "sizeof(Top_Type) = " << sizeof(Top_Type) <<  std::endl;

  Top_Type l_tt{};

  Handle<File_Definition> l_fh{};
  Handle<Texture_Definition> l_th{};
  Handle<Material_Definition> l_mh{};

  l_tt.other(l_fh);
  l_tt.other(l_th);
  l_tt.other(l_mh);


  l_tt.member(Index_Tag<0>(),l_fh);;
  l_tt.member(Index_Tag<1>(),l_fh);;
  l_tt.member(Index_Tag<0>(),l_th);;
  l_tt.member(Index_Tag<0>(),l_mh);;

  using APCI_F = Abstract_Project_Interface_Imp<File_Definition>;
  using APCI_FT = Abstract_Project_Interface_Imp<File_Definition, Texture_Definition>;
  using APCI_FTM = Abstract_Project_Interface_Imp<File_Definition, Texture_Definition, Material_Definition>;

  std::cout << "sizeof(APCI_F) = " << sizeof(APCI_F) <<  std::endl;
  std::cout << "sizeof(APCI_FT) = " << sizeof(APCI_FT) <<  std::endl;
  std::cout << "sizeof(APCI_FTM) = " << sizeof(APCI_FTM) <<  std::endl;
/*
  using Project_Interface = Project_Interface_Imp<File_Definition, Texture_Definition, Material_Definition>;

  std::cout << "sizeof(Project_Interface) = " << sizeof(Project_Interface) <<  std::endl;

  QString l_filepath{"D:/Source Army Knife/Test Projects/Project/Project.sakpro"};

  using Project_Interface = Project_Interface_Imp<File_Definition, Texture_Definition, Material_Definition>;
  Project_Interface l_pi{};
  Abstract_Project_Interface* l_api{&l_pi};
  if (l_api)
  {
    l_api->save();
    l_api->load();

    l_api->name();
    l_api->location();
    l_api->filepath();

    l_api->can_undo();
    l_api->can_redo();
    l_api->undo_count();
    l_api->redo_count();
    l_api->undo();
    l_api->redo();
    l_api->clear_history();

    QString l_name{};
    l_api->has_name(l_name);
    l_api->get_all_names();
    l_api->fix_name(l_name);

    Abstract_Project_Interface::Signalbox_Type* l_signalbox{nullptr};
    l_api->add_signalbox(l_signalbox);
    l_api->remove_signalbox(l_signalbox);
    l_api->clear_signalboxes();

    // now the type bits
    Do_Project_Interface<File_Definition>()(l_api);
    Do_Project_Interface<Texture_Definition>()(l_api);
    Do_Project_Interface<Material_Definition>()(l_api);
  }
*/
  {
    test::Top<File_Definition,Texture_Definition,Material_Definition> l_top{};
    l_top.get_section<File_Definition>()->other(Tag<File_Definition>{});
    l_top.get_section<Texture_Definition>()->other(Tag<Texture_Definition>{});
    l_top.get_section<Material_Definition>()->other(Tag<Material_Definition>{});

    l_top.get_member<File_Definition,0>()->func(Tag<File_Definition>{}, Index_Tag<0>{});
    l_top.get_member<File_Definition,1>()->func(Tag<File_Definition>{}, Index_Tag<1>{});
    l_top.get_member<Texture_Definition,0>()->func(Tag<Texture_Definition>{}, Index_Tag<0>{});
    l_top.get_member<Material_Definition,0>()->func(Tag<Material_Definition>{}, Index_Tag<0>{});
    l_top.get_member<Material_Definition,1>()->func(Tag<Material_Definition>{}, Index_Tag<1>{});
    l_top.get_member<Material_Definition,2>()->func(Tag<Material_Definition>{}, Index_Tag<2>{});

    std::unique_ptr<test::Top<File_Definition,Texture_Definition,Material_Definition>> l_top_imp{ new test::Top_Imp<File_Definition,Texture_Definition,Material_Definition>{} };

    l_top_imp->get_section<File_Definition>()->other(Tag<File_Definition>{});
    l_top_imp->get_section<Texture_Definition>()->other(Tag<Texture_Definition>{});
    l_top_imp->get_section<Material_Definition>()->other(Tag<Material_Definition>{});

    l_top_imp->get_member<File_Definition,0>()->func(Tag<File_Definition>{}, Index_Tag<0>{});
    l_top_imp->get_member<File_Definition,1>()->func(Tag<File_Definition>{}, Index_Tag<1>{});
    l_top_imp->get_member<Texture_Definition,0>()->func(Tag<Texture_Definition>{}, Index_Tag<0>{});
    l_top_imp->get_member<Material_Definition,0>()->func(Tag<Material_Definition>{}, Index_Tag<0>{});
    l_top_imp->get_member<Material_Definition,1>()->func(Tag<Material_Definition>{}, Index_Tag<1>{});
    l_top_imp->get_member<Material_Definition,2>()->func(Tag<Material_Definition>{}, Index_Tag<2>{});


  }


  std::cout << "==============================" << std::endl;
}
