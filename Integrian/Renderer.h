#pragma once

#ifndef INTEGRIAN_RENDERER_H
#define INTEGRIAN_RENDERER_H

#include "Singleton.h"
#include <vector>
#include "Camera.h"

struct SDL_Window;
namespace Integrian
{
	class GameObject;
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void SetClearColour(const RGBColour& colour) noexcept;

		void Render(GameObject* pGameObject) noexcept;

	private:
		friend class Singleton<Renderer>;
		friend class App;
		static void ClearBackground() noexcept;
		static void StartRenderLoop(SDL_Window* pWindow) noexcept;
		static void EndRenderLoop(SDL_Window* pWindow) noexcept;
		void RenderAll(const std::unique_ptr<Camera>& pCamera, const Rectf& target) noexcept;

		inline static RGBColour m_ClearColour{ 192.f, 192.f, 192.f };
		inline static std::vector<GameObject*> m_pGameObjectsToRender{};
	};
}

#endif // !INTEGRIAN_RENDERER_H