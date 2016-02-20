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

	SpawnAngreifers(20);
}

void EnemyControl::Update(Number * elapsed)
{
	for (size_t ship = 0; ship < vup_Angreifers.size(); ship++)
	{
		if (vup_Angreifers.at(ship)->m_Active)
			vup_Angreifers.at(ship)->Update(elapsed);
	}
}

void EnemyControl::UpdateShots(Number * elapsed)
{
	for (size_t ship = 0; ship < vup_Angreifers.size(); ship++)
	{
		vup_Angreifers.at(ship)->UpdateShots(elapsed);
	}
}

void EnemyControl::PlayerPointer(std::shared_ptr<Player> playerPointer)
{
	spPlayer = playerPointer;
}

void EnemyControl::SpawnAngreifers(int numberOfShips)
{
	for (int shipNum = 0; shipNum < numberOfShips; shipNum++)
	{
		bool spawnNewShip = true;
		int spawnShip = 0;

		for (size_t ship = 0; ship < vup_Angreifers.size(); ship++)
		{
			if (!vup_Angreifers.at(ship)->m_Active)
			{
				spawnNewShip = false;
				spawnShip = ship;
				break;
			}
		}

		if (spawnNewShip)
		{
			vup_Angreifers.push_back(std::unique_ptr<Angreifer>(new Angreifer));
			spawnShip = vup_Angreifers.size() - 1;
			vup_Angreifers.at(spawnShip)->Setup(pScene);
			vup_Angreifers.at(spawnShip)->PlayerPointer(spPlayer);
		}

		vup_Angreifers.at(spawnShip)->Reset();
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
