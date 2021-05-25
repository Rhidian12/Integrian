#pragma once
#ifndef INTEGRIAN_APP_H
#define INTEGRIAN_APP_H

#include <memory> // std::unique_pointer
#include "GameObject.h" // GameObject
#include "Structs.h" // Rectf
#include <string> // std::string
#include "ListenerInterface.h" // IListener
#include <unordered_map> // std::unordered_map
#include "GameInput.h" // CommandAndButton
#include <functional> // std::function
#include <array> // std::array
#include <unordered_map> // std::unordered_map

struct SDL_Window;
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

		virtual void Update(const float elapsedSeconds) = 0;
		virtual void FixedUpdate(const float elapsedSeconds) = 0;
		virtual void LateUpdate(const float elapsedSeconds) = 0;

		virtual void OnAppEnter();
		virtual void OnAppExit();

		virtual void Render() const = 0;

		[[nodiscard]] virtual Rectf GetLevelBoundaries() const = 0;
		[[nodiscard]] virtual Rectf GetTarget() const = 0;
		[[nodiscard]] uint32_t GetWindowWidth() const;
		[[nodiscard]] uint32_t GetWindowHeight() const;
		[[nodiscard]] std::string GetAppName() const;
		[[nodiscard]] GameObject* GetGameObject(const std::string& name) const;
		[[nodiscard]] const std::unordered_map<std::string, GameObject*>& GetGameObjects() const;

		void AddGameObject(const std::string& name, GameObject* pGameObject);

		void SetWindowSize(const uint32_t windowWidth, const uint32_t windowHeight);

		virtual bool OnEvent(const Event& event) override;

	protected:
		Rectf m_Target{};
		bool m_HasStarted{};
		bool m_IsInitializationFinished{};
		std::string m_AppName{};

		std::unique_ptr<OrthographicCamera> m_pCamera{};
		std::unordered_map<std::string, std::function<void()>> m_Commands{};
		std::unordered_map<std::string, GameObject*> m_pGameObjects{};

		inline static uint32_t m_WindowWidth{};
		inline static uint32_t m_WindowHeight{};
		inline static SDL_Window* m_pWindow{};

		// make the constructor protected, so only children can make an app
		App(const std::string& appName);

		/* This removes a command from both the CommandManager and all inputs linked to it */
		void RemoveCommand(const std::string& commandName);

	private:
		friend class App_Selector; // TODO: Make this a friend function for Run()
		void TransformCameraAndRender() const;
		void UpdateApplication();

		bool Initialize();
		bool InitializeCamera();
		bool InitializeLibraries();
		void FinishInitializationOfApp();
		void ClearBackground() const;

		void ShutDown();

		void Run();

		inline static bool m_IsLibraryInitialised{ false };
		inline static bool m_IsLibraryDestroyed{ false };

		float m_TimeSinceLastUpdate;

		std::array<std::unordered_map<ControllerInput, std::vector<CommandAndButton>>, 4> m_CC;
		std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> m_KC;
		std::unordered_map<MouseButton, std::vector<CommandAndButton>> m_MC;
	};
}

#endif // !INTEGRIAN_APP_H