#include "renderer.h"

static colour_t colour_blend(const colour_t col1, const colour_t col2, floating_point_t albedo)
{
	const colour_t colour1 = col1 * (1 - albedo);
	const colour_t colour2 = col2 * albedo;

	//std::cout << colour1 << " " << colour2;

	return colour1 + colour2;
}

static colour_t multi_sampled_pixel_colour(const objects_t& objects, const ray_t& ray, size_t depth)
{
	// Default pixel colour BLACK
	colour_t ret = BLACK;

	if (depth > MAX_SCATTER_DEPTH)
	{
		return ret;
	}

	std::optional<object::hit_info> pixel;

	// Sample ray intersect colour based on Z order
	for (const auto& object : objects)
	{
		const auto h_i = object->get_hit_info(ray);
		if (h_i.has_value() &&
			(!pixel.has_value() ||
				pixel.value().z > h_i.value().z))
		{
			// Set colour of pixel in image to h_i.value().colour
			pixel = h_i.value();
		}
	}

	if (pixel.has_value())
	{
		ret =
			colour_blend(pixel.value().colour, multi_sampled_pixel_colour(objects, pixel.value().next_ray, ++depth), 0.8);
			//pixel.value().colour * 0.5 +			
			//multi_sampled_pixel_colour(objects, pixel.value().next_ray, ++depth) * 0.5;
	}

	return ret;
}

void renderer::render(const objects_t& objects, image_t& img, const camera& cam)
{
	timer t("Render");
	std::cout << "Starting render loop..." << std::endl;

	// Render loop
	for (size_t height = 0; height < IMAGE_HEIGHT; height++)
	{
		size_t x = (float(height) / IMAGE_HEIGHT) * 100;
		std::cout << "Render loop is " << x << " % complete." << "\r";

		//std::cout << h << std::endl;
		for (size_t width = 0; width < IMAGE_WIDTH; width++)
		{
			const floating_point_t u = floating_point_t(width) / floating_point_t(IMAGE_WIDTH - 1);
			const floating_point_t v = floating_point_t(height) / floating_point_t(IMAGE_HEIGHT - 1);
			ray_t ray(
				cam.getOrigin(),
				cam.getLLC() + u *
				cam.getHorizontal() + v *
				cam.getVertical() - cam.getOrigin());

			ray.direction.normalise();			

			img[IMAGE_WIDTH * height + width] = multi_sampled_pixel_colour(objects, ray, 0);
		}
	}

	std::cout << "Render loop is 100% complete.\r" << std::endl;
}