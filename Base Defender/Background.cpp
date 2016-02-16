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
		dot = new SceneMesh(Mesh::POINT_MESH);
		dot->getMesh()->addVertex(0, 0, 0);
		dot->setPosition(Vector3(-800 + Random::Number(0, 1600), -100 + Random::Number(0, 200), -1));
		pScene->addChild(dot);
	}

	for (int star = 0; star < 100; star++) //Right Star field
	{
		SceneMesh *dot;
		dot = new SceneMesh(Mesh::POINT_MESH);
		dot->getMesh()->addVertex(0, 0, 0);
		dot->setPosition(Vector3(Random::Number(800, 1200), -100 + Random::Number(0, 200), -1));
		pScene->addChild(dot);
	}

	for (int star = 0; star < 100; star++) //Left Star field
	{
		SceneMesh *dot;
		dot = new SceneMesh(Mesh::POINT_MESH);
		dot->getMesh()->addVertex(0, 0, 0);
		dot->setPosition(Vector3(-1600 + Random::Number(0, 800), -100 + Random::Number(0, 200), -1));
		pScene->addChild(dot);
	}
}