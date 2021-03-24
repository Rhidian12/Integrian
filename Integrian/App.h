#pragma once
#ifndef INTEGRIAN_APP_H
#define INTEGRIAN_APP_H

#include "pch.h"
#include <memory>
#include "GameObject.h"
#include "Logger.h"
#include "ServiceLocator.h"

namespace Integrian
{
	class OrthographicCamera;
	class Timer;
	class App abstract
	{
	public:
		virtual ~App();
		// remove copy/move constructors/assignment operators
		App(const App&) = delete;
		App(App&&) = delete;
		App& operator=(const App&) = delete;
		App& operator=(App&&) = delete;

		virtual void Start() = 0;

		void Run();

		virtual void Update(const float elapsedSeconds) = 0;
		virtual void FixedUpdate(const float elapsedSeconds) = 0;
		virtual void LateUpdate(const float elapsedSeconds) = 0;

		virtual void Render() const = 0;

		[[nodiscard]] virtual Rectf GetLevelBoundaries() const = 0;
		[[nodiscard]] virtual Rectf GetTarget() const = 0;
		[[nodiscard]] uint32_t GetWindowWidth() const;
		[[nodiscard]] uint32_t GetWindowHeight() const;

		void SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight);

	protected:
		Rectf m_Target{};
		uint32_t m_WindowWidth{};
		uint32_t m_WindowHeight{};
		SDL_Window* m_pWindow{};
		bool m_HasStarted{};
		bool m_IsInitializationFinished{};

		std::unique_ptr<OrthographicCamera> m_pCamera;
		std::vector<GameObject*> m_pGameObjects;

		// make the constructor protected, so only children can make an app
		App();

	private:
		void TransformCameraAndRender() const;
		void UpdateApplication(float& timeSinceLastUpdate);

		bool Initialize();
		bool InitializeCamera();
		void FinishInitializationOfApp();
		void ClearBackground() const;

		void ShutDown();
	};
}

#endif // !INTEGRIAN_APP_H