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

    shared_ptr<Lambertian> ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).lenght() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    Color rand1 = Color::random();
                    Color rand2 = Color::random();
                    Color albedo = Color(rand1.x() * rand2.x(), rand1.y() * rand2.y(), rand1.z() * rand2.z());
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    Color albedo = Color::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    shared_ptr<Dielectric> material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    shared_ptr<Lambertian> material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    shared_ptr<Metal> material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	// Camera
	Camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 600;
	cam.samples_per_pixel = 500;
	cam.max_depth = 50;

	cam.fov = 20;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.up = vec3(0, 1, 0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;

	auto start_time = std::chrono::high_resolution_clock::now();
	cam.render(world);
	auto end_time = std::chrono::high_resolution_clock::now();
	double render_time_us = static_cast<double>((end_time - start_time).count()) / 1000.0;
	double render_time_ms = render_time_us / 1000.0;
	double render_time_s = render_time_ms / 1000.0;

	std::clog << render_time_s << "\n";
}