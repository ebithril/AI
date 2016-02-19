#pragma once
#include "Controller.h"

#include "BlackboardInformation.h"
#include "../CommonUtilities/GrowingArray.h"

class Blackboard;

class BlackboardController : public Controller
{
public:
	BlackboardController();
	~BlackboardController();

	CommonUtilities::Vector::Vector2<float> GetDirection() override;

	void SetBlackboard(Blackboard* aBlackboard);
	void SetOtherBlackboard(Blackboard* aBlackboard);

	const BlackboardInformation& GetSuggestedAction();

	const CommonUtilities::Containers::GrowingArray<CommonUtilities::Vector::Vector2<float>>& GetEnemyPositions() const;
private:
	CommonUtilities::Vector::Vector2<float> GetBlackboardSteering();

	void CalcSuggestedAction();
	void CheckAllCommands();
	void CheckAllExceptAdvance();
	void CheckNeedSupport();
	void CheckFoundEnemyAndSupport();
	void CheckFoundEnemy();
	void CheckFlanking();

	CommonUtilities::Vector::Vector2<float> AdvanceCommand(const BlackboardInformation& someBlackboardInfo);
	CommonUtilities::Vector::Vector2<float> NeedSupportCommand(const BlackboardInformation& someBlackboardInfo);
	CommonUtilities::Vector::Vector2<float> FoundEnemyCommand(const BlackboardInformation& someBlackboardInfo);
	CommonUtilities::Vector::Vector2<float> FlankingCommand(const BlackboardInformation& someBlackboardInfo);
	void Shoot();
	CommonUtilities::Vector::Vector2<float> myStartPosition;

	BlackboardInformation mySuggestedAction;

	CommonUtilities::Containers::GrowingArray<CommonUtilities::Vector::Vector2<float>> myEnemyPositions;

	Blackboard* myBlackboard;
	Blackboard* myOtherBlackboard;
};
