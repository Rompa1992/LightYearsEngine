#include "framework/MathUtility.h"
#include <random>

namespace ly
{
	/// Vectors
	constexpr float PI = 3.1415926535f;

	inline float DegreesToRadians(const float degrees)
	{
		return degrees * (PI / 180.f);
	}

	inline float RadiansToDegrees(const float radians)
	{
		return radians * (180.f / PI);
	}

	sf::Vector2f RotationToVector(const float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	/// Lerps
	float LerpFloat(float a, float b, float alpha)
	{ 
		if (alpha > 1) alpha = 1;
		if (alpha < 0) alpha = 0;

		return a + (b - a) * alpha;
	}

	sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha)
	{
		int lerpR = LerpFloat(a.r, b.r, alpha);
		int lerpG = LerpFloat(a.g, b.g, alpha);
		int lerpB = LerpFloat(a.b, b.b, alpha);
		int lerpA = LerpFloat(a.a, b.a, alpha);

		return sf::Color(lerpR, lerpG, lerpB, lerpA);
	}
	sf::Vector2f LerpVectorFloat(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
	{
		float lerpX = LerpFloat(a.x, b.x, alpha);
		float lerpY = LerpFloat(a.y, b.y, alpha);

		return sf::Vector2f(lerpX, lerpY);
	}

	/// Random
	float RandomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distribution{ min, max };

		return distribution(gen);
	}

	sf::Vector2f RandomUnitVector()
	{
		float randomX = RandomRange(-1, 1);
		float randomY = RandomRange(-1, 1);

		sf::Vector2f randomVector{ randomX, randomY };

		NormalizeVector(randomVector);

		return randomVector;
	}
}