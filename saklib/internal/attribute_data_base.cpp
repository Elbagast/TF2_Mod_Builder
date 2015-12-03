#include "attribute_data_base.h"

#include "exceptions/bad_attribute_data_type.h"
#include "type_string.h"

//---------------------------------------------------------------------------
// Attribute_Data_Definition_Base
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Attribute_Data_Definition_Base::~Attribute_Data_Definition_Base() = default;

// Interface
//============================================================
bool saklib::internal::Attribute_Data_Definition_Base::is_bool() const
{
    return false;
}

bool saklib::internal::Attribute_Data_Definition_Base::is_int() const
{
    return false;
}

saklib::internal::Attribute_Data_Definition_Bool& saklib::internal::Attribute_Data_Definition_Base::get_value_bool()
{
    throw Bad_Attribute_Data_Type(TS_Bool()());
}

saklib::internal::Attribute_Data_Definition_Int& saklib::internal::Attribute_Data_Definition_Base::get_value_int()
{
    throw Bad_Attribute_Data_Type(TS_Int()());
}

saklib::internal::Attribute_Data_Definition_Bool const& saklib::internal::Attribute_Data_Definition_Base::cget_value_bool() const
{
    throw Bad_Attribute_Data_Type(TS_Bool()());
}

saklib::internal::Attribute_Data_Definition_Int const& saklib::internal::Attribute_Data_Definition_Base::cget_value_int() const
{
    throw Bad_Attribute_Data_Type(TS_Int()());
}


//---------------------------------------------------------------------------
// Attribute_Data_Base
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Attribute_Data_Base::~Attribute_Data_Base() = default;

// Interface
//============================================================
bool saklib::internal::Attribute_Data_Base::is_bool() const
{
    return false;
}

bool saklib::internal::Attribute_Data_Base::is_int() const
{
    return false;
}

saklib::internal::Attribute_Data_Bool& saklib::internal::Attribute_Data_Base::get_value_bool()
{
    throw Bad_Attribute_Data_Type(TS_Bool()());
}

saklib::internal::Attribute_Data_Int& saklib::internal::Attribute_Data_Base::get_value_int()
{
    throw Bad_Attribute_Data_Type(TS_Int()());
}

saklib::internal::Attribute_Data_Bool const& saklib::internal::Attribute_Data_Base::cget_value_bool() const
{
    throw Bad_Attribute_Data_Type(TS_Bool()());
}

saklib::internal::Attribute_Data_Int const& saklib::internal::Attribute_Data_Base::cget_value_int() const
{
    throw Bad_Attribute_Data_Type(TS_Int()());
}
