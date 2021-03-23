// == Includes ==
#include "pch.h"
#include <vld.h>
#include "App_Selector.h"
#include "App.h"
#include "VisualBenchmark.h"

// == Include correct application == 
#ifdef TEST_APP
#include "Test_App.h"
#endif

// == Global Variables ==
bool g_IsLooping{ true };

int main(int argc, char* args[])
{
	// make the parameters unreferenced
	(void)argc;
	(void)args;

	//Session::Get().BeginSession();

	// == Make the application ==
	Integrian::App* pApplication{};

	try
	{
		// == Initialise the correct application
#ifdef GRAPPLE_HOOK_APP
		pApplication = new Grapple_Hook_App{};
#endif
#ifdef BENCHMARK_APP
		pApplication = new Benchmark_App{};
#endif
#ifdef TEST_APP
		pApplication = new Integrian::Test_App{};
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
	SafeDelete(pApplication);

	//Session::Get().EndSession();

	return 0;
}