#pragma once

#include <cmath>
#include <array>
#include <iostream>

namespace unstd 
{
    template <typename _T, size_t _S>
    struct vector : std::array<_T, _S>
    {
        // Quality-of-life overloads
        bool operator==(const vector& v) const { return std::equal(this->begin(), this->end(), v.begin()); }
        bool operator!=(const vector& v) const { return !(*this == v); }

        // Arithmatic overloads
        const vector& operator+() const { return *this; }
        constexpr vector operator-() const { return _T(- 1) * vector<_T, _S>(*this); }
        vector& operator*=(const _T& t) { for (auto& i : *this) i *= t; return *this; }
        vector& operator/=(const _T& t) { for (auto& i : *this) i /= t; return *this; }
        vector& operator+=(const vector& v) { for (size_t i = 0; i < _S; i++) (*this)[i] += v[i]; return *this; }
        vector& operator-=(const vector& v) { return operator+=(-v); }

        // Floating-point-specific methods
        _T length() const { return std::sqrt(square_length()); }
        _T square_length() const { _T ret = 0; for (const auto& i : *this) ret += i * i; return ret; }
        _T inverse_length() const { return 1.0 / length(); }

        vector& normalise() { return operator*=(inverse_length()); }
    };

    // Non-member arithmatic overloads
    template <typename _T, size_t _S>
    constexpr vector<_T, _S> operator+(const vector<_T, _S>& v, const vector<_T, _S>& w)
    {
        vector<_T, _S> ret;
        for (size_t i = 0; i < _S; i++) ret[i] = v[i] + w[i];
        return ret;
    }

    template <typename _T, size_t _S>
    constexpr vector<_T, _S> operator-(const vector<_T, _S>& v, const vector<_T, _S>& w)
    {
        return v + (-w);
    }

    template <typename _T, size_t _S>
    constexpr vector<_T, _S> operator*(const _T& t, const vector<_T, _S>& v)
    {
        vector<_T, _S> ret;
        for (size_t i = 0; i < _S; i++) ret[i] = t*v[i];
        return ret;
    }

    template <typename _T, size_t _S>
    constexpr vector<_T, _S> operator/(const vector<_T, _S>& v, const _T& t)
    {
        return (_T(1.0) / t)*v;
    }

#include <concepts>

    template <typename _T, size_t _S, typename _F>
    requires std::floating_point<_F>
    constexpr vector<_T, _S> operator*(const vector<_T, _S>& v, const _F& t)
    {
        vector<_T, _S> ret;
        for (size_t i = 0; i < _S; i++)
            ret[i] = _T(_F(v[i]*t));

        return ret;
    }

    // Dot, cross, and triple product
    template <typename _T, size_t _S>
    constexpr _T dot_product(const vector<_T, _S>& v, const vector<_T, _S>& w)
    {
        _T ret = 0;
        for (size_t i = 0; i < _S; i++) ret += v[i] * w[i];
        return ret;
    }

    template <typename _T, size_t _S>
    constexpr vector<_T, _S> cross_product(const vector<_T, _S>& v, const vector<_T, _S>& w)
    {
        static_assert(_S == 3,"The cross product is only defined in three dimensions");
        return { v[1] * w[2] - v[2] * w[1], v[2] * w[0] - v[0] * w[2], v[0] * w[1] - v[1] * w[0] };
    }

    template <typename _T, size_t _S>
    constexpr _T scalar_triple_product(const vector<_T, _S>& v, const vector<_T, _S>& w, const vector<_T, _S>& u)
    {
        return unstd::dot_product(v, unstd::cross_product(w, u));
    }

    // Ostream overload
    template <typename _T, size_t _S>
    std::ostream& operator<<(std::ostream& os, const vector<_T, _S>& v)
    {
        if constexpr (std::is_integral<_T>::value)
            for (const auto& i : v) os << (int) i << " ";
        else
            for (const auto& i : v) os << i << " ";

        return os;
    }
}