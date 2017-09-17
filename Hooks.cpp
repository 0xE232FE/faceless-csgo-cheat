#include "stdafx.h"
#include "Tools/Menu/Menu.h"
#include "Tools/Hacks/Misc.h"
#include "Tools/Utils/Playerlist.h"
#include "Tools/Hacks/Esp.h"
#include "Tools/Hacks/Antiaim.h"
#include "Tools/Hacks/Aimbot.h"
#include "Tools/Hacks/Legit.h"
#include "Tools/Hacks/CreateMoveETC.h"
#include "Tools/Menu/SettingsManager.h"
#include "Tools/Hacks/UI/UI.h"
#include "Tools/Hacks/KnifeBot.h"
#define DEV
#define RandomInt(min, max) (rand() % (max - min + 1) + min)
#define PI_2 PI/2
#define PI_4 PI/4
CHackManager Hacks;

VTHookManager VMTPanel;
VTHookManager VMTClient;
VTHookManager VMTEngine;
VTHookManager VMTModelRender;
VTHookManager VMTClientMode;
VTHookManager VMTGameEvent;
VTHookManager VMTSurface;

class Hitbox;

std::vector< int > AutoStraferConstants = {};
std::vector< const char* > smoke_materials =
{
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
};

typedef void(*Fucntion)(IGameEvent* event);

void ChatMsg(IGameEvent* event)
{
	GUI.ChatBox.AddMessage(Message(false, event->GetInt("userid"), (char*)event->GetString("text")));
}

void Death(IGameEvent* event)
{
	GUI.Feed.AddDeath(DeathInfo(event->GetInt("attacker"), event->GetInt("userid"), (char*)event->GetString("weapon"), event->GetInt("headshot")));
}

class CGameEventListener : public IGameEventListener2
{
private:
	std::string eventName;
	Fucntion Call;
	bool server;
public:
	CGameEventListener() : eventName(""), Call(nullptr), server(false)
	{
	}

	CGameEventListener(const std::string& gameEventName, const Fucntion Func, bool Server) : eventName(gameEventName), Call(Func), server(Server)
	{
		this->RegListener();
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		this->Call(event);
	}

	virtual int IndicateEventHandling(void)
	{
		return 0x2A;
	}
	 
	void RegListener(void)
	{
		static bool first = true;
		if (!first)
			return;
		if (Interfaces.g_GameEventMgr->AddListener(this, this->eventName.c_str(), server))
			Hacks.listeners.push_back(this);
	}
};

#define REG_EVENT_LISTENER(p, e, n, s) p = new CGameEventListener(n, e, s)
CGameEventListener* Deaths;
CGameEventListener* Msgs;

void Init()
{
	REG_EVENT_LISTENER(Deaths, &Death, "player_death", false);
	REG_EVENT_LISTENER(Msgs, &ChatMsg, "player_say", false);
}

void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	if (!strcmp("HudZoom", Interfaces.pPanel->GetName(vguiPanel)))
		return;
	Hacks.oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (strcmp("FocusOverlayPanel", Interfaces.pPanel->GetName(vguiPanel)))
	{
		return;
	}
	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{
		Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();

		if (Hacks.LocalPlayer)
		{
			
			
			Misc::DrawScope();
			Esp::DoEsp();
			GUI.Draw();
		}
	}
	Esp::Watermark();
	DrawMenu();
}
void bypass()
{
ConVar* cheats = Interfaces.g_ICVars->FindVar("sv_cheats");

	if (Settings.GetSetting(Tab_Misc, Misc_Bypass)) {
		if (cheats)
		{
			cheats->SetValue(1);
		}
	}
	else {
		if (cheats)
		{
			cheats->SetValue(0);
		}
	}
}


void FovChanger()
{
	if (Settings.GetSetting(Tab_Visuals, Visuals_EnableFOV)) {

		int viewmodelfovvalue = Settings.GetSetting(Tab_Visuals, Visuals_FovValue);

		ConVar* viewmodelfovcvar = Interfaces.g_ICVars->FindVar("viewmodel_fov");
		*(int*)((DWORD)&viewmodelfovcvar->fnChangeCallback + 0xC) = NULL;
		viewmodelfovcvar->SetValue(viewmodelfovvalue);

	}
}



void Kiduahook() {
	static bool steal = false;

	ConVar* nameConvar = Interfaces.g_ICVars->FindVar("name");
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = 0;

	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue("WANA HVH?");
		}
		else
		{
			nameConvar->SetValue("WANA HVH?");
		}
		steal = !steal;
	}
}
void awname() {
	static bool steal = false;

	ConVar* nameConvar = Interfaces.g_ICVars->FindVar("name");
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = 0;

	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue("™AIMWARE.net");
		}
		else
		{
			nameConvar->SetValue("™AIMWARE.net ");
		}
		steal = !steal;
	}
}
void iwebzname() {
	static bool steal = false;

	ConVar* nameConvar = Interfaces.g_ICVars->FindVar("name");
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = 0;

	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue("INTERWEBZ-");
		}
		else
		{
			nameConvar->SetValue("-INTERWEBZ");
		}
		steal = !steal;
	}
}
void puname() {
	static bool steal = false;

	ConVar* nameConvar = Interfaces.g_ICVars->FindVar("name");
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = 0;

	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue("\n PU ROCKS! \n");
		}
		else
		{
			nameConvar->SetValue("\n PU ROCKS! \n");
		}
		steal = !steal;
	}
}
void revenger() {
	static bool steal = false;

	ConVar* nameConvar = Interfaces.g_ICVars->FindVar("name");
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = 0;

	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue("\x01\x0B\x0D""R""\x0D""e""\x0D""v""\x0D""e""\x0D""n""\x0D""g""\x0D""e""\x0D""r""\x0D""""\x0D""""\x0D""""\x0D""""\x0D""""\x03");
		}
		else
		{
			nameConvar->SetValue("\x01\x0B\x03""R""\x03""e""\x03""v""\x03""e""\x03""n""\x03""g""\x03""e""\x03""r""\x03""""\x03""""\x03""""\x03""""\x03""""\x0D");
		}
		steal = !steal;
	}
}
void runname()
{
	switch (NemeSpam)
	{
	case 0: break;
	case 1: break;
	case 2: Kiduahook(); break;
	case 3: revenger(); break;
	case 4: awname(); break;
	case 5: puname(); break;
	case 6: iwebzname(); break;


		//case 9: NameSteal(); break;
	}
}


