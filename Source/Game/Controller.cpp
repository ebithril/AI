#include "stdafx.h"
#include "Controller.h"

#include "Actor.h"

#include "../CommonUtilities/GrowingArray.h"
#include "Obstacle.h"
#include "PollingStation.h"

#define WALL_AVOID_DISTANCE 0.1f
#define UNIT_AVOID_DISTANCE 0.05f
#define OBSTACLE_AVOID_DISTANCE 0.06f

Controller::Controller()
{
	mySpeed = 0.01f;
}

Controller::~Controller()
{
}

void Controller::SetParent(Actor* aParent)
{
	myParent = aParent;
}

void Controller::SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector)
{
}

const CommonUtilities::Vector::Vector2<float>& Controller::GetPosition() const
{
	return myParent->GetPosition();
}

CommonUtilities::Vector::Vector2<float> Controller::AvoidWalls()
{
	CommonUtilities::Vector::Vector2<float> position = myParent->GetPosition();
	CommonUtilities::Vector::Vector2<float> direction = { 0, 0 };

	if (position.y <= WALL_AVOID_DISTANCE)
	{
		direction.y += ((1.f - position.y) / WALL_AVOID_DISTANCE);
	}
	if (position.y >= 1 - WALL_AVOID_DISTANCE)
	{
		direction.y += ((1.f - (1.f - position.y)) / WALL_AVOID_DISTANCE) * -1.f;
	}

	if (position.x <= WALL_AVOID_DISTANCE)
	{
		direction.x += ((1.f - position.x) / WALL_AVOID_DISTANCE);
	}
	if (position.x >= 1 - WALL_AVOID_DISTANCE)
	{
		direction.x += ((1.f - (1.f - position.x)) / WALL_AVOID_DISTANCE) * -1.f;
	}

	if (direction.x != 0 || direction.y != 0)
	{
		CommonUtilities::Vector::Normalize(direction);
	}

	return direction * mySpeed;
}

CommonUtilities::Vector::Vector2<float> Controller::AvoidUnits()
{
	CommonUtilities::Containers::GrowingArray<Actor*>& actors = PollingStation::GetInstance()->GetActors();

	CommonUtilities::Vector::Vector2<float> result = { 0, 0 };

	for (Actor* actor : actors)
	{
		if (actor != myParent)
		{
			CommonUtilities::Vector::Vector2<float> direction = myParent->GetPosition() - actor->GetPosition();

			if (CommonUtilities::Vector::Length2(direction) <= UNIT_AVOID_DISTANCE * UNIT_AVOID_DISTANCE)
			{
				result += CommonUtilities::Vector::GetNormalized(direction) * (1 - (CommonUtilities::Vector::Length(direction) / UNIT_AVOID_DISTANCE));
			}
		}
	}

	if (result.x != 0 || result.y != 0)
	{
		CommonUtilities::Vector::Normalize(result);
	}

	result *= mySpeed;

	return result;
}

CommonUtilities::Vector::Vector2<float> Controller::AvoidObstacles()
{
	CommonUtilities::Containers::GrowingArray<Obstacle*>& obstacles = PollingStation::GetInstance()->GetObstacles();

	CommonUtilities::Vector::Vector2<float> result = { 0, 0 };

	for (Obstacle* obstacle : obstacles)
	{
		CommonUtilities::Vector::Vector2<float> direction = myParent->GetPosition() - obstacle->GetPosition();

		if (CommonUtilities::Vector::Length2(direction) <= OBSTACLE_AVOID_DISTANCE * OBSTACLE_AVOID_DISTANCE)
		{
			result += CommonUtilities::Vector::GetNormalized(direction) * (1 - (CommonUtilities::Vector::Length(direction) / OBSTACLE_AVOID_DISTANCE));
		}
	}

	if (result.x != 0 || result.y != 0)
	{
		CommonUtilities::Vector::Normalize(result);
	}

	result *= mySpeed;

	return result;
}