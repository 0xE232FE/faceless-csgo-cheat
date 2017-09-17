#include "../../stdafx.h"
#include "SettingsManager.h"
#include "Menu.h"

int MenuAlpha;
int TextRed;
int TextGreen;
int TextBlue;
int TextAlpha;
int BackgroundRed;
int BackgroundGreen;
int BackgroundBlue;
int BackgroundAlpha;
int OutlineRed;
int OutlineGreen;
int OutlineBlue;
int OutlineAlpha;

float GlobalMenuAlpha = 0.f;
float W = 0.f;
float H = 0.f;
float S = 0.f;

/* func buttons here */
void Unhook();

void SaveSettings();

void LoadSettings();

//void ResetSettings();
void ResetMenuStyle(); 
bool savesettings = false;
bool loadsettings = false;
bool resetsettings = false;

int phase1 = 0;
int phase2 = 30;
int phase3 = 60;
int phase4 = 90;

bool Clicked_This_Frame;
bool Holding_Mouse_1;
bool Dont_Click;
bool Holding_Menu;
bool Holding_M;
int Menu_Drag_X;
int Menu_Drag_Y;
int M_Drag_X;
int M_Drag_Y;
int Tab_Count = 0;

bool keys[256];
bool oldKeys[256];

bool GetKeyPress( unsigned int key )
{
	try
	{
		if( keys[ key ] == true && oldKeys[ key ] == false )
			return true;
		else
			return false;
	}
	catch( ... )
	{
	}
}

std::vector< char* > KeyStrings = { "  _  ", " M1 ", " M2 ", " BREAK ", " M ", " M4 ", " M5 ",
	"  _  ", " BCKSPC ", " TAB ", "  _  ", "  _  ", "  _  ", " ENTER ", "  _  ", "  _  ", " SHIFT ",
	" CTRL ", " ALT "," PAUSE "," CAPS ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	" ESC ", "  _  ", "  _  ", "  _  ", "  _  ", " SPACE "," PGUP ", " PGDOWN ", " END ", " HOME ", " LEFT ",
	" UP ", " RIGHT ", " DOWN ", "  _  ", " PRNT ", "  _  ", " PRTSCR ", " INS "," DEL ", "  _  ", " 0 ", " 1 ",
	" 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", " A ", " B ", " C ", " D ", " E ", " F ", " G ", " H ", " I ", " J ", " K ", " L ", " M ", " N ", " O ", " P ", " Q ", " R ", " S ", " T ", " U ",
	" V ", " W ", " X "," Y ", " Z ", " LFTWIN ", " RGHTWIN ", "  _  ", "  _  ", "  _  ", " NUM0 ", " NUM1 ",
	" NUM2 ", " NUM3 ", " NUM4 ", " NUM5 ", " NUM6 "," NUM7 ", " NUM8 ", " NUM9 ", " * ", " + ", " _ ", " - ", " . ", " / ", " F1 ", " F2 ", " F3 ",
	" F4 ", " F5 ", " F6 ", " F7 ", " F8 ", " F9 ", " F10 ", " F11 ", " F12 "," F13 ", " F14 ", " F15 ", " F16 ", " F17 ", " F18 ", " F19 ", " F20 ", " F21 ",
	" F22 ", " F23 ", " F24 ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ","  _  ", "  _  ", "  _  ",
	" NUMLCK ", " SCRLLLCK ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  ","  _  ", "  _  ", "  _  ", "  _  ", "  _  ", " LSHIFT ", " RSHIFT ", " LCTRL ",
	" RCTRL ", " LMENU ", " RMENU ", "  _  ","  _  ", "  _  ","  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  ", "  _  ", " NTRK ", " PTRK ", " STOP ", " PLAY ", "  _  ", "  _  ",
	"  _  ", "  _  ", "  _  ", "  _  ", ";", "+", ",", "-", ".", "/?", "~", "  _  ", "  _  ",
	"  _  ", "  _  ","  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ","  _  ",
	"  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  ", "  _  ","  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ", "  _  ",
	"  _  ", "  _  " };

void DrawMouse()
{


	POINT Mouse;
	POINT mp;
	GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x;
	Mouse.y = mp.y;
	static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 255, 255, 255, GlobalMenuAlpha };

	Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
	Interfaces.pSurface->DrawSetTexture(Texturer);
	Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
	/**/
	Vertex_t Verts[3];
	Verts[0].x = Mouse.x;
	Verts[0].y = Mouse.y;
	Verts[1].x = Mouse.x + 10;
	Verts[1].y = Mouse.y + 4;
	Verts[2].x = Mouse.x;
	Verts[2].y = Mouse.y + 10;
	Interfaces.pSurface->DrawTexturedPolygon(3, Verts);
}

void CMenu::Set_Current_Tab( int tab )
{
	Current_tab = tab;
}

int CMenu::GetCurret_Tab()
{
	return Current_tab;
}

void CMenu::Update_Frame()
{
	if( !Holding_Mouse_1 )
	{
		if( GetClicked() )
		{
			Holding_Menu = true;
		}
		else
		{
			Holding_Menu = false;
		}
		if (GetClickedM())
		{
			Holding_M = true;
		}
		else
		{
			Holding_M = false;
		}
	}

	if( Holding_Menu )
	{
		MenuPOS NewPOS;
		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		NewPOS.x = Mouse.x - Menu_Drag_X;
		NewPOS.y = Mouse.y - Menu_Drag_Y;
		this->pos = NewPOS;
	}
	if (Holding_M)
	{
		MenuPOS NewPOS;
		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		NewPOS.x = Mouse.x - M_Drag_X;
		NewPOS.y = Mouse.y - M_Drag_Y;
		this->Mpos = NewPOS;
		Holding_Menu = false;
	}
}

bool CMenu::GetClicked()
{
	if( !( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) )
	{
		return false;
	}

	POINT Mouse;
	POINT mp;
	GetCursorPos( &mp );
	ScreenToClient( GetForegroundWindow(), &mp );
	Mouse.x = mp.x;
	Mouse.y = mp.y;

	if (Mouse.x > this->pos.x  && Mouse.y > this->pos.y - 6 && Mouse.x < this->pos.x + 525 && Mouse.y < this->pos.y + 30)
	{
		if( !Holding_Mouse_1 )
		{
			Menu_Drag_X = Mouse.x - pos.x;
			Menu_Drag_Y = Mouse.y - pos.y;
		}
		return true;
	}
	else
	{
		return false;
	}
	
}
bool CMenu::GetClickedM()
{
	if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		return false;
	}

	POINT Mouse;
	POINT mp;
	GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x;
	Mouse.y = mp.y;

	
	if (Mouse.x > this->Mpos.x  && Mouse.y > this->Mpos.y && Mouse.x < this->Mpos.x + 200 && Mouse.y < this->Mpos.y + 30)
	{
		if (!Holding_Mouse_1)
		{
			M_Drag_X = Mouse.x - Mpos.x;
			M_Drag_Y = Mouse.y - Mpos.y;
		}
		return true;
	}
	else
	{
		return false;
	}
}
CMenu Menu;
class CButton;
class CButton1;
class CSlider;
class CDropbox;
class CKeybutton;
class CTab;
class CMenuBox;
class CSettingsDropBox;

class CButton1
{
private:
	MenuPOS pos;
	MenuPOS offset;
	int Tab;
	int Sub;

	int Setting;
	char* Name = "ERROR";

	bool Hovering()
	{
		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y - 2 && Mouse.x < this->pos.x + 12 && Mouse.y < this->pos.y - 2 + 12)
		{
			return true;
		}
		return false;
	}

	bool Clicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}

		if (Hovering())
		{
			return true;
		}
		return false;
	}

public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if (Menu.GetCurret_Tab() == Tab)
		{
			if (Clicked())
			{
				Dont_Click = true;
				Settings.SetSetting(Tab, Setting, !Settings.GetMenuSetting(Tab, Setting));
			}
		}
	}

	void Draw()
	{
		float MenuRedStyle = 0;
		float MenuGreenStyle = 149;
		float MenuBlueStyle = 255;
		if (Menu.GetCurret_Tab() == Tab)
		{

			if (Settings.GetMenuSetting(this->Tab, this->Setting))
			{
			}
			//Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
			//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);
			Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 3, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);
		}
	}

	void Init(int Tab, int Setting, bool defult, int x, int y, char* name, int sub)
	{
		this->Tab = Tab;
		this->Setting = Setting;
		this->offset.y = y;
		this->offset.x = x;
		this->Name = name;
		this->Sub = sub;

		Settings.SetSetting(Tab, Setting, defult);
	}
};

class CButton
{
private:
	MenuPOS pos;
	MenuPOS offset;
	int Tab;
	int Sub;

	int Setting;
	char* Name = "ERROR";

	bool Hovering()
	{
		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;
		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y - 2 && Mouse.x < this->pos.x + 12 && Mouse.y < this->pos.y - 2 + 12 )
		{
			return true;
		}
		return false;
	}

	bool Clicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}

		if( Hovering() )
		{
			return true;
		}
		return false;
	}

public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if( Menu.GetCurret_Tab() == Tab )
		{
			if( Clicked() )
			{
				Dont_Click = true;
				Settings.SetSetting( Tab, Setting, !Settings.GetMenuSetting( Tab, Setting ) );
			}
		}
	}

	void Draw()
	{
		float MenuRedStyle = 0;
		float MenuGreenStyle = 149;
		float MenuBlueStyle = 255;
		if( Menu.GetCurret_Tab() == Tab )
		{
			Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y - 2 + 2, this->pos.x + 13, this->pos.y - 2 + 9);
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y - 2 + 1, this->pos.x + 11, this->pos.y - 2 + 11 );

			if( Settings.GetMenuSetting( this->Tab, this->Setting ) )
			{
				Interfaces.pSurface->DrawString(Hacks.Font_Controls, this->pos.x + 1, this->pos.y - 3,0, CColor(255, 255, 255, GlobalMenuAlpha), L"✔");
			}
			//Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
			//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);
			Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 4, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);
		}
	}

	void Init( int Tab, int Setting, bool defult, int x, int y, char* name, int sub )
	{
		this->Tab = Tab;
		this->Setting = Setting;
		this->offset.y = y;
		this->offset.x = x;
		this->Name = name;
		this->Sub = sub;

		Settings.SetSetting( Tab, Setting, defult );
	}
};


