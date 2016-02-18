#pragma once
#include "Actor.h"

class PlayerShot : public Actor
{
public:
	PlayerShot();
	~PlayerShot();

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void Activate(void);
	void Deactivate(void);

};

