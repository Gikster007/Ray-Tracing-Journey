#pragma once

#include "hittable.h"
#include "vec3.h"
#include "interval.h"

class Sphere : public Hittable
{
public:
	Sphere(point3 _center, double _radius);

	bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

private:
	point3 center;
	double radius;
};