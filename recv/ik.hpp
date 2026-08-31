#ifndef IK_H
#define IK_H
#include <utility>
#include <cmath>

using namespace std;

int inverse_top(float x, float y);

pair<float,float> inverse_side(float x, float y, float a, float b);

#endif