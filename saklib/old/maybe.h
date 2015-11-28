#ifndef MAYBE_H
#define MAYBE_H

namespace saklib
{
    /*
    Maybe<T>
    ====================================================================================================
    Simple pairing of a value and bool for cases where the value may or may not be important. This class
    should simplify declarations of constraints and make sure bool / value pairs are correct.
    */
    template <typename T>
    class Maybe
    {
    public:

        Maybe():
            m_value(),
            m_used(false)
        {}
        explicit Maybe(T const& value):
            m_value(value),
            m_used(true)
        {}

        ~Maybe() = default;

        Maybe(Maybe const& other) = default;
        Maybe& operator=(Maybe const& other) = default;

        //Maybe(Maybe && other) = default;
        //Maybe& operator=(Maybe && other) = default;

        T const& value() const
        {
            return m_value;
        }
        bool used() const
        {
            return m_used;
        }

        void set_value(T const& value)
        {
            m_value = value;
            m_used = true;
        }
        void unset_value()
        {
            m_value = T();
            m_used = false;
        }

    private:
        T m_value;
        bool m_used;
    };
} // namespace saklib

#endif // MAYBE_H

