#pragma once
#ifndef CGRENADE_H
#define CGRENADE_H

#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <process.h>
#include <Mmsystem.h>
#include <stdint.h>
#include <signal.h>
#include <WinInet.h>
#include <comdef.h>
#include <Wbemidl.h>
#include "../../SDK/Vector.hpp"
#include <WinSock.h>
#include <Windns.h>
#include <vector>
#pragma comment (lib, "iphlpapi.lib")
#pragma comment (lib, "Wininet.lib")
#pragma comment (lib, "urlmon.lib")
#pragma comment (lib, "wbemuuid.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "Dnsapi.lib")

#pragma warning(disable:4996)
#pragma warning(disable:4244)

struct GrenadeInfo_t
{
	int id; // id
	std::string szName; // Name
	std::string szDescription; // Description
	std::string szWeapon; // GrenadeName
	SDK::Vector vecOrigin; // Position
	SDK::Vector vecViewangles; // Angle
};

class CGrenadeAPI
{
private:
	std::string szHost = "asrjfsanfasuirwqirioqwer.altervista.org";
	std::string szApi = "/grenadeapi/pages/api.php?map=";

	std::string HttpGet(std::string hostaddr, std::string api);
	std::string parseString(std::string szBefore, std::string szAfter, std::string szSource);

public:
	std::vector<GrenadeInfo_t> GrenadeInfo;
	bool bUpdateGrenadeInfo(std::string szMapName);
	bool GetInfo(int iNum, GrenadeInfo_t* info);
};


extern CGrenadeAPI cGrenade;

#endif 

