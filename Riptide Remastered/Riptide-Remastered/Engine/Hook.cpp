
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																																				//
//																	CREDITS:																	//					
//																																				//
//											Riptide founded and coded by Baseult https://www.unknowncheats.me/forum/members/2604732.html		//
//											Riptide founded and coded by mitch 																    //
//											Riptide founded and coded by Swifty 									                            //
//											Riptide founded and coded by undetected 							                                //
//											Riptide founded and coded by karmafreediet 				                                            //
//											Riptide coded by vsonyp0wer 							                                            //
//																																			    //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "Hook.h"


//[enc_string_enable /]
//[junk_enable /]

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG1( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD1( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define Assert(_exp) ((void)0)

namespace G
{
	extern CBaseEntity* LocalPlayer;
	extern CUserCmd* UserCmd;

}

namespace Engine
{
	namespace Hook
	{



		//CVMT HOOKS
		vfunc_hook panel;
		vfunc_hook client;
		vfunc_hook sound;
		vfunc_hook surface;

		//VMT HOOKS
		CSX::Hook::VTable IDirect3DDevice9Table;
		CSX::Hook::VTable ClientModeTable;
		CSX::Hook::VTable GameEventTable;
		CSX::Hook::VTable ModelRenderTable;
		CSX::Hook::VTable ClientTable;
		CSX::Hook::VTable SteamGameCoordinatorTable;



		IDirect3DDevice9* g_pDevice = nullptr;

		typedef HRESULT(WINAPI* Present_t)(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
		Present_t Present_o;

		typedef HRESULT(WINAPI* Reset_t)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
		Reset_t Reset_o;

		struct CUSTOMVERTEX {
			FLOAT x, y, z;
			FLOAT rhw;
			DWORD color;
			// FLOAT tu, tv; 
		};

		//----------------------------------------------CLAMP STUFF--------------------------------------------------------------
		void VectorAngles(Vector forward, QAngle & ang_out)
		{
			if (forward.x == 0.0f && forward.y == 0.0f)
			{
				ang_out.x = (forward.z <= 0.0f) ? 90.0f : 270.f;
				ang_out.y = 0.0f;
			}
			else
			{
				ang_out.x = atan2(-forward.z, forward.Length2D()) * -180 / 3.14;
				ang_out.y = atan2(forward.y, forward.x) * 180 / 3.14;
			}

			ang_out.z = 0.0f;
		}


		void NormalizeFloat(float & in)
		{
			if (in > 180.f || in < -180.f)
			{
				float ry = in / 360.f;

				if (ry < 0.f)
					ry = -ry;

				ry = round(ry);

				if (in < 0.f)
					in = (in + 360.f * ry);
				else
					in = (in - 360.f * ry);
			}
		}


		//--------------------------------------------------CIRCLE----------------------------------------------------------
		void CircleFilledDualColor(float x, float y, float rad, float rotate, int type, int resolution, DWORD color, DWORD color2, IDirect3DDevice9* m_device)
		{
			LPDIRECT3DVERTEXBUFFER9 g_pVB2;

			std::vector<CUSTOMVERTEX> circle(resolution + 2);

			float angle = rotate * D3DX_PI / 180, pi = D3DX_PI;

			if (type == 1)
				pi = D3DX_PI; // Full circle
			if (type == 2)
				pi = D3DX_PI / 2; // 1/2 circle
			if (type == 3)
				pi = D3DX_PI / 4; // 1/4 circle

			pi = D3DX_PI / type; // 1/4 circle

			circle[0].x = x;
			circle[0].y = y;
			circle[0].z = 0;
			circle[0].rhw = 1;
			circle[0].color = color2;

			for (int i = 1; i < resolution + 2; i++)
			{
				circle[i].x = (float)(x - rad * cos(pi*((i - 1) / (resolution / 2.0f))));
				circle[i].y = (float)(y - rad * sin(pi*((i - 1) / (resolution / 2.0f))));
				circle[i].z = 0;
				circle[i].rhw = 1;
				circle[i].color = color;
			}


			int _res = resolution + 2;
			for (int i = 0; i < _res; i++)
			{
				circle[i].x = x + cos(angle)*(circle[i].x - x) - sin(angle)*(circle[i].y - y);
				circle[i].y = y + sin(angle)*(circle[i].x - x) + cos(angle)*(circle[i].y - y);
			}

			m_device->CreateVertexBuffer((resolution + 2) * sizeof(CUSTOMVERTEX), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB2, NULL);

			VOID* pVertices;
			g_pVB2->Lock(0, (resolution + 2) * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0);
			memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(CUSTOMVERTEX));
			g_pVB2->Unlock();

			m_device->SetTexture(0, NULL);
			m_device->SetPixelShader(NULL);
			m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			m_device->SetStreamSource(0, g_pVB2, 0, sizeof(CUSTOMVERTEX));
			m_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
			m_device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, resolution);
			if (g_pVB2 != NULL)
				g_pVB2->Release();
		}

		void DrawLine(int x0, int y0, int x1, int y1, Color col)
		{
			Interfaces::Surface()->DrawSetColor(col);
			Interfaces::Surface()->DrawLine(x0, y0, x1, y1);
		}

		void DrawCircle(float x, float y, float r, float s, Color color)
		{
			float Step = M_PI * 2.0 / s;
			for (float a = 0; a < (M_PI * 2.0); a += Step)
			{
				float x1 = r * cos(a) + x;
				float y1 = r * sin(a) + y;
				float x2 = r * cos(a + Step) + x;
				float y2 = r * sin(a + Step) + y;

				DrawLine(x1, y1, x2, y2, color);
			}
		}

		DWORD color = D3DCOLOR_RGBA((int)(0 * 255.0f), (int)(0 * 255.0f), (int)(0 * 255.0f), (int)(1 * 255.0f));
		DWORD color2 = D3DCOLOR_RGBA((int)(0 * 255.0f), (int)(0 * 255.0f), (int)(0 * 255.0f), (int)(0 * 255.0f));

		void Crosshair(IDirect3DDevice9* pDevice)
		{
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

			if (Settings::Misc::ShowSpread)
			{
				int width, height;
				Interfaces::Engine()->GetScreenSize(width, height);
				if (local && IsLocalAlive())
				{
					static Vector ViewAngles;
					Interfaces::Engine()->GetViewAngles(ViewAngles);
					ViewAngles += (local->GetAimPunchAngle()) * 2.f;

					static Vector fowardVec;
					AngleVectors(ViewAngles, fowardVec);
					fowardVec *= 10000;


					Vector start = local->GetOrigin() + local->GetViewOffset();
					Vector end = start + fowardVec, endScreen;

					CBaseWeapon* weaponbase = local->GetBaseWeapon();

					if (weaponbase->GetWeaponId())
					{
						float cone = weaponbase->GetInaccuracy();

						if (cone > 0.0f)
						{
							float size;
							Vector screen;

							if (cone < 0.01f) cone = 0.01f;

							float size1337 = (cone * height) * 0.7f;


							if (WorldToScreen(end, endScreen))
							{
								CircleFilledDualColor(Client::iScreenWidth / 2, Client::iScreenHeight / 2, size1337, 0, 1, 50, color, color2, pDevice);
							}
						}
					}
				}
			}
		}


		//--------------------------------------------------------HOOK RESETS------------------------------------------------------------------
		HRESULT WINAPI Hook_Present(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
		{
			Crosshair(pDevice);
			Client::OnRender();
			return Present_o(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}


		HRESULT WINAPI Hook_Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			Client::OnLostDevice();

			HRESULT hRes = Reset_o(pDevice, pPresentationParameters);

			Client::OnResetDevice();

			return hRes;
		}

		//------------------------------------------------------CREATEMOVE--------------------------------------------------------------------------------------
		void __stdcall CHLCreateMove(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
		{
			static auto oCreateMove = client.get_original<create_move_t>(22);
			oCreateMove(Interfaces::Client(), sequence_number, input_sample_frametime, active);
			CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			CUserCmd *cmd = Interfaces::Input()->GetUserCmd(0, sequence_number);
			if (!cmd)
				return;

			static float next_time = 0;

			if (!cmd->command_number)
				return;

			if (!localplayer)
				return;

			if (Settings::Misc::ThirdPersonType == 2)
			{
				if (Interfaces::Engine()->IsConnected() || Interfaces::Engine()->IsInGame())
				{

					Client::g_pAimbot->AntiAimCreateMoveFake(cmd, bSendPacket);
					Settings::Misc::qLastTickAngle = cmd->viewangles;
				}
			}

			Client::g_pAimbot->AntiAimCreateMoveFake(cmd, bSendPacket);
			Client::g_pAntiAim->Fakewalk(cmd, bSendPacket);
			Client::g_pAntiAim->Glitchwalk(cmd, bSendPacket);
			Client::g_pFakeLag->Fakelag(cmd, bSendPacket);


		}
#pragma warning(disable : 4409)
		__declspec(naked) void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
		{
			__asm
			{
				PUSH	EBP
				MOV		EBP, ESP
				PUSH	EBX
				LEA		ECX, [ESP]
				PUSH	ECX
				PUSH	active
				PUSH	input_sample_frametime
				PUSH	sequence_number
				CALL	CHLCreateMove
				POP		EBX
				POP		EBP
				RETN	0Ch
			}
		}

		bool WINAPI Hook_CreateMove(float flInputSampleTime, CUserCmd* cmd)
		{

			ClientModeTable.UnHook();
			auto origAng = cmd->viewangles;

			PDWORD pEBP;
			__asm mov pEBP, ebp;

			bool& bSendPacket = *(bool*)(*pEBP - 0x1C);


			if (Settings::Misc::ThirdPersonType == 1)
			{
				if (Interfaces::Engine()->IsConnected() || Interfaces::Engine()->IsInGame())
				{
					Client::g_pAimbot->AntiAimCreateMove(cmd, bSendPacket);
					Settings::Misc::qLastTickAngle = cmd->viewangles;
				}
			}

			Client::g_pAimbot->AntiAimCreateMove(cmd, bSendPacket);

			CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

			Client::OnCreateMove(cmd);

			bool ret = Interfaces::ClientMode()->CreateMove(flInputSampleTime, cmd);
			ClientModeTable.ReHook();

			if (Settings::Aimbot::weapon_aim_settings[Client::iWeaponID].aim_pSilent)
				return false;
			if (Settings::Ragebot::Silent)
				return false;
			if (Settings::Ragebot::AAEnabled)
				return false;
			if (Settings::Ragebot::Enabled)
				return false;


			return ret;
		}

		//------------------------------------------------------------------OVERRIDEVIEW---------------------------------------------------------
		bool WINAPI Hook_OverrideView(CViewSetup* pSetup)
		{
			Client::OnOverrideView(pSetup);

			ClientModeTable.UnHook();
			bool ret = Interfaces::ClientMode()->OverrideView(pSetup);
			ClientModeTable.ReHook();
			return ret;
		}

		float WINAPI Hook_GetViewModelFOV()
		{
			ClientModeTable.UnHook();
			float fov = Interfaces::ClientMode()->GetViewModelFOV();
			ClientModeTable.ReHook();

			Client::OnGetViewModelFOV(fov);

			return fov;
		}

		//-----------------------------------------------------------------MESSAGES----------------------------------------------------------------------

		EGCResults __fastcall Hook_RetrieveMessage(void* ecx, void* edx, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize)
		{
			SteamGameCoordinatorTable.UnHook();
			EGCResults status = Interfaces::SteamGameCoordinator()->RetrieveMessage(punMsgType, pubDest, cubDest, pcubMsgSize);
			SteamGameCoordinatorTable.ReHook();
			if (status != k_EGCResultOK)
				return status;
			Client::OnRetrieveMessage(ecx, edx, punMsgType, pubDest, cubDest, pcubMsgSize);
			return status;
		}
		EGCResults __fastcall Hook_SendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
		{
			uint32_t messageType = unMsgType & 0x7FFFFFFF;
			void* pubDataMutable = const_cast<void*>(pubData);
			Client::OnSendMessage(ecx, edx, unMsgType, pubData, cubData);
			SteamGameCoordinatorTable.UnHook();
			EGCResults status = Interfaces::SteamGameCoordinator()->SendMessage(unMsgType, pubData, cubData);
			SteamGameCoordinatorTable.ReHook();
			return status;
		}

		//--------------------------------------------------------------FIREEVENT------------------------------------------------------------------------------------

		bool WINAPI Hook_FireEventClientSideThink(IGameEvent* pEvent)
		{
			bool ret = false;

			if (!pEvent)
			{
				GameEventTable.UnHook();
				ret = Interfaces::GameEvent()->FireEventClientSide(pEvent);
				GameEventTable.ReHook();
				return ret;
			}

			Client::OnFireEventClientSideThink(pEvent);

			GameEventTable.UnHook();
			ret = Interfaces::GameEvent()->FireEventClientSide(pEvent);
			GameEventTable.ReHook();

			return ret;
		}

		//-------------------------------------------------------------FRAMESTAGE------------------------------------
		
																												
		void WINAPI Hook_FrameStageNotify(ClientFrameStage_t Stage)													
		{																											
			Client::OnFrameStageNotify(Stage);																		
			if (Stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)									
			{																										
				Client::g_pResolver->Resolver();																	
				Client::g_pResolver->Override();																	
			}																									    
			ClientTable.UnHook();																					
			Interfaces::Client()->FrameStageNotify(Stage);														
			ClientTable.ReHook();																					
		}																											





		//------------------------------------------------------------DRAWMODEL--------------------------------------------------------------------------------------
		void WINAPI Hook_DrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state,
			const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld = NULL)
		{
			ModelRenderTable.UnHook();

			if (ctx && pCustomBoneToWorld)
				Client::OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			if (ctx && pCustomBoneToWorld && Client::g_pEsp && Settings::Esp::esp_Chams)
			{
				Interfaces::ModelRender()->ForcedMaterialOverride(0);
			}

			ModelRenderTable.ReHook();
		}





		void AngleVectors2(const Vector &angles, Vector *forward)
		{
			Assert(s_bMathlibInitialized);
			Assert(forward);

			float  sp, sy, cp, cy;

			sy = sin(DEG2RAD(angles[1]));
			cy = cos(DEG2RAD(angles[1]));

			sp = sin(DEG2RAD(angles[0]));
			cp = cos(DEG2RAD(angles[0]));

			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		Vector CalcAngle2(Vector src, Vector dst)
		{
			Vector ret;
			VectorAngles(dst - src, ret);
			return ret;
		}

		void OutOfViewIndicatorCircle(CBaseEntity * entity)
		{
			CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			if (!entity || !pLocal)
				return;
			if (entity == pLocal)
				return;
			
			if (entity->GetTeam() == pLocal->GetTeam())
				return;
			if (entity->IsDead())
				return;

			Vector eyeangles, poopvec;
			int screen_w, screen_h;
			Interfaces::Engine()->GetScreenSize(screen_w, screen_h);
			Interfaces::Engine()->GetViewAngles(eyeangles);
			QAngle newangle = CalcAngle2(Vector(pLocal->GetAbsOrigin().x, pLocal->GetAbsOrigin().y, 0), Vector(entity->GetAbsOrigin().x, entity->GetAbsOrigin().y, 0));
			AngleVectors2(QAngle(0, 270, 0) - newangle + QAngle(0, eyeangles.y, 0), &poopvec);
			auto circlevec = Vector(screen_w / 2, screen_h / 2, 0) + (poopvec * 250.f);
			if (!entity->IsDead())
				g_Render->DrawFilledCircle(Vector2D(circlevec.x, circlevec.y), pLocal->IsVisible(entity) ? Color::Green() : Color::Red(), 10, 30);
		}
		std::string sPanel = ("FocusOverlayPanel");
		void __fastcall hkPaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
		{
			DWORD enabless;
			bool antiss = true;

			if (antiss)
				enabless = !Interfaces::Engine()->IsTakingScreenshot();
			else
				enabless = !antiss;

			const auto panelName = Interfaces::VPanel()->GetName(vguiPanel);
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			static auto ofunc = panel.get_original<paint_traverse_t>(41);

			ofunc(pPanels, vguiPanel, forceRepaint, allowForce);

			bool test = true;

			static unsigned int FocusOverlayPanel = 0;
			static bool FoundPanel = false;




			const char* pszPanelName = Interfaces::VPanel()->GetName(vguiPanel);

			if (!strstr(pszPanelName, sPanel.data()))
				return;


			Interfaces::VPanel()->SetMouseInputEnabled(vguiPanel, bIsGuiVisible);


			if (!FoundPanel)
			{
				PCHAR szPanelName = (PCHAR)Interfaces::VPanel()->GetName(vguiPanel);
				if (strstr(szPanelName, "FocusOverlayPanel"))
				{
					FocusOverlayPanel = vguiPanel;
					FoundPanel = true;
				}
			}
			else if (FocusOverlayPanel == vguiPanel && !Interfaces::Engine()->IsTakingScreenshot())
			{
				int w, h;
				Interfaces::Engine()->GetScreenSize(w, h);



				if (local && !local->IsDead() && Settings::Esp::esp_AAIndicator) {
					static const auto fake_color = Color(255, 0, 0);
					auto client_viewangles = Vector();
					Interfaces::Engine()->GetViewAngles(client_viewangles);
					int w, h;
					Interfaces::Engine()->GetScreenSize(w, h);

					constexpr auto radius = 80.f;

					const auto screen_center = Vector2D(w / 2.f, h / 2.f);
					const auto fake_rot = DEG2RAD(client_viewangles.y - lastFake.y - 90);

					auto draw_arrow = [&](float rot, Color color) -> void
					{
						std::vector<SDK::Vertex_t> vertices;
						vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot) * radius, screen_center.y + sinf(rot) * radius)));
						vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot + DEG2RAD(10)) * (radius - 15.f), screen_center.y + sinf(rot + DEG2RAD(10)) * (radius - 15.f)))); //25
						vertices.push_back(SDK::Vertex_t(Vector2D(screen_center.x + cosf(rot - DEG2RAD(10)) * (radius - 15.f), screen_center.y + sinf(rot - DEG2RAD(10)) * (radius - 15.f)))); //25
						g_Render->TexturedPolygon(3, vertices, color);
					};

					draw_arrow(fake_rot, fake_color);
					static const auto real_color = Color(0, 255, 0);
					const auto real_rot = DEG2RAD(client_viewangles.y - lastReal.y - 90);
					draw_arrow(real_rot, real_color);
					static const auto lby_color = Color(0, 0, 255);
					const auto lby_rot = DEG2RAD(client_viewangles.y - local->GetLowerBodyYaw() - 90);
					draw_arrow(lby_rot, lby_color);
				}


				if (Settings::Radar::barrel && Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
				{
					for (auto i = 1; i <= Interfaces::EntityList()->GetHighestEntityIndex(); ++i)
					{
						CBaseEntity* entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
						if (!entity)
							continue;
						if (entity == local)
							continue;
						using namespace Settings::Esp;
						if (i < 65 &&/* !entity->IsDormant() &&*/ !entity->IsDead()) {
							OutOfViewIndicatorCircle(entity);
						}
					}
				}
			}
		}
		QAngle CalcAngle(Vector src, Vector dst)
		{
			QAngle angles;
			Vector delta = src - dst;
			VectorAngles(delta, angles);
			delta.Normalized();
			return angles;
		}


		//-------------------------------------------------------------INITIALIZE---------------------------------------------------
		bool Initialize()
		{
			if (!CSX::Utils::IsModuleLoad(D3D9_DLL))
				return false;

			if (!CSX::Utils::IsModuleLoad(SHADERPIDX9_DLL))
				return false;

			if (!CSX::Utils::IsModuleLoad(GAMEOVERLAYRENDERER_DLL))
				return false;

			DWORD d3d9TablePtrPtr = CSX::Memory::FindPattern(SHADERPIDX9_DLL, D3D9_PATTERN, D3D9_MASK, 1);
			DWORD_PTR** dwPresent_o = (DWORD_PTR**)CSX::Memory::FindPattern(GAMEOVERLAYRENDERER_DLL, GMOR_PATTERN, GMOR_MASK, 1);

			if (d3d9TablePtrPtr && dwPresent_o)
			{
				g_pDevice = (IDirect3DDevice9*)(**(PDWORD*)d3d9TablePtrPtr);

				if (IDirect3DDevice9Table.InitTable(g_pDevice))
				{
					DWORD_PTR* dwAddress = *dwPresent_o;
					Present_o = (Present_t)(*dwAddress);
					*dwAddress = (DWORD_PTR)(&Hook_Present);

					Reset_o = (Reset_t)IDirect3DDevice9Table.GetHookIndex(D3D9::TABLE::Reset, Hook_Reset);

					//---------------------------------------------------CLIENTMODE-------------------------------------------------------------------					
					if (!ClientModeTable.InitTable(Interfaces::ClientMode()))
						return false;
					ClientModeTable.HookIndex(TABLE::IClientMode::CreateMove, Hook_CreateMove);
					ClientModeTable.HookIndex(TABLE::IClientMode::OverrideView, Hook_OverrideView);
					ClientModeTable.HookIndex(TABLE::IClientMode::GetViewModelFOV, Hook_GetViewModelFOV);

					//--------------------------------------------------PAINTTRAVERSE-----------------------------VMT UD---------------------------------
					if (!panel.setup(Interfaces::VPanel()))
						return false;
					panel.hook_index(41, hkPaintTraverse);

					//---------------------------------------------------CREATEMOVE / ANTIAIM -------------------VMT UD------------------------------
					if (!client.setup(Interfaces::Client()))
						return false;
					client.hook_index(22, hkCreateMove);

					//------------------------------------------------GAMEEVENT / LOGS --------------------------------------------------------------
					if (!GameEventTable.InitTable(Interfaces::GameEvent()))
						return false;

					GameEventTable.HookIndex(TABLE::IGameEventManager2::FireEventClientSide, Hook_FireEventClientSideThink);

					//------------------------------------------------SKINCHANGER / RAGEBOT------------------------------------------------------------
					if ( !ClientTable.InitTable( Interfaces::Client() ) )		
						return false;

					ClientTable.HookIndex( TABLE::IBaseClientDLL::FrameStageNotify , Hook_FrameStageNotify );

					//----------------------------------------PROTOBUF / INVENTORYCHANGER..-------------------------------------------------------
					if (!SteamGameCoordinatorTable.InitTable(Interfaces::SteamGameCoordinator()))
						return false;
					SteamGameCoordinatorTable.HookIndex(0, Hook_SendMessage);
					SteamGameCoordinatorTable.HookIndex(2, Hook_RetrieveMessage);

					//----------------------------------------CHAMS / ESP---------------------------------------------------------------------------
					if (!ModelRenderTable.InitTable(Interfaces::ModelRender()))
						return false;
					ModelRenderTable.HookIndex(TABLE::IVModelRender::DrawModelExecute, Hook_DrawModelExecute);

				

					//-----------------------------------------INITIALIZE----------------------------------------------------------------------------
					if (Client::Initialize(g_pDevice))

						return true;
				}
			}

			return false;
		}

		void Shutdown()
		{
			IDirect3DDevice9Table.UnHook();
			sound.unhook_all();
			ClientModeTable.UnHook();
			GameEventTable.UnHook();
			ModelRenderTable.UnHook();
			ClientTable.UnHook();
			SteamGameCoordinatorTable.UnHook();
		}
	}
}
