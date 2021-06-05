#pragma once
#include <App.h>

class Qbert_StartMenu final : public Integrian::App
{
public:
	Qbert_StartMenu();
	virtual ~Qbert_StartMenu() = default;

	virtual void Start() override;

	virtual void OnAppEnter() override;

	[[nodiscard]] virtual Integrian::Rectf GetLevelBoundaries() const override { return Integrian::Rectf{ 0.f,0.f, float(Integrian::App::m_WindowWidth), float(Integrian::App::m_WindowHeight) }; }
	[[nodiscard]] virtual Integrian::Rectf GetTarget() const override { return Integrian::Rectf{}; }
private:

};