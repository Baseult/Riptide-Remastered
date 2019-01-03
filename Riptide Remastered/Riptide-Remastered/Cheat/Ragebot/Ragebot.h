



#include <Psapi.h>
#include <unordered_map>
#define RandomInt(min, max) (rand() % (max - min + 1) + min)

#define INRANGE(x,a,b)    (x >= a && x <= b)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
#define FCVAR_CHEAT				(1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats

#define MakePtr (cast, ptr, addValue) ( cast )( (DWORD)( ptr ) + ( DWORD )( addValue ) )
#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / Interfaces::GlobalVars()->interval_per_tick ) )
#define TICKS_TO_TIME( t ) ( Interfaces::GlobalVars()->interval_per_tick *( t ) )
#define TICK_INTERVAL ( Interfaces::GlobalVars()->interval_per_tick )
#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define square( x ) ( x * x )

using namespace Client;

namespace Client
{
	extern int iWeaponID;
}
enum
{
	PITCH = 0, // up / down
	YAW, // left / right
	ROLL // fall over
};
struct Hitbox
{
	Hitbox(void)
	{
		hitbox = -1;
	}

	Hitbox(int newHitBox)
	{
		hitbox = newHitBox;
	}

	int  hitbox;
	Vector points[9];
};

enum
{
	FL_HIGH = (1 << 0),
	FL_LOW = (1 << 1),
	FL_SPECIAL = (1 << 2)
};


enum Bone : int
{
	BONE_HEAD = 0,
	BONE_NECK,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_HIP,
	BONE_PELVIS
};

struct BestPoint
{
	BestPoint(void)
	{
		hitbox = -1;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	BestPoint(int newHitBox)
	{
		hitbox = newHitBox;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	Vector point;
	int  index;
	int  dmg;
	int  flags;
	int  hitbox;
};

namespace CPlayerList
{
	extern std::vector<int> friends;
	extern std::vector<int> Players;
}

class CRageBot
{
public:
	bool Run();
	bool AimStep(QAngle& angle);
private:
	void FindTarget();
	void GoToTarget();
	void GetBestBone(CBaseEntity* entity, float& best_damage, Bone& best_bone);


	int BestAimPointHitbox(CBaseEntity * target);

	bool EntityIsValid(int i);
	bool GetHitbox(CBaseEntity* target, Hitbox* hitbox);
	bool GetBestPoint(CBaseEntity* target, Hitbox* hitbox, BestPoint* point);

	float oldForward;
	float oldSideMove;
};

float m_bestfov = 360.0f;
float m_bestdist = 8192.f;
float m_bestthreat = 0.f;
CBaseEntity* m_bestent = nullptr;
bool m_target = false;
QAngle AimStepLastAngle;

std::vector<int> CPlayerList::friends = {};
typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);

namespace U
{
	DWORD FindPattern(std::string moduleName, std::string pattern);

	void ClipTraceToPlayers(const Vector & vecAbsStart, const Vector & vecAbsEnd, unsigned int mask, ITraceFilter * filter, trace_t * tr);
	void TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, CBaseEntity* ignore, trace_t* ptr);
}

enum Hitboxes : int
{
	HITBOX_HEAD2 = 0,
	HITBOX_NECK2,
	HITBOX_PELVIS2,
	HITBOX_SPINE2,
	HITBOX_LEGS2,
	HITBOX_ARMS2,
};

std::unordered_map<int, std::vector<const char*>> hitboxes = {
	{ HITBOX_HEAD2,{ "head_0" } },
{ HITBOX_NECK2,{ "neck_0" } },
{ HITBOX_PELVIS2,{ "pelvis" } },
{ HITBOX_SPINE2,{ "spine_0", "spine_1", "spine_2", "spine_3" } },
{ HITBOX_LEGS2,{ "leg_upper_L", "leg_upper_R", "leg_lower_L", "leg_lower_R", "ankle_L", "ankle_R" } },
{ HITBOX_ARMS2,{ "hand_L", "hand_R", "arm_upper_L", "arm_lower_L", "arm_upper_R", "arm_lower_R" } },
};
std::unordered_map<int, std::vector<const char*>> baim = {


	{ HITBOX_SPINE2,{ "spine_0", "spine_1", "spine_2", "spine_3" } },
{ HITBOX_LEGS2,{ "leg_upper_L", "leg_upper_R", "leg_lower_L", "leg_lower_R", "ankle_L", "ankle_R" } },
{ HITBOX_ARMS2,{ "hand_L", "hand_R", "arm_upper_L", "arm_lower_L", "arm_upper_R", "arm_lower_R" } },
};

