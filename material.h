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