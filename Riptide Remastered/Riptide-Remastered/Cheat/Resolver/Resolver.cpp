#include "Resolver.h"

using namespace Client;

void CResolver::Override()
{
	if (!Settings::Ragebot::ResolverOverride)
		return;

	if (!GetAsyncKeyState(Settings::Ragebot::OverrideKey))
		return;

	int w, h, cx, cy;

	Interfaces::Engine()->GetScreenSize(w, h);

	cx = w / 2;
	cy = h / 2;

	Vector crosshair = Vector(cx, cy, 0);

	CBaseEntity * nearest_player = nullptr;
	float bestFoV = 0;
	Vector bestHead2D;

	CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	for (int i = 1; i <= Interfaces::GlobalVars()->maxClients; i++) //0 is always the world entity
	{

		auto pEnt = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

		if (!pEnt) continue;

		if (pEnt == LocalPlayer) continue;

		if (pEnt->IsDead()) continue;
/*
		if (pEnt->IsDormant()) continue;*/

		if (pEnt->GetTeam() == LocalPlayer->GetTeam()) continue;

		PlayerInfo pTemp;

		if (!Interfaces::Engine()->GetPlayerInfo(i, &pTemp))
			continue;

		CBaseEntity *player = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);


		Vector headPos3D = player->GetBonePosition(HITBOX_HEAD), headPos2D;

		if (!WorldToScreen(headPos3D, headPos2D))
			continue;

		float FoV2D = crosshair.DistTo(headPos2D);

		if (!nearest_player || FoV2D < bestFoV)
		{
			nearest_player = player;
			bestFoV = FoV2D;
			bestHead2D = headPos2D;
		}
	}

	if (nearest_player) //use pointers and avoid double calling of GetClientEntity
	{
		int minX = cx - (w / 10), maxX = cx + (w / 10);

		if (bestHead2D.x < minX || bestHead2D.x > maxX)
			return;

		int totalWidth = maxX - minX;

		int playerX = bestHead2D.x - minX;

		int yawCorrection = -(((playerX * 360) / totalWidth) - 180);

		float_t new_yaw = yawCorrection;

		ClampYaw(new_yaw);

		nearest_player->GetEyeAngles2()->y += new_yaw;
	}
}

void CResolver::Resolver()
{
	int resolvemode;
	int bruteforce_after_x = 5;
	CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (Settings::Ragebot::Resolver)
	{
		for (auto i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			auto pEnt = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

			if (!pEnt) continue;

			if (pEnt == pLocal) continue;

			if (pEnt->IsDead()) continue;

		/*	if (pEnt->IsDormant()) continue;*/

			if (pEnt->GetTeam() == pLocal->GetTeam()) continue;

			PlayerInfo pTemp;

			if (!Interfaces::Engine()->GetPlayerInfo(i, &pTemp))
				continue;

			auto FYaw = pEnt->GetLowerBodyYaw();
			auto pitch = pEnt->GetEyeAngles2()->x;

			pEnt->GetEyeAngles2()->y = FYaw;
			float PlayerIsMoving = abs(pEnt->GetVelocity().Length2D());
			bool bLowerBodyUpdated = false;
			bool IsBreakingLBY = false;

			bool isFakeHeading = false;

			float oldLBY = pEnt->GetLowerBodyYaw();


			if (oldLBY != pEnt->GetLowerBodyYaw())
			{
				bLowerBodyUpdated = true;
			}
			else
			{
				bLowerBodyUpdated = false;
			}

			if (pEnt->GetEyeAngles2()->y - pEnt->GetLowerBodyYaw() > 35)
			{
				isFakeHeading = true;
			}
			else
			{
				isFakeHeading = false;
			}

			float bodyeyedelta = fabs(pEnt->GetEyeAngles2()->y - pEnt->GetLowerBodyYaw());
			if (PlayerIsMoving || bLowerBodyUpdated)// || LastUpdatedNetVars->eyeangles.x != CurrentNetVars->eyeangles.x || LastUpdatedNetVars->eyeyaw != CurrentNetVars->eyeangles.y)
			{
				resolvemode = 3;
				pEnt->GetEyeAngles2()->y = FYaw;
				oldLBY = pEnt->GetEyeAngles2()->y;

				IsBreakingLBY = false;
			}
			else
			{
				resolvemode = 1;

				if (bodyeyedelta == 0.f && pEnt->GetVelocity().Length2D() >= 0 && pEnt->GetVelocity().Length2D() < 36)
				{
					pEnt->GetEyeAngles2()->y = oldLBY;
					IsBreakingLBY = true;
				}
				else
				{
					IsBreakingLBY = false;
				}
			}

			if (IsBreakingLBY)
			{
				resolvemode = 2;

				pEnt->GetEyeAngles2()->y = oldLBY;

				switch (pLocal->GetShotsFired() % 3)
				{
				case 1: pEnt->GetEyeAngles2()->y = 180; break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180;
				case 3: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + pEnt->GetEyeAngles2()->y + rand() % 35;
				}
			}
			else if (!IsBreakingLBY && !isFakeHeading)
			{
				resolvemode = 3;

				pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw();

				switch (pLocal->GetShotsFired() % 4)
				{
				case 1: pEnt->GetEyeAngles2()->y = 45 + rand() % 180;
				case 2: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 90;
				case 3: pEnt->GetEyeAngles2()->y = 180 + rand() % 90;
				case 4: pEnt->GetEyeAngles2()->y = oldLBY + pEnt->GetEyeAngles2()->y + rand() % 45;
				}
			}
			else if (isFakeHeading)
			{
				resolvemode = 2;

				pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() - pEnt->GetEyeAngles2()->y;

				switch (pLocal->GetShotsFired() % 2)
				{
				case 1: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetEyeAngles2()->y + rand() % 360; break;
				}
			}
			else if (pLocal->GetShotsFired() >= bruteforce_after_x && bruteforce_after_x != 0)
			{
				resolvemode = 2;

				pEnt->GetEyeAngles2()->y = 180;

				switch (pLocal->GetShotsFired() % 4)
				{
				case 1: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw(); break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 3: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180; break;
				case 4: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 45; break;
				}
			}
			else
			{
				resolvemode = 1;

				pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180;

				switch (pLocal->GetShotsFired() % 13)
				{
				case 1: pEnt->GetEyeAngles2()->y = 180; break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180;
				case 3: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + pEnt->GetEyeAngles2()->y + rand() % 35;
				case 4: pEnt->GetEyeAngles2()->y = 45 + rand() % 180;
				case 5: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 90;
				case 6: pEnt->GetEyeAngles2()->y = 180 + rand() % 90;
				case 7: pEnt->GetEyeAngles2()->y = oldLBY + pEnt->GetEyeAngles2()->y + rand() % 45;
				case 8: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw(); break;
				case 9: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 10: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180; break;
				case 11: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 45; break;
				case 12: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 13: pEnt->GetEyeAngles2()->y = pEnt->GetEyeAngles2()->y + rand() % 360; break;
				}
			}
		}
	}
}