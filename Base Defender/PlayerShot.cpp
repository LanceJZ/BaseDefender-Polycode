#include "PlayerShot.h"

PlayerShot::PlayerShot()
{
	mLifeTimerBase = 2;
	upLifeTimer = std::unique_ptr<Timer>(new Timer(false, 0));
}

PlayerShot::~PlayerShot()
{
}

void PlayerShot::Setup(CollisionScene * scene)
{
	pShotModel = new Entity();
	LoadVoxEntity("Resources/PlayerShot", pShotModel);
	scene->addChild(pShotModel);
	pShotModelSide = new Entity();
	LoadVoxEntity("Resources/PlayerShot", pShotModelSide);
	scene->addChild(pShotModelSide);
	Deactivate();
}

void PlayerShot::Update(Number * elapsed)
{
	Actor::Update(elapsed);

	SideEdge(); //This needs to be before side copy position gets set, or it blinks.

	Vector3 otherSide = m_Position;
	pShotModelSide->enabled = Otherside(otherSide);
	pShotModelSide->setPosition(otherSide);

	pShotModel->setPosition(m_Position); //This needs to be here after side copy gets disabled or it blinks.

	if (upLifeTimer->getElapsedf() > mLifeTimerAmount)
		Deactivate();
}

void PlayerShot::Activate(Vector3 position, Vector3 velocity)
{
	m_Position = position;
	m_Velocity = velocity;
	pShotModel->enabled = true;
	pShotModelSide->enabled = true;
	m_Active = true;
	upLifeTimer->Reset();
	mLifeTimerAmount = Random::Number(mLifeTimerBase / 1.25, mLifeTimerBase);
}

void PlayerShot::Deactivate(void)
{
	pShotModel->enabled = false;
	pShotModelSide->enabled = false;
	m_Active = false;
}
