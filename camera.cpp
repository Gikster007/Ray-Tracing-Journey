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

	center = lookfrom;

	// Determine viewport dimensions
	double theta = degrees_to_radians(fov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h * focus_dist;
	double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame
	w = vec3::unit_vector(lookfrom - lookat);
	u = vec3::unit_vector(vec3::cross(up, w));
	v = vec3::cross(w, u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges
	vec3 viewport_u = viewport_width * u;	// Vector across viewport horizontal edge
	vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

	// Calculate the horizontal and vertical delta vectors from pixel to pixel
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel
	vec3 viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// Calculate the camera defocus disk basis vectors
	double defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
	defocus_disk_u = u * defocus_radius;
	defocus_disk_v = v * defocus_radius;
}

Ray Camera::get_ray(int i, int j) const
{
	// Get a randomly-sampled camera ray for the pixel at location i,j, originating from
	// the camera defocus disk
	
	point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
	point3 pixel_sample = pixel_center + pixel_sample_square();

	vec3 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
	vec3 ray_direction = pixel_sample - ray_origin;

	return Ray(ray_origin, ray_direction);
}

point3 Camera::defocus_disk_sample() const {
	// Returns a random point in the camera defocus disk.
	vec3 p = p.random_in_unit_disk();
	return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
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
		Ray scattered;
		Color attenuation;
		if (rec.mat->scatter(r, rec, attenuation, scattered))
		{
			Color rc = ray_color(scattered, depth - 1, world);
			return Color(attenuation.x() * rc.x(), attenuation.y() * rc.y(), attenuation.z() * rc.z());
		}
		return Color(0, 0, 0);
	}

	vec3 unit_direction = vec3::unit_vector(r.direction());
	double a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}
