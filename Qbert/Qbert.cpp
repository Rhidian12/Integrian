#include <iostream>
#include <App_Selector.h>

#include "Qbert_MainGame.h"
#include "Qbert_StartMenu.h"
#include "ControlsScreen.h"
#include "KeyboardExplanationScreen.h"
#include "EndScreen.h"
#include "CoOpMainGame.h"

int main(int, char**)
{
	Integrian::Logger::SetDebugOnly(true);

	Integrian::App_Selector& appSelector{ Integrian::App_Selector::GetInstance() };

	appSelector.AddApplication(new Qbert_StartMenu{});
	appSelector.AddApplication(new Qbert_MainGame{ 1 });
	appSelector.AddApplication(new CoOpMainGame{});
	appSelector.AddApplication(new KeyboardExplanationScreen{});
	appSelector.AddApplication(new ControlsScreen{});
	appSelector.AddApplication(new EndScreen{});

	appSelector.SetActiveApplication("StartMenu");
	appSelector.RunActiveApplication();

	return 0;
}