#pragma once

#include "common.h"

#include "color.h"
#include "hittable.h"

class Camera
{
public:
	// Image
	double aspect_ratio = 1.0;
	int image_width = 100;

	void Render(const Hittable& world);

private:
	int    image_height;   // Rendered image height
	point3 center;         // Camera center
	point3 pixel00_loc;    // Location of pixel 0, 0
	vec3   pixel_delta_u;  // Offset to pixel to the right
	vec3   pixel_delta_v;  // Offset to pixel below

	void initialize();

	Color ray_color(const Ray& r, const Hittable& world) const;
};