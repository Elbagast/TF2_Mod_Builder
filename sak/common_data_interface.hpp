#ifndef COMMON_DATA_INTERFACE_TRAITS_HPP
#define COMMON_DATA_INTERFACE_TRAITS_HPP

class QString;

namespace sak
{
    class Project;

    template <typename H, typename BH>
    class Common_Data_Const_Interface
    {
    public:
        using common_interface_type = Common_Data_Const_Interface<H,BH>;

        using handle_type = H;
        using basic_handle_type = BH;

        Common_Data_Const_Interface(handle_type const& a_handle, basic_handle_type const& a_data);

    protected:
        ~Common_Data_Const_Interface();
    public:

        QString const& cget_name() const;
        QString const& cget_description() const;

    protected:
        handle_type const& m_handle;
        basic_handle_type const& m_data;
    };

    template <typename H, typename BH>
    class Common_Data_Interface
    {
    public:
        using common_interface_type = Common_Data_Interface<H,BH>;

        using handle_type = H;
        using basic_handle_type = BH;

        Common_Data_Interface(handle_type const& a_handle, basic_handle_type& a_data, Project* a_project);
    protected:
        ~Common_Data_Interface();
    public:
        void set_name(QString const& a_name);
        void set_description(QString const& a_description);

    protected:
        handle_type const& m_handle;
        basic_handle_type& m_data;
        Project* m_project;
    };
}





#endif // COMMON_DATA_INTERFACE_TRAITS_HPP
