#ifndef SAKLIB_PROPERTY_H
#define SAKLIB_PROPERTY_H

namespace saklib
{
    /*
    IProperty_R<T>
    ====================================================================================================
    */
    template <typename T>
    class IProperty_R
    {
    public:
        using data_type = T;

        virtual ~IProperty_R() = default;

        data_type const& data() const              { return v_data(); }
    protected:
        virtual data_type const& v_data() const = 0;
    };

    /*
    IProperty_RW<T>
    ====================================================================================================
    Interface for access to an Object's data, read and write access
    */
    template <typename T>
    class IProperty_RW :
            public virtual IProperty_R<T>
    {
    public:
        using data_type = typename IProperty_R<T>::data_type;

        ~IProperty_RW() override = default;

        using IProperty_R<T>::data;
        void set_data(data_type const& arg_data)   { v_set_data(arg_data); }
    protected:
        virtual void v_set_data(data_type const& arg_data) = 0;
    };


    namespace local
    {
        /*
        Property_R<T>
        ====================================================================================================
        */
        template <typename T>
        class Property_R :
                public virtual IProperty_R<T>
        {
        public:
            using data_type = typename IProperty_R<T>::data_type;

            // Special 6
            //============================================================
            explicit Property_R(data_type const& a_data):
                IProperty_R<T>(),
                m_data(a_data)
            {}
            ~Property_R() override = default;

            using IProperty_R<T>::data;
        protected:
             data_type const& v_data() const override              { return m_data; }
        private:
             data_type m_data;
        };

        /*
        Property_RW<T>
        ====================================================================================================
        */
        template <typename T>
        class Property_RW :
                public virtual IProperty_RW<T>
        {
        public:
            using data_type = typename IProperty_RW<T>::data_type;

            // Special 6
            //============================================================
            Property_RW():
                IProperty_RW<T>(),
                m_data()
            {}
            explicit Property_RW(data_type const& a_data):
                IProperty_RW<T>(),
                m_data(a_data)
            {}
            ~Property_RW() override = default;

            using IProperty_RW<T>::data;
            using IProperty_RW<T>::set_data;
        protected:
             data_type const& v_data() const override              { return m_data; }
             void v_set_data(data_type const& a_data) override     { m_data = a_data; }
        private:
             data_type m_data;
        };
    } // namespace local


    namespace remote
    {
        /*
        Property_R<T>
        ====================================================================================================
        */
        template <typename T>
        class Property_R :
                public virtual IProperty_R<T>
        {
        public:
            using data_type = typename IProperty_R<T>::data_type;

            // Special 6
            //============================================================
           explicit  Property_R(IProperty_R<T> const& a_interface):
                IProperty_R<T>(),
                mr_interface(a_interface)
            {}
            ~Property_R() override = default;

            using IProperty_R<T>::data;
        protected:
             data_type const& v_data() const override              { return mr_interface.data(); }
        private:
             IProperty_R const& mr_interface;
        };


        /*
        Property_RW<T>
        ====================================================================================================
        */
        template <typename T>
        class Property_RW :
                public virtual IProperty_RW<T>
        {
        public:
            using data_type = typename IProperty_RW<T>::data_type;

            // Special 6
            //============================================================
            explicit Property_RW(IProperty_RW<T>& a_interface):
                IProperty_RW<T>(),
                mr_interface(a_interface)
            {}
            ~Property_RW() override = default;

            using IProperty_RW<T>::data;
            using IProperty_RW<T>::set_data;
        protected:
             data_type const& v_data() const override              { return mr_interface.data(); }
             void v_set_data(data_type const& a_data) override     { mr_interface.set_data(a_data); }
        private:
             IProperty_RW<T>& mr_interface;
        };
    } // namespace remote

} // namespace saklib

#define TEMPLATE_IPROPERTY_R(name) \
    template <typename T> class I##name##_R \
    { \
    public: \
        using data_type = T; \
        virtual ~I##name##_R() = default; \
        data_type const& name() const { return v_##name(); } \
        char const* name##_c_str() const { return #name; } \
    protected: \
        virtual data_type const& v_##name() const = 0; \
    };

#define TEMPLATE_IPROPERTY_RW(name) \
    template <typename T> class I##name##_RW : public I##name##_R<T> \
    { \
    public: \
        using data_type = typename I##name##_R<T>::data_type; \
        virtual ~I##name##_RW() = default; \
        void set_##name(data_type const& arg_data)   { v_set_##name(arg_data); } \
    protected: \
        virtual void v_set_##name(data_type const& arg_data) = 0; \
    };

#define TEMPLATE_LOCAL_PROPERTY_R(name) \
    template <typename T> class Local##name##_R : public I##name##_R<T> \
    { \
    public: \
        using data_type = typename I##name##_R<T>::data_type; \
        explicit Local##name##_R(data_type const& a_data): I##name##_R<T>(), m_data(a_data) {} \
        ~Local##name##_R() override = default; \
    protected: \
        data_type const& v_##name() const override { return m_data; } \
    private: \
        data_type m_data; \
    };

#define TEMPLATE_LOCAL_PROPERTY_RW(name) \
    template <typename T> class Local_##name##_RW : public I##name##_RW<T> \
    { \
    public: \
        using data_type = typename I##name##_RW<T>::data_type; \
        Local_##name##_RW(): I##name##_RW<T>(), m_data() {} \
        explicit Local_##name##_RW(data_type const& a_data): I##name##_RW<T>(), m_data(a_data) {} \
        ~Local_##name##_RW() override = default; \
    protected: \
        data_type const& v_##name() const override { return m_data; } \
        void v_set_##name(data_type const& a_data) override { m_data = a_data; } \
    private: \
        data_type m_data; \
    };

#define TEMPLATE_REMOTE_PROPERTY_R(name) \
    template <typename T> class Remote_##name##_R : public I##name##_R<T> \
    { \
    public: \
        using data_type = typename I##name##_RW<T>::data_type; \
        explicit Remote_##name##_R(I##name##_R<T> const& a_data): I##name##_R<T>(), m_data(a_data) {} \
        ~Remote_##name##_R() override = default; \
    protected: \
        data_type const& v_##name() const override { return m_data.name(); } \
    private: \
        I##name##_R<T> const& m_data; \
    };

#define TEMPLATE_REMOTE_PROPERTY_RW(name) \
    template <typename T> class Remote_##name##_RW : public I##name##_RW<T> \
    { \
    public: \
        using data_type = typename I##name##_RW<T>::data_type; \
        explicit Remote_##name##_RW(I##name##_RW<T>& a_data): I##name##_RW<T>(), m_data(a_data) {} \
        ~Remote_##name##_RW() override = default; \
    protected: \
        data_type const& v_##name() const override { return m_data.name(); } \
        void v_set_##name(data_type const& a_data) override { m_data.set_data(a_data); } \
    private: \
        I##name##_RW<T>& m_data; \
    };

#define ALL_TEMPLATES_PROPERTY(name) \
    TEMPLATE_IPROPERTY_R(name) \
    TEMPLATE_IPROPERTY_RW(name) \
    TEMPLATE_LOCAL_PROPERTY_R(name) \
    TEMPLATE_LOCAL_PROPERTY_RW(name) \
    TEMPLATE_REMOTE_PROPERTY_R(name) \
    TEMPLATE_REMOTE_PROPERTY_RW(name)



#endif // LOCAL_PROPERTY_H

