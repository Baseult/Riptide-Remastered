























#pragma once

#include "../Main/Main.h"

#define FIX_MIN_FOV_HEAD	30
#define FIX_MIN_FOV_CHEST	50
#define FOV_BASE_DISTANCE	200

struct k_weapon_data {
	int itemDefinitionIndex;
	int paintKit;
	int rarity;
	int seed;
	float wear;
	char* name = "";
};

extern QAngle lastReal, lastFake;

namespace Settings
{
	void LoadSettings(string szIniFile);
	void SaveSettings(string szIniFile);
	extern float hitmarkerAlpha;

	extern int menu_key;

	namespace MedalChanger {
		extern bool enabled;
		extern std::vector<uint32_t> medals;
		extern bool equipped_medal_override;
		extern uint32_t equipped_medal;
	}
	namespace ProfileChanger {
		extern bool enabled;
		extern int rank_id;
		extern int wins;
		extern int cmd_friendly;
		extern int cmd_leader;
		extern int cmd_teaching;
		extern int level;
		extern int xp;
		extern int ban;
		extern int time;
	}
	namespace InventoryChanger {
		extern bool enabled;
		extern std::vector<k_weapon_data> weapons;
	}



	namespace Ragebot
	{
		extern bool Enabled;
		extern bool ResolverOverride;
		extern bool PositionAdjustment;
		extern	bool AutoFire;
		extern bool Over;
		extern int KeyOver;
		extern int Filter; // will hold flags for team/enemy/etc.
		extern bool Silent;
		extern bool RCS;
		extern bool VisCheck;
		extern bool AutoWall;
		extern float AutoWallDmg;
		extern int	Hitbox;
		extern float FOV;
		extern int	FakeLags;
		extern bool HitChance;
		extern float HitChanceAmt;
		extern bool AutoStop;
		extern bool AutoCrouch;
		extern bool FriendlyFire;
		extern bool	Aimstep;
		extern float AimstepAmount;
		extern bool	HitScanAll;
		extern bool   bones[6];//
		extern int TargetMethod;
		extern bool HitScanHitbox;
		extern bool AWPBODY;
		extern int BaimAfterHP;
		extern int BaimAfterShoots;
		extern bool ZeusBot;
		extern float ZeusDist;
		extern int HitScan;
		extern bool MultiPoints;
		extern float PointScale;
		extern bool ShootWhenStopped;//Ussles
		extern bool AutoRevolver;
		extern bool AutoStopCanShoot; // Ussles
		extern bool AutoStopFast; // Ussles
		extern bool AutoScope;
		extern bool UntrustedCheck;
		extern int fakewalk;
		extern int walkspeed;
		extern bool AAEnabled;
		extern int Pitch;
		extern int Pitches;
		extern int RealYaw;
		extern int FakeYaw;
		extern int manualrightkey;
		extern int manualleftkey;
		extern int manualbackkey;
		extern int RealYawAdd;
		extern int Side;
		extern bool AimAtPlayer;
		extern bool DetectEdge;
		extern bool PSilent;
		extern bool Resolver;
		extern bool aw;
		extern bool Dynamic;
		extern int YawReal;
		extern int YawFake;
		extern int Fakelag_amt;
		extern bool Fakelag;
		extern bool glitch_bool;
		extern int OverrideKey;
	}

	namespace Aimbot
	{
		struct weapon_aim_s
		{
			//[swap_lines]

			bool aim_Active;
			bool aim_pSilent;
			int aim_pSilentFov;
			int aim_Smooth;
			int aim_Fov;
			int aim_FovType;
			int aim_BestHit;
			int aim_Spot;
			int aim_Delay;
			int aim_Rcsx;
			int aim_Rcsy;
			int aim_RcsStandalone;
			int aim_RcsAfterXShot;
			int aim_Rcs;
			int aim_RcsFov;
			int aim_RcsSmooth;
			int aim_RcsClampType;
			bool aim_AutoPistol;
			//[/swap_lines]
		};
		//[swap_lines]
		extern bool Custom1;
		extern bool aim_Active;
		extern bool aim_Backtrack;
		extern bool aim_DrawBacktrack;
		extern int aim_Backtracktickrate;
		extern bool aim_Deathmatch;
		extern bool aim_WallAttack;
		extern bool aim_CheckSmoke;
		extern bool aim_AntiJump;
		extern int aim_RcsType;
		extern bool aim_DrawFov;
		extern bool aim_DrawSpot;
		extern bool aim_KillDelay;
		extern float aim_KillDelayTime;
		extern bool aim_OnKey;
		extern int aim_Key;
		extern bool aim_CheckFlash;
		extern bool aim_FastZoom;
		extern bool aim_Crouch;

