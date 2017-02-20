#ifndef COMMON_DATA_INTERFACE_TRAITS_H
#define COMMON_DATA_INTERFACE_TRAITS_H

class QString;

namespace sak
{
    class Project;

    template <typename BH>
    class Common_Data_Const_Interface
    {
    public:
        using basic_handle_type = BH;

        explicit Common_Data_Const_Interface(basic_handle_type const& a_handle);

        QString const& cget_name() const;
        QString const& cget_description() const;

    private:
        basic_handle_type const& m_handle;
    };

    template <typename BH>
    class Common_Data_Interface
    {
    public:
        using basic_handle_type = BH;

        explicit Common_Data_Interface(basic_handle_type& a_handle, Project* a_project);

        void set_name(QString const& a_name);
        void set_description(QString const& a_description);
    private:
        basic_handle_type& m_handle;
        Project* m_signal_reciever;
    };

    template <typename BH>
    class Common_Data_Interface_Traits
    {
    public:
        using basic_handle_type = BH;

        using interface_type = Common_Data_Const_Interface<BH>;
        using const_interface_type = Common_Data_Const_Interface<BH>;

        explicit Common_Data_Interface_Traits(Project* a_project);

        interface_type get(basic_handle_type& a_ref);
        const_interface_type cget(basic_handle_type const& a_ref) const;
    private:
        Project* m_project;
    };
}


/*

*/


#endif // COMMON_DATA_INTERFACE_TRAITS_H
