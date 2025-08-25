#pragma once

#include <limits>
#include <numbers>

// Constants
const double infty = std::numeric_limits<double>::infinity();
using std::numbers::pi;

// Functions
inline double degsToRads(double deg) { return deg*pi / 180.0F; }
