#ifndef UTLS_HPP
#define UTLS_HPP

#include <type_traits>

namespace utls
{
    template <class T>
    constexpr auto asSigned(T pT)
    {
        return std::make_signed_t<T>(pT);
    }

    template <class T>
    constexpr auto asUnsigned(T pT)
    {
        return std::make_unsigned_t<T>(pT);
    }
} // namespace utls

#endif
