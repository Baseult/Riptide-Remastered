#pragma once

#include "../../Engine/Engine.h"

inline float ClampYaw(float yaw)
{
	while (yaw > 180.f)
		yaw -= 360.f;
	while (yaw < -180.f)
		yaw += 360.f;
	return yaw;
}

namespace Engine
{
	class CPlayer;
}

using namespace Engine;

class CResolver
{
public:
	//[/swap_lines]
	void Override();
	void Resolver();
private:
};