		extern weapon_aim_s weapon_aim_settings[33];
		//[/swap_lines]
	}

	namespace Esp
	{
		//[swap_lines]
		extern int esp_Style; // 0 - Box 1 - CoalBox
		extern int esp_Size;
		extern bool esp_CapitalToggle;
		extern bool esp_Line;
		extern bool esp_Outline; // Box ( 0 - Box 1 - OutlineBox ) ,
						  // CoalBox ( 0 - CoalBox 1 - OutlineCoalBox )	
		extern bool esp_Time;
		extern bool esp_legitAAWarnings;
		extern bool esp_AsusWalls;
		extern int esp_WallsOpacity;
		extern bool esp_Name;
		extern bool esp_Rank;
		extern int esp_Health;
		extern int esp_Armor;
		extern bool esp_Weapon;
		extern int esp_WeaponIcon;
		extern bool esp_Ammo;
		extern bool esp_Distance;
		extern bool esp_Sound;
		extern int  SoundESPDistance;
		extern bool esp_Dlightz;
		extern bool esp_Fish;
		extern bool esp_Watermark;
		extern bool esp_Chicken;
		extern bool bEspWarnings;
		extern float esp_Ambient[3];
		extern float esp_Dlight[3];
		extern bool helper;
		extern float GrenadeHelper[3];
		extern bool esp_NightMode;
		extern bool esp_InScoped;
		extern bool esp_Flashed;
		extern bool esp_Defusing;
		extern bool esp_AAIndicator;
		extern bool esp_Statusx;
		extern bool esp_Skeleton;
		extern bool esp_Team;
		extern bool esp_Enemy;
		//extern int esp_Visible;
		extern bool esp_Visible;
		//extern int esp_ChamsVisible;
		extern bool esp_ChamsVisible;

		extern int esp_Chams;
		extern bool esp_Bomb;
		extern int esp_BombTimer;
		extern bool esp_WorldWeapons;
		extern bool esp_WorldGrenade;
		extern bool esp_HealthChams;

		extern bool Visuals_WorldWeapons;

		extern float SoundVisuals_Color[3];
		extern float WeaponEnemy_Color[3];
		extern float WorldWeapon_Color[3];
		extern float Visuals_Line_Color[3];
		extern float Name_Color[3];
		extern float Skelet[3];
		extern bool esp_Cheatbuild;

		extern float esp_Color_CT[3];
		extern float esp_Color_TT[3];
		extern float esp_Color_VCT[3];
		extern float esp_Color_VTT[3];

		extern float chams_Color_CT[3];
		extern float chams_Color_TT[3];
		extern float chams_Color_VCT[3];
		extern float chams_Color_VTT[3];
		extern float flTracer_Beam[3];
		extern bool esp_beams_tracer;
		extern float flTracersDuration;
		extern float flTracersWidth;
		extern bool DamageIndicator;
		extern float DamagerColor[3];
		/*extern bool esp_GrenadePrediction;*/
		//[/swap_lines]
	}



	namespace Radar
	{
		//[swap_lines]
		extern bool Radar_Enable;
		extern bool rad_Active;
		extern bool rad_Team;
		extern bool rad_Enemy;
		extern int rad_Range;
		extern int rad_Alpha;
		extern float rad_Color_CT[3];
		extern float rad_Color_TT[3];
		extern float rad_Color_VCT[3];
		extern float rad_Color_VTT[3];
		extern bool barrel;
		//[/swap_lines]
	}

	namespace Skin
	{
		//[swap_lines]
		extern int knf_ct_model;
		extern int knf_ct_skin;
		extern int knf_tt_model;
		extern int knf_tt_skin;
		extern int gloves_skin;
		extern int gloves_model;
		//[/swap_lines]
	}

