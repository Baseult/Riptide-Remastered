#include "Misc.h"


using namespace Client;
//[junk_enable /]
//[enc_string_enable /]
void CMisc::OnRender()
{
	if (Settings::Misc::misc_Punch2)
	{
		CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		if (Interfaces::Engine()->IsInGame() && localplayer)
		{
			Vector ViewAngles;
			Interfaces::Engine()->GetViewAngles(ViewAngles);
			ViewAngles += (localplayer->GetAimPunchAngle()) * 2.f;

			Vector fowardVec;
			AngleVectors(ViewAngles, fowardVec);
			fowardVec *= 10000;

			Vector start = localplayer->GetEyePosition();
			Vector end = start + fowardVec, endScreen;

			if (WorldToScreen(end, endScreen) && IsLocalAlive())
			{
				g_pRender->DrawLine(endScreen.x + 7, endScreen.y + 0.5, endScreen.x - 8, endScreen.y + 0.5, Color::Red());
				g_pRender->DrawLine(endScreen.x + 0, endScreen.y + 7, endScreen.x + 0, endScreen.y - 8, Color::Red());
			}
		}
	}
}




void CMisc::OnEvents(IGameEvent* pEvent)
{
	if (Settings::Misc::Killmessage)
	{
		if (!strcmp(pEvent->GetName(), "player_death"))
		{
			int attacker = Interfaces::Engine()->GetPlayerForUserID(pEvent->GetInt("attacker"));
			int userid = Interfaces::Engine()->GetPlayerForUserID(pEvent->GetInt("userid"));
			if (attacker != userid)
			{
				if (attacker == Interfaces::Engine()->GetLocalPlayer())
				{
					Interfaces::Engine()->ExecuteClientCmd("say You just got killed by riptide.tk cheat!");
					if (attacker = userid)
					{
						Interfaces::Engine()->ExecuteClientCmd("say You just got killed by riptide.tk cheat!");
					}
				}
			}
		}
	}
}

void CMisc::OnCreateMove(CUserCmd* cmd)
{
	CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	static bool gravityTurnedOn = false;

	if (Settings::Misc::misc_ragdoll_gravity) {
		ConVar* Gravity = Interfaces::GetConVar()->FindVar("cl_ragdoll_gravity");
		Gravity->SetValue(Settings::Misc::misc_ragdoll_gravity_amount);
		gravityTurnedOn = true;
	}
	else {
		if (gravityTurnedOn == true) {
			ConVar* Gravity = Interfaces::GetConVar()->FindVar("cl_ragdoll_gravity");
			Gravity->SetValue(800.f);
			gravityTurnedOn = false;
		}
	}

	static bool pushscaleTurnedOn = false;

	if (Settings::Misc::misc_pushscale) {
		ConVar* Pushscale = Interfaces::GetConVar()->FindVar("phys_pushscale");
		Pushscale->SetValue(Settings::Misc::misc_pushscale_amount);
		pushscaleTurnedOn = true;
	}
	else {
		if (pushscaleTurnedOn == true) {
			ConVar* Pushscale = Interfaces::GetConVar()->FindVar("phys_pushscale");
			Pushscale->SetValue(600.f);
			pushscaleTurnedOn = false;
		}
	}

	if (Settings::Misc::misc_Bhop)
	{
		static bool bLastJumped = false;
		static bool bShouldFake = false;

		if (!localplayer)
			return;

		if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
			return;

		if (!bLastJumped && bShouldFake)
		{
			bShouldFake = false;             
			cmd->buttons |= IN_JUMP;
		}
		else if (cmd->buttons & IN_JUMP)
		{
			if (g_pPlayers->GetLocal()->iFlags & FL_ONGROUND)
			{
				bLastJumped = true;
				bShouldFake = true;
			}
			else
			{
				cmd->buttons &= ~IN_JUMP;
				bLastJumped = false;
			}
		}
		else
		{
			bLastJumped = false;
			bShouldFake = false;
		}
	}

	if (Settings::Misc::misc_Telehop)
	{
		static bool bDirection = true;
		static bool takethatshitoff = false;
		int iFlags = g_pPlayers->GetLocal()->iFlags;

		if ((cmd->buttons & IN_JUMP) && (iFlags & FL_ONGROUND))
		{
			cmd->forwardmove = 450;
		}

		if ((cmd->buttons & IN_JUMP) || !(iFlags &
			FL_ONGROUND)) {
			if (bDirection)
			{
				cmd->sidemove = -450.f;
				bDirection = false;
			}
			else
			{
				cmd->sidemove = +450.f;
				bDirection = true;
			}
		}
	}



	if (Settings::Misc::misc_spamregular)
		ChatSpamRegular();

	if (Settings::Misc::misc_spamrandom)
		ChatSpamRandom();

	if (Settings::Misc::misc_Clan > 0)
		ClanTag();

	if (Settings::Misc::misc_AutoStrafe == 1 && !(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND))
	{
		if (cmd->mousedx > 1 || cmd->mousedx < -1)
		{
			cmd->sidemove = cmd->mousedx < 0.f ? -400.f : 400.f;
		}
	}
	else if (Settings::Misc::misc_AutoStrafe == 2 && !(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND))
	{
			bool bKeysPressed = true;
			if (GetKeyState(0x41) || GetKeyState(0x57) || GetKeyState(0x53) || GetKeyState(0x44)) bKeysPressed = false;

			if ((GetAsyncKeyState(VK_SPACE) && !(localplayer->GetFlags() & FL_ONGROUND)) && bKeysPressed)
			{
				if (cmd->mousedx > 1 || cmd->mousedx < -1) {
					cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
				}
				else {
					cmd->forwardmove = (1800.f * 4.f) / localplayer->GetVelocity().Length2D();
					cmd->sidemove = (cmd->command_number % 2) == 0 ? -450.f : 450.f;
					if (cmd->forwardmove > 450.f)
						cmd->forwardmove = 450.f;
				}
			}
		
	}

	if (Settings::Misc::misc_AntiAfk)
	{
		static bool Jitter;
		Jitter = !Jitter;
		if (Jitter)
			cmd->sidemove += 450;
		else
			cmd->sidemove = -450;

		if (!Jitter)
			cmd->forwardmove = -450;
		else
			cmd->forwardmove = +450;

		cmd->buttons += IN_MOVELEFT;
	}

	ConVar* skybox = Interfaces::GetConVar()->FindVar("sv_skyname");

	if (Settings::Misc::misc_SkyName) { if (skybox) skybox->SetValue(Settings::Misc::misc_SkyName); }
	if (Settings::Misc::misc_NoSky) { if (skybox) skybox->SetValue("sky_l4d_rural02_ldr"); }

	ConVar* snow = Interfaces::GetConVar()->FindVar("mat_drawgray");

	if (Settings::Misc::misc_Snow)
	{
		snow->SetValue(1);
	}
	else
	{
		snow->SetValue(0);
	}

	

	


	if (Settings::Misc::misc_radiospam)
	{
		const char* radioCommands[] = {
			"coverme",
			"takepoint",
			"holdpos",
			"regroup",
			"followme",
			"takingfire",
			"go",
			"fallback",
			"sticktog",
			"report",
			"roger",
			"enemyspot",
			"needbackup",
			"sectorclear",
			"inposition",
			"reportingin",
			"getout",
			"negative",
			"enemydown",
		};

		Interfaces::Engine()->ClientCmd_Unrestricted2(radioCommands[std::rand() % ARRAYSIZE(radioCommands)]);
	}
	if (Settings::Misc::misc_NoFlash)
	{
		localplayer->ModulateFlashAlpha() = 0.f;
	}
}

