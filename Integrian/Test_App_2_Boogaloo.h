#pragma once
#ifndef INTEGRIAN_TEST_APP_2_BOOGALOO_H
#define INTEGRIAN_TEST_APP_2_BOOGALOO_H

#include "App.h"

namespace Integrian
{
	class Test_App_2_Boogaloo final : public App  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		Test_App_2_Boogaloo();
		virtual ~Test_App_2_Boogaloo() = default;

		virtual void Start() override;

		virtual void Update(const float) override {};
		virtual void FixedUpdate(const float) override {};
		virtual void LateUpdate(const float) override {};

		virtual void Render() const override;

		virtual Rectf GetLevelBoundaries() const override { return Rectf{ 0.f,0.f,float(GetWindowWidth()),float(GetWindowHeight()) }; };
		virtual Rectf GetTarget() const override { return Rectf{}; };

	private:
	};
}

#endif // INTEGRIAN_TEST_APP_2_BOOGALOO_H