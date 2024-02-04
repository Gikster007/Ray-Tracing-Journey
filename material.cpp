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

Dielectric::Dielectric(double index_of_refraction)
{
	ir = index_of_refraction;
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);
	double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

	vec3 unit_direction = vec3::unit_vector(r_in.direction());
	double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	vec3 direction;

	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
		direction = vec3::reflect(unit_direction, rec.normal);
	else
		direction = vec3::refract(unit_direction, rec.normal, refraction_ratio);

	scattered = Ray(rec.p, direction);
	return true;
}