void New_CreateMove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	CInput::CVerifiedUserCmd* VerifiedCmd;
	AA.ShouldAA = false;
	CreateMoveETC::GetCmds(sequence_number, Hacks.CurrentCmd, VerifiedCmd);
	Aimbot.Target = Vector(0, 0, 0);





	Misc::ServerRankReveal();

	if (Hacks.CurrentCmd && VerifiedCmd && Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && Hacks.LocalPlayer)
	{
		plist.Update();
		MEMCHECK;
		Misc::ClantagChanger();
		
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
		Vector OrigAng = Hacks.CurrentCmd->viewangles;
		Misc::Normalize(OrigAng);
		
		
		//Misc::ThirdPerson();
		CreateMoveETC::BhopMovement(OrigAng);
		if (Hacks.LocalWeapon)
		{
			if (Hacks.LocalPlayer->isAlive())
			{
				if( Settings.GetMenuSetting( Tab_Misc, Misc_Aimstep ) )
				{
					for (int i = 0; i < Interfaces.pEntList->GetHighestEntityIndex(); i++ )
					{
						CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity( i );
						if( pEntity )
						{
							string s = "echo " + std::to_string( Hacks.CurrentCmd->tick_count ) + ":" + std::to_string( pEntity->pelvisangs() );
							Interfaces.pEngine->ClientCmd_Unrestricted( s.c_str(), 0 );
						}
					}
				}

				CreateMoveETC::LocalPrediction();
				Settings.weaponconfigs();
				Legitbot.Run();
				if (Settings.GetSetting(Tab_Misc, Misc_KnifeBot))
				KnifeBot::Run();
				if (Hacks.LocalWeapon->HasAmmo())
				{
					Aimbot.Aim(Hacks.CurrentCmd);
					if (Misc::Shooting() && LocalInfo.Choked < 13)
					{
						if (!Settings.GetSetting(Tab_Ragebot, Ragebot_GOTV) && !Hacks.LocalWeapon->IsMiscWeapon())
							Hacks.SendPacket = false;
						if (!Settings.GetSetting(Tab_Ragebot, Ragebot_SilentAim) && Settings.GetSetting(Tab_Ragebot, Ragebot_AimbotEnabled))
							Interfaces.pEngine->SetViewAngles(Hacks.CurrentCmd->viewangles);
						if (Settings.GetSetting(Tab_Ragebot, Ragebot_AimbotEnabled))
							Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;
					}
					else if (!Hacks.LocalWeapon->IsNade() && !Hacks.LocalWeapon->IsMiscWeapon())
						Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
					if (*Hacks.LocalWeapon->GetItemDefinitionIndex() == weapon_revolver && Settings.GetSetting(Tab_Ragebot, Ragebot_AimbotEnabled))
					{
						if (Hacks.LocalWeapon->GetPostponeFireReadyTime() - Misc::GetServerTime() > 0.05)
							Hacks.CurrentCmd->buttons |= IN_ATTACK;
					}
				}
				else
				{
					Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
					Hacks.CurrentCmd->buttons |= IN_RELOAD;
				}
				if (!Misc::Shooting())
					AA.Run();
			}
		}

		CreateMoveETC::CleanUp(OrigAng);
		LocalInfo.Choked = Hacks.SendPacket ? 0 : LocalInfo.Choked + 1;
		CreateMoveETC::VerifyCmd(VerifiedCmd);
		plist.UpdateSim();
	}
}

void __declspec(naked) __fastcall Hooked_Createmove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	Hacks.SendPacket = true;
	__asm
	{
		MOV Hacks.SendPacket, BL
		PUSH EBP
		MOV EBP, ESP
		SUB ESP, 8
		PUSHAD
		PUSH active
		PUSH input_sample_frametime
		PUSH sequence_number
		CALL Hacks.oCreateMove
	}
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	New_CreateMove(thisptr, _EAX, sequence_number, input_sample_frametime, active);
	__asm
	{
		POPAD
		MOV BL, Hacks.SendPacket
		MOV ESP, EBP
		POP EBP
		RETN 0x0C
	}
}

#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)

void __stdcall Hooked_OverrideView(CViewSetup* pSetup)
{
	static Vector newOrigin;
	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		if(Settings.GetSetting(Tab_Visuals, Visuals_fov) > 0)
			pSetup->fov += Settings.GetSetting(Tab_Visuals, Visuals_fov);

		if (!KEY_DOWN(VK_CAPITAL))
		{
			newOrigin = pSetup->origin;
		}
		CHECKMEM;
		//pSetup->angles = Aimbot.Angles;
	}
	Hacks.FOV = pSetup->fov;
	Hacks.FOV = pSetup->fovViewmodel;
	Hacks.oOverrideView(pSetup);
}



void __stdcall Hooked_PlaySound(const char* pSample)
{
	Hacks.oPlaySound(pSample);

	if (strstr(pSample, "weapons/hegrenade/beep.wav"))
	{
		if (!Settings.GetMenuSetting(Tab_Misc, Misc_AutoAccept))
			return;

		Interfaces.pEngine->ClientCmd_Unrestricted("echo SOUND_FILE_FOUND", 0);
		DWORD dwIsReady = (Utils.PFindPattern("client.dll", "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 8B 8E"));
		reinterpret_cast< void(*)() >(dwIsReady)();
	}
}



void AutoResolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		string s = "echo " + std::to_string( Hacks.CurrentCmd->tick_count ) + ":" + std::to_string( Player->entity->pelvisangs() );
		Interfaces.pEngine->ClientCmd_Unrestricted( s.c_str(), 0 );
	}

	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if(orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (flLowerBodyYaw != Player->flLastPelvisAng)
		{
			if (Player->entity->GetVecVelocity().Length2D() == 0)
			{
				int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
				while (temp < 0)
					temp += 360;
				while (temp > 360)
					temp -= 360;
				Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
			}

			iLastUpdatedTick = 0;
			Player->flLastPelvisAng = flLowerBodyYaw;
			Player->flEyeAng = orginalview.y;
		}

		if (Player->entity->GetVecVelocity().Length2D() >= 1)
		{
			flResolve = flLowerBodyYaw;
		}
		else
		{
			flResolve = Player->flLastPelvisAng;
		}
		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}

