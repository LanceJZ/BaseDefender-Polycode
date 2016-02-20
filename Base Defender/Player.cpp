#include "Player.h"

Player::Player()
{
	m_Active = true;
	m_Flipped = false;
	m_DecelerationY = 0.1;
	m_DecelerationX = 0.02;

	up_ThrustTimer = std::unique_ptr<Timer>(new Timer(false, 0));
	up_ThrustTimer->Reset();
}

Player::~Player()
{
}

void Player::Setup(CollisionScene * scene)
{
	pScene = scene;
	pCamera = scene->getDefaultCamera();

	pRadarDot = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1, 0.5, 0.1);
	pRadarDot->setColor(0.36, 0.25, 0.70, 1);
	pRadarDot->setPosition(0, 0, 10);
	scene->addChild(pRadarDot);

	pLight = new SceneLight(SceneLight::POINT_LIGHT, pScene, 1225000);
	pLight->setPosition(200, 500, 1000);
	pLight->setLightColor(1, 1, 1);
	pScene->addLight(pLight);

	pShipModel = new Entity();
	m_ShipParts = LoadVoxEntity("Resources/Player", pShipModel);
	pScene->addChild(pShipModel);
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
	pLight->setPositionX(m_Position.x);
	pCamera->setPositionX(m_Position.x + m_Velocity.x * 0.5);
	pCamera->lookAt(Vector3(m_Position.x + m_Velocity.x * 0.5, 0, 0));


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

	SideEdge();
	UpdateRadar();
}

void Player::UpdateShots(Number * elapsed)
{
	for (size_t shot = 0; shot < vup_Shots.size(); shot++)
	{
		vup_Shots.at(shot)->Update(elapsed);
	}
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
	m_Acceleration.y = 10;
}

void Player::MoveDown(void)
{
	m_Acceleration.y = -10;
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

	if (up_ThrustTimer->getElapsedf() > 0.031)
	{
		pThrust1->enabled = true;
		pThrust2->enabled = false;
		up_ThrustTimer->Reset();
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
	bool spawnNewShot = true;
	int spawnShot = 0;
	Number shotVelocity = 100;

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
		vup_Shots.push_back(std::unique_ptr<PlayerShot>(new PlayerShot));
		spawnShot = vup_Shots.size() - 1;
		vup_Shots.at(spawnShot)->Setup(pScene);
	}

	if (m_Flipped)
	{
		shotVelocity = -100 + m_Velocity.x * 0.75;
	}
	else
	{
		shotVelocity = 100 + m_Velocity.x * 0.75;
	}

	vup_Shots.at(spawnShot)->Activate(m_Position, Vector3(shotVelocity, m_Velocity.y * 0.1, 0));
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

void Player::UpdateRadar(void)
{
	Number dotY = (50 + m_Position.y) / 6.4;

	pRadarDot->setPositionY(-78 + dotY);
	pRadarDot->setPositionX(pCamera->getPosition().x);
}