namespace G
{
	float hitmarkerAlpha;
	bool	KillStop;
	DWORD KillStopDelay;
	QAngle LastAngle;
	QAngle LastAngle2;
	CBaseEntity* LocalPlayer;
	bool Return;
	CUserCmd* UserCmd;
	HMODULE Dll;
	HWND Window;
	bool PressedKeys[256];
	bool d3dinit;
	float FOV;
	int ChamMode;
	bool SendPacket = true;
	int BestTarget;
	bool AllowSilent;
	float KillDelayTime;
	bool KillDelayEnd;
	float FireDelayTime;
	bool			Aimbotting;
	QAngle doz;
	float		FSNLBY;
	bool			LastLBYUpdate;
	int			TickCount;
	Vector		BestHitboxVec;
	bool ChangeAAY;
	QAngle VisualAngle;
	bool ScopeAction;
	bool InAntiAim;
	float hurtTime;
	int hurtDamage;

}

class CAutowall
{
public:

	struct FireBulletData
	{
		Vector          src;
		trace_t         enter_trace;
		Vector          direction;
		CTraceFilter    filter;
		float           trace_length;
		float           trace_length_remaining;
		float           current_damage;
		int             penetrate_count;
	};

	float GetDamagez(const Vector& vecPoint);
	float GetDamage(const Vector& vecPoint, FireBulletData& fData);
	bool SimulateFireBullet(CBaseWeapon* pWeapon, FireBulletData &data);
	bool HandleBulletPenetration(CWeaponInfo *wpn_data, FireBulletData &data);
	bool TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace);
	bool DidHitNonWorldEntity(CBaseEntity* m_pEnt);
	void ScaleDamage(int hitgroup, CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage);
	float GetHitgroupDamageMultiplier(int iHitGroup);

};

namespace M
{
	extern inline void SinCos(float radians, float* sine, float* cosine);
	extern void VectorAngles(const Vector& forward, QAngle& angles);
	extern void AngleVectors(const QAngle& angles, Vector* forward);
	//	extern void AngleVectors(const QAngle& angles, Vector* forward, Vector* right, Vector* up);
	extern QAngle CalcAngle(Vector v1, Vector v2);
	extern float GetFov(const QAngle& viewAngle, const QAngle& aimAngle);
	extern float VectorDistance(Vector v1, Vector v2);
	extern void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector& out);
	extern float GetDelta(float hspeed, float maxspeed, float airaccelerate);
	extern Vector ExtrapolateTick(Vector p0, Vector v0);
	extern float DotProduct(const Vector & a, const Vector & b);
	//	extern void AngleVectors(const Vector & angles, Vector * forward);
	extern inline float RandFloat(float M, float N);

	extern void CorrectMovement(QAngle vOldAngles, CUserCmd* cmd, float fOldForward, float fOldSidemove);

	inline float FASTSQRT(float x)
	{
		unsigned int i = *(unsigned int*)&x;

		i += 127 << 23;
		i >>= 1;
		return *(float*)&i;
	}
}


void inline M::SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void M::VectorAngles(const Vector& forward, QAngle& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90)
			angles[1] -= 180;
		else if (angles[1] < 90)
			angles[1] += 180;
		else if (angles[1] == 90)
			angles[1] = 0;
	}

	angles[2] = 0.0f;
}

void M::AngleVectors(const QAngle& angles, Vector* forward)
{
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}


float M::GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	Vector ang, aim;

	AngleVectors(viewAngle, &aim);
	AngleVectors(aimAngle, &ang);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}

QAngle M::CalcAngle(Vector src, Vector dst)
{
	QAngle angles;
	Vector delta = src - dst;
	VectorAngles(delta, angles);
	delta.Normalized();
	return angles;
}

