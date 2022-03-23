#include "polygon.h"
#include "sphere.h"
#include "camera.h"
#include "renderer.h"

#include <memory>
#include <fstream>

typedef std::vector<std::unique_ptr<object>> objects_t;

static bool load_objects(objects_t& objects)
{
	// Pushes back a sphere
#if 1
	{
		std::unique_ptr<sphere> obj = std::make_unique<sphere>(5);
		obj->set_centre({ 0.0, 0.0, -70.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	// Pushes back a cow
#if 1
	{
		std::unique_ptr<polygon> obj = std::make_unique<polygon>();
		obj->pgon_colour = SILVER;

		std::fstream fs("cow.obj");
		if (!fs)
			return false;

		fs >> *obj;
		obj->set_centre({ -5.0, 0.0, -50.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	// Pushes back a teapot
#if 1
	{
		std::unique_ptr<polygon> obj = std::make_unique<polygon>();
		obj->pgon_colour = GOLD;

		std::fstream fs("teapot.obj");
		if (!fs)
			return false;

		fs >> *obj;
		obj->set_centre({ 3.0, -3.25, -40.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	// Pushes back an igea head
#if 1
	{
		std::unique_ptr<polygon> obj = std::make_unique<polygon>();
		obj->pgon_colour = GOLD;

		std::fstream fs("igea.obj");
		if (!fs)
			return false;

		fs >> *obj;
		obj->set_centre({ 0.0, 0.0, -1.0 });

		objects.emplace_back(std::move(obj));
	}
#endif

	return true;
}

int main()
{
	timer t("Program");
	// Creates an objects vector and loads it up
	objects_t objects;
	if (!load_objects(objects))
		return 1;

	// Too big to be allocated on the stack
	std::unique_ptr<image_t> img = std::make_unique<image_t>();

	// Camera 
	camera cam1;

	// Does the rendering
	renderer r;
	r.render(objects, *img, cam1);

	// Outputs the rendered PPM
	std::ofstream of("output.ppm");
	of << *img;

	return 0;
}