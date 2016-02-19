#include "stdafx.h"
#include "LineSegment.h"

LineSegment::LineSegment()
{
}

LineSegment::LineSegment(const CommonUtilities::Vector::Vector2<float>& aStartPoint, const CommonUtilities::Vector::Vector2<float>& aEndPoint)
{
	myStartPoint = aStartPoint;
	myEndPoint = aEndPoint;
}

LineSegment::~LineSegment()
{
}

const CommonUtilities::Vector::Vector2<float>& LineSegment::GetStartPoint() const
{
	return myStartPoint;
}

const CommonUtilities::Vector::Vector2<float>& LineSegment::GetEndPoint() const
{
	return myEndPoint;
}