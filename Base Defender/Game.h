#pragma once
#include "Load.h"
#include <vector>
#include "Player.h"
#include "Background.h"
#include "EnemyControl.h"
#include "City.h"
#include "HUD.h"

namespace ptree = boost::property_tree;
using namespace Polycode;

class Game : public Load, public EventHandler
{
public:
	Game(PolycodeView *view);
	~Game();

	void handleEvent(Event *events);
	bool Update(void);

private:
	Core *pCore;
	CollisionScene *pScene;

	bool m_Exit;
	bool m_Paused;

	void handlePlayerInput(void);
};

