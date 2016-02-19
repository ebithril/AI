#pragma once

#include <tga2d/math/vector2.h>
#include "../CommonUtilities/Vector2.h"

#include <tga2d/math/vector4.h>
#include "../CommonUtilities/Vector4.h"

DX2D::Vector2f ConvertToDXD2DVector(const CommonUtilities::Vector::Vector2<float>& aVector)
{
	return{ aVector.x, aVector.y };
}
DX2D::Vector4f ConvertToDXD2DVector(const CommonUtilities::Vector::Vector4<float>& aVector)
{
	return{ aVector.x, aVector.y, aVector.z, aVector.w };
}