float M::VectorDistance(Vector v1, Vector v2)
{
	return FASTSQRT(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
}

void M::VectorTransform(Vector& in1, matrix3x4_t& in2, Vector& out)
{
	out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
	out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
	out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

float M::GetDelta(float hspeed, float maxspeed, float airaccelerate)
{
	auto term = (30.0 - (airaccelerate * maxspeed / 66.0)) / hspeed;

	if (term < 1.0f && term > -1.0f)
	{
		return acos(term);
	}

	return 0.f;
}

inline float M::RandFloat(float M, float N)
{
	return (float)(M + (rand() / (RAND_MAX / (N - M))));
}

inline Vector M::ExtrapolateTick(Vector p0, Vector v0)
{
	return p0 + (v0 * Interfaces::GlobalVars()->interval_per_tick);
}

FORCEINLINE float M::DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}



void M::CorrectMovement(QAngle vOldAngles, CUserCmd* cmd, float fOldForward, float fOldSidemove)
{
	// side/forward move correction
	float deltaView;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (cmd->viewangles.y < 0.0f)
		f2 = 360.0f + cmd->viewangles.y;
	else
		f2 = cmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);

	deltaView = 360.0f - deltaView;

	cmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	cmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}






DWORD U::FindPattern(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}
DWORD 	ClipTraceToPlayersFn = U::FindPattern(("client_panorama.dll"), ("53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC ? ? ? ? 8B 43 10"));

void U::ClipTraceToPlayers(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
{
	if (!ClipTraceToPlayersFn)
		return;

	_asm
	{
		MOV		EAX, filter
		LEA		ECX, tr
		PUSH	ECX
		PUSH	EAX
		PUSH	mask
		LEA		EDX, vecAbsEnd
		LEA		ECX, vecAbsStart
		CALL	ClipTraceToPlayersFn
		ADD		ESP, 0xC
	}
}

void U::TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, CBaseEntity* ignore, trace_t* ptr)
{
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	Interfaces::EngineTrace()->TraceRay(ray, mask, &filter, ptr);
}


CAutowall* AutoWall = new CAutowall();

float CAutowall::GetHitgroupDamageMultiplier(int iHitGroup)
{
	switch (iHitGroup) {
	case HITGROUP_GENERIC:
		return 1.0f;
	case HITGROUP_HEAD:
		return 4.0f;
	case HITGROUP_CHEST:
		return 1.0f;
	case HITGROUP_STOMACH:
		return 1.25f;
	case HITGROUP_LEFTARM:
		return 1.0f;
	case HITGROUP_RIGHTARM:
		return 1.0f;
	case HITGROUP_LEFTLEG:
		return 0.75f;
	case HITGROUP_RIGHTLEG:
		return 0.75f;
	case HITGROUP_GEAR:
		return 1.0f;
	default:
		break;
	}
	return 1.0f;
}


void CAutowall::ScaleDamage(int hitgroup, CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage)
{
	current_damage *= GetHitgroupDamageMultiplier(hitgroup);

	if (!Settings::Ragebot::FriendlyFire && enemy->GetTeam() == G::LocalPlayer->GetTeam())
	{
		current_damage = 0;
		return;
	}

	int armor = enemy->GetArmor();
	int helmet = enemy->HasHelmet();

	if (armor > 0)
	{
		if (hitgroup == HITGROUP_HEAD)
		{
			if (helmet)
				current_damage *= (weapon_armor_ratio * .5f);
		}
		else
		{
			current_damage *= (weapon_armor_ratio * .5f);
		}
	}
}

bool CAutowall::DidHitNonWorldEntity(CBaseEntity* m_pEnt)
{
	return m_pEnt != NULL && m_pEnt == Interfaces::EntityList()->GetClientEntity(0);
}

TraceToExitFn TraceToExits = (TraceToExitFn)U::FindPattern(("client_panorama.dll"), ("55 8B EC 83 EC 30 F3 0F 10 75"));
bool CAutowall::TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace)
{
	if (!TraceToExits)
	{
		return false;
	}
	_asm
	{
		push trace
		push z2
		push y2
		push x2
		push z
		push y
		push x
		mov edx, tr
		mov ecx, end
		call TraceToExits
		add esp, 0x1C
	}
}

bool CAutowall::HandleBulletPenetration(CWeaponInfo *wpn_data, FireBulletData &data)
{
	surfacedata_t *enter_surface_data = Interfaces::Physprops()->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	float enter_surf_penetration_mod = *(float*)((DWORD)enter_surface_data + 88);

	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow((wpn_data->range_modifier), (data.trace_length * 0.002));

	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
		data.penetrate_count = 0;

	if (data.penetrate_count <= 0)
		return false;

	Vector dummy;
	trace_t trace_exit;
	if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit))
		return false;

	surfacedata_t *exit_surface_data = Interfaces::Physprops()->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;

	float exit_surf_penetration_mod = *(float*)((DWORD)exit_surface_data + 88);
	float final_damage_modifier = 0.16f;
	float combined_penetration_modifier = 0.0f;

	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
	{
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else
	{
		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
	}

	if (enter_material == exit_material)
	{
		if (exit_material == 87 || exit_material == 85)
			combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)
			combined_penetration_modifier = 2.0f;
	}

	float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->penetration) * 1.25f);
	float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;

	float lost_damage = fmaxf(0.0f, v35 + thickness);

	if (lost_damage > data.current_damage)
		return false;

	if (lost_damage >= 0.0f)
		data.current_damage -= lost_damage;

	if (data.current_damage < 1.0f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}

