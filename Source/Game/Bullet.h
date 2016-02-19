#pragma once

#include "../CommonUtilities/Vector2.h"

#include "Faction.h"

namespace DX2D
{
	class CSprite;
}

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init(const CommonUtilities::Vector::Vector2<float>& aPosition, const CommonUtilities::Vector::Vector2<float>& aDirection);
	void Update(float aDeltaTime);
	void Render();

	void SetIsDead();

	void SetFaction(eFaction aFaction);

	bool GetIsDead();
	eFaction GetFaction();
	const CommonUtilities::Vector::Vector2<float>& GetPosition();
private:
	CommonUtilities::Vector::Vector2<float> myPosition;
	CommonUtilities::Vector::Vector2<float> myDirection;

	eFaction myFaction;

	float myLifeTime;
	float mySpeed;
	DX2D::CSprite* mySprite;
};