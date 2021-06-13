#pragma once

#ifndef APP_SELECTOR_H
#define APP_SELECTOR_H

#include "Singleton.h" // Singleton
#include "ListenerInterface.h" // IListener

namespace Integrian
{
	class App;
	class INTEGRIAN_API App_Manager final : public IListener
	{
	public:
		~App_Manager();

		App_Manager(const App_Manager&) = delete;
		App_Manager(App_Manager&&) = delete;
		App_Manager& operator=(const App_Manager&) = delete;
		App_Manager& operator=(App_Manager&&) = delete;

		/*
		This class is a Singleton, and thus the only way to call functions is through calling App_Manager::GetInstance()
		*/
		static App_Manager& GetInstance();
		
		/*
		Add a new Application to the App_Manager.
		Parameters:
		1 > App* pApplication > Pointer to the new Application.
		*/
		void AddApplication(App* pApplication);

		/*
		Sets the Application -- already added to the App_Manager -- with the given Name as active.
		Parameters:
		1 > const char* pName > Name of the Application to be activated. 
		*/
		void SetActiveApplication(const char* pName);

		/*
		This function starts the Engine. First add all Applications needed to the App_Manager, then call this function.
		*/
		void RunActiveApplication();

		/*
		Removes an Application -- already added to the App_Manager -- with the given name.
		Note: This function does not delete the Application until the end of the program.
		Parameters:
		1 > const char* pName > Name of the Application to be removed.
		*/
		void RemoveApplication(const char* pName);

		/*
		This function is used internally and SHOULD NOT BE CALLED MANUALLY
		*/
		bool OnEvent(const Event& event) override;

		/*
		Returns the current active Application.
		If no Application was explicitly set to active, then this function returns the first added application.
		*/
		[[nodiscard]] App* GetActiveApplication() const;

	private:
		class App_Manager_Implementation;
		App_Manager_Implementation* m_pImplementation;

		App_Manager();
		friend class Singleton<App_Manager>;
	};
}

#endif // !APP_SELECTOR_H