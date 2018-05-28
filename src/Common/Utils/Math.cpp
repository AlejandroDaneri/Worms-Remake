#include "Math.h"
#include <cmath>

const float PI = 3.14159265;

float Math::degreesToRadians(int angle){
	return angle * PI / 180;
}

int Math::radiansToDegrees(float angle){
	return angle * 180 / PI;
}

float Math::cosDegrees(int angle){
	return cos(Math::degreesToRadians(angle));
}

float Math::sinDegrees(int angle){
	return sin(Math::degreesToRadians(angle));
}