#pragma once
#include <Component.h>
#include <Graph2D.h>

namespace Integrian
{
	class GameObject;
}

class QbertGraphComponent final : public Integrian::Component
{
public:
	QbertGraphComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	Integrian::Graph2D<Integrian::GraphNode2D, Integrian::GraphConnection2D>* GetGraph() const noexcept;

private:
	Integrian::Graph2D<Integrian::GraphNode2D, Integrian::GraphConnection2D>* m_pGraph;
};