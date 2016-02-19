#pragma once

#include "Bullet.h"
#include "Blackboard.h"

#include "../CommonUtilities/StaticArray.h"
#include "../CommonUtilities/GrowingArray.h"

#include "../CommonUtilities/InputWrapper.h"

#include "Commander.h"
#include "ControlPoint.h"

#define NUMBER_OF_ACTORS 6
#define NUMBER_OF_OBSTACLES 49
#define NUMBER_OF_CONTROL_POINTS 3

enum class eRenderMode
{
	DEFAULT,
	TEAM_ONE_INFLUENCE,
	TEAM_TWO_INFLUENCE,
	TEAM_ONE_DIFFERENCE,
	TEAM_TWO_DIFFERENCE,
	TEAM_ONE_GOAL,
	TEAM_TWO_GOAL,
	TEAM_ONE_TENSION,
	TEAM_TWO_TENSION,
	TEAM_ONE_VULNERABILITY,
	TEAM_TWO_VULNERABILITY,
};

class Actor;
class Obstacle;

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
	void SpawnBullet(const CommonUtilities::Vector::Vector2<float>& aPosition, const CommonUtilities::Vector::Vector2<float> aDirection, eFaction aFaction);
private:
	//CommonUtilities::Containers::StaticArray<Actor*, NUMBER_OF_ACTORS> myActors;
	//CommonUtilities::Containers::StaticArray<Obstacle*, NUMBER_OF_OBSTACLES> myObstacles;
	//
	//CommonUtilities::Containers::StaticArray<Blackboard, 2> myBlackboards;

	eRenderMode myRenderMode;
	CommonUtilities::Containers::StaticArray<Commander*, 2> myCommanders;
	CommonUtilities::Containers::StaticArray<ControlPoint, NUMBER_OF_CONTROL_POINTS> myControlPoints;
	CommonUtilities::Containers::GrowingArray<Bullet> myBullets;
	CommonUtilities::InputWrapper* myInputWrapper;
};