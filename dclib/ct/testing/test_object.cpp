#include <dclib/ct/testing/test_object.hpp>

#include <dclib/ct/object.hpp>
#include <dclib/ct/member.hpp>
#include <dclib/litype/string.hpp>
#include <string>
#include <iostream>

static_assert(std::is_same_v<dclib::meta::typelist<bool, int, float>,
              dclib::ct::v1::object
              <
              DCLIB_LITYPE_STRING("type")
              ,dclib::ct::v1::member<DCLIB_LITYPE_STRING("a"),bool>
              ,dclib::ct::v1::member<DCLIB_LITYPE_STRING("b"),int>
              ,dclib::ct::v1::member<DCLIB_LITYPE_STRING("c"),float>
              >::member_value_typelist>, "bad typelists");

void dclib::ct::test_object()
{
  std::cout << "Test dclib::ct::object" << std::endl;
  std::cout << "=======================" << std::endl;

  // Starting simple
  using Test_Object1 =
  object
  <
  DCLIB_LITYPE_STRING("Test_Object1")
  ,member<DCLIB_LITYPE_STRING("member0"),bool>
  ,member<DCLIB_LITYPE_STRING("member1"),int>
  ,member<DCLIB_LITYPE_STRING("member2"),double>
  ,member<DCLIB_LITYPE_STRING("member3"),std::string>
  >;

  Test_Object1 to1{};

  std::cout << "type= " << to1.type() << std::endl;

  std::cout << "size= " << to1.size() << std::endl;

  std::cout << "0= " << to1.cat<0>().name() << " " << to1.cat<0>().cget() << std::endl;
  std::cout << "1= " << to1.cat<1>().name() << " " << to1.cat<1>().cget() << std::endl;
  std::cout << "2= " << to1.cat<2>().name() << " " << to1.cat<2>().cget() << std::endl;
  std::cout << "3= " << to1.cat<3>().name() << " " << to1.cat<3>().cget() << std::endl;



  std::cout << "member1= " << to1.cget<DCLIB_LITYPE_STRING("member0")>().name() << " " << to1.cget<DCLIB_LITYPE_STRING("member0")>().cget() << std::endl;
  std::cout << "member1= " << to1.cget<DCLIB_LITYPE_STRING("member1")>().name() << " " << to1.cget<DCLIB_LITYPE_STRING("member1")>().cget() << std::endl;
  std::cout << "member1= " << to1.cget<DCLIB_LITYPE_STRING("member2")>().name() << " " << to1.cget<DCLIB_LITYPE_STRING("member2")>().cget() << std::endl;
  std::cout << "member1= " << to1.cget<DCLIB_LITYPE_STRING("member3")>().name() << " " << to1.cget<DCLIB_LITYPE_STRING("member3")>().cget() << std::endl;

  Test_Object1 to2{std::make_tuple(true,5,2.5648,"weeee")};



  std::cout << "member1= " << to2.cget<DCLIB_LITYPE_STRING("member0")>().name() << " " << to2.cget<DCLIB_LITYPE_STRING("member0")>().cget() << std::endl;
  std::cout << "member1= " << to2.cget<DCLIB_LITYPE_STRING("member1")>().name() << " " << to2.cget<DCLIB_LITYPE_STRING("member1")>().cget() << std::endl;
  std::cout << "member1= " << to2.cget<DCLIB_LITYPE_STRING("member2")>().name() << " " << to2.cget<DCLIB_LITYPE_STRING("member2")>().cget() << std::endl;
  std::cout << "member1= " << to2.cget<DCLIB_LITYPE_STRING("member3")>().name() << " " << to2.cget<DCLIB_LITYPE_STRING("member3")>().cget() << std::endl;

  std::cout << "=======================" << std::endl;
}
