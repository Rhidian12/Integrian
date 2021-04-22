#pragma once
#ifndef INTEGRIAN_APP_H
#define INTEGRIAN_APP_H

#include <memory> // std::unique_pointer
#include "GameObject.h" // GameObject
#include "Structs.h" // Rectf
#include <string> // std::string
#include "ListenerInterface.h" // IListener
#include "App_Info.h" // App_Info

namespace Integrian
{
	class OrthographicCamera;
	class Timer;
	class App abstract : public IListener
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
		[[nodiscard]] std::string GetAppName() const;
		[[nodiscard]] App_Info& GetAppInfo();

		void SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight);

		virtual bool OnEvent(const Event& event) override;

	protected:
		Rectf m_Target{};
		bool m_HasStarted{};
		bool m_IsInitializationFinished{};
		std::string m_AppName{};

		std::unique_ptr<OrthographicCamera> m_pCamera{};
		std::vector<GameObject*> m_pGameObjects{};

		App_Info m_AppInfo{};

		inline static uint32_t m_WindowWidth{};
		inline static uint32_t m_WindowHeight{};
		inline static SDL_Window* m_pWindow{};

		// make the constructor protected, so only children can make an app
		App(const std::string& appName);

	private:
		void TransformCameraAndRender() const;
		void UpdateApplication(float& timeSinceLastUpdate);

		bool Initialize();
		bool InitializeCamera();
		bool InitializeLibraries();
		void FinishInitializationOfApp();
		void ClearBackground() const;

		void ShutDown();

		inline static bool m_IsLibraryInitialised{ false };
		inline static bool m_IsLibraryDestroyed{ false };
	};
}

#endif // !INTEGRIAN_APP_H