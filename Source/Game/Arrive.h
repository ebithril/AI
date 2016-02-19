#pragma once
#include "Controller.h"

class Arrive : public Controller
{
public:
	Arrive();
	~Arrive();

	CommonUtilities::Vector::Vector2<float> GetDirection() override;

	void SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector) override;
private:
	CommonUtilities::Vector::Vector2<float> ArriveDirection();

	CommonUtilities::Vector::Vector2<float> myTargetPosition;
};