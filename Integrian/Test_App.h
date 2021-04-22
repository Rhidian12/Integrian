#pragma once
#ifndef INTEGRIAN_TEST_APP_H
#define INTEGRIAN_TEST_APP_H

#include "App.h"

namespace Integrian
{
	class Test_App final : public App  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		Test_App();
		virtual ~Test_App() = default;

		virtual void Start() override;

		virtual void Update(const float dt) override;
		virtual void FixedUpdate(const float) override {};
		virtual void LateUpdate(const float) override {};

		virtual void Render() const override;

		virtual Rectf GetLevelBoundaries() const override { return Rectf{ 0.f,0.f,float(m_WindowWidth),float(m_WindowHeight)}; };
		virtual Rectf GetTarget() const override { return Rectf{}; };

	private:
		void InitPlayerOne();
		void InitPlayerTwo();
	};
}

#endif // INTEGRIAN_TEST_APP_H