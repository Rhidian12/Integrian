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
	class TextureManager final
	{
	public:
		TextureManager(const char* pFile, const int line);
		void Init(const std::string& path);
		
		// == CleanUp ==
		virtual	~TextureManager();

		void AddTexture(const std::string& name, const std::string& path);
		void AddTexture(const std::string& name, const std::string& path, const std::string& textToRender, const int size, const RGBColour& colour);
		
		// == Get Textures ==
		const std::unordered_map<std::string, Integrian::Texture*>& GetTextures() const;

	private:
		inline static bool m_IsInstantiated{};
		std::string m_DataPath;
		std::unordered_map<std::string, Texture*> m_pTextures;
	};
}

#endif // !ENGINE_TEXTUREMANAGER_H