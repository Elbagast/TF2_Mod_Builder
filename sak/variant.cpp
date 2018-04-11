#include "variant.hpp"

#include "data_type.hpp"

// Special 6
//============================================================
sak::Variant::Variant():
  m_type{Data_Type::Unknown},
  m_data{}
{}

sak::Variant::Variant(Bool a_value):
  m_type{Data_Type::Bool},
  m_data{a_value}
{}

sak::Variant::Variant(Int8 a_value):
  m_type{Data_Type::Int8},
  m_data{a_value}
{}

sak::Variant::Variant(Int16 a_value):
  m_type{Data_Type::Int16},
  m_data{a_value}
{}

sak::Variant::Variant(Int32 a_value):
  m_type{Data_Type::Int32},
  m_data{a_value}
{}

sak::Variant::Variant(Int64 a_value):
  m_type{Data_Type::Int64},
  m_data{a_value}
{}

sak::Variant::Variant(Uint8 a_value):
  m_type{Data_Type::Uint8},
  m_data{a_value}
{}

sak::Variant::Variant(Uint16 a_value):
  m_type{Data_Type::Uint16},
  m_data{a_value}
{}

sak::Variant::Variant(Uint32 a_value):
  m_type{Data_Type::Uint32},
  m_data{a_value}
{}

sak::Variant::Variant(Uint64 a_value):
  m_type{Data_Type::Uint64},
  m_data{a_value}
{}

sak::Variant::Variant(Float32 a_value):
  m_type{Data_Type::Float32},
  m_data{a_value}
{}

sak::Variant::Variant(Float64 a_value):
  m_type{Data_Type::Float64},
  m_data{a_value}
{}

//sak::Variant::Variant(ColourRGB a_value);
//sak::Variant::Variant(ColourRGBA a_value);
sak::Variant::Variant(String const& a_value):
  m_type{Data_Type::String},
  m_data{a_value}
{}

sak::Variant::Variant(Filepath const& a_value):
  m_type{Data_Type::Filepath},
  m_data{a_value}
{}

//sak::Variant::Variant(Enumeration const& a_value);
sak::Variant::Variant(Entity_ID a_value):
  m_type{Data_Type::Entity_ID},
  m_data{a_value}
{}


sak::Variant::Variant(Variant const& a_other) = default;
sak::Variant& sak::Variant::operator=(Variant const& a_other) = default;

sak::Variant::Variant(Variant && a_other):
  m_type{a_other.m_type},
  m_data{std::move(a_other.m_data)}
{
  // must clear the one moved from
  a_other.m_type = Data_Type::Unknown;
}

sak::Variant& sak::Variant::operator=(Variant && a_other)
{
  if (this != std::addressof(a_other))
  {
    m_type = a_other.m_type;
    m_data = std::move(a_other.m_data);
    // must clear the one moved from
    a_other.m_type = Data_Type::Unknown;
  }
  return *this;
}


// Interface
//============================================================
bool sak::Variant::is_valid() const noexcept
{
  return sak::is_valid(m_type);
}

sak::Data_Type sak::Variant::type() const noexcept
{
  return m_type;
}

sak::Bool sak::Variant::get_bool() const
{
  return boost::get<Bool>(m_data);
}
sak::Int8 sak::Variant::get_int8() const
{
  return boost::get<Int8>(m_data);
}
sak::Int16 sak::Variant::get_int16() const
{
  return boost::get<Int16>(m_data);
}
sak::Int32 sak::Variant::get_int32() const
{
  return boost::get<Int32>(m_data);
}
sak::Int64 sak::Variant::get_int64() const
{
  return boost::get<Int64>(m_data);
}
sak::Uint8 sak::Variant::get_uint8() const
{
  return boost::get<Uint8>(m_data);
}
sak::Uint16 sak::Variant::get_uint16() const
{
  return boost::get<Uint16>(m_data);
}
sak::Uint32 sak::Variant::get_uint32() const
{
  return boost::get<Uint32>(m_data);
}
sak::Uint64 sak::Variant::get_uint64() const
{
  return boost::get<Uint64>(m_data);
}
sak::Float32 sak::Variant::get_float32() const
{
  return boost::get<Float32>(m_data);
}
sak::Float64 sak::Variant::get_float64() const
{
  return boost::get<Float64>(m_data);
}
//sak::ColourRGB sak::Variant::get_colour_rgb() const;
//sak::ColourRGBA sak::Variant::get_colour_rgba() const;
sak::String sak::Variant::get_string() const
{
  return boost::get<String>(m_data);
}
sak::Filepath sak::Variant::get_filepath() const
{
  return boost::get<Filepath>(m_data);
}
//sak::Enumeration sak::Variant::get_enumeration() const;
sak::Entity_ID sak::Variant::get_entity_id() const
{
  return boost::get<Entity_ID>(m_data);
}
