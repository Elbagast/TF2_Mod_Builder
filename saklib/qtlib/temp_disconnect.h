#ifndef TEMP_DISCONNECT_H
#define TEMP_DISCONNECT_H

#include <QObject>

namespace Saklib
{
    namespace Qtlib
    {
        /*
        Temp_Disconnect
        ====================================================================================================
        Class to encapsulate a temporary disconnection then reconnection of a Qt signal

        (const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                     const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot,
        */
        template <typename Func1, typename Func2>
        class Temp_Disconnect
        {
        public:
            Temp_Disconnect(typename QtPrivate::FunctionPointer<Func1>::Object const* sender, Func1 signal,
                            typename QtPrivate::FunctionPointer<Func2>::Object const* receiver, Func2 slot):
                mp_sender(sender),
                mfp_signal(signal),
                mp_receiver(receiver),
                mfp_slot(slot)
            {
                QObject::disconnect(mp_sender, mfp_signal, mp_receiver, mfp_slot);
            }

            ~Temp_Disconnect()
            {
                QObject::connect(mp_sender, mfp_signal, mp_receiver, mfp_slot);
            }

        private:
            typename QtPrivate::FunctionPointer<Func1>::Object const* mp_sender;
            Func1 mfp_signal;
            typename QtPrivate::FunctionPointer<Func2>::Object const* mp_receiver;
            Func2 mfp_slot;
        };

        template <typename Func1, typename Func2>
        Temp_Disconnect<Func1, Func2> make_Temp_Disconnect(typename QtPrivate::FunctionPointer<Func1>::Object const* sender, Func1 signal,
                                                           typename QtPrivate::FunctionPointer<Func2>::Object const* receiver, Func2 slot)
        {
            return Temp_Disconnect<Func1, Func2>(sender, signal, receiver, slot);
        }

    } // namespace Qtlib
} // namespace Saklib
#endif // TEMP_DISCONNECT_H
