#pragma once

#include "vector.h"

namespace unstd
{
	template <typename _T, size_t _S>
	struct line
	{
		line() = default;
		line(const unstd::vector<_T, _S>& origin_, const unstd::vector<_T, _S>& direction_)
			: origin(origin_), direction(direction_) {}

		typedef unstd::vector<_T, _S> spacial_t;

		spacial_t operator[](const _T& t) const { return origin + t*direction; }

		spacial_t origin;
		spacial_t direction;
	};
}