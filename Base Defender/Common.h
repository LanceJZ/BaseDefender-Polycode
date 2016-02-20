#pragma once
#include <Polycode.h>
#include <PolycodeView.h>
#include <Polycode3DPhysics.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <vector>
#include <fstream>
#include <iostream>
#include "Random.h"

struct Voxel
{
	Color boxColor;
	Vector3 Position;
};

class Common
{
public:
	Common();
	~Common();

	Vector3 AngleToVector(Number angle, Number magnitude);
	Number AngleToTarget(Vector3 origin, Vector3 target);
	Number RandomAngle(void);
};

