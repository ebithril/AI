#include "stdafx.h"
#include "Actor.h"

#include "Controller.h"
#include "PollingStation.h"

#include "GameWorld.h"

#include "HelpFunctions.h"

#define PI 3.14159265358f

Actor::Actor() : myPosition(0,0)
{
	myShotTimer = 0;
	myController = nullptr;
	mySprite = new DX2D::CSprite("Sprites/unit.dds");
	mySprite->SetPivot({ 0.5f, 0.5f });

	PollingStation::GetInstance()->AddActor(this);

	myHealth = 10;
}

Actor::~Actor()
{
	delete mySprite;
}

void Actor::Update(float aDeltaTime)
{ 
	myShotTimer -= aDeltaTime;
	CommonUtilities::Vector::Vector2<float> suggestedMovement = myController->GetDirection();

	myPosition += suggestedMovement * aDeltaTime;

	mySprite->SetPosition(DX2D::Vector2f(myPosition.x, myPosition.y));

	CheckForEnemiesAndShoot();
}

void Actor::SetController(Controller* aController)
{
	myController = aController;
	myController->SetParent(this);
}

void Actor::SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myPosition = aPosition;

	mySprite->SetPosition(DX2D::Vector2f(myPosition.x, myPosition.y));
}

void Actor::SetColor(const CommonUtilities::Vector::Vector4<float>& aColor)
{
	mySprite->SetColor(DX2D::CColor(aColor.x, aColor.y, aColor.z, aColor.w));
	myColor = aColor;
}

const CommonUtilities::Vector::Vector2<float>& Actor::GetPosition() const
{
	return myPosition;
}

void Actor::SetFaction(eFaction aFaction)
{
	myFaction = aFaction;
}

void Actor::CollideVSBullet(Bullet& aBullet)
{
	if (aBullet.GetFaction() != myFaction)
	{
		CommonUtilities::Vector::Vector2<float> max = myPosition + CommonUtilities::Vector::Vector2<float>(16.f / 1920.f, 16.f / 1080.f);
		CommonUtilities::Vector::Vector2<float> min = myPosition - CommonUtilities::Vector::Vector2<float>(16.f / 1920.f, 16.f / 1080.f);

		CommonUtilities::Vector::Vector2<float> bulletMax = aBullet.GetPosition() + CommonUtilities::Vector::Vector2<float>(4.f / 1920.f, 4.f / 1080.f);
		CommonUtilities::Vector::Vector2<float> bulletMin = aBullet.GetPosition() - CommonUtilities::Vector::Vector2<float>(4.f / 1920.f, 4.f / 1080.f);

		if (bulletMin.x > max.x)
		{
			return;
		}
		if (bulletMin.y > max.y)
		{
			return;
		}

		if (bulletMax.x < min.x)
		{
			return;
		}
		if (bulletMax.y < min.y)
		{
			return;
		}

		--myHealth;

		aBullet.SetIsDead();
	}
}

void Actor::CollideVSControlPoint(ControlPoint& aControlPoint)
{
	if (aControlPoint.GetFaction() != myFaction)
	{
		CommonUtilities::Vector::Vector2<float> max = myPosition + CommonUtilities::Vector::Vector2<float>(16.f / 1920.f, 16.f / 1080.f);
		CommonUtilities::Vector::Vector2<float> min = myPosition - CommonUtilities::Vector::Vector2<float>(16.f / 1920.f, 16.f / 1080.f);

		CommonUtilities::Vector::Vector2<float> controlPointMax = aControlPoint.GetPosition() + CommonUtilities::Vector::Vector2<float>(32.f / 1920.f, 32.f / 1080.f);
		CommonUtilities::Vector::Vector2<float> controlPointMin = aControlPoint.GetPosition() - CommonUtilities::Vector::Vector2<float>(32.f / 1920.f, 32.f / 1080.f);

		if (controlPointMin.x > max.x)
		{
			return;
		}
		if (controlPointMin.y > max.y)
		{
			return;
		}

		if (controlPointMax.x < min.x)
		{
			return;
		}
		if (controlPointMax.y < min.y)
		{
			return;
		}

		aControlPoint.SetFaction(myFaction);
		aControlPoint.SetColor(myColor);
	}
}

void Actor::Render()
{
	mySprite->Render();
}

Controller* Actor::GetController()
{
	return myController;
}

void Actor::SetGameWorld(CGameWorld* aGameWorld)
{
	myGameWorld = aGameWorld;
}

int Actor::GetHealth()
{
	return myHealth;
}

void Actor::CheckForEnemiesAndShoot()
{
	CommonUtilities::Containers::GrowingArray<Actor*> actors = PollingStation::GetInstance()->GetActors();

	for (Actor* actor : actors)
	{
		if (actor->myFaction != myFaction)
		{
			float length = CommonUtilities::Vector::Length(actor->myPosition - myPosition);

			if (length <= 0.2f)
			{
				Shoot(myPosition, actor->myPosition - myPosition);
				return;
			}
		}
	}
}

void Actor::ClampMovement(CommonUtilities::Vector::Vector2<float>& aMovement, const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement)
{
	if (aMovement.x > aSuggestedMovement.x)
	{
		aMovement.x = aSuggestedMovement.x;
	}
	else if (aMovement.y > aSuggestedMovement.y)
	{
		aMovement.y = aSuggestedMovement.y;
	}
}

void Actor::UpdateRotation(const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement)
{
	float rotation = atan2f(aSuggestedMovement.y, aSuggestedMovement.x);

	if (rotation < -PI)
	{
		rotation += PI * 2;
	}
	else if (rotation > PI)
	{
		rotation -= PI * 2;
	}

	mySprite->SetRotation(rotation);
}

void Actor::Shoot(const CommonUtilities::Vector::Vector2<float>& aPosition, const CommonUtilities::Vector::Vector2<float> aDirection)
{
	if (myShotTimer <= 0)
	{
		myGameWorld->SpawnBullet(aPosition, aDirection, myFaction);
		myShotTimer = 0.25f; 
	}
}