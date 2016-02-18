#pragma once
#include "Random.h"
#include "Actor.h"
#include "Player.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);
	void DeactivateShot(int shot);
	void Pause(bool paused);
	void Hit(void);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);
	void PlayerPointer(std::shared_ptr<Player> playerPointer);

protected:
	std::vector<ScenePrimitive*> m_ShipParts;
	std::shared_ptr<Player> pPlayer;
	CollisionScene *pScene;
	Entity *pShipModel;
	Entity *pShipModelSide;

	Number mMaxY;
	Number mMaxX;

private:

};

