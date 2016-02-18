#include "EnemyControl.h"

std::shared_ptr<Angreifer> p_Angreifer(new Angreifer);

EnemyControl::EnemyControl()
{
}

EnemyControl::~EnemyControl()
{
}

void EnemyControl::Setup(CollisionScene * scene)
{
	pScene = scene;

	SpawnAngreifers(10);
}

void EnemyControl::Update(Number * elapsed)
{
	for (size_t ship = 0; ship < vp_Angreifers.size(); ship++)
	{
		if (vp_Angreifers.at(ship)->m_Active)
			vp_Angreifers.at(ship)->Update(elapsed);
	}
}

void EnemyControl::UpdateShots(Number * elapsed)
{
	for (size_t ship = 0; ship < vp_Angreifers.size(); ship++)
	{
		vp_Angreifers.at(ship)->UpdateShots(elapsed);
	}
}

void EnemyControl::PlayerPointer(std::shared_ptr<Player> playerPointer)
{
	pPlayer = playerPointer;
}

void EnemyControl::SpawnAngreifers(int numberOfShips)
{
	for (int shipNum = 0; shipNum < numberOfShips; shipNum++)
	{
		bool spawnNewShip = true;
		int spawnShip = 0;

		for (size_t ship = 0; ship < vp_Angreifers.size(); ship++)
		{
			if (!vp_Angreifers.at(ship)->m_Active)
			{
				spawnNewShip = false;
				spawnShip = ship;
				break;
			}
		}

		if (spawnNewShip)
		{
			vp_Angreifers.push_back(std::unique_ptr<Angreifer>(new Angreifer));
			spawnShip = vp_Angreifers.size() - 1;
			vp_Angreifers.at(spawnShip)->Setup(pScene);
			vp_Angreifers.at(spawnShip)->PlayerPointer(pPlayer);
		}

		vp_Angreifers.at(spawnShip)->Reset();
	}
}

void EnemyControl::SendAngreiferToCity(void)
{
}

void EnemyControl::SpawnAngriff_auf_Stadt(Vector3 postion, Vector3 velocity, UINT cityAttacking, Vector3 cityPosition)
{
}

void EnemyControl::SpawnmAngreiferFC(Vector3 position, Vector3 velocity)
{
}

void EnemyControl::SpawnJäger(Vector3 position, Vector3 velocity)
{
}
