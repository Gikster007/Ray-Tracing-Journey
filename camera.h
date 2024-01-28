#pragma once

#include "common.h"

#include "color.h"
#include "hittable.h"

class Camera
{
public:
	// Image
	double aspect_ratio = 1.0;	// Ratio of image width over height
	int image_width = 100;		// Rendered image width in pixel count
	int samples_per_pixel = 10; // Count of random samples for each pixel

	void render(const Hittable& world);

private:
	int    image_height;   // Rendered image height
	point3 center;         // Camera center
	point3 pixel00_loc;    // Location of pixel 0, 0
	vec3   pixel_delta_u;  // Offset to pixel to the right
	vec3   pixel_delta_v;  // Offset to pixel below

	void initialize();

	Ray get_ray(int i, int j) const;

	vec3 pixel_sample_square() const;

	Color ray_color(const Ray& r, const Hittable& world) const;
};