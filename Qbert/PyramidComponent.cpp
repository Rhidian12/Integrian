#include "PyramidComponent.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TextureManager.h>

PyramidComponent::PyramidComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
{
}

Integrian::GameObject* PyramidComponent::CreateTile(Integrian::Texture* pInactiveTileTexture, Integrian::Texture* /*pActiveTileTexture*/)
{
	using namespace Integrian;

	GameObject* pTile{ new GameObject{} };
	pTile->AddComponent(new TextureComponent{ pTile, pInactiveTileTexture });
	return nullptr;
}
