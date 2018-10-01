#pragma once

#include<random>
#include<math.h>
#include"vector2.h"

namespace bear { namespace core {

	/*
	All of these interval functions assume max > min
	@ TODO: code a robust error checking for all max/min scenarios
	*/

	static int randomIntegerInterval(int min, int max) {
		int range = (max - min);
		int x = rand() % range;
		return (min + x);
	}

	static float randomFloatZeroToOne()
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return x;
	}

	static float randomFloatInterval(float min, float max) {
		float x = randomFloatZeroToOne();
		float range = max - min;
		return (range*x) + min;
	}

#define PI 3.14159265

	static Vector2f randomPointInsideUnitCircle() {
		float randomAngle = randomFloatInterval(0, 2 * PI);
		return Vector2f(cos(randomAngle), sin(randomAngle));
	}

	static Vector2f randomPointInsideCircle(float radius) {
		float randomRadius = randomFloatInterval(1, radius);
		Vector2f point = randomPointInsideUnitCircle();
		point = point * randomRadius;
		return point;
	}
} }