bool CAutowall::SimulateFireBullet(CBaseWeapon* pWeapon, FireBulletData &data)
{
	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	CWeaponInfo* weaponData = G::LocalPlayer->GetWeapon()->GetCSWpnData();

	if (weaponData == NULL)
		return false;

	data.current_damage = (float)weaponData->damage;

	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
	{
		data.trace_length_remaining = weaponData->range - data.trace_length;

		Vector end = data.src + data.direction * data.trace_length_remaining;

		U::TraceLine(data.src, end, 0x4600400B, G::LocalPlayer, &data.enter_trace);
		U::ClipTraceToPlayers(data.src, end + data.direction * 40.f, 0x4600400B, &data.filter, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if ((data.enter_trace.hitgroup <= 7) && (data.enter_trace.hitgroup > 0))
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= pow(weaponData->range_modifier, data.trace_length * 0.002);
			ScaleDamage(data.enter_trace.hitgroup, (CBaseEntity*)data.enter_trace.m_pEnt, weaponData->armor_ratio, data.current_damage);

			return true;
		}

		if (!HandleBulletPenetration(weaponData, data))
			break;
	}

	return false;
}

float CAutowall::GetDamagez(const Vector& point)
{
	float damage = 0.f;
	Vector dst = point;
	FireBulletData data;
	data.src = G::LocalPlayer->GetEyePosition();
	data.filter.pSkip = G::LocalPlayer;

	QAngle angles = M::CalcAngle(data.src, dst);
	M::AngleVectors(angles, &data.direction);
	Vector dataNormalized;

	data.direction.Normalized();

	CBaseWeapon* pWeap = G::LocalPlayer->GetBaseWeapon();
	if (SimulateFireBullet(pWeap, data))
	{
		damage = data.current_damage;
	}

	return damage;
}

float CAutowall::GetDamage(const Vector& point, FireBulletData& fData)
{/*
 float damage = 0.f;
 Vector dst = point;
 FireBulletData data;
 data.src = G::LocalPlayer->GetEyePosition();
 data.filter.pSkip = G::LocalPlayer;

 QAngle angles = M::CalcAngle(data.src, dst);
 M::AngleVectors(angles, &data.direction);

 data.direction.NormalizeInPlace();

 CBaseWeapon* pWeap = G::LocalPlayer->GetWeapon();

 if (SimulateFireBullet(pWeap, data))
 damage = data.current_damage;

 fData = data;*/

	return 0;
}
#define VK_E 0x45
#define VK_C 0x43
#define VK_V 0x56
int Vibor1 = -1;
const char* AimKey[10] = { "LKM", "PKM", "CTRL", "SHIFT", "E", "C", "V", "Mouse5", "Mouse6","CapsLock" };
DWORD dwKey[10] = { VK_LBUTTON, VK_RBUTTON, VK_LCONTROL, VK_SHIFT, VK_E, VK_C, VK_V, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL };


bool CRageBot::Run()
{
	QAngle oldAngle;
	Interfaces::Engine()->GetViewAngles(oldAngle);
	oldForward = G::UserCmd->forwardmove;
	oldSideMove = G::UserCmd->sidemove;

	if (!Settings::Ragebot::Enabled)
		return false;

	if (G::LocalPlayer->GetWeapon()->IsGrenade())
		return false;

	if (G::LocalPlayer->GetWeapon()->IsKnife())
		return false;

	G::BestTarget = -1;

	if (!G::LocalPlayer->GetBaseWeapon())
		return false;

	if (G::BestTarget == -1)
		FindTarget();

	if (G::BestTarget != -1 && m_target)
		GoToTarget();


	if (!Settings::Ragebot::aw)
		M::CorrectMovement(oldAngle, G::UserCmd, oldForward, oldSideMove);


	return true;
}

