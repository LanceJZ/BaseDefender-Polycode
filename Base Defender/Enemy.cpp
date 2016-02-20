#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Setup(CollisionScene * scene)
{
	pScene = scene;
	pCamera = scene->getActiveCamera();
	pShipModel = new Entity();
	pShipModelSide = new Entity();
	pShipModelSide->enabled = false;
	scene->addChild(pShipModel);
	scene->addChild(pShipModelSide);

	pRadarDot = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5, 0.5, 0.1);
	pRadarDot->setColor(0.22, 0.14, 0.81, 1);
	pRadarDot->setPosition(0, 0, 10);
	scene->addChild(pRadarDot);
}

void Enemy::Update(Number * elapsed)
{
	Actor::Update(elapsed);

	if (m_Velocity.x > mMaxX || m_Velocity.x < -mMaxX || m_Velocity.y > mMaxY || m_Velocity.y < -mMaxY)
		m_Acceleration = 0;

	if (m_Position.y > 78)
	{
		m_Acceleration = 0;
		m_Position.y = 78;
		BounceY();
	}
	else if (m_Position.y < -50)
	{
		m_Acceleration = 0;
		m_Position.y = -50;
		BounceY();
	}

	SideEdge();

	Vector3 otherSide = m_Position;
	pShipModelSide->enabled = Otherside(otherSide);
	pShipModelSide->setPosition(otherSide);
	
	pShipModel->setPosition(m_Position);
	UpdateRadar();
}

void Enemy::Pause(bool paused)
{
}

void Enemy::Hit(void)
{
}

void Enemy::Activate(void)
{
}

void Enemy::Deactivate(void)
{
}

void Enemy::NewGame(void)
{
}

void Enemy::Reset(void)
{
	m_Active = true;
	pShipModel->enabled = true;
	m_Position = Vector3(Random::Number(-m_WorldWidth / 2, m_WorldWidth / 2), Random::Number(70, 80), 0);
	pShipModel->setPosition(m_Position);
}

void Enemy::PlayerPointer(std::shared_ptr<Player> playerPointer)
{
	spPlayer = playerPointer;
}

void Enemy::UpdateRadar(void)
{
	Number dotY = (50 + m_Position.y) / 6.4;
	Number dotX = ((-pCamera->getPosition().x + m_Position.x) / 20 + pCamera->getPosition().x);

	pRadarDot->setPositionY(-78 + dotY);
	pRadarDot->setPositionX(dotX);
}
