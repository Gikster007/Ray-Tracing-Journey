#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
	Sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

	bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec);

private:
	point3 center;
	double radius;
};