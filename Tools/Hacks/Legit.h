#pragma once
#include "stdafx.h"
#include "../Utils/Hitbox.h"
#include "Misc.h"
#include "../Utils/LocalInfo.h"

#include <vector>
using namespace std;

#include "../Utils/Playerlist.h"

#define keystate(i) GetAsyncKeyState(i & 0x8000)

class Legit
{
private:
	float deltaTime;
	float curAimTime;

	int besttarget = -1;
	int besthitbox = -1;

	bool EntityIsValid(int i,int hitbox)
	{
		auto pEntity = static_cast<CBaseEntity*> (Interfaces.pEntList->GetClientEntity(i));

		if (!pEntity)
			return false;
		if (pEntity == Hacks.LocalPlayer)
			return false;
		if (pEntity->GetHealth() <= 0)
			return false;
		if (pEntity->HasGunGameImmunity())
			return false;
		if (pEntity->IsDormant())
			return false;
		if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
			return false;

		return true;
	}
	
	void GetBestTarget()
	{
		float bestfov = 9999999.f;
		Vector vSrc = Hacks.LocalPlayer->GetEyePosition();
		for (int i = 0; i < Interfaces.pEntList->GetHighestEntityIndex(); i++)
		{
			if (!EntityIsValid(i,Settings.GetSettingLegit(Tab_Legitbot,Legitbot_hitbox) + 1))
				continue;
			
			auto pEntity = static_cast<CBaseEntity*> (Interfaces.pEntList->GetClientEntity(i));
			if (!pEntity)
				continue;
			
		
			if (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_multihitbox))
			{
				for (int j = 0; j <= 27; j++)
				{
					Vector vec = pEntity->GetBonePos(j);
				
					//if (!Misc::isVisible(pEntity, j))
					//	continue;
					float fov = Misc::GetFov(Hacks.CurrentCmd->viewangles + LocalInfo.PunchAns * (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_rcsforceX) / 50.f) / 5 * 4.6, Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), pEntity->GetBonePos(j)));
					if (fov > Settings.GetSettingLegit(Tab_Legitbot, Legitbot_fov))
						continue;
					
					if (fov < bestfov)
					{
						if (!Misc::pIsVisible(vSrc, vec, Hacks.LocalPlayer, pEntity, Settings.GetSettingLegit(Tab_Legitbot, Legitbot_SmokeCheck)))
							continue;
						if(Hacks.LocalPlayer->IsFlashed() > Settings.GetSettingLegit(Tab_Legitbot, Legitbot_FlashCheckDuration) && Settings.GetSettingLegit(Tab_Legitbot, Legitbot_FlashCheck))
							continue;
						if (!(pEntity->GetFlags() & FL_ONGROUND) && Settings.GetSettingLegit(Tab_Legitbot, Legitbot_JumpCheck))
							continue;
						bestfov = fov;
						besttarget = i;
						besthitbox = j;
					}
				}
			}
			else
			{
				
				Vector vec = pEntity->GetBonePos(Settings.GetSettingLegit(Tab_Legitbot, Legitbot_hitbox) + 1);
					if (!Misc::pIsVisible(vSrc, vec, Hacks.LocalPlayer, pEntity, Settings.GetSettingLegit(Tab_Legitbot, Legitbot_SmokeCheck)))
					continue;
					if (Hacks.LocalPlayer->IsFlashed() && Settings.GetSettingLegit(Tab_Legitbot, Legitbot_FlashCheck))
						continue;
					if (!(pEntity->GetFlags() & FL_ONGROUND) && Settings.GetSettingLegit(Tab_Legitbot, Legitbot_JumpCheck))
						continue;
				float fov = Misc::GetFov(Hacks.CurrentCmd->viewangles + LocalInfo.PunchAns, Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), pEntity->GetBonePos(Settings.GetSettingLegit(Tab_Legitbot, Legitbot_hitbox) + 1)));
				if (fov > Settings.GetSettingLegit(Tab_Legitbot, Legitbot_fov))
					continue;
				if (fov < bestfov)
				{
					bestfov = fov;
					besttarget = i;
					besthitbox = Settings.GetSettingLegit(Tab_Legitbot, Legitbot_hitbox) + 1;
				}
			}
			
		}
		if (bestfov == 9999999.f)
		{
			besttarget = -1;
			besthitbox = -1;
		}
		return;

	}

	void GoToTarget(int target, int hitbox)
	{
		auto pEntity = static_cast<CBaseEntity*> (Interfaces.pEntList->GetClientEntity(target));
		if (!pEntity)
			return;
		Vector dst = Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(),pEntity->GetBonePos(hitbox));
		Vector src = Hacks.CurrentCmd->viewangles;

		dst.x -= LocalInfo.PunchAns.x * (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_rcsforceX) / 50.f);
		dst.y -= LocalInfo.PunchAns.y * (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_rcsforceY) / 50.f);

		Vector delta = dst - src;

		delta.Normalize();

		if (!delta.IsZero())
		{

			float smoothX = Settings.GetSettingLegit(Tab_Legitbot, Legitbot_smoothX);
			float finalTimeX = delta.Length();
			float smoothY = Settings.GetSettingLegit(Tab_Legitbot, Legitbot_smoothY);
			float finalTimeY = delta.Length();

			if (smoothX != 0)
			{
				finalTimeX = delta.Length() / smoothX;
			}

			if (smoothY != 0)
			{
				finalTimeY = delta.Length() / smoothY;
			}

			float curAimTimeY = curAimTime;
			curAimTimeY += deltaTime;
			curAimTime += deltaTime;

			if (curAimTime > finalTimeX)
				curAimTime = finalTimeX;

			if (curAimTimeY > finalTimeY)
				curAimTimeY = finalTimeY;

			float percentX = curAimTime / finalTimeX;
			float percentY = curAimTimeY / finalTimeY;

			delta.x *= percentX;
			delta.y *= percentY;
			dst = src + delta;
		}

		Hacks.CurrentCmd->viewangles = dst.Normalize();
		Interfaces.pEngine->SetViewAngles(Hacks.CurrentCmd->viewangles);
	}
