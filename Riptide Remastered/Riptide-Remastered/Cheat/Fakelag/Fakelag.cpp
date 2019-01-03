#include "Fakelag.h"


using namespace Client;


void CFakeLag::Fakelag(CUserCmd * cmd, bool& bSendPacket)
{
	if (Settings::Ragebot::FakeLags <= 0)
		return;

	CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (!Interfaces::Engine()->IsInGame())
		return;

	if (Settings::Ragebot::FakeLags == 1)
	{
		if (Interfaces::Engine()->IsInGame() && LocalPlayer && IsLocalAlive())
		{
			if (cmd->weaponselect != 0 || cmd->buttons & IN_ATTACK)
			{
				choked = Settings::Ragebot::Fakelag_amt - 1;
			}
			else
			{
				choked = choked > Settings::Ragebot::Fakelag_amt - 1 ? 0 : choked + 1;
				bSendPacket = choked < 1;
			}

		}
	}

	if (Settings::Ragebot::FakeLags == 2) {
		if (ticks >= ticksMax)
		{
			bSendPacket = true;
			ticks = 0;
		}
		else
		{
			bSendPacket = ticks < ticksMax - Settings::Ragebot::Fakelag_amt;
		}
	}
	else if (Settings::Ragebot::FakeLags == 3) { // Switch
		static int FakelagFactor = Settings::Ragebot::Fakelag_amt;
		bSendPacket = 1 ? !(ticks % (FakelagFactor + 1)) : 1;
		if (bSendPacket) {
			FakelagFactor = (rand() % 7) + 6;
		}
	}
	else if (Settings::Ragebot::FakeLags == 4) { // Pulsive

		Vector vel = LocalPlayer->GetVelocity();
		vel.z = 0.0f;

		int f = (int)(ceilf((64.0f / 0.0078125f) / vel.Length()));

		if (Settings::Ragebot::Fakelag_amt > 0)
		{
			if (f > Settings::Ragebot::Fakelag_amt)
				f = Settings::Ragebot::Fakelag_amt;
		}
		else
		{
			if (f > 14)
				f = 14;
		}
		if (f < 1)
			f = 1;

		bSendPacket = 1 ? !(ticks % (f)) : 1;
	}

	ticks++;
}