#ifndef REFERENCE_COUNTER_H
#define REFERENCE_COUNTER_H


namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Reference_Counter
        {
        public:
            using traits_type = T;

            // Special 6
            //============================================================
            explicit Reference_Counter(traits_type const& a_traits);

            ~Reference_Counter();

            Reference_Counter(Reference_Counter const& other);
            Reference_Counter& operator=(Reference_Counter const& other);

            Reference_Counter(Reference_Counter && other);
            Reference_Counter& operator=(Reference_Counter && other);

        private:
            traits_type m_traits;
        };
    } // namespace internal
} // namespace saklib


#endif // REFERENCE_COUNTER_H


// Special 6
//============================================================
template <typename T>
saklib::internal::Reference_Counter<T>::Reference_Counter(traits_type const& a_traits) :
    m_traits{ a_traits }
{
    m_traits.increment();
}


template <typename T>
saklib::internal::Reference_Counter<T>::~Reference_Counter()
{
    if (mp_manager != nullptr)
    {
        mp_manager->decrement_reference_count(m_handle);
    }
}

template <typename T>
saklib::internal::Reference_Counter<T>::Reference_Counter(Reference_Counter const& other) :
    mp_manager{ other.mp_manager },
    m_handle{ (mp_manager != nullptr ? other.m_handle : handle_type(null_handle())) }
{
    if (mp_manager != nullptr)
    {
        mp_manager->increment_reference_count(m_handle);
    }
}

template <typename T>
saklib::internal::Reference_Counter<T>& saklib::internal::Reference_Counter<T>::operator=(Reference_Counter const& other)
{
    if (&other != this)
    {
        manager_type* old_manager{ mp_manager };
        handle_type old_handle{ m_handle };

        mp_manager = other.mp_manager;
        m_handle = other.m_handle;

        if (mp_manager)
        {
            mp_manager->increment_reference_count(m_handle); // this is a new holder of this value so increment
        }
        if (old_manager)
        {
            old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
        }
    }
    return *this;
}

template <typename T>
saklib::internal::Reference_Counter<T>::Reference_Counter(Reference_Counter && other) :
    mp_manager{ std::move(other.mp_manager) },
    m_handle{ std::move(other.m_handle) }
{
    // no reference count change
    other.mp_manager = nullptr;
    other.m_handle = null_handle();
}
