#include "stdafx.h"
#include "Blackboard.h"

#include "BlackboardController.h"

Blackboard::Blackboard()
{
	myExperts.Init(4);
}

Blackboard::~Blackboard()
{
}

void Blackboard::RegisterExpert(BlackboardController* aExpert)
{
	myExperts.Add(aExpert);
	aExpert->SetBlackboard(this);
}

void Blackboard::Update()
{
	BlackboardInformation highestPrio;
	highestPrio.myCommand = eBlackboardCommand::NOTHING;
	highestPrio.myExpert = nullptr;
	highestPrio.myInsistance = 0;
	
	myMostImportant = highestPrio;

	for (BlackboardController* expert : myExperts)
	{
		const BlackboardInformation& info = expert->GetSuggestedAction();

		if (info.myInsistance > highestPrio.myInsistance)
		{
			highestPrio = info;
		}
	}

	myMostImportant = highestPrio;
}

const BlackboardInformation& Blackboard::GetSuggestedAction()
{
	return myMostImportant;
}

const CommonUtilities::Containers::GrowingArray<BlackboardController*>& Blackboard::GetExperts()
{
	return myExperts;
}
