#include "stdafx.h"
#include "SpriteManager.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>

SpriteManager::SpriteManager()
{
	mySprites.Init(128);
}

SpriteManager::~SpriteManager()
{
}

bool SpriteManager::CheckIfExists(const std::string& aFilePath)
{

}
