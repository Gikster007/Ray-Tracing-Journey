#pragma once

#include "common.h"
#include "color.h"

class HitRecord;

class Material
{
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Color& a);

	bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
};

class Metal : public Material
{
public:
	Metal(const Color& a, double f);

	bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
	double fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(double index_of_refraction);

	bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	double ir; // Index of refraction

	static double reflectance(double cosine, double ref_idx)
	{
		// Use Schlick's approximation for reflectance
		double r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};