void CRageBot::GetBestBone(CBaseEntity* entity, float& best_damage, Bone& best_bone)
{
	if (entity == G::LocalPlayer)
		return;
	bool Baim = false;
	if ((Settings::Ragebot::BaimAfterShoots > 0 && G::LocalPlayer->GetShotsFired() > Settings::Ragebot::BaimAfterShoots) || (Settings::Ragebot::BaimAfterHP > 0 && entity->GetHealth() <= Settings::Ragebot::BaimAfterHP))
		Baim = true;
	else
		Baim = false;

	best_bone = BONE_HEAD;

	if (!Baim)
	{
		for (std::unordered_map<int, std::vector<const char*>>::iterator it = hitboxes.begin(); it != hitboxes.end(); it++)
		{
			if (!Settings::Ragebot::bones[it->first])
				continue;

			std::vector<const char*> hitboxList = hitboxes[it->first];

			for (std::vector<const char*>::iterator it2 = hitboxList.begin(); it2 != hitboxList.end(); it2++)
			{
				Bone bone = (Bone)entity->GetBoneByName(*it2);
				Vector vec_bone = entity->GetBonePosition(bone);

				float damage = AutoWall->GetDamagez(vec_bone);

				if (damage > best_damage)
				{
					best_damage = damage;
					best_bone = bone;
				}
			}
		}

	}
	if (Baim)
	{
		for (std::unordered_map<int, std::vector<const char*>>::iterator it = baim.begin(); it != baim.end(); it++)
		{
			if (!Settings::Ragebot::bones[it->first])
				continue;

			std::vector<const char*> hitboxList = baim[it->first];

			for (std::vector<const char*>::iterator it2 = hitboxList.begin(); it2 != hitboxList.end(); it2++)
			{
				Bone bone = (Bone)entity->GetBoneByName(*it2);
				Vector vec_bone = entity->GetBonePosition(bone);

				float damage = AutoWall->GetDamagez(vec_bone);

				if (damage > best_damage)
				{
					best_damage = damage;
					best_bone = bone;
				}
			}
		}

	}
}



void CRageBot::FindTarget()
{
	m_bestfov = Settings::Ragebot::FOV;
	m_bestdist = 8192.f;
	m_bestthreat = 0.f;
	G::BestHitboxVec = Vector(0, 0, 0);
	m_target = false;
	m_bestent = nullptr;

	for (int i = 0; i <= Interfaces::GlobalVars()->maxClients; i++)
	{
		if (!EntityIsValid(i))
			continue;

		PlayerInfo entityInformation;
		Interfaces::Engine()->GetPlayerInfo(i, &entityInformation);
		CBaseEntity* Entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
		Vector hitbox = Entity->GetBonePosition(Settings::Ragebot::Hitbox);

		QAngle viewAngles;
		Interfaces::Engine()->GetViewAngles(viewAngles);

		float fov = M::GetFov(viewAngles, M::CalcAngle(G::LocalPlayer->GetEyePosition(), hitbox));
		if (fov < m_bestfov)
		{
			G::BestTarget = i;
			if (Settings::Ragebot::HitScan > 0)
			{
				if (Settings::Ragebot::HitScan == 1 && Settings::Ragebot::aw)
				{
					float damage = 0.0f;
					Bone bone;
					GetBestBone(Entity, damage, bone);

					if (damage >= Settings::Ragebot::AutoWallDmg)
					{
						m_bestent = Entity;
						G::BestHitboxVec = Entity->GetBonePosition(bone);
						m_target = true;
					}
				}
			}
			else
			{
				m_bestent = Entity;
				m_bestfov = fov;
				G::BestHitboxVec = hitbox;
				m_target = true;
			}
		}
	}
}

void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector &out)
{
	out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
	out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
	out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
}

bool HitChance(float flChance, CBaseWeapon *pWep)
{
	if (flChance >= 99.f)
		flChance = 99.f;

	if (flChance < 1)
		flChance = 1;

	float flSpread = pWep->GetInaccuracy() * 10;
	return ((((100.f - flChance) * 0.65f) * 0.01125) >= flSpread);
}

