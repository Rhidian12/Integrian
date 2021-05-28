#include "IntegrianPCH.h" // precompiled header
#include "TextureManager.h" // header
#include "Texture.h" // texture
#include "Logger.h" // logger
#include <algorithm> // std::find_if
Integrian::TextureManager::TextureManager()
{
}

Integrian::TextureManager::~TextureManager()
{
	for (std::pair<std::string, Texture*> pPair : m_pTextures)
		SafeDelete(pPair.second);
}

void Integrian::TextureManager::AddTexture(const std::string& name, const std::string& path)
{
	if (!m_pTextures.insert(std::make_pair(name, new Texture{ path })).second)
		Logger::LogWarning(name + " was not inserted!\n");
}

void Integrian::TextureManager::AddTexture(const std::string& name, const std::string& path, const std::string& textToRender, const int size, const RGBColour& colour)
{
	if(!m_pTextures.insert(std::make_pair(name, new Texture{ textToRender,path,size,colour})).second)
		Logger::LogWarning(name + " was not inserted!\n");
}

const std::string& Integrian::TextureManager::GetTextureName(Texture* pTexture) const noexcept
{
	const std::unordered_map<std::string, Texture*>::const_iterator cIt{ std::find_if(m_pTextures.cbegin(), m_pTextures.cend(), [this, pTexture](const std::pair<std::string, Texture*>& pair)->bool
		{
			return pair.second == pTexture;
		}) };

	if (cIt != m_pTextures.cend())
		return cIt->first;
	else
	{
#ifdef _DEBUG
		Logger::LogWarning("TextureManager::GetTextureName() that texture was not found in the TextureManager!\n");
#endif
		return "";
	}
}

Integrian::Texture* Integrian::TextureManager::GetTexture(const std::string& name) const
{
	std::unordered_map<std::string, Texture*>::const_iterator cIt{ m_pTextures.find(name) };
	if (cIt != m_pTextures.cend())
		return cIt->second;
	else
	{
		Logger::LogError("Texture with name: " + name + " was not found!\n");
		return nullptr;
	}
}

const std::unordered_map<std::string, Integrian::Texture*>& Integrian::TextureManager::GetTextures() const
{
	return m_pTextures;
}