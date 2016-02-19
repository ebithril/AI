#pragma once

#include "../CommonUtilities/GrowingArray.h"
#include "BlackboardInformation.h"

class BlackboardController;

class Blackboard
{
public:
	Blackboard();
	~Blackboard();

	void RegisterExpert(BlackboardController* aExpert);

	void Update();

	const BlackboardInformation& GetSuggestedAction();

	const CommonUtilities::Containers::GrowingArray<BlackboardController*>& GetExperts();
private:
	CommonUtilities::Containers::GrowingArray<BlackboardController*> myExperts;
	BlackboardInformation myMostImportant;
};