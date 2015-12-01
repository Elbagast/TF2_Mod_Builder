#ifndef SAKLIB_OBJECT_POINTER_STORAGE_H
#define SAKLIB_OBJECT_POINTER_STORAGE_H

#include "iobject_pointer_storage.h"

namespace saklib
{
    namespace local
    {
        /*
        Object_Pointer_Storage<T>
        ====================================================================================================
        */
        template <typename T>
        class Object_Pointer_Storage_R :
                public virtual IObject_Pointer_Storage_R<T>
        {
        public:
            // Typedefs
            //============================================================
            using stored_type = typename IObject_Pointer_Storage_R<T>::stored_type;
            using storage_type = typename IObject_Pointer_Storage_R<T>::storage_type;
            using pointer = typename  IObject_Pointer_Storage_R<T>::pointer;
            using const_pointer = typename IObject_Pointer_Storage_R<T>::const_pointer;

            // Special 6
            //============================================================
            Object_Pointer_Storage_R():
                IObject_Pointer_Storage_R<T>(),
                m_storage()
            {}
            explicit Object_Pointer_Storage_R(storage_type& a_storage):
                IObject_Pointer_Storage_R<T>(),
                m_storage()
            {
                std::swap(m_storage, a_storage);
            }
            explicit Object_Pointer_Storage_R(storage_type&& a_storage):
                IObject_Pointer_Storage_R<T>(),
                m_storage(std::move(a_storage))
            {}
            ~Object_Pointer_Storage_R() override = default;

        protected:
            // Virtuals
            //============================================================
            size_type v_size() const override                   { return m_storage.size(); }
            bool v_empty() const override                       { return m_storage.empty(); }
            bool v_has_index(size_type index) const override    { return !m_storage.empty() && index < m_storage.size(); }
            pointer v_at(size_type index) override              { return m_storage.at(index).get(); }
            const_pointer v_cat(size_type index) const override { return m_storage.at(index).get(); }
        private:
            storage_type m_storage;
        };


        /*
        Object_Pointer_Storage_RW<T>
        ====================================================================================================
        */
        template <typename T>
        class Object_Pointer_Storage_RW:
                public virtual IObject_Pointer_Storage_RW<T>
        {
        public:
            // Typedefs
            //============================================================
            using stored_type = typename IObject_Pointer_Storage_R<T>::stored_type;
            using storage_type = typename IObject_Pointer_Storage_R<T>::storage_type;
            using pointer = typename IObject_Pointer_Storage_R<T>::pointer;
            using const_pointer = typename IObject_Pointer_Storage_R<T>::const_pointer;

            // Special 6
            //============================================================
            Object_Pointer_Storage_RW():
                IObject_Pointer_Storage_RW<T>(),
                m_storage()
            {}
            explicit Object_Pointer_Storage_RW(storage_type& a_storage):
                IObject_Pointer_Storage_RW<T>(),
                m_storage()
            {
                std::swap(m_storage, a_storage);
            }
            explicit Object_Pointer_Storage_RW(storage_type&& a_storage):
                IObject_Pointer_Storage_RW<T>(),
                m_storage(std::move(a_storage))
            {}
            ~Object_Pointer_Storage_RW() override = default;

        protected:
            // Virtuals
            //============================================================
            size_type v_size() const override                                   { return m_storage.size(); }
            bool v_empty() const override                                       { return m_storage.empty(); }
            bool v_has_index(size_type index) const override                    { return !m_storage.empty() && index < m_storage.size(); }
            pointer v_at(size_type index) override                              { return m_storage.at(index).get(); }
            const_pointer v_cat(size_type index) const override                 { return m_storage.at(index).get(); }

            void v_push_back(stored_type& a_pointer) override  { m_storage.emplace_back(a_pointer.release()); }
            void v_push_back(stored_type&& a_pointer) override { m_storage.emplace_back(a_pointer.release()); }
            //void v_push_back(pointer a_pointer) override                        { m_storage.emplace_back(a_pointer); }
            void v_clear() override                                             { m_storage.clear(); }
        private:
            storage_type m_storage;
        };

    } // namespace local
} // namespace saklib
#endif // SAKLIB_OBJECT_POINTER_STORAGE_H