	namespace Misc
	{
		//[swap_lines]
		extern bool misc_SkinChanger;
		extern float misc_TextColor[3];
		extern float misc_MenuColor[3];
		extern QAngle qLastTickAngle;
		extern bool misc_ragdoll_gravity;
		extern int misc_ragdoll_gravity_amount;
		extern bool misc_pushscale;
		extern int misc_pushscale_amount;
		extern bool misc_ThirdPerson;
		extern bool RemoveScope;
		extern int ThirdPersonType;
		extern int misc_ThirdPersonRange;
		extern int misc_Clan;
		extern bool misc_spamregular;
		extern bool misc_spamrandom;
		extern bool misc_RainbowMenu;
		extern float misc_RainbowSpeed;
		extern bool window_profilechanger;
		extern bool window_medalchanger;
		extern bool window_inventorychanger;
		extern bool skinids;
		extern bool medalids;
		extern bool weaponids;
		extern bool stickerids;
		extern char misc_NameChange;
		extern bool misc_wireframesmoke;
		extern const char* misc_SkyName;
		extern int misc_CurrentSky;
		extern bool misc_NoSky;
		extern bool misc_Snow;
		extern bool misc_Bhop;
		extern bool misc_Punch2;
		extern bool misc_AwpAim;
		extern bool misc_NoFlash;
		extern bool misc_NoSmoke;
		extern int misc_AutoStrafe;
		extern bool misc_AutoAccept;
		extern bool misc_Spectators;
		extern bool misc_FovChanger;
		extern int misc_FovView;
		extern int misc_FovModelView;
		extern float misc_AwpAimColor[3];
		extern float hitmarkerAlpha;
		extern bool misc_HitMarker;
		extern int misc_HitMarkerSound;
		extern float misc_HitMarkerColor[3];
		extern float KillDelayVar;
		extern bool KillDelayBool2;
		extern bool misc_radiospam;
		extern bool Killmessage;
		extern bool misc_AntiAfk;
		extern bool ShowSpread;
		extern bool misc_Telehop;
		extern bool invalwayson;
		//[/swap_lines]
	}

	namespace Knifebot
	{
		//[swap_lines]
		extern bool knf_Active;
		extern bool knf_Team;
		extern int knf_Attack;
		extern int knf_DistAttack;
		extern int knf_DistAttack2;
		//[/swap_lines]
	}
}

//[enc_string_enable /]

#define HACK_NAME "riptide-remastered"

#define RAGEBOT_TEXT "Ragebot"
#define AIMBOT_TEXT "Aimbot"
#define CONFIG_TEXT "Config"
#define KNIFEBOT_TEXT "Knifebot"
#define VISUAL_TEXT "Visual"
#define RADAR_TEXT "Radar"
#define SKIN_TEXT "Skin"
#define MISC_TEXT "Misc"
#define CVAR_MISC_SKIN_CHANGER "misc_SkinChanger"
#define CVAR_Enabled "Enabled"
#define CVAR_Aimstep "Aimstep"
#define CVAR_Silent "Silent"
#define CVAR_MultiPoints "MultiPoints"

#define CVAR_FriendlyFire "FriendlyFire"
#define CVAR_AutoFire "AutoFire"
#define CVAR_AutoStop "AutoStop"
#define CVAR_AutoScope "AutoScope"
#define CVAR_AutoCrouch "AutoCrouch"
#define CVAR_RCS "RCS"
#define CVAR_FOV "FOV"
#define CVAR_AimstepAmount "AimstepAmount"
#define CVAR_PointScale "esp_PointScale"
#define CVAR_Hitbox "Hitbox"
#define CVAR_HitScan "HitScan"
#define CVAR_aw "aw"
#define CVAR_MISC_WIREFRAMESMOKE "misc_wireframesmoke"
#define CVAR_HitChance "HitChance"
#define CVAR_Resolver "Resolver"
#define CVAR_AutoWallDmg "AutoWallDmg"
#define CVAR_BaimAfterShoots "BaimAfterShoots"
#define CVAR_HitChanceAmt "HitChanceAmt"
#define CVAR_BaimAfterHP "BaimAfterHP"
#define CVAR_AAEnabled "AAEnabled"
#define CVAR_UntrustedCheck "UntrustedCheck"
#define CVAR_Pitch "Pitch"
#define CVAR_ESP_COLOR_GrenadeHelper "GrenadeHelper"
#define CVAR_fakewalk "fakewalk"
#define CVAR_RealYaw "RealYaw"
#define CVAR_FakeLags "FakeLags"
#define CVAR_Fakelag_amt "Fakelag_amt"
#define CVAR_MISC_INVALWAYSON "misc_InvAlwaysOn"
#define CVAR_FakeYaw "FakeYaw"
#define CVAR_walkspeed "walkspeed"
#define CVAR_RealYawAdd "RealYawAdd"

