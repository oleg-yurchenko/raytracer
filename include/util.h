#pragma once

#include <limits>
#include <numbers>
#include <cstdlib>

// Constants
const double infty = std::numeric_limits<double>::infinity();
using std::numbers::pi;

// Functions
inline double degsToRads(double deg) { return deg*pi / 180.0F; }

// random float from 0 to 1.0
inline double randDouble() { return std::rand() / (RAND_MAX + 1.0F); }

inline double randDouble(double min, double max) { return min + (max-min)*randDouble(); }
