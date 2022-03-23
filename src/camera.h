#pragma once
#include "config.h"

class camera
{
public:
	camera() = default;
	camera(
		spacial_t orig,
		spacial_t hori,
		spacial_t vert)
		:	origin(orig),
			horizontal(hori),
			vertical(vert)
	{
		lower_left_corner = 
			origin - horizontal / floating_point_t(2.0) - 
			vertical / floating_point_t(2.0) - 
			spacial_t({ 0, 0, focal_length });
	}

	~camera() = default;

	spacial_t getOrigin() const { return origin; }
	spacial_t getHorizontal() const { return horizontal; }
	spacial_t getVertical () const { return vertical; }
	spacial_t getLLC() const { return lower_left_corner; }

private:

	floating_point_t cam_height = floating_point_t(2.0);
	floating_point_t cam_width = ASPECT_RATIO * cam_height;
	floating_point_t focal_length = floating_point_t(10.0);

	// Default camera position.
	spacial_t origin = { 0, 0, 0 };
	spacial_t horizontal = { cam_width, 0, 0 };
	spacial_t vertical = { 0 , cam_height, 0 };
	spacial_t lower_left_corner = origin - horizontal / floating_point_t(2.0) - vertical / floating_point_t(2.0) - spacial_t({ 0, 0, focal_length });
};