class CSlider
{
private:
	int Tab = 0;
	int Size = 0;
	int SubTab = 0;
	int Setting = 0;
	double Max = 100;
	double Min = 0;
	bool color_from_some_set = false;
	int cus_r, cus_g, cus_b, cus_a;
	bool custom_color = true;
	int r = 55, g = 5, b = 5, a = 255, r_back = 5, g_back = 55, b_back = 5, a_back = 255;
	MenuPOS pos;
	MenuPOS offset;
	char* Name = "ERROR";
	//char* SValue = "0";
	bool Is_Holding;

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			this->Is_Holding = false;
			return false;
		}
		if( Holding_Mouse_1 )
		{
			if( !this->Is_Holding )
			{
				return false;
			}
		}
		if( Dont_Click )
			return false;

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + Size && Mouse.y < this->pos.y + 16 )
		{
			this->Is_Holding = true;
			return true;
		}
		else if( this->Is_Holding )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	void Draw()
	{
		float MenuRedStyle = 0;
		float MenuGreenStyle = 149;
		float MenuBlueStyle = 255;
		if( Menu.GetCurret_Tab() == Tab )
		{
			double Ratio = Settings.GetMenuSetting( this->Tab, this->Setting ) / ( this->Max - this->Min );
			double Location = Ratio * Size;
			if (GlobalMenuAlpha == 0)
			{
				Interfaces.pSurface->DrawSetColor(0, 0, 0, 0);
			}
			else if (custom_color)
			{
				Interfaces.pSurface->DrawSetColor(r_back, g_back, b_back, a_back * (GlobalMenuAlpha / 255));
			}
			else
			{
				Interfaces.pSurface->DrawSetColor(39, 39, 39,GlobalMenuAlpha);
			}
			
			if (GlobalMenuAlpha == 0)
			{
				Interfaces.pSurface->DrawSetColor(0, 0, 0, 0);
			}
			else if (color_from_some_set)
			{
			//	Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, cus_r), Settings.GetSetting(Tab_Colors, cus_g), Settings.GetSetting(Tab_Colors, cus_b), Settings.GetSetting(Tab_Colors, cus_a) * (GlobalMenuAlpha / 255));
			}
			else if (custom_color)
			{
				Interfaces.pSurface->DrawSetColor(r, g, b, a * (GlobalMenuAlpha / 255));
			}
			else
			{
				Interfaces.pSurface->DrawSetColor(MenuRedStyle, MenuGreenStyle, MenuBlueStyle,  GlobalMenuAlpha);
			}
			Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + 7, this->pos.x + Size - 1 + 2, this->pos.y + 10);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + Size - 1, this->pos.y + 12);
			Interfaces.pSurface->DrawSetColor(227, 0, 0, GlobalMenuAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + Location, this->pos.y + 12);
			Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 10, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
			float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
			char vl[128];
			sprintf(vl, "%.f", Value1);
			Interfaces.pSurface->DrawT(this->pos.x + Location - 3, this->pos.y + 2.5, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, true, vl);
		}
	}

	void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int size, int sub, int R = 55, int G = 5, int B = 5, int A = 255, int RB = 5, int GB = 55, int BB = 5, int AB = 255, int color_set_r = -1, int color_set_g = -1, int color_set_b = -1, int color_set_a = -1)
	{
		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Max = max;
		Min = min;
		Name = name;
		Size = size;
		SubTab = sub;
		if (color_set_r != -1 && color_set_g != -1 && color_set_b != -1 && color_set_a != -1)
		{
			color_from_some_set = true;
			custom_color = false;
			Settings.SetSetting(Tab, Setting, defult);
			cus_r = color_set_r;
			cus_g = color_set_g;
			cus_b = color_set_b;
			cus_a = color_set_a;
			return;
		}
		if (R == -1 || G == -1 || B == -1 || A == -1 || RB == -1 || GB == -1 || BB == -1 || AB == -1)
		{
			custom_color = false;
			Settings.SetSetting(Tab, Setting, defult);
			return;
		}
		r = R;
		g = G;
		b = B;
		a = A;
		r_back = RB;
		g_back = GB;
		b_back = BB;
		a_back = AB;
		Settings.SetSetting( Tab, Setting, defult );
	}

	void Update()
	{
		this->pos.x = Menu.pos.x + offset.x;
		this->pos.y = Menu.pos.y + offset.y;

		// get clicked and changing value
		if( Menu.GetCurret_Tab() == Tab )
		{
			if( this->GetClicked() )
			{
				Dont_Click = true;
				POINT Mouse;
				POINT mp;
				GetCursorPos( &mp );
				ScreenToClient( GetForegroundWindow(), &mp );
				Mouse.x = mp.x;
				Mouse.y = mp.y;
				// get differance
				double idifference;
				idifference = Mouse.x - this->pos.x;
				// Set Value
				double value = ( ( idifference / Size) * ( this->Max - this->Min ) );
				if( value < Min )
				{
					value = Min;
				}
				else if( value > Max )
				{
					value = Max;
				}

				Settings.SetSetting( Tab, Setting, value );
			}
		}
	}
};

class CDropBox
{
private:
	int Tab = 0;
	int Setting = 0;

	char* Name = "ERROR";
	char* Parts[256];
	int Amount = 0;

	bool Dropping = false;

	MenuPOS pos;
	MenuPOS offset;
	int Sub = 0;

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}
		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 16 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int GetPartClicked()
	{
		if( !Clicked_This_Frame )
		{
			return -1;
		}
		if( Holding_Mouse_1 )
		{
			return -1;
		}
		if( Dont_Click )
		{
			return -1;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		for( int i = 1; i < this->Amount; i++ )
		{
			if( Mouse.x > this->pos.x && Mouse.y > this->pos.y + ( 16 * ( i ) ) && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + ( 16 * ( i + 1 ) ) )
			{
				return i;
			}
		}
		return -1;
	}

public:
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if( Tab == Menu.GetCurret_Tab() )
		{
			if( this->GetClicked() )
			{
				if( this->Dropping == true )
				{
					this->Dropping = false;
				}
				else
				{
					this->Dropping = true;
				}
				Dont_Click = true;
			}
			else if( this->Dropping )
			{
				int index = this->GetPartClicked();
				if( index != -1 )
				{
					Settings.SetSetting( this->Tab, this->Setting, index );
					this->Dropping = false;
					Dont_Click = true;
				}
				else if( Clicked_This_Frame && !Holding_Mouse_1 )
				{
					Dropping = false;
				}
			}
			else
			{
				Dropping = false;
			}
		}
		else
		{
			Dropping = false;
		}
	}

	void Draw()
	{
		if( Tab == Menu.GetCurret_Tab() )
		{
			Interfaces.pSurface->DrawSetColor(39, 39, 39, GlobalMenuAlpha);
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 1, this->pos.y + 1, this->pos.x + 124, this->pos.y + 15 );
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + 2, this->pos.x + 126, this->pos.y + 13);
			Interfaces.pSurface->DrawT( this->pos.x + 1, this->pos.y - 15, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name );

			if( this->Dropping )
			{
				for( int i = 1; i < this->Amount; i++ )
				{
					Interfaces.pSurface->DrawSetColor(39, 39, 39, GlobalMenuAlpha); //dark top color
					Interfaces.pSurface->DrawFilledRect( this->pos.x, this->pos.y + ( 16 * i ), this->pos.x + 125, this->pos.y + ( 16 * i ) + 16 );
					Interfaces.pSurface->DrawT( this->pos.x + 11, this->pos.y + ( 16 * i ), CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[ i ] );
					//part 2
					int value = ( int )Settings.GetMenuSetting( Tab, Setting );
					if( value >= this->Amount )
						value = 0;
					//Interfaces.pSurface->DrawT(pos.x + 11, pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, Parts[value]);

					static int Texture = Interfaces.pSurface->CreateNewTextureID( true ); //need to make a texture with procedural true
					unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha/2 };//{ color.r(), color.g(), color.b(), color.a() };

					Interfaces.pSurface->DrawSetTextureRGBA( Texture, buffer, 1, 1 ); //Texture, char array of texture, width, height
					Interfaces.pSurface->DrawSetColor(250, 250, 250, GlobalMenuAlpha ); // keep this full color and opacity use the RGBA @top to set values.
					Interfaces.pSurface->DrawSetTexture( Texture ); // bind texture

					Vertex_t Verts2[3];
					Verts2[ 0 ].x = pos.x + 103;
					Verts2[ 0 ].y = pos.y + 11;
					Verts2[ 1 ].x = pos.x + 107.5;
					Verts2[ 1 ].y = pos.y + 6;
					Verts2[ 2 ].x = pos.x + 112;
					Verts2[ 2 ].y = pos.y + 11;

					Interfaces.pSurface->DrawTexturedPolygon( 3, Verts2 );
				}
				int value = ( int )Settings.GetMenuSetting( Tab, Setting );
				if( value >= this->Amount )
					value = 0;
				Interfaces.pSurface->DrawT( this->pos.x + 11, this->pos.y, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[ value ] );
			}
			else
			{
				int value = ( int )Settings.GetMenuSetting( Tab, Setting );
				if( value >= this->Amount )
					value = 0;
				Interfaces.pSurface->DrawT( this->pos.x + 11, this->pos.y, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[ value ] );

				static int Texture = Interfaces.pSurface->CreateNewTextureID( true ); //need to make a texture with procedural true
				unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };

				Interfaces.pSurface->DrawSetTextureRGBA( Texture, buffer, 1, 1 ); //Texture, char array of texture, width, height
				Interfaces.pSurface->DrawSetColor(75, 75, 75, GlobalMenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
				Interfaces.pSurface->DrawSetTexture( Texture ); // bind texture

				Vertex_t Verts2[3];
				Verts2[ 0 ].x = pos.x + 103;
				Verts2[ 0 ].y = pos.y + 6;
				Verts2[ 1 ].x = pos.x + 112;
				Verts2[ 1 ].y = pos.y + 6;
				Verts2[ 2 ].x = pos.x + 107.5;
				Verts2[ 2 ].y = pos.y + 11;

				Interfaces.pSurface->DrawTexturedPolygon( 3, Verts2 );
			}
		}
	}

	void Init( int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int sub )
	{
		Name = name;
		Amount = parts;

		for( int i = 0; i < parts; i++ )
		{
			Parts[ i ] = arr[ i ];
		}

		Tab = tab;
		Setting = setting;
		offset.x = x;
		offset.y = y;
		Sub = sub;
	}
};

class CSettingsDropBox
{
private:
	int Tab = 0;
	int Setting = 0;

	char* Name = "ERROR";
	char* Parts[256];
	int Amount = 0;

	bool Dropping = false;

	MenuPOS pos;
	MenuPOS offset;
	int Sub = 0;

	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}
		if (Dont_Click)
		{
			return false;
		}
		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 16)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int GetPartClicked()
	{
		if (!Clicked_This_Frame)
		{
			return -1;
		}
		if (Holding_Mouse_1)
		{
			return -1;
		}
		if (Dont_Click)
		{
			return -1;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		for (int i = 1; i < this->Amount; i++)
		{
			if (Mouse.x > this->pos.x && Mouse.y > this->pos.y + (16 * (i)) && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + (16 * (i + 1)))
			{
				return i;
			}
		}
		return -1;
	}

public:
	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if (Tab_Misc == Menu.GetCurret_Tab())
		{
			if (this->GetClicked())
			{
				if (this->Dropping == true)
				{
					this->Dropping = false;
				}
				else
				{
					this->Dropping = true;
				}
				Dont_Click = true;
			}
			else if (this->Dropping)
			{
				int index = this->GetPartClicked();
				if (index != -1)
				{
					Settings.SetSetting(this->Tab, this->Setting, index);
					this->Dropping = false;
					Dont_Click = true;
				}
				else if (Clicked_This_Frame && !Holding_Mouse_1)
				{
					Dropping = false;
				}
			}
			else
			{
				Dropping = false;
			}
		}
		else
		{
			Dropping = false;
		}
	}

	void Draw()
	{
		if (Tab_Misc == Menu.GetCurret_Tab())
		{
			Interfaces.pSurface->DrawSetColor(39, 39, 39, GlobalMenuAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 1, this->pos.x + 124, this->pos.y + 15);
			Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + 2, this->pos.x + 126, this->pos.y + 13);
			Interfaces.pSurface->DrawT(this->pos.x + 1, this->pos.y - 15, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);

			if (this->Dropping)
			{
				for (int i = 1; i < this->Amount; i++)
				{
					Interfaces.pSurface->DrawSetColor(39, 39, 39, GlobalMenuAlpha); //dark top color
					Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (16 * i), this->pos.x + 125, this->pos.y + (16 * i) + 16);
					Interfaces.pSurface->DrawT(this->pos.x + 11, this->pos.y + (16 * i), CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[i]);
					//part 2
					int value = (int)Settings.GetMenuSetting(Tab, Setting);
					if (value >= this->Amount)
						value = 0;
					//Interfaces.pSurface->DrawT(pos.x + 11, pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, Parts[value]);

					static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
					unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha / 2 };//{ color.r(), color.g(), color.b(), color.a() };

					Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
					Interfaces.pSurface->DrawSetColor(250, 250, 250, GlobalMenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
					Interfaces.pSurface->DrawSetTexture(Texture); // bind texture

					Vertex_t Verts2[3];
					Verts2[0].x = pos.x + 103;
					Verts2[0].y = pos.y + 11;
					Verts2[1].x = pos.x + 107.5;
					Verts2[1].y = pos.y + 6;
					Verts2[2].x = pos.x + 112;
					Verts2[2].y = pos.y + 11;

					Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);
				}
				int value = (int)Settings.GetMenuSetting(Tab, Setting);
				if (value >= this->Amount)
					value = 0;
				Interfaces.pSurface->DrawT(this->pos.x + 11, this->pos.y, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
			}
			else
			{
				int value = (int)Settings.GetMenuSetting(Tab, Setting);
				if (value >= this->Amount)
					value = 0;
				Interfaces.pSurface->DrawT(this->pos.x + 11, this->pos.y, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);

				static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
				unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };

				Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
				Interfaces.pSurface->DrawSetColor(75, 75, 75, GlobalMenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
				Interfaces.pSurface->DrawSetTexture(Texture); // bind texture

				Vertex_t Verts2[3];
				Verts2[0].x = pos.x + 103;
				Verts2[0].y = pos.y + 6;
				Verts2[1].x = pos.x + 112;
				Verts2[1].y = pos.y + 6;
				Verts2[2].x = pos.x + 107.5;
				Verts2[2].y = pos.y + 11;

				Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);
			}
		}
	}

	void Init(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int sub)
	{
		Name = name;
		Amount = parts;

		for (int i = 0; i < parts; i++)
		{
			Parts[i] = arr[i];
		}

		Tab = tab;
		Setting = setting;
		offset.x = x;
		offset.y = y;
		Sub = sub;
	}
};
class CKeyButton
{
private:
	MenuPOS pos;
	MenuPOS offset;

