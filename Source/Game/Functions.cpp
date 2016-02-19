#include "stdafx.h"
#include "Functions.h"

#include "../CommonUtilities/Vector2.h"
#include "LineSegment.h"

const CommonUtilities::Vector::Vector2<float> GetClosestPointOnLineSegment(const LineSegment& aLine, const CommonUtilities::Vector::Vector2<float>& aPoint)
{
	CommonUtilities::Vector::Vector2<float> AP = aPoint - aLine.GetStartPoint();       //Vector from A to P   
	CommonUtilities::Vector::Vector2<float> AB = aLine.GetEndPoint() - aLine.GetStartPoint();       //Vector from A to B  

	float magnitudeAB = Length2(AB);     //Magnitude of AB vector (it's length squared)     
	float ABAPproduct = Dot(AP, AB);    //The DOT product of a_to_p and a_to_b     
	float distance = ABAPproduct / magnitudeAB; //The normalized "distance" from a to your closest point  

	if (distance < 0)     //Check if P projection is over vectorAB
	{
		return aLine.GetStartPoint();

	}
	else if (distance > 1)
	{
		return aLine.GetEndPoint();
	}
	else
	{
		return aLine.GetStartPoint() + AB * distance;
	}
}

bool LineInsideCircle(const LineSegment& aLine, const CommonUtilities::Vector::Vector2<float>& aCircleCenterPosition, const float aCircleRadius)
{
	CommonUtilities::Vector::Vector2<float> closestPoint = GetClosestPointOnLineSegment(aLine, aCircleCenterPosition);

	return PointInsideCircle(closestPoint, aCircleCenterPosition, aCircleRadius);
}

bool PointInsideCircle(const CommonUtilities::Vector::Vector2<float>& aPoint, const CommonUtilities::Vector::Vector2<float>& aCircleCenterPosition, const float& aCircleRadius)
{
	float lengthBetweenPoints = Length(aCircleCenterPosition - aPoint);

	if (aCircleRadius >= lengthBetweenPoints)
	{
		return true;
	}
	else
	{
		return false;
	}
}