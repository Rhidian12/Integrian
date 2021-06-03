#pragma once
#include <Component.h>
#include <vector>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
	class Blackboard;
}

class TileComponent;
class CoilyFSM final : public Integrian::Component
{
public:
	CoilyFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

private:
	void DFS(std::vector<Integrian::GameObject*>& pCheckedTiles, TileComponent* pTileToCheck, TileComponent* pWantedTile);

	Integrian::Blackboard* m_pBlackboard;
	Integrian::GameObject* m_pQbert;
};