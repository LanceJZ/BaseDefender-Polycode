#include "Player.h"

Player::Player()
{
	m_Active = true;
	m_Flipped = false;
	m_DecelerationY = 0.1;
	m_DecelerationX = 0.02;

	p_ThrustTimer = std::unique_ptr<Timer>(new Timer(false, 2000));
	p_ThrustTimer->Reset();
}

Player::~Player()
{
}

void Player::Setup(CollisionScene * scene)
{
	pScene = scene;
	pCamera = scene->getDefaultCamera();

	pLight = new SceneLight(SceneLight::POINT_LIGHT, pScene, 1225000);
	pLight->setPosition(200, 500, 1000);
	pLight->setLightColor(1, 1, 1);
	pScene->addLight(pLight);

	pShipModel = new Entity();
	m_ShipParts = LoadVoxEntity("Resources/Player", pShipModel);
	pScene->addChild(pShipModel);
	//pShipModel->addChild(pLight);
	pThrust1 = new Entity();
	LoadVoxEntity("Resources/Thrust1", pThrust1);
	pShipModel->addChild(pThrust1);
	pThrust1->enabled = false;
	pThrust2 = new Entity();
	LoadVoxEntity("Resources/Thrust2", pThrust2);
	pShipModel->addChild(pThrust2);
	pThrust2->enabled = false;
	pThrust1->setPositionX(-11);
	pThrust1->setPositionY(1);
	pThrust1->setYaw(0);
	pThrust2->setPositionX(-11);
	pThrust2->setPositionY(1);
	pThrust2->setYaw(0);
}

void Player::Update(Number * elapsed)
{
	Actor::Update(elapsed);

	Decelerate();

	pShipModel->setPosition(m_Position); //Player Position
	pCamera->setPositionX(m_Position.x + m_Velocity.x * 0.5);
	pCamera->lookAt(Vector3(m_Position.x + m_Velocity.x * 0.5, 0, 0));

	if (!pCamera->isAABBInFrustum(mAABB))
	{
		m_Acceleration = 0;

		if (m_Position.y > 78)
		{
			m_Position.y = 78;
			BounceY();
		}
		else if (m_Position.y < -50)
		{
			m_Position.y = -50;
			BounceY();
		}
	}

	if (m_Position.x > 800)
		m_Position.x = -800;

	if (m_Position.x < -800)
		m_Position.x = 800;

	if (m_Position.y > 0)
	{
		mAABB.min.y = m_Position.y + 5;
		mAABB.max.y = m_Position.y + 5;
	}
	else
	{
		mAABB.min.y = m_Position.y - 40;
		mAABB.max.y = m_Position.y - 40;
	}

	mAABB.min.x = m_Position.x;
	mAABB.max.x = m_Position.x;

	pLight->setPositionX(pShipModel->getPosition().x);
}

void Player::UpdateShots(Number * elapsed)
{
}

void Player::GotPoints(int points)
{
}

void Player::DeactivateShot(int shot)
{
}

void Player::Pause(bool paused)
{
}

void Player::TurnLeft(void)
{
	if (!m_Flipped)
	{
		pShipModel->setYaw(180);
		m_Flipped = true;
	}
}

void Player::TurnRight(void)
{
	if (m_Flipped)
	{
		pShipModel->setYaw(0);
		m_Flipped = false;
	}
}

void Player::MoveUp(void)
{
	if (pCamera->isAABBInFrustum(mAABB))
	{
		m_Acceleration.y = 10;
	}
	else
	{
		m_Acceleration.y = 0;
	}
}

void Player::MoveDown(void)
{
	if (pCamera->isAABBInFrustum(mAABB))
	{
		m_Acceleration.y = -10;
	}
	else
	{
		m_Acceleration.y = 0;
	}	
}

void Player::ThrustOn(void)
{
	if (m_Flipped)
	{
		if (m_Velocity.x > -100)
		{
			m_Acceleration.x = -4;
		}
	}
	else
	{
		if (m_Velocity.x < 100)
		{
			m_Acceleration.x = 4;
		}
	}

	if (p_ThrustTimer->getElapsedf() > 0.031)
	{
		pThrust1->enabled = true;
		pThrust2->enabled = false;
		p_ThrustTimer->Reset();
	}
	else
	{
		pThrust1->enabled = false;
		pThrust2->enabled = true;
	}

}

void Player::ThrustOff(void)
{
	pThrust1->enabled = false;
	pThrust2->enabled = false;
}

void Player::ShieldOn(void)
{
}

void Player::ShieldOff(void)
{
}

void Player::FireShot(void)
{
}

void Player::Hit(void)
{
}

void Player::Activate(void)
{
}

void Player::Deactivate(void)
{
}

void Player::NewGame(void)
{
}

void Player::Reset(void)
{
}
