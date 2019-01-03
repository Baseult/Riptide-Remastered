#include "Antiaim.h"
#pragma warning(disable:4244)

using namespace Client;

CAntiAim::CAntiAim()
{
	CMe* m_pLocal;
}

void  CAntiAim::Glitchwalk(CUserCmd * cmd, bool& bSendPacket)
{
	CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (Settings::Ragebot::glitch_bool)
	{

		static int iChoked = -1;
		iChoked++;

		static bool slowmo;
		slowmo = !slowmo;


		const auto lag = 90;


		if (iChoked < lag)
		{

			bSendPacket = false;
			if (slowmo)
			{
				cmd->tick_count = INT_MAX;
				cmd->command_number += INT_MAX + cmd->tick_count % 2 ? 1 : 0;
				cmd->buttons |= IN_FORWARD;
				cmd->buttons |= IN_LEFT;
				cmd->buttons |= IN_BACK;
				cmd->forwardmove = cmd->sidemove = 0.f;
			}
			else
			{
				bSendPacket = true;
				iChoked = -1;
				Interfaces::GlobalVars()->frametime *= (LocalPlayer->GetVelocity().Length2D()) / 1.2;
				cmd->buttons |= IN_FORWARD;
			}

		}
		else
		{
			if (!bSendPacket)
			{

				if (slowmo)
				{
					cmd->tick_count = INT_MAX;
					cmd->command_number += INT_MAX + cmd->tick_count % 2 ? 1 : 0;
					cmd->buttons |= IN_FORWARD;
					cmd->buttons |= IN_LEFT;
					cmd->buttons |= IN_BACK;
					cmd->forwardmove = cmd->sidemove = 0.f;
				}

			}
			else
			{

				if (slowmo)
				{
					bSendPacket = true;
					iChoked = -1;
					cmd->tick_count = INT_MAX;
					Interfaces::GlobalVars()->frametime *= (LocalPlayer->GetVelocity().Length2D()) / 1.25;
					cmd->buttons |= IN_FORWARD;
				}

			}
		}

	}
}

void CAntiAim::Fakewalk(CUserCmd * cmd, bool& bSendPacket)
{
	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (GetAsyncKeyState(Settings::Ragebot::fakewalk))
	{
		static int chocking = -1;
		chocking++;

		if (chocking < (int)Settings::Ragebot::walkspeed)
		{
			bSendPacket = false;
			cmd->tick_count += 10;
			cmd += 7 + cmd->tick_count % 2 ? 0 : 1;
			cmd->buttons |= g_pPlayers->GetLocal()->m_pEntity->movetype() == IN_BACK;
			cmd->forwardmove = cmd->sidemove = 0.f;
		}
		else
		{
			bSendPacket = true;
			chocking = -1;
			Interfaces::GlobalVars()->frametime *= (pPlayer->GetVelocity().Length2D()) / 1.f;
			cmd->buttons |= g_pPlayers->GetLocal()->m_pEntity->movetype() == IN_FORWARD;
		}
	}
}
