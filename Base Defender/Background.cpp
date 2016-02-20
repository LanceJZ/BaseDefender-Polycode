#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Setup(CollisionScene * scene)
{
	pScene = scene;

	std::vector<ScenePrimitive*> boxs;

	for (int star = 0; star < 4000; star++) //Main Star field
	{
		SceneMesh *dot;
		SceneMesh *dotSide;
		dot = new SceneMesh(Mesh::POINT_MESH);
		dot->getMesh()->addVertex(0, 0, 0);
		dotSide = new SceneMesh(Mesh::POINT_MESH);
		dotSide->getMesh()->addVertex(0, 0, 0);
		dot->setPosition(Vector3(Random::Number(-1200, 1200), Random::Number(-100, 100), -1));
		pScene->addChild(dot);

		if (dot->getPosition().x > 1050)
		{
			dotSide->setPosition(dot->getPosition().x - 1600, dot->getPosition().y, -1);
			//pScene->addChild(dotSide);
		}
		else if (dot->getPosition().x < -1050)
		{
			dotSide->setPosition(dot->getPosition().x + 1600, dot->getPosition().y, -1);
			//pScene->addChild(dotSide);
		}
	}
}