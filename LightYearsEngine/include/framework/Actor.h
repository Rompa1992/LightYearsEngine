#pragma once 

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

	class b2Body;

namespace ly
{
	class World;																										// CodeExplanations->When to Forward Declare vs Include

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmount);
		void AddActorRotationOffset(const float offsetAmount);

		virtual void Destroy() override;

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void OnBeginActorOverlap(Actor* hitActor);
		virtual void OnEndActorOverlap(Actor* hitActor);
		virtual void ApplyDamage(float amount);

		bool IsActorOutOfWindowBounds(float allowence = 200) const;
		bool IsOtherTeamHostile(Actor* other);

		void SetTexture(const std::string& texturePath);
		void SetActorLocation(const sf::Vector2f& newLocation);
		void SetActorRotation(const float newRotation);
		void SetEnablePhysics(bool enable);
		void SetTeamID(uint8 teamID) { _teamID = teamID; }

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		const sf::Sprite& GetSprite() const { return _sprite; }
		sf::Sprite& GetSprite() { return _sprite; }
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorForwardRight() const;
		sf::Vector2u GetWindowSize() const;
		sf::FloatRect GetActorGlobalBounds() const;
		const World* GetWorld() const { return _owningWorld; }	
		World* GetWorld() { return _owningWorld; }
		uint8 GetTeamID() const { return _teamID; }
		static uint8 GetNeturalTeamID() { return _neturalTeamID; }

		virtual ~Actor();
	private:
		void CenterSpritePivot();																								// called in SetTexture();
		void InitPhysics();
		void UnInitPhysics();
		void UpddatePhysicsTransform();
		
		World* _owningWorld;
		bool _hasBeganPlay;

		sf::Sprite _sprite;
		shared_ptr<sf::Texture> _texture;
		
		b2Body* _physicsBody;
		bool _physicsEnabled;

		uint8 _teamID;
		const static uint8 _neturalTeamID = 255;

	};
}