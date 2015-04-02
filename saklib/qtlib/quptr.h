#ifndef QUPTR_H
#define QUPTR_H

#include <QPointer>
#include <memory>

namespace Saklib
{
    namespace Qtlib
    {
        /*
        QUptr
        ====================================================================================================
        Qt classes generally have parent-based lifetimes, but this means things get a bit complicated when
        you want to specify the lifetimes yourself. An Element_Widget needs to only last as long as the
        corresponding Element, but a shared pointer for the widget will not necessarily reflect that. The
        parenting also means that a std::unique_ptr of a Qt class might call delete on a pointer that was
        deleted elsewhere already. Since it's not always clear where this happens, we need a smart pointer
        that manages double-deletes as needed, rather than having to guess whether it's happened already.

        How do do this is pretty simple: QUptr has a QPointer that stores the pointer, and calls delete on
        that pointer if it isn't set to null by the time ~QUptr is called. Now just use it you would a
        std::unique_ptr.
        */
        template <typename T>
        class QUptr
        {
            // T must inherit QObject or this won't compile
        public:
            QUptr():
                m_qptr(nullptr)
            {}
            QUptr(std::nullptr_t null_pointer):
                m_qptr(null_pointer)
            {}
            explicit QUptr(T* pointer):
                m_qptr(pointer)
            {}
            explicit QUptr(std::unique_ptr<T>&& uptr):
                m_qptr(uptr.release())
            {}
            ~QUptr()
            {
                reset();
            }

            QUptr(QUptr const& other) = delete;
            QUptr& operator=(QUptr const& other) = delete;

            QUptr(QUptr && other):
                m_qptr(std::move(other.m_qptr))
            {
                other.m_qptr.clear();
            }

            QUptr& operator=(QUptr && other)
            {
                m_qptr = std::move(other.m_qptr);
                other.m_qptr.clear();
                return *this;
            }

            QUptr& operator=(std::unique_ptr<T>&& uptr)
            {
                m_qptr = uptr.release();
                return *this;
            }

            //
            T* release()
            {
                T* result = m_qptr.data();
                m_qptr.clear();
                return result;
            }

            void reset()
            {
                if (m_qptr.data() != nullptr)
                {
                    delete m_qptr.data();
                    m_qptr = nullptr;
                }
            }

            void reset(T* pointer)
            {
                reset();
                m_qptr = pointer;
            }

            void swap(QUptr& other)
            {
                T* other_ptr = other.release();
                other.reset(this->release());
                this->reset(other_ptr);
            }

            T* get() const
            {
                return m_qptr.data();
            }

            explicit operator bool() const
            {
                return !m_qptr.isNull();
            }
            T& operator*()
            {
                return *(m_qptr.data());
            }

            T* operator->() const
            {
                return m_qptr.data();
            }

        private:
            QPointer<T> m_qptr;
        };

        template <typename T, typename... Args>
        QUptr<T> make_quptr(Args&&... args)
        {
            return QUptr<T>(new T(std::forward<Args>(args)...));
        }

    } // namespace Qtlib
} // namespace Saklib

#endif // QUPTR_H
