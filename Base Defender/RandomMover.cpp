#include "RandomMover.h"

RandomMover::RandomMover()
{
	mMoveTimerAmount = 0;
	pMoveTimer = std::unique_ptr<Timer>(new Timer(false, 0));
	pMoveTimer->Reset();
}

RandomMover::~RandomMover()
{
}

void RandomMover::Update(Number * elapsed)
{
}

Vector3 RandomMover::VectorChange(void)
{
	return AngleToVector(Random::Number(0, 2 * PI), Random::Number(mMoveSpeed / 16, mMoveSpeed));
}

bool RandomMover::DoesMovementChange(void)
{
	if (pMoveTimer->getElapsedf() > mMoveTimerAmount)
	{
		pMoveTimer->Reset();
		mMoveTimerAmount = Random::Number(mMoveTimerBase / 10, mMoveTimerBase);
		return true;
	}

	return false;
}