public:
	void Run()
	{
		double cur_time = clock();
		static double time = clock();
		int fire_delay = Settings.GetSettingLegit(Tab_Legitbot, Legitbot_Firedelay);
		if (fire_delay > 0)
		{
			if (Hacks.CurrentCmd->buttons & IN_ATTACK)
			{
				if (cur_time - time < fire_delay)
				{
					Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
				}
			}
			else
			{
				time = clock();
			}
		}

		curAimTime = 0.f;

		static float oldServerTime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
		float serverTime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
		deltaTime = serverTime - oldServerTime;
		oldServerTime = serverTime;

		if (Hacks.LocalWeapon->IsMiscWeapon())
			return;

		if (Settings.GetMenuSetting(Tab_Legitbot, Legitbot_hitbox) == 0)
		{
			Settings.SetSetting(Tab_Legitbot, Legitbot_hitbox, 1);
		}
		
		if ( (!Settings.GetSettingLegit(Tab_Legitbot, Legitbot_enable)) || (Settings.GetSettingLegit(Tab_Legitbot,Legitbot_Aimonkey) && !(GetAsyncKeyState(Settings.GetSettingLegit(Tab_Legitbot, Legitbot_Aimbotkey)) & 0x8000)))
			return;
		static int do_or_not = 0;
		if (do_or_not == 0)
		{
			GetBestTarget();
		}
		else
		{
			do_or_not++;
			if(do_or_not>15)
			{
				do_or_not = 0;
			}
		}

		
		
		
		if (besttarget == -1 || besthitbox == -1)
			return;
		if (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_Psilent))
		{
			if (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_PS))
			{
				if (GetAsyncKeyState(Settings.GetSetting(Tab_Legitbot, Legitbot_Pskey)))
				{
					DoPerfectSilent(besttarget, besthitbox);
				}
				else
				{
					GoToTarget(besttarget, besthitbox);
				}
			}
			else
			{
				DoPerfectSilent(besttarget, besthitbox);
			}
		}
		else
		GoToTarget(besttarget, besthitbox);

		

		
	}
	
	
	void DoPerfectSilent(int target, int hitbox)
	{
		auto pEntity = static_cast<CBaseEntity*> (Interfaces.pEntList->GetClientEntity(target));
		Vector AimbotAngle = Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), pEntity->GetBonePos(hitbox));
			float flServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
			float flNextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();
			Vector localangs;
			Interfaces.pEngine->GetViewAngles(localangs);
			bool BulletTime = true;

			if (flNextPrimaryAttack > flServerTime)
				BulletTime = false;

			if (Hacks.CurrentCmd->buttons & IN_ATTACK && BulletTime)
			{
				Hacks.SendPacket = false;
				Hacks.CurrentCmd->viewangles = AimbotAngle - LocalInfo.PunchAns * (Settings.GetSettingLegit(Tab_Legitbot, Legitbot_Prcsforce) / 50.f);
				

				//if (!Hacks.SendPacket)
				//{
				//	/*Hacks.CurrentCmd->viewangles = localangs;
				//	std::chrono::milliseconds(2);*/
				//	Hacks.SendPacket = true;
				//}
			}
			else
			{
				Hacks.CurrentCmd->viewangles = localangs;
				std::chrono::milliseconds(2);
				Hacks.SendPacket = true;
				Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
				
			}
		
		
	}
}Legitbot;


