#include "stdafx.h"
#include "Bullet.h"

#include <tga2d/sprite/sprite.h>

Bullet::Bullet()
{
	mySpeed = 0.2f;
	myLifeTime = 5.f;
	mySprite = nullptr;
}

Bullet::~Bullet()
{
}

void Bullet::Init(const CommonUtilities::Vector::Vector2<float>& aPosition, const CommonUtilities::Vector::Vector2<float>& aDirection)
{
	myPosition = aPosition;
	myDirection = CommonUtilities::Vector::GetNormalized(aDirection);
	mySprite = new DX2D::CSprite("Sprites/Bullet.png");
	mySprite->SetPivot({ 0.5f, 0.5f });
}

void Bullet::Update(float aDeltaTime)
{
	myLifeTime -= aDeltaTime;

	myPosition += myDirection * mySpeed * aDeltaTime;

	mySprite->SetPosition({ myPosition.x, myPosition.y });
}

void Bullet::Render()
{
	mySprite->Render();
}

void Bullet::SetIsDead()
{
	myLifeTime = 0;
}

void Bullet::SetFaction(eFaction aFaction)
{
	myFaction = aFaction;
}

bool Bullet::GetIsDead()
{
	return myLifeTime <= 0;
}

eFaction Bullet::GetFaction()
{
	return myFaction;
}

const CommonUtilities::Vector::Vector2<float>& Bullet::GetPosition()
{
	return myPosition;
}
