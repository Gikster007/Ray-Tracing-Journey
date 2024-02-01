#include <iostream>
#include <chrono>

#include "hittable-list.h"
#include "sphere.h"
#include "color.h"
#include "material.h"
#include "camera.h"

int main()
{
	// World
	HittableList world;

	shared_ptr<Lambertian> material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	shared_ptr<Lambertian> material_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	shared_ptr<Metal> material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.0);
	shared_ptr<Metal> material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.5);

	world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	// Camera
	Camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	auto start_time = std::chrono::high_resolution_clock::now();
	cam.render(world);
	auto end_time = std::chrono::high_resolution_clock::now();
	double render_time_us = static_cast<double>((end_time - start_time).count()) / 1000.0;
	double render_time_ms = render_time_us / 1000.0;
	double render_time_s = render_time_ms / 1000.0;

	std::clog << render_time_s << "\n";
}