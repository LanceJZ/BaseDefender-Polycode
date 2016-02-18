#include "EnemyShot.h"

EnemyShot::EnemyShot()
{
	pLifeTimer = std::unique_ptr<Timer>(new Timer(false, 0));
	pShot = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5, 0.5, 0.5);
	SetAABB(pShot);
	Deactivate();
}

EnemyShot::~EnemyShot()
{
}

void EnemyShot::Setup(CollisionScene * scene)
{
	scene->addChild(pShot);
}

void EnemyShot::Update(Number * elapsed)
{
	Actor::Update(elapsed);

	pShot->setPosition(m_Position);

	if (pLifeTimer->getElapsedf() > mLifeTimerAmount)
		Deactivate();
}

void EnemyShot::Activate(Vector3 position, Vector3 velocity, float lifeTimer)
{
	pShot->enabled = true;
	m_Active = true;
	m_Position = position;
	m_Velocity = velocity;
	mLifeTimerAmount = Random::Number(lifeTimer / 2, lifeTimer);
	pLifeTimer->Reset();
}

void EnemyShot::Deactivate(void)
{
	pShot->enabled = false;
	m_Active = false;
}
