#pragma once
#ifndef INTEGRIAN_TEXTURE_COMPONENT_H
#define INTEGRIAN_TEXTURE_COMPONENT_H

#include "Component.h" // Component

namespace Integrian
{
	class Texture;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent();
		TextureComponent(Texture* pTexture);
		~TextureComponent() = default;

		virtual void Render(const Point2f& pos) const override;
		
		void AddTexture(Texture* pTexture);
		Texture* GetTexture() const;
		
	private:
		Texture* m_pTexture;
	};
}

#endif //INTEGRIAN_TEXTURE_COMPONENT_H