#pragma once

#include "object.h"

class sphere : public object
{
public:
	sphere(floating_point_t radius_);

	std::optional<hit_info> get_hit_info(const ray_t& ray) const override;
	
	const floating_point_t radius;
};