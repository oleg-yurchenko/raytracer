#pragma once

#include <util.h>

template<typename T>
class Interval
{
public:
  T min, max;

  Interval()
    : min(T(+infty))
    , max(T(-infty))
  {}

  Interval(T min, T max)
    : min(min)
    , max(max)
  {}
  ~Interval() = default;

  T    size() const { return max - min; }
  bool contains(T x) const { return x >= min && x <= max; }
  bool surrounds(T x) const { return x > min && x < max; }

  double clamp(double x) const { return x < min ? min : x > max ? max : x; }
};

typedef Interval<double> IntervalD;
