#pragma once

#include "vec3.h"

using point3 = vec3;

class Ray
{
private:
	point3 orig;
	vec3 dir;

public:
	Ray() {}
	Ray(const vec3& origin, const vec3& direction);

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }
};