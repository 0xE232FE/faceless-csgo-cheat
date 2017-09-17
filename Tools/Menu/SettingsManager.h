#pragma once
#include "../../stdafx.h"

//Don't change the location of max value, always at the end.
//And also add new vars to bottom of lists or it will cause problems in cfgs.
//Skeltal is the cutest
enum MenuTabs
{
	Tab_Legitbot1 = 0,
	Tab_Legitbot,
	Tab_Ragebot,
	Tab_Visuals,
	Tab_Misc,
	Tab_Colors,
	Tab_Skinchanger,
	Tab_Plist,
	Tab_Config,
	MAXVALUEMENU,
	
	
};

enum Config
{
	Config_save,
	Config_load,
	Config_type,
};

enum RagebotTab
{
	Ragebot_AimbotEnabled,
	Ragebot_Selection,
	Ragebot_Hitbox,
	Ragebot_Multipoint,
	AntiAim_Dinamic,

	Ragebot_PS,
	Ragebot_Multibox,
	Ragebot_Velocity,
	Ragebot_AutoShoot,
	Ragebot_Autoscope,
	Ragebot_SilentAim,
	Ragebot_Hitchance,
	Ragebot_MinDamage,
	Ragebot_AcceptKill,
	AntiAim_Enabled,
	AntiAim_Pitch,
	AntiAim_Yaw,
	AntiAim_FakeYaw,
	AntiAim_AtTargets,
	AntiAim_FakeHitbox,
	AntiAim_EdgeDetection,
	Ragebot_Resolver,
	AntiAim_FakeWalk,
	AntiAim_FakeWalkButton,
	Ragebot_Accuracy,
	Ragebot_PreferBodyAim,
	Ragebot_PositionAdjustment,
	Ragebot_GOTV,
	Ragebot_MultipointType,
	Rage_Switch,
	MAXVALUERAGE
};

enum Visualstab
{
	Visuals_Enable,
	Visuals_Glow,
	Visuals_BoxEnabled,
	Visuals_BoxType,
	Visuals_Dlight,
	Visuals_EspTeam,
	Visuals_HealthBar,
	Visuals_ArmorBar,
	Visuals_Name,
	Visuals_Flashed,
	Visuals_Weapons,
	Visuals_Weaponsic,
	Visuals_AimLines,
	Visuals_Skeltal,
	Visuals_EngineRadar,
	Visuals_Hostage,
	Visuals_DroppedWeapons,
	Visuals_NoRecoil,
	Visuals_NoFlash,
	Visuals_NoSmoke,
	Visuals_ThirdPerson,
	Visual_TPRange,
	Visuals_NoScope,
	Visuals_Chams,
	Visuals_ChamsXQZ,
	Visuals_ChamsTeam,
	Visuals_ChamsGuns,
	Visuals_XQZ,
	Visuals_Crosshair,
	Visuals_CrosshairDynamic,
	Visuals_EnableFOV,
	Visuals_FovValue,
	Visuals_C4,
	Visuals_Flags,
	Visuals_MethyHands,
	Visuals_Dlights,
	Visuals_fov,
	Visuals_Night,
	Visuals_TP,
	Visuals_TP1,
	MAXVALUEVISUALS
};

enum MiscTab
{
	Visuals_SkyE,
	Visuals_Predaction,
	Visuals_Sky,
	Misc_WhichWeapon,
	Misc_AntiUntrusted,
	Misc_AutoJump,
	Misc_AutoStrafe,
	Misc_AutoStraferMode,
	Misc_ClanTagSpammer,
	EnableNameSpam,
	EnableChatSpam,
	Misc_ClanTagSelection,
	Misc_ClanTagAnimate,
	ChatSpamMessage,
	NemeSpam,
	Misc_EnableFOV,
	Misc_FovValue,
	Misc_Bypass,
	Misc_AutoAccept,
	Misc_KnifeBot,
	Misc_DrawMonitor,
	Misc_DrawMonitor1,
	Misc_FakeLag,
	Misc_Aimstep,
	Misc_ZStrafe,
	Misc_ZStrafeKey,
	Misc_CircleStrafe,
	Misc_CircleStrafeKey,
	Misc_X,
	Misc_Y,
	Misc_S,
	Misc_UI,
	
	MAXVALUEMISC
};