#define CVAR_AIMBOT_DRAWBACKTRACK "aim_DrawBacktrack"


#define CVAR_AIMBOT_DEATHMATCH "aim_FriendlyFire"
#define CVAR_AIMBOT_WALLATTACK "aim_WallAttack"

#define CVAR_AIMBOT_CHECKFLASH "aim_CheckFlash"
#define CVAR_AIMBOT_ANTIJUMP	"aim_IgnoreJump"
#define CVAR_AIMBOT_RCSTYPE "aim_RcsType"
#define CVAR_AIMBOT_DRAWFOV "aim_DrawFov"
#define CVAR_AIMBOT_DRAWSPOT "aim_DrawSpot"
#define CVAR_AIMBOT_ONKEY "aim_OnKey"
#define CVAR_AIMBOT_KEY "aim_Key"
#define CVAR_AIMBOT_FASTZOOM "aim_FastZoom"
#define CVAR_AIMBOT_CROUCH "aim_Crouch"

#define CVAR_AIMBOT_pSilent "aim_pSilent"
#define CVAR_AIMBOT_pSilentFov "aim_pSilentFov"
#define CVAR_ESP_TIME "esp_Time"
#define CVAR_ESP_WATER "esp_Watermark"

#define CVAR_AIMBOT_ACTIVE "aim_Active"
#define CVAR_AIMBOT_SMOOTH "aim_Smooth"
#define CVAR_AIMBOT_FOV "aim_Fov"
#define CVAR_AIMBOT_FOVTYPE "aim_FovType"
#define CVAR_AIMBOT_BESTHIT "aim_BestHit"
#define CVAR_AIMBOT_SPOT "aim_Spot"
#define CVAR_AIMBOT_DELAY "aim_Delay"

#define LEGITAALEFT    "Left"
#define LEGITAARIGHT   "Right"

#define CVAR_AIMBOT_RCSX "aim_Rcsx"
#define CVAR_AIMBOT_RCSY "aim_Rcsy"
#define CVAR_AIMBOT_RCSFOV "aim_RcsFov"
#define CVAR_AIMBOT_RCSSMOOTH "aim_RcsSmooth"
#define CVAR_AIMBOT_RCSCLAMPTYPE "aim_RcsClampType"
#define CVAR_AIMBOT_AUTOPISTOL "aim_AutoPistol"



#define CVAR_ESP_SIZE "esp_Size"
#define CVAR_ESP_CAPITALTOGGLE "esp_CapitalToggle"
#define CVAR_ESP_LINE "esp_Line"
#define CVAR_ESP_OUTLINE "esp_Outline"
#define CVAR_ESP_NAME "esp_Name"



#define CVAR_ESP_AAINDICATOR "esp_AAIndicator"


#define CVAR_KEY_MOUSE3 "MOUSE WHEEL"
#define CVAR_KEY_MOUSE4 "RIGHT MOUSE"
#define CVAR_KEY_MOUSE5 "LEFT ALT"

#define CVAR_ESP_CHEATBUILD "esp_Cheatbuild"



#define CVAR_ESP_AMMO "esp_Ammo"





#define CVAR_ESP_SKELETON "esp_Skeleton"
#define CVAR_ESP_TEAM "esp_Team"
#define CVAR_ESP_ENEMY "esp_Enemy"
#define CVAR_ESP_VISIBLE "esp_Visible"
#define CVAR_ESP_CHAMSVISIBLE "esp_ChamsVisible"


#define CVAR_ESP_CHAMS "esp_Chams"
#define CVAR_ESP_BOMB "esp_Bomb"
#define CVAR_ESP_BOMBTIMER "esp_BombTimer"
#define CVAR_ESP_WORLDWEAPONS "esp_WorldWeapons"
#define CVAR_ESP_WORLDGRENADE "esp_WorldGrenade"

