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
	static void render(const objects_t& objects, image_t& img, const camera& cam);

private:


};