enum Skins
{
	SkinsEnable,
	AK47,
	AWP,
	SSG08,
	SCAR20,
	G3SG1,
	M4A1,
	M4A1S,
	USP,
	P2000,
	MAC10,
	MP9,
	UMP45,
	P90,
	BIZON,
	AUG,
	SG553,
	MP7,
	P250,
	Glock18c,
	Stattrak,
	StattrakVal,
	DUALB,
	FAMAS,
	Galil,
	Deagle,
	FiveSeven,
	Tec9,
	CZ75,
	KnifeSkin,
	Glove,
	SkinsGroup,

	GloveSkin,
	GloveSkin1,
	GloveSkin2,
	GloveSkin3,
	GloveSkin4,
	GloveSkin5,
	GloveModel,
	MAXVALUESKINS
};

enum LegitbotTab
{
	Legitbot_enable,
	Legitbot_Fov,
	Legitbot_Aimonkey,
	Legitbot_fov,
	Legitbot_fovtype,
	Legitbot_SmokeCheck,
	Legitbot_Psilent,
	Legitbot_smoothtype,
	Legitbot_smoothX,
	Legitbot_smoothY,
	Legitbot_multihitbox,
	Legitbot_hitbox,
	Legitbot_rcs,
	Legitbot_rcsforceX,
	Legitbot_rcsforceY,
	Legitbot_Aimbotkey,
	Legitbot_Smokecheck,
	Legitbot_Firedelay,
	Legitbot_Pskey,
	Legitbot_PS,
	Legitbot_PSfov,
	Legitbot_Prcsforce,
	Legitbot_FlashCheck,
	Legitbot_FlashCheckDuration,
	Legitbot_JumpCheck,
	MAXVALUELEGIT
};

enum colors
{
	TextR,
	TextG,
	TextB,
	ChamsR,
	ChamsG,
	ChamsB,
	ChamsRCT,
	ChamsGCT,
	ChamsBCT,
	ChamsRT,
	ChamsGT,
	ChamsBT,
	ChamsRCTIN,
	ChamsGCTIN,
	ChamsBCTIN,
	ChamsRTIN,
	ChamsGTIN,
	ChamsBTIN,
	MenuStyleR,
	MenuStyleG,
	MenuStyleB,
	Colors_chams_visible_r,
	Colors_chams_visible_g,
	Colors_chams_visible_b,
	Colors_chams_visible_a,
	Colors_chams_invisible_r,
	Colors_chams_invisible_g,
	Colors_chams_invisible_b,
	Colors_chams_invisible_a,
	Colors_controls_text_r,
	Colors_controls_text_g,
	Colors_controls_text_b,
	Colors_controls_text_a,
	Colors_controls_background_r,
	Colors_controls_background_g,
	Colors_controls_background_b,
	Colors_controls_background_a,
	Colors_background_r,
	Colors_background_g,
	Colors_background_b,
	Colors_background_a,
	Colors_outline_r,
	Colors_outline_g,
	Colors_outline_b,
	Colors_outline_a,
	Colors_sliders_r,
	Colors_sliders_g,
	Colors_sliders_b,
	Colors_sliders_a,
	Colors_sliders_back_r,
	Colors_sliders_back_g,
	Colors_sliders_back_b,
	Colors_sliders_back_a,
	Colors_menutitle_r,
	Colors_menutitle_g,
	Colors_menutitle_b,
	Colors_menutitle_a,
	Colors_menutab_r,
	Colors_menutab_g,
	Colors_menutab_b,
	Colors_menutab_a,
	MAXVALUECOLORS
};

enum weapongroups
{
	Group_Default = 0,
	Group_Rifle,
	Group_Pistol,
	Group_Shotgun,
	Group_SMG,
	Group_Heavy,
	Group_AWP,
	Group_Scout,
	Group_Othersnipers,
	MAXVALUEWEAPONGROUPS
};



class SettingsManger
{
public:
	bool weaponconfigs();

	static void SetSetting(int Tab, int Setting, double Value);

	static double GetSetting(int Tab, int Setting);

	static double GetSettingLegit(int Tab, int Setting);

	double GetPlayer(int index, int Tab, int Setting);

	static double GetMenuSetting(int Tab, int Setting);
};

extern SettingsManger Settings;
