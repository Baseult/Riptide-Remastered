#pragma once

#include "../../Engine/Engine.h"

using namespace Engine;


class CAntiAim
{
public:
	CAntiAim();
	void Glitchwalk(CUserCmd * cmd, bool & bSendPacket);
	void Fakewalk(CUserCmd * cmd, bool & bSendPacket);

	//[/swap_lines]
private:
};