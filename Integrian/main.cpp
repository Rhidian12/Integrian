// == Includes ==
#include "IntegrianPCH.h" // precompiled header
#include <vld.h> // visual leak detector
#include "App_Selector.h" // App_Selector
#include "App.h" // App
#include "VisualBenchmark.h" // Testing purposes
#include <atomic> // std::atomic

// == Include correct application == 
#ifdef TEST_APP
#include "Test_App.h"
#include "Test_App_2_Boogaloo.h"
#endif

// == Global Variables ==
std::atomic<bool> volatile g_IsLooping{ true };

int main(int argc, char* args[])
{
	// make the parameters unreferenced
	(void)argc;
	(void)args;

	//Session::Get().BeginSession();

	{
		Integrian::App_Selector& appSelector{ Integrian::App_Selector::GetInstance() };

		try
		{
			appSelector.AddApplication(new Integrian::Test_App{});
			appSelector.AddApplication(new Integrian::Test_App_2_Boogaloo{});
		}
		catch (...)
		{
#pragma warning( push )
#pragma warning( disable : 4297 ) // disable the warning telling us that SDL_Main is marked as noexcept
			Integrian::ExceptionHandler e{};
			e.ProcessException();
			return -1;
#pragma warning ( pop )
		}

		try
		{
			// == Run The Application ==
			while (g_IsLooping.load())
				appSelector.GetActiveApplication()->Run();
		}
		catch (...)
		{
#pragma warning( push )
#pragma warning( disable : 4297 ) // disable the warning telling us that SDL_Main is marked as noexcept
			Integrian::ExceptionHandler e{};
			e.ProcessException();
			return -1;
#pragma warning ( pop )
		}

		//Session::Get().EndSession();
	}

	return 0;
}