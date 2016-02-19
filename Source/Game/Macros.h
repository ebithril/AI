#pragma once

#include <random>

#define RANDOM_FLOAT(aMax, aMin) ((float(rand()) / float(RAND_MAX)) * (float(aMax) - float(aMin))) + float(aMin)

#define MAX(a, b) (a) > (b) ? (a) : (b)
