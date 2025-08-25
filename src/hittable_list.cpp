#include <hittable_list.h>

bool HittableList::hit(const Ray3& r, IntervalD t, HitRecord& hr) const
{
  HitRecord tmpHr;
  bool hitAnything = false;
  double closest = t.max;

  for (const auto& hittable : hittables)
  {
    if (hittable->hit(r, Interval(t.min, closest), tmpHr))
    {
      hitAnything = true;
      closest = tmpHr.t;
      hr = tmpHr;
    }
  }

  return hitAnything;
}