#define CVAR_ESP_COLOR_SKELET "Skelet"
#define CVAR_ESP_COLOR_SOUNDESP "SoundVisuals_Color"
#define CVAR_ESP_COLOR_WEAPONENEMY "WeaponEnemy_Color"
#define CVAR_ESP_COLOR_WORLDWEAPON "WorldWeapon_Color"
#define CVAR_ESP_COLOR_LINE "Visuals_Line_Color"
#define CVAR_ESP_COLOR_NAME "Name_Color"

#define CVAR_ESP_COLOR_CT "esp_Color_CT"
#define CVAR_ESP_COLOR_TT "esp_Color_TT"
#define CVAR_ESP_COLOR_VCT "esp_Color_VCT"
#define CVAR_ESP_COLOR_VTT "esp_Color_VTT"

#define CVAR_CHAMS_COLOR_CT "chams_Color_CT"
#define CVAR_CHAMS_COLOR_TT "chams_Color_TT"
#define CVAR_CHAMS_COLOR_VCT "chams_Color_VCT"
#define CVAR_CHAMS_COLOR_VTT "chams_Color_VTT"



#define C4_TIMER_STRING "C4 Timer: %0.2f"

#define CVAR_RAD_ENABLE "Radar_Enable"
#define CVAR_RAD_ACTIVE "rad_Active"
#define CVAR_RAD_TEAM "rad_Team"
#define CVAR_RAD_ENEMY "rad_Enemy"
#define CVAR_RAD_RANGE "rad_Range"
#define CVAR_RAD_ALPHA "rad_Alpha"
#define CVAR_RAD_BARREL "barrel"

#define CVAR_RAD_COLOR_CT "rad_Color_CT"
#define CVAR_RAD_COLOR_TT "rad_Color_TT"
#define CVAR_RAD_COLOR_VCT "rad_Color_VCT"
#define CVAR_RAD_COLOR_VTT "rad_Color_VTT"
#define CVAR_ESP_WALLSOPACITY "esp_WallsOpacity"
#define CVAR_KNIFEBOT_ACTIVE "knf_Active"
#define CVAR_KNIFEBOT_TEAM "knf_Team"
#define CVAR_KNIFEBOT_ATTACK "knf_Attack"
#define CVAR_KNIFEBOT_DISTATTACK "knf_DistAttack"
#define CVAR_KNIFEBOT_DISTATTACK2 "knf_DistAttack2"
#define CVAR_MISC_MENU_COLOR "misc_MenuColor"
#define CVAR_SKIN_CT_MODEL "knf_ct_model"
#define CVAR_SKIN_CT_SKIN "knf_ct_skin"
#define CVAR_SKIN_TT_MODEL "knf_tt_model"
#define CVAR_SKIN_TT_SKIN "knf_tt_skin"
#define CVAR_SKIN_GLOVES "gloves_skin"
#define INVCHANGE_TEXT "InventoryChanger"
#define CVAR_MISC_BHOP "misc_Bhop"
#define CVAR_MISC_PUNCH2 "misc_Punch2"
#define CVAR_MISC_AWPAIM "misc_AwpAim"
#define CVAR_MISC_NOFLASH "misc_NoFlash"
#define CVAR_MISC_NOSMOKE "misc_NoSmoke"
#define CVAR_MISC_AUTOSTRAFE "misc_AutoStrafe"
#define CVAR_MISC_AUTOACCEPT "misc_AutoAccept"
#define CVAR_MISC_SPECTATORS "misc_Spectators"
#define CVAR_MISC_FOV_CHANGER "misc_FovChanger"
#define CVAR_MISC_FOV_VIEW "misc_FovView"
#define CVAR_MISC_FOV_MDL_VIEW "misc_FovModelView"
#define CVAR_MISC_AWPAIM_COLOR "misc_AwpAimColor"
#define CVAR_MISC_HITMARKER "misc_HitMarker"
#define CVAR_MISC_HITMARKER_COLOR "misc_HitMarkerColor"
#define CVAR_MISC_HITMARKERSOUND "misc_HitMarkerSound"
#define CVAR_MISC_RADIOSPAM "misc_radiospam"
#define CVAR_MISC_KILLSPAM "Killmessage"
#define CVAR_MISC_THIRDPERSON "misc_ThirdPerson"
#define CVAR_MISC_THIRDPERSONRANGE "misc_ThirdPersonRange"