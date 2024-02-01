#include "material.h"

#include "hittable.h"

Lambertian::Lambertian(const Color& a)
{
	albedo = a;
}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	vec3 scatter_direction = rec.normal + vec3::random_unit_vector();

	// Catch degenerate scatter direction
	if (scatter_direction.near_zero())
		scatter_direction = rec.normal;

	scattered = Ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}

Metal::Metal(const Color& a, double f)
{
	albedo = a;
	fuzz = f < 1 ? f : 1;
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	vec3 reflected = vec3::reflect(vec3::unit_vector(r_in.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + fuzz * vec3::random_unit_vector());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}
