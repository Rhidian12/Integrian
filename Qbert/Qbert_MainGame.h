#pragma once
#include <App.h>

class Qbert_MainGame final : public Integrian::App
{
public:
	Qbert_MainGame(const int level);
	virtual ~Qbert_MainGame() = default;

	virtual void Start() override;

	virtual void OnAppEnter() override {}
	virtual void OnAppExit() override;

	virtual void Render() const override;

	virtual void LateUpdate(const float) override;

	[[nodiscard]] virtual Integrian::Rectf GetLevelBoundaries() const override { return Integrian::Rectf{ 0.f,0.f, float(Integrian::App::m_WindowWidth), float(Integrian::App::m_WindowHeight) }; }
	[[nodiscard]] virtual Integrian::Rectf GetTarget() const override { return Integrian::Rectf{}; }

	static const int GetLevel();
	static void SetLevel(const int level);

private:
	inline static int m_Level{};
};