#pragma once
#include "Common.h"
#include "Random.h"

class Background
{
public:
	Background();
	~Background();

	void Setup(CollisionScene *scene);

private:
	CollisionScene *pScene;
	Camera *pCamera;
};

