#include <iostream>
#include <App_Selector.h>

#include "Qbert_MainGame.h"

int main(int, char**)
{
	Integrian::App_Selector& appSelector{ Integrian::App_Selector::GetInstance() };
	appSelector.AddApplication(new Qbert_MainGame{});

	appSelector.RunActiveApplication();

	return 0;
}