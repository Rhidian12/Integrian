#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <iostream>
TextureManager* TextureManager::m_pInstance{ nullptr };
TextureManager::TextureManager()
{
	AddTexture("small", "Images/small.png");
	AddTexture("Background", "Images/Background/Background.png");
}
TextureManager* TextureManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new TextureManager{};
	return m_pInstance;
}
TextureManager::~TextureManager()
{
	for (std::pair<std::string, Integrian::Texture*> pPair : m_pTextures)
		SAFE_DELETE(pPair.second);
}
void TextureManager::CleanUp()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}
void TextureManager::AddTexture(const std::string& name, const std::string& path)
{
	if (!m_pTextures.insert(std::make_pair(name, new Integrian::Texture{ path })).second)
	{
		// == If The Insertion Failed, .second Will Be False ==
		std::cout << name << " was not inserted! Check " << path << std::endl;
	}
}
const std::unordered_map<std::string, Integrian::Texture*>& TextureManager::GetTextures() const
{
	return m_pTextures;
}