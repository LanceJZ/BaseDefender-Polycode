#include "Game.h"

std::shared_ptr<Player> sp_Player(new Player);
std::unique_ptr<Background> up_Background(new Background);
std::shared_ptr<EnemyControl> sp_Enemy(new EnemyControl);
std::unique_ptr<City> up_City(new City);
std::unique_ptr<HUD> up_HUD(new HUD);

Game::Game(PolycodeView *view) : EventHandler()
{
	m_Exit = false;
	pCore = new POLYCODE_CORE(view, 1280, 720, false, true, 0, 0, 120, 0, true);
	pScene = new CollisionScene(CollisionScene::SCENE_3D);
	pCore->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", true);

	//SceneLight *light;

	//light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 98000);
	//light->setPosition(-500, -500, 500);
	//light->setLightColor(1, 1, 1);
	//pScene->addLight(light);

	//light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 36000);
	//light->setPosition(500, -70, 500);
	//light->setLightColor(1, 1, 1);
	//pScene->addLight(light);

	pScene->getDefaultCamera()->setPositionZ(200);

	up_Background->Setup(pScene);
	sp_Player->Setup(pScene);
	sp_Enemy->PlayerPointer(sp_Player);
	sp_Enemy->Setup(pScene);
	up_City->Setup(pScene, Vector3(0, -60, 0));
	up_HUD->Setup(pScene);

	m_Paused = false;
}

Game::~Game()
{
}

void Game::handleEvent(Event * events)
{
	if (events->getDispatcher() == pCore->getInput())
	{

		InputEvent *inputEvent = (InputEvent*)events;

		if (inputEvent->keyCode() == KEY_ESCAPE)
			m_Exit = true;
	}
}

bool Game::Update(void)
{
	if (!m_Paused)
	{
		pCore->doSleep();

		Number frameelapsed = pCore->getElapsed();
		Number *elapsed = &frameelapsed;

		if (sp_Player->m_Active)
		{
			sp_Player->Update(elapsed);
			handlePlayerInput();
		}

		sp_Enemy->Update(elapsed);
		sp_Enemy->UpdateShots(elapsed);
		sp_Player->UpdateShots(elapsed);
		up_HUD->Update(elapsed);
		up_City->Update(elapsed);
	}


	if (m_Exit)
	{
		return false;
	}

	return pCore->updateAndRender();
}

void Game::handlePlayerInput(void)
{
	//Main keys.
	bool key_up = pCore->getInput()->getKeyState(KEY_UP);
	bool key_down = pCore->getInput()->getKeyState(KEY_DOWN);
	bool key_thrust = pCore->getInput()->getKeyState(KEY_LCTRL);
	bool key_left = pCore->getInput()->getKeyState(KEY_LEFT);
	bool key_right = pCore->getInput()->getKeyState(KEY_RIGHT);
	bool key_fire = pCore->getInput()->getKeyState(KEY_LSHIFT);
	//Alternative keys.
	bool key_thrustalt = pCore->getInput()->getKeyState(KEY_q);
	bool key_upalt = pCore->getInput()->getKeyState(KEY_w);
	bool key_downalt = pCore->getInput()->getKeyState(KEY_s);
	bool key_leftalt = pCore->getInput()->getKeyState(KEY_a);
	bool key_rightalt = pCore->getInput()->getKeyState(KEY_d);
	bool key_firealt = pCore->getInput()->getKeyState(KEY_SPACE);

	if (key_up)
	{
		sp_Player->MoveUp();
	}
	else if (key_down)
	{
		sp_Player->MoveDown();
	}

	if (key_thrust)
	{
		sp_Player->ThrustOn();
	}
	else
	{
		sp_Player->ThrustOff();
	}

	if (key_right)
	{
		sp_Player->TurnRight();
	}

	if (key_left)
	{
		sp_Player->TurnLeft();
	}

	if (key_fire)
	{
		sp_Player->FireShot();
	}
}