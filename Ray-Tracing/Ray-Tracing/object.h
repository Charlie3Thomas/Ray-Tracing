#pragma once

#include "config.h"

#include <optional>

class object
{
public:
	virtual ~object() = default;

	struct hit_info
	{
		hit_info() = default;
		hit_info(const colour_t& col)
			:colour(col) {}
		hit_info(const colour_t& col_, floating_point_t z_)
			:colour(col_), z(z_) {}
		hit_info(const colour_t& col_, floating_point_t z_, const ray_t& ray_)
			:colour(col_), z(z_), next_ray(ray_) {}
		~hit_info() = default;

		floating_point_t z;
		floating_point_t albedo;
		colour_t colour;
		ray_t next_ray;
	};

	virtual std::optional<hit_info> get_hit_info(const ray_t& ray) const = 0;

	virtual void set_centre(const spacial_t& centre) { _centre = centre; }
	const spacial_t& get_centre() const { return _centre; }

protected:
	spacial_t _centre{ 0, 0, 0 };
};