#pragma once

#include <cmath>
#include <type_traits>

namespace unstd
{
	template <typename _T>
	constexpr _T pow(const _T& a, const _T& b)
	{
		static_assert(std::is_unsigned<_T>::value, "The type must be an unsigned integral");

		_T ret = 1;
		for (size_t i = 0; i < b; i++) ret *= a;
		return ret;
	}


	template <typename _T>
	constexpr _T unsigned_max() 
	{
		return pow<_T>(2, 8 * sizeof(_T)) - 1; 
	}
}