bool MultiPoints(CBaseEntity* target, Vector Start)
{
	if (target) {
		matrix3x4_t matrix[128];

		CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		if (!pLocal)
			return false;

		CBaseWeapon* pWeapon = pLocal->GetWeapon();
		if (!pWeapon)
			return false;

		if (!target->SetupBones2(matrix, 128, 0x00000100, 0))
			return false;

		studiohdr_t* studioHdr = Interfaces::ModelInfo()->GetStudioModel(target->GetModel2());

		if (!studioHdr)
			return false;

		mstudiobbox_t* pBox = studioHdr->pHitbox(Settings::Ragebot::Hitbox, 0);

		if (!pBox)
			return false;

		Vector points[8] = { Vector(pBox->m_vBbmin.x, pBox->m_vBbmin.y, pBox->m_vBbmin.z), // 0
			Vector(pBox->m_vBbmin.x, pBox->m_vBbmax.y, pBox->m_vBbmin.z), // 1
			Vector(pBox->m_vBbmax.x, pBox->m_vBbmax.y, pBox->m_vBbmin.z), // 2
			Vector(pBox->m_vBbmax.x, pBox->m_vBbmin.y, pBox->m_vBbmin.z), // 3
			Vector(pBox->m_vBbmax.x, pBox->m_vBbmax.y, pBox->m_vBbmax.z), // 4
			Vector(pBox->m_vBbmin.x, pBox->m_vBbmax.y, pBox->m_vBbmax.z), // 5
			Vector(pBox->m_vBbmin.x, pBox->m_vBbmin.y, pBox->m_vBbmax.z), // 6
			Vector(pBox->m_vBbmax.x, pBox->m_vBbmin.y, pBox->m_vBbmax.z)  // 7
		};

		Vector vMin, vMax;

		VectorTransform(pBox->m_vBbmin, matrix[pBox->m_Bone], vMin);
		VectorTransform(pBox->m_vBbmax, matrix[pBox->m_Bone], vMax);

		Vector vCenter = (vMin + vMax) * 0.5f;
		Start = vCenter;

		if (Settings::Ragebot::MultiPoints)
		{
			int iCount = 7;

			for (int i = 0; i <= iCount; i++)
			{
				Vector vTargetPos;
				switch (i)
				{
				case 0:
				default:
					vTargetPos = vCenter; break;
				case 1:
					vTargetPos = (points[7] + points[1]) * Settings::Ragebot::PointScale; break;
				case 2:
					vTargetPos = (points[3] + points[4]) * Settings::Ragebot::PointScale; break;
				case 3:
					vTargetPos = (points[4] + points[0]) * Settings::Ragebot::PointScale; break;
				case 4:
					vTargetPos = (points[2] + points[7]) * Settings::Ragebot::PointScale; break;
				case 5:
					vTargetPos = (points[6] + points[7]) * Settings::Ragebot::PointScale; break;
				case 6:
					vTargetPos = (points[5] + points[3]) * Settings::Ragebot::PointScale; break;
				case 7:
					vTargetPos = (points[1] + points[2]) * Settings::Ragebot::PointScale; break;
				}

				if (i > 0)
				{
					Vector vReturnPos;
					VectorTransform(vTargetPos, matrix[pBox->m_Bone], vReturnPos);
					Start = vReturnPos;
				}
			}

			return true;
		}
		else
			return true;
	}
	else
		return false;
}

float GetDistance(float* A, float* B)
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];
	float dz = A[2] - B[2];

	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

