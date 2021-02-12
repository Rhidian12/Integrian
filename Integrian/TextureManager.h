#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef ENGINE_TEXTUREMANAGER_H
#define ENGINE_TEXTUREMANAGER_H

#include <unordered_map>
namespace Integrian
{
	class Texture;
}
class TextureManager final
{
public:
	// == CleanUp ==
	~TextureManager();
	static void CleanUp();

	// == Get Manager ==
	static TextureManager* GetInstance();

	// == Get Textures ==
	const std::unordered_map<std::string, Integrian::Texture*>& GetTextures() const;

private:
	TextureManager();

	void AddTexture(const std::string& name, const std::string& path);

	static TextureManager* m_pInstance;
	std::unordered_map<std::string, Integrian::Texture*> m_pTextures;
};

#endif // !ENGINE_TEXTUREMANAGER_H