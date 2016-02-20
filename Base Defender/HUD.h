#pragma once
#include "Actor.h"

class HUD :	public Actor
{
public:
	HUD(void);
	~HUD(void);

	void Setup(CollisionScene *scene);
	void Update(Number *elapsed);
	void Activate(void);
	void Deactivate(void);
	void NewGame(void);
	void Reset(void);

private:
	CollisionScene *pScene;
	Entity *pOverlayModel;
	Camera *pCamera;

};
