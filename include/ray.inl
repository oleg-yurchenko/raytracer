#define RAY_3 Ray<Point3, Direction3>
#define POINT_3 Point3

template<>
inline POINT_3 RAY_3::at(double t) const
{
  return orig + dir*t;
}
