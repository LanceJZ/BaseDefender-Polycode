#pragma once
#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
#include "PolyRectangle.h"
#include "Load.h"

struct Rotate
{
	float Amount;
	float Velocity;
	float Acceleration;
};

class Actor : public Load
{
public:
	Actor(void);

	bool m_Hit;
	bool m_Spawn;
	bool m_GameOver;

	void Update(Number *elapsed);
	bool CirclesIntersect(Vector3 target, float targetRadius);
	bool RectangleIntersect(Polycode::Rectangle target);
	bool ValueInRange(Number value, Number min, Number max);

	bool m_Active;
	float m_Radius;
	Vector3 m_Position;
	Vector3 m_Velocity;
	Vector3 m_Acceleration;
	Rotate m_Rotation; //In Degrees
	
protected:
	float m_WindowHeight;
	float m_WindowWidth;
	float m_DecelerationX; //Amount of deceleration on X per frame.
	float m_DecelerationY; //Amount of deceleration on Y per frame.

	Polycode::Rectangle m_Rectangle;
	Polycode::Rectangle m_InsideBorder;

	bool CheckForXLeft(void);
	bool CheckForXRight(void);
	bool CheckForYBottom(void);
	bool CheckForYTop(void);
	void BounceX(void);
	void BounceY(void);
	void Decelerate(void); // Decelerate actor.

	std::vector<ScenePrimitive*> LoadVoxEntity(std::string filename, Entity *model);
};
