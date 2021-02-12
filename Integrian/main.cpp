// == Includes ==
#include "pch.h"
#include <vld.h>
#include "App_Selector.h"
#include "App.h"

// == Include correct application == 
#ifdef GRAPPLE_HOOK_APP
#include "Grapple_Hook_App.h"
#endif
#ifdef BENCHMARK_APP
#include "Benchmark_App.h"
#endif

// == Global Variables ==
bool g_IsLooping{ true };

// == Should Update Be Fixed? ==
bool g_IsUpdateFixed{ true };
float g_TimePerFrame{ 1.f / 144.f };

int main(int argc, char* args[])
{
	// make the parameters unreferenced
	(void)argc;
	(void)args;

	// == Make the application ==
	Engine::App* pApplication{};

	try
	{
		// == Initialise the correct application
#ifdef GRAPPLE_HOOK_APP
		pApplication = new Grapple_Hook_App{};
#endif
#ifdef BENCHMARK_APP
		pApplication = new Benchmark_App{};
#endif
	}
	catch (...)
	{
#pragma warning( push )
#pragma warning( disable : 4297 ) // disable the warning telling us that SDL_Main is marked as noexcept
		ExceptionHandler e{};
		e.ProcessException();
		return -1;
#pragma warning ( pop )
	}

	try
	{
		// == Run The Application ==
		pApplication->Run();
	}
	catch (...)
	{
#pragma warning( push )
#pragma warning( disable : 4297 ) // disable the warning telling us that SDL_Main is marked as noexcept
		ExceptionHandler e{};
		e.ProcessException();
		return -1;
#pragma warning ( pop )
	}

	// == Cleanup ==
	SAFE_DELETE(pApplication);

	return 0;
}