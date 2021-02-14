#pragma once
#ifndef INTEGRIAN_TEXTURE_H
#define INTEGRIAN_TEXTURE_H

#include <string>
#include "TypeDefines.h"
#include "Structs.h"
#include <SDL_opengl.h>
#include <SDL_ttf.h>

struct SDL_Surface;
namespace Integrian
{
	class Texture final
	{
	public:
		explicit Texture(const std::string& imagePath);
		explicit Texture(const std::string& text, const std::string& fontPath, int ptSize, const RGBColour& textColor);
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;
		~Texture();

		void Draw(const Point2f& dstBottomLeft = {}, const Rectf& srcRect = Rectf{}) const;
		void Draw(const Rectf& dstRect, const Rectf& srcRect = Rectf{}) const;

		[[nodiscard]] float GetWidth() const;
		[[nodiscard]] float GetHeight() const;
		[[nodiscard]] bool IsCreationOk() const;

	private:
		//DATA MEMBERS
		GLuint m_Id;
		float m_Width;
		float m_Height;
		bool m_CreationOk;

		// FUNCTIONS
		void CreateFromImage(const std::string& path);
		void CreateFromString(const std::string& text, TTF_Font* pFont, const RGBColour& textColor);
		void CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const RGBColour& textColor);
		void CreateFromSurface(SDL_Surface* pSurface);
		void DrawFilledRect(const Rectf& dstRect) const;
	};
}

#endif // INTEGRIAN_TEXTURE_H