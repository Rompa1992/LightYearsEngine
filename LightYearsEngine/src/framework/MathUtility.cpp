#include "framework/MathUtility.h"

namespace ly
{
	constexpr float PI = 3.1415926535f;

	sf::Vector2f RotationToVector(const float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	inline float DegreesToRadians(const float degrees)
	{
		return degrees * (PI / 180.f);
	}

	inline float RadiansToDegrees(const float radians)
	{
		return radians * (180.f / PI);
	}
}