std::vector<const char*> smoke_materials =
{
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
};

void CMisc::OnDrawModelExecute()
{
	static bool NoSmoke = false;
	static bool WireFrameSmoke = false;

	if (Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoSmoke = true;
		}
	}
	else if (!Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoSmoke = false;

		}
	}

	if (Settings::Misc::misc_wireframesmoke)

	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);

			WireFrameSmoke = true;
		}
	}

	else if (!Settings::Misc::misc_wireframesmoke)

	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);

			WireFrameSmoke = false;
		}
	}

}





void CMisc::OnOverrideView(CViewSetup * pSetup)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->GetIsScoped())
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		pSetup->fov = (float)Settings::Misc::misc_FovView;
	}
}

void CMisc::OnGetViewModelFOV(float& fov)
{
	if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot())
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		fov = (float)Settings::Misc::misc_FovModelView;
	}
}

void SetThirdPersonAngles(QAngle angles)
{
	CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	static int deadflag = Offset::Entity::deadflag;
	*(QAngle*)((uintptr_t)local->GetBaseEntity() + deadflag + 0x4) = angles;
	Interfaces::Input()->m_fCameraInThirdPerson = true;
}

void CMisc::FrameStageNotify(ClientFrameStage_t Stage)
{
	CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	


	if (Interfaces::Engine()->IsInGame() && Stage == ClientFrameStage_t::FRAME_RENDER_START)
	{

		CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		if (!localplayer)
			return;

		static QAngle vecAngles;
		Interfaces::Engine()->GetViewAngles(vecAngles);

		if (Settings::Misc::misc_ThirdPerson && !localplayer->IsDead())
		{
			if (!Interfaces::Input()->m_fCameraInThirdPerson)
				Interfaces::Input()->m_fCameraInThirdPerson = true;

			Interfaces::Input()->m_vecCameraOffset = QAngle(vecAngles.x, vecAngles.y, Settings::Misc::misc_ThirdPersonRange);

			SetThirdPersonAngles(Settings::Misc::qLastTickAngle);
		}
		else
		{
			if (Interfaces::Input()->m_fCameraInThirdPerson || localplayer->GetIsScoped())
			{
				Interfaces::Input()->m_fCameraInThirdPerson = false;
				Interfaces::Input()->m_vecCameraOffset = QAngle(vecAngles.x, vecAngles.y, 0);
			}
		}
	}
}

vector<int> CMisc::GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (/*pCheckPlayer->IsDormant() || */!pCheckPlayer->IsDead())
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}

void CMisc::OnRenderSpectatorList()
{
	if (Settings::Misc::misc_Spectators)
	{
		int DrawIndex = 1;

		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;

			CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

			if (!pPlayer)
				continue;

			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);

			if (Pinfo.m_bIsFakePlayer)
				continue;

			if (g_pRender)
			{
				string Name = Pinfo.m_szPlayerName;

				if (Name != "")
				{
					Color PlayerObsColor;
					//[junk_disable /]
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						Name.append(" - Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						Name.append(" - 3rd person");
						PlayerObsColor = Color::Aqua();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						Name.append(" - Free look");
						PlayerObsColor = Color::Red();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						Name.append(" - Deathcam");
						PlayerObsColor = Color::Yellow();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						Name.append(" - Freezecam");
						PlayerObsColor = Color::LimeGreen();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						Name.append(" - Fixed");
						PlayerObsColor = Color::Orange();
						break;
					default:
						break;
					}
					//[junk_enable /]
					g_pRender->Text(iScreenWidth - 300, 300 + (DrawIndex * 13), false, true, PlayerObsColor, "%s", Name.c_str());
					DrawIndex++;
				}
			}
		}
	}
}