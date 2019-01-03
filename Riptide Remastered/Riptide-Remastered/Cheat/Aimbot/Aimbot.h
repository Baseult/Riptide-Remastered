#pragma once

#include "../../Engine/Engine.h"

#define MAXBACKTRACKTICKS ((int)Settings::Aimbot::aim_Backtracktickrate)
#define TICK_INTERVAL			(Interfaces::GlobalVars()->interval_per_tick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

class CTimer;

namespace Engine
{
	class CMe;
	class CPlayer;
}

using namespace Engine;

enum AIM_ATTACK_TYPE
{
	AA_SHOTGUN,
	AA_SNIPER_PISTOL
};

class CAimbot
{
public:

	CAimbot();

	//[swap_lines]
	bool	IsEnable();
	int GetPlayerSilentFov(CPlayer * pPlayer);
	int		GetPlayerFov(CPlayer* pPlayer);
	int		GetBestTarget();
	int		GetBestHitBox();
	void	OnRender();
	void OnEvents(IGameEvent * pEvent);
	void	Aimbot(CUserCmd * cmd, CMe * pLocal, bool &bSendPacket);
	void	AimbotSet(CUserCmd * cmd, CMe * pLocal, bool &bSendPacket);
	void	AutoPistol();
	void PerfectSilent(CUserCmd * cmd, CMe * pLocal, bool & bSendPacket);
	void	OnCreateMove(CUserCmd* cmd, CMe* pLocal);

	void DoAntiAimX(int AntiAim, QAngle & angles);
	void DoAntiAimY(int AntiAim, QAngle & angles);
	void AntiAimCreateMove(CUserCmd * cmd, bool & bSendPacket);
	void AntiAimCreateMoveFake(CUserCmd * cmd, bool & bSendPacket);


	//[/swap_lines]
private:

	CMe*		m_pLocal;
	CUserCmd*	m_cmd;

	int		m_iBestPreTarget;
	int		m_iBestTarget;
	int		m_iBestHitbox;
	bool    m_pAim_KeyTrue;
	bool    m_pAim_KeyTrue2;
	ULONGLONG    m_pAim_KeyTrueTime;

	bool	m_bClamp;
	bool	m_bAttack;
	bool	m_bAttackPsilent;
	bool	m_bAimShot;
	bool	m_bTargetFov;
	bool	m_bTargetPsilentFov;
	bool	m_bTargetChange;
	bool	m_bAutoPistolEn;

	QAngle m_oldangle;

	CTimer*	m_pShotDelay;
	Vector	m_vAimBestHitbox;
	Vector  m_vAimBestHitboxScreen;
	Vector  m_vAimBestHitboxScreen2;
};