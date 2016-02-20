#include "Common.h"

Common::Common()
{
}

Common::~Common()
{
}

Vector3 Common::AngleToVector(Number angle, Number magnitude)
{
	return Vector3(std::cos(angle) * magnitude, std::sin(angle) * magnitude, 0);
}

Number Common::AngleToTarget(Vector3 origin, Vector3 target)
{
	return std::atan2(target.y - origin.y, target.x - origin.x);
}

Number Common::RandomAngle(void)
{
	return Random::Number(0, 2 * PI);
}