//void Resolver() {
//	float curtime = Interfaces.pGlobalVars->curtime;
//
//	if (*Pitch == 180.f) *Pitch = 89.f;
//	else if (*Pitch > 180.f && *Pitch < 290.f) *Pitch = -89.f;
//	else if (*Pitch >= 89.f && *Pitch <= 180.f) *Pitch = 89.f;
//	else if (*Pitch == 0.f)
//		FixAngel1(pEnt, Pitch, 0);
//	static Vector angles = Vector(0, 0, 0);
//	static float difference = 0;
//
//	float PlayerIsMoving = abs(pEnt->GetVelocity().Length());
//	bool bLowerBodyUpdated = false;
//	bool IsUsingFakeAngles = false;
//	float oldlowerbodyyaw;
//	if (oldlowerbodyyaw != *FYaw)
//	{
//		bLowerBodyUpdated = true;
//	}
//	float bodyeyedelta = pEnt->GetEyeAnglesXY().y - *Yaw;
	//if (PlayerIsMoving || bLowerBodyUpdated)// || LastUpdatedNetVars->eyeangles.x != CurrentNetVars->eyeangles.x || LastUpdatedNetVars->eyeyaw != CurrentNetVars->eyeangles.y) 
	//{
	//	if (bLowerBodyUpdated || (PlayerIsMoving && bodyeyedelta >= 35.0f))
	//	{
	//		*Yaw = *FYaw;
	//		oldlowerbodyyaw = *Yaw;
	//	}
//
//		IsUsingFakeAngles = false;
//	}
//	else
//	{
//		if (bodyeyedelta > 35.0f)
//		{
//			*Yaw = oldlowerbodyyaw;
//			IsUsingFakeAngles = true;
//		}
//		else
//		{
//			IsUsingFakeAngles = false;
//		}
//	}
//	if (IsUsingFakeAngles)
//	{
//		int com = GetEstimatedServerTickCount(90);
//
//		if (com % 2)
//		{
//			*Yaw += 90;
//		}
//		else if (com % 3)
//			*Yaw -= 90;
//		else
//			*Yaw -= 0;
//	}
//
//
//}


void LBYResolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		string s = "echo " + std::to_string(Hacks.CurrentCmd->tick_count) + ":" + std::to_string(Player->entity->pelvisangs());
		Interfaces.pEngine->ClientCmd_Unrestricted(s.c_str(), 0);
	}

	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if (orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (Player->entity->GetVecVelocity().Length2D() == 0)
		{
			int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
		}

		if (Player->entity->GetVecVelocity().Length2D() >= 1)
		{
			flResolve = flLowerBodyYaw;
		}
		else
		{
			int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
		}
		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}

void ForceResolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		string s = "echo " + std::to_string(Hacks.CurrentCmd->tick_count) + ":" + std::to_string(Player->entity->pelvisangs());
		Interfaces.pEngine->ClientCmd_Unrestricted(s.c_str(), 0);
	}

	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if (orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (Player->entity->GetVecVelocity().Length2D() == 0)
		{
			int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
		}

		int value = rand() % 11;
		switch (value) {
		case 0:flResolve = flResolve; break;
		case 1:flResolve += 0; break;
		case 2:flResolve = flResolve + 180; break;
		case 3:flResolve += 15; break;
		case 4:flResolve = flResolve + 90; break;
		case 5:flResolve -= 15; break;
		case 6:flResolve = flResolve + 270; break;
		case 7:flResolve += 0; break;
		case 8:flResolve = flResolve + 180; break;
		case 9:flResolve -= 45; break;
		case 10:flResolve += 45; break;
		}
		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}

void RandResolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		string s = "echo " + std::to_string(Hacks.CurrentCmd->tick_count) + ":" + std::to_string(Player->entity->pelvisangs());
		Interfaces.pEngine->ClientCmd_Unrestricted(s.c_str(), 0);
	}

	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if (orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (Player->entity->GetVecVelocity().Length2D() == 0)
		{
			int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
		}

		int value = rand() % 3 + 0;
		switch (value)
		{
		case 0:
		{
			flResolve = (rand() % 180);
			break;
		}
		case 1:
		{
			flResolve = (rand() % 360);
			break;
		}
		case 2:
		{
			flResolve = 0;
			break;
		}
		}
		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}


void LBYInverseResolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		string s = "echo " + std::to_string(Hacks.CurrentCmd->tick_count) + ":" + std::to_string(Player->entity->pelvisangs());
		Interfaces.pEngine->ClientCmd_Unrestricted(s.c_str(), 0);
	}

	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if (orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		static float TimedYaw;

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (Player->entity->GetVecVelocity().Length2D() == 0)
		{
			int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
		}


		if (Player->entity->GetVecVelocity().Length2D() >= 1)
		{
			flResolve = flLowerBodyYaw + 180;
		}

		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}

void Smart1Resolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		string s = "echo " + std::to_string(Hacks.CurrentCmd->tick_count) + ":" + std::to_string(Player->entity->pelvisangs());
		Interfaces.pEngine->ClientCmd_Unrestricted(s.c_str(), 0);
	}

	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if (orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		static float TimedYaw;

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (flLowerBodyYaw != Player->flLastPelvisAng)
		{
			if (Player->entity->GetVecVelocity().Length2D() == 0)
			{
				int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
				while (temp < 0)
					temp += 360;
				while (temp > 360)
					temp -= 360;
				Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;

				TimedYaw = Player->entity->GetEyeAngles().y - Player->entity->pelvisangs();
				flResolve = abs(TimedYaw);
			}

			iLastUpdatedTick = 0;
			Player->flLastPelvisAng = flLowerBodyYaw;
			Player->flEyeAng = orginalview.y;
		}

		if (Player->entity->GetVecVelocity().Length2D() >= 1)
		{
			flResolve = flLowerBodyYaw;
		}
		else
		{
			int temp = static_cast<int>(floor(orginalview.y - flLowerBodyYaw));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			flResolve = Player->Backtrack[temp] + orginalview.y;

			TimedYaw = Player->entity->GetEyeAngles().y - Player->entity->pelvisangs();
			flResolve = abs(TimedYaw);
		}
		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}

