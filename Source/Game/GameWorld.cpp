#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/text/text.h>
#include <tga2d/primitives/custom_shape.h>
#include <tga2d/math/color.h>

#include "BlackboardController.h"

#include "Actor.h"
#include "Obstacle.h"
#include "Macros.h"

#include "PollingStation.h"

#include <time.h>

const float randFactor = 0.03f;

using namespace DX2D;
CGameWorld::CGameWorld()
{
	myBullets.Init(128);
	myRenderMode = eRenderMode::DEFAULT;
}

CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{
	srand(time(0));

	myInputWrapper = new CommonUtilities::InputWrapper();
	myInputWrapper->Init(*(CEngine::GetInstance()->GetHWND()), CEngine::GetInstance()->GetHInstance());

	myCommanders[0] = new Commander();
	myCommanders[1] = new Commander();

	myCommanders[0]->SetStartPosition({ 0.1f, 0.1f });
	myCommanders[1]->SetStartPosition({ 0.9f, 0.9f });

	myCommanders[0]->SetFaction(eFaction::TEAM_ONE);
	myCommanders[1]->SetFaction(eFaction::TEAM_TWO);

	myCommanders[0]->SetGameWorld(this);
	myCommanders[1]->SetGameWorld(this);

	myCommanders[0]->Init();
	myCommanders[1]->Init();

	myCommanders[0]->SetOpponent(myCommanders[1]);
	myCommanders[1]->SetOpponent(myCommanders[0]);

	for (int i = 0; i < NUMBER_OF_CONTROL_POINTS; i++)
	{
		myControlPoints[i].Init();
		myControlPoints[i].SetPosition({ RANDOM_FLOAT(0.2f, 0.8f), RANDOM_FLOAT(0.2f, 0.8f) });
		PollingStation::GetInstance()->AddControlPoint(&myControlPoints[i]);
	}

	//for (int i = 0; i < 3; i++)
	//{
	//	myActors[i] = new Actor();
	//	BlackboardController* controller = new BlackboardController();
	//	
	//	myActors[i]->SetController(controller);
	//	myActors[i]->SetPosition({ i * 0.1f + 0.7f, 0.9f });
	//
	//	myBlackboards[0].RegisterExpert(controller);
	//	controller->SetOtherBlackboard(&myBlackboards[1]);
	//
	//	myActors[i]->SetGameWorld(this);
	//}
	//
	//for (int i = 3; i < 6; i++)
	//{
	//	myActors[i] = new Actor();
	//	BlackboardController* controller = new BlackboardController();
	//
	//	myActors[i]->SetController(controller);
	//	myActors[i]->SetPosition({ 0.2f, (i - 3) * 0.1f });
	//
	//	myBlackboards[1].RegisterExpert(controller);
	//	controller->SetOtherBlackboard(&myBlackboards[0]);
	//	
	//	myActors[i]->SetGameWorld(this);
	//}
	//
	//for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
	//{
	//	myObstacles[i] = new Obstacle();
	//
	//	myObstacles[i]->SetPosition({ 0.14f * (i / 7) + 0.11f + RANDOM_FLOAT(-randFactor, randFactor), 0.14f * (i % 7) + 0.11f + RANDOM_FLOAT(-randFactor, randFactor) });
	//
	//	PollingStation::GetInstance()->AddObstacle(myObstacles[i]);
	//}
}


