#pragma once
#include "Enemy.h"
#include "RandomMover.h"
#include "RandomShooter.h"

class Angreifer : public Enemy, RandomMover, RandomShooter //Enemy that seeks out city while randomly shooting. Common.
{
public:
	Angreifer();
	~Angreifer();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void UpdateShots(Number *elapsed);

private:
	CollisionScene *pScene;
};

