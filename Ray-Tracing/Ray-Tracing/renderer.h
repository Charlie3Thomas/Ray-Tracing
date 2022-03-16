#pragma once
#include "config.h"
#include "camera.h"
#include "object.h"
#include "timer.h"

typedef std::vector<std::unique_ptr<object>> objects_t;

class renderer
{
public:
	renderer() = default;
	~renderer() = default;

	static void render(const objects_t& objects, image_t& img, const camera cam)
	{
		timer t("Render");
		std::cout << "Starting render loop..." << std::endl;

		// Render loop
		for (size_t h = 0; h < IMAGE_HEIGHT; h++)
		{
			//std::cout << h << std::endl;
			for (size_t w = 0; w < IMAGE_WIDTH; w++)
			{
				const floating_point_t u = floating_point_t(w) / floating_point_t(IMAGE_WIDTH - 1);
				const floating_point_t v = floating_point_t(h) / floating_point_t(IMAGE_HEIGHT - 1);
				const ray_t ray(cam.getOrigin(), cam.getLLC() + u * cam.getHorizontal() + v * cam.getVertical() - cam.getOrigin());

				img[IMAGE_WIDTH * h + w] = WHITE;
				for (const auto& object : objects)
				{
					std::optional<colour_t> colour = object->get_colour(ray);
					if (colour.has_value())
					{
						img[IMAGE_WIDTH * h + w] = colour.value();
						break;
					}

				}
			}
		}

		std::cout << "Render finished." << std::endl;
	}



private:
};

static void render(const objects_t& objects, image_t& img, const camera cam)
{
	
}