	int Tab;
	int Setting;
	bool Getting_New_Key;
	char* Name = "ERROR";
	int Sub = 0;

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if( Mouse.x > this->pos.x + 26 && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 135 && Mouse.y < this->pos.y + 20 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab )
		{
			Interfaces.pSurface->DrawT(this->pos.x, this->pos.y, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", "");
			if( this->Getting_New_Key )
			{
				Interfaces.pSurface->DrawT( this->pos.x + 104, this->pos.y - 3, CColor(160, 160, 160, GlobalMenuAlpha), Hacks.Font_Controls, false, "[_]" );
			}
			else
			{
				if( Settings.GetMenuSetting( this->Tab, this->Setting ) == -1 )
					Interfaces.pSurface->DrawT( this->pos.x + 104, this->pos.y - 3, CColor(160, 160, 160, GlobalMenuAlpha), Hacks.Font_Controls, false, "[_]" );
				else
				{
					char* NameOfKey = KeyStrings[ ( int )Settings.GetMenuSetting( this->Tab, this->Setting ) ];
					Interfaces.pSurface->DrawT( this->pos.x + 104, this->pos.y - 3, CColor(160, 160, 160, GlobalMenuAlpha), Hacks.Font_Controls, false,NameOfKey );
				}
			}
		}
	}

	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;

		if( Menu.GetCurret_Tab() == Tab )
		{
			if( Getting_New_Key )
			{
				for( int i = 0; i < 255; i++ )
				{
					if( GetKeyPress( i ) )
					{
						if( i == VK_INSERT )
						{
							this->Getting_New_Key = false;
							Settings.SetSetting( Tab, Setting, -1 );
							break;
						}
						if( i == VK_ESCAPE )
						{
							Settings.SetSetting( Tab, Setting, -1 );
							this->Getting_New_Key = false;
							break;
						}
						Settings.SetSetting( Tab, Setting, i );
						this->Getting_New_Key = false;
						break;
					}
				}
			}
			else if( this->GetClicked() )
			{
				this->Getting_New_Key = !this->Getting_New_Key;
			}
		}
	}

	void Init( int x, int y, int tab, int setting, char* name, int sub )
	{
		offset.x = x;
		offset.y = y;
		Tab = tab;
		Setting = setting;
		Name = name;
		Sub = sub;
		Settings.SetSetting( Tab, Setting, -1 );
	}
};

class CTab
{
public:
	void Update()
	{
		pos.x = Menu.pos.x + 0;
		pos.y = Menu.pos.y + 52 + ((270 / Tab_Count) * Tab);

		if (GetClicked())
		{
			Dont_Click = true;
			Menu.Set_Current_Tab(Tab);
		}
	}

	void Draw()
	{
		if (Menu.GetCurret_Tab() == Tab)
		{
			Interfaces.pSurface->DrawT(pos.x + 71, pos.y + (220 / Tab_Count / 2) + 6, CColor(255, 255, 255, (GlobalMenuAlpha / 255.f) * 240.f), Hacks.Font_Tab, true, Name);
		}
		else
		{
			Interfaces.pSurface->DrawT(pos.x + 71, pos.y + (220 / Tab_Count / 2) + 6, CColor(100, 100, 100, (GlobalMenuAlpha / 255.f) * 110.f), Hacks.Font_Tab, true, Name);
		}
	}

	void Init(char* name, int tab, char* name1, char* icon)
	{
		Name = name;
		Name1 = name1;
		Tab = tab;
		Icon = icon;
	}

private:
	int Tab;
	MenuPOS pos;
	char* Name = "ERROR";
	char* Name1 = "ERROR";
	char* Icon = "ERROR";

	bool GetClicked()
	{
		if (!Clicked_This_Frame)
		{
			return false;
		}
		if (Holding_Mouse_1)
		{
			return false;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos(&mp);
		ScreenToClient(GetForegroundWindow(), &mp);
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if (Mouse.x > pos.x && Mouse.y > pos.y && Mouse.x < pos.x + (175 - 66) && Mouse.y < pos.y + ((270 / Tab_Count)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class CMenuBox
{
public:
	void Init( char* name, int x, int y, int w, int h, int tab, int sub )
	{
		Name = name;
		offset.x = x;
		offset.y = y;
		size.x = w;
		size.y = h;
		Tab = tab;
		SubTab = sub;
	}

	void Update()
	{
		pos.x = Menu.pos.x + offset.x;
		pos.y = Menu.pos.y + offset.y;
	}

	void Draw()
	{
		if( Tab == Menu.GetCurret_Tab() )
		{
			int Width = 0, Height = 0;
			char Buffer[256] = { '\0' };
			va_list Args;
			va_start(Args, Name);
			vsprintf_s( Buffer, Name, Args );
			va_end(Args);
			size_t Size = strlen( Buffer );
			/* set up size.xidebuffer*/
			wchar_t* wBuffer = new wchar_t[Size];
			/* char -> size.xchar */
			mbstowcs_s( nullptr, wBuffer, Size, Buffer, Size - 1 );
			/* check center */
			Interfaces.pSurface->GetTextSize( Hacks.Font_Controls, wBuffer, Width, Height );
			Interfaces.pSurface->DrawSetColor(75, 75, 75, GlobalMenuAlpha / 2);
			Interfaces.pSurface->DrawLine( pos.x, pos.y, pos.x, pos.y + size.y );
			Interfaces.pSurface->DrawLine( pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y );
			Interfaces.pSurface->DrawLine( pos.x + size.x, pos.y, pos.x + size.x, pos.y + size.y );
			Interfaces.pSurface->DrawLine(pos.x, pos.y, (pos.x * 2 + size.x) / 2 - Width / 2 - 6, pos.y);
			Interfaces.pSurface->DrawLine((pos.x * 2 + size.x) / 2 + Width / 2 + 6, pos.y, pos.x + size.x, pos.y );
			Interfaces.pSurface->DrawSetColor(75, 75, 75, GlobalMenuAlpha / 2);
			Interfaces.pSurface->DrawLine( pos.x + 1, pos.y + 1, pos.x + 1, pos.y + size.y - 1 );
			Interfaces.pSurface->DrawLine( pos.x + 1, pos.y + size.y - 1, pos.x + size.x - 1, pos.y + size.y - 1 );
			Interfaces.pSurface->DrawLine( pos.x + size.x - 1, pos.y + 1, pos.x + size.x - 1, pos.y + size.y - 1 );
			Interfaces.pSurface->DrawLine( pos.x + 1, pos.y + 1, (pos.x * 2 + size.x) / 2 - Width / 2 - 6, pos.y + 1 );
			Interfaces.pSurface->DrawLine((pos.x * 2 + size.x) / 2 + Width / 2 + 6, pos.y + 1, pos.x + size.x - 1, pos.y + 1);
			Interfaces.pSurface->DrawT((pos.x + pos.x + size.x) / 2, pos.y - 6, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, true, Name);
		}
	}

private:
	MenuPOS pos;
	MenuPOS offset;
	MenuPOS size;
	char* Name = "ERROR";
	int Tab;
	char* Icon = "ERROR";
	int SubTab = 0;
};

class CFunctionButton
{
public:
	void Update()
	{
		this->pos.x = Menu.pos.x + this->offset.x;
		this->pos.y = Menu.pos.y + this->offset.y;

		if( Menu.GetCurret_Tab() == Tab_Misc)
		{
			if( this->GetClicked() )
			{
				DWORD disfunc = Function;
				__asm
				{
					CALL disfunc
				}
			}
		}
	}

	void Draw()
	{
		if( Menu.GetCurret_Tab() == Tab_Misc)
		{
			Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 3, this->pos.y + 1, this->pos.x + 121, this->pos.y + 12);
			Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 3, this->pos.x + 123, this->pos.y + 12);
			Interfaces.pSurface->DrawFilledRect( this->pos.x + 2, this->pos.y + 2, this->pos.x + 123, this->pos.y + 14 );
			Interfaces.pSurface->DrawT( this->pos.x + 62.5, this->pos.y, CColor(250, 250, 250, GlobalMenuAlpha), Hacks.Font_Controls, true, Name );
		}
	}

	void Init( int x, int y, DWORD function, char* name, int tab )
	{
		Function = function;
		Name = name;
		offset.x = x;
		offset.y = y;
		Tab = tab;
	}

	bool GetClicked()
	{
		if( !Clicked_This_Frame )
		{
			return false;
		}
		if( Holding_Mouse_1 )
		{
			return false;
		}
		if( Dont_Click )
		{
			return false;
		}

		POINT Mouse;
		POINT mp;
		GetCursorPos( &mp );
		ScreenToClient( GetForegroundWindow(), &mp );
		Mouse.x = mp.x;
		Mouse.y = mp.y;

		if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 16)
		{
			return true;
		}

		return false;
	}

private:
	DWORD Function;
	char* Name = "NO NAME";
	MenuPOS pos;
	MenuPOS offset;
	int Tab = -1;
};

std::vector< CSlider > Sliders;
std::vector< CButton > Buttons;
std::vector< CButton1 > Buttons1;
std::vector< CDropBox > Dropboxes;
std::vector< CKeyButton > KeyButtons;
std::vector< CMenuBox > MenuBoxs;
std::vector< CTab > Tabs;
std::vector< CSettingsDropBox > SettingsDropboxes;
std::vector< CFunctionButton > FuncButtons;

int Dropboxs_Amount = 0;
int SettingsDropboxs_Amount = 0;

void CheckBox( int Tab, int Setting, bool defult, int x, int y, char* name )
{
	CButton Filler;
	Filler.Init( Tab, Setting, defult, x, y, name, -1 );
	Buttons.push_back( Filler );
}
void AddNewSettingsDropBox(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr)
{
	CSettingsDropBox SettingsDropper;
	SettingsDropper.Init(x, y, tab, setting, name, parts, arr, -1);
	SettingsDropboxes.push_back(SettingsDropper);//
	SettingsDropboxs_Amount++;
}
void EzSlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int size, int r = -1, int g = -1, int b = -1, int a = -1, int rb = -1, int gb = -1, int bb = -1, int ab = -1, int cus_r = -1, int cus_g = -1, int cus_b = -1, int cus_a = -1)
{
	CSlider Slid;
	Slid.Init(x, y, min, max, defult, name, tab, setting, size, -1, r, g, b, a, rb, gb, bb, ab, cus_r, cus_g, cus_b, cus_a);
	Sliders.push_back( Slid );
}

void ComdoBox( int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr )
{
	CDropBox Dropper;
	Dropper.Init( x, y, tab, setting, name, parts, arr, -1 );
	Dropboxes.push_back( Dropper );//
	Dropboxs_Amount++;
}

void AddNewKeyButton( int x, int y, int tab, int setting, char* name )
{
	CKeyButton KeyButton;
	KeyButton.Init( x, y, tab, setting, name, -1 );
	KeyButtons.push_back( KeyButton );
}

void AddNewTab( char* Name, int Tab, char* Name1, char* Icon )
{
	CTab Filler;
	Filler.Init( Name, Tab, Name1 , Icon );
	Tabs.push_back( Filler );
	Tab_Count++;
}

void AddNewMenuBox( char* name, int x, int y, int w, int h, int Tab )
{
	CMenuBox Filler;
	Filler.Init( name, x, y, w, h, Tab, -1 );
	MenuBoxs.push_back( Filler );
}

void EzButton( int x, int y, DWORD function, char* name, int tab )
{
	CFunctionButton Filler;
	Filler.Init( x, y, function, name, tab );
	FuncButtons.push_back( Filler );
}
void EzButton1(int x, int y, DWORD function, char* name, int tab)
{
	CFunctionButton Filler;
	Filler.Init(x, y, function, name, tab);
	FuncButtons.push_back(Filler);
}
extern player_info_t* Info;
std::vector< char* > ingameNames{ "NONE", "DEAGLE", "DUALBERETTAS", "FIVESEVEN", "GLOCK", "AK47", "AUG", "AWP", "FAMAS", "G3SG1",
	"GALILAR", "M249", "M4A4", "MAC10", "P90", "UMP45", "XM1014", "PPBIZON", "MAG7", "NEGEV", "SAWEDOFF", "TEC9",
	"P2000", "MP7", "MP9", "NOVA", "P250", "SCAR20", "SG553", "SSG08", "CTKnife", "TKnife", "M4A1S", "USPS", "CZ75AUTO", "R8Revolver" };
int page[256];
int selected[256];
int realselected[256];

void drawselectbox( int amount, char* arr[100], int width, int height, int setting, int realvals[100] )
{
	int startx = Menu.pos.x + width + 3;
	int starty = Menu.pos.y + height + 3;
	Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
	Interfaces.pSurface->DrawOutlinedRect( startx - 2, starty - 2, startx + 137, starty + 202 );

	for( int i = 0; i < 10; i++ )
	{
		int number = i + 10 * page[ setting ];
		if( number > amount )
		{
		}
		else
		{
			Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
			Interfaces.pSurface->DrawFilledRect( startx, starty + i * 16, startx + 120, starty + i * 16 + 16 );
			Interfaces.pSurface->DrawSetColor( 30, 30, 30, GlobalMenuAlpha );
			Interfaces.pSurface->DrawFilledRect( startx + 1, starty + i * 16 + 1, startx + 119, starty + i * 16 + 15 );
			if( number == selected[ setting ] )
			{
				Interfaces.pSurface->DrawT( startx + 3, starty + i * 16 + 3, CColor( 20, 200, 255, GlobalMenuAlpha ), Hacks.Font_Controls, false, arr[ number ] );
				realselected[ setting ] = realvals[ number ];
			}
			else
				Interfaces.pSurface->DrawT( startx + 3, starty + i * 16 + 3, CColor( 255, 255, 255, GlobalMenuAlpha ), Hacks.Font_Controls, false, arr[ number ] );
		}
	}
	double drawbarheight = ( 10 * 160 );
	drawbarheight /= amount;
	if( drawbarheight > 200 )
		drawbarheight = 200;
	Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
	Interfaces.pSurface->DrawOutlinedRect( startx + 125, starty, startx + 135, starty + 200 );
	Interfaces.pSurface->DrawFilledRect( startx + 127, starty + page[ setting ] * drawbarheight, startx + 133, starty + drawbarheight + page[ setting ] * drawbarheight );
	// scroll
	if( Clicked_This_Frame )
	{
		if( !Holding_Mouse_1 )
		{
			if( !Dont_Click )
			{
				POINT Mouse;
				POINT mp;
				GetCursorPos( &mp );
				ScreenToClient( GetForegroundWindow(), &mp );
				Mouse.x = mp.x;
				Mouse.y = mp.y;
				if( Mouse.x > startx + 125 && Mouse.y > starty && Mouse.x < startx + 135 && Mouse.y < starty + 200 )
				{
					int percentage = ( Mouse.y - starty );
					for( int i = 0; i < 10; i++ )
					{
						if( drawbarheight * i < percentage && percentage < drawbarheight * ( i + 1 ) )
						{
							page[ setting ] = i;
						}
					}
				}
			}
		}
	}
	// getting clicked
	if( Clicked_This_Frame )
	{
		if( !Holding_Mouse_1 )
		{
			if( !Dont_Click )
			{
				POINT Mouse;
				POINT mp;
				GetCursorPos( &mp );
				ScreenToClient( GetForegroundWindow(), &mp );
				Mouse.x = mp.x;
				Mouse.y = mp.y;
				if( Mouse.x > startx && Mouse.y > starty && Mouse.x < startx + 120 && Mouse.y < starty + 200 )
				{
					int percentage = ( Mouse.y - starty );
					for( int i = 0; i < 10; i++ )
					{
						if( 20 * i < percentage && percentage < 20 * ( i + 1 ) )
						{
							int number = i + 10 * page[ setting ];
							selected[ setting ] = number;
						}
					}
				}
			}
		}
	}
}

void upp()
{
	ConVar* sv_cheats = Interfaces.g_ICVars->FindVar("sv_cheats");
	SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
	sv_cheats_spoofed->SetInt(1);
	Interfaces.pEngine->ClientCmd_Unrestricted("cl_fullupdate", 0);
}

void mine()
{
	ConVar* sv_cheats1 = Interfaces.g_ICVars->FindVar("mat_showlowresimage");
	SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats1);
	sv_cheats_spoofed->SetInt(1);

}

