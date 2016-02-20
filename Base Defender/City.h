#pragma once
#include "Actor.h"

namespace CityModels
{
	enum ID
	{
		New,
		Damaged10,
		Damaged25,
		Damaged50,
		Damaged75,
		Distroyed,
		Shield
	};
}

class City : public Actor
{
public:
	City();
	~City();

	void Setup(CollisionScene *scene, Vector3 position);
	void Update(Number *elapsed);
	void Pause(bool paused);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);
	void HitByBomb(void);
	bool GotDistroyed(void);

private:
	std::unique_ptr<Timer> pAlertTimer;
	std::vector<ScenePrimitive*> m_CityParts;

	Entity *pCityModel;
	ScenePrimitive *pRadarDot;
	Camera *pCamera;

	float mHitPoints;
	float mTimerAlertBase;
	float mTimerAlertAmount;
	bool mAlertOn;
	bool mRadarAlert;
	bool mDistroyed;

	void Alert(void);
	void UpdateRadar(void);

};

