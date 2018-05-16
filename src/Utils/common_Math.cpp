#include "math_utils.h"
#include <cmath>

const float PI = 3.14159265;

float Math::degrees_to_radians(int angle){
	return angle * PI / 180;
}

int Math::radians_to_degrees(float angle){
	return angle * 180 / PI;
}

float Math::cos_degrees(int angle){
	return cos(Math::degrees_to_radians(angle));
}

float Math::sin_degrees(int angle){
	return sin(Math::degrees_to_radians(angle));
}