#include "IntegrianPCH.h" // precompiled header
#include "TextureManager.h" // header
#include "Texture.h" // texture
#include "Logger.h" // logger
Integrian::TextureManager::TextureManager()
	: m_DataPath{}
{
}

void Integrian::TextureManager::Init(const std::string& path)
{
	m_DataPath = path;
}

Integrian::TextureManager::~TextureManager()
{
	for (std::pair<std::string, Texture*> pPair : m_pTextures)
		SafeDelete(pPair.second);
}

void Integrian::TextureManager::AddTexture(const std::string& name, const std::string& path)
{
	if (!m_pTextures.insert(std::make_pair(name, new Texture{ m_DataPath + path })).second)
		Logger::LogWarning(name + " was not inserted!\n");
}

void Integrian::TextureManager::AddTexture(const std::string& name, const std::string& path, const std::string& textToRender, const int size, const RGBColour& colour)
{
	if(!m_pTextures.insert(std::make_pair(name, new Texture{ textToRender,m_DataPath + path,size,colour})).second)
		Logger::LogWarning(name + " was not inserted!\n");
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