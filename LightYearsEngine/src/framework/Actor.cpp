#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/PhysicsSystem.h"
#include "framework/World.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: _owningWorld{ owningWorld },
		_hasBeganPlay{ false },
		_sprite{},
		_texture{},
		_physicsBody{nullptr},
		_physicsEnabled{false},
		_teamID{GetNeturalTeamID()}
	{
		SetTexture(texturePath);
	}

	/// Public Functions
	/// -----------------

	/// Void
	void ly::Actor::BeginPlayInternal()
	{
		if (!_hasBeganPlay)
		{
			_hasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
			Tick(deltaTime);
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(_sprite);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmount)
	{
		SetActorLocation(GetActorLocation() + offsetAmount);
	}

	void Actor::AddActorRotationOffset(const float offsetAmount)
	{
		SetActorRotation(GetActorRotation() + offsetAmount);
	}

	/// Override
	void Actor::Destroy()
	{
		UnInitPhysics();
		Object::Destroy();
	}

	/// Virtual
	void Actor::BeginPlay()
	{
		//LOG("Actor began play");
	}

	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor Ticking");
	}

	void Actor::OnBeginActorOverlap(Actor* hitActor)
	{
		//LOG("Actor Overlapped");
	}

	void Actor::OnEndActorOverlap(Actor* hitActor)
	{
		//LOG("Actor End Overlap");
	}

	void
		Actor::ApplyDamage(float amount)
	{

	}

	/// bool
	bool Actor::IsActorOutOfWindowBounds(float allowence) const
	{
		const int windowWidth = GetWorld()->GetWindowSize().x;
		const int windowHeight = GetWorld()->GetWindowSize().y;

		const float actorWidth = GetActorGlobalBounds().width;
		const float actorHeight = GetActorGlobalBounds().height;

		const sf::Vector2f actorPosition = GetActorLocation();

		if (actorPosition.x < - actorWidth - allowence)
			return true;

		if (actorPosition.x > windowWidth + actorWidth + allowence)
			return true;

		if (actorPosition.y < - actorHeight - allowence)
			return true;

		if (actorPosition.y > windowHeight + actorHeight + allowence)
			return true;

		return false;
	}

	bool Actor::IsOtherTeamHostile(Actor* other)
	{
		if (other == nullptr) return false;

		if (GetTeamID() == GetNeturalTeamID() || other->GetTeamID() == GetNeturalTeamID())
			return false;

		return GetTeamID() != other->GetTeamID();
	}

	/// Setters
	void Actor::SetTexture(const std::string& texturePath)
	{
		_texture = AssetManager::Get().LoadTexture(texturePath);

		if (!_texture) return;

		_sprite.setTexture(*_texture);

		int textureWidth = _texture->getSize().x;
		int textureHeight = _texture->getSize().y;
		_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{0, 0}, sf::Vector2i{textureWidth, textureHeight} });
		CenterSpritePivot();
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLocation)
	{
		_sprite.setPosition(newLocation);
		UpddatePhysicsTransform();
	}

	void Actor::SetActorRotation(const float newRotation)
	{
		_sprite.setRotation(newRotation);
		UpddatePhysicsTransform();
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		_physicsEnabled = enable;

		if (_physicsEnabled)
			InitPhysics();
		else
			UnInitPhysics();
	}

	/// Getters
	sf::Vector2f Actor::GetActorLocation() const
	{
		return _sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return _sprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation() - 90.f);
	}

	sf::Vector2f Actor::GetActorForwardRight() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return _owningWorld->GetWindowSize();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return _sprite.getGlobalBounds();
	}

	Actor::~Actor()
	{
		LOG("Actor was destroyed");
	}

	/// Private Functions
	/// -----------------
	void Actor::CenterSpritePivot()
	{
		sf::FloatRect bound = _sprite.getGlobalBounds();
		_sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}

	void Actor::InitPhysics()
	{
		if (!_physicsBody)
			_physicsBody = PhysicsSystem::Get().AddListener(this);
	}

	void Actor::UnInitPhysics()
	{
		if (_physicsBody)
		{
			PhysicsSystem::Get().RemoveListener(_physicsBody);
			_physicsBody = nullptr;
		}
	}

	void Actor::UpddatePhysicsTransform()
	{
		if (_physicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());

			_physicsBody->SetTransform(pos, rotation);
		}
	}
}
