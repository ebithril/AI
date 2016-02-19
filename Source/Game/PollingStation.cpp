#include "stdafx.h"
#include "PollingStation.h"

PollingStation* PollingStation::ourInstance = nullptr;

PollingStation::PollingStation()
{
	myActors.Init(4);
	myObstacles.Init(4);
	myControlPoints.Init(4);
}

PollingStation::~PollingStation()
{
}

PollingStation* PollingStation::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new PollingStation();
	}

	return ourInstance;
}

void PollingStation::AddActor(Actor* aActor)
{
	myActors.Add(aActor);
}

void PollingStation::RemoveActor(Actor* aActor)
{
	myActors.RemoveCyclic(aActor);
}

CommonUtilities::Containers::GrowingArray<Actor*>& PollingStation::GetActors()
{
	return myActors;
}

void PollingStation::AddObstacle(Obstacle* aObstacle)
{
	myObstacles.Add(aObstacle);
}

CommonUtilities::Containers::GrowingArray<Obstacle*>& PollingStation::GetObstacles()
{
	return myObstacles;
}

void PollingStation::AddControlPoint(ControlPoint* aControlPoint)
{
	myControlPoints.Add(aControlPoint);
}

CommonUtilities::Containers::GrowingArray<ControlPoint*>& PollingStation::GetControlPoints()
{
	return myControlPoints;
}