#include "GirderSize.h"
#include "Math.h"
#include "ObjectSizes.h"

float GirderSize::getGirderWidthMeters(int size, int angle){
	angle = GirderSize::normalizeAngle(angle);
	return Math::cosDegrees(angle) * size +
				Math::sinDegrees(angle) * girder_height;
}

int GirderSize::getGirderWidthPixels(int size, int angle){
	return SCALE_FACTOR * GirderSize::getGirderWidthMeters(size, angle);
}

float GirderSize::getGirderHeightMeters(int size, int angle){
	angle = GirderSize::normalizeAngle(angle);
	return Math::sinDegrees(angle) * size +
				Math::cosDegrees(angle) * girder_height;
}

int GirderSize::getGirderHeightPixels(int size, int angle){
	return SCALE_FACTOR * GirderSize::getGirderHeightMeters(size, angle);
}

int GirderSize::normalizeAngle(int angle){
	return angle > 90 ? 180 - angle : angle;
}
