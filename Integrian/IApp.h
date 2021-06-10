#pragma once

#include "App.h"
#include <memory>

namespace Integrian
{
	class IApp
	{
	public:
		INTEGRIAN_API IApp(const char* pName);

		/* 
		Default constructor
		*/
		INTEGRIAN_API virtual ~IApp() = default;

		/*
		This function must be overwritten by derived Applications.
		Use this function to initialize the Application
		*/
		INTEGRIAN_API virtual void Start() = 0;

		/*
		This function can be overwritten by derived Applications.
		GameObject::FixedUpdate() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific FixedUpdate behaviours related to a specific user-defined Application.
		Parameters:
		1 > const float elapsedSeconds > elapsedSeconds since last timer update
		*/
		INTEGRIAN_API virtual void FixedUpdate(const float) {}

		/*
		This function can be overwritten by derived Applications.
		GameObject::Update() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific Update behaviours related to a specific user-defined Application.
		Parameters:
		1 > const float elapsedSeconds > elapsedSeconds since last timer update
		*/
		INTEGRIAN_API virtual void Update(const float) {}

		/*
		This function can be overwritten by derived Applications.
		GameObject::LateUpdate() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific LateUpdate behaviours related to a specific user-defined Application.
		Parameters:
		1 > const float elapsedSeconds > elapsedSeconds since last timer update
		*/
		INTEGRIAN_API virtual void LateUpdate(const float) {}

		/*
		This function can be overwritten by derived Applications.
		GameObject::Render() is already called by default on all GameObjects attached to the current Application.
		Overwrite this function for specific Render behaviours related to a specific user-defined Application.
		*/
		INTEGRIAN_API virtual void Render() const {}

		/*
		This function can be overwritten by derived Applications.
		This function is called when an Application gets activated.
		*/
		INTEGRIAN_API virtual void OnAppEnter() {}

		/*
		This function can be overwritten by derived Applications.
		This function is called when an Application gets deactivated.
		*/
		INTEGRIAN_API virtual void OnAppExit() {}

		/*
		Returns the width of the viewport
		*/
		INTEGRIAN_API [[nodiscard]] uint32_t GetWindowWidth() const noexcept;

		/*
		Returns the height of the viewport
		*/
		INTEGRIAN_API [[nodiscard]] uint32_t GetWindowHeight() const noexcept;

		/*
		Returns the name of the application
		*/
		INTEGRIAN_API [[nodiscard]] const char* GetAppName() const noexcept;

	private:
		std::unique_ptr<App> m_pApp;
	};
}