void skinchanger()
{
}

void SetupMenu()
{
		//Interfaces.pEngine->ExecuteClientCmd("cl_fullupdate");
	char* arr[512] = { "ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR", };

	//Tabs
	if (Tab_Legitbot1 == Menu.GetCurret_Tab())
	{
		AddNewTab("< Back", Tab_Legitbot1, "LEGITBOT", "G");
		AddNewTab("LegitBot", Tab_Legitbot, "LEGITBOT", "G");
		AddNewTab("RageBot", Tab_Ragebot, "RAGEBOT", "B");
		AddNewTab("Visuals", Tab_Visuals, "ESP", "C");
		AddNewTab("SKINS", Tab_Skinchanger, "Ы","Ы");
		AddNewTab("Colors", Tab_Colors, "COLORS", "E");
		AddNewTab("Misc", Tab_Misc, "MISC", "D");
		//AddNewTab("(О игроке)", Tab_Plist,"INFO" ,"F");

		//AddNewTab( "CFG", Tab_Config, "" );
	}
	else
	{

	}

	
	{
		//Dropbox Config
		std::vector< char* > Hitbox = { "Head", "Head", "Chest", "Stomach" };
		std::vector< char* > FovType = { "Static", "Static" };
		std::vector< char* > SmoothType = { "Static", "Static" };

		//Controls
		{







			CheckBox(Tab_Legitbot, Legitbot_enable, false, 120 + 20, 50 + 20, "Aimbot Enabled");
			CheckBox(Tab_Legitbot, Legitbot_Aimonkey, false, 120 + 20, 70 + 20, "Aimbot On Key");
			AddNewKeyButton(30 + 90 + 20, 85 + 20 - 15, Tab_Legitbot, Legitbot_Aimbotkey, "Key");
			CheckBox(Tab_Legitbot, Legitbot_multihitbox, false, 120 + 20, 105 - 15 + 20, "Nearest");
			ComdoBox(120 + 20, 135 - 15 + 20, Tab_Legitbot, Legitbot_hitbox, "Hitbox", 4, Hitbox);
			//ComdoBox(235, 140, Tab_Legitbot, Legitbot_fovtype, "Fov Type", 2, FovType);
			EzSlider(120 + 20, 170 - 15 + 20, 0, 100, 0, "Fov", Tab_Legitbot, Legitbot_fov, 117);
			//ComdoBox(235, 200, Tab_Legitbot, Legitbot_smoothtype, "Smooth Type", 2, SmoothType);
			EzSlider(120 + 20, 195 - 15 + 20, 0, 100, 0, "Speed X", Tab_Legitbot, Legitbot_smoothY, 50);
			EzSlider(174 + 20 + 13, 195 - 15 + 20, 0, 100, 0, "Speed Y", Tab_Legitbot, Legitbot_smoothX, 50);
			//CheckBox(Tab_Legitbot, Legitbot_rcs, false, 215, 270, "Rcs");
			EzSlider(120 + 20, 220 - 15 + 20, 0, 100, 0, "RCS X", Tab_Legitbot, Legitbot_rcsforceX, 50);
			EzSlider(174 + 20 + 13, 220 - 15 + 20, 0, 100, 0, "RCS Y", Tab_Legitbot, Legitbot_rcsforceY, 50);
			CheckBox(Tab_Legitbot, Legitbot_Psilent, false, 120 + 20, 285 - 15, "pSilent");
			EzSlider(120 + 20, 265 - 15, 0, 150, 0, "Delay", Tab_Legitbot, Legitbot_Firedelay, 50);
			EzSlider(174 + 20 + 13, 265 - 15, 0, 100, 0, "pSilent RCS", Tab_Legitbot, Legitbot_Prcsforce, 50);
			CheckBox(Tab_Legitbot, Legitbot_SmokeCheck, false, 270 + 20, 50 + 20, "SmokeCheck");
			CheckBox(Tab_Legitbot, Legitbot_FlashCheck, false, 270 + 20, 70 + 20, "FlashCheck");
			CheckBox(Tab_Legitbot, Legitbot_JumpCheck, false, 270 + 20, 110, "JumpCheck");
			CheckBox(Tab_Legitbot, Legitbot_Fov, false, 270 + 20, 130, "DrawFov");
			CheckBox(Tab_Legitbot, Legitbot_PS, false, 120 + 20, 305 - 15, "pSilent on key");
			AddNewKeyButton(120 + 20, 320 - 15 - 15, Tab_Legitbot, Legitbot_Pskey, "Key");










		}
	}

	/* Ragebot */

	//AddNewMenuBox("Aimbot", 115, 90, 235, 385, Tab_Ragebot);
	//{
		//Dropbox Config
	std::vector< char* > Selection = { "Cycle", "Cycle","Fov" };
	std::vector< char* > Hitbox = { "Head", "Head", "Neck", "Chest", "Pelvis" };
	std::vector< char* > MultipointType = { "Compression", "Compression", "Max", };
	std::vector< char * > MultiBox = { "Off", "Off", "Adaptive", "Full" };

	//Controls
	CheckBox(Tab_Ragebot, Ragebot_AimbotEnabled, false, 120 + 20, 60, "Enabled");
	ComdoBox(120 + 20, 85, Tab_Ragebot, Ragebot_Selection, "Selection", 3, Selection);
	ComdoBox(120 + 20, 115, Tab_Ragebot, Ragebot_Hitbox, "Hitbox", 5, Hitbox);

	//	ComdoBox( 235, 155 + 70, Tab_Ragebot, Ragebot_MultipointType, "", 3, MultipointType );
	EzSlider(250 + 20, 140 - 20, 0, 100, 100, "Custom Point Scale", Tab_Ragebot, Ragebot_PS, 125);
	ComdoBox(120 + 20, 145, Tab_Ragebot, Ragebot_Multibox, "HitScan", 4, MultiBox);
	CheckBox(Tab_Ragebot, Ragebot_Multipoint, false, 120 + 20, 170, "Multipoint");
	CheckBox(Tab_Ragebot, Ragebot_SilentAim, false, 120 + 20, 190, "Silent aim");
	CheckBox(Tab_Ragebot, Ragebot_Velocity, false, 120 + 20, 250, "Adaptive Hitbox");
	CheckBox(Tab_Ragebot, Ragebot_AutoShoot, false, 120 + 20, 210, "AutoShoot");
	CheckBox(Tab_Ragebot, Ragebot_Autoscope, false, 120 + 20, 230, "AutoScope");

	EzSlider(120 + 20, 275, 0, 100, 50, "HitChance", Tab_Ragebot, Ragebot_Hitchance, 125);
	EzSlider(120 + 20, 300, 0, 120, 0, "MinDamage", Tab_Ragebot, Ragebot_MinDamage, 125);
	std::vector< char* > Antiaim_Pitch = { "Off", "Off","Emotion", "Down", "Emros", };
	std::vector< char* > Antiaim_Yaw = { "Off", "Off", "Jitter Skeet", "Fake Jitter" , "Fake", "Fake2", "Fake Spin", "Crooked Distortion", "lby breaker", "LBY", "Shafle" };
	std::vector< char* > AtTargets = { "Off", "Off", "IfTarget", "Normal" };
	std::vector< char* > resolvers = { "Off", "Off", "No Name", "LBY", "Force" , "Random", "LBY Inverse", "Smart" };

	//Controls
	CheckBox(Tab_Ragebot, AntiAim_Enabled, false, 250 + 20, 165 - 20, "Enable");
	ComdoBox(250 + 20, 190 - 20, Tab_Ragebot, AntiAim_Pitch, "Pitch", 4, Antiaim_Pitch);
	ComdoBox(250 + 20, 220 - 20, Tab_Ragebot, AntiAim_Yaw, "Yaw", 11, Antiaim_Yaw);
	CheckBox(Tab_Ragebot, AntiAim_Dinamic, false, 250 + 20, 310 - 20 - 20, "DinamicAA");
	ComdoBox(250 + 20, 250 - 20, Tab_Ragebot, AntiAim_AtTargets, "At Targets", 4, AtTargets);
	CheckBox(Tab_Ragebot, AntiAim_FakeWalk, false, 250 + 20, 275 - 20, "FakeWalk");
	AddNewKeyButton(250 + 20, 290 - 20 - 15, Tab_Ragebot, AntiAim_FakeWalkButton, "Key");
	std::vector< char* > PreferBodyAim = { "Disable", "Disable", "Smart", "Full" };

	//Controls

	//ComdoBox(490, 70, Tab_Ragebot, Ragebot_Accuracy, "Accuracy Boost", 5, Accuracy);
	ComdoBox(250 + 20, 70, Tab_Ragebot, Ragebot_PreferBodyAim, "bAIM", 4, PreferBodyAim);
	ComdoBox(250 + 20, 330 - 20 - 15, Tab_Ragebot, Ragebot_Resolver, "Resolver", 8, resolvers);
	CheckBox(Tab_Ragebot, Ragebot_PositionAdjustment, false, 250 + 20, 95, "Position Adjustment");
	//	CheckBox(Tab_Ragebot, Ragebot_AntiResovler, false, 380, 150, "Anti-Resolver");
	//	CheckBox(Tab_Ragebot, Ragebot_correction, false, 380, 170, "Fake-Lag correction");
	//	CheckBox(Tab_Ragebot, Ragebot_Accuracy, false, 250, 135, "Accuracy Boost");
	//	CheckBox(Tab_Ragebot, Ragebot_AAcorrect, false, 380, 210, "Anti-Aim correction");
//	}

	std::vector< char* > AWPSKINEZ = { "BOOM", "BOOM", "Dragon Lore", "Forest DDPAT", "Pink DDPAT", "Snake Camo", "Lightning Strike", "Safari Mesh",
		"Corticera", "Redline","Man-o'-war", "Graphite","Electric Hive","Pit Viper","Asiimov","Worm God","Medusa","Sun in Leo","Hyper Beast", "" };
	std::vector< char* > SSGSKINEZ = {
		"Slaughter",
		"Slaughter",
		"Lichen Dashed",
		"Fade",
		"Dark Water",
		"Blue Spruce",
		"Sand Dune",
		"Palm",
		"Mayan Dreams",
		"Blood in the Water",
		"Tropical Storm",
		"Acid Fade",
		"Slashed",
		"Detour",
		"Abyss",
		"",
	};
	std::vector< char* > SCARSKINEZ = { "Crimson Web","Crimson Web",
		"Splash Jam",
		"Storm",
		"Contractor",
		"Carbon Fiber",
		"Sand Mesh",
		"Palm",
		"Emerald",
		"Crimson Web",
		"Cardiac",
		"Army Sheen",
		"Cyrex",
		"Grotto",
		"Emerald",
	};
	std::vector< char* > S3SG1SKINEZ = { "Desert Storm","Desert Storm",
		"Arctic Camo",
		"Bone Mask",
		"Contractor",
		"Safari Mesh",
		"Polar Camo",
		"Jungle Dashed",
		"VariCamo",
		"Predator",
		"Demeter",
		"Azure Zebra",
		"Green Apple",
		"Orange Kimono",
		"Neon Kimono",
		"Murky",
		"Chronos"

	};
	std::vector< char* > AK47SKINEZ = { "First Class",
		"First Class",
		"Red Laminate",
		"Contrast Spray",
		"Case Hardened",
		"Safari Mesh",
		"Jungle Spray",
		"Predator",
		"Black Laminate",
		"Fire Serpent",
		"Cartel",
		"Emerald Pinstripe",
		"Blue Laminate",
		"Redline",
		"Vulcan",
		"Jaguar",
		"Jet Set",
		"Wasteland Rebel",
		"Elite Build",
		"Hydroponic",
		"Aquamarine Revenge",
	};
	std::vector< char* > M4A1SKINEZ = { "Desert Storm",
		"Desert Storm",
		"Tornado",
		"Forest DDPAT",
		"Radiation Hazard",
		"Modern Hunter",
		"Jungle Tiger",
		"Urban DDPAT",
		"Bullet Rain",
		"Predator",
		"Faded Zebra",
		"Zirka",
		"Asiimov",
		"Howl",
		"X-Ray",
		"Desert-Strike",
		"Griffin",
		"Dragon King",
		"Poseidon",
		"Daybreak",
		"Evil Daimyo",
	};
	std::vector< char* > M4A1SSKINEZ = { "Slaughter",
		"Slaughter",
		"Hot Rod",
		"Dark Water",
		"Hyper Beast",
		"Boreal Forest",
		"VariCamo",
		"Nitro",
		"Bright Water",
		"Atomic Alloy",
		"Blood Tiger",
		"Guardian",
		"Master Piece",
		"Knight",
		"Cyrex",
		"Basilisk",
		"Icarus Fell",
	};
	std::vector< char* > USPSKINEZ = { "Slaughter","Slaughter",
		"Forest Leaves",
		"Dark Water",
		"VariCamo",
		"Overgrowth",
		"Caiman",
		"Blood Tiger",
		"Serum",
		"Night Ops",
		"Stainless",
		"Guardian",
		"Orion",
		"Road Rash",
		"Royal Blue",
		"Business Class",
		"Para Green",
		"Torque",
	};
	std::vector< char* > GlockSKINEZ = { "Groundwater","Groundwater",
		"Candy Apple",
		"Fade",
		"Night",
		"Dragon Tattoo",
		"Twilight Galaxy",
		"Sand Dune",
		"Brass",
		"Catacombs",
		"Sand Dune",
		"Steel Disruption",
		"Blue Fissure",
		"Death Rattle",
		"Water Elemental",
		"Reactor",
		"Grinder",
		"Bunsen Burner",
	};
	std::vector< char* > P2000SKINEZ = { "Grassland Leaves","Grassland Leaves",
		"Silver",
		"Granite Marbleized",
		"Forest Leaves",
		"Ossified",
		"Handgun",
		"Fade",
		"Scorpion",
		"Grassland",
		"Corticera",
		"Ocean Foam",
		"Pulse",
		"Amber Fade",
		"Red FragCam",
		"Chainmail",
		"Coach Class",
		"Ivory",
		"Fire Elemental",
		"Asterion",
		"Pathfinder",
	};
	std::vector< char* > P250SKINEZ = { "Whiteout",
		"Whiteout",
		"Metallic DDPAT",
		"Splash",
		"Gunsmoke",
		"Modern Hunter",
		"Bone Mask",
		"Boreal Forest",
		"Sand Dune",
		"Nuclear Threat",
		"Mehndi",
		"Facets",
		"Hive",
		"Muertos",
		"Steel Disruption",
		"Undertow",
		"Franklin",
		"Neon Kimono",
		"Supernova",
		"Contamination",
		"Cartel",
		"Valence",
		"Crimson Kimono",
		"Mint Kimono",
	};
	std::vector< char* > CZSKINEZ = { "Pole Position","Pole Position",
		"Crimson Web",
		"Nitro",
		"Hexane",
		"Tread Plate",
		"The Fuschia Is Now",
		"Victoria",
		"Tuxedo",
		"Army Sheen",
		"Poison Dart",
		"Nitro",
		"Chalice",
		"Twist",
		"Tigris",
		"Green Plaid",
		"Emerald",
		"Yellow Jacket",
	};
	std::vector< char* > TEC9SKINEZ = { "Tornado","Tornado",
		"Groundwater",
		"Forest DDPAT",
		"Terrace",
		"Urban DDPAT",
		"Ossified",
		"Hades",
		"Brass",
		"Nuclear Threat",
		"VariCamo",
		"Nuclear Threat",
		"Red Quartz",
		"Tornado",
		"Blue Titanium",
		"Army Mesh",
		"Titanium Bit",
		"Sandstorm",
		"Isaac",
		"Toxic",
		"Bamboo Forest",
	};
	std::vector< char* > F7SKINEZ = { "Candy Apple","Candy Apple",
		"Bone Mask",
		"Case Hardened",
		"Contractor",
		"Forest Night",
		"Orange Peel",
		"Jungle",
		"Nitro",
		"Red Quartz",
		"Anodized Gunmetal",
		"Nightshade",
		"Silver Quartz",
		"Kami",
		"Copper Galaxy",
		"Neon Kimono",
		"Fowl Play",
		"Hot Shot",
		"Urban Hazard",
		"Monkey Business",

	};
	std::vector< char* > DEAGLESKINEZ = { "Blaze","Blaze",
		"Pilot",
		"Midnight Storm",
		"Sunset StormN",
		"Forest DDPAT",
		"Crimson Web",
		"Urban DDPAT",
		"Night",
		"Hypnotic",
		"Mudder",
		"VariCamo",
		"Golden Koi",
		"Red Quartz",
		"Cobalt Disruption",
		"Urban Rubble",
		"Naga",
		"Hand Cannon",
		"Heirloom",
		"Meteorite",
		"Conspiracy",
		"Bronze Deco",
		"Sunset StormC",

	};
	std::vector< char* > ELITESKINEZ = { "Anodized Navy","Anodized Navy",
		"Ossified",
		"Stained",
		"Contractor",
		"Colony",
		"Demolition",
		"Black Limba",
		"Red Quartz",
		"Cobalt Quartz",
		"Hemoglobin",
		"Urban Shock",
		"Marina",
		"Panther",
		"Retribution",
		"Briar",
		"Duelist",
		"Moon in Libra",

	};
	std::vector< char* > FAMASSKINEZ = { "Contrast Spray","Contrast Spray",
		"Colony",
		"Cyanospatter",
		"Djinn",
		"fterimage",
		"Doomkitty",
		"Spitfire",
		"Teardown",
		"Hexane",
		"Pulse",
		"Sergeant",
		"Styx",
		"Neural Net",

	};
	std::vector< char* > GALILSKINEZ = { "Forest DDPAT", "Forest DDPAT",
		"Contrast Spray",
		"Orange DDPAT",
		"Eco",
		"Winter Forest",
		"Sage Spray",
		"VariCamo",
		"Chatterbox",
		"Shattered",
		"Kami",
		"Blue Titanium",
		"Urban Rubble",
		"Hunting Blind",
		"Sandstorm",
		"Tuxedo",
		"Cerberus",
		"Aqua Terrace",
		"Rocket Pop",

	};
	std::vector< char* > MACSKINEZ = { "Tornado", "Tornado",
		"Candy Apple",
		"Silver",
		"Forest DDPAT",
		"Urban DDPAT",
		"Fade",
		"Neon Rider",
		"Ultraviolet",
		"Palm",
		"Graven",
		"Tatter",
		"Amber Fade",
		"Heat",
		"Curse",
		"Indigo",
		"Commuter",
		"Nuclear Garden",
		"Malachite",

	};
	std::vector< char* > MP9SKINEZ = { "Ruby Poison Dart","Ruby Poison Dart",
		"Bone Mask",
		"Hot Rod",
		"Storm",
		"Bulldozer",
		"Hypnotic",
		"Sand Dashed",
		"Orange Peel",
		"Dry Season",
		"Dark Age",
		"Rose Iron",
		"Green Plaid",
		"Setting Sun",
		"Dart",
		"Deadly Poison",
		"Pandora's Box",

	};
	std::vector< char* > P90SKINEZ = { "Leather","Leather",
		"Virus",
		"Contrast Spray",
		"Storm",
		"Cold Blooded",
		"Glacier Mesh",
		"Sand Spray",
		"Death by Kitty",
		"Ash Wood",
		"Fallout Warning",
		"Scorched",
		"Emerald Dragon",
		"Teardown",
		"Blind Spot",
		"Trigon",
		"Desert Warfare",
		"Module",
		"Asiimov",
		"Elite Build",


	};
	std::vector< char* > MP7SKINEZ = { "Groundwater","Groundwater",
		"Whiteout",
		"Forest DDPAT",
		"Anodized Navy",
		"Skulls",
		"Gunsmoke",
		"Contrast Spray",
		"Bone Mask",
		"Ossified",
		"Orange Peel",
		"VariCamo",
		"Army Recon",
		"Ocean Foam",
		"Full Stop",
		"Urban Hazard",
		"Olive Plaid",
		"Armor Core",
		"Asterion",
		"Nemesis",


	};
	std::vector< char* > UMPSKINEZ = { "Blaze","Blaze",
		"Forest DDPAT",
		"Gunsmoke",
		"Urban DDPAT",
		"Grand Prix",
		"Carbon Fiber",
		"Caramel",
		"Fallout Warning",
		"Scorched",
		"Bone Pile",
		"Delusion",
		"Corporal",
		"Indigo",
		"Labyrinth",
		"Minotaur's Labyrinth",
		"Riot",


	};
	std::vector< char* > BIZONSKINEZ = { "Blue Streak","Blue Streak",
		"Modern Hunter",
		"Forest Leaves",
		"Bone Mask",
		"Carbon Fiber",
		"Sand Dashed",
		"Urban Dashed",
		"Brass",
		"VariCamo",
		"Irradiated Alert",
		"Rust Coat",
		"Water Sigil",
		"Night Ops",
		"Cobalt Halftone",
		"Antique",
		"Rust Coat",
		"Osiris",
		"Chemical Green",
		"Bamboo Print",
		"Bamboo Forest",


	};
	std::vector< char* > AUGSKINEZ = { "Wings","Wings",
		"Copperhead",
		"Bengal Tiger",
		"Anodized Navy",
		"Radiation Hazard",
		"Condemned",
		"Hot Rod",
		"Storm",
		"Contractor",
		"Colony",
		"Chameleon",
		"Torque",
		"Asterion",
		"Daedalus",
		"Akihabara Accept",

	};
	std::vector< char* > SGSKINEZ = { "Tornado","Tornado",
		"Anodized Navy",
		"Contrast Spray",
		"Bone Mask",
		"Bulldozer",
		"Ultraviolet",
		"Waves Perforated",
		"Damascus Steel",
		"Fallout Warning",
		"Wave Spray",
		"Gator Mesh",
		"Damascus Steel",
		"Pulse",
		"Army Sheen",
		"Traveler",
		"Fallout Warning",
		"Cyrex",

	};
	std::vector< char* > GloveModelSTD = { "Bloodhound","Bloodhound", "Sporty", "Slick", "Specialist","Moto", "Handwrap" };
	std::vector< char* > GloveSkinSTD = { "Bloodhound Black","Bloodhound Black", "Bloodhound Snakeskin", "Bloodhound Metallic", "Sporty Purple", "Sporty Green","Sporty Light Blue","Sporty Military","Slick Black","Slick Military","Slick Red","Specialist DDPAT", "Specialist Kimono", "Specialist Emerald" ,"Specialist Orange" ,"Moto Mint" ,"Moto Boom","Moto Blue","Moto Black","Handwrap Grey Camo", "Handwrap Slaughter" ,"Handwrap Orange Camo" ,"Handwrap Leathery","" };

	CheckBox(Tab_Skinchanger, SkinsEnable, false, 20 + 120 + 10, 60, "Skin Changer"); CheckBox(Tab_Skinchanger, Glove, false, 120 + 120 + 10, 60, "Glove Changer");
	CheckBox(Tab_Skinchanger, Stattrak, false, 220 + 120 + 10, 60, "Stattrak"); EzSlider(290 + 120 + 10, 55, 0, 550, 1337, "", Tab_Skinchanger, StattrakVal,100); EzButton(250 + 20, 260, (DWORD)upp, "Force Update", Tab_Misc);
	ComdoBox(10 + 120 + 10, 90, Tab_Skinchanger, AWP, "AWP SKIN", 19, AWPSKINEZ);
	ComdoBox(10 + 120 + 10, 122, Tab_Skinchanger, SSG08, "SSG-08 SKIN", 15, SSGSKINEZ);
	ComdoBox(10 + 120 + 10, 154, Tab_Skinchanger, SCAR20, "SCAR20 SKIN", 15, SCARSKINEZ);
	ComdoBox(10 + 120 + 10, 186, Tab_Skinchanger, G3SG1, "G3SG1 SKIN", 17, S3SG1SKINEZ);
	ComdoBox(10 + 120 + 10, 218, Tab_Skinchanger, AK47, "AK-47 SKIN", 21, AK47SKINEZ);
	ComdoBox(10 + 120 + 10, 250, Tab_Skinchanger, M4A1, "M4A4 SKIN", 21, M4A1SKINEZ);
	ComdoBox(10 + 120 + 10, 282, Tab_Skinchanger, M4A1S, "M4A1-S SKIN", 17, M4A1SSKINEZ);
	ComdoBox(10 + 120 + 10, 314, Tab_Skinchanger, DUALB, "DUAL BERRETS SKIN", 18, ELITESKINEZ);

	ComdoBox(150 + 120 + 10, 90, Tab_Skinchanger, USP, "USP-S SKIN", 18, USPSKINEZ);
	ComdoBox(150 + 120 + 10, 122, Tab_Skinchanger, Glock18c, "Glock-18 SKIN", 18, GlockSKINEZ);
	ComdoBox(150 + 120 + 10, 154, Tab_Skinchanger, P2000, "P2000 SKIN", 21, P2000SKINEZ);
	ComdoBox(150 + 120 + 10, 186, Tab_Skinchanger, P250, "P250 SKIN", 24, P250SKINEZ);
	ComdoBox(150 + 120 + 10, 218, Tab_Skinchanger, CZ75, "CZ-75 SKIN", 18, CZSKINEZ);
	ComdoBox(150 + 120 + 10, 250, Tab_Skinchanger, Tec9, "TEC-9 SKIN", 21, TEC9SKINEZ);
	ComdoBox(150 + 120 + 10, 282, Tab_Skinchanger, FiveSeven, "Five Seven SKIN", 20, F7SKINEZ);
	ComdoBox(150 + 120 + 10, 314, Tab_Skinchanger, Deagle, "Deagle SKIN", 23, DEAGLESKINEZ);
	
	ComdoBox(290 + 120 + 10, 90, Tab_Skinchanger, FAMAS, "FAMAS SKIN", 14, FAMASSKINEZ);
	ComdoBox(290 + 120 + 10, 122, Tab_Skinchanger, Galil, "Galil SKIN", 19, GALILSKINEZ);
	ComdoBox(290 + 120 + 10, 154, Tab_Skinchanger, MAC10, "MAC-10 SKIN", 19, MACSKINEZ);
	ComdoBox(290 + 120 + 10, 186, Tab_Skinchanger, MP9, "MP-9 SKIN", 17, MP9SKINEZ);
	ComdoBox(290 + 120 + 10, 218, Tab_Skinchanger, MP7, "MP-7 SKIN", 20, MP7SKINEZ);
	ComdoBox(290 + 120 + 10, 250, Tab_Skinchanger, P90, "P90 SKIN", 21, P90SKINEZ);
	ComdoBox(290 + 120 + 10, 282, Tab_Skinchanger, UMP45, "UMP-45 SKIN", 17, UMPSKINEZ);
	ComdoBox(290 + 120 + 10, 314, Tab_Skinchanger, BIZON, "BIZON SKIN", 21, BIZONSKINEZ);

	ComdoBox(450 + 120 + 10, 90, Tab_Skinchanger, AUG, "AUG SKIN", 16, AUGSKINEZ);
	ComdoBox(450 + 120 + 10, 122, Tab_Skinchanger, SG553, "SG-556 SKIN", 18, SGSKINEZ);

	
	ComdoBox(250 + 20, 180, Tab_Misc, GloveModel, "Glove Model", 7, GloveModelSTD);
	ComdoBox(250 + 20, 210, Tab_Misc, GloveSkin, "Glove Skin", 23, GloveSkinSTD);
	/* MISC */
	{
		//AddNewMenuBox( "Miscellaneous", 195, 20, 235, 455, Tab_Misc );
		
			//Dropbox Config
			std::vector< char* > AutoStraferMode = { "Silent", "Silent", "Normal", "Sideways", "W Only" };
			//std::vector<char*> ClanMode = { "Woghook", "Woghook", "Undefeated", "Chefware", "keegan_priv", "ANIME.CHEAT" };
			std::vector< char* > ClanTag = { "FACELESS"};
			
			std::vector< char* > NameSpam = { "Off", "Off", "WANA HVH?", "RevengerColored","AimWare","Project Unknown","InterWebz","" };
			std::vector< char* > Fakelag = { "Off", "Off", "Maximum", "Adaptive", "Switch", "Step", "Random" };
			/*GloveSkin.AddItem("Bloodhound Black"); //0
	GloveSkin.AddItem("Bloodhound Snakeskin"); //1
	GloveSkin.AddItem("Bloodhound Metallic"); //2
	GloveSkin.AddItem("Sporty Purple"); //3
	GloveSkin.AddItem("Sporty Green"); //4
	GloveSkin.AddItem("Sporty Light Blue"); //5
	GloveSkin.AddItem("Sporty Military"); //6
	GloveSkin.AddItem("Slick Black"); //7
	GloveSkin.AddItem("Slick Military"); //8
	GloveSkin.AddItem("Slick Red"); //9
	GloveSkin.AddItem("Specialist DDPAT"); //10
	GloveSkin.AddItem("Specialist Kimono"); //11
	GloveSkin.AddItem("Specialist Emerald"); //12
	GloveSkin.AddItem("Specialist Orange"); //13
	GloveSkin.AddItem("Moto Mint"); //14
	GloveSkin.AddItem("Moto Boom"); //15
	GloveSkin.AddItem("Moto Blue"); //16
	GloveSkin.AddItem("Moto Black"); //17
	GloveSkin.AddItem("Moto Black"); //17
	GloveSkin.AddItem("Handwrap Grey Camo"); //18
	
	GloveSkin.AddItem("Handwrap Slaughter"); //19
	GloveSkin.AddItem("Handwrap Orange Camo"); //20
	GloveSkin.AddItem("Handwrap Leathery"); //21*/
			
			//Controls
			CheckBox(Tab_Misc, Misc_AntiUntrusted, true, 250 + 20, 70, "Anti Untrusted");
			//CheckBox(Tab_Misc, Misc_Bypass, false, 220, 90, "SV_CHEATS");
			CheckBox( Tab_Misc, Misc_AutoJump, true, 120 + 20, 70, "Bunny hop" );
			CheckBox( Tab_Misc, Misc_AutoStrafe, false, 120 + 20, 90, "Auto Strafe" );
			ComdoBox(120 + 20, 110, Tab_Misc, Misc_AutoStraferMode, "", 5, AutoStraferMode );
			ComdoBox( 250 + 20, 240, Tab_Misc, Misc_FakeLag, "Fake Lag", 6, Fakelag );
			//CheckBox( Tab_Misc, Misc_ZStrafe, false, 215, 165, "Z Strafe" );
			//AddNewKeyButton( 390, 165, Tab_Misc, Misc_ZStrafeKey, "" );
			CheckBox( Tab_Misc, Misc_CircleStrafe, false, 120 + 20, 325, "Circle Strafe" );
			AddNewKeyButton(120 + 20, 325, Tab_Misc, Misc_CircleStrafeKey, "" );
			CheckBox( Tab_Misc, Misc_AutoAccept, false, 120 + 20, 135, "Auto Accept" );
			//CheckBox( Tab_Misc, Misc_Aimstep, false, 215, 225, "Aimstep" );
			CheckBox(Tab_Misc, Misc_KnifeBot, true, 250 + 20, 90, "Knifebot");
			CheckBox(Tab_Misc, Misc_DrawMonitor, false, 250 + 20, 110, "Radar");
			EzSlider(250 + 20, 285, 0, 1900, 0, "Radar X", Tab_Misc, Misc_X, 125);
			EzSlider(250 + 20, 310, 0, 1900, 0, "Radar Y", Tab_Misc, Misc_Y, 125);
			std::vector< char* > Sky = { "Sky", "NoSky", "Night", "Night2" };
			CheckBox(Tab_Misc, Visuals_SkyE, false, 250 + 20, 130, "Sky");
			ComdoBox(250 + 20, 150, Tab_Misc, Visuals_Sky, "", 4, Sky);
			//CheckBox(Tab_Misc, Misc_DrawMonitor1, false, 250, 170, "Kills");
		
		//AddNewMenuBox( "Settings", 450, 20, 235, 160, Tab_Misc );
		{
			//Controls
			//CheckBox( Tab_Misc, Misc_AntiUntrusted, true, 470, 70, "Anti Untrusted" );
		}
		//AddNewMenuBox( "Weapon Config", 450, 200, 235, 275, Tab_Misc );
		{
			//Dropbox Config
			std::vector< char* > wgroup = { "Current", "Rifle","Pistol", "Shotgun", "SMG", "Heavy",  "Awp", "Scout", "Other Snipers", "Current" };

			//Controls
			//ComdoBox( 120, 140, Tab_Config, Misc_WhichWeapon, "Weapon Group", 10, wgroup );
		}
	}



	{
		{//Colors

			


			EzSlider(120 + 20, 75, 0, 255, 0, "R ", Tab_Colors, ChamsRCT, 25);
			EzSlider(120 + 20 + 35, 75, 0, 255, 0, "G ", Tab_Colors, ChamsGCT, 25);
			EzSlider(120 + 20 + 35 + 35, 75, 0, 255, 255, "B ", Tab_Colors, ChamsBCT, 25);


			EzSlider(120 + 20, 105, 0, 255, 255, "R ", Tab_Colors, ChamsRT, 25);
			EzSlider(120 + 20 + 35, 105, 0, 255, 0, "G ", Tab_Colors, ChamsGT, 25);
			EzSlider(120 + 20 + 35 + 35, 105, 0, 255, 0, "B ", Tab_Colors, ChamsBT, 25);

			EzSlider(120 + 20, 135, 0, 255, 0, "R ", Tab_Colors, ChamsRCTIN, 25);
			EzSlider(120 + 20 + 35, 135, 0, 255, 0, "G ", Tab_Colors, ChamsGCTIN, 25);
			EzSlider(120 + 20 + 35 + 35, 135, 0, 255, 255, "B ", Tab_Colors, ChamsBCTIN, 25);


			EzSlider(120 + 20, 165, 0, 255, 255, "R", Tab_Colors, ChamsRTIN, 25);
			EzSlider(120 + 20 + 35, 165, 0, 255, 0, "G", Tab_Colors, ChamsGTIN, 25);
			EzSlider(120 + 20 + 35 + 35, 165, 0, 255, 0, "B", Tab_Colors, ChamsBTIN, 25);


			EzSlider(120 + 20, 195, 0, 255, 255, "R", Tab_Colors, MenuStyleR, 25);
			EzSlider(120 + 20 + 35, 195, 0, 255, 0, "G", Tab_Colors, MenuStyleG, 25);
			EzSlider(120 + 20 + 35 + 35, 195, 0, 255, 0, "B", Tab_Colors, MenuStyleB, 25);




		}

	}

	/* Visual */
	{
		//Dropbox Config
		//std::vector<char*> VisBox = { "Frame" ,"Frame", "Alt" };

		//Controls
		CheckBox( Tab_Visuals, Visuals_BoxEnabled, false, 120, 60 + 10, "Box" );
		CheckBox(Tab_Visuals, Visuals_XQZ, false, 120, 80 + 10, "Only Visible");
		CheckBox( Tab_Visuals, Visuals_EspTeam, false, 120, 100 + 10, "Show Team" );
		CheckBox( Tab_Visuals, Visuals_HealthBar, false, 120, 120 + 10, "Show Health Bar" );
		CheckBox( Tab_Visuals, Visuals_ArmorBar, false, 120, 140 + 10, "Show Armor" );
		CheckBox( Tab_Visuals, Visuals_Name, false, 120, 160 + 10, "Show Name" );
		CheckBox( Tab_Visuals, Visuals_Weapons, false, 120, 180 + 10, "Weapons" );
		CheckBox(Tab_Visuals, Visuals_Weaponsic, false, 120, 200 + 10, "Weapons(Icons)");
		CheckBox( Tab_Visuals, Visuals_Flashed, false, 120, 280 + 10, "Flashed" );
		CheckBox(Tab_Visuals, Visuals_Night, false, 120, 300 + 10, "LBY Indicator");

		
		CheckBox( Tab_Visuals, Visuals_AimLines, false, 120, 260 + 10, "Aim Lines" );
		CheckBox( Tab_Visuals, Visuals_Skeltal, false, 120, 240 + 10, "Skeleton" );
		EzSlider(250, 220 + 10 + 20, 0, 80, 0, "ViewFov", Tab_Visuals, Visuals_fov,125);

		//CheckBox( Tab_Visuals, Visuals_Hostage, false, 215, 240, "Hostage" );
		//CheckBox( Tab_Visuals, Visuals_Flags, false, 215, 260, "Flags" );
	}

	
	{
	}
	//AddNewMenuBox( "Chams", 195, 325, 235, 150, Tab_Visuals );
	{

		//Controls
		CheckBox( Tab_Visuals, Visuals_Chams, false, 250, 60 + 10, "Chams" );
		CheckBox(Tab_Visuals, Visuals_ChamsTeam, false, 250, 80 + 10, "Show Team");
		CheckBox( Tab_Visuals, Visuals_ChamsXQZ, false, 250, 100 + 10, "Only visible" );
		//CheckBox( Tab_Visuals, Visuals_ChamsGuns, false, 215, 390, "Dropped Weapons" );
		
	}

	//AddNewMenuBox( "Other ESP", 450, 20, 235, 180, Tab_Visuals );
	{
		//Controls
		CheckBox( Tab_Visuals, Visuals_DroppedWeapons, false, 250, 120 + 10, "Dropped Weapons" );
		//CheckBox( Tab_Visuals, Visuals_Crosshair, false, 120, 280, "Fov" );
		//CheckBox( Tab_Visuals, Visuals_CrosshairDynamic, false, 470, 80, "Crosshair Dynamic" );
		CheckBox( Tab_Visuals, Visuals_C4, false, 250, 140 + 10, "Show Bomb" );
		CheckBox( Tab_Visuals, Visuals_NoScope, false, 250, 160 + 10, "Draw Lines In Scope" );

	}

	//AddNewMenuBox( "Effects", 450, 220, 235, 255, Tab_Visuals );
	{
		//Controls
		CheckBox(Tab_Visuals, Visuals_NoFlash, false, 250, 180 + 10, "No Flash");
		CheckBox(Tab_Visuals, Visuals_NoSmoke, false, 250, 200 + 10, "No Smoke");
		CheckBox( Tab_Visuals, Visuals_NoRecoil, false, 250, 220 + 10, "No Visual Recoil" );
		
	//	CheckBox(Tab_Visuals, Visuals_EnableFOV, true, 350, 50, "Enable Fov ");
	
		//EzSlider(350, 70, 0, 120, 68, "ViewModelFov", Tab_Visuals, Visuals_FovValue);
		CheckBox( Tab_Visuals, Visuals_ThirdPerson, false, 120, 220 + 10, "ThirdPerson" );
	
		
		//CheckBox( Tab_Visuals, Visuals_NoScope, false, 470, 320, "Remove Scope" );
	}

	/* Config */

	//Dropbox Config
	std::vector< char* > ConfigType = { "Default","Legit","Rage","Rage AWP","Rage ELITE" };
	std::vector< char* > ClanTag = { "FACELESS", "FACELESS", "WANNA HVH?"};

	//Controls
	CheckBox(Tab_Misc, Misc_ClanTagSpammer, false, 120 + 20, 235, "Clantag Changer");
	ComdoBox(120 + 20, 215, Tab_Misc, Misc_ClanTagSelection, "", 3, ClanTag);

	CheckBox(Tab_Misc, Misc_ClanTagAnimate, false, 120 + 20, 285, "Animated Clantag");
	EzButton(120 + 20, 305, (DWORD)mine, "Minecraft", Tab_Config);
	AddNewSettingsDropBox(120 + 20, 255, Tab_Config, Config_type, "", 5, ConfigType);
	EzButton( 120 + 20, 155, ( DWORD )LoadSettings, "Load", Tab_Config);
	EzButton( 120 + 20, 175, ( DWORD )SaveSettings, "Save", Tab_Config);
	EzButton(120 + 20, 195, (DWORD)Unhook, "Uninject", Tab_Config);
	
	//EzButton(195, 185, (DWORD)ResetSettings, "Reset", Tab_Config);F
	//EzButton( 370, 300, ( DWORD )Unhook, "Unload DLL", Tab_Config);
}