void __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage)
{
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (Hacks.LocalPlayer)
	{
		LocalInfo.PunchAns = *Hacks.LocalPlayer->GetPunchAnglePtr();
		LocalInfo.Flags = Hacks.LocalPlayer->GetFlags();
	}

	ConVar* mat_postprocess_enable = Interfaces.g_ICVars->FindVar("mat_postprocess_enable");
	mat_postprocess_enable->SetValue(0);

	Vector*pPunchAngle = nullptr, *pViewPunchAngle = nullptr, vPunchAngle, vViewPunchAngle;
	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		if (Hacks.LocalPlayer)
		{
			Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
			if (curStage == FRAME_RENDER_START)
			{
				MEMCHECK;
				if (Settings.GetSetting(Tab_Visuals, Visuals_NoRecoil))
				{
					pPunchAngle = Hacks.LocalPlayer->GetPunchAnglePtr();
					pViewPunchAngle = Hacks.LocalPlayer->GetViewPunchAnglePtr();

					if (pPunchAngle && pViewPunchAngle)
					{
						vPunchAngle = *pPunchAngle;
						pPunchAngle->Init();
						vViewPunchAngle = *pViewPunchAngle;
						pViewPunchAngle->Init();
					}
				}
				for (auto matName : smoke_materials)
				{
					IMaterial* mat = Interfaces.pMaterialSystem->FindMaterial(matName, "Other textures");
					mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Settings.GetSetting(Tab_Visuals, Visuals_NoSmoke));
				}
			}
		}
		if (*reinterpret_cast<bool*>(reinterpret_cast<DWORD>(Interfaces.pInput) + 0xA5))
			*reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(Hacks.LocalPlayer) + 0x31C8) = Hacks.LastAngles;
	}

	Hacks.oFrameStageNotify(curStage);

	if (pPunchAngle && pViewPunchAngle)
	{
		*pPunchAngle = vPunchAngle;
		*pViewPunchAngle = vViewPunchAngle;
	}
	static auto spin = 0;
	if (Settings.GetMenuSetting(Tab_Misc, Misc_Aimstep))
	{
		std::array< float, 24 >* flPoseParameters = Hacks.LocalPlayer->GetPoseParameters();

		for (int i = 0; i < 24; i++)
		{
			Interfaces.pEngine->ClientCmd_Unrestricted(string("echo " + std::string("#" + std::to_string(i) + ": " + std::to_string(flPoseParameters->at(i) * 360.f) + "\n")).c_str(), 0);
		}
		Interfaces.pEngine->ClientCmd_Unrestricted(string("echo " + std::string("EYE_YAW: " + std::to_string(Hacks.LocalPlayer->GetEyeAngles().y) + "\n")).c_str(), 0);
		Interfaces.pEngine->ClientCmd_Unrestricted(string("echo " + std::string("LB_YAW: " + std::to_string(Hacks.LocalPlayer->pelvisangs()) + "\n")).c_str(), 0);

		Settings.SetSetting(Tab_Misc, Misc_Aimstep, false);
	}

	if (Settings.GetSetting(Tab_Ragebot, Ragebot_Resolver) == 3)
	{
		LBYResolver;
	}

	if (Settings.GetSetting(Tab_Ragebot, Ragebot_Resolver) == 4)
	{
		ForceResolver;
	}


	if (Settings.GetSetting(Tab_Ragebot, Ragebot_Resolver) == 5)
	{
		RandResolver;
	}

	if (Settings.GetSetting(Tab_Ragebot, Ragebot_Resolver) == 6)
	{
		LBYInverseResolver;
	}

	if (Settings.GetSetting(Tab_Ragebot, Ragebot_Resolver) == 7)
	{
		Smart1Resolver;
	}
	if (Settings.GetSetting(Tab_Ragebot, Ragebot_Resolver) == 2)
	{
		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
			{
				for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
				{
					auto pEntity = static_cast<CBaseEntity*>(Interfaces.pEntList->GetClientEntity(i));
					if (pEntity == nullptr)
						continue;
					if (pEntity == Hacks.LocalPlayer)
						continue;
					if (!Hacks.LocalPlayer->isAlive())
						continue;
					if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
						continue;
					if (!pEntity->isAlive())
						continue;
					if (!(pEntity->GetHealth() > 0))
						continue;
					if (pEntity->IsDormant())
						continue;
					player_info_t info;
					if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info)))
						continue;
					PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);
					Player->entity = pEntity;

					Vector* angs = Player->entity->GetEyeAnglesPointer();
					if (!Settings.GetSetting(Tab_Misc, Misc_AntiUntrusted))
					{
						if (angs->x > 90.0f && angs->x < 270.f)
						{
							if (angs->x > 180.f)
								angs->x = -89.f;
							else
								angs->x = 89.0f;
						}
					}
					AutoResolver(angs, Player);
				}
			}
		}
	}

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && curStage == FRAME_RENDER_START)
	{
		CBaseEntity *pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

		if (Hacks.LocalPlayer->isAlive())
		{
			Vector LastAngleAA;
			if (*(bool*)((DWORD)Interfaces.pInput + 0xA5))
				*(Vector*)((DWORD)pLocal + 0x31C8) = LastAngleAA;
		}

		if ((Settings.GetSetting(Tab_Visuals, Visuals_ThirdPerson)))
		{
			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && Hacks.LocalPlayer->isAlive())
			{
				ConVar* sv_cheats = Interfaces.g_ICVars->FindVar("sv_cheats");
				SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
				sv_cheats_spoofed->SetInt(1);
				Interfaces.pEngine->ClientCmd_Unrestricted("thirdperson", 0);

			}
			else
			{
				Interfaces.pEngine->ClientCmd_Unrestricted("firstperson", 0);
			}
		}
		else
		{
			Interfaces.pEngine->ClientCmd_Unrestricted("firstperson", 0);
		}

		if (pLocal->m_bIsScoped())
		{
			Interfaces.pEngine->ClientCmd_Unrestricted("firstperson", 0);
		}
	}
	if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
		{
			//Utilities::Log("APPLY SKIN APPLY SKIN");
			CBaseEntity *pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
			int iBayonet = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
			int iButterfly = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
			int iFlip = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
			int iGut = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
			int iKarambit = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
			int iM9Bayonet = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			int iHuntsman = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
			int iFalchion = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
			int iDagger = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
			int iBowie = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");

			int Skin = Settings.GetSetting(Tab_Misc, KnifeSkin);

			int iGunGame = Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_knife_gg.mdl");

			for (int i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++) // CHANGE
			{
				CBaseEntity *pEntity = Interfaces.pEntList->GetClientEntity(i);

				if (pEntity)
				{
					ULONG hOwnerEntity = *(PULONG)((DWORD)pEntity + 0x148);

					CBaseEntity* pOwner = Interfaces.pEntList->GetClientEntityFromHandle((HANDLE)hOwnerEntity);

					if (pOwner)
					{
						if (pOwner == pLocal)
						{
							std::string sWeapon = Interfaces.g_pModelInfo->GetModelName(pEntity->GetModel());

							if (sWeapon.find("models/weapons", 0) != std::string::npos) 
								continue;

							if (sWeapon.find("c4_planted", 0) != std::string::npos)
								continue;

							if (sWeapon.find("thrown", 0) != std::string::npos)
								continue;

							if (sWeapon.find("smokegrenade", 0) != std::string::npos)
								continue;


							if (sWeapon.find("flashbang", 0) != std::string::npos)
								continue;

							if (sWeapon.find("fraggrenade", 0) != std::string::npos)
								continue;

							if (sWeapon.find("molotov", 0) != std::string::npos)
								continue;

							if (sWeapon.find("decoy", 0) != std::string::npos)
								continue;

							if (sWeapon.find("incendiarygrenade", 0) != std::string::npos)
								continue;

							if (sWeapon.find("ied", 0) != std::string::npos)
								continue;

							if (sWeapon.find("w_eq_", 0) != std::string::npos)
								continue;

							if (Settings.GetSetting(Tab_Skinchanger, Glove))
							{
								CBaseEntity *pLocal = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

								static bool bUpdate = false;

								int* hMyWearables = pLocal->GetWearables();

								if (!hMyWearables)
									return;

								if (!Interfaces.pEntList->GetClientEntity(hMyWearables[0] & 0xFFF))
								{
									for (ClientClass *pClass = Interfaces.pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext)
									{
										if (pClass->m_ClassID != (int)CSGOClassID::CEconWearable)
											continue;

										int entry = (Interfaces.pEntList->GetHighestEntityIndex() + 1), serial = RandomInt(0x0, 0xFFF);
										pClass->m_pCreateFn(entry, serial);
										hMyWearables[0] = entry | (serial << 16); //crash

										bUpdate = true;
										break;
									}


									player_info_t LocalPlayerInfo;
									Interfaces.pEngine->GetPlayerInfo(Interfaces.pEngine->GetLocalPlayer(), &LocalPlayerInfo);
								}
								CBaseCombatWeapon* pWeapon_g = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);



								int Glove_model = Settings.GetSetting(Tab_Misc, GloveModel);
								int Glove_skin = Settings.GetSetting(Tab_Misc, GloveSkin);
								
								if (!pWeapon_g)
									return;

								if (bUpdate) {
									if (Glove_model == 1)
									{

										*pWeapon_g->GetItemDefinitionIndex() = 5027;
										*pWeapon_g->GetItemIDHigh() = -1;

										((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
										pWeapon_g->PreDataUpdate(0);

										if (Glove_skin != 1 && Glove_skin != 2 && Glove_skin != 3)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5027;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10006;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 1)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5027;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10006;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 2)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5027;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10007;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 3)
										{
											*pWeapon_g->GetItemDefinitionIndex() = 5027;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10008;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}

									}
									if (Glove_model == 2)
									{

										*pWeapon_g->GetItemDefinitionIndex() = 5030;
										*pWeapon_g->GetItemIDHigh() = -1;
										((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
										pWeapon_g->PreDataUpdate(0);

										if (Glove_skin != 4 && Glove_skin != 5 && Glove_skin != 6 && Glove_skin != 7)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5030;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10037;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 4)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5030;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10037;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}

										else if (Glove_skin == 5)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5030;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10038;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}

										else if (Glove_skin == 6)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5030;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10018;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}

										else if (Glove_skin == 7)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5030;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10019;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
									}
									if (Glove_model == 3)
									{

										*pWeapon_g->GetItemDefinitionIndex() = 5027;
										*pWeapon_g->GetItemIDHigh() = -1;
										((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
										pWeapon_g->PreDataUpdate(0);

										if (Glove_skin != 8 && Glove_skin != 9 && Glove_skin != 10)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5031;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10013;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 8)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5031;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10013;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 9)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5031;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10015;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 10)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5031;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10016;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
									}
									if (Glove_model == 4)
									{

										*pWeapon_g->GetItemDefinitionIndex() = 5034;
										*pWeapon_g->GetItemIDHigh() = -1;
										((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
										pWeapon_g->PreDataUpdate(0);
										if (Glove_skin != 11 && Glove_skin != 12 && Glove_skin != 13 && Glove_skin != 14)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5034;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10030;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 11)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5034;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10030;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 12)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5034;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10033;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 13)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5034;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10034;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 14)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5034;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10035;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
									}
									if (Glove_model == 5)
									{

										*pWeapon_g->GetItemDefinitionIndex() = 5033;
										*pWeapon_g->GetItemIDHigh() = -1;
										((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
										pWeapon_g->PreDataUpdate(0);
										if (Glove_skin != 15 && Glove_skin != 16 && Glove_skin != 17 && Glove_skin != 18)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5033;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10024;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 15)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5033;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10026;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 16)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5033;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10027;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 17)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5033;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10028;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 18)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5033;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10024;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
									}
									if (Glove_model == 6)
									{

										*pWeapon_g->GetItemDefinitionIndex() = 5032;
										*pWeapon_g->GetItemIDHigh() = -1;
										((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
										pWeapon_g->PreDataUpdate(0);
										if (Glove_skin != 19 && Glove_skin != 20 && Glove_skin != 21 && Glove_skin != 22)
										{

											*pWeapon_g->GetItemDefinitionIndex() = 5032;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10009;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 19)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5032;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10009;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 20)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5032;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10010;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 21)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5032;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10021;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
										else if (Glove_skin == 22)
										{


											*pWeapon_g->GetItemDefinitionIndex() = 5032;
											*pWeapon_g->GetItemIDHigh() = -1;
											*pWeapon_g->GetFallbackPaintKit() = 10036;
											((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
											pWeapon_g->PreDataUpdate(0);
										}
									}
								}
									/*	*pWeapon_g->ModelIndex() = sporty; // m_nModelIndex
									*pWeapon_g->ViewModelIndex() = sporty;
									*pWeapon_g->WorldModelIndex() = sporty + 1;
									*pWeapon_g->GetItemDefinitionIndex() = 5030;
									*pWeapon_g->GetItemIDHigh() = -1;
									*pWeapon_g->GetFallbackPaintKit() = 10018;
									((CBaseEntity*)pWeapon_g)->SetModelIndexVirtual(Interfaces.g_pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
									
								pWeapon_g->PreDataUpdate(0);*/
									


									if (Settings.GetSetting(Tab_Skinchanger, SkinsEnable))
									{
										int AWPSKIN = Settings.GetSetting(Tab_Skinchanger, AWP);
										int SSGSKIN = Settings.GetSetting(Tab_Skinchanger, SSG08);
										int SCARSKIN = Settings.GetSetting(Tab_Skinchanger, SCAR20);
										int G3SG1SKIN = Settings.GetSetting(Tab_Skinchanger, G3SG1);
										int AK47SKIN = Settings.GetSetting(Tab_Skinchanger, AK47);
										int M4A4SKIN = Settings.GetSetting(Tab_Skinchanger, M4A1);
										int M4A1SSKIN = Settings.GetSetting(Tab_Skinchanger, M4A1S);
										int USPSKIN = Settings.GetSetting(Tab_Skinchanger, USP);
										int P2000SKIN = Settings.GetSetting(Tab_Skinchanger, P2000);
										int GlockSKIN = Settings.GetSetting(Tab_Skinchanger, Glock18c);
										int P250SKIN = Settings.GetSetting(Tab_Skinchanger, P250);
										int TEC9SKIN = Settings.GetSetting(Tab_Skinchanger, Tec9);
										int F7SKIN = Settings.GetSetting(Tab_Skinchanger, FiveSeven);
										int CZSKIN = Settings.GetSetting(Tab_Skinchanger, CZ75);
										int DEAGLESKIN = Settings.GetSetting(Tab_Skinchanger, Deagle);
										int ELITESKIN = Settings.GetSetting(Tab_Skinchanger, DUALB);
										int FAMASSKIN = Settings.GetSetting(Tab_Skinchanger, FAMAS);
										int GALILSKIN = Settings.GetSetting(Tab_Skinchanger, Galil);
										int MAC10SKIN = Settings.GetSetting(Tab_Skinchanger, MAC10);
										int MP9SKIN = Settings.GetSetting(Tab_Skinchanger, MP9);
										int MP7SKIN = Settings.GetSetting(Tab_Skinchanger, MP7);
										int P90SKIN = Settings.GetSetting(Tab_Skinchanger, P90);
										int UMPSKIN = Settings.GetSetting(Tab_Skinchanger, UMP45);
										int BIZONSKIN = Settings.GetSetting(Tab_Skinchanger, BIZON);
										int AUGSKIN = Settings.GetSetting(Tab_Skinchanger, AUG);
										int SG556SKIN = Settings.GetSetting(Tab_Skinchanger, SG553);
										CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pEntity;
										int weapon = *pWeapon->GetItemDefinitionIndex();

										if (Settings.GetSetting(Tab_Skinchanger, Stattrak))
										{
											float StatVal = Settings.GetSettingLegit(Tab_Skinchanger, StattrakVal);
											*pWeapon->GetFallbackStatTrak() = StatVal;
										}
										

										switch (weapon)
										{
											





										case 39:
										{
											switch (SG556SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 101;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 101;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 28;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 22;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 27;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 39;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 98;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 136;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 410;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 169;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 186;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 243;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 247;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 287;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 298;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 363;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 378;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 487;
												break;
											}
										}
										break;

										case 8:
										{
											switch (AUGSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 73;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 73;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 10;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 9;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 28;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 167;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 110;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 33;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 100;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 46;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 47;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 280;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 305;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 442;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 444;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 455;
												break;
											}

										}
										break;
										case 26:
										{
											switch (BIZONSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 13;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 13;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 164;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 25;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 27;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 70;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 148;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 149;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 159;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 235;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 171;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 203;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 224;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 236;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 267;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 306;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 323;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 349;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 376;
												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 457;
												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 459;
												break;
											}
										}
										break;
										case 19:
										{
											switch (P90SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 342;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 342;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 22;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 100;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 67;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 111;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 124;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 156;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 234;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 169;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 175;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 182;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 244;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 228;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 283;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 311;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 335;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 359;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 486;
												break;
											}
										}
										break;
										case 33:
										{
											switch (MP7SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 2;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 2;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 102;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 28;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 11;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 15;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 22;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 27;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 36;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 141;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 235;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 245;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 209;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 213;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 250;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 354;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 365;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 423;
												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 472;
												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 481;
												break;
											}
										}
										break;
										case 24:
										{
											switch (UMPSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 37;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 37;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 15;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 17;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 436;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 70;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 93;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 169;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 175;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 193;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 392;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 281;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 333;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 362;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 441;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 488;
												break;
											}
										}
										break;
										case 17:
										{
											switch (MAC10SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 101;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 101;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 3;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 32;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 17;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 38;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 433;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 98;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 157;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 188;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 337;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 246;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 284;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 310;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 333;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 343;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 372;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 402;
												break;
											}
										}
										break;

										case 34:
										{
											switch (MP9SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 482;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 482;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 27;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 33;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 100;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 39;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 61;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 148;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 141;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 199;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 329;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 262;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 366;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 368;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 386;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 403;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 448;
												break;

											}
										}
										break;
										case 13:
										{
											switch (GALILSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 22;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 83;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 428;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 76;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 119;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 235;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 398;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 192;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 308;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 216;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 237;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 241;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 264;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 297;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 379;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 460;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 478;
												break;
											}
										}
										break;
										case 10:
										{
											switch (FAMASSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 22;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 22;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 47;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 92;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 429;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 154;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 178;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 194;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 244;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 218;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 260;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 288;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 371;

												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 477;
												break;
											}
										}
										break;

										case 2:
										{
											switch (ELITESKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 28;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 28;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 36;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 43;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 46;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 47;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 153;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 190;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 248;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 249;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 220;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 396;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 261;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 276;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 307;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 330;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 447;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 450;
												break;
											}
										}
										break;
										case 30:
										{
											switch (TEC9SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 101;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 101;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 2;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 463;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 17;
										
											break;
										case 6:
											*pWeapon->GetFallbackPaintKit() = 36;
											break;
										case 7:
											*pWeapon->GetFallbackPaintKit() = 439;
											break;
										case 8:
											*pWeapon->GetFallbackPaintKit() = 159;
											break;
										case 9:
											*pWeapon->GetFallbackPaintKit() = 168;
											break;
										case 10:
											*pWeapon->GetFallbackPaintKit() = 235;
											break;
										case 11:
											*pWeapon->GetFallbackPaintKit() = 179;
											break;
										case 12:
											*pWeapon->GetFallbackPaintKit() = 248;
											break;
										case 13:
											*pWeapon->GetFallbackPaintKit() = 206;
											break;
										case 14:
											*pWeapon->GetFallbackPaintKit() = 216;
											break;
										case 15:
											*pWeapon->GetFallbackPaintKit() = 242;
											break;
										case 16:
											*pWeapon->GetFallbackPaintKit() = 272;
											break;
										case 17:
											*pWeapon->GetFallbackPaintKit() = 289;
											break;
										case 18:
											*pWeapon->GetFallbackPaintKit() = 303;
											break;
										case 19:
											*pWeapon->GetFallbackPaintKit() = 374;
											break;
										case 20:
											*pWeapon->GetFallbackPaintKit() = 459;
											break;
										}
										}
										break;
										case 36:
										{
											switch (P250SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 102;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 102;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 34;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 162;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 15;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 164;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 27;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 77;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 99;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 168;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 258;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 207;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 219;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 404;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 230;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 271;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 290;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 464;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 358;
												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 373;
												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 388;
												break;
											case 21:
												*pWeapon->GetFallbackPaintKit() = 426;
												break;
											case 22:
												*pWeapon->GetFallbackPaintKit() = 466;
												break;
											case 23:
												*pWeapon->GetFallbackPaintKit() = 467;
												break;
											}
										}
										break;
										case 1:
										{
											switch (DEAGLESKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 37;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 37;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 347;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 468;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 469;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 5;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 12;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 17;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 40;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 61;

												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 90;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 235;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 185;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 248;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 231;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 237;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 397;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 328;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 273;
												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 296;
												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 351;
												break;
											case 21:
												*pWeapon->GetFallbackPaintKit() = 425;
												break;
											case 22:
												*pWeapon->GetFallbackPaintKit() = 470;
												break;
											}

										}
										break;
										case 63:
										{
											switch (CZSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 435;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 435;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 12;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 254;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 218;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 268;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 269;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 270;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 297;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 298;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 315;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 322;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 325;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 334;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 350;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 366;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 453;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 476;
												break;
											}
										}
										break;
										case 32:
										{
											switch (P2000SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 104;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 104;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 32;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 21;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 25;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 36;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 385;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 38;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 71;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 95;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 184;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 211;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 338;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 246;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 275;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 327;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 346;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 357;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 389;
												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 442;
												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 443;
												break;
											}
										}
										break;
										case 60:
										{
											switch (M4A1SSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 59;

												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 59;

												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 33;

												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 60;

												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 430;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 77;

												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 235;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 254;

												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 189;

												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 301;

												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 217;

												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 257;

												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 321;

												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 326;

												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 360;

												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 383;

												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 440;

												break;
											}
										}
										break;
										case 16:
										{
											switch (M4A4SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 8;


												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 8;


												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 101;

												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 5;

												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 167;

												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 164;

												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 16;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 17;

												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 155;

												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 170;

												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 176;

												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 187;

												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 255;

												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 309;

												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 215;

												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 336;

												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 384;

												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 400;

												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 449;

												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 471;

												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 480;

												break;
											}
										}
										break;

										case 7:
										{
											switch (AK47SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 341;

												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 341;

												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 14;

												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 22;

												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 44;

												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 72;

												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 122;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 170;

												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 172;

												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 180;

												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 394;

												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 300;

												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 226;

												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 282;

												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 302;

												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 316;

												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 340;

												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 380;

												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 422;

												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 456;

												break;
											case 20:
												*pWeapon->GetFallbackPaintKit() = 474;

												break;

											}
										}
										break;
										case 11:
										{
											switch (G3SG1SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 8;


												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 8;


												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 6;

												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 27;

												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 46;

												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 72;

												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 74;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 147;

												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 235;

												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 170;

												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 195;

												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 229;

												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 294;

												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 465;

												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 464;

												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 382;

												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 438;

												break;
											}
										}
										break;
										case 38:
										{
											switch (SCARSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 12;


												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 12;


												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 165;

												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 100;

												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 46;

												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 70;

												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 116;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 157;

												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 196;

												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 232;

												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 391;

												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 298;

												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 312;

												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 406;

												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 453;

												break;
											}
										}
										break;
										case 3:
										{
											switch (F7SKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 3;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 3;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 27;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 44;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 46;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 78;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 141;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 151;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 254;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 248;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 210;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 223;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 252;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 265;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 274;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 464;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 352;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 377;
												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 387;
												break;
											case 19:
												*pWeapon->GetFallbackPaintKit() = 427;
												break;
											}
										}
										break;
										case 61:
										{
											switch (USPSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 59;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 59;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 25;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 60;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 235;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 183;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 339;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 217;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 221;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 236;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 277;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 290;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 313;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 318;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 332;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 364;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 454;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 489;
												break;
											}
										}
										break;
										case 40:
										{
											switch (SSGSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 59;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 59;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 26;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 38;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 60;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 96;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 99;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 157;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 200;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 222;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 233;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 253;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 304;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 319;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 361;
												break;
											}
										}
										break;
										case 4:
										{
											switch (GlockSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 2;
												break;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 2;
												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 3;
												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 38;
												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 40;
												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 48;
												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 337;
												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 99;
												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 159;
												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 399;
												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 208;
												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 230;
												break;
											case 12:
												*pWeapon->GetFallbackPaintKit() = 278;
												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 293;
												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 353;
												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 367;
												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 381;
												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 479;

												break;
											}
										}
										break;
										case 9: // AWP
										{
											switch (AWPSKIN)
											{
											case 0:
												*pWeapon->GetFallbackPaintKit() = 174;
											case 1:
												*pWeapon->GetFallbackPaintKit() = 174;

												break;
											case 2:
												*pWeapon->GetFallbackPaintKit() = 344;

												break;
											case 3:
												*pWeapon->GetFallbackPaintKit() = 5;

												break;
											case 4:
												*pWeapon->GetFallbackPaintKit() = 84;

												break;
											case 5:
												*pWeapon->GetFallbackPaintKit() = 30;

												break;
											case 6:
												*pWeapon->GetFallbackPaintKit() = 51;

												break;
											case 7:
												*pWeapon->GetFallbackPaintKit() = 72;

												break;
											case 8:
												*pWeapon->GetFallbackPaintKit() = 181;

												break;
											case 9:
												*pWeapon->GetFallbackPaintKit() = 259;


												break;
											case 10:
												*pWeapon->GetFallbackPaintKit() = 395;


												break;
											case 11:
												*pWeapon->GetFallbackPaintKit() = 212;


												break;

											case 12:
												*pWeapon->GetFallbackPaintKit() = 227;


												break;
											case 13:
												*pWeapon->GetFallbackPaintKit() = 251;


												break;
											case 14:
												*pWeapon->GetFallbackPaintKit() = 279;


												break;
											case 15:
												*pWeapon->GetFallbackPaintKit() = 424;


												break;
											case 16:
												*pWeapon->GetFallbackPaintKit() = 446;


												break;
											case 17:
												*pWeapon->GetFallbackPaintKit() = 451;


												break;
											case 18:
												*pWeapon->GetFallbackPaintKit() = 475;


												break;
											}
										}
										break;

										
										}




										*pWeapon->GetItemIDHigh() = -1;
									}


								}

							}


						}
					}
				}
			}
		}
	}




	void InitKeyValues(KeyValues* keyValues, char* name)
	{
		static DWORD initKeyValueAddr = 0;

		if (!initKeyValueAddr)initKeyValueAddr = Utils.PFindPattern("client.dll", "68 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 FC EB 07 C7 45 ?? ?? ?? ?? ?? 8B 03 56*") + 7;

		static DWORD dwFunction = 0;

		if (!dwFunction) dwFunction = initKeyValueAddr + *reinterpret_cast<PDWORD_PTR>(initKeyValueAddr + 1) + 5;

		if (!dwFunction) {
			return;
		}
		__asm
		{
			push name
			mov ecx, keyValues
			call dwFunction
		}
	}

	void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
	{
		static  DWORD dwFunction = 0;

		if (!dwFunction) dwFunction = Utils.PFindPattern("client.dll", "E8 ? ? ? ? 84 C0 74 08 8B C6");

		if (!dwFunction) {
			return;
		}

		__asm
		{
			push pBuffer
			push resourceName
			mov ecx, keyValues
			call dwFunction
		}
	}

