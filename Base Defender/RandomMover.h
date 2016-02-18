#pragma once
#include "Common.h"

class RandomMover : Common
{
public:
	RandomMover();
	~RandomMover();

	void Update(Number *elapsed);

protected:
	float mMoveSpeed;
	float mMoveTimerAmount;
	float mMoveTimerBase;

	Vector3 VectorChange(void);
	bool DoesMovementChange(void);

private:
	std::unique_ptr<Timer> pMoveTimer;
};

