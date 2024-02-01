#pragma once

#include "ray.h"
#include "interval.h"

#include "material.h"

struct HitRecord
{
	point3 p;
	vec3 normal;
	shared_ptr<Material> mat;
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

	virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};