void DrawLBY()
{
	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && Hacks.LocalPlayer->isAlive())
	{
		float MenuRedStyle = 75;
		float MenuGreenStyle = 75;
		float MenuBlueStyle = 75;
		Interfaces.pSurface->DrawSetColor(28, 28, 28, 255);
		Interfaces.pSurface->DrawFilledRect(Menu.Mpos.x, Menu.Mpos.y, Menu.Mpos.x + 110, Menu.Mpos.y + 30 + 15);


		Interfaces.pSurface->DrawSetColor(MenuRedStyle, MenuGreenStyle, MenuBlueStyle, 255);
		Interfaces.pSurface->DrawFilledRect(Menu.Mpos.x, Menu.Mpos.y, Menu.Mpos.x + 3, Menu.Mpos.y + 30 + 15);
		Interfaces.pSurface->DrawFilledRect(Menu.Mpos.x + 217, Menu.Mpos.y, Menu.Mpos.x + 110, Menu.Mpos.y + 30 + 15);
		Interfaces.pSurface->DrawSetColor(39, 39, 39, 255);
		Interfaces.pSurface->DrawFilledRect(Menu.Mpos.x + 3, Menu.Mpos.y + 2, Menu.Mpos.x + 107, Menu.Mpos.y + 5);
		Interfaces.pSurface->DrawFilledRect(Menu.Mpos.x + 3, Menu.Mpos.y + 345, Menu.Mpos.x + 107, Menu.Mpos.y + 28 + 15);
		if (Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -15 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 15)
		Interfaces.pSurface->DrawT(Menu.Mpos.x + 55, Menu.Mpos.y + 15, CColor(255, 0, 0, 255), Hacks.Font_Watermark, true, "LBY");
		else
		Interfaces.pSurface->DrawT(Menu.Mpos.x + 55, Menu.Mpos.y + 15, CColor(0, 255, 0, 255), Hacks.Font_Watermark, true, "LBY");

		/*if (Settings.GetSettingLegit(Tab_Visuals, Visuals_Night))
		{


			//Interfaces.pSurface->DrawStringY(Hacks.Font_Watermark, 1000, 150, Color::Purple(), FONT_RIGHT, shotslocal.c_str());
			//Interfaces.pSurface->DrawStringY(Hacks.Font_Watermark, 1000, 175, Color::Purple(), FONT_RIGHT, shotsactive.c_str());

			if (Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -15 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 15)
				Interfaces.pSurface->DrawStringY(Hacks.Font_Watermark, 100, 500, Color::Red(), FONT_LEFT, "LBY");
			else
				Interfaces.pSurface->DrawStringY(Hacks.Font_Watermark, 100, 500, Color::Green(), FONT_LEFT, "LBY");

		}*/
	}
}

