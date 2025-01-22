#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
		/// Vectors
		inline float DegreesToRadians(const float degrees);
		inline float RadiansToDegrees(const float radians);
		sf::Vector2f RotationToVector(const float rotation);

		template<typename T>
		float GetVectorLength(const sf::Vector2<T>& vector)
		{
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		template<typename T>
		sf::Vector2<T>& NormalizeVector(sf::Vector2<T>& vectorToNormalize)
		{
			float vectorLength = GetVectorLength<T>(vectorToNormalize);

			if (vectorLength == 0.f)
				return vectorToNormalize;																					// Return the original vector if length is 0

			float scaleFactor = 1.f / vectorLength; 
			vectorToNormalize.x *= scaleFactor;
			vectorToNormalize.y *= scaleFactor;

			return vectorToNormalize;
		}

		/// Lerps
		float LerpFloat(float a, float b, float alpha);
		sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);
		sf::Vector2f LerpVectorFloat(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

		/// Random
		float RandomRange(float min, float max);
		sf::Vector2f RandomUnitVector();

}
