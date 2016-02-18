#pragma once
#include "Common.h"
#include "EnemyShot.h"

class RandomShooter : public Common
{
public:
	RandomShooter();
	~RandomShooter();

protected:
	std::vector<std::unique_ptr<EnemyShot>> vup_Shots;

	float mShotTimerBase;
	float mShotTimerAmount;
	float mShotLifeTimerBase;

	void FireShot(Vector3 position, CollisionScene *scene);
	bool TimeToFire(void);

private:
	std::unique_ptr<Timer> pShotTimer;
};

