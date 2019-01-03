
#include "Settings.h"

//[enc_string_enable /]
//[junk_enable /]

using namespace Client;

QAngle lastReal, lastFake;

namespace Settings
{
	void LoadSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());


		Ragebot::Enabled = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Enabled, Ragebot::Enabled);
		Ragebot::Aimstep = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Aimstep, Ragebot::Aimstep);
		Ragebot::Silent = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Silent, Ragebot::Silent);
		Ragebot::MultiPoints = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_MultiPoints, Ragebot::MultiPoints);
		Ragebot::FriendlyFire = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_FriendlyFire, Ragebot::FriendlyFire);
		Ragebot::AutoFire = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AutoFire, Ragebot::AutoFire);
		Ragebot::AutoStop = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AutoStop, Ragebot::AutoStop);
		Ragebot::AutoScope = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AutoScope, Ragebot::AutoScope);
		Ragebot::AutoCrouch = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AutoCrouch, Ragebot::AutoCrouch);
		Ragebot::RCS = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_RCS, Ragebot::RCS);
		Ragebot::FOV = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_FOV, Ragebot::FOV);
		Ragebot::AimstepAmount = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AimstepAmount, Ragebot::AimstepAmount);
		Ragebot::PointScale = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_PointScale, Ragebot::PointScale);
		Ragebot::Hitbox = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Hitbox, Ragebot::Hitbox);
		Ragebot::HitScan = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_HitScan, Ragebot::HitScan);
		Ragebot::aw = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_aw, Ragebot::aw);
		Ragebot::HitChance = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_HitChance, Ragebot::HitChance);
		Ragebot::Resolver = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Resolver, Ragebot::Resolver);
		Ragebot::AutoWallDmg = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AutoWallDmg, Ragebot::AutoWallDmg);
		Ragebot::BaimAfterShoots = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_BaimAfterShoots, Ragebot::BaimAfterShoots);
		Ragebot::HitChanceAmt = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_HitChanceAmt, Ragebot::HitChanceAmt);
		Ragebot::BaimAfterHP = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_BaimAfterHP, Ragebot::BaimAfterHP);
		Ragebot::AAEnabled = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_AAEnabled, Ragebot::AAEnabled);
		Ragebot::UntrustedCheck = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_UntrustedCheck, Ragebot::UntrustedCheck);
		Ragebot::Pitch = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Pitch, Ragebot::Pitch);
		Ragebot::fakewalk = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_fakewalk, Ragebot::fakewalk);
		Ragebot::RealYaw = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_RealYaw, Ragebot::RealYaw);
		Ragebot::FakeYaw = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_FakeYaw, Ragebot::FakeYaw);
		Ragebot::walkspeed = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_walkspeed, Ragebot::walkspeed);
		Ragebot::RealYawAdd = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_RealYawAdd, Ragebot::RealYawAdd);
		Ragebot::FakeLags = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_FakeLags, Ragebot::FakeLags);
		Ragebot::Fakelag_amt = CSX::Cvar::LoadCvar(RAGEBOT_TEXT, CVAR_Fakelag_amt, Ragebot::Fakelag_amt);


		Aimbot::aim_DrawBacktrack = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWBACKTRACK, Aimbot::aim_DrawBacktrack);
		Aimbot::aim_Active = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_ACTIVE, Aimbot::aim_Active);


		Aimbot::aim_Deathmatch = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DEATHMATCH, Aimbot::aim_Deathmatch);
		Aimbot::aim_WallAttack = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_WALLATTACK, Aimbot::aim_WallAttack);

		Aimbot::aim_CheckFlash = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_CHECKFLASH, Aimbot::aim_CheckFlash);
		Aimbot::aim_AntiJump = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_ANTIJUMP, Aimbot::aim_AntiJump);
		Aimbot::aim_RcsType = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_RCSTYPE, Aimbot::aim_RcsType);
		Aimbot::aim_DrawFov = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWFOV, Aimbot::aim_DrawFov);
		Aimbot::aim_DrawSpot = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWSPOT, Aimbot::aim_DrawSpot);
		Aimbot::aim_OnKey = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_ONKEY, Aimbot::aim_OnKey);
		Aimbot::aim_Key = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_KEY, Aimbot::aim_Key);
		Aimbot::aim_FastZoom = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_FASTZOOM, Aimbot::aim_FastZoom);
		Aimbot::aim_Crouch = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_CROUCH, Aimbot::aim_Crouch);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			// ���������
			if (i <= 9)
			{
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 1);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 1);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 0);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 1);
				Aimbot::weapon_aim_settings[i].aim_Rcsx = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSX, 100);
				Aimbot::weapon_aim_settings[i].aim_Rcsy = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSY, 100);
				Aimbot::weapon_aim_settings[i].aim_AutoPistol = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_AUTOPISTOL, 0);
				Aimbot::weapon_aim_settings[i].aim_RcsFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, 20);
				Aimbot::weapon_aim_settings[i].aim_RcsSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, 300);
				Aimbot::weapon_aim_settings[i].aim_RcsClampType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, 0);
				Aimbot::weapon_aim_settings[i].aim_pSilent = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_pSilent, 0);
				Aimbot::weapon_aim_settings[i].aim_pSilentFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_pSilentFov, 1);
			}

			// ��������
			if (i >= 10 && i <= 30)
			{
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 1);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 1);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 0);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcsx = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSX, 100);
				Aimbot::weapon_aim_settings[i].aim_Rcsy = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSY, 100);
				Aimbot::weapon_aim_settings[i].aim_RcsFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, 20);
				Aimbot::weapon_aim_settings[i].aim_RcsSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, 300);
				Aimbot::weapon_aim_settings[i].aim_RcsClampType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, 0);
				Aimbot::weapon_aim_settings[i].aim_pSilent = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_pSilent, 0);
				Aimbot::weapon_aim_settings[i].aim_pSilentFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_pSilentFov, 1);
			}

			// ���������
			if (i >= 31 && i <= 32)
			{
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 1);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 1);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 0);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcsx = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSX, 100);
				Aimbot::weapon_aim_settings[i].aim_Rcsy = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSY, 100);
				Aimbot::weapon_aim_settings[i].aim_RcsFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, 20);
				Aimbot::weapon_aim_settings[i].aim_RcsSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, 300);
				Aimbot::weapon_aim_settings[i].aim_RcsClampType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, 0);
				Aimbot::weapon_aim_settings[i].aim_pSilent = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_pSilent, 0);
				Aimbot::weapon_aim_settings[i].aim_pSilentFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_pSilentFov, 1);
			}
		}





		Esp::esp_Size = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SIZE, Esp::esp_Size);
		Esp::esp_CapitalToggle = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CAPITALTOGGLE, Esp::esp_CapitalToggle);
		Esp::esp_Line = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_LINE, Esp::esp_Line) != false;
		Esp::esp_Outline = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_OUTLINE, Esp::esp_Outline) != false;
		Esp::esp_Watermark = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WATER, Esp::esp_Watermark) != false;
		Esp::esp_Time = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_TIME, Esp::esp_Time) != false;
		Esp::esp_Name = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_NAME, Esp::esp_Name) != false;
		
		Esp::esp_Cheatbuild = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHEATBUILD, Esp::esp_Cheatbuild) != false;

		
		


		Esp::esp_Ammo = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_AMMO, Esp::esp_Ammo) != false;

		

		Esp::esp_Skeleton = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SKELETON, Esp::esp_Skeleton) != false;
		Esp::esp_Team = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_TEAM, Esp::esp_Team) != false;
		Esp::esp_Enemy = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_ENEMY, Esp::esp_Enemy) != false;
		Esp::esp_Visible = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_VISIBLE, Esp::esp_Visible);
		Esp::esp_ChamsVisible = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHAMSVISIBLE, Esp::esp_ChamsVisible);
		Esp::esp_AAIndicator = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_AAINDICATOR, Esp::esp_AAIndicator);


		Esp::esp_Chams = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHAMS, Esp::esp_Chams);
		Esp::esp_Bomb = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BOMB, Esp::esp_Bomb) != false;
		Esp::esp_BombTimer = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BOMBTIMER, Esp::esp_BombTimer);
		Esp::esp_WorldWeapons = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WORLDWEAPONS, Esp::esp_WorldWeapons) != false;
		Esp::esp_WorldGrenade = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WORLDGRENADE, Esp::esp_WorldGrenade) != false;





		string esp_Color_CT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_CT, "0,164,255");
		string esp_Color_TT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_TT, "255,64,64");
		string esp_Color_VCT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VCT, "124,252,0");
		string esp_Color_VTT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VTT, "124,252,0");


		CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WALLSOPACITY, Settings::Esp::esp_WallsOpacity);

		string chams_Color_CT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_CT, "0,164,255");
		string chams_Color_TT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_TT, "255,64,64");
		string chams_Color_VCT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VCT, "124,252,0");
		string chams_Color_VTT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VTT, "124,252,0");


		string GrenadeHelper = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_GrenadeHelper, "255,0,0");

		ScanColorFromCvar(GrenadeHelper.c_str(), Settings::Esp::GrenadeHelper);


		string Color_HITMARKER = CSX::Cvar::LoadCvar(VISUAL_TEXT, "esp_HitMarkerColor", "255,0,0");



		string SoundVisuals_Color = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_SOUNDESP, "255,255,255");
		string WeaponEnemy_Color = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_WEAPONENEMY, "255,255,255");
		string WorldWeapon_Color = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_WORLDWEAPON, "255,255,255");

		//string Visuals_Line_Color = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_LINE, "0,0,0");
		//string Name_Color = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_NAME, "255,255,0");
		string Skelet = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_SKELET, "255,255,255");
		ScanColorFromCvar(SoundVisuals_Color.c_str(), Settings::Esp::SoundVisuals_Color);
		ScanColorFromCvar(WeaponEnemy_Color.c_str(), Settings::Esp::WeaponEnemy_Color);
		ScanColorFromCvar(WorldWeapon_Color.c_str(), Settings::Esp::WorldWeapon_Color);
		//ScanColorFromCvar(Visuals_Line_Color.c_str(), Settings::Esp::Visuals_Line_Color);
		//ScanColorFromCvar(Name_Color.c_str(), Settings::Esp::Name_Color);
		ScanColorFromCvar(Skelet.c_str(), Settings::Esp::Skelet);




		ScanColorFromCvar(esp_Color_CT.c_str(), Settings::Esp::esp_Color_CT);
		ScanColorFromCvar(esp_Color_TT.c_str(), Settings::Esp::esp_Color_TT);
		ScanColorFromCvar(esp_Color_VCT.c_str(), Settings::Esp::esp_Color_VCT);
		ScanColorFromCvar(esp_Color_VTT.c_str(), Settings::Esp::esp_Color_VTT);

		ScanColorFromCvar(chams_Color_CT.c_str(), Settings::Esp::chams_Color_CT);
		ScanColorFromCvar(chams_Color_TT.c_str(), Settings::Esp::chams_Color_TT);
		ScanColorFromCvar(chams_Color_VCT.c_str(), Settings::Esp::chams_Color_VCT);
		ScanColorFromCvar(chams_Color_VTT.c_str(), Settings::Esp::chams_Color_VTT);

		Radar::Radar_Enable = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ENABLE, Radar::Radar_Enable) != false;
		Radar::rad_Active = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ACTIVE, Radar::rad_Active) != false;
		Radar::rad_Team = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_TEAM, Radar::rad_Team) != false;
		Radar::rad_Enemy = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ENEMY, Radar::rad_Enemy) != false;
		Radar::rad_Range = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_RANGE, Radar::rad_Range);
		Radar::rad_Alpha = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ALPHA, Radar::rad_Alpha);
		Radar::barrel = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_BARREL, Radar::barrel);

		string Color_CT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_CT, "0,164,255");
		string Color_TT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_TT, "255,64,64");
		string Color_VCT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_VCT, "0,255,0");
		string Color_VTT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_VTT, "0,255,0");

		ScanColorFromCvar(Color_CT.c_str(), Radar::rad_Color_CT);
		ScanColorFromCvar(Color_TT.c_str(), Radar::rad_Color_TT);
		ScanColorFromCvar(Color_VCT.c_str(), Radar::rad_Color_VCT);
		ScanColorFromCvar(Color_VTT.c_str(), Radar::rad_Color_VTT);

		Knifebot::knf_Active = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ACTIVE, Knifebot::knf_Active) != false;
		Knifebot::knf_Team = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_TEAM, Knifebot::knf_Team) != false;
		Knifebot::knf_Attack = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ATTACK, Knifebot::knf_Attack);
		Knifebot::knf_DistAttack = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK, Knifebot::knf_DistAttack);
		Knifebot::knf_DistAttack2 = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK2, Knifebot::knf_DistAttack2);

		Skin::knf_ct_model = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_CT_MODEL, Skin::knf_ct_model);
		Skin::knf_ct_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_CT_SKIN, Skin::knf_ct_skin);
		Skin::knf_tt_model = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_TT_MODEL, Skin::knf_tt_model);
		Skin::knf_tt_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_TT_SKIN, Skin::knf_tt_skin);
		Skin::gloves_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_GLOVES, Skin::gloves_skin);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackPaintKit = CSX::Cvar::LoadCvar(SKIN_TEXT, pWeaponData[i], 0);
		}

		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
			ForceFullUpdate();


		Misc::misc_SkinChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_SKIN_CHANGER, Misc::misc_SkinChanger) != false;
		Misc::misc_Bhop = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_BHOP, Misc::misc_Bhop) != false;
		Misc::misc_Punch2 = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_PUNCH2, Misc::misc_Punch2) != false;
		Misc::misc_AwpAim = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AWPAIM, Misc::misc_AwpAim) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOFLASH, Misc::misc_NoFlash) != false;
		Misc::misc_NoSmoke = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOSMOKE, Misc::misc_NoSmoke) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_WIREFRAMESMOKE, Misc::misc_wireframesmoke) != false;
		Misc::misc_AutoStrafe = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AUTOSTRAFE, Misc::misc_AutoStrafe) != false;
		Misc::misc_AutoAccept = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AUTOACCEPT, Misc::misc_AutoAccept) != false;
		Misc::misc_Spectators = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_SPECTATORS, Misc::misc_Spectators) != false;
		Misc::misc_FovChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_CHANGER, Misc::misc_FovChanger) != false;
		Misc::misc_FovView = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_VIEW, Misc::misc_FovView);
		Misc::misc_FovModelView = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_MDL_VIEW, Misc::misc_FovModelView);
		Misc::invalwayson = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_INVALWAYSON, Misc::invalwayson);
		Misc::misc_HitMarker = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_HITMARKER, Misc::misc_HitMarker) != false;
		Misc::misc_HitMarkerSound = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_HITMARKERSOUND, Misc::misc_HitMarkerSound);
		Misc::misc_radiospam = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_RADIOSPAM, Misc::misc_radiospam);
		Misc::Killmessage = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_KILLSPAM, Misc::Killmessage);
		Misc::misc_ThirdPerson = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_THIRDPERSON, Misc::misc_ThirdPerson);
		Misc::misc_ThirdPersonRange = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_THIRDPERSONRANGE, Misc::misc_ThirdPersonRange);
		string Color_AWPAIM = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AWPAIM_COLOR, "255,255,255");
		ScanColorFromCvar(Color_AWPAIM.c_str(), Misc::misc_AwpAimColor);

		string Color_MENU = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_MENU_COLOR, "0,0,0");

		ScanColorFromCvar(Color_MENU.c_str(), Misc::misc_MenuColor);

		string Color_TEXT = CSX::Cvar::LoadCvar(MISC_TEXT, "misc_TextColor", "255,255,255");

		ScanColorFromCvar(Color_TEXT.c_str(), Misc::misc_TextColor);


	}

	void SaveSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());

		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Enabled, Ragebot::Enabled);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Aimstep, Ragebot::Aimstep);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Silent, Ragebot::Silent);

		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_MultiPoints, Ragebot::MultiPoints);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_FriendlyFire, Ragebot::FriendlyFire);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AutoFire, Ragebot::AutoFire);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AutoStop, Ragebot::AutoStop);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AutoScope, Ragebot::AutoScope);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AutoCrouch, Ragebot::AutoCrouch);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_RCS, Ragebot::RCS);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_FOV, Ragebot::FOV);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AimstepAmount, Ragebot::AimstepAmount);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_PointScale, Ragebot::PointScale);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Hitbox, Ragebot::Hitbox);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_HitScan, Ragebot::HitScan);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_aw, Ragebot::aw);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_HitChance, Ragebot::HitChance);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Resolver, Ragebot::Resolver);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AutoWallDmg, Ragebot::AutoWallDmg);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_BaimAfterShoots, Ragebot::BaimAfterShoots);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_HitChanceAmt, Ragebot::HitChanceAmt);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_BaimAfterHP, Ragebot::BaimAfterHP);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_AAEnabled, Ragebot::AAEnabled);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_UntrustedCheck, Ragebot::UntrustedCheck);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Pitch, Ragebot::Pitch);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_fakewalk, Ragebot::fakewalk);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_RealYaw, Ragebot::RealYaw);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_FakeYaw, Ragebot::FakeYaw);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_walkspeed, Ragebot::walkspeed);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_RealYawAdd, Ragebot::RealYawAdd);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_FakeLags, Ragebot::FakeLags);
		CSX::Cvar::SaveCvar(RAGEBOT_TEXT, CVAR_Fakelag_amt, Ragebot::Fakelag_amt);

		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWBACKTRACK, Aimbot::aim_DrawBacktrack);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_ACTIVE, Aimbot::aim_Active);


		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DEATHMATCH, Aimbot::aim_Deathmatch);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_WALLATTACK, Aimbot::aim_WallAttack);

		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_CHECKFLASH, Aimbot::aim_CheckFlash);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_ANTIJUMP, Aimbot::aim_AntiJump);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_RCSTYPE, Aimbot::aim_RcsType);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWFOV, Aimbot::aim_DrawFov);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWSPOT, Aimbot::aim_DrawSpot);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_ONKEY, Aimbot::aim_OnKey);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_KEY, Aimbot::aim_Key);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_FASTZOOM, Aimbot::aim_FastZoom);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_CROUCH, Aimbot::aim_Crouch);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			// ���������
			if (i <= 9)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSX, Aimbot::weapon_aim_settings[i].aim_Rcsx);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSY, Aimbot::weapon_aim_settings[i].aim_Rcsy);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_AUTOPISTOL, Aimbot::weapon_aim_settings[i].aim_AutoPistol);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, Aimbot::weapon_aim_settings[i].aim_RcsFov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, Aimbot::weapon_aim_settings[i].aim_RcsSmooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, Aimbot::weapon_aim_settings[i].aim_RcsClampType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_pSilent, Aimbot::weapon_aim_settings[i].aim_pSilent);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_pSilentFov, Aimbot::weapon_aim_settings[i].aim_pSilentFov);
			}

			// ��������
			if (i >= 10 && i <= 30)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSX, Aimbot::weapon_aim_settings[i].aim_Rcsx);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSY, Aimbot::weapon_aim_settings[i].aim_Rcsy);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, Aimbot::weapon_aim_settings[i].aim_RcsFov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, Aimbot::weapon_aim_settings[i].aim_RcsSmooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, Aimbot::weapon_aim_settings[i].aim_RcsClampType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_pSilent, Aimbot::weapon_aim_settings[i].aim_pSilent);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_pSilentFov, Aimbot::weapon_aim_settings[i].aim_pSilentFov);
			}

			// ���������
			if (i >= 31 && i <= 32)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSX, Aimbot::weapon_aim_settings[i].aim_Rcsx);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSY, Aimbot::weapon_aim_settings[i].aim_Rcsy);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, Aimbot::weapon_aim_settings[i].aim_RcsFov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, Aimbot::weapon_aim_settings[i].aim_RcsSmooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, Aimbot::weapon_aim_settings[i].aim_RcsClampType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_pSilent, Aimbot::weapon_aim_settings[i].aim_pSilent);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_pSilentFov, Aimbot::weapon_aim_settings[i].aim_pSilentFov);
			}
		}


		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_TIME, Settings::Esp::esp_Time);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SIZE, Settings::Esp::esp_Size);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CAPITALTOGGLE, Settings::Esp::esp_CapitalToggle);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_LINE, Settings::Esp::esp_Line);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_OUTLINE, Settings::Esp::esp_Outline);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_NAME, Settings::Esp::esp_Name);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WALLSOPACITY, Settings::Esp::esp_WallsOpacity);

		
		
		
	


		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_AMMO, Settings::Esp::esp_Ammo);

	
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_AAINDICATOR, Settings::Esp::esp_AAIndicator);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WATER, Settings::Esp::esp_Watermark);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHEATBUILD, Settings::Esp::esp_Cheatbuild);


		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SKELETON, Settings::Esp::esp_Skeleton);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_TEAM, Settings::Esp::esp_Team);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_ENEMY, Settings::Esp::esp_Enemy);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_VISIBLE, Settings::Esp::esp_Visible);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHAMSVISIBLE, Settings::Esp::esp_ChamsVisible);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHAMS, Settings::Esp::esp_Chams);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BOMB, Settings::Esp::esp_Bomb);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BOMBTIMER, Settings::Esp::esp_BombTimer);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WORLDWEAPONS, Settings::Esp::esp_WorldWeapons);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WORLDGRENADE, Settings::Esp::esp_WorldGrenade);


		string esp_Color_CT =
			to_string(int(Settings::Esp::esp_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[2] * 255.f));

		string esp_Color_TT =
			to_string(int(Settings::Esp::esp_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[2] * 255.f));

		string esp_Color_VCT =
			to_string(int(Settings::Esp::esp_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[2] * 255.f));

		string esp_Color_VTT =
			to_string(int(Settings::Esp::esp_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		string GrenadeHelper =
			to_string(int(Settings::Esp::GrenadeHelper[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::GrenadeHelper[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::GrenadeHelper[2] * 255.f));

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_CT, esp_Color_CT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_TT, esp_Color_TT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VCT, esp_Color_VCT);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VTT, esp_Color_VTT);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_GrenadeHelper, GrenadeHelper);

		string chams_Color_CT =
			to_string(int(Settings::Esp::chams_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[2] * 255.f));

		string chams_Color_TT =
			to_string(int(Settings::Esp::chams_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[2] * 255.f));

		string chams_Color_VCT =
			to_string(int(Settings::Esp::chams_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[2] * 255.f));

		string chams_Color_VTT =
			to_string(int(Settings::Esp::chams_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[2] * 255.f));

		string SoundVisuals_Color =
			to_string(int(Settings::Esp::SoundVisuals_Color[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::SoundVisuals_Color[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::SoundVisuals_Color[2] * 255.f));

		string WeaponEnemy_Color =
			to_string(int(Settings::Esp::WeaponEnemy_Color[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::WeaponEnemy_Color[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::WeaponEnemy_Color[2] * 255.f));

		string WorldWeapon_Color =
			to_string(int(Settings::Esp::WorldWeapon_Color[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::WorldWeapon_Color[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::WorldWeapon_Color[2] * 255.f));

		string Visuals_Line_Color =
			to_string(int(Settings::Esp::Visuals_Line_Color[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::Visuals_Line_Color[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::Visuals_Line_Color[2] * 255.f));

		string Name_Color =
			to_string(int(Settings::Esp::Name_Color[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::Name_Color[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::Name_Color[2] * 255.f));

		string Skelet =
			to_string(int(Settings::Esp::Skelet[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::Skelet[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::Skelet[2] * 255.f));



		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_CT, chams_Color_CT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_TT, chams_Color_TT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VCT, chams_Color_VCT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VTT, chams_Color_VTT);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_SKELET, Skelet);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_SOUNDESP, SoundVisuals_Color);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_WEAPONENEMY, WeaponEnemy_Color);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_WORLDWEAPON, WorldWeapon_Color);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_LINE, Visuals_Line_Color);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_NAME, Name_Color);



		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ENABLE, Radar::Radar_Enable);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ACTIVE, Radar::rad_Active);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_TEAM, Radar::rad_Team);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ENEMY, Radar::rad_Enemy);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_RANGE, Radar::rad_Range);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ALPHA, Radar::rad_Alpha);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_BARREL, Radar::barrel);

		string Color_CT =
			to_string(int(Radar::rad_Color_CT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_CT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_CT[2] * 255.f));

		string Color_TT =
			to_string(int(Radar::rad_Color_TT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_TT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_TT[2] * 255.f));

		string Color_VCT =
			to_string(int(Radar::rad_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VCT[2] * 255.f));

		string Color_VTT =
			to_string(int(Radar::rad_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VTT[2] * 255.f));

		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_CT, Color_CT);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_TT, Color_TT);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_VCT, Color_VCT);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_VTT, Color_VTT);

		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ACTIVE, Knifebot::knf_Active);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_TEAM, Knifebot::knf_Team);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ATTACK, Knifebot::knf_Attack);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK, Knifebot::knf_DistAttack);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK2, Knifebot::knf_DistAttack2);

		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_CT_MODEL, Skin::knf_ct_model);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_CT_SKIN, Skin::knf_ct_skin);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_TT_MODEL, Skin::knf_tt_model);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_TT_SKIN, Skin::knf_tt_skin);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_GLOVES, Skin::gloves_skin);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackPaintKit);
		}


		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_SKIN_CHANGER, Misc::misc_SkinChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_BHOP, Misc::misc_Bhop);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_PUNCH2, Misc::misc_Punch2);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOFLASH, Misc::misc_NoFlash);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_WIREFRAMESMOKE, Misc::misc_wireframesmoke);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOSMOKE, Misc::misc_NoSmoke);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AWPAIM, Misc::misc_AwpAim);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AUTOSTRAFE, Misc::misc_AutoStrafe);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AUTOACCEPT, Misc::misc_AutoAccept);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_SPECTATORS, Misc::misc_Spectators);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_CHANGER, Misc::misc_FovChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_VIEW, Misc::misc_FovView);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_MDL_VIEW, Misc::misc_FovModelView);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_HITMARKER, Settings::Misc::misc_HitMarker);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_HITMARKERSOUND, Settings::Misc::misc_HitMarkerSound);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_RADIOSPAM, Settings::Misc::misc_radiospam);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_KILLSPAM, Settings::Misc::Killmessage);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_THIRDPERSON, Settings::Misc::misc_ThirdPerson);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_THIRDPERSONRANGE, Settings::Misc::misc_ThirdPersonRange);

		string Color_MENU =
			to_string(int(Misc::misc_MenuColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_MenuColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_MenuColor[2] * 255.f));

		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_MENU_COLOR, Color_MENU);

		string Color_TEXT =
			to_string(int(Misc::misc_TextColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_TextColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_TextColor[2] * 255.f));

		CSX::Cvar::SaveCvar(MISC_TEXT, "misc_TextColor", Color_TEXT);

		string Color_AWP_AIM =
			to_string(int(Misc::misc_AwpAimColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_AwpAimColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_AwpAimColor[2] * 255.f));
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AWPAIM_COLOR, Color_AWP_AIM);

		string Color_HITMARKER =
			to_string(int(Misc::misc_HitMarkerColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_HitMarkerColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_HitMarkerColor[2] * 255.f));
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_HITMARKER_COLOR, Color_HITMARKER);
	}

	float hitmarkerAlpha;

	int menu_key = 45;



	namespace Ragebot
	{
		bool 	Enabled = false;
		bool ResolverOverride = false;
		bool PositionAdjustment = false;
		bool 	AutoFire = false;
		bool 	Over;
		int 	KeyOver;
		int 	Filter; // will hold flags for team/enemy/etc.
		bool 	Silent = false;
		bool	RCS = false;
		bool 	VisCheck;
		bool 	AutoWall = false;
		float	AutoWallDmg = 1;
		int		Hitbox = 0;
		float 	FOV = 1;
		int		FakeLags = 0;
		bool 	HitChance = false;
		float	HitChanceAmt = 1;
		bool 	AutoStop = false;
		bool 	AutoCrouch = false;
		bool 	FriendlyFire = false;
		bool	Aimstep = false;
		float	AimstepAmount = 1;
		bool	HitScanAll = false;
		bool    bones[6] = { false, false, false, false, false, false };//
		int TargetMethod;
		bool HitScanHitbox = false;
		bool AWPBODY;
		int BaimAfterHP = 1;
		int BaimAfterShoots = 1;
		bool ZeusBot = 0;
		float ZeusDist = 500.f;
		int HitScan = 0;
		bool MultiPoints = false;
		float PointScale = 0.f;
		bool ShootWhenStopped = false;//Ussles
		bool AutoRevolver = false;
		bool AutoStopCanShoot = false; // Ussles
		bool AutoStopFast = false; // Ussles
		bool AutoScope = false;
		bool UntrustedCheck = false;
		int fakewalk = 0;
		int walkspeed = 0;
		bool AAEnabled = false;
		int Pitch = 0;
		int Pitches;
		int RealYaw = 0;
		int FakeYaw = 0;
		int manualrightkey;
		int manualleftkey;
		int manualbackkey;
		int RealYawAdd = 0;
		int Side;
		bool AimAtPlayer;
		bool DetectEdge;
		bool PSilent;
		bool Resolver = false;
		bool aw = false;
		bool	Dynamic = false;
		int		YawReal = 0;
		int YawFake;
		int Fakelag_amt = 1;
		bool Fakelag = false;
		bool glitch_bool = false;
		int OverrideKey;
	}


	namespace Aimbot
	{
		bool Custom1 = false;
		bool aim_Active = false;
		bool aim_Backtrack = false;
		bool aim_DrawBacktrack = false;
		int aim_Backtracktickrate = 1;
		bool aim_Deathmatch = false;
		bool aim_WallAttack = false;
		bool aim_CheckSmoke = false;
		bool aim_AntiJump = false;
		int aim_RcsType = 0;
		bool aim_DrawFov = false;
		bool aim_DrawSpot = false;
		bool aim_KillDelay = false;
		float aim_KillDelayTime = 0;
		bool aim_OnKey = false;
		int aim_Key = 1;
		bool aim_CheckFlash = false;
		bool aim_FastZoom = false;
		bool aim_Crouch = false;
		int aim_Rcsx = 100;
		int aim_Rcsy = 100;
		int aim_RcsFov = 20;
		int aim_RcsSmooth = 300;

		weapon_aim_s weapon_aim_settings[33] = { 0 };
	}



	namespace MedalChanger {
		bool enabled = false;
		// std::vector<uint32_t> medals = { 874, 875, 879, 883, 889, 890, 896, 897, 903, 904, 910, 913, 916, 917, 923, 926, 927, 931, 937, 940, 941, 947, 948, 954, 955, 961, 1003, 1015, 1026, 1030, 1318, 1329, 1332, 1338, 1344, 1363, 1372 };
		std::vector<uint32_t> medals = {};
		bool equipped_medal_override = false;
		uint32_t equipped_medal = 0;
	}
	namespace ProfileChanger {
		bool enabled = false;
		int rank_id = 0;
		int wins = 0;
		int cmd_friendly = 0;
		int cmd_leader = 0;
		int cmd_teaching = 0;
		int level = 0;
		int xp = 0;
		int ban = 0;
		int time = 0;

	}
	namespace InventoryChanger {
		bool enabled = false;
		std::vector<k_weapon_data> weapons = {};
	}

	namespace Esp
	{
		int esp_Style = 0; // 0 - Box 1 - CoalBox
		int esp_Size = 1;
		bool esp_CapitalToggle = 0;
		bool esp_Line = false;
		bool esp_Outline = false; // Box ( 0 - Box 1 - OutlineBox ) ,
								  // CoalBox ( 0 - CoalBox 1 - OutlineCoalBox )	
		bool esp_Time = true;

		bool esp_Chicken = false;
		bool esp_Fish = false;
		bool helper = false;
		bool esp_Watermark = true;
		bool esp_Cheatbuild = true;
		bool esp_Name = false;
		bool esp_Rank = false;
		int esp_Health = 0;
		int esp_Armor = 0;
		bool esp_Weapon = false;
		int esp_WeaponIcon = 0;
		bool esp_Ammo = false;
		bool esp_Distance = false;
		bool esp_Sound = false;
		int  SoundESPDistance = 600;
		bool esp_Dlightz = false;
		bool esp_NightMode = false;
		bool esp_InScoped = false;
		bool esp_Flashed = false;
		bool esp_HealthChams = false;
		bool esp_Defusing = false;
		bool esp_AAIndicator = false;
		bool esp_Statusx = false;
		bool esp_legitAAWarnings = false;
		bool bEspWarnings = false;
		int esp_WallsOpacity = 100;
		float esp_Ambient[3];
		float esp_Dlight[3];
		bool esp_AsusWalls = false;
		bool esp_Skeleton = 0;;
		bool esp_Team = 1;
		bool esp_Enemy = 1;
		//int esp_Visible = 1;
		bool esp_Visible = 1;
		//int esp_ChamsVisible = 1;
		bool esp_ChamsVisible = 1;

		int esp_Chams = 0;
		bool esp_Bomb = false;
		int esp_BombTimer = 40;
		bool esp_WorldWeapons = false;
		bool esp_WorldGrenade = false;

		float Skelet[3] = { 0.f,0.0f,0.f };
		float SoundVisuals_Color[3] = { 0.f,0.0f,0.f };
		float WeaponEnemy_Color[3] = { 0.f,0.0f,0.f };
		float WorldWeapon_Color[3] = { 0.f,0.0f,0.f };
		float Visuals_Line_Color[3] = { 0.f,0.0f,0.f };
		float Name_Color[3] = { 0.f,0.0f,0.f };

		float esp_Color_CT[3] = { 0.f,0.0f,0.f };
		float esp_Color_TT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VCT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VTT[3] = { 0.f,0.0f,0.f };

		float GrenadeHelper[3] = { 0.f,0.f,0.f };

		float chams_Color_CT[3] = { 0.f,0.0f,0.f };
		float chams_Color_TT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VCT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VTT[3] = { 0.f,0.0f,0.f };
		float flTracer_Beam[3] = { 200.f,0.0f,255.f };
		bool esp_beams_tracer = false;
		float flTracersDuration = 1;
		float flTracersWidth = 1;
		bool DamageIndicator = false;
		float DamagerColor[3] = { 0.f,0.0f,0.f };
	/*	bool esp_GrenadePrediction = false;*/
	}



	namespace Radar
	{
		bool Radar_Enable = false;
		bool rad_Active = false;
		bool rad_Team = false;
		bool rad_Enemy = false;
		int rad_Range = 1;
		int rad_Alpha = 255;
		float rad_Color_CT[3] = { 0.f,0.0f,0.f };
		float rad_Color_TT[3] = { 0.f,0.0f,0.f };
		float rad_Color_VCT[3] = { 0.f,0.f,0.f };
		float rad_Color_VTT[3] = { 0.f,0.f,0.f };
		bool barrel = false;
	}

	namespace Knifebot
	{
		bool knf_Active = false;
		bool knf_Team = false;
		int knf_Attack = 0;
		int knf_DistAttack = 1;
		int knf_DistAttack2 = 1;
	}

	namespace Skin
	{
		int knf_ct_model = 0;
		int knf_ct_skin = 0;
		int knf_tt_model = 0;
		int knf_tt_skin = 0;
		int gloves_skin = 0;
		int gloves_model = 0;
	}

	namespace Misc
	{

		bool RemoveScope = false;
		bool misc_SkinChanger = false;
		float misc_MenuColor[3] = { 0.f, 0.f, 0.f };
		float misc_TextColor[3] = { 0.f, 0.f, 0.f };
		QAngle qLastTickAngle;
		bool misc_ThirdPerson = false;
		int ThirdPersonType = 1;
		bool misc_ragdoll_gravity;
		int misc_ragdoll_gravity_amount;
		bool misc_pushscale;
		int misc_pushscale_amount;
		int misc_ThirdPersonRange = 0.f;
		char misc_NameChange = 0;
		int misc_Clan = 0;
		bool misc_spamregular = false;
		bool misc_spamrandom = false;
		bool misc_RainbowMenu = false;
		float misc_RainbowSpeed = 0.001f;
		bool stickerids = false;
		const char* misc_SkyName;
		int misc_CurrentSky;
		bool misc_NoSky = false;
		bool misc_Snow = false;
		bool misc_Bhop = false;
		bool misc_Punch2 = false;
		bool window_profilechanger;
		bool window_medalchanger;
		bool window_inventorychanger;
		bool skinids = false;
		bool medalids = false;
		bool weaponids = false;
		bool misc_AwpAim = false;
		bool misc_wireframesmoke = false;
		bool misc_NoFlash = false;
		bool misc_NoSmoke = false;
		int misc_AutoStrafe = 0;
		bool misc_AutoAccept = false;
		bool misc_Spectators = false;
		bool misc_FovChanger = false;
		int misc_FovView = 90;
		int misc_FovModelView = 60;
		float misc_AwpAimColor[3] = { 0.f,0.f,0.f };
		bool misc_HitMarker = false;
		float hitmarkerAlpha;
		int misc_HitMarkerSound = 0;
		float misc_HitMarkerColor[3] = { 0.f, 0.f, 0.f };
		float KillDelayVar = 0;
		bool KillDelayBool2 = false;
		bool misc_radiospam = false;
		bool Killmessage = false;
		bool misc_AntiAfk = false;
		bool ShowSpread = 0;
		bool misc_Telehop = false;
		bool invalwayson = false;
	}
}