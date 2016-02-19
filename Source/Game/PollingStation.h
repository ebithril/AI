#pragma once

#include "..\CommonUtilities\GrowingArray.h"

class Actor;
class Obstacle;
class ControlPoint;

class PollingStation
{
public:
	static PollingStation* GetInstance();

	void AddActor(Actor* aActor);
	void RemoveActor(Actor* aActor);
	CommonUtilities::Containers::GrowingArray<Actor*>& GetActors();

	void AddObstacle(Obstacle* aObstacle);
	CommonUtilities::Containers::GrowingArray<Obstacle*>& GetObstacles();

	void AddControlPoint(ControlPoint* aControlPoint);
	CommonUtilities::Containers::GrowingArray<ControlPoint*>& GetControlPoints();
private:
	PollingStation();
	~PollingStation();

	static PollingStation* ourInstance;

	CommonUtilities::Containers::GrowingArray<Actor*> myActors;
	CommonUtilities::Containers::GrowingArray<Obstacle*> myObstacles;
	CommonUtilities::Containers::GrowingArray<ControlPoint*> myControlPoints;
};