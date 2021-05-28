#pragma once
#include <App.h>

class Qbert_MainGame final : public Integrian::App
{
public:
	Qbert_MainGame();
	virtual ~Qbert_MainGame() = default;

	virtual void Start() override;

	virtual void OnAppEnter() override {}
	virtual void OnAppExit() override {}

	virtual void Render() const override {};

	[[nodiscard]] virtual Integrian::Rectf GetLevelBoundaries() const override { return Integrian::Rectf{ 0.f,0.f, float(Integrian::App::m_WindowWidth), float(Integrian::App::m_WindowHeight) }; }
	[[nodiscard]] virtual Integrian::Rectf GetTarget() const override { return Integrian::Rectf{}; }

private:

};