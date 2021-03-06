#include "stdafx.h"

#include "sprite/sprite.h"
#include "sprite/textured_quad.h"
#include "texture/texture_manager.h"

using namespace DX2D;
DX2D::CSprite::CSprite(const char* aTexturePath)
	:myQuad(nullptr)
	,myHasChangedSize(false)
	,myShouldRender(true)
	,myIsPartOfbatch(false)
	, myShouldRenderBatched(false)
{
	InternalInit(aTexturePath);
}


DX2D::CSprite::~CSprite(void)
{
	delete myQuad;
}

CSprite::CSprite(const CSprite& aCSprite)
{
	myQuad = nullptr;
	*this = aCSprite;
}

CSprite& DX2D::CSprite::operator=(const CSprite& aCSprite)
{
	myHasChangedSize = aCSprite.myHasChangedSize;
	myShouldRender = aCSprite.myShouldRender;
	myIsPartOfbatch = aCSprite.myIsPartOfbatch;
	myShouldRenderBatched = aCSprite.myShouldRenderBatched;
	if (aCSprite.myQuad != nullptr)
	{
		if (myQuad == nullptr)
		{
			myQuad = new CTexturedQuad();
		}
		*myQuad = *aCSprite.myQuad;
	}
	return *this;
}


void DX2D::CSprite::InternalInit(const char* aTexturePath)
{
	myQuad = new CTexturedQuad();
	myQuad->Init(aTexturePath);
}


void DX2D::CSprite::Render()
{
	if (!myShouldRender)
	{
		return;
	}
	if (!myIsPartOfbatch)
	{
		myQuad->Render();
	}	
	myShouldRenderBatched = true;
}

void DX2D::CSprite::SetPosition(const Vector2f& aPosition)
{
	myQuad->myPosition = aPosition;
}

const Vector2f& DX2D::CSprite::GetPosition() const
{
	return myQuad->myPosition;
}

void DX2D::CSprite::SetPivot(const Vector2f& aPivot)
{
	myQuad->myPivot = aPivot;
}

const Vector2f& DX2D::CSprite::GetPivot() const
{
	return myQuad->myPivot;
}


void DX2D::CSprite::SetTextureRect( float aX, float aY, float aWidth, float aHeight )
{
	myQuad->SetTextureRect(aX, aY, aWidth, aHeight);
}

STextureRext* DX2D::CSprite::GetTextureRect()
{
	return &myQuad->GetTextureRect();
}

bool DX2D::CSprite::HasSameTextureAs(CSprite* aSprite) const
{
	return myQuad->myTexture == aSprite->myQuad->myTexture;
}

const DX2D::Vector2f& DX2D::CSprite::GetUVOffset() const
{
	return myQuad->myUV;
}

void DX2D::CSprite::SetUVOffset(const Vector2f& aUV)
{
	myQuad->SetUV(aUV);
}



void DX2D::CSprite::SetColor(const CColor& aColor)
{
	myQuad->SetColor(aColor);
}

CColor DX2D::CSprite::GetColor() const
{
	return myQuad->GetColor();
}


void DX2D::CSprite::SetRotation( const float aRotationInRadians )
{
	myQuad->myRotation = aRotationInRadians;
}

float DX2D::CSprite::GetRotation() const
{
	return myQuad->myRotation;
}

void DX2D::CSprite::SetSize(const Vector2f& aSize)
{
	myQuad->SetSize(aSize);
	myHasChangedSize = true;
}

Vector2f DX2D::CSprite::GetSize() const
{
	Vector2f withWindowRatioSize;
	withWindowRatioSize = myQuad->mySize * myQuad->mySizeMultiplier;
	withWindowRatioSize.x *= CEngine::GetInstance()->GetWindowRatioInversed();

	return withWindowRatioSize;
}

Vector2<unsigned int> DX2D::CSprite::GetImageSize() const
{
	return myQuad->myImageSize;
}

void DX2D::CSprite::SetUVScale(Vector2f aScale)
{
	myQuad->myUVScale = aScale;
}

Vector2f DX2D::CSprite::GetUVScale() const
{
	return myQuad->myUVScale;
}

bool DX2D::CSprite::HasValidTexture() const
{
	return !myQuad->myTexture->myIsFailedTexture;
}

void DX2D::CSprite::SetMap(const EShaderMap aMapType, const char* aPath)
{
	myQuad->SetMap(aMapType, aPath);
}
