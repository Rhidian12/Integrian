#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef APP_BENCHMARK_H
#define APP_BENCHMARK_H

#include "App.h"
class Benchmark_App final : public Engine::App
{
public:
	Benchmark_App();
	virtual ~Benchmark_App() = default;

	virtual void Render() const override {};
	virtual void Update(const float elapsedSeconds) override;

	virtual const Engine::Rectf GetLevelBoundaries() const { return Engine::Rectf{}; };

	Benchmark_App(const Benchmark_App& other) = delete;
	Benchmark_App(Benchmark_App&& other) = delete;
	void operator=(const Benchmark_App& other) = delete;
	void operator=(Benchmark_App&& other) = delete;

private:
};

#endif // !APP_BENCHMARK_H