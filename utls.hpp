#ifndef UTLS_HPP
#define UTLS_HPP

#include <algorithm>
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
        if (val >= 0)
        {
            return static_cast<int>(val);
        }
        else
        {
            return static_cast<int>(std::floor(val));
        }
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

    template <class Container, class UnaryPredicate>
    constexpr void updateRemoveErase(Container& container, const UnaryPredicate& updateFunWithRemoveCond)
    {
        container.erase(std::remove_if(container.begin(), container.end(), updateFunWithRemoveCond), container.end());
    }
} // namespace utls

#endif
