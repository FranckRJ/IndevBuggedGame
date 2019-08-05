#ifndef UTLS_HPP
#define UTLS_HPP

#include <type_traits>

namespace utls
{
    template <class T>
    constexpr auto asSigned(T t)
    {
        return std::make_signed_t<T>(t);
    }

    template <class T>
    constexpr auto asUnsigned(T t)
    {
        return std::make_unsigned_t<T>(t);
    }
} // namespace utls

#endif
