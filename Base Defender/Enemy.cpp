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
	pShipModel = new Entity();
	pShipModelSide = new Entity();
	pShipModelSide->enabled = false;
	pScene->addChild(pShipModel);
	pScene->addChild(pShipModelSide);
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

	if (m_Position.x > 800)
	{
		m_Position.x = -800;
	}

	if (m_Position.x < -800)
	{
		m_Position.x = 800;
	}

	if (m_Position.x > 650)
	{
		pShipModelSide->enabled = true;
		pShipModelSide->setPosition(m_Position.x - 1600, m_Position.y, 0);
	}
	else if (m_Position.x < -650)
	{
		pShipModelSide->enabled = true;
		pShipModelSide->setPosition(m_Position.x + 1600, m_Position.y, 0);
	}
	else
	{
		pShipModelSide->enabled = false;
	}

	pShipModel->setPosition(m_Position);
}

void Enemy::UpdateShots(Number * elapsed)
{
}

void Enemy::DeactivateShot(int shot)
{
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
	m_Position = Vector3(Random::Number(-800, 800), Random::Number(70, 80), 0);
	pShipModel->setPosition(m_Position);
}

void Enemy::PlayerPointer(std::shared_ptr<Player> playerPointer)
{
	pPlayer = playerPointer;
}
