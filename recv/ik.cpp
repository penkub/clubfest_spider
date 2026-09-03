
#include<utility>
#include "ik.hpp"
#include <cmath>

using namespace std;

int inverse_top(float x, float y){
  float tan_value = y/x;
  return(atan(tan_value)*(180/M_PI));
}

pair<float,float> inverse_side(float x, float y, float a, float b){
  float c = sqrt(pow(x,2)+pow(y,2));
  float angle_a_c = acos((pow(a,2)-pow(b,2)+pow(c,2))/(2*c*a))*(180/M_PI);//compare to the middle one and use -90 - 90
  float angle_a_b = acos((pow(a,2)-pow(c,2)+pow(b,2))/(2*a*b))*(180/M_PI);//use value 0 - 180 na krub ee
  float angle_c_horizon = asin(y/c)*(180/M_PI);
  float angle_a_horizon = angle_a_c+angle_c_horizon;
  return make_pair(angle_a_horizon,angle_a_b);
}