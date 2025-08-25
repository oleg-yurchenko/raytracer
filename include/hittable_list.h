#pragma once

#include <hittable.h>
#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
  std::vector<std::shared_ptr<Hittable>> hittables;

  HittableList() {}
  HittableList(std::shared_ptr<Hittable> ht) { add(ht); }

  inline void clear() { hittables.clear(); }

  inline void add(std::shared_ptr<Hittable> ht) { hittables.push_back(ht); }
  
  bool hit(const Ray3& r, IntervalD t, HitRecord& hr) const override;
};

