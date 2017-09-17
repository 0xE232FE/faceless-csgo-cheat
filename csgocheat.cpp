#include "stdafx.h"
#include "Tools/Hacks/Misc.h"

extern void savesets();

extern std::string settingstostring();

bool Unhook_Cheat = false;

auto ExitCheat() -> bool;

void Unhook()
{
	Unhook_Cheat = true;
}
void ResetMenuStyle()
{
	Settings.SetSetting(Tab_Colors, MenuStyleR, 70);
	Settings.SetSetting(Tab_Colors, MenuStyleG, 20);
	Settings.SetSetting(Tab_Colors, MenuStyleB, 140);
	
}
void SaveSettings()
{
	settingstostring();
}

void LoadSettings()
{
	savesets();
}

bool ExitCheat()
{
	if( !Unhook_Cheat )
		return false;

	Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "UNLOADED", 0 );

	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_mouseenable 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "crosshair 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "firstperson", 0 );
	Sleep( 100 );

	if( Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() )
	{
		Misc::SetClanTag( "", Hacks.LocalPlayer->GetName().c_str() );
		Sleep( 100 );
	}

	Hacks.UnHook();
	Sleep( 200 );

	SetWindowLongPtr( INIT::Window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( INIT::OldWindow ) );
	Sleep( 200 );

	FreeLibraryAndExitThread( INIT::Dll, 0 );
}

DWORD WINAPI CheatMain( LPVOID lpThreadParameter )
{
	Interfaces.InitialiseSDK();

	CNetvarManager::Instance()->CreateDatabase();
	Hacks.Hook();
	auto u = Interfaces.pEngine->GetEngineBuildNumber();
	{
		Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
		Interfaces.pEngine->ClientCmd_Unrestricted( "...", 0 );
		Interfaces.pEngine->ClientCmd_Unrestricted("..", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted(".", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("Started", 0);
		while( !Unhook_Cheat )
		{
			Misc::ServerRankReveal();
			Sleep( 15 );
		}

		ExitCheat();
	}
	return 0;
}
