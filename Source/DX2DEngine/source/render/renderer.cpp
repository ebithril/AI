#include "stdafx.h"

#include "render/renderer.h"
#include "engine.h"
#include "d3d/direct_3d.h"
#include "render/render_object.h"

using namespace DX2D;

CRenderer::CRenderer()
{
}


CRenderer::~CRenderer()
{
}

void CRenderer::AddToRender( CRenderObject* aObject )
{
	CDirectEngine& direct3D = CEngine::GetInstance()->GetDirect3D();
	direct3D.Draw(aObject);
}

