#pragma once


class Input
{
private:
	static BYTE mOldKeyState[256];
	static BYTE mKeyState[256];

public:

	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

};
