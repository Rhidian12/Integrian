#pragma once
#ifndef INTEGRIAN_TEXTURE_COMPONENT_H
#define INTEGRIAN_TEXTURE_COMPONENT_H

#include "Component.h" // Component

namespace Integrian
{
	class GameObject;
	class Texture;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* pParent);
		TextureComponent(GameObject* pParent, Texture* pTexture);
		~TextureComponent() = default;

		virtual void Initialize() override;

		virtual void Render(const Point2f& pos) const override;
		
		void SetTexture(Texture* pTexture);
		Texture* GetTexture() const;
		
	private:
		Texture* m_pTexture;
	};
}

#endif //INTEGRIAN_TEXTURE_COMPONENT_H