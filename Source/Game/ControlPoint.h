#pragma once
#include "../CommonUtilities/Vector2.h"
#include "../CommonUtilities/Vector4.h"

#include "Faction.h"

namespace DX2D
{
	class CSprite;
}

class ControlPoint
{
public:
	ControlPoint();
	~ControlPoint();

	void Init();

	void SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);
	const CommonUtilities::Vector::Vector2<float>& GetPosition() const;

	const CommonUtilities::Vector::Vector2<float>& GetPosition();

	void SetFaction(eFaction aFaction);
	void SetColor(const CommonUtilities::Vector::Vector4<float>& aColor);

	void Render();
	eFaction GetFaction();
private:
	CommonUtilities::Vector::Vector2<float> myPosition;

	eFaction myFaction;

	DX2D::CSprite* mySprite;
};