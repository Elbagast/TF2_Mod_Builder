#ifndef NULL_ON_MOVE_H
#define NULL_ON_MOVE_H

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Nullptr_On_Move
        {
        public:
            using pointer_type = T*;
            using const_pointer_type = T const*;

            Nullptr_On_Move():
                mp_pointer(nullptr)
            {}

            Nullptr_On_Move(pointer_type a_pointer):
                mp_pointer(a_pointer)
            {}
            ~Nullptr_On_Move() = default;

            Nullptr_On_Move(Nullptr_On_Move const& a_other) = default;
            Nullptr_On_Move& operator=(Nullptr_On_Move const& a_other) = default;

            Nullptr_On_Move(Nullptr_On_Move && a_other):
                 mp_pointer(std::move(a_other.mp_pointer))
            {
                a_other.mp_pointer = nullptr;
            }

            Nullptr_On_Move& operator=(Nullptr_On_Move && a_other)
            {
                mp_pointer = std::move(a_other.mp_pointer);
                a_other.mp_pointer = nullptr;
            }

            operator pointer_type()
            {
                return mp_pointer;
            }

            operator const_pointer_type() const
            {
                return mp_pointer;
            }

            pointer_type get()
            {
                return mp_pointer;
            }

            const_pointer_type cget() const
            {
                return mp_pointer;
            }

        private:
            pointer_type mp_pointer;
        };
    } // namespace internal
} // namespace saklib

#endif // NULL_ON_MOVE_H