IMaterial* Create_Material(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}

bool Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{
	static IMaterial* Covered_Lit = Create_Material(true, true, false);
	static IMaterial* Visable_Lit = Create_Material(false, true, false);
	float ChamsRed = Settings.GetSettingLegit(Tab_Colors, ChamsRCT);
	float ChamsGreen = Settings.GetSettingLegit(Tab_Colors, ChamsGCT);
	float ChamsBlue = Settings.GetSettingLegit(Tab_Colors, ChamsBCT);
	float ChamsRedT = Settings.GetSettingLegit(Tab_Colors, ChamsRT);
	float ChamsGreenT = Settings.GetSettingLegit(Tab_Colors, ChamsGT);
	float ChamsBlueT = Settings.GetSettingLegit(Tab_Colors, ChamsBT);

	float ChamsRedIN = Settings.GetSettingLegit(Tab_Colors, ChamsRCTIN);
	float ChamsGreenIN = Settings.GetSettingLegit(Tab_Colors, ChamsGCTIN);
	float ChamsBlueIN = Settings.GetSettingLegit(Tab_Colors, ChamsBCTIN);
	float ChamsRedTIN = Settings.GetSettingLegit(Tab_Colors, ChamsRTIN);
	float ChamsGreenTIN = Settings.GetSettingLegit(Tab_Colors, ChamsGTIN);
	float ChamsBlueTIN = Settings.GetSettingLegit(Tab_Colors, ChamsBTIN);
	CBaseEntity* Model_Entity = Interfaces.pEntList->GetClientEntity(pInfo.entity_index);
	auto Model_Name = Interfaces.g_pModelInfo->GetModelName(const_cast< model_t* >(pInfo.pModel));
	if (Settings.GetSetting(Tab_Visuals, Visuals_Chams))
	{
		if (Model_Entity->IsPlayer())
		{
			if (Model_Entity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !Settings.GetSetting(Tab_Visuals, Visuals_ChamsTeam))
				return false;

			if (Model_Entity->GetTeam() == 2)
			{
				Covered_Lit->ColorModulate(ChamsRedTIN / 255.f, ChamsGreenTIN / 255.f, ChamsBlueTIN / 255.f); // t colour
				Visable_Lit->ColorModulate(ChamsRedT / 255.f, ChamsGreenT / 255.f, ChamsBlueT / 255.f); // t colour Visable
			}
			else
			{
				Covered_Lit->ColorModulate(ChamsRedIN / 255.f, ChamsGreenIN / 255.f, ChamsBlueIN / 255.f); // ct colour
				Visable_Lit->ColorModulate(ChamsRed / 255.f, ChamsGreen / 255.f, ChamsBlue / 255.f); // ct colour Visable
			}

			if (!Model_Entity->isAlive())
				return false;

			if (Model_Entity->HasGunGameImmunity())
				Covered_Lit->AlphaModulate(0.75f);
			else
				Covered_Lit->AlphaModulate(1.f);

			if (!Settings.GetSetting(Tab_Visuals, Visuals_ChamsXQZ))
			{
				Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
				Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			return true;
		}
		if (Model_Entity->IsWeapon() && Settings.GetSetting(Tab_Visuals, Visuals_ChamsGuns))
		{
			Covered_Lit->ColorModulate(0 / 255.f, 237 / 255.f, 255 / 255.f);
			Visable_Lit->ColorModulate(0 / 255.f, 200 / 255.f, 255 / 255.f);
			Visable_Lit->AlphaModulate(1.0f);
			Covered_Lit->AlphaModulate(1.0f);

			if (!Settings.GetSetting(Tab_Visuals, Visuals_ChamsXQZ))
			{
				Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
				Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
			}

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			return true;
		}
	}
	if (Settings.GetSetting(Tab_Visuals, Visuals_NoFlash))
	{
		IMaterial* Flash = Interfaces.pMaterialSystem->FindMaterial("effects\\flashbang", "ClientEffect textures");
		IMaterial* FlashWhite = Interfaces.pMaterialSystem->FindMaterial("effects\\flashbang_white", "ClientEffect textures");
		Flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		FlashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		return false;
	}
	return false;
}


void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{
	if (!Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
		Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	Interfaces.g_pModelRender->ForcedMaterialOverride(nullptr, OVERRIDE_NORMAL);
}

void __stdcall Hooked_ClientCmdUnrestricted(const char* szCmdString, char flag)
{
	string str(szCmdString);
	std::string prefix;
	if (!str.compare(0, string("Clantag ").size(), "Clantag "))
	{
		str.replace(0, string("Clantag ").size(), "");
		prefix = string("\\n");
		std::size_t found = str.find(prefix);
		if (found != std::string::npos)
			str.replace(found, found + prefix.size(), "\n");
		Misc::SetClanTag(str.c_str(), "");
	}
	else if (!str.compare(0, string("ReleaseName").size(), "ReleaseName"))
	{
		Misc::setName("\n\xAD\xAD\xAD­­­");
	}
	else if (!str.compare(0, string("Name ").size(), "Name "))
	{
		str.replace(0, string("Name ").size(), "");
		prefix = string("\\n");
		std::size_t found = str.find(prefix);
		if (found != std::string::npos)
			str.replace(found, found + prefix.size(), "\n");
		Misc::setName(str.c_str());
	}
	/*
	else if (!str.compare(0, string("Save ").size(), "Save ")) {
	str.replace(0, string("Save ").size(), "");
	std::ofstream output(str);
	Menu::Menu.Save(output);
	}
	else if (!str.compare(0, string("Load ").size(), "Load ")) {
	str.replace(0, string("Load ").size(), "");
	std::ifstream input(str);
	if (input.good()) Menu::Menu.Load(input);
	}
	else if (!str.compare(0, string("Delete ").size(), "Delete ")) {
	str.replace(0, string("Delete ").size(), "");
	std::ofstream output(str);
	if (output.good()) {
	output.close();
	std::remove(str.c_str());
	}
	}
	*/
	else
		Hacks.oClientCmdUnresticted(szCmdString, flag);
}

LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//if (Menu::Menu.active) return true;

	return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);
}
