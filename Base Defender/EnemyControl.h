#pragma once
#include "Angreifer.h"

class EnemyControl
{
public:
	EnemyControl();
	~EnemyControl();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);
	void PlayerPointer(std::shared_ptr<Player> playerSP);

private:
	CollisionScene *pScene;
	std::shared_ptr<Player> pPlayer;
	std::vector<std::unique_ptr<Angreifer>> vp_Angreifers;

	UINT mNumberOfAngreifers;
	std::unique_ptr<Timer> pAngreiferSpawnTimer;
	std::unique_ptr<Timer> pCityHuntTimer;
	float mAngreiferSpawnTimerAmount;
	float mCityHuntTimerAmount;

	void SpawnAngreifers(int numberOfShips);
	void SendAngreiferToCity(void);
	void SpawnAngriff_auf_Stadt(Vector3 postion, Vector3 velocity, UINT cityAttacking, Vector3 cityPosition);
	void SpawnmAngreiferFC(Vector3 position, Vector3 velocity);
	void SpawnJäger(Vector3 position, Vector3 velocity);
};