void CGameWorld::Update(float aTimeDelta)
{
	//myBlackboards[0].Update();
	//myBlackboards[1].Update();

	//for (int i = 0; i < NUMBER_OF_ACTORS; i++)
	//{
	//	myActors[i]->Update(aTimeDelta);
	//	myActors[i]->Render();
	//}
	//
	//for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
	//{
	//	myObstacles[i]->Render();
	//}

	myInputWrapper->PollInput();

	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_1))
	{
		myRenderMode = eRenderMode::DEFAULT;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_2))
	{
		myRenderMode = eRenderMode::TEAM_ONE_INFLUENCE;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_3))
	{
		myRenderMode = eRenderMode::TEAM_TWO_INFLUENCE;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_4))
	{
		myRenderMode = eRenderMode::TEAM_ONE_DIFFERENCE;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_5))
	{
		myRenderMode = eRenderMode::TEAM_TWO_DIFFERENCE;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_6))
	{
		myRenderMode = eRenderMode::TEAM_ONE_GOAL;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_7))
	{
		myRenderMode = eRenderMode::TEAM_TWO_GOAL;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_8))
	{
		myRenderMode = eRenderMode::TEAM_ONE_TENSION;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_9))
	{
		myRenderMode = eRenderMode::TEAM_TWO_TENSION;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_0))
	{
		myRenderMode = eRenderMode::TEAM_ONE_VULNERABILITY;
	}
	if (myInputWrapper->KeyPress(eKeyboardKeys::KEY_MINUS))
	{
		myRenderMode = eRenderMode::TEAM_TWO_VULNERABILITY;
	}

	for (int i = 0; i < 2; i++)
	{
		myCommanders[i]->Update(aTimeDelta);
	}

	for (int i = 0; i < myBullets.Size(); i++)
	{
		myBullets[i].Update(aTimeDelta);

		if (myBullets[i].GetIsDead() == true)
		{
			myBullets.RemoveCyclicAtIndex(i);
			--i;
		}
	}

	CommonUtilities::Containers::GrowingArray<Actor*> actors = PollingStation::GetInstance()->GetActors();

	for (Actor* actor : actors)
	{
		for (Bullet& bullet : myBullets)
		{
			actor->CollideVSBullet(bullet);
		}

		for (int i = 0; i < NUMBER_OF_CONTROL_POINTS; i++)
		{
			actor->CollideVSControlPoint(myControlPoints[i]);
		}
	}

	switch (myRenderMode)
	{
	case eRenderMode::DEFAULT:
		for (int i = 0; i < NUMBER_OF_CONTROL_POINTS; i++)
		{
			myControlPoints[i].Render();
		}

		myCommanders[0]->Render();
		myCommanders[1]->Render();

		for (int i = 0; i < myBullets.Size(); i++)
		{
			myBullets[i].Render();
		}
		break;
	case eRenderMode::TEAM_ONE_INFLUENCE:
		myCommanders[0]->GetInfluenceMap().Render();
		break;
	case eRenderMode::TEAM_TWO_INFLUENCE:
		myCommanders[1]->GetInfluenceMap().Render();
		break;
	case eRenderMode::TEAM_ONE_DIFFERENCE:
		myCommanders[0]->GetDifference().Render();
		break;
	case eRenderMode::TEAM_TWO_DIFFERENCE:
		myCommanders[1]->GetDifference().Render();
		break;
	case eRenderMode::TEAM_ONE_TENSION:
		myCommanders[0]->GetTension().Render();
		break;
	case eRenderMode::TEAM_TWO_TENSION:
		myCommanders[1]->GetTension().Render();
		break;
	case eRenderMode::TEAM_ONE_GOAL:
		break;
	case eRenderMode::TEAM_TWO_GOAL:
		break;
	case eRenderMode::TEAM_ONE_VULNERABILITY:
		myCommanders[0]->GetVulnerability().Render();
		break;
	case eRenderMode::TEAM_TWO_VULNERABILITY:
		myCommanders[1]->GetVulnerability().Render();
		break;
	default:
		break;
	}

	CEngine::GetInstance()->GetLightManager().SetAmbience(1.0f);
}

void CGameWorld::SpawnBullet(const CommonUtilities::Vector::Vector2<float>& aPosition, const CommonUtilities::Vector::Vector2<float> aDirection, eFaction aFaction)
{
	myBullets.Add(Bullet());
	myBullets.GetLast().Init(aPosition, aDirection);
	myBullets.GetLast().SetFaction(aFaction);
}