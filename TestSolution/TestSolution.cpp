#include <iostream>
#include <App.h>
#include <AudioSystem.h>
#include <SDLAudioSystem.h>
#include <App_Selector.h>
#include <EventQueue.h>

int main(int, char**)
{
	using namespace Integrian;

	class Foo final : public App
	{
	public:
		Foo()
			: App{ "Foo" }
		{}
		virtual void Start() override
		{
			std::cout << "Foo" << std::endl;
		}

		virtual Rectf GetLevelBoundaries() const override { return Rectf{ 0.f,0.f,float(GetWindowWidth()),float(GetWindowHeight()) }; };
		virtual Rectf GetTarget() const override { return Rectf{}; };
	};

	App* pFoo{ new Foo{} };

	App_Manager::GetInstance().AddApplication(pFoo);

	delete pFoo;

	return 0;
}