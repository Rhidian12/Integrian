#include "PyramidComponent.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>

PyramidComponent::PyramidComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pTiles{}
{
}

void PyramidComponent::Update(const float /*elapsedSeconds*/)
{
}

void PyramidComponent::AddTile(Integrian::GameObject* pTile)
{
	m_pTiles.push_back(pTile);
}
