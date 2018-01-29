#ifndef SAK_EXCEPTION_HPP
#define SAK_EXCEPTION_HPP

#ifndef SAK_EXCEPTION_FWD_HPP
#include "exception_fwd.hpp"
#endif

#include <cstdint>
/*
#ifndef INCLUDE_STD_EXCEPTION
#define INCLUDE_STD_EXCEPTION
#include <exception>
#endif

#include <stdexcept>
#include <QException>
*/
namespace sak
{
  //---------------------------------------------------------------------------
  // Exception
  //---------------------------------------------------------------------------
  // Base class for exceptions.
  class Exception
  {
  public:
    virtual ~Exception();
  };

  //---------------------------------------------------------------------------
  // Filesystem_Error
  //---------------------------------------------------------------------------
  // Base class for filesystem exceptions.
  class Filesystem_Error :
      public Exception
  {
  public:
    ~Filesystem_Error() override;
  };

  //---------------------------------------------------------------------------
  // Directory_Error
  //---------------------------------------------------------------------------
  class Directory_Error :
      public Filesystem_Error
  {
  public:
    ~Directory_Error() override;
  };

  //---------------------------------------------------------------------------
  // Directory_Missing_Error
  //---------------------------------------------------------------------------
  class Directory_Missing_Error :
      public Directory_Error
  {
  public:
    ~Directory_Missing_Error() override;
  };

  //---------------------------------------------------------------------------
  // Directory_Creation_Error
  //---------------------------------------------------------------------------
  class Directory_Creation_Error :
      public Directory_Error
  {
  public:
    ~Directory_Creation_Error() override;
  };

  //---------------------------------------------------------------------------
  // Directory_Read_Error
  //---------------------------------------------------------------------------
  class Directory_Read_Error :
      public Directory_Error
  {
  public:
    ~Directory_Read_Error() override;
  };

  //---------------------------------------------------------------------------
  // Directory_Write_Error
  //---------------------------------------------------------------------------
  class Directory_Write_Error :
      public Directory_Error
  {
  public:
    ~Directory_Write_Error() override;
  };

  //---------------------------------------------------------------------------
  // File_Error
  //---------------------------------------------------------------------------
  class File_Error :
      public Filesystem_Error
  {
  public:
    ~File_Error() override;
  };

  //---------------------------------------------------------------------------
  // File_Missing_Error
  //---------------------------------------------------------------------------
  class File_Missing_Error :
      public File_Error
  {
  public:
    ~File_Missing_Error() override;
  };

  //---------------------------------------------------------------------------
  // File_Creation_Error
  //---------------------------------------------------------------------------
  class File_Creation_Error :
      public File_Error
  {
  public:
    ~File_Creation_Error() override;
  };

  //---------------------------------------------------------------------------
  // File_Read_Error
  //---------------------------------------------------------------------------
  class File_Read_Error :
      public File_Error
  {
  public:
    ~File_Read_Error() override;
  };

  //---------------------------------------------------------------------------
  // File_Write_Error
  //---------------------------------------------------------------------------
  class File_Write_Error :
      public File_Error
  {
  public:
    ~File_Write_Error() override;
  };

  //---------------------------------------------------------------------------
  // File_Format_Error
  //---------------------------------------------------------------------------
  class File_Format_Error :
      public File_Error
  {
  public:
    ~File_Format_Error() override;
  };


  //---------------------------------------------------------------------------
  // XML_Error
  //---------------------------------------------------------------------------
  class XML_Error :
      public File_Error
  {
  public:
    explicit XML_Error(std::int64_t a_line);
    ~XML_Error() override;

    std::int64_t line() const;
  private:
    std::int64_t m_line;
  };


  //---------------------------------------------------------------------------
  // XML_Missing_Start_Element_Error
  //---------------------------------------------------------------------------
  class XML_Missing_Start_Element_Error :
      public XML_Error
  {
  public:
    explicit XML_Missing_Start_Element_Error(char const* a_name, std::int64_t a_line);
    ~XML_Missing_Start_Element_Error() override;

    char const* name() const;
  private:
    std::int64_t m_line;
  };
}

#endif // SAK_EXCEPTION_HPP
