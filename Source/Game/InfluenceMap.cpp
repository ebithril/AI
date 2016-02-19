#include "stdafx.h"
#include "InfluenceMap.h"

#include "../CommonUtilities/Vector2.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>

#include "Macros.h"

InfluenceMap::InfluenceMap()
{
}

InfluenceMap::~InfluenceMap()
{
}

void InfluenceMap::Init()
{
	myBatch = new DX2D::CSpriteBatch(true);
	myBatch->Init("Sprites/influenceTile.png");

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		myMap[i] = 0;
		myHasBeenAdded[i] = false;
		mySprites[i] = new DX2D::CSprite("Sprites/influenceTile.png");
		mySprites[i]->SetPosition({ float(i / INFLUENCE_MAP_RESOLUTION) / float(INFLUENCE_MAP_RESOLUTION), float(i % INFLUENCE_MAP_RESOLUTION) / float(INFLUENCE_MAP_RESOLUTION) });

		myBatch->AddObject(mySprites[i]);
	}
}

InfluenceMap InfluenceMap::operator-(const InfluenceMap& aInfluenceMap)
{
	InfluenceMap newMap;

	float aMax = 0;
	float aMin = 10;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		newMap.myMap[i] = myMap[i] - aInfluenceMap.myMap[i];

		/*if (newMap.myMap[i] > aMax)
		{
			aMax = newMap.myMap[i];
		}

		if (newMap.myMap[i] < aMin)
		{
			aMin = newMap.myMap[i];
		}*/
	}

	/*float total = aMax - aMin;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		newMap.myMap[i] /= total;
	}*/

	return newMap;
}

InfluenceMap InfluenceMap::operator+(const InfluenceMap& aInfluenceMap)
{
	InfluenceMap newMap;

	float aMax = 0;
	float aMin = 10;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		newMap.myMap[i] = myMap[i] + aInfluenceMap.myMap[i];

		/*if (newMap.myMap[i] > aMax)
		{
		aMax = newMap.myMap[i];
		}

		if (newMap.myMap[i] < aMin)
		{
		aMin = newMap.myMap[i];
		}*/
	}

	/*float total = aMax - aMin;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		newMap.myMap[i] /= total;
	}*/

	return newMap;
}

const InfluenceMap& InfluenceMap::operator=(const InfluenceMap& aInfluenceMap)
{
	myMap = aInfluenceMap.myMap;

	return *this;
}

void InfluenceMap::Clear()
{
	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		myMap[i] = 0;
		myHasBeenAdded[i] = false;
	}
}

void InfluenceMap::AddInfluence(const CommonUtilities::Vector::Vector2<float>& aPosition, int aSize, float aIntensity)
{
	CommonUtilities::Vector::Vector2<float> positionInMap = aPosition * 100.f;

	int index = VectorToIndex(positionInMap);

	myMap[index] += aIntensity;
	myHasBeenAdded[index] = true;

	for (int i = 0; i < aSize; i++)
	{
		CommonUtilities::Vector::Vector2<float> position = positionInMap;
		position.x += i;

		if (position.x >= INFLUENCE_MAP_RESOLUTION)
		{
			break;
		}

		for (int j = 0; j < aSize; j++)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y >= INFLUENCE_MAP_RESOLUTION)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION && myHasBeenAdded[index] == false)
			{
				float length = 1.f - (float(abs(i) * abs(i) + abs(j) * abs(j)) / (float(aSize) * float(aSize)));
				float intensity = aIntensity * (MAX((length), 0.f));
				myMap[index] += intensity;
				myHasBeenAdded[index] = true;
			}
		}

		for (int j = 0; j > -aSize; j--)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y < 0)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION && myHasBeenAdded[index] == false)
			{
				float length = 1.f - (float(abs(i) * abs(i) + abs(j) * abs(j)) / (float(aSize) * float(aSize)));
				float intensity = aIntensity * (MAX((length), 0.f));
				myMap[index] += intensity;
				myHasBeenAdded[index] = true;
			}
		}
	}

	for (int i = 0; i > -aSize; i--)
	{
		CommonUtilities::Vector::Vector2<float> position = positionInMap;
		position.x += i;

		if (position.x < 0)
		{
			break;
		}

		for (int j = 0; j < aSize; j++)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y >= INFLUENCE_MAP_RESOLUTION)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION && myHasBeenAdded[index] == false)
			{
				float length = 1.f - (float(abs(i) * abs(i) + abs(j) * abs(j)) / (float(aSize) * float(aSize)));
				float intensity = aIntensity * (MAX((length), 0.f));
				myMap[index] += intensity;
				myHasBeenAdded[index] = true;
			}
		}

		for (int j = 0; j > -aSize; j--)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y < 0)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION && myHasBeenAdded[index] == false)
			{
				float length = 1.f - (float(abs(i) * abs(i) + abs(j) * abs(j)) / (float(aSize) * float(aSize)));
				float intensity = aIntensity * (MAX((length), 0.f));
				myMap[index] += intensity;
				myHasBeenAdded[index] = true;
			}
		}
	}

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		myHasBeenAdded[i] = false;
	}
}

