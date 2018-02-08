#include "test_abstract_project_interface.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/data.hpp>
#include <sak/handle.hpp>
#include <sak/tag.hpp>
#include <sak/abstract_project_interface.hpp>
#include <sak/project_data.hpp>

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


  using APCI_F = Abstract_Project_Chained_Interface<File_Definition>;
  using APCI_FT = Abstract_Project_Chained_Interface<File_Definition, Texture_Definition>;
  using APCI_FTM = Abstract_Project_Chained_Interface<File_Definition, Texture_Definition, Material_Definition>;

  std::cout << "sizeof(APCI_F) = " << sizeof(APCI_F) <<  std::endl;
  std::cout << "sizeof(APCI_FT) = " << sizeof(APCI_FT) <<  std::endl;
  std::cout << "sizeof(APCI_FTM) = " << sizeof(APCI_FTM) <<  std::endl;

  QString l_filepath{"D:/Source Army Knife/Test Projects/Project/Project.sakpro"};


  //auto l_pi = make_project_interface(Project_Data {l_filepath});

  //std::cout << "Name =     \"" << l_pi->name().toStdString() << "\"" << std::endl;
  //std::cout << "Location = \"" << l_pi->location().toStdString() << "\"" << std::endl;
  //std::cout << "Filepath = \"" << l_pi->filepath().toStdString() << "\"" << std::endl;


  std::cout << "==============================" << std::endl;
}
