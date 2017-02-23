#ifndef DATA_H
#define DATA_H

namespace generic
{
    //---------------------------------------------------------------------------
    // Data<Args...>
    //---------------------------------------------------------------------------
    /*
    Need that data class you've been playing around with for ages.

    For things like:

    struct Some_Data
    {
        Some_Type0 m_memmber0;
        Some_Type1 m_memmber1;
        Some_Type2 m_memmber2;
        Some_Type3 m_memmber3;
    };

    We want:

    template <typname Type, typename...Args>
    class Data;

    using Some_Data =
    Data
    <
        Type<"Some Data">,
        Member<Some_Type0,"Member0">,
        Member<Some_Type1,"Member1">,
        Member<Some_Type2,"Member2">,
        Member<Some_Type3,"Member3">
    >;

    Then access any member at both compiletime and runtime.


    */
    class Data
    {
    public:
        Data();
    };

}


#endif // DATA_H
