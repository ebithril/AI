#pragma once

class LineSegment;

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename T>
		class Vector2;
	}
}

const CommonUtilities::Vector::Vector2<float> GetClosestPointOnLineSegment(const LineSegment& aLine, const CommonUtilities::Vector::Vector2<float>& aPoint);

bool LineInsideCircle(const LineSegment& aLine, const CommonUtilities::Vector::Vector2<float>& aCircleCenterPosition, const float aCircleRadius);

bool PointInsideCircle(const CommonUtilities::Vector::Vector2<float>& aPoint, const CommonUtilities::Vector::Vector2<float>& aCircleCenterPosition, const float& aCircleRadius);