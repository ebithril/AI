#pragma once

#include "../CommonUtilities/StaticArray.h"

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
}

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename T>
		class Vector2;
	}
}

#define INFLUENCE_MAP_RESOLUTION 100

class InfluenceMap
{
public:
	InfluenceMap();
	~InfluenceMap();

	void Init();

	InfluenceMap operator-(const InfluenceMap& aInfluenceMap);
	InfluenceMap operator+(const InfluenceMap& aInfluenceMap);

	const InfluenceMap& operator=(const InfluenceMap& aInfluenceMap);

	void Clear();
	void AddInfluence(const CommonUtilities::Vector::Vector2<float>& aPosition, int aSize, float aIntensity);

	float GetValue(const CommonUtilities::Vector::Vector2<float>& aPosition);

	CommonUtilities::Vector::Vector2<float> GetBestPosition(const CommonUtilities::Vector::Vector2<float>& aPosition, float aRange);

	void Normalize();

	void Render();
	InfluenceMap Abs();

private:
	int VectorToIndex(const CommonUtilities::Vector::Vector2<float>& aPosition);
	CommonUtilities::Containers::StaticArray<float, INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION> myMap;
	CommonUtilities::Containers::StaticArray<bool, INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION> myHasBeenAdded;

	CommonUtilities::Containers::StaticArray<DX2D::CSprite*, INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION> mySprites;
	DX2D::CSpriteBatch* myBatch;
};