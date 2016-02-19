#pragma once

#include "../CommonUtilities/Vector2.h"

class LineSegment
{
public:
	LineSegment();
	LineSegment(const CommonUtilities::Vector::Vector2<float>& aStartPoint, const CommonUtilities::Vector::Vector2<float>& aEndPoint);
	~LineSegment();

	const CommonUtilities::Vector::Vector2<float>& GetStartPoint() const;
	const CommonUtilities::Vector::Vector2<float>& GetEndPoint() const;

private:
	CommonUtilities::Vector::Vector2<float> myStartPoint;
	CommonUtilities::Vector::Vector2<float> myEndPoint;
};