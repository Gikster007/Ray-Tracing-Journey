#include "camera.h"

#include "vec3.h"

void Camera::render(const Hittable& world)
{
	initialize();

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)
		{
			Color pixel_color(0, 0, 0);
			for (int sample = 0; sample < samples_per_pixel; ++sample)
			{
				Ray r = get_ray(i, j);
				pixel_color += ray_color(r, max_depth, world);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::clog << "\rDone.                    \n";
}

void Camera::initialize()
{
	image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	center = point3(0, 0, 0);

	// Determine viewport dimensions
	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

	// Calculate the vectors across the horizontal and down the vertical viewport edges
	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel
	vec3 viewport_upper_left =
		center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray Camera::get_ray(int i, int j) const
{
	// Get a randomly sampled camera ray for the pixel at location i,j
	
	point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
	point3 pixel_sample = pixel_center + pixel_sample_square();

	vec3 ray_origin = center;
	vec3 ray_direction = pixel_sample - ray_origin;

	return Ray(ray_origin, ray_direction);
}

vec3 Camera::pixel_sample_square() const
{
	// Returns a random point in the square surrounding a pixel at the origin.
	double px = -0.5 + random_double();
	double py = -0.5 + random_double();
	return (px * pixel_delta_u) + (py * pixel_delta_v);
}

Color Camera::ray_color(const Ray& r, int depth, const Hittable& world) const
{
	HitRecord rec;

	// If we've exceeded the ray bounce limit, no more light is gathered
	if (depth <= 0)
		return Color(0, 0, 0);

	if (world.hit(r, Interval(0.001, infinity), rec))
	{
		vec3 direction = rec.normal + vec3::random_unit_vector();
		return 0.5 * ray_color(Ray(rec.p, direction), depth - 1, world);
	}

	vec3 unit_direction = vec3::unit_vector(r.direction());
	double a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