/*
class Legit {
	int GetBestPoint(Vector& aimspot, Hitbox box) {
		Vector Aimangles;
		Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), box.points[0], Aimangles);
		if (Misc::FovTo(Hacks.CurrentCmd->viewangles, Aimangles) > Menu::AimbotMenu::Selection::Fov.value) return false;
		float bestdamage = 0;
		for (int index = 0; index < 27; ++index) {
			Vector Aimangles;
			Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), box.points[index], Aimangles);
			if (Misc::FovTo(Hacks.CurrentCmd->viewangles, Aimangles) > Menu::AimbotMenu::Selection::Fov.value) continue;
			float damage = Autowall::GetDamage(box.points[index]);
			if (damage > bestdamage) {
				aimspot = box.points[index];
				bestdamage = damage;
			}
		}
		return bestdamage;
	}

	bool LegitAim(float fov, int hitbox) {
		if (!(Menu::LegitMenu::TriggerbotEnable.active || Hacks.CurrentCmd->buttons & IN_ATTACK && Misc::bullettime() && LocalInfo.Choked < 13)) return false;
		std::vector<Vector> possibleaimspots;
		std::vector<CBaseEntity*> possibletargets;
		for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++) {
			auto pEntity = static_cast<CBaseEntity*> (Interfaces.pEntList->GetClientEntity(i));
			if (pEntity == nullptr) continue;
			if (pEntity == Hacks.LocalPlayer) continue;
			if (!pEntity->isAlive()) continue;
			if (!(pEntity->GetHealth() > 0)) continue;
			if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !Menu::AimbotMenu::Selection::TeamEnable.active) continue;
			if (pEntity->IsDormant()) continue;
			//if(GetChockedPackets(pEntity) == 0) continue;
			if (pEntity->HasGunGameImmunity()) continue;
			player_info_t info;
			if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info))) continue;
			possibletargets.emplace_back(pEntity);
		}
		if ((int)possibletargets.size()) {
			for (auto pEntity : possibletargets) {
				Hitbox box;
				if (!box.GetHitbox(pEntity, hitbox)) continue;
				Vector Aimspot;
				if (GetBestPoint(Aimspot, box) != 0) {
					//FindActualHitbox(pEntity, Aimspot);

					plist.Update();
					PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);
					Player->entity = pEntity;
					possibleaimspots.emplace_back(Aimspot);
				}
			}
		}
		for (auto Spot : possibleaimspots) {
			Vector vecCurPos = Hacks.LocalPlayer->GetEyePosition();
			Vector angs;
			Misc::CalcAngle(vecCurPos, Spot, angs);
			Vector localangs;
			Interfaces.pEngine->GetViewAngles(localangs);
			if (Misc::FovTo(localangs, angs) <= fov) {
				if (!Menu::LegitMenu::SilentEnable.active) Interfaces.pEngine->SetViewAngles(angs);
				Hacks.CurrentCmd->viewangles = angs;
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
				Hacks.SendPacket = false;
				return true;
			}
		}
	}

	void GetSettings(float& fov, float& recoil, int& Hitbox) {
		if (Hacks.LocalWeapon->isRifle() || Hacks.LocalWeapon->isSmgW()) {
			fov = Menu::LegitMenu::Rifle::FOV.value;
			recoil = Menu::LegitMenu::Rifle::Recoil.value;
			Hitbox = Menu::LegitMenu::Rifle::Hitbox.activeid;
		}
		else if (Hacks.LocalWeapon->isSniper()) {
			fov = Menu::LegitMenu::Sniper::FOV.value;
			recoil = Menu::LegitMenu::Sniper::Recoil.value;
			Hitbox = Menu::LegitMenu::Sniper::Hitbox.activeid;
		}
		else if (Hacks.LocalWeapon->isPistol()) {
			fov = Menu::LegitMenu::Pistol::FOV.value;
			recoil = Menu::LegitMenu::Pistol::Recoil.value;
			Hitbox = Menu::LegitMenu::Pistol::Hitbox.activeid;
		}
	}

public:
	void Run() {
		if (!Menu::LegitMenu::LegitEnable.active) return;
		if (!LocalInfo.Flags & FL_ONGROUND && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND && Hacks.CurrentCmd->buttons & IN_JUMP && Menu::LegitMenu::Bhop.active) Hacks.CurrentCmd->buttons &= ~IN_JUMP;
		float fov = 0, recoil = 0;
		int hitbox = 0;
		GetSettings(fov, recoil, hitbox);
		LegitAim(fov, hitbox);
		Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (recoil * 2);
	}
} LegitBot;
*/
