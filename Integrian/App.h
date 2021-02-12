#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include "pch.h"
#include <memory>

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
		void operator=(const App&) = delete;
		void operator=(App&&) = delete;

		virtual void Start() = 0;

		bool Initialize();
		bool InitializeCamera();
		void Run();

		virtual void Render() const = 0;
		virtual void Update(const float elapsedSeconds) = 0;

		void TransformCameraAndRender() const;
		void UpdateApplication(const float elapsedSeconds);

		virtual const Rectf GetLevelBoundaries() const = 0;
		virtual const Rectf GetTarget() const = 0;
		const uint32_t GetWindowWidth() const;
		const uint32_t GetWindowHeight() const;

		void SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight);

	protected:
		Rectf m_Target{};
		uint32_t m_WindowWidth{};
		uint32_t m_WindowHeight{};
		SDL_Window* m_pWindow{};
		std::unique_ptr<Timer> m_pTimer;
		OrthographicCamera* m_pCamera;
		bool m_HasStarted{};
		bool m_IsInitialisationFinished{};

		// make the constructor protected, so only children can make an app
		App();

	private:
		void FinishInitialisationOfApp();
		void ShutDown();
		void ClearBackground() const;
	};
}

#endif // !ENGINE_APP_H