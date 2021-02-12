#include "pch.h"
#include "Texture.h"
#include <iostream>
Engine::Texture::Texture(const std::string& path)
	: m_Id{}
	, m_CreationOk{}
	, m_Width{}
	, m_Height{}
{
	CreateImageFromString(path);
}
Engine::Texture::~Texture()
{
	glDeleteTextures(1, &m_Id);
}
void Engine::Texture::Draw(const Engine::Rectf& destRect, const Engine::Rectf& srcRect) const
{
	if (!m_CreationOk)
	{
		// Draw a filled rectangle here
		return;
	}
	// text is the srcrect, and what we define of the texture
	float textLeft{};
	float textRight{};
	float textTop{};
	float textBottom{};

	float defaultDestWidth{};
	float defaultDestHeight{};
	if (srcRect == Engine::Rectf{})
	{
		// no sourcerect specified
		// use the entire texture
		textRight = 1.f;
		textBottom = 1.f;
		// we don't redefine left and top since they are 0.f
		defaultDestWidth = m_Width;
		defaultDestHeight = m_Height;
	}
	else
	{
		// sourcerect specified
		// convert to range [0.f, 1.f]
		textLeft = srcRect.leftBottom.x / m_Width;
		textRight = (srcRect.leftBottom.x + srcRect.width) / m_Width;
		textBottom = srcRect.height / m_Height;
		textTop = (srcRect.leftBottom.y - srcRect.height) / m_Height;

		defaultDestWidth = m_Width;
		defaultDestHeight = m_Height;
	}

	float vertexLeft{};
	float vertexBottom{};
	float vertexRight{};
	float vertexTop{};
	if (destRect == Engine::Rectf{})
	{
		// no destRect specified
		vertexLeft = destRect.leftBottom.x;
		vertexBottom = destRect.leftBottom.y;
		vertexRight = destRect.leftBottom.x + m_Width;
		vertexTop = destRect.leftBottom.y + m_Height;
	}
	else
	{
		vertexLeft = destRect.leftBottom.x;
		vertexBottom = destRect.leftBottom.y;
		vertexRight = destRect.leftBottom.x + destRect.width;
		vertexTop = destRect.leftBottom.y + destRect.height;
	}

	// Tell opengl which texture we will use
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Draw
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(textLeft, textBottom);
			glVertex2f(vertexLeft, vertexBottom);

			glTexCoord2f(textLeft, textTop);
			glVertex2f(vertexLeft, vertexTop);

			glTexCoord2f(textRight, textTop);
			glVertex2f(vertexRight, vertexTop);

			glTexCoord2f(textRight, textBottom);
			glVertex2f(vertexRight, vertexBottom);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
void Engine::Texture::CreateImageFromString(const std::string& path)
{
	m_CreationOk = true;

	// Load image at specified path
	SDL_Surface* pLoadedSurface = IMG_Load(path.c_str());
	if (pLoadedSurface == nullptr)
	{
		std::cerr << "Texture::CreateFromImage, error when calling IMG_Load: " << SDL_GetError() << std::endl;
		m_CreationOk = false;
		return;
	}
	CreateFromSurface(pLoadedSurface);

	// Free loaded surface
	SDL_FreeSurface(pLoadedSurface);
}
void Engine::Texture::CreateFromSurface(SDL_Surface* pSurface)
{
	m_CreationOk = true;

	m_Width = static_cast<float>(pSurface->w);
	m_Height = static_cast<float>(pSurface->h);
	
	// Generate an array of textures, we only want one texture, so give it a size of 1
	glGenTextures(1, &m_Id);

	// Bind (select) the texture we just generated as the texture OpenGL should use
	glBindTexture(GL_TEXTURE_2D, m_Id);

	GLenum pixelFormat{ GL_RGB };

	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR;
		}
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA;
		}
		break;
	default:
		std::cerr << "Texture::CreateFromSurface, unknow pixel format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";
		m_CreationOk = false;
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

	// Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
	// *smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
	// each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
	// further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
	// them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
const float Engine::Texture::GetWidth() const
{
	return m_Width;
}
const float Engine::Texture::GetHeight() const
{
	return m_Height;
}