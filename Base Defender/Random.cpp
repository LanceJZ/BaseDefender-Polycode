#include "Random.h"
//Random Number Generator
static std::mt19937 m_Random;

void Random::Setup(void)
{
	// Initiate Random Number Generator
	m_Random.seed(unsigned long(time(0)));
}

double Random::Number(double Min, double Max)
{
	bool negitiveMin = false;
	bool negitiveMax = false;

	int MinNegitive = 0;

	if (Min < 0)
	{
		negitiveMin = true;
		Min *= -1;
	}

	if (Max < 0)
	{
		negitiveMax = true;
		Max *= -1;
	}

	if (negitiveMin && !negitiveMax)
	{
		Max += Min;
		MinNegitive = Min;
		Min = 0;
	}

	std::uniform_real_distribution<double> roll(Min, Max);
	double ranNum = roll(m_Random);

	if (negitiveMin && !negitiveMax)
		ranNum -= MinNegitive;

	if (negitiveMin && negitiveMax)
		ranNum *= -1;

	return ranNum;
}

float Random::Clip(float number, float lower, float upper)
{
	return std::max(lower, std::min(number, upper));
}