#include "stdafx.h"
#include "ControlPoint.h"
#include <tga2d/sprite/sprite.h>

ControlPoint::ControlPoint()
{
	myFaction = eFaction::NEUTRAL;
}

ControlPoint::~ControlPoint()
{
}

void ControlPoint::Init()
{
	mySprite = new DX2D::CSprite("Sprites/ControlPoint.png");
	mySprite->SetPivot({ 0.5f, 0.5f });
	myFaction = eFaction::NEUTRAL;
}

void ControlPoint::SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition({ aPosition.x, aPosition.y });
}

const CommonUtilities::Vector::Vector2<float>& ControlPoint::GetPosition()
{
	return myPosition;
}

const CommonUtilities::Vector::Vector2<float>& ControlPoint::GetPosition() const
{
	return myPosition;
}

void ControlPoint::SetFaction(eFaction aFaction)
{
	myFaction = aFaction;
}

void ControlPoint::SetColor(const CommonUtilities::Vector::Vector4<float>& aColor)
{
	CommonUtilities::Vector::Vector4<float> color = aColor * 0.5f;
	mySprite->SetColor({ color.x, color.y, color.z, aColor.w });
}

void ControlPoint::Render()
{
	mySprite->Render();
}

eFaction ControlPoint::GetFaction()
{
	return myFaction;
}
