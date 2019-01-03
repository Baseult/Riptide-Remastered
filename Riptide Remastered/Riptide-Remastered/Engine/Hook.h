#pragma once

#include "Engine.h"
#include "Render2.h"
#include "../VMT/Vmthook.h"
typedef void(__thiscall* paint_traverse_t)(PVOID, unsigned int, bool, bool);                  // PaintTraverse hook
using create_move_t = void(__thiscall *)(IBaseClientDLL *, int, float, bool);                 // CreateMove hook
using EmitsoundXD = void(__stdcall*)(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
	float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags, int iPitch,
	const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int test);
using PlaySound = void(__thiscall *)(ISurface*, const char*);

namespace Engine
{
	namespace Hook
	{
		bool Initialize();
		void Shutdown();
	}
}