void CRageBot::GoToTarget()
{
	bool auto_shoot = false;
	bool can_shoot = true;
	bool reloading = false;
	CMe * m_pLocal;

	if (!Settings::Ragebot::Enabled)
		return;

	auto weapon = G::LocalPlayer->GetWeapon();
	int weap_id = G::LocalPlayer->GetWeapon()->GetWeaponId();
	int weap_type = G::LocalPlayer->GetWeapon()->GetWeaponType();

	if (!weapon)
		return;

	float server_time = G::LocalPlayer->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;

	float next_shot = weapon->GetNextPrimaryAttack() - server_time;
	if (next_shot > 0 || (Settings::Ragebot::ShootWhenStopped && G::LocalPlayer->GetVelocity().Length() > 60))
		can_shoot = false;

	MultiPoints(m_bestent, G::BestHitboxVec);

	QAngle aim_angle = M::CalcAngle(G::LocalPlayer->GetEyePosition(), G::BestHitboxVec);

	static int chocked = 0;

	if (Settings::Ragebot::RCS)
		aim_angle -= G::LocalPlayer->GetAimPunchAngle() * 2.f;

	if (!Settings::Ragebot::MultiPoints)
		return;




	if (can_shoot)
	{


		if (Settings::Ragebot::Silent)
		{
			QAngle oldView = G::UserCmd->viewangles;
			float oldSidemove = G::UserCmd->sidemove;
			float oldForwardmove = G::UserCmd->forwardmove;

			float flServerTime = G::LocalPlayer->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;
			float flNextPrimaryAttack = G::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();

			bool bBulletTime = true;
			if (flNextPrimaryAttack > flServerTime)
				bBulletTime = false;

			if (G::UserCmd->buttons & IN_ATTACK)
			{
				bSendPacket = false;
			}
			else {
				bSendPacket = true;
				G::UserCmd->viewangles = oldView;
				G::UserCmd->sidemove = oldSidemove;
				G::UserCmd->forwardmove = oldForwardmove;
			}

		}

		if (Settings::Ragebot::Aimstep)
		{
			auto_shoot = AimStep(aim_angle);
			if (auto_shoot)
			{
				G::Aimbotting = true;
				G::UserCmd->viewangles = aim_angle;
			}
		}
		else
		{
			auto_shoot = true;
			G::Aimbotting = true;
			G::UserCmd->viewangles = aim_angle;
		}
	}

	if (!Settings::Ragebot::Silent)
		Interfaces::Engine()->SetViewAngles(G::UserCmd->viewangles);

	if (Settings::Ragebot::AutoStop)
	{
		if (!Settings::Ragebot::ShootWhenStopped && (!Settings::Ragebot::AutoStopCanShoot || can_shoot))
		{
			if (!Settings::Ragebot::AutoStopFast || G::LocalPlayer->GetVelocity().Length() <= 60)
			{
				oldForward = 0;
				oldSideMove = 0;
				G::UserCmd->upmove = 0;
			}
			else
			{
				oldForward = -oldForward;
				oldSideMove = -oldSideMove;
				G::UserCmd->upmove = 0;
				auto_shoot = false;
			}
		}
	}


	if (Settings::Ragebot::AutoCrouch)
		G::UserCmd->buttons |= IN_DUCK;

	///* Auto Reload */
	if (weapon->GetWeaponAmmo() == 0)
	{
		G::UserCmd->buttons &= ~IN_ATTACK;
		G::UserCmd->buttons |= IN_RELOAD;
	}

	if (auto_shoot && can_shoot && Settings::Ragebot::AutoFire && (!Settings::Ragebot::HitChance || HitChance(Settings::Ragebot::HitChanceAmt, G::LocalPlayer->GetWeapon()))) {
		float dist = M::VectorDistance(G::LocalPlayer->GetOrigin(), m_bestent->GetOrigin());

		if (weap_id == WEAPON_TASER && Settings::Ragebot::ZeusBot && dist < Settings::Ragebot::ZeusDist)
			G::UserCmd->buttons |= IN_ATTACK;
		else if (weap_id != WEAPON_TASER)
			G::UserCmd->buttons |= IN_ATTACK;

		G::Aimbotting = true;
	}

	CBaseWeapon* activeWeapon = G::LocalPlayer->GetWeapon();
	float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();
	if ((nextPrimaryAttack - (G::LocalPlayer->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick)) > 0)
	{
		G::UserCmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		if (Settings::Ragebot::AutoScope && (G::LocalPlayer->GetWeapon()->GetWeaponType() == WEAPONTYPE_SNIPER_RIFLE || G::LocalPlayer->GetWeapon()->GetWeaponId() == WEAPON_AUG || G::LocalPlayer->GetWeapon()->GetWeaponId() == WEAPON_SG556) && !G::LocalPlayer->GetIsScoped())
		{
			G::UserCmd->buttons |= IN_ZOOM;
		}


	}
}

bool CRageBot::AimStep(QAngle& angle)
{
	if (!G::Aimbotting)
		AimStepLastAngle = G::UserCmd->viewangles;

	float fov = M::GetFov(AimStepLastAngle, angle);

	G::Aimbotting = fov > Settings::Ragebot::AimstepAmount;

	if (!G::Aimbotting)
		return true;

	QAngle AimStepDelta = AimStepLastAngle - angle;

	if (AimStepDelta.y < 0)
		AimStepLastAngle.y += Settings::Ragebot::AimstepAmount;
	else
		AimStepLastAngle.y -= Settings::Ragebot::AimstepAmount;

	AimStepLastAngle.x = angle.x;
	angle = AimStepLastAngle;

	return false;
}

float GenerateRandomFloat(float Min, float Max)
{
	float randomized = (float)rand() / (float)RAND_MAX;
	return Min + randomized * (Max - Min);
}

