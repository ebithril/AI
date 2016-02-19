#pragma once

#include "..\CommonUtilities\Vector2.h"
#include "..\CommonUtilities\Vector4.h"
#include <tga2d\sprite\sprite.h>

#include "Faction.h"

class Controller;

class CGameWorld;
class ControlPoint;
class Bullet;

class Actor
{
public:
	Actor();
	~Actor();

	void Update(float aDeltaTime);

	void SetController(Controller* aController);

	void SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);

	void SetColor(const CommonUtilities::Vector::Vector4<float>& aColor);

	const CommonUtilities::Vector::Vector2<float>& GetPosition() const;

	void SetFaction(eFaction aFaction);

	void CollideVSBullet(Bullet& aBullet);
	void CollideVSControlPoint(ControlPoint& aControlPoint);

	void Render();
	Controller* GetController();

	void Shoot(const CommonUtilities::Vector::Vector2<float>& aPosition, const CommonUtilities::Vector::Vector2<float> aDirection);
	void SetGameWorld(CGameWorld* aGameWorld);

	int GetHealth();
private:
	void CheckForEnemiesAndShoot();
	void ClampMovement(CommonUtilities::Vector::Vector2<float>& aMovement, const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement);
	void UpdateRotation(const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement);

	eFaction myFaction;

	CommonUtilities::Vector::Vector2<float> myPosition;
	CommonUtilities::Vector::Vector4<float> myColor;

	float myShotTimer;
	float mySpeed;
	CGameWorld* myGameWorld;

	int myHealth;

	Controller* myController;
	DX2D::CSprite* mySprite;
};