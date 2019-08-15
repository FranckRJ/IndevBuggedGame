#ifndef UTLS_HPP
#define UTLS_HPP

#include <cmath>
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

    template <class T>
    constexpr T coerceIn(const T& val, const T& min, const T& max)
    {
        if (val < min)
        {
            return min;
        }
        else if (val > max)
        {
            return max;
        }
        else
        {
            return val;
        }
    }

    template <class T>
    constexpr int intFloor(const T& val)
    {
        return static_cast<int>(std::floor(val));
    }

    template <class T>
    constexpr int intRound(const T& val)
    {
        return static_cast<int>(std::round(val));
    }

    template <class T>
    constexpr int intCeil(const T& val)
    {
        return static_cast<int>(std::ceil(val));
    }
} // namespace utls

#endif