void DrawMonitor()
{
	float StatVal = Settings.GetSettingLegit(Tab_Misc, Misc_X);
	float StatVal1 = Settings.GetSettingLegit(Tab_Misc, Misc_Y);
	float StatVal2 = Settings.GetSettingLegit(Tab_Misc, Misc_S);
	int W, H;
	Interfaces.pEngine->GetScreenSize(W, H);
	Vector TL(30 + StatVal, 30 + StatVal1, 0);
	Vector TR(TL.x + 200 + StatVal2, TL.y + StatVal2, 0);
	Vector BL(TL.x, TL.y + 200 + StatVal2, 0);
	Vector BR(TL.x + 200 + StatVal2, TL.y + 200 + StatVal2, 0);

	DrawRect(TL.x - 1, TL.y + 1, TL.x + 202 + StatVal2, TL.y + 198 + StatVal2, CColor(5, 5, 5, 255));
	DrawRect(TL.x + 1, TL.y - 1, TL.x + 198 + StatVal2, TL.y + 202 + StatVal2, CColor(5, 5, 5, 255));
	DrawRect(TL.x, TL.y, TL.x + 200 + StatVal2, TL.y + 200 + StatVal2, CColor(5, 5, 5, 255));
	DrawRect(TL.x + 1, TL.y + 1, TL.x + 199 + StatVal2, TL.y + 199 + StatVal2, CColor(32, 34, 36, 255));
	Interfaces.pSurface->DrawSetColor(28, 28, 28, 255);
	Interfaces.pSurface->DrawFilledRect(TL.x + 2, TL.y + 2, TL.x + 198 + StatVal2, TL.y + 198 + StatVal2);

	Interfaces.pSurface->DrawSetColor(75, 75, 75, 255);

	Interfaces.pSurface->DrawLine(TL.x + 50 + StatVal2, TL.y + 50 + StatVal2, TL.x + 100 + StatVal2, TL.y + 100 + StatVal2);
	Interfaces.pSurface->DrawLine(TR.x - 66 + StatVal2, TL.y + 50 + StatVal2, TL.x + 100 + StatVal2, TL.y + 100 + StatVal2);

	Interfaces.pSurface->DrawLine(TL.x + 100 + StatVal2, TL.y + StatVal2, TL.x + 100 + StatVal2, TL.y + 200 + StatVal2);
	Interfaces.pSurface->DrawLine(TL.x + (StatVal2 / 2), TL.y + 100 + (StatVal2 / 2), TL.x + 200 + StatVal2, TL.y + 100 + StatVal2);


	Vector center = Vector((TL.x + TR.x) / 2, (TL.y + BL.y) / 2, 0.f);

	for (int i = 0; i < Interfaces.pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);
		if (pEntity)
		{
			if (!pEntity->isValidPlayer() || Hacks.LocalPlayer->GetIndex() == pEntity->GetIndex())
				continue;
			CColor c = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? CColor(50, 150, 255, 255) : CColor(255, 255, 255, 255);
			Vector relPos = (pEntity->GetAbsOrigin() - Hacks.LocalPlayer->GetAbsOrigin()) * 0.05f;
			relPos.y *= -1.f;
			Vector drawAt = Vector(relPos.x + center.x, relPos.y + center.y, 0);
			Vector localAng;
			Interfaces.pEngine->GetViewAngles(localAng);

			drawAt = g_Math.RotatePoint(drawAt, center, localAng.y - 90);
			if (drawAt.x < TR.x && drawAt.x > TL.x && drawAt.y < BL.y && drawAt.y > TL.y)
				DrawRect(drawAt.x - 1, drawAt.y - 1, drawAt.x + 2, drawAt.y + 2, c);
		}
	}
}

