#include "stdafx.h"
#include "BlackboardController.h"

#include "Blackboard.h"
#include "Actor.h"

#include "Functions.h"
#include "LineSegment.h"

#include "PollingStation.h"
#include "Obstacle.h"

#include <tga2d/engine.h>
#include <tga2d/drawers/debug_drawer.h>

BlackboardController::BlackboardController() : Controller()
{
	myStartPosition = { -1.f, -1.f };

	myEnemyPositions.Init(4);
}

BlackboardController::~BlackboardController()
{
}

CommonUtilities::Vector::Vector2<float> BlackboardController::GetDirection()
{
	CommonUtilities::Vector::Vector2<float> steeringOutput = AvoidObstacles() + AvoidUnits() + AvoidWalls() + CommonUtilities::Vector::GetNormalized(GetBlackboardSteering()) * mySpeed * 1.02f;

	if (CommonUtilities::Vector::Length(steeringOutput) > mySpeed)
	{
		steeringOutput = CommonUtilities::Vector::GetNormalized(steeringOutput) * mySpeed;
	}

	return steeringOutput;
}

void BlackboardController::SetBlackboard(Blackboard* aBlackboard)
{
	myBlackboard = aBlackboard;
}

void BlackboardController::SetOtherBlackboard(Blackboard* aBlackboard)
{
	myOtherBlackboard = aBlackboard;
}

CommonUtilities::Vector::Vector2<float> BlackboardController::GetBlackboardSteering()
{
	const BlackboardInformation& suggestedAction = myBlackboard->GetSuggestedAction();

	if (myEnemyPositions.Size() > 0)
	{
		Shoot();
	}

	switch (suggestedAction.myCommand)
	{
	case eBlackboardCommand::ADVANCE:
		return AdvanceCommand(suggestedAction);
		break;
	case eBlackboardCommand::NEED_SUPPORT:
		return NeedSupportCommand(suggestedAction);
		break;
	case eBlackboardCommand::FOUND_ENEMY:
		return FoundEnemyCommand(suggestedAction);
		break;
	case eBlackboardCommand::FLANKING:
		return FlankingCommand(suggestedAction);
		break;
	case eBlackboardCommand::NOTHING:
		return { 0, 0 };
		break;
	default:
		break;
	}

	return { 1, 1 };
}

void BlackboardController::CalcSuggestedAction()
{
	const BlackboardInformation& suggestedAction = myBlackboard->GetSuggestedAction();
	
	switch (suggestedAction.myCommand)
	{
	case eBlackboardCommand::ADVANCE:
		CheckAllExceptAdvance();
		break;
	case eBlackboardCommand::NEED_SUPPORT:
		mySuggestedAction.myCommand = eBlackboardCommand::NOTHING;
		mySuggestedAction.myExpert = this;
		CheckFoundEnemyAndSupport();
		break;
	case eBlackboardCommand::FOUND_ENEMY:
		CheckFoundEnemyAndSupport();
		break;
	case eBlackboardCommand::FLANKING:
		CheckFoundEnemyAndSupport();
		break;
	case eBlackboardCommand::NOTHING:
		CheckAllCommands();
		break;
	default:
		break;
	}
}

void BlackboardController::CheckAllCommands()
{
	CheckNeedSupport();

	if (mySuggestedAction.myCommand == eBlackboardCommand::NEED_SUPPORT)
	{
		return;
	}

	CheckFoundEnemy();

	if (mySuggestedAction.myCommand == eBlackboardCommand::FOUND_ENEMY)
	{
		return;
	}

	CheckFlanking();

	if (mySuggestedAction.myCommand == eBlackboardCommand::FLANKING)
	{
		return;
	}

	mySuggestedAction.myCommand = eBlackboardCommand::ADVANCE;
}

void BlackboardController::CheckAllExceptAdvance()
{
	CheckNeedSupport();

	if (mySuggestedAction.myCommand == eBlackboardCommand::NEED_SUPPORT)
	{
		return;
	}

	CheckFoundEnemy();

	if (mySuggestedAction.myCommand == eBlackboardCommand::FOUND_ENEMY)
	{
		return;
	}

	CheckFlanking();
}

void BlackboardController::CheckNeedSupport()
{

}

void BlackboardController::CheckFoundEnemyAndSupport()
{
	CheckNeedSupport();

	if (mySuggestedAction.myCommand == eBlackboardCommand::NEED_SUPPORT)
	{
		return;
	}

	CheckFoundEnemy();
}

void BlackboardController::CheckFoundEnemy()
{
	const CommonUtilities::Containers::GrowingArray<BlackboardController*>& experts = myOtherBlackboard->GetExperts();

	CommonUtilities::Containers::GrowingArray<Obstacle*>& obstacles = PollingStation::GetInstance()->GetObstacles();

	for (const BlackboardController* expert : experts)
	{
		LineSegment line(myParent->GetPosition(), expert->GetPosition());

		bool isBlocked = false;
		for (Obstacle* obstacle : obstacles)
		{
			if (LineInsideCircle(line, obstacle->GetPosition(), 0.02f) == true)
			{
				isBlocked = true;
			}
		}

		if (isBlocked == false)
		{
			DX2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ expert->GetPosition().x, expert->GetPosition().y }, { myParent->GetPosition().x, myParent->GetPosition().y });

			myEnemyPositions.Add(expert->GetPosition());
		}
	}

	if (myEnemyPositions.Size() > 0)
	{
		mySuggestedAction.myCommand = eBlackboardCommand::FOUND_ENEMY;
	}
}

