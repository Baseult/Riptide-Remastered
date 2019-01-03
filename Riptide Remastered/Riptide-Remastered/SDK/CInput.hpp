#pragma once

#include "QAngle.hpp"
#include "CRC.hpp"
#include "ButtonCode.h"
//#include "SDK.h"

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)
#define IN_SPEED		(1 << 17)
#define IN_WALK			(1 << 18)
#define IN_ZOOM			(1 << 19)
#define IN_WEAPON1		(1 << 20)
#define IN_WEAPON2		(1 << 21)
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)
#define IN_GRENADE2		(1 << 24)
#define IN_LOOKSPIN		(1 << 25)

namespace SDK
{
	class bf_read;
	class bf_write;

	class CUserCmd {
	public:
		virtual ~CUserCmd() {};

		CRC32_t GetChecksum(void) const
		{
			CRC32_t crc;
			CRC32_Init(&crc);

			CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
			CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
			CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
			CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
			CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
			CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
			CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
			CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
			CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
			CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
			CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
			CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
			CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
			CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));

			CRC32_Final(&crc);
			return crc;
		}

		int       command_number;     // 0x04
		int       tick_count;         // 0x08
		QAngle    viewangles;         // 0x0C
		Vector    aimdirection;       // 0x18
		float     forwardmove;        // 0x24
		float     sidemove;           // 0x28
		float     upmove;             // 0x2C
		int       buttons;            // 0x30
		byte      impulse;            // 0x34
		int       weaponselect;       // 0x38
		int       weaponsubtype;      // 0x3C
		int       random_seed;        // 0x40
		short     mousedx;            // 0x44
		short     mousedy;            // 0x46
		bool      hasbeenpredicted;   // 0x48
		char      pad_0x4C[0x18];     // 0x4C
	};

	class CVerifiedUserCmd
	{
	public:
		CUserCmd  m_cmd;
		CRC32_t   m_crc;
	};

	class CInput
	{
	public:
		template <typename T> __forceinline T GetVirtualFunction(PVOID Base, DWORD Index)
		{
			return (T)((uint32_t *) *(uint32_t **)Base)[Index];
		}
		CInput::CUserCmd *GetUserCmd(int slot, int seq)
		{
			using OriginalFn = CUserCmd * (__thiscall *)(void *, int, int);
			return GetVirtualFunction<OriginalFn>(this, 8)(this, slot, seq);
		}
		void*               pvftable;                     //0x00 - [0x04] (0x04)
		char				pad_0x04[0x08];				  //0x04 - [0x0C] (pad)
		bool                m_fTrackIRAvailable;          //0x0C - [0x0D] (0x01)
		bool                m_fMouseInitialized;          //0x0D - [0x0E] (0x01)
		bool                m_fMouseActive;               //0x0E - [0x0F] (0x01)
		bool                m_fJoystickAdvancedInit;      //0x0F - [0x10] (0x01)
		char                pad_0x10[0x2C];               //0x10 - [0x3C] (pad)
		void*               m_pKeys;                      //0x3C - [0x40] (0x04)
		char                pad_0x40[0x64];               //0x40 - [0xA4] (pad)
		char                pad_0x38[0x64];
		int                 pad_0x41;
		int                 pad_0x42;
		bool                m_fCameraInterceptingMouse;   //0xA4 - [0xA5] (0x01)
		bool                m_fCameraInThirdPerson;       //0xA5 - [0xA6] (0x01)
		bool                m_fCameraMovingWithMouse;     //0xA6 - [0xA7] (0x01)
		Vector				m_vecCameraOffset;            //0xA7 - [0xB3] (0x0C)
		bool                m_fCameraDistanceMove;        //0xB3 - [0xB4] (0x01)
		int                 m_nCameraOldX;                //0xB4 - [0xB8] (0x04)
		int                 m_nCameraOldY;                //0xB8 - [0xBC] (0x04)
		int                 m_nCameraX;                   //0xBC - [0xC0] (0x04)
		int                 m_nCameraY;                   //0xC0 - [0xC4] (0x04)
		bool                m_CameraIsOrthographic;       //0xC4 - [0xC5] (0x01)
		Vector              m_angPreviousViewAngles;      //0xC5 - [0xD1] (0x0C)
		Vector              m_angPreviousViewAnglesTilt;  //0xD1 - [0xDD] (0x0C)
		float               m_flLastForwardMove;          //0xDD - [0xE1] (0x04)
		int                 m_nClearInputState;           //0xE1 - [0xE5] (0x04)
		char                pad_0xE4[0x8];                //0xE5 - [0xED] (pad)
		CUserCmd*           m_pCommands;                  //0xED - [0xF1] (0x04)
		CVerifiedUserCmd*   m_pVerifiedCommands;		  //0xF1 - [0xF5] (0x04)
		char*   consoleName;                       //0x0004
		char    pad_0x0008[12];                    //0x0008
		int     iMaxClip1;                         //0x0014
		int     iMaxClip2;                         //0x0018
		int     iDefaultClip1;                     //0x001C
		int     iDefaultClip2;                     //0x0020
		int     iMaxReservedAmmo;                  //0x0024
		char    pad_0x0028[8];                     //0x0028
		char*   szWorldModel;                      //0x0030
		char*   szViewModel;                       //0x0034
		char*   szDroppedModel;                    //0x0038
		char    pad_0x003C[64];                    //0x003C
		char*   szEmptySound;                      //0x007C
		char    pad_0x0080[4];                     //0x0080
		char*   szBulletType;                      //0x0084
		char*   szHudName;                         //0x0088
		char*   szWeaponName;                      //0x008C
		char    pad_0x0090[60];                    //0x0090
		int     WeaponType;                        //0x00CC
		int     iWeaponPrice;                      //0x00D0
		int     iKillAward;                        //0x00D4
		char*   szAnimationPrefix;                 //0x00D8
		float   flCycleTime;                       //0x00DC
		float   flCycleTimeAlt;                    //0x00E0
		float   flTimeToIdle;                      //0x00E4
		float   flIdleInterval;                    //0x00E8
		bool    bFullAuto;                         //0x00EC
		char    pad_0x00ED[3];                     //0x00ED
		int     iDamage;                           //0x00F0
		float   flArmorRatio;                      //0x00F4
		int     iBullets;                          //0x00F8
		float   flPenetration;                     //0x00FC
		float   flFlinchVelocityModifierLarge;     //0x0100
		float   flFlinchVelocityModifierSmall;     //0x0104
		float   flRange;                           //0x0108
		float   flRangeModifier;                   //0x010C
		float   flThrowVelocity;                   //0x0110
		char    pad_0x0114[12];                    //0x0114
		bool    bHasSilencer;                      //0x0120
		char    pad_0x0121[3];                     //0x0121
		char*   pSilencerModel;                    //0x0124
		int     iCrosshairMinDistance;             //0x0128
		int     iCrosshairDeltaDistance;           //0x012C
		float   flMaxPlayerSpeed;                  //0x0130
		float   flMaxPlayerSpeedAlt;               //0x0134
		float   flSpread;                          //0x0138
		float   flSpreadAlt;                       //0x013C
		float   flInaccuracyCrouch;                //0x0140
		float   flInaccuracyCrouchAlt;             //0x0144
		float   flInaccuracyStand;                 //0x0148
		float   flInaccuracyStandAlt;              //0x014C
		float   flInaccuracyJumpInitial;           //0x0150
		float   flInaccuracyJump;                  //0x0154
		float   flInaccuracyJumpAlt;               //0x0158
		float   flInaccuracyLand;                  //0x015C
		float   flInaccuracyLandAlt;               //0x0160
		float   flInaccuracyLadder;                //0x0164
		float   flInaccuracyLadderAlt;             //0x0168
		float   flInaccuracyFire;                  //0x016C
		float   flInaccuracyFireAlt;               //0x0170
		float   flInaccuracyMove;                  //0x0174
		float   flInaccuracyMoveAlt;               //0x0178
		float   flInaccuracyReload;                //0x017C
		char    pad_0x0180[4];                     //0x0180
		int     iRecoilSeed;                       //0x0184
		float   flRecoilAngle;                     //0x0188
		float   flRecoilAngleAlt;                  //0x018C
		float   flRecoilAngleVariance;             //0x0190
		float   flRecoilAngleVarianceAlt;          //0x0194
		float   flRecoilMagnitude;                 //0x0198
		float   flRecoilMagnitudeAlt;              //0x019C
		float   flRecoilMagnitudeVariance;         //0x01A0
		float   flRecoilMagnitudeVarianceAlt;      //0x01A4
		float   flRecoveryTimeCrouch;              //0x01A8
		float   flRecoveryTimeStand;               //0x01AC
		float   flRecoveryTimeCrouchFinal;         //0x01B0
		float   flRecoveryTimeStandFinal;          //0x01B4
		int     iRecoveryTransitionStartBullet;    //0x01B8
		int     iRecoveryTransitionEndBullet;      //0x01BC
		bool    bUnzoomAfterShot;                  //0x01C0
		bool    bHideViewModelZoomed;              //0x01C1
		char    pad_0x01C2[2];                     //0x01C2
		char    iZoomLevels[3];                    //0x01C4
		int     iZoomFOV[2];                       //0x01C7
		float   fZoomTime[3];                      //0x01C9
		char*   szWeaponClass;                     //0x01CC
		float   flAddonScale;                      //0x01D0
		char    pad_0x01D4[4];                     //0x01D4
		char*   szEjectBrassEffect;                //0x01D8
		char*   szTracerEffect;                    //0x01DC
		int     iTracerFrequency;                  //0x01E0
		int     iTracerFrequencyAlt;               //0x01E4
		char*   szMuzzleFlashEffect_1stPerson;     //0x01E8
		char    pad_0x01EC[4];                     //0x01EC
		char*   szMuzzleFlashEffect_3rdPerson;     //0x01F0
		char    pad_0x01F4[4];                     //0x01F4
		char*   szMuzzleSmokeEffect;               //0x01F8
		float   flHeatPerShot;                     //0x01FC
		char*   szZoomInSound;                     //0x0200
		char*   szZoomOutSound;                    //0x0204
		float   flInaccuracyPitchShift;            //0x0208
		float   flInaccuracySoundThreshold;        //0x020C
		float   flBotAudibleRange;                 //0x0210
		char    pad_0x0214[8];                     //0x0214
		char*   pWrongTeamMsg;                     //0x021C
		bool    bHasBurstMode;                     //0x0220
		char    pad_0x0221[3];                     //0x0221
		bool    bIsRevolver;                       //0x0224
		bool    bCannotShootUnderwater;            //0x0225
	};

	class IInputSystem
	{
	public:
		void EnableInput(bool bEnable)
		{
			VirtualFn(void*)(PVOID, bool);
			GetMethod< OriginalFn >(this, 11)(this, bEnable);
		}

		bool IsButtonDown(ButtonCode_t code)
		{
			VirtualFn(bool)(PVOID, ButtonCode_t);
			return GetMethod< OriginalFn >(this, 15)(this, code);
		}

		void ResetInputState()
		{
			VirtualFn(void)(PVOID);
			GetMethod< OriginalFn >(this, 39)(this);
		}



		ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
		{
			VirtualFn(ButtonCode_t)(PVOID, int);
			return GetMethod< OriginalFn >(this, 44)(this, nVirtualKey);
		}

		int ButtonCodeToVirtualKey(ButtonCode_t code)
		{
			VirtualFn(int)(PVOID, ButtonCode_t);
			return GetMethod< OriginalFn >(this, 45)(this, code);
		}

		void GetCursorPosition(int* m_pX, int* m_pY)
		{
			VirtualFn(void)(PVOID, int*, int*);
			GetMethod< OriginalFn >(this, 56)(this, m_pX, m_pY);
		}
	};
}