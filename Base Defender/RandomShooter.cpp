#include "RandomShooter.h"

RandomShooter::RandomShooter()
{
	mShotTimerAmount = 0;
	pShotTimer = std::unique_ptr<Timer>(new Timer(false, 0));
	pShotTimer->Reset();
}

RandomShooter::~RandomShooter()
{
}

void RandomShooter::FireShot(Vector3 position, CollisionScene *scene)
{
	bool spawnNewShot = true;
	int spawnShot = 0;

	for (size_t shotCheck = 0; shotCheck < vup_Shots.size(); shotCheck++)
	{
		if (!vup_Shots.at(shotCheck)->m_Active)
		{
			spawnNewShot = false;
			spawnShot = shotCheck;
			break;
		}
	}

	if (spawnNewShot)
	{
		vup_Shots.push_back(std::unique_ptr<EnemyShot>(new EnemyShot));
		spawnShot = vup_Shots.size() - 1;
		vup_Shots.at(spawnShot)->Setup(scene);
	}

	vup_Shots.at(spawnShot)->Activate(position, AngleToVector(Random::Number(0, 2 * PI), 75), mShotLifeTimerBase);
}

bool RandomShooter::TimeToFire(void)
{
	if (pShotTimer->getElapsedf() > mShotTimerAmount)
	{
		pShotTimer->Reset();
		mShotTimerAmount = Random::Number(mShotTimerBase / 10, mShotTimerBase);
		return true;
	}

	return false;
}
