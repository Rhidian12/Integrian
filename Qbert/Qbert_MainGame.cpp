#include "Qbert_MainGame.h"
#include <Texture.h>
#include <TextureComponent.h>
#include <TextureManager.h>

Qbert_MainGame::Qbert_MainGame()
	: Integrian::App{ "Qbert_MainGame" }
{
}

void Qbert_MainGame::Start()
{
	Integrian::TextureManager::GetInstance().AddTexture("Sabaton", "Resources/Images/Sabaton.jpg");

	Integrian::GameObject* pGameObject{ new Integrian::GameObject{} };
	pGameObject->AddComponent(new Integrian::TextureComponent{Integrian::TextureManager::GetInstance().GetTexture("Sabaton") });
	m_pGameObjects.push_back(pGameObject);
}

void Qbert_MainGame::Update(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->Update(elapsedSeconds);
}

void Qbert_MainGame::FixedUpdate(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->FixedUpdate(elapsedSeconds);
}

void Qbert_MainGame::LateUpdate(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->LateUpdate(elapsedSeconds);
}

void Qbert_MainGame::Render() const
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}
