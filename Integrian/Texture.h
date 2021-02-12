#pragma once
// ====================================
// This class was created by Kevin Hoefman and Marleen De Wandel
// Professors at Howest Digital Arts and Entertainment
// ====================================
#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include "pch.h"
#include <string>
struct SDL_Surface;
namespace Engine
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		void Draw(const Rectf& destRect = Rectf{}, const Rectf& srcRect = Rectf{}) const;

		const float GetWidth() const;
		const float GetHeight() const;

	private:
		GLuint m_Id;
		bool m_CreationOk;
		float m_Width;
		float m_Height;

		void CreateImageFromString(const std::string& path);
		void CreateFromSurface(SDL_Surface* pSurface);
	};
}

#endif // !ENGINE_TEXTURE_H