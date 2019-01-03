//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#pragma once

#include <Windows.h>

#ifndef NETWORKSTRINGTABLEDEFS_H
#define NETWORKSTRINGTABLEDEFS_H
#ifdef _WIN32
#pragma once
#endif

typedef int TABLEID;

#define INVALID_STRING_TABLE -1
const unsigned short INVALID_STRING_INDEX = (unsigned short)-1;

// table index is sent in log2(MAX_TABLES) bits
#define MAX_TABLES	32  // Table id is 4 bits

#define INTERFACENAME_NETWORKSTRINGTABLESERVER "VEngineServerStringTable001"
#define INTERFACENAME_NETWORKSTRINGTABLECLIENT "VEngineClientStringTable001"

class INetworkStringTable;

typedef void(*pfnStringChanged)(void *object, INetworkStringTable *stringTable, int stringNumber, char const *newString, void const *newData);

//-----------------------------------------------------------------------------
// Purpose: Game .dll shared string table interfaces
//-----------------------------------------------------------------------------
class INetworkStringTable
{
public:

	virtual					~INetworkStringTable(void) {};

	// Table Info
	virtual const char		*GetTableName(void) const = 0;
	virtual TABLEID			GetTableId(void) const = 0;
	virtual int				GetNumStrings(void) const = 0;
	virtual int				GetMaxStrings(void) const = 0;
	virtual int				GetEntryBits(void) const = 0;

	// Networking
	virtual void			SetTick(int tick) = 0;
	virtual bool			ChangedSinceTick(int tick) const = 0;

	// Accessors (length -1 means don't change user data if string already exits)
	virtual int				AddString(bool bIsServer, const char *value, int length = -1, const void *userdata = 0) = 0;

	virtual const char		*GetString(int stringNumber) = 0;
	virtual void			SetStringUserData(int stringNumber, int length, const void *userdata) = 0;
	virtual const void		*GetStringUserData(int stringNumber, int *length) = 0;
	virtual int				FindStringIndex(char const *string) = 0; // returns INVALID_STRING_INDEX if not found

																	 // Callbacks
	virtual void			SetStringChangedCallback(void *object, pfnStringChanged changeFunc) = 0;
};

class INetworkStringTableContainer
{
public:

	virtual					~INetworkStringTableContainer(void) {};

	// table creation/destruction
	virtual INetworkStringTable	*CreateStringTable(const char *tableName, int maxentries, int userdatafixedsize = 0, int userdatanetworkbits = 0) = 0;
	virtual void				RemoveAllTables(void) = 0;

	// table infos
	virtual INetworkStringTable	*FindTable(const char *tableName) const = 0;
	virtual INetworkStringTable	*GetTable(TABLEID stringTable) const = 0;
	virtual int					GetNumTables(void) const = 0;

	virtual INetworkStringTable	*CreateStringTableEx(const char *tableName, int maxentries, int userdatafixedsize = 0, int userdatanetworkbits = 0, bool bIsFilenames = false) = 0;
	virtual void				SetAllowClientSideAddString(INetworkStringTable *table, bool bAllowClientSideAddString) = 0;
};

#endif // NETWORKSTRINGTABLEDEFS_H

class CNetworkStringTableContainer
{
public:
	INetworkStringTable * FindTable(const char *tableName)
	{
		typedef INetworkStringTable*(__thiscall* oFindTable)(PVOID, const char*);
		return GetMethod<oFindTable>(this, 3)(this, tableName);
	}
};



struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

struct surfaceaudioparams_t
{
	float reflectivity;
	float hardnessFactor;
	float roughnessFactor;
	float roughThreshold;
	float hardThreshold;
	float hardVelocityThreshold;
};

struct surfacesoundnames_t
{
	unsigned short walkStepLeft;
	unsigned short walkStepRight;
	unsigned short runStepLeft;
	unsigned short runStepRight;
	unsigned short impactSoft;
	unsigned short impactHard;
	unsigned short scrapeSmooth;
	unsigned short scrapeRough;
	unsigned short bulletImpact;
	unsigned short rolling;
	unsigned short breakSound;
	unsigned short strainSound;
};

struct surfacesoundhandles_t
{
	short walkStepLeft;
	short walkStepRight;
	short runStepLeft;
	short runStepRight;
	short impactSoft;
	short impactHard;
	short scrapeSmooth;
	short scrapeRough;
	short bulletImpact;
	short rolling;
	short breakSound;
	short strainSound;
};

struct surfacegameprops_t
{
public:
	float maxSpeedFactor;
	float jumpFactor;
	char pad00[0x4];
	float flPenetrationModifier;
	float flDamageModifier;
	unsigned short material;
	char pad01[0x3];
};

struct surfacedata_t
{
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
	surfacesoundhandles_t soundhandles;
};

class IPhysicsSurfaceProps
{
public:
	virtual ~IPhysicsSurfaceProps(void)
	{}

	// parses a text file containing surface prop keys
	virtual int ParseSurfaceData(const char* pFilename, const char* pTextfile) = 0;
	// current number of entries in the database
	virtual int SurfacePropCount(void) const = 0;

	virtual int GetSurfaceIndex(const char* pSurfacePropName) const = 0;
	virtual void GetPhysicsProperties(int surfaceDataIndex, float* density, float* thickness, float* friction, float* elasticity) const = 0;

	virtual surfacedata_t* GetSurfaceData(int surfaceDataIndex) = 0;
	virtual const char* GetString(unsigned short stringTableIndex) const = 0;

	virtual const char* GetPropName(int surfaceDataIndex) const = 0;

	// sets the global index table for world materials
	// UNDONE: Make this per-CPhysCollide
	virtual void SetWorldMaterialIndexTable(int* pMapArray, int mapSize) = 0;

	// NOTE: Same as GetPhysicsProperties, but maybe more convenient
	virtual void GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t* pParamsOut) const = 0;
};
