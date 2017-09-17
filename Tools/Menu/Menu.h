
#pragma once

void DrawMenu();

struct MenuPOS
{
	long x = 0, y = 0;
};

class CMenu
{
public:
	MenuPOS pos;
	MenuPOS Mpos;
	void Set_Current_Tab( int tab );
	void Set_Current_SubTab(int tab);
	int GetCurret_Tab();

	void Update_Frame();
	int GetCurret_SubTab();
	bool Opened = false;
private:
	int Current_tab = 0;
	int Current_Subtab = 0;
	bool GetClicked();
	bool GetClickedM();
};

extern CMenu Menu;

bool GetKeyPress( unsigned int key );

