#include "framework/MathUtility.h"

namespace ly
{
	const float PI = 3.1415926535;

	sf::Vector2f RotationToVector(float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float DegreesToRadians(float degrees)
	{
		float radians = degrees * (PI / 180.f);
		return radians;
	}

	float RadiansToDegrees(float radians)
	{
		float degrees = radians * (180.f / PI);
		return degrees;
	}
}