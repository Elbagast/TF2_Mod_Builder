#ifndef QSTRING_TRAITS_H
#define QSTRING_TRAITS_H

#include "../types.h"
#include <QString>
#include <numeric>
#include "../elementid.h"

namespace saklib
{
    namespace Qtlib
    {
        /*
        QString_Traits<T>
        ====================================================================================================
        Class which contains unique functions for each type that is specialised. By default there is nothing
        of interest.

        */
        template <typename T>
        struct QString_Traits
        {
            static bool const is_specialised{ false };
            static bool const is_specialized{ false };

            static QString to_qstring(T const& value)    { return std::string(); }
            static T from_qstring(QString const& value)  { return T(); }
        };


        /*
        QString_Traits<bool>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<bool>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(bool value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static bool from_qstring(QString const& value)   { return value.toUInt() > 0 ? true : false; }
        };


        /*
        QString_Traits<int>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<int>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(int value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static int from_qstring(QString const& value)    { return value.toInt(); }
        };

        /*
        QString_Traits<long>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<long>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(long value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static long from_qstring(QString const& value)    { return value.toLong(); }
        };

        /*
        QString_Traits<long long>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<long long>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(long long value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static long long from_qstring(QString const& value)    { return value.toLongLong(); }
        };

        /*
        QString_Traits<unsigned int>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<unsigned int>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(unsigned int value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static unsigned int from_qstring(QString const& value)    { return value.toUInt(); }
        };

        /*
        QString_Traits<unsigned long>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<unsigned long>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(unsigned long value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static unsigned long from_qstring(QString const& value)    { return value.toULong(); }
        };

        /*
        QString_Traits<unsigned long long>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<unsigned long long>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(unsigned long long value)
            {
                QString result{};
                result.setNum(value);
                return result;
            }
            static unsigned long long from_qstring(QString const& value)    { return value.toULongLong(); }
        };


        /*
        QString_Traits<float>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<float>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(float value)
            {
                QString result{};
                result.setNum(value, 'g', std::numeric_limits<float>::max_digits10);
                return result;
            }
            static float from_qstring(QString const& value) { return value.toFloat(); }
        };

        /*
        QString_Traits<double>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<double>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(double value)
            {
                QString result{};
                result.setNum(value, 'g', std::numeric_limits<double>::max_digits10);
                return result;
            }
            static double from_qstring(QString const& value) { return value.toDouble(); }
        };

        /*
        QString_Traits<long double>
        ====================================================================================================

        template <>
        struct QString_Traits<long double>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(long double value)
            {
                QString result{};
                result.setNum(value, 'g', std::numeric_limits<long double>::max_digits10);
                return result;
            }
            static long double from_qstring(QString const& value) { no appropriate function }
        };
        */

        /*
        QString_Traits<String>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<String>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(String const& value)   { return QString(value.c_str()); }
            static String from_qstring(QString const& value) { return value.toStdString(); }
        };


        /*
        QString_Traits<Path>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<Path>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(Path const& value)   { return QString(value.string().c_str()); }
            static Path from_qstring(QString const& value) { return Path(value.toStdString()); }
        };


        /*
        QString_Traits<ElementID>
        ====================================================================================================
        */
        template <>
        struct QString_Traits<ElementID>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(ElementID const& value)   { return QString_Traits<size_type>::to_qstring(value.value()); }
            static ElementID from_qstring(QString const& value) { return ElementID(QString_Traits<size_type>::from_qstring(value)); }
        };


        /*
        QString_Traits<std::vector<T>>
        ====================================================================================================
        */
        template <typename T>
        struct QString_Traits<std::vector<T>>
        {
            static bool const is_specialised{ true };
            static bool const is_specialized{ true };

            static QString to_qstring(std::vector<T> const& vector)
            {
                QString result{"[ "};
                if (!vector.empty())
                {
                    for (std::size_t index = 0, end = vector.size(); index < end; ++index)
                    {
                        result.push_back('"');
                        result.append(QString_Traits<T>::to_qstring(vector.at(index)));
                        result.push_back('"');
                        if (index != end - 1)
                        {
                            result.append(", ");
                        }
                    }
                }

                result.append(" ]");
                return result;
            }
            static std::vector<T> from_qstring(QString const& value)
            {
                std::vector<T> result{};

                assert(false);

                return result;
            }
        };



        /*
        Convenience functions
        ====================================================================================================
        */
        template <typename T>
        QString to_qstring(T const& value)
        {
            assert(QString_Traits<T>::is_specialised);
            return QString_Traits<T>::to_qstring(value);
        }

        template <typename T>
        T from_qstring(QString const& value)
        {
            assert(QString_Traits<T>::is_specialised);
            return QString_Traits<T>::from_qstring(value);
        }


    } // namespace Qtlib
} // namespace saklib

#endif // QSTRING_TRAITS_H

