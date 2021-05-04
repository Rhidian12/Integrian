#include "PyramidComponent.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>

PyramidComponent::PyramidComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
{
}

PyramidComponent::~PyramidComponent()
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		Integrian::SafeDelete(pGameObject);
}

void PyramidComponent::Update(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->Update(elapsedSeconds);
}

void PyramidComponent::Render(const Integrian::Point2f&) const
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}

void PyramidComponent::CreateTiles(const unsigned int size, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	// we need to make a size x size triangle
	// so let's start by adding the tiles at the 3 angles
	const Point2f& parentTransform{ m_pParent->transform.GetPosition() };

	// top angle
	m_pGameObjects.push_back(CreateTile(Point2f{ parentTransform.x, parentTransform.y + size * pInactiveTileTexture->GetHeight() }, pInactiveTileTexture));

	// left angle
	m_pGameObjects.push_back(CreateTile(Point2f{ parentTransform.x - size * pInactiveTileTexture->GetWidth(), parentTransform.y }, pInactiveTileTexture));

	// right angle
	m_pGameObjects.push_back(CreateTile(Point2f{ parentTransform.x + size * pInactiveTileTexture->GetWidth(), parentTransform.y }, pInactiveTileTexture));

	// now we need to go down in rows equal to size - 1 (since top row == top angle which is already made)
	for (unsigned int i{}; i < size - 1; ++i)
	{
		

	}
}

Integrian::GameObject* PyramidComponent::CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	GameObject* pTile{ new GameObject{} };

	pTile->AddComponent(new TextureComponent{ pTile, pInactiveTileTexture });
	pTile->transform.SetPosition(location);

	return pTile;
}
