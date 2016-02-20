#include "EnemyShot.h"

EnemyShot::EnemyShot()
{
	upLifeTimer = std::unique_ptr<Timer>(new Timer(false, 0));
	pShot = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5, 0.5, 0.5);
	pShotSide = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5, 0.5, 0.5);
	SetAABB(pShot);
	Deactivate();
}

EnemyShot::~EnemyShot()
{
}

void EnemyShot::Setup(CollisionScene * scene)
{
	scene->addChild(pShot);
	scene->addChild(pShotSide);
}

void EnemyShot::Update(Number * elapsed)
{
	Actor::Update(elapsed);

	SideEdge();

	Vector3 otherSide = m_Position;
	pShotSide->enabled = Otherside(otherSide);
	pShotSide->setPosition(otherSide);

	pShot->setPosition(m_Position);

	if (upLifeTimer->getElapsedf() > mLifeTimerAmount)
		Deactivate();
}

void EnemyShot::Activate(Vector3 position, Vector3 velocity, float lifeTimer)
{
	pShot->enabled = true;
	m_Active = true;
	m_Position = position;
	m_Velocity = velocity;
	mLifeTimerAmount = Random::Number(lifeTimer / 2, lifeTimer);
	upLifeTimer->Reset();
}

void EnemyShot::Deactivate(void)
{
	pShot->enabled = false;
	pShotSide->enabled = false;
	m_Active = false;
}
