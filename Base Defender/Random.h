#pragma once
#include <random>
#include <time.h>
#include <memory>
#include <algorithm>

class Random
{
public:
	//Random number generator
	static double Number(double Min, double Max);
	static float Clip(float number, float lower, float upper);
	static void Setup(void);
};
