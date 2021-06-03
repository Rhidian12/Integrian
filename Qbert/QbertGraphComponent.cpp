#include "QbertGraphComponent.h"
#include "PyramidComponent.h"
#include <App.h>
#include <App_Selector.h>
#include "TileFactoryComponent.h"

QbertGraphComponent::QbertGraphComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pGraph{}
{
}

void QbertGraphComponent::PostInitialize()
{
	using namespace Integrian;

	m_pGraph = new Graph2D<GraphNode2D, GraphConnection2D>{ false };

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	PyramidComponent* pPyramid{ pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>() };

	for (size_t i{}; i < pPyramid->GetTiles().size(); ++i)
	{
		m_pGraph->AddNode(new GraphNode2D{ i });
	}

	uint64_t counter{};
	for (unsigned int y{}; y < pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<TileFactoryComponent>()->GetSize() - 1; ++y)
	{
		for (unsigned int x{}; x <= y; ++x)
		{
			const uint64_t leftBottomIndex{ counter + (y - x) + x + 1 };
			const uint64_t rightBottomIndex{ counter + (y - x) + x + 2 };

			m_pGraph->AddConnection(new GraphConnection2D{ counter, leftBottomIndex });
			m_pGraph->AddConnection(new GraphConnection2D{ counter, rightBottomIndex });
			++counter;
		}
	}
}
