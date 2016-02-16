#include "Game.h"

std::shared_ptr<Player> p_Player(new Player);
std::unique_ptr<Background> p_Background(new Background);

Game::Game(PolycodeView *view) : EventHandler()
{
	m_Exit = false;
	pCore = new POLYCODE_CORE(view, 1280, 720, false, true, 0, 0, 90, 0, true);
	pScene = new CollisionScene(CollisionScene::SCENE_3D);
	pCore->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addDirResource("Resources", true);

	SceneLight *light;

	light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 98000);
	light->setPosition(-500, -500, 500);
	light->setLightColor(1, 1, 1);
	pScene->addLight(light);

	light = new SceneLight(SceneLight::POINT_LIGHT, pScene, 36000);
	light->setPosition(500, -70, 500);
	light->setLightColor(1, 1, 1);
	pScene->addLight(light);

	pScene->getDefaultCamera()->setPositionZ(200);

	p_Background->Setup(pScene);
	p_Player->Setup(pScene);

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

		if (p_Player->m_Active)
		{
			p_Player->Update(&frameelapsed);
			handlePlayerInput();
		}
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
	bool key_thrust = pCore->getInput()->getKeyState(KEY_LSHIFT);
	bool key_left = pCore->getInput()->getKeyState(KEY_LEFT);
	bool key_right = pCore->getInput()->getKeyState(KEY_RIGHT);
	bool key_fire = pCore->getInput()->getKeyState(KEY_LCTRL);
	//Alternative keys.
	bool key_thrustalt = pCore->getInput()->getKeyState(KEY_q);
	bool key_upalt = pCore->getInput()->getKeyState(KEY_w);
	bool key_downalt = pCore->getInput()->getKeyState(KEY_s);
	bool key_leftalt = pCore->getInput()->getKeyState(KEY_a);
	bool key_rightalt = pCore->getInput()->getKeyState(KEY_d);
	bool key_firealt = pCore->getInput()->getKeyState(KEY_SPACE);

	if (key_up)
	{
		p_Player->MoveUp();
	}
	else if (key_down)
	{
		p_Player->MoveDown();
	}

	if (key_thrust)
	{
		p_Player->ThrustOn();
	}
	else
	{
		p_Player->ThrustOff();
	}

	if (key_right)
	{
		p_Player->TurnRight();
	}

	if (key_left)
	{
		p_Player->TurnLeft();
	}
}