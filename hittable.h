#pragma once

#include "ray.h"

struct HitRecord
{
	point3 p;
	vec3 normal;
	double t;
	bool front_face;

	void set_face_normal(const Ray& r, const vec3& outward_normal)
	{
		// Sets the hit record normal vector
		// NOTE: the parameter 'outward_normal' is assumed to have unit length (normalised)

		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord rec) const = 0;
};