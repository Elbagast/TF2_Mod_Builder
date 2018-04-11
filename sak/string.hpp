#ifndef SAK_STRING_HPP
#define SAK_STRING_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_STRING_FWD_HPP
#include "string_fwd.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // String
  //---------------------------------------------------------------------------
  // Unicode string class. Uses copy on write. Mostly just so we can enforce
  // specific encoding when we need to.

  class String
  {
  private:
    // Data Members
    //============================================================
    std::shared_ptr<std::string> m_data;

  public:
    // Special 6
    //============================================================
    String();
    explicit String(std::string const& a_data);

    String(String const& a_other);
    String& operator=(String const& a_other);

    String(String && a_other);
    String& operator=(String && a_other);

    // Interface
    //============================================================
    bool is_empty() const noexcept;

    std::string to_std_string() const;

    // Swap the data.
    void swap(String& a_other) noexcept;

    friend bool operator==(String const& a_lhs, String const& a_rhs) noexcept;
    friend bool operator<(String const& a_lhs, String const& a_rhs) noexcept;

    friend bool operator==(String const& a_lhs, std::string const& a_rhs) noexcept;
    friend bool operator==(std::string const& a_lhs, String const& a_rhs) noexcept;
  };

  // Comparison Operators
  //============================================================
  bool operator==(String const& a_lhs, String const& a_rhs) noexcept;
  bool operator!=(String const& a_lhs, String const& a_rhs) noexcept;

  bool operator<(String const& a_lhs, String const& a_rhs) noexcept;
  bool operator>(String const& a_lhs, String const& a_rhs) noexcept;
  bool operator<=(String const& a_lhs, String const& a_rhs) noexcept;
  bool operator>=(String const& a_lhs, String const& a_rhs) noexcept;


  bool operator==(String const& a_lhs, std::string const& a_rhs) noexcept;
  bool operator==(std::string const& a_lhs, String const& a_rhs) noexcept;

  bool operator!=(String const& a_lhs, std::string const& a_rhs) noexcept;
  bool operator!=(std::string const& a_lhs, String const& a_rhs) noexcept;

  // Non-member Interface
  //============================================================
  void swap(String& a_lhs, String& a_rhs) noexcept;

} // namespace sak

#endif // SAK_STRING_HPP
