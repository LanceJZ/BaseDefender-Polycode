#pragma once
#include "Actor.h"

class PlayerShot : public Actor
{
public:
	PlayerShot();
	~PlayerShot();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void Activate(Vector3 position, Vector3 velocity);
	void Deactivate(void);

private:
	Entity *pShotModel;
	Entity *pShotModelSide;

	std::unique_ptr<Timer> upLifeTimer;

	float mLifeTimerAmount;
	float mLifeTimerBase;
};

