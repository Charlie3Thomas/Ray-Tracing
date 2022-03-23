#include "sphere.h"

sphere::sphere(floating_point_t radius_)
	: radius(radius_)
{

}

std::optional<object::hit_info> sphere::get_hit_info(const ray_t& ray) const
{
	std::optional<hit_info> ret;

	const spacial_t oc = _centre - ray.origin;
	const floating_point_t oc_dot_direction = unstd::dot_product(oc, ray.direction);
	const floating_point_t l_sqrd = oc.square_length() - std::pow(oc_dot_direction, 2);

	if (l_sqrd > std::pow(radius, 2))
	{
		return ret;
	}

	const floating_point_t alignment = l_sqrd / std::pow(radius, 2);
	const floating_point_t z = std::sqrt(std::pow(radius, 2) - l_sqrd);
	const floating_point_t t = oc_dot_direction - z;
	if (t < EPSILON)
	{
		return ret;
	}

	const spacial_t intersect = ray[t];

	const spacial_t normal = intersect - _centre;

	ray_t scattered_ray(intersect, ray.direction - 2.0 * unstd::dot_product(normal, ray.direction) * normal);

	scattered_ray.direction.normalise();

	return hit_info(RED * std::cos(3.14159265359 * std::sqrt(alignment) / 2), (intersect - ray.origin).length(), scattered_ray);
}