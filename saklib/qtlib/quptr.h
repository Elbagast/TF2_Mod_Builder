#ifndef QUPTR_H
#define QUPTR_H

#include "../types.h"
#include <QPointer>

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

        So, this class owns a pointer to a Qt class, but the destructor only calls delete on the pointer if
        it determines that that was not already done, otherwise it's a std::unique_ptr.


        ...Alternatively investigate a different system for managing Element_Widgets
        */
        template <typename T>
        class QUptr
        {
            // T must inherit QObject or this won't compile
        public:
            QUptr():
                m_ptr(nullptr),
                m_qptr(nullptr)
            {}
            QUptr(std::nullptr_t null_pointer):
                m_ptr(null_pointer),
                m_qptr(null_pointer)
            {}
            explicit QUptr(T* pointer):
                m_ptr(pointer),
                m_qptr(pointer)
            {}

            QUptr(QUptr const& other) = delete;
            QUptr& operator=(QUptr const& other) = delete;

            // Implicit default move

            //
            // release
            // reset
            // swap
            // get
            // operator bool
            // operator*
            // opearator->

        private:
            Uptr<T> m_ptr;
            QPointer<T> m_qptr;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // QUPTR_H
