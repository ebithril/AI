#include "stdafx.h"
#include "Arrive.h"

#include "Actor.h"

#define SLOW_RADIUS	0.05f

Arrive::Arrive()
{
	myTargetPosition = { 0.5f, 0.5f };
}

Arrive::~Arrive()
{
}

CommonUtilities::Vector::Vector2<float> Arrive::GetDirection()
{
	CommonUtilities::Vector::Vector2<float> direction = AvoidObstacles() + AvoidUnits() + AvoidWalls() + ArriveDirection() * 1.1f;

	if (CommonUtilities::Vector::Length(direction) > mySpeed)
	{
		CommonUtilities::Vector::Normalize(direction);
		direction *= mySpeed;
	}

	return direction;
}

void Arrive::SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector)
{
	myTargetPosition = aVector;
}

CommonUtilities::Vector::Vector2<float> Arrive::ArriveDirection()
{
	CommonUtilities::Vector::Vector2<float> position = myParent->GetPosition();

	CommonUtilities::Vector::Vector2<float> direction = myTargetPosition - position;

	if (direction.x == 0 && direction.y == 0)
	{
		return direction;
	}

	if (CommonUtilities::Vector::Length2(direction) <= SLOW_RADIUS * SLOW_RADIUS)
	{
		direction = GetNormalized(direction) * mySpeed * (CommonUtilities::Vector::Length(direction) / SLOW_RADIUS);
	}
	else
	{
		direction = GetNormalized(direction) * mySpeed;
	}

	return direction;
}