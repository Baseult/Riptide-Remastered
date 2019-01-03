#pragma once

#include <Windows.h>

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

#define VirtualFn( cast ) typedef cast( __thiscall* OriginalFn )

template< typename Function > Function GetMethod( PVOID Base , DWORD Index )
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];
	return (Function)( dwAddress );
}

typedef struct con_nprint_s
{
	int		index;			// Row #
	float	time_to_live;	// # of seconds before it disappears. -1 means to display for 1 frame then go away.
	float	color[3];		// RGB colors ( 0.0 -> 1.0 scale )
	bool	fixed_width_font;
} con_nprint_t;

struct ScreenFade_t
{
	unsigned short 	duration;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration
	unsigned short 	holdTime;		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, seconds duration until reset (fade & hold)
	short			fadeFlags;		// flags
	byte			r , g , b , a;		// fade to color ( max alpha )
};

struct CHudTexture
{
	char	szShortName[64];	//0x0000
	char	szTextureFile[64];	//0x0040
	bool	bRenderUsingFont;	//0x0080
	bool	bPrecached;			//0x0081
	char	cCharacterInFont;	//0x0082
	BYTE	pad_0x0083;			//0x0083
	int		hFont;				//0x0084
	int		iTextureId;			//0x0088
	float	afTexCoords[4];		//0x008C
	int		iPosX[4];			//0x009C
}; //Size=0x00AC

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};
class CWeaponInfo
{
public:
	char _0x0000[20];
	__int32 max_clip;	//0x0014 
	char _0x0018[12];
	__int32 max_reserved_ammo;	//0x0024 
	char _0x0028[96];
	char* hud_name;//0x0088 
	char* weapon_name;	//0x008C 
	char _0x0090[60];
	__int32 type;//0x00CC 
	__int32 price;//0x00D0 
	__int32 reward;//0x00D4 
	char _0x00D8[20];
	BYTE full_auto;//0x00EC 
	char _0x00ED[3];
	__int32 damage;//0x00F0 
	float armor_ratio;	//0x00F4 
	__int32 bullets;	//0x00F8 
	float penetration;	//0x00FC 
	char _0x0100[8];
	float range;//0x0108 
	float range_modifier;//0x010C 
	char _0x0110[16];
	BYTE silencer;//0x0120 
	char _0x0121[15];
	float max_speed;	//0x0130 
	float max_speed_alt;//0x0134 
	char _0x0138[76];
	__int32 recoil_seed;//0x0184 
	char _0x0188[32];
};


namespace SDK
{
	typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
	typedef void* (*InstantiateInterfaceFn)();

	typedef void(*pfnDemoCustomDataCallback)(unsigned char *pData, size_t iSize);

	enum class FontFeature {
		FONT_FEATURE_ANTIALIASED_FONTS = 1,
		FONT_FEATURE_DROPSHADOW_FONTS = 2,
		FONT_FEATURE_OUTLINE_FONTS = 6,
	};

	enum class FontDrawType {
		FONT_DRAW_DEFAULT = 0,
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE,
		FONT_DRAW_TYPE_COUNT = 2,
	};

	enum class FontFlags {
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
		FONTFLAG_ANTIALIAS = 0x010,
		FONTFLAG_GAUSSIANBLUR = 0x020,
		FONTFLAG_ROTARY = 0x040,
		FONTFLAG_DROPSHADOW = 0x080,
		FONTFLAG_ADDITIVE = 0x100,
		FONTFLAG_OUTLINE = 0x200,
		FONTFLAG_CUSTOM = 0x400,
		FONTFLAG_BITMAP = 0x800,
	};

	enum class ClientFrameStage_t {
		FRAME_UNDEFINED = -1,
		FRAME_START,
		FRAME_NET_UPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_START,
		FRAME_NET_UPDATE_POSTDATAUPDATE_END,
		FRAME_NET_UPDATE_END,
		FRAME_RENDER_START,
		FRAME_RENDER_END
	};



		enum class ObserverMode_t : int
		{
			OBS_MODE_NONE = 0,
			OBS_MODE_DEATHCAM = 1,
			OBS_MODE_FREEZECAM = 2,
			OBS_MODE_FIXED = 3,
			OBS_MODE_IN_EYE = 4,
			OBS_MODE_CHASE = 5,
			OBS_MODE_ROAMING = 6
		};
	
}