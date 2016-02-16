#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player();
	~Player();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);
	void GotPoints(int points);
	void DeactivateShot(int shot);
	void Pause(bool paused);
	void TurnLeft(void);
	void TurnRight(void);
	void MoveUp(void);
	void MoveDown(void);
	void ThrustOn(void);
	void ThrustOff(void);
	void ShieldOn(void);
	void ShieldOff(void);
	void FireShot(void);
	void Hit(void);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);

private:
	CollisionScene *pScene;
	Entity *pShipModel;
	Entity *pThrust1;
	Entity *pThrust2;
	Camera *pCamera;
	SceneLight *pLight;
	AABB mAABB;

	std::vector<ScenePrimitive*> m_ShipParts;

	std::unique_ptr<Timer> p_ThrustTimer;

	bool m_Flipped;
};

