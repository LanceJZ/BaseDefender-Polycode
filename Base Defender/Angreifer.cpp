#include "Angreifer.h"

Angreifer::Angreifer()
{
	mMoveTimerBase = 5;
	mMoveSpeed = 3;
	mMaxX = 5;
	mMaxY = 2.5;

	mShotTimerBase = 5;
	mShotLifeTimerBase = 1.75;
}

Angreifer::~Angreifer()
{
}

void Angreifer::Setup(CollisionScene * scene)
{
	Enemy::Setup(scene);

	pScene = scene;

	m_ShipParts = LoadVoxEntity("Resources/Angreifer", pShipModel);	
	LoadVoxEntity("Resources/Angreifer", pShipModelSide);
}

void Angreifer::Update(Number * elapsed)
{
	Enemy::Update(elapsed);

	if (DoesMovementChange())
	{
		m_Acceleration = VectorChange();
	}

	if (TimeToFire())
	{
		FireShot(m_Position, pScene);
	}
}

void Angreifer::UpdateShots(Number * elapsed)
{
	for (size_t shot = 0; shot < vup_Shots.size(); shot++)
	{
		vup_Shots.at(shot)->Update(elapsed);
	}
}
