#pragma once
#include <Component.h>
#include <vector>
#include <queue>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
	class Blackboard;
}

class QbertGraphComponent;
class TileComponent;
class CoilyFSM final : public Integrian::Component
{
public:
	CoilyFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

private:
	void BFS(std::vector<int>& path, int startNode, int wantedNote);

	Integrian::Blackboard* m_pBlackboard;
	Integrian::GameObject* m_pQbert;
	QbertGraphComponent* m_pGraph;
};