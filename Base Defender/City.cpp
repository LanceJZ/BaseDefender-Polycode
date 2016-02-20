#include "City.h"

City::City()
{
}

City::~City()
{
}

void City::Setup(CollisionScene * scene, Vector3 position)
{
	pCamera = scene->getDefaultCamera();

	pRadarDot = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4, 2, 0.1);
	pRadarDot->setColor(0.6, 0.5, 0.70, 1);
	pRadarDot->setPosition(0, 0, 10);
	scene->addChild(pRadarDot);

	pCityModel = new Entity();
	m_CityParts = LoadVoxEntity("Resources/CityNew", pCityModel);
	scene->addChild(pCityModel);
	pCityModel->setPosition(position);
	m_Position = position;
}

void City::Update(Number * elapsed)
{
	UpdateRadar();
}

void City::Pause(bool paused)
{
}

void City::Activate(void)
{
	m_Active = true;
	mAlertOn = false;
	mDistroyed = false;
	mTimerAlertBase = 3;
	mHitPoints = 100;
}

void City::Deactivate(void)
{
}

void City::NewGame(void)
{
}

void City::Reset(void)
{
}

void City::HitByBomb(void)
{
	if (!mDistroyed)
	{
		mHitPoints -= 10;
		mAlertOn = true;
		//mRadar->setTexture(*mRadarCityAlert);
		//mTimerAlert = Common::ResetTimer(mAmountAlertTimer, mAmountAlertTimer / 2);

		if (mHitPoints < 10)
		{
			mDistroyed = true;
			mAlertOn = false;
			//Entity::SetTexture(mCityDistroyed);
			//mRadar->setTexture(*mRadarCityDistroyed);
		}
		else if (mHitPoints < 20)
		{
			//Entity::SetTexture(mCityDamaged4);
		}
		else if (mHitPoints < 40)
		{
			//Entity::SetTexture(mCityDamaged3);
		}
		else if (mHitPoints < 60)
		{
			//Entity::SetTexture(mCityDamaged2);
		}
		else if (mHitPoints < 80)
		{
			//Entity::SetTexture(mCityDamaged1);
		}
	}
}

bool City::GotDistroyed(void)
{
	return mDistroyed;
}

void City::Alert(void)
{
}

void City::UpdateRadar(void)
{
	Number dotY = -18 + m_Position.y;
	Number dotX = ((-pCamera->getPosition().x + m_Position.x) / 20 + pCamera->getPosition().x);

	pRadarDot->setPositionY(dotY);
	pRadarDot->setPositionX(dotX);
}
