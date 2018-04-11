#ifndef SAK_FILEPATH_HPP
#define SAK_FILEPATH_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_FILEPATH_FWD_HPP
#include "filepath_fwd.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_EXPERIMENTAL_FILESYSTEM
#define INCLUDE_STD_EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Filepath
  //---------------------------------------------------------------------------
  // Stores a filepath, which may or may not be incomplete. Uses copy on write.

  class Filepath
  {
  private:
    // Data Members
    //============================================================
    std::shared_ptr<std::experimental::filesystem::v1::path> m_data;

  public:
    // Special 6
    //============================================================
    Filepath();
    explicit Filepath(std::experimental::filesystem::v1::path const& a_data);
    explicit Filepath(std::string const& a_data);

    Filepath(Filepath const& a_other);
    Filepath& operator=(Filepath const& a_other);

    Filepath(Filepath && a_other);
    Filepath& operator=(Filepath && a_other);

    // Interface
    //============================================================
    bool is_empty() const noexcept;

    bool is_absolute() const;
    bool is_relative() const;

    std::string to_std_string() const;

    // Swap the data.
    void swap(Filepath& a_other) noexcept;

    friend bool operator==(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;
    friend bool operator<(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;
  };

  // Comparison Operators
  //============================================================
  bool operator==(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;
  bool operator!=(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;

  bool operator<(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;
  bool operator>(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;
  bool operator<=(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;
  bool operator>=(Filepath const& a_lhs, Filepath const& a_rhs) noexcept;

  // Non-member Interface
  //============================================================
  void swap(Filepath& a_lhs, Filepath& a_rhs) noexcept;
}


#endif // SAK_FILEPATH_HPP
