#include "test_integer.hpp"
#include <dclib/litype/integer.hpp>
#include <type_traits>

static_assert(DCLIB_LITYPE_INTEGER(true)::value == true,"");
static_assert(DCLIB_LITYPE_INTEGER(false)::value == false,"");

static_assert(std::is_same<DCLIB_LITYPE_INTEGER(true)::value_type, bool>::value,"");
static_assert(std::is_same<DCLIB_LITYPE_INTEGER(false)::value_type, bool>::value,"");

static_assert(DCLIB_LITYPE_INTEGER(char(-5))::value == char(-5),"");
//static_assert(DCLIB_LITYPE_INTEGER(unsigned char(123))::value == unsigned char(123),"");

static_assert(std::is_same<DCLIB_LITYPE_INTEGER(char(-5))::value_type, char>::value,"");
//static_assert(std::is_same<DCLIB_LITYPE_INTEGER(unsigned char(123))::value_type, unsigned char>::value,"");

static_assert(DCLIB_LITYPE_INTEGER(short(-856))::value == short(-856),"");
//static_assert(DCLIB_LITYPE_INTEGER(unsigned short(546))::value == unsigned short(546),"");

static_assert(std::is_same<DCLIB_LITYPE_INTEGER(short(-5))::value_type, short>::value,"");
//static_assert(std::is_same<DCLIB_LITYPE_INTEGER(unsigned short(123))::value_type, unsigned short>::value,"");

static_assert(DCLIB_LITYPE_INTEGER(5)::value == 5,"");
static_assert(DCLIB_LITYPE_INTEGER(5u)::value == 5u,"");

static_assert(std::is_same<DCLIB_LITYPE_INTEGER(5)::value_type, int>::value,"");
static_assert(std::is_same<DCLIB_LITYPE_INTEGER(5u)::value_type, unsigned int>::value,"");

static_assert(DCLIB_LITYPE_INTEGER(5l)::value == 5l,"");
static_assert(DCLIB_LITYPE_INTEGER(5ul)::value == 5ul,"");

static_assert(std::is_same<DCLIB_LITYPE_INTEGER(5l)::value_type, long>::value,"");
static_assert(std::is_same<DCLIB_LITYPE_INTEGER(5ul)::value_type, unsigned long>::value,"");

static_assert(DCLIB_LITYPE_INTEGER(5ll)::value == 5ll,"");
static_assert(DCLIB_LITYPE_INTEGER(5ull)::value == 5ull,"");

static_assert(std::is_same<DCLIB_LITYPE_INTEGER(5ll)::value_type, long long>::value,"");
static_assert(std::is_same<DCLIB_LITYPE_INTEGER(5ull)::value_type, unsigned long long>::value,"");


void dclib::litype::test_integer()
{

}
