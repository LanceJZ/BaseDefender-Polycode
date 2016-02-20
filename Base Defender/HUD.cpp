#include "HUD.h"

HUD::HUD(void)
{
	pOverlayModel = new Entity();
}

HUD::~HUD(void)
{
}

void HUD::Setup(CollisionScene * scene)
{
	pCamera = scene->getDefaultCamera();
	ScenePrimitive *bottom;
	ScenePrimitive *radarBack;
	ScenePrimitive *radar;
	bottom = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 280, 25, 0.1);
	bottom->setPosition(0, -70, 9);
	bottom->setColor(0.135, 0.05, 0.95, 1);
	radarBack = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 120.25, 20.25, 0.1);
	radarBack->setPosition(0, -68.2, 9.1);
	radarBack->setColor(0.05, 0, 0.165, 1);
	//radar = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.25, 0.25, 0.1);
	//radar->setPosition(0, -78, 10); //Bottom of radar
	//radar->setPosition(0, -58, 10); //Top of radar
	//radar->setPosition(60, -70, 10); //Right of radar
	//radar->setPosition(-60, -70, 10); //Left of radar
	pOverlayModel->addChild(bottom);
	pOverlayModel->addChild(radarBack);
	scene->addChild(pOverlayModel);
}

void HUD::Update(Number * elapsed)
{
	pOverlayModel->setPositionX(pCamera->getPosition().x);
}

void HUD::Activate(void)
{
}

void HUD::Deactivate(void)
{
}

void HUD::NewGame(void)
{
}

void HUD::Reset(void)
{
}
