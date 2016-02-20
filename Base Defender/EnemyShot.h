#pragma once
#include "Actor.h"

class EnemyShot : public Actor
{
public:
	EnemyShot();
	~EnemyShot();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void Activate(Vector3 position, Vector3 velocity, float lifeTimer);
	void Deactivate(void);

	float mLifeTimerAmount;

private:
	ScenePrimitive *pShot;
	ScenePrimitive *pShotSide;

	std::unique_ptr<Timer> upLifeTimer;
};

