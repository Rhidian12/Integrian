#pragma once
#ifndef INTEGRIAN_APP_H
#define INTEGRIAN_APP_H

#include <memory> // std::unique_pointer
#include "GameObject.h" // GameObject
#include "Structs.h" // Rectf
#include <string> // std::string
#include "ListenerInterface.h" // IListener
#include <map> // std::map
#include <unordered_map> // std::unordered_map
#include "GameInput.h" // CommandAndButton
#include <functional> // std::function
#include <array> // std::array
#include <unordered_map> // std::unordered_map
#include "GameObjectInformation.h"
#include "Camera.h"

struct SDL_Window;
namespace Integrian
{
	class OrthographicCamera;
	class Timer;
	class INTEGRIAN_API App : public IListener
	{
	public:
		virtual ~App();
		// remove copy/move constructors/assignment operators
		App(const App&) = delete;
		App(App&&) = delete;
		App& operator=(const App&) = delete;
		App& operator=(App&&) = delete;

		/*
		This function must be overwritten by derived Applications.
		Use this function to initialize the Application
		*/
		virtual void Start() = 0;

		/*
		This function can be overwritten by derived Applications.
		GameObject::FixedUpdate() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific FixedUpdate behaviours related to a specific user-defined Application.
		Parameters:
		1 > const float elapsedSeconds > elapsedSeconds since last timer update
		*/
		virtual void Update(const float) {}

		/*
		This function can be overwritten by derived Applications.
		GameObject::Update() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific Update behaviours related to a specific user-defined Application.
		Parameters:
		1 > const float elapsedSeconds > elapsedSeconds since last timer update
		*/
		virtual void FixedUpdate(const float) {}
		
		/*
		This function can be overwritten by derived Applications.
		GameObject::LateUpdate() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific LateUpdate behaviours related to a specific user-defined Application.
		Parameters:
		1 > const float elapsedSeconds > elapsedSeconds since last timer update
		*/
		virtual void LateUpdate(const float) {}

		/*
		This function can be overwritten by derived Applications.
		GameObject::Render() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific Render behaviours related to a specific user-defined Application.
		*/
		virtual void OnAppEnter() {}
		
		/*
		This function can be overwritten by derived Applications.
		This function is called when an Application gets activated.
		*/
		virtual void OnAppExit() {}

		/*
		This function can be overwritten by derived Applications.
		This function is called when an Application gets deactivated.
		*/
		virtual void Render() const {}

		/*
		Returns the width of the viewport
		*/
		[[nodiscard]] uint32_t GetWindowWidth() const;

		/*
		Returns the height of the viewport
		*/
		[[nodiscard]] uint32_t GetWindowHeight() const;

		/*
		Returns the name of the application
		*/
		[[nodiscard]] const char* GetAppName() const;

		/*
		This function returns the LevelBoundaries and needs to be implemented by the Derived apps for the working of the camera
		virtual Integrian::Rectf GetLevelBoundaries() const override { return Integrian::Rectf{ 0.f,0.f, float(GetWindowWidth()), float(GetWindowHeight()) }; }
		This provided function can be used as a default return type
		*/
		[[nodiscard]] virtual Rectf GetLevelBoundaries() const = 0;

		/*
		This functions returns the Target and needs to be implemented by the Derived applications for the working of the camera
		virtual Integrian::Rectf GetTarget() const override { return Integrian::Rectf{}; }
		This provided function can be used as a default return type
		*/
		[[nodiscard]] virtual Rectf GetTarget() const = 0;
	
		/*
		Adds a GameObject to this Application with a User-Defined Name
		Parameters:
		1 > const char* pName > User-defined Name given to the GameObject
		2 > GameObject* pGameObject > GameObject to add
		*/
		void AddGameObject(const char* pName, GameObject* pGameObject);

		/*
		Returns a GameObject with ID Name, which was added to this Application by using App::AddGameObject()
		Parameters:
		1 > const char* pName > User-defined Name given to the GameObject
		*/
		[[nodiscard]] GameObject* GetGameObject(const char* pName) const;

		/*
		Returns a vector of all GameObjects with the given Tag. Tags are not set by default to anything.
		Parameters:
		1 > const char* pTag > User-defined tag given to the GameObject.
		*/
		[[nodiscard]] std::vector<GameObject*>&& GetGameObjectsWithTag(const char* pTag) const noexcept;

		/*
		Removes a GameObject with ID Name, which was added to this Application by using App::AddGameObject()
		Parameters:
		1 > const char* pName > User-Defined Name given to the GameObject
		*/
		void RemoveGameObject(const char* pName) noexcept;

		/*
		This function is used internally and SHOULD NOT BE CALLED MANUALLY
		*/
		virtual bool OnEvent(const Event& event) override;

	protected:
		// make the constructor protected, so only children can make an app
		App(const char* pAppName);

	private:
		class AppImplementation;
		AppImplementation* m_pAppImplementation;

		friend class App_Manager;
		void TransformCameraAndRender() const;
		void UpdateApplication();

		void FinishInitializationOfApp();
		void ClearBackground() const;

		void AppExit();
		void AppEnter();

		void Run();
	};
}

#endif // !INTEGRIAN_APP_H