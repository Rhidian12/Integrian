// == Includes ==
#include "IntegrianPCH.h" // precompiled header
#include <vld.h> // visual leak detector
#include "App_Selector.h" // App_Selector
#include "App.h" // App
#include <atomic> // std::atomic

// == Include correct application == 
#include "Test_App.h"
#include "Test_App_2_Boogaloo.h"

// == Global Variables ==
std::atomic<bool> volatile g_IsLooping{ true };

//int main(int, char**)
//{
//	Integrian::App_Selector& appSelector{ Integrian::App_Selector::GetInstance() };
//
//	try
//	{
//		appSelector.AddApplication(new Integrian::Test_App{});
//		appSelector.AddApplication(new Integrian::Test_App_2_Boogaloo{});
//
//		appSelector.SetActiveApplication("Test_App");
//	}
//	catch (...)
//	{
//#pragma warning( push )
//#pragma warning( disable : 4297 ) // disable the warning telling us that SDL_Main is marked as noexcept
//		Integrian::ExceptionHandler e{};
//		e.ProcessException();
//		return -1;
//#pragma warning ( pop )
//	}
//
//	try
//	{
//		// == Run The Application ==
//		appSelector.RunActiveApplication();
//	}
//	catch (...)
//	{
//#pragma warning( push )
//#pragma warning( disable : 4297 ) // disable the warning telling us that SDL_Main is marked as noexcept
//		Integrian::ExceptionHandler e{};
//		e.ProcessException();
//		return -1;
//#pragma warning ( pop )
//	}
//
//	return 0;
//}