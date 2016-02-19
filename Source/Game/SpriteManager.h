#pragma once

#include "../CommonUtilities/GrowingArray.h"
#include <unordered_map>

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
}

class SpriteManager
{
public:
	SpriteManager* GetInstance();

	DX2D::CSprite* CreateSprite(const std::string& aFilePath);
	void RemoveSprite(DX2D::CSprite* aSpriteToRemove);
	void RenderAll();

private:
	SpriteManager();
	~SpriteManager();

	static SpriteManager* ourInstance;

	bool CheckIfExists(const std::string& aFilePath);
	CommonUtilities::Containers::GrowingArray<DX2D::CSprite*> mySprites;
	std::unordered_map<std::string, DX2D::CSpriteBatch*> myBatches;
};

