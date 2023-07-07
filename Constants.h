#pragma once 

#include <string>

#include "template.h"

namespace Assets{
	const std::string BallPngPath = "assets\\ball.png";
	const std::string StoneBrick = "assets\\brick.png";
	const std::string EdgeLavaTile = "assets\\edgeLavaTile.png";
	const std::string FinishLineTile = "assets\\finishLine.png";
}

namespace Constants {
	const int PhysicsTickInterval = 5; //ms
	
	const int WindowWidth = 1920;
	const int WindowHeight = 1080;

	const float H1LableHeight =  100.0f;
	const float H2LableHeight =  35.0f;

	const int DefaultBlockWidthHeight = 75;

};