#include <sphere.h>

bool Sphere::hit(const Ray3& r, IntervalD t, HitRecord& hr) const
{
  Direction3 oc = center - r.origin();
  double a = r.direction().lengthSquared();
  double h = r.direction() * oc;
  double c = oc.lengthSquared() - radius*radius;
  double disc = h*h - a*c;
  
  if (disc < 0.0F)
    return false;

  double sqrtd = std::sqrt(disc);

  // Find the nearest root that lies in the acceptable range
  double root = (h - sqrtd) / a;
  if (!t.surrounds(root))
  {
    root = (h + sqrtd) / a;
    if (!t.surrounds(root))
      return false;
  }

  hr.t = root;
  hr.p = r.at(hr.t);
  Direction3 normal = (hr.p - center) * (1.0F/radius);
  hr.setFaceNormal(r, normal);

  return true;
}
