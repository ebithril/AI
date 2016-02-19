#pragma once

#include "BlackboardCommand.h"

class BlackboardController;

struct BlackboardInformation
{
public:
	eBlackboardCommand myCommand;
	BlackboardController* myExpert;
	int myInsistance;
};