float InfluenceMap::GetValue(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	return myMap[VectorToIndex(aPosition * 100.f)];
}

CommonUtilities::Vector::Vector2<float> InfluenceMap::GetBestPosition(const CommonUtilities::Vector::Vector2<float>& aPosition, float aRange)
{
	CommonUtilities::Vector::Vector2<float> positionInMap = aPosition * 100.f;

	int range = int(aRange * 100);

	float bestValue = 0;

	int index;

	CommonUtilities::Vector::Vector2<float> bestPos = { 0.5f, 0.5f };

	for (int i = 0; i < range; i++)
	{
		CommonUtilities::Vector::Vector2<float> position = positionInMap;
		position.x += i;

		if (position.x >= INFLUENCE_MAP_RESOLUTION)
		{
			break;
		}

		for (int j = 0; j < range; j++)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y >= INFLUENCE_MAP_RESOLUTION)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && range < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION)
			{
				float length = CommonUtilities::Vector::Length(aPosition - (position / 100.f));
				float value = myMap[index] / length;
				
				if (value > bestValue)
				{
					bestValue = value;
					bestPos = (position / 100.f);
				}
			}
		}

		for (int j = 0; j > -range; j--)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y < 0)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION)
			{
				float length = CommonUtilities::Vector::Length(aPosition - (position / 100.f));
				float value = myMap[index] / length;

				if (value > bestValue)
				{
					bestValue = value;
					bestPos = (position / 100.f);
				}
			}
		}
	}

	for (int i = 0; i > -range; i--)
	{
		CommonUtilities::Vector::Vector2<float> position = positionInMap;
		position.x += i;

		if (position.x < 0)
		{
			break;
		}

		for (int j = 0; j < range; j++)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y >= INFLUENCE_MAP_RESOLUTION)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION)
			{
				float length = CommonUtilities::Vector::Length(aPosition - (position / 100.f));
				float value = myMap[index] / length;

				if (value > bestValue)
				{
					bestValue = value;
					bestPos = (position / 100.f);
				}
			}
		}

		for (int j = 0; j > -range; j--)
		{
			position.y = positionInMap.y;
			position.y += j;

			if (position.y < 0)
			{
				break;
			}

			index = VectorToIndex(position);

			if (index >= 0 && index < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION)
			{
				float length = CommonUtilities::Vector::Length(aPosition - (position / 100.f));
				float value = myMap[index] / length;

				if (value > bestValue)
				{
					bestValue = value;
					bestPos = (position / 100.f);
				}
			}
		}
	}

	return bestPos;
}

void InfluenceMap::Normalize()
{
	float aMax = 0;
	float aMin = 10;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		if (myMap[i] > aMax)
		{
			aMax = myMap[i];
		}

		if (myMap[i] < aMin)
		{
			aMin = myMap[i];
		}
	}

	float total = aMax - aMin;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		myMap[i] /= total;
	}
}

void InfluenceMap::Render()
{
	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		if (myMap[i] >= 0)
		{
			mySprites[i]->SetColor({ myMap[i], 0, 0, 1 });
		}
		else
		{
			mySprites[i]->SetColor({ 0, 0, abs(myMap[i]), 1 });
		}
	}

	myBatch->Render(true);
}

InfluenceMap InfluenceMap::Abs()
{
	InfluenceMap newMap;

	for (int i = 0; i < INFLUENCE_MAP_RESOLUTION * INFLUENCE_MAP_RESOLUTION; i++)
	{
		newMap.myMap[i] = abs(myMap[i]);
	}

	return newMap;
}

int InfluenceMap::VectorToIndex(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	return int(int(aPosition.x) * INFLUENCE_MAP_RESOLUTION + int(aPosition.y));
}