/*void drawnades()
{
	ConVar* granade = Interfaces.g_ICVars->FindVar("sv_grenade_trajectory");
	SpoofedConvar* sv_grenade_trajectory = new SpoofedConvar(granade);
	if (Settings.GetSetting(Tab_Misc, Visuals_Predaction))
	{
		granade->SetValue(1);
	}
	else
	{
		granade->SetValue(0);
	}
}*/

void DrawMenu()
{

	unsigned int Build = Interfaces.pEngine->GetEngineBuildNumber();
	static float rainbow;
	static bool firsttime = true;
	Dont_Click = false;
	if (Settings.GetSetting(Tab_Misc, Misc_DrawMonitor))
		DrawMonitor();
	if (Settings.GetSetting(Tab_Visuals, Visuals_Night))
		DrawLBY();
	/* UPDATE KEYS */
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++)
	{
		keys[x] = (GetAsyncKeyState(x));
	}

	static int Clock = 0;
	if (GlobalMenuAlpha == 0 || GlobalMenuAlpha == 255)
		if (GetKeyPress(VK_INSERT))
		{
			Interfaces.pSurface->LockCursor();
			Clock = 0;
			Menu.Opened = !Menu.Opened;
			std::string msg = "cl_mouseenable " + std::to_string(!Menu.Opened);
			Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
		}

	double timeSoFar1 = (double)Clock / 30.f;
	Clock++;

	if (Menu.Opened)
	{
		GlobalMenuAlpha = min(GlobalMenuAlpha + 6, 255);
		H = min(H + 10, 350);
		if (Tab_Legitbot1 == Menu.GetCurret_Tab())
		{
			W = max(W - 35, 0);
		}
		else
		{
			W = min(W + 35, 410);
		}

	}
	else
	{
		GlobalMenuAlpha = max(GlobalMenuAlpha - 10, 0);
		H = max(H - 10, 0);
	}
	if (firsttime)
	{
		//if(  Build == 13587 )	
		if (Build != 13596)
		{
			SetupMenu();
			firsttime = false;

		}
		else
		{
			Unhook();
		}
	}

	if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		Holding_Mouse_1 = false;
	}
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		Clicked_This_Frame = true;
	}
	else
	{
		Clicked_This_Frame = false;
	}

	Menu.Update_Frame();
	float MenuRedStyle = 75;
	float MenuGreenStyle = 75;
	float MenuBlueStyle = 75;
	//Drawing the menu base
	if (Tab_Legitbot == Menu.GetCurret_Tab())
	{

	}

	if (Tab_Legitbot1 == Menu.GetCurret_Tab())
	{
		Interfaces.pSurface->DrawSetColor(28, 28, 28, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + W, Menu.pos.y + H);
		Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + W, Menu.pos.y + 52);
	}
	if (Tab_Skinchanger == Menu.GetCurret_Tab())
	{
		Interfaces.pSurface->DrawSetColor(28, 28, 28, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + W + 317, Menu.pos.y + H);
		Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + W + 317, Menu.pos.y + 52);
	}
	else
	{
		Interfaces.pSurface->DrawSetColor(28, 28, 28, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + W, Menu.pos.y + H);
		Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + W, Menu.pos.y + 52);
	}
	Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 1, Menu.pos.y - 1, Menu.pos.x + 140, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 2, Menu.pos.y - 2, Menu.pos.x + 138, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 3, Menu.pos.y - 3, Menu.pos.x + 136, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 4, Menu.pos.y - 4, Menu.pos.x + 134, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 5, Menu.pos.y - 5, Menu.pos.x + 132, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 6, Menu.pos.y - 6, Menu.pos.x + 130, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 7, Menu.pos.y - 7, Menu.pos.x + 128, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 8, Menu.pos.y - 8, Menu.pos.x + 126, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 9, Menu.pos.y - 9, Menu.pos.x + 124, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 10, Menu.pos.y - 10, Menu.pos.x + 122, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 11, Menu.pos.y - 11, Menu.pos.x + 120, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 12, Menu.pos.y - 12, Menu.pos.x + 118, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 13, Menu.pos.y - 13, Menu.pos.x + 116, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 14, Menu.pos.y - 14, Menu.pos.x + 114, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 15, Menu.pos.y - 15, Menu.pos.x + 112, Menu.pos.y + 10);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 16, Menu.pos.y - 16, Menu.pos.x + 110, Menu.pos.y + 10);
	Interfaces.pSurface->DrawSetColor(28, 28, 28, GlobalMenuAlpha);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + 142, Menu.pos.y + H);
	Interfaces.pSurface->DrawSetColor(38, 38, 38, GlobalMenuAlpha);
	Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y, Menu.pos.x + 142, Menu.pos.y + 52);

	if (Tab_Legitbot1 == Menu.GetCurret_Tab())
	{

	}

	if (Tab_Colors == Menu.GetCurret_Tab())
	{
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
		float boxr = Settings.GetSettingLegit(Tab_Colors, MenuStyleR);
		float boxg = Settings.GetSettingLegit(Tab_Colors, MenuStyleG);
		float boxb = Settings.GetSettingLegit(Tab_Colors, MenuStyleB);
		Interfaces.pSurface->DrawSetColor(ChamsRed, ChamsGreen, ChamsBlue, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75, Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25 + 15, Menu.pos.y + 75 + 15);
		Interfaces.pSurface->DrawSetColor(ChamsRedT, ChamsGreenT, ChamsBlueT, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 30, Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25 + 15, Menu.pos.y + 30 + 75 + 15);
		Interfaces.pSurface->DrawSetColor(ChamsRedIN, ChamsGreenIN, ChamsBlueIN, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 30 + 30, Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25 + 15, Menu.pos.y + 30 + 30 + 75 + 15);
		Interfaces.pSurface->DrawSetColor(ChamsRedTIN, ChamsGreenTIN, ChamsBlueTIN, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 30 + 30 + 30, Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25 + 15, Menu.pos.y + 30 + 30 + 30 + 75 + 15);
		Interfaces.pSurface->DrawSetColor(boxr, boxg, boxb, GlobalMenuAlpha);
		Interfaces.pSurface->DrawFilledRect(Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 30 + 30 + 30 + 30, Menu.pos.x + 120 + 20 + 35 + 35 + 10 + 25 + 15, Menu.pos.y + 30 + 30 + 30 + 30 + 75 + 15);
		Interfaces.pSurface->DrawT(Menu.pos.x + 120 + 19 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 2, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "Chams CT");
		Interfaces.pSurface->DrawT(Menu.pos.x + 120 + 19 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 2 + 30, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "Chams T");
		Interfaces.pSurface->DrawT(Menu.pos.x + 120 + 19 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 2 + 30 + 30, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "Chams CT invisible");
		Interfaces.pSurface->DrawT(Menu.pos.x + 120 + 19 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 2 + 30 + 30 + 30, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "Chams T invisible");
		Interfaces.pSurface->DrawT(Menu.pos.x + 120 + 19 + 20 + 35 + 35 + 10 + 25, Menu.pos.y + 75 + 2 + 30 + 30 + 30 + 30, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "Box");
	}

	//Interfaces.pSurface->DrawFilledRect(Menu.pos.x, Menu.pos.y , Menu.pos.x , Menu.pos.y);
	Interfaces.pSurface->DrawT(Menu.pos.x + 8, Menu.pos.y + 18, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Watermark, false, "FACELESS");
	if (Tab_Legitbot == Menu.GetCurret_Tab())
	{
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && Hacks.LocalPlayer->isAlive())
		{
			Interfaces.pSurface->DrawT(Menu.pos.x + 270, Menu.pos.y + 150, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Watermark, false, Hacks.LocalWeapon->GetGunIcon());
		}
	}
	if (Menu.Opened)

	for( CTab& Tab : Tabs )
		Tab.Draw();

	for( CMenuBox& MenuBox : MenuBoxs )
		MenuBox.Draw();

	for( CFunctionButton& FuncButton : FuncButtons )
		FuncButton.Draw();

	for( CKeyButton& KeyButton : KeyButtons )
		KeyButton.Draw();

	for( CSlider& slider : Sliders )
		slider.Draw();

	for( CButton& Button : Buttons )
		Button.Draw();
	std::reverse(SettingsDropboxes.begin(), SettingsDropboxes.end());

	for (CSettingsDropBox& SettingsDropbox : SettingsDropboxes)
		SettingsDropbox.Draw();

	std::reverse(SettingsDropboxes.begin(), SettingsDropboxes.end());
	std::reverse( Dropboxes.begin(), Dropboxes.end() );

	for( CDropBox& Dropbox : Dropboxes )
		Dropbox.Draw();

	std::reverse( Dropboxes.begin(), Dropboxes.end() );
	
	if( Menu.Opened )
	{
		
		DrawMouse();
		for( CTab& Tab : Tabs )
			Tab.Update();

		for( CMenuBox& MenuBox : MenuBoxs )
			MenuBox.Update();

		for (CSettingsDropBox& SettingsDropbox : SettingsDropboxes)
			SettingsDropbox.Update();

		for( CDropBox& Dropbox : Dropboxes )
			Dropbox.Update();

		for( CSlider& slider : Sliders )
			slider.Update();

		for( CButton& Button : Buttons )
			Button.Update();

		for( CKeyButton& KeyButton : KeyButtons )
			KeyButton.Update();

		for( CFunctionButton& FuncButton : FuncButtons )
			FuncButton.Update();
	}
	if( Clicked_This_Frame )
	{
		Holding_Mouse_1 = true;
	}
}
