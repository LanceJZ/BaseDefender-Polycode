#include "Actor.h"

Actor::Actor(void)
{
	m_Active = false;

	m_Rotation.Amount = 0;
	m_Rotation.Acceleration = 0;
	m_Rotation.Velocity = 0;

	m_WindowWidth = 800 / (80 / 3.7);
	m_WindowHeight = 720 / (80 / 3.7);
}

//Protected methods
bool Actor::CheckForXLeft(void)
{
	if (m_Position.x - m_Radius < -m_WindowWidth)
	{
		m_Position.x = -m_WindowWidth + m_Radius;
		return true;
	}

	return false;
}

bool Actor::CheckForXRight(void)
{
	if (m_Position.x + m_Radius > m_WindowWidth)
	{
		m_Position.x = m_WindowWidth - m_Radius;
		return true;
	}

	return false;
}

bool Actor::CheckForYBottom(void)
{
	if (m_Position.y - m_Radius < -m_WindowHeight)
	{
		m_Position.y = -m_WindowHeight + m_Radius;
		return true;
	}

	return false;
}

bool Actor::CheckForYTop(void)
{
	if (m_Position.y + m_Radius > m_WindowHeight)
	{
		m_Position.y = m_WindowHeight - m_Radius;
		return true;
	}

	return false;
}

void Actor::BounceX(void)
{
	m_Velocity.x *= 0.5f;
	m_Velocity.x *= -1.0f;
	m_Acceleration = 0;		
}

void Actor::BounceY(void)
{
	m_Velocity.y *= 0.5f;
	m_Velocity.y *= -1.0f;
	m_Acceleration = 0;
}

void Actor::Decelerate(void)
{
	if (m_Velocity.x != 0 || m_Velocity.y != 0)
	{
		float x = m_Velocity.x * -1;
		x *= m_DecelerationX;
		x /= 1;
		m_Acceleration.x = x;

		float y = m_Velocity.y * -1;
		y *= m_DecelerationY;
		y /= 1;
		m_Acceleration.y = y;
	}
}

std::vector<ScenePrimitive*> Actor::LoadVoxEntity(std::string filename, Entity * model)
{
	std::vector<ScenePrimitive*> parts = Load::ReadBoxes(filename);
	Load::ReadVoxelEntity(model, parts);

	return parts;
}

void Actor::Update(Number *elapsed)
{
	//Calculate movement this frame according to velocity and acceleration.
	m_Velocity += m_Acceleration;
	m_Position += (m_Velocity * *elapsed);
	//Calculate rotation this frame according to velocity and acceleration.
	m_Rotation.Velocity += m_Rotation.Acceleration;
	m_Rotation.Amount += (m_Rotation.Velocity * *elapsed);
	//Flip rotation to zero when it makes a full rotation.
	m_Rotation.Amount += 360 % 360;
	//Update rectangle. rectangle is always centered to the entity.
	m_Rectangle.x = m_Position.x;
	m_Rectangle.y = m_Position.y;
}

bool Actor::CirclesIntersect(Polycode::Vector3 target, float targetRadius)
{
	Number dx = target.x - m_Position.x;
	Number dy = target.y - m_Position.y;
	float rad = m_Radius + targetRadius;

	if ((dx * dx) + (dy * dy) < rad * rad)
		return true;

	return false;
}

bool Actor::RectangleIntersect(Polycode::Rectangle target)
{
	Number max = m_Rectangle.x + m_Rectangle.w;
	Number min = m_Rectangle.x - m_Rectangle.w;
	Number targetmax = target.x + target.w + m_Rectangle.w;
	Number targetmin = target.x - target.w - m_Rectangle.w;

	bool OverlapX = ValueInRange(target.x, min, max) ||
		ValueInRange(m_Rectangle.x, targetmin, targetmax);

	max = m_Rectangle.y + m_Rectangle.h;
	min = m_Rectangle.y - m_Rectangle.h;
	targetmax = target.y + target.h + m_Rectangle.h;
	targetmin = target.y - target.h - m_Rectangle.h;

	bool OverlapY = ValueInRange(target.y, min, max) ||
		ValueInRange(m_Rectangle.y, targetmin, targetmax);

	return OverlapX && OverlapY;
}

bool Actor::ValueInRange(Number value, Number min, Number max)
{
	return (value >= min) && (value <= max);
}
