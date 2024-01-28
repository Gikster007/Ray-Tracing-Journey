#include <iostream>
#include <chrono>

#include "hittable-list.h"
#include "sphere.h"
#include "camera.h"

int main()
{
	// World
	HittableList world;
	world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

	// Camera
	Camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.samples_per_pixel = 10;

	auto start_time = std::chrono::high_resolution_clock::now();
	cam.render(world);
	auto end_time = std::chrono::high_resolution_clock::now();
	double render_time_us = static_cast<double>((end_time - start_time).count()) / 1000.0;
	double render_time_ms = render_time_us / 1000.0;
	double render_time_s = render_time_ms / 1000.0;

	std::clog << render_time_s << "\n";
}