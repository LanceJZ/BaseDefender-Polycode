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
	void Pause(bool paused);
	void Hit(void);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);
	void PlayerPointer(std::shared_ptr<Player> playerPointer);

protected:
	std::vector<ScenePrimitive*> m_ShipParts;
	std::shared_ptr<Player> spPlayer;

	CollisionScene *pScene;
	Camera *pCamera;
	Entity *pShipModel;
	Entity *pShipModelSide;
	ScenePrimitive *pRadarDot;

	Number mMaxY;
	Number mMaxX;

private:
	void UpdateRadar(void);

};

