#pragma once

#include "../CommonUtilities/GrowingArray.h"
#include "../CommonUtilities/Vector2.h"
#include "../CommonUtilities/Vector4.h"
#include "Faction.h"

#include "InfluenceMap.h"

class Actor;
class CGameWorld;

class Commander
{
public:
	Commander();
	~Commander();

	void Init();

	void SetStartPosition(const CommonUtilities::Vector::Vector2<float>& aStartPosition);

	void Update(float aDeltaTime);
	void Render();
	InfluenceMap& GetInfluenceMap();
	InfluenceMap& GetDifference();
	InfluenceMap& GetTension();
	InfluenceMap& GetVulnerability();

	void SetFaction(eFaction aFaction);

	void SetGameWorld(CGameWorld* aGameWorld);

	void SetOpponent(Commander* aOpponent);
private:
	CommonUtilities::Containers::GrowingArray<Actor*> myActors;
	CommonUtilities::Vector::Vector4<float> myColor;
	CommonUtilities::Vector::Vector2<float> myStartPosition;
	eFaction myFaction;
	float mySpawnTimer;

	InfluenceMap myInfluence;
	InfluenceMap myDifference;
	InfluenceMap myTensionMap;
	InfluenceMap vulnerabilityMap;
	InfluenceMap myGoalMap;
	InfluenceMap myFinalMap;

	Commander* myOpponent;

	CGameWorld* myGameWorld;
};