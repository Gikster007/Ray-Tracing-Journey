#include "sphere.h"

bool Sphere::hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec)
{
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;

    double discrimnant = half_b * half_b - a * c;
    if (discrimnant < 0)
        return false;
    double sqrtd = sqrt(discrimnant);

    // Find the nearest root that lies in the acceptable range;
    double root = (-half_b - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root)
    {
        root = (-half_b + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
