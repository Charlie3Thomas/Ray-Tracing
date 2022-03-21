#pragma once
#include "config.h"
#include "line.h"

/*
	MATERIAL

	Reflection
		Scatter cone size
		Albedo

	Colour
*/

struct material
{
	colour_t colour;
	floating_point_t roughness;
	floating_point_t albedo;
};