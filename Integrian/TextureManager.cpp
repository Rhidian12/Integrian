#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <iostream>
Integrian::TextureManager::TextureManager()
{
}

Integrian::TextureManager::~TextureManager()
{
	for (std::pair<std::string, Texture*> pPair : m_pTextures)
		SAFE_DELETE(pPair.second);
}

void Integrian::TextureManager::AddTexture(const std::string& name, const std::string& path)
{
	if (!m_pTextures.insert(std::make_pair(name, new Texture{ path })).second)
	{
		// TODO: Turn this into a Logger thing
		// == If The Insertion Failed, .second Will Be False ==
		std::cout << name << " was not inserted! Check " << path << std::endl;
	}
}

void Integrian::TextureManager::AddTexture(const std::string& name, const std::string& path, const std::string& textToRender, const int size, const RGBColour& colour)
{
	if(!m_pTextures.insert(std::make_pair(name, new Texture{textToRender,path,size,colour})).second)
	{
		// TODO: Logger thingie
	}
}

const std::unordered_map<std::string, Integrian::Texture*>& Integrian::TextureManager::GetTextures() const
{
	return m_pTextures;
}