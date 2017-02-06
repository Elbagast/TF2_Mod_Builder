#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
class QWidget;

namespace sak
{
    class Exception
    {
    public:
        virtual ~Exception() = 0;
        virtual void dialog(QWidget* a_parent) const = 0;
    };

    // When there is an error with the filesystem
    class Filesystem_Error :
            public Exception
    {
    public:
        Filesystem_Error(QString const& a_path1, QString const& a_path2);
        ~Filesystem_Error() override;
        void dialog(QWidget* a_parent) const override;

        QString const& path1() const;
        QString const& path2() const;
    private:
        QString m_path1;
        QString m_path2;
    };

    // When an expected directory is missing
    class Directory_Missing_Error :
            public Filesystem_Error
    {
    public:
        explicit Directory_Missing_Error(QString const& a_dirpath);
        ~Directory_Missing_Error() override;
        void dialog(QWidget* a_parent) const override;
    };

    // When an expected file is missing
    class File_Missing_Error :
            public Filesystem_Error
    {
    public:
        explicit File_Missing_Error(QString const& a_filepath);
        ~File_Missing_Error() override;
        void dialog(QWidget* a_parent) const override;
    };

    // When write access to a file fails
    class File_Write_Error :
            public Filesystem_Error
    {
    public:
        explicit File_Write_Error(QString const& a_filepath);
        ~File_Write_Error() override;
        void dialog(QWidget* a_parent) const override;
    };

    // When read access to a file fails
    class File_Read_Error :
            public Filesystem_Error
    {
    public:
        explicit File_Read_Error(QString const& a_filepath);
        ~File_Read_Error() override;
        void dialog(QWidget* a_parent) const override;
    };
}


#endif // EXCEPTION_H
