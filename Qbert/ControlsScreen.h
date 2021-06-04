#pragma once
#include <App.h>

class ControlsScreen final : public Integrian::App
{
public:
	ControlsScreen();
	virtual ~ControlsScreen() = default;

	virtual void Start() override;

	[[nodiscard]] virtual Integrian::Rectf GetLevelBoundaries() const override { return Integrian::Rectf{ 0.f,0.f, float(Integrian::App::m_WindowWidth), float(Integrian::App::m_WindowHeight) }; }
	[[nodiscard]] virtual Integrian::Rectf GetTarget() const override { return Integrian::Rectf{}; }

private:

};

