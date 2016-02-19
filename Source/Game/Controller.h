#pragma once

#include "..\CommonUtilities\Vector2.h"
#include "Event.h"

class Actor;

class Controller
{
public:
	Controller();
	virtual ~Controller();
	virtual CommonUtilities::Vector::Vector2<float> GetDirection() = 0;

	void SetParent(Actor* aParent);
	virtual void SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector);
	const CommonUtilities::Vector::Vector2<float>& GetPosition() const;
protected:
	CommonUtilities::Vector::Vector2<float> AvoidWalls();
	CommonUtilities::Vector::Vector2<float> AvoidUnits();
	CommonUtilities::Vector::Vector2<float> AvoidObstacles();

	float mySpeed;
	Actor* myParent;
};