bool CRageBot::GetHitbox(CBaseEntity* target, Hitbox* hitbox)
{
	matrix3x4_t matrix[MAXSTUDIOBONES];

	if (!target->SetupBones2(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
		return false;


	studiohdr_t *hdr = Interfaces::ModelInfo()->GetStudioModel(target->GetModel2());

	if (!hdr)
		return false;

	mstudiohitboxset_t *hitboxSet = hdr->pHitboxSet(target->GetHitboxSet_());
	mstudiobbox_t *untransformedBox = hitboxSet->pHitbox(hitbox->hitbox);

	Vector bbmin = untransformedBox->m_vBbmin;
	Vector bbmax = untransformedBox->m_vBbmax;

	if (untransformedBox->m_flRadius != -1.f)
	{
		bbmin -= Vector(untransformedBox->m_flRadius, untransformedBox->m_flRadius, untransformedBox->m_flRadius);
		bbmax += Vector(untransformedBox->m_flRadius, untransformedBox->m_flRadius, untransformedBox->m_flRadius);
	}

	Vector points[] = { ((bbmin + bbmax) * .5f),
		Vector(bbmin.x, bbmin.y, bbmin.z),
		Vector(bbmin.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmin.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmin.y, bbmax.z),
		Vector(bbmax.x, bbmin.y, bbmax.z) };


	for (int index = 0; index <= 8; ++index)
	{
		if (index != 0)
			points[index] = ((((points[index] + points[0]) * .5f) + points[index]) * .5f);

		M::VectorTransform(points[index], matrix[untransformedBox->m_Bone], hitbox->points[index]);
	}

	Vector vMin, vMax, vCenter, sCenter;
	VectorTransform(bbmin, matrix[hitbox->hitbox], vMin);
	VectorTransform(bbmax, matrix[hitbox->hitbox], vMax);
	vCenter = (vMin + vMax) * 0.5;

	return true;
}

bool CRageBot::GetBestPoint(CBaseEntity* target, Hitbox* hitbox, BestPoint *point)
{
	Vector center = hitbox->points[0];

	if (hitbox->hitbox == HITBOX_HEAD)
	{
		Vector high = ((hitbox->points[3] + hitbox->points[5]) * .5f);

		float pitch = target->GetEyeAngles().x;
		if ((pitch > 0.f) && (pitch <= 89.f))
		{
			Vector height = (((high - hitbox->points[0]) / 3) * 4);
			Vector new_height = (hitbox->points[0] + (height * (pitch / 89.f)));

			hitbox->points[0] = new_height;
			point->flags |= FL_HIGH;
		}
		else if ((pitch < 292.5f) && (pitch >= 271.f))
		{
			hitbox->points[0] -= Vector(0.f, 0.f, 1.f);
			point->flags |= FL_LOW;
		}
	}

	for (int index = 0; index <= 8; ++index)
	{
		int temp_damage = AutoWall->GetDamagez(hitbox->points[index]);

		if ((point->dmg < temp_damage))
		{
			point->dmg = temp_damage;
			point->point = hitbox->points[index];
			point->index = index;
		}
	}

	return (point->dmg > Settings::Ragebot::AutoWallDmg);
}


enum class CSGOHitboxID
{
	Head = 0,
	Neck,
	Pelvis,
	Stomach,
	LowerChest,
	Chest,
	UpperChest,
	RightThigh,
	LeftThigh,
	RightShin,
	LeftShin,
	RightFoot,
	LeftFoot,
	RightHand,
	LeftHand,
	RightUpperArm,
	RightLowerArm,
	LeftUpperArm,
	LeftLowerArm
};


int CRageBot::BestAimPointHitbox(CBaseEntity* target)
{
	return -1;
}

bool CRageBot::EntityIsValid(int i)
{
	CBaseEntity* Entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

	if (!Entity)
		return false;

	if (Entity == G::LocalPlayer)
		return false;

	if (!Settings::Ragebot::FriendlyFire)
	{
		if (Entity->GetTeam() == G::LocalPlayer->GetTeam())
			return false;
	}

	if (!Entity->IsVisible(G::LocalPlayer) && !Settings::Ragebot::aw)
		return false;

	/*if (Entity->IsDormant())
		return false;*/

	if (Entity->GetHealth() <= 0)
		return false;

	if (Settings::Ragebot::HitScan == 0 && Settings::Ragebot::aw)

		if (Settings::Ragebot::AutoWallDmg > AutoWall->GetDamagez(Entity->GetBonePosition(Settings::Ragebot::Hitbox)))
			return false;

	return true;
}



