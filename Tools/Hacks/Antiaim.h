#pragma once
//#include "stdafx.h"
#include "../Menu/Menu.h"
#include "Misc.h"
#include "Aimbot.h"
#include "../Utils/LocalInfo.h"
#include "../Menu/SettingsManager.h"

class AntiAim
{
public:
	float MyLowerBody = 0.0f;
	bool flip2 = false;
	float flip2angle = 0.0f;
	bool start = false;
	bool jitter = false;
	bool flip = false;
	bool ShouldAA = true;
	int current = 0;
	bool bSwitch = false;
private:
	bool CanFireNext(CBaseEntity* pEntity)
	{
		CBaseCombatWeapon* pWeapon = pEntity->GetActiveBaseCombatWeapon();
		float flServerTime = pEntity->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;

		float flNextShot = pWeapon->NextPrimaryAttack() - flServerTime;
		return flNextShot == 1;
	}

	void AtTargets(Vector& viewangles)
	{
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_AtTargets) != 1)
		{
			if (Aimbot.Target != Vector(0, 0, 0))
			{
				Misc::CalcAngle(Hacks.LocalPlayer->GetVecOrigin(), Aimbot.Target + Hacks.LocalPlayer->GetVecOrigin(), viewangles);
			}
			else if (Settings.GetSetting(Tab_Ragebot, AntiAim_AtTargets) == 2)
				ShouldAA = false;
		}
	}

	void DoFakeWalk()
	{
		if (GetAsyncKeyState(Settings.GetSetting(Tab_Ragebot, AntiAim_FakeWalkButton)))
		{
			static int iChoked = -1;
			iChoked++;

			if (iChoked < 3)
			{
				Hacks.SendPacket = false;
				Hacks.CurrentCmd->tick_count += 10;
				Hacks.CurrentCmd += 7 + Hacks.CurrentCmd->tick_count % 2 ? 0 : 1;
				Hacks.CurrentCmd->buttons |= Hacks.LocalPlayer->GetMoveType() == IN_BACK;
				Hacks.CurrentCmd->forwardmove = Hacks.CurrentCmd->sidemove = 0.f;
			}
			else
			{
				Hacks.SendPacket = true;
				iChoked = -1;
				Interfaces.pGlobalVars->frametime *= (Hacks.LocalPlayer->GetVecVelocity().Length2D()) / 1.f;
				Hacks.CurrentCmd->buttons |= Hacks.LocalPlayer->GetMoveType() == IN_FORWARD;
			}
		}
	}

	void Fakelag()
	{
		static int Ticks = 6;
		static Vector pos = Hacks.LocalPlayer->GetVecOrigin();
		int fakelag = Settings.GetSetting(Tab_Misc, Misc_FakeLag);
		switch (fakelag)
		{
		case 0:
		case 1:
			if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
			{
				if (Hacks.CurrentCmd->tick_count % 3 == 0)
					Hacks.SendPacket = false;
			}
			break;
		case 2:
			if (!(LocalInfo.Choked > 12))
				Hacks.SendPacket = false;
			break;
		case 3:
			if (!((pos - LocalInfo.LastPos).Length2DSqr() > 4096.f) && !(LocalInfo.Choked > 12))
				Hacks.SendPacket = false;
			break;
		case 4:
			if (LocalInfo.Choked > Ticks)
			{
				if (Ticks == 12)
					Ticks = 5;
				else
					Ticks = 12;
			}
			else
				Hacks.SendPacket = false;
			break;
		case 5:
			if (LocalInfo.Choked > Ticks)
			{
				Ticks += ((rand() % 4) + 2) * ((rand() % 2) + 2);
				while (Ticks > 12)
					Ticks -= 7;
			}
			else
				Hacks.SendPacket = false;
			break;
		}
		pos = Hacks.LocalPlayer->GetVecOrigin();
	}

	void SidewaysFake(int& Add)
	{
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
		{
			if (Hacks.SendPacket)
			{
				static bool t = false;
				Add = t ? 90 : 120;
				t = !t;
			}
		}
	}

	void BackFake(int& Add)
	{
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox) && Hacks.SendPacket)
		{
			static bool t = false;
			Add = t ? -165 : 165;
			t = !t;
		}
	}

	void jittertime()
	{
		static clock_t start1_t1 = clock();
		double timeSoFar1 = (double)(clock() - start1_t1) / CLOCKS_PER_SEC;
		if (timeSoFar1 < 0.05)
			return;
		jitter = !jitter;
		start1_t1 = clock();
	}

	void fliptime()
	{
		static clock_t start_t1 = clock();
		double timeSoFar = (double)(clock() - start_t1) / CLOCKS_PER_SEC;
		if (timeSoFar < 4.0)
			return;
		start_t1 = clock();
	}

	void Axis(Vector& View)
	{
		static float addj;
		float temp;
		static float trigger;
		int random;
		int maxJitter;
		int Add = 0;
		static int SpinYaw = 0;
		float JitterAng = 0;
		static float StoredAng = 0;
		jittertime();
		fliptime();
		//static int jitter = 0;
		static int last = 0;
		int help = {};
		int Fake = rand() % 3;
		static int Spin[2] = { 0, 0 };
		for (int& s : Spin)
			if (s > 180)
				s -= 360;
			else if (s < -180)
				s += 360;
		int yaw = Settings.GetSetting(Tab_Ragebot, AntiAim_Yaw);
		switch (yaw)

		{


			//Sideways Distortion
		case 2: // B1G Jitter 
			static bool v23;
			float fYawSwitch;
			float fYawSwitch_1;
			static bool yawSwitchJitterToggle;
			static bool flip;
			static bool flip2;


			static bool yFlip;
			yFlip = !yFlip;
			Hacks.SendPacket = yFlip;
			v23 = !v23;
			if (v23)
			{
				Hacks.SendPacket = true;
				if (!Settings.GetSetting(Tab_Ragebot, AntiAim_Dinamic))
				{
					if (yFlip)
					{
						Hacks.SendPacket = true;
						Add = 145.0;
						Hacks.SendPacket = false;
						Add = -80;// -80.000000 - 
						Hacks.SendPacket = true;
					}
					else
					{
						Hacks.SendPacket = true;
						Add = -145.0;
						Hacks.SendPacket = false;
						Add = -80;// -80.000000 - 
						Hacks.SendPacket = true;
					}
				}
				else if (Settings.GetSetting(Tab_Ragebot, AntiAim_Dinamic))
				{
					if (yFlip)
					{
						Hacks.SendPacket = true;
						Add += 145.0;
						Hacks.SendPacket = false;
						Add -= -80;// -80.000000 - 
						Hacks.SendPacket = true;
					}
					else
					{
						Hacks.SendPacket = true;
						Add += -145.0;
						Hacks.SendPacket = false;
						Add -= -80;// -80.000000 - 
						Hacks.SendPacket = true;
					}
				}
				Hacks.SendPacket = true;
			}
			if (!v23)
			{
				Hacks.SendPacket = false;
				if (!Settings.GetSetting(Tab_Ragebot, AntiAim_Dinamic))
				{
					if (yFlip)
					{
						Hacks.SendPacket = false;
						fYawSwitch = 100.0;
					}
					if (yFlip)
					{
						Hacks.SendPacket = false;
						fYawSwitch = -100.0;
					}
				}
				else if (Settings.GetSetting(Tab_Ragebot, AntiAim_Dinamic))
				{
					if (yFlip)
					{
						Hacks.SendPacket = false;
						fYawSwitch += 100.0;
					}
					if (yFlip)
					{
						Hacks.SendPacket = false;
						fYawSwitch -= -100.0;
					}
				}
				else
				{
					Hacks.SendPacket = false;
					if (!Settings.GetSetting(Tab_Ragebot, AntiAim_Dinamic))
						fYawSwitch = -100.0;
					else if (Settings.GetSetting(Tab_Ragebot, AntiAim_Dinamic))
						fYawSwitch -= -100.0;
					fYawSwitch_1 = Add + fYawSwitch;
					yawSwitchJitterToggle = yawSwitchJitterToggle == 0;
					Add = fYawSwitch_1;
					Hacks.SendPacket = true;
				}
			}
			break;
			//180 or back
		case 3: {

			static bool Switch;
			if (Hacks.LocalPlayer->pelvisangs() != MyLowerBody)
				Switch = !Switch;
			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1 && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
				Add = Switch ? 170 : -170;
			else
			{
				if (Hacks.SendPacket)
					Add = Switch ? -90 : 90;
				else
					Add = Switch ? 90 : -90;
				MyLowerBody = Hacks.LocalPlayer->pelvisangs();
			}
		}
				break;

		case 4: {

			static bool Switch;
			if (Hacks.LocalPlayer->pelvisangs() != MyLowerBody)
				Switch = !Switch;
			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1 && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
				Add = Switch ? 170 : -170;
			else
			{
				if (Hacks.SendPacket)
					Add = Switch ? -135 : 135;
				else
					Add = Switch ? 90 : -90;
				MyLowerBody = Hacks.LocalPlayer->pelvisangs();
			}
		}
				break;
		case 5: //Crooked Distortion

			if (Hacks.SendPacket)
			{
				if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
				{
					if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						Add = 90;
					}
					else
					{
						Add = -90;
					}
				}
				else
				{
					Add = 170;
				}
			}
			else
			{
				if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					Add = -45;
				}
				else
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
					{
						Add = -161;
					}
					else
					{
						Add = -20;
					}
				}
			}

			break;

			//Spin
		case 6: //Spin

			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
			{
				if (Hacks.SendPacket)
				{
					if (flip)
						SpinYaw += 35;
					else
						SpinYaw -= 35;
					View.y = SpinYaw;
				}
				else
				{
					float flRandom = rand() % 10 + 5.f;
					flRandom *= rand() % 2 == 0 ? -1.f : 1.f;
					switch (Hacks.CurrentCmd->tick_count % 4)
					{
					case 0:
						JitterAng = -170.f;
						break;
					case 1:
						JitterAng = 180.f;
						break;
					case 2:
						JitterAng = 170.f;
						break;
					case 3:
						JitterAng = 180.f;
						break;
					}
					Add = JitterAng + flRandom;
				}
			}
			else
			{
				if (Hacks.SendPacket)
				{
					if (flip)
						SpinYaw += 35;
					else
						SpinYaw -= 35;
					StoredAng = SpinYaw;
					View.y = SpinYaw;
				}
				else
				{
					float flFake = rand() % 32 + 19.f;
					if ((StoredAng) < 0)
						StoredAng += flFake;
					else if ((StoredAng) > 0)
						StoredAng -= flFake;
					Add = StoredAng;
				}
			}

			//Hacks.CurrentCmd->viewangles.y = SpinYaw;
			break;
			//180 Distortion
		case 7: //180 Distortion

			if (Settings.GetSetting(Tab_Misc, Misc_AntiUntrusted))
			{
				if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
				{
					if (Hacks.SendPacket)
					{
						if (jitter)
							Add = -120;
						else
							Add = 120;
					}
					else
					{
						float flRandom = rand() % 5 + 1.f;
						switch (Hacks.CurrentCmd->tick_count % 4)
						{
						case 0:
							Add = -170.f - flRandom;
							break;
						case 3:
						case 1:
							Add = 180.f;
							break;
						case 2:
							Add = 170.f + flRandom;
							break;
						}
					}
				}
				else
				{
					if (Hacks.SendPacket)
					{
						switch (Hacks.CurrentCmd->tick_count % 4)
						{
						case 0:
							Add = -125.f;
							break;
						case 1:
							Add = -179.f;
							break;
						case 2:
							Add = 125.f;
							break;
						case 3:
							Add = 179.f;
							break;
						case 4:
							Add = -125.f;
							break;
						}
					}
					else
					{
						float flRandom = rand() % 33 + 30.f;
						switch (Hacks.CurrentCmd->tick_count % 4)
						{
						case 0:
							Add = -125.f - flRandom;
							break;
						case 1:
							Add = -179.f - flRandom;
							break;
						case 2:
							Add = 125.f + flRandom;
							break;
						case 3:
							Add = 179.f - flRandom;
							break;
						case 4:
							Add = -125.f - flRandom;
							break;

						}
					}
				}
			}
			else
			{
				//Nospread
				if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
				{
					if (Hacks.SendPacket)
					{
						SpinYaw += 45;
						View.y = SpinYaw;
					}
					else
					{
						if (!LocalInfo.Flags & FL_ONGROUND)
						{
							float flRandom = rand() % 32 + 28.f;
							switch (Hacks.CurrentCmd->tick_count % 4)
							{
							case 0:
								Add = -125.f;
								break;
							case 1:
								Add = -179.f;
								break;
							case 2:
								Add = 125.f;
								break;
							case 3:
								Add = 179.f;
								break;
							case 4:
								Add = -125.f;
								break;
							}
						}
					}
				}
				else
				{
					return;
				}
			}



			break;

		case 8:
		{
			static int base = 0;
			if (!(rand() % 40))
				base = rand() % 360;
			if (!Hacks.SendPacket)
			{
				View.y = base;
				if (LocalInfo.Flags & FL_ONGROUND)
				{
					switch (Hacks.CurrentCmd->tick_count % 2)
					{
					case 0:
						Add = 45;
						break;
					case 1:
						Add = 180;
						break;
					}
				}
				else
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
					{
						switch (Hacks.CurrentCmd->tick_count % 2)
						{
						case 0:
							Add = 165;
							break;
						case 1:
							Add = -90;
							break;
						}
					}
					else
					{
						switch (Hacks.CurrentCmd->tick_count % 2)
						{
						case 0:
							Add = -165;
							break;
						case 1:
							Add = 90;
							break;
						}
					}
				}
			}
			else
			{
				View.y = base;
				Add = 0;
			}
		}
		break;
		}

		if (Settings.GetSetting(Tab_Ragebot, AntiAim_Yaw) == 9)
		{
			switch (Hacks.CurrentCmd->tick_count % 2)
			{
			case 0:
			{
				if (Hacks.SendPacket)
				{
					if (Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -15 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 15)
						Add = (Hacks.LocalPlayer->pelvisangs()) + 90.f;
					else
						Add = (Hacks.LocalPlayer->pelvisangs()) - 90.f;
				}
				else
				{
					if (Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -15 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 15)
						Add = (Hacks.LocalPlayer->pelvisangs()) - 90.f;
					else
						Add = (Hacks.LocalPlayer->pelvisangs()) + 90.f;
				}
				break;
			}

			case 1:
			{
				if (Hacks.SendPacket)
				{
					if (Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -15 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 15)
						Add = (Hacks.LocalPlayer->pelvisangs()) - 90.f;
					else
						Add = (Hacks.LocalPlayer->pelvisangs()) + 90.f;
				}
				else
				{
					if (Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -15 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 15)
						Add = (Hacks.LocalPlayer->pelvisangs()) + 90.f;
					else
						Add = (Hacks.LocalPlayer->pelvisangs()) - 90.f;
				}
				break;
			}
			}
		}
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_Yaw) == 11)//Shafle
		{
			int jitter_shuffle = 180;
			float jitter = rand() % (jitter_shuffle + 1);
			if (left)
			{
				if (Hacks.SendPacket)
				{
					View.y -= 90;
					if (flip2)
						View.y -= jitter;
					else
						View.y += jitter;
				}
				else
					View.y += 90;
			}
			else
			{
				if (Hacks.SendPacket)
				{
					if (flip2)
						View.y -= jitter;
					else
						View.y += jitter;
					View.y += 90;
				}
				else
					View.y -= 90;
			}
		}
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_Yaw) == 10)//LBY
		{
			float jitter = rand() % 360;
			float jitter1 = rand() % 15;

			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() == 0)
			{
				if (Hacks.SendPacket)
					flip2 ? Add = View.y -= 90 : View.y += 90;
				else
					Add = View.y = Hacks.LocalPlayer->pelvisangs();
			}
			else
			{
				if (Hacks.SendPacket)
				{
					if (flip2)
						View.y += jitter;
					else
						View.y -= jitter;
				}
				else
				{
					View.y -= jitter1;
				}
			}
		}
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_Yaw) == 8)
		{
			if (Hacks.SendPacket)
			{
				if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
				{
					if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						Add = 90;
					}
					else
					{
						Add = -90;
					}
				}
				else
				{
					Add = 170;
				}
			}
			else
			{
				if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					Add = -45;
				}
				else
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
					{
						Add = -161;
					}
					else
					{
						Add = -20;
					}
				}
			}
		}

		Hacks.CurrentCmd->viewangles.y = View.y + Add;
		int pitch = Settings.GetSetting(Tab_Ragebot, AntiAim_Pitch);
		switch (pitch)
		{
		case 2:
			Hacks.CurrentCmd->viewangles.x = 89;
			break;
		case 3:
			Hacks.CurrentCmd->viewangles.x = 272.911758f;
			if (!Hacks.SendPacket)
				Hacks.CurrentCmd->viewangles.x = 89;
			break;
		case 4:
			Hacks.CurrentCmd->viewangles.x = 89;
			if (Hacks.LocalWeapon->isSniper())
				Hacks.CurrentCmd->viewangles.x = 85;
			else if (Hacks.LocalWeapon->isRifle() || Hacks.LocalWeapon->isSmgW())
				Hacks.CurrentCmd->viewangles.x = 80;
			else if (Hacks.LocalWeapon->isPistol())
				Hacks.CurrentCmd->viewangles.x = 89;
			else if (Hacks.LocalWeapon->isMachineW())
				Hacks.CurrentCmd->viewangles.x = 78.50;
			else if (Hacks.LocalWeapon->isShotgun())
				Hacks.CurrentCmd->viewangles.x = 75.00;
			break;
		case 5:
			Hacks.CurrentCmd->viewangles.x = 179.99;
			break;
		}
	}

public:
	void Run()
	{
		if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeWalk))
			DoFakeWalk();

		if (!Settings.GetSetting(Tab_Ragebot, AntiAim_Enabled))
			return;
		if (Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
			return;
		if (Hacks.CurrentCmd->buttons & IN_USE)
			return;
		ShouldAA = true;
		Fakelag();
		Vector View = Hacks.CurrentCmd->viewangles;
		AtTargets(View);
		if (ShouldAA)
			Axis(View);
	}
} AA;
