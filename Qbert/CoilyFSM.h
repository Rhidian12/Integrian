#pragma once
#include <Component.h>
#include <vector>
#include <queue>
#include <ListenerInterface.h>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
	class Blackboard;
}

class QbertGraphComponent;
class TileComponent;
class CoilyFSM final : public Integrian::Component, public Integrian::IListener
{
public:
	CoilyFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	void Reset();

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	void BFS(std::vector<int>& path, int startNode, int wantedNote);

	Integrian::Blackboard* m_pBlackboard;
	Integrian::GameObject* m_pQbert;
	QbertGraphComponent* m_pGraph;
};