void BlackboardController::CheckFlanking()
{
	mySuggestedAction.myCommand = eBlackboardCommand::FLANKING;
}

CommonUtilities::Vector::Vector2<float> BlackboardController::AdvanceCommand(const BlackboardInformation& someBlackboardInfo)
{
	if (myStartPosition.y > 0.5f)
	{
		return { 1.f, -1.f };
	}
	else
	{
		return { -1.f, 1.f };
	}
}

CommonUtilities::Vector::Vector2<float> BlackboardController::NeedSupportCommand(const BlackboardInformation& someBlackboardInfo)
{
	if (someBlackboardInfo.myExpert == this)
	{
		const CommonUtilities::Containers::GrowingArray<BlackboardController*>& experts = myBlackboard->GetExperts();

		CommonUtilities::Vector::Vector2<float> direction = { 0, 0 };

		for (const BlackboardController* expert : experts)
		{
			if (expert != this)
			{
				direction += expert->GetPosition() - myParent->GetPosition();
			}
		}

		return CommonUtilities::Vector::GetNormalized(direction);
	}
	else
	{
		return CommonUtilities::Vector::GetNormalized(someBlackboardInfo.myExpert->GetPosition() - myParent->GetPosition());
	}
}

CommonUtilities::Vector::Vector2<float> BlackboardController::FoundEnemyCommand(const BlackboardInformation& someBlackboardInfo)
{
	if (someBlackboardInfo.myExpert == this)
	{
		CommonUtilities::Vector::Vector2<float> direction = { 0, 0 };

		for (const CommonUtilities::Vector::Vector2<float>& enemyPosition : myEnemyPositions)
		{
			direction += enemyPosition - myParent->GetPosition();
		}

		return CommonUtilities::Vector::GetNormalized(direction);
	}
	else
	{
		const CommonUtilities::Containers::GrowingArray<CommonUtilities::Vector::Vector2<float>>& enemyPositions = someBlackboardInfo.myExpert->GetEnemyPositions();

		CommonUtilities::Vector::Vector2<float> direction = { 0, 0 };

		for (const CommonUtilities::Vector::Vector2<float>& enemyPosition : enemyPositions)
		{
			direction += enemyPosition - myParent->GetPosition();
		}

		return CommonUtilities::Vector::GetNormalized(direction);
	}
}

CommonUtilities::Vector::Vector2<float> BlackboardController::FlankingCommand(const BlackboardInformation& someBlackboardInfo)
{
	if (someBlackboardInfo.myExpert == this)
	{
		if (myStartPosition.y > 0.5f)
		{
			if (myParent->GetPosition().x < 0.3f)
			{
				return { 1.f, 0.f };
			}
			else
			{
				return { 0.f, -1.f };
			}
		}
		else
		{
			if (myParent->GetPosition().x < 0.7f)
			{
				return{ -1.f, 0.f };
			}
			else
			{
				return{ 0.f, 1.f };
			}
		}
	}
	else
	{
		return AdvanceCommand(someBlackboardInfo);
	}
}

void BlackboardController::Shoot()
{
	CommonUtilities::Vector::Vector2<float> closest = myEnemyPositions[0] - myParent->GetPosition();

	for (int i = 1; i < myEnemyPositions.Size(); i++)
	{
		if (CommonUtilities::Vector::Length2(closest) > CommonUtilities::Vector::Length2(myEnemyPositions[i] - myParent->GetPosition()))
		{
			closest = myEnemyPositions[i] - myParent->GetPosition();
		}
	}

	myParent->Shoot(myParent->GetPosition(), closest);
}

const BlackboardInformation& BlackboardController::GetSuggestedAction()
{
	myEnemyPositions.RemoveAll();

	if (myStartPosition.x = -1.f)
	{
		myStartPosition = myParent->GetPosition();
	}

	mySuggestedAction.myCommand = eBlackboardCommand::NOTHING;
	mySuggestedAction.myExpert = this;

	CalcSuggestedAction();

	switch (mySuggestedAction.myCommand)
	{
	case eBlackboardCommand::ADVANCE:
		mySuggestedAction.myInsistance = 1;
		break;
	case eBlackboardCommand::NEED_SUPPORT:
		mySuggestedAction.myInsistance = 10;
		break;
	case eBlackboardCommand::FOUND_ENEMY:
		mySuggestedAction.myInsistance = 5;
		break;
	case eBlackboardCommand::FLANKING:
		mySuggestedAction.myInsistance = 3;
		break;
	case eBlackboardCommand::NOTHING:
		mySuggestedAction.myInsistance = 0;
		break;
	default:
		mySuggestedAction.myInsistance = 0;
		break;
	}

	return mySuggestedAction;
}

const CommonUtilities::Containers::GrowingArray<CommonUtilities::Vector::Vector2<float>>& BlackboardController::GetEnemyPositions() const
{
	return myEnemyPositions;
}