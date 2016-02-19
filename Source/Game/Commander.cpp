#include "stdafx.h"
#include "Commander.h"

#include "Actor.h"

#include "Arrive.h"

#include "ControlPoint.h"
#include "PollingStation.h"

#include "Macros.h"
#include <random>

Commander::Commander()
{
	myActors.Init(128);

	myColor = { RANDOM_FLOAT(0.f, 1.f), RANDOM_FLOAT(0.f, 1.f), RANDOM_FLOAT(0.f, 1.f), 1.f };

	mySpawnTimer = 0;
}

Commander::~Commander()
{
}

void Commander::Init()
{
	myInfluence.Init();
	myDifference.Init();
	myTensionMap.Init();
	vulnerabilityMap.Init();
	myGoalMap.Init();
}

void Commander::Render()
{
	for (Actor* actor : myActors)
	{
		actor->Render();
	}
}

InfluenceMap& Commander::GetInfluenceMap()
{
	return myInfluence;
}

InfluenceMap& Commander::GetDifference()
{
	return myDifference;
}

InfluenceMap& Commander::GetTension()
{
	return myTensionMap;
}

InfluenceMap& Commander::GetVulnerability()
{
	return vulnerabilityMap;
}

void Commander::SetFaction(eFaction aFaction)
{
	myFaction = aFaction;
}

void Commander::SetGameWorld(CGameWorld* aGameWorld)
{
	myGameWorld = aGameWorld;
}

void Commander::SetOpponent(Commander* aOpponent)
{
	myOpponent = aOpponent;
}

void Commander::Update(float aDeltaTime)
{
	mySpawnTimer -= aDeltaTime;

	if (mySpawnTimer <= 0)
	{
		mySpawnTimer = 5;

		CommonUtilities::Containers::GrowingArray<ControlPoint*>& controlPoints = PollingStation::GetInstance()->GetControlPoints();

		float maxValue = 0;
		ControlPoint* targetPoint = nullptr;

		for (int i = 0; i < controlPoints.Size(); i++)
		{
			float value = (-myDifference.GetValue(controlPoints[i]->GetPosition()) + vulnerabilityMap.GetValue(controlPoints[i]->GetPosition())) / (CommonUtilities::Vector::Length(controlPoints[i]->GetPosition() - myStartPosition) * 1000.f);

			if (value >= maxValue)
			{
				targetPoint = controlPoints[i];
				maxValue = value;
			}
		}

		myActors.Add(new Actor());

		myActors.GetLast()->SetController(new Arrive());
		myActors.GetLast()->SetPosition(myStartPosition);

		if (targetPoint != nullptr)
		{
			myActors.GetLast()->GetController()->SetTargetPosition(targetPoint->GetPosition());
		}
		else
		{
			myActors.GetLast()->GetController()->SetTargetPosition({ 0.5f, 0.5f });
		}

		myActors.GetLast()->SetColor(myColor);
		myActors.GetLast()->SetFaction(myFaction);
		myActors.GetLast()->SetGameWorld(myGameWorld);
	}

	myInfluence.Clear();
	myGoalMap.Clear();

	for (int i = 0; i < myActors.Size(); i++)
	{
		/*CommonUtilities::Containers::GrowingArray<ControlPoint*>& controlPoints = PollingStation::GetInstance()->GetControlPoints();

		float maxValue = 0;
		ControlPoint* targetPoint = nullptr;

		for (int i = 0; i < controlPoints.Size(); i++)
		{
		float value = (-myDifference.GetValue(controlPoints[i]->GetPosition()) + vulnerabilityMap.GetValue(controlPoints[i]->GetPosition())) / (CommonUtilities::Vector::Length(controlPoints[i]->GetPosition() - myStartPosition) * 1000.f);

		if (value >= maxValue)
		{
		targetPoint = controlPoints[i];
		maxValue = value;
		}
		}

		if (targetPoint != nullptr)
		{
		myActors[i]->GetController()->SetTargetPosition(targetPoint->GetPosition());
		}
		else
		{
		myActors[i]->GetController()->SetTargetPosition({ 0.5f, 0.5f });
		}
		*/
		myActors[i]->GetController()->SetTargetPosition(myFinalMap.GetBestPosition(myActors[i]->GetPosition(), 0.2f));

		myActors[i]->Update(aDeltaTime);

		myInfluence.AddInfluence(myActors[i]->GetPosition(), 20, 0.1f);

		if (myActors[i]->GetHealth() <= 0)
		{
			PollingStation::GetInstance()->RemoveActor(myActors[i]);
			myActors.RemoveCyclicAtIndex(i);
			--i;
		}
	}

	CommonUtilities::Containers::GrowingArray<ControlPoint*>& controlPoints = PollingStation::GetInstance()->GetControlPoints();

	for (ControlPoint* controlPoint : controlPoints)
	{
		if (controlPoint->GetFaction() == myFaction)
		{
			myGoalMap.AddInfluence(controlPoint->GetPosition(), 25, 0.2f);
		}
		else
		{
			if (controlPoint->GetFaction() == eFaction::NEUTRAL)
			{
				myGoalMap.AddInfluence(controlPoint->GetPosition(), 25, 1.f);
			}
			else
			{
				myGoalMap.AddInfluence(controlPoint->GetPosition(), 25, 0.5f);
			}
		}
	}

	/*myGoalMap.Normalize();
	myInfluence.Normalize();*/

	myDifference = myInfluence - myOpponent->myInfluence;
	//myTensionMap = myDifference + myGoalMap;
	myTensionMap = myInfluence + myOpponent->myInfluence + myGoalMap;
	myTensionMap.Normalize();
	//myTensionMap = myGoalMap + myDifference.Abs();

	vulnerabilityMap = myTensionMap - myDifference.Abs();
	vulnerabilityMap.Normalize();

	myFinalMap = vulnerabilityMap - myDifference;
}

void Commander::SetStartPosition(const CommonUtilities::Vector::Vector2<float>& aStartPosition)
{
	myStartPosition = aStartPosition;
}