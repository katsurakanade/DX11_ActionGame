/*
インプットクラス
*/
#pragma once

#define	NUM_KEY_MAX	(256)
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

class Input
{
private:

	// インスタンス
	static LPDIRECTINPUT8 mInput;
	static LPDIRECTINPUTDEVICE8 DevKeyboard;
	// 状態
	static BYTE mOldKeyState[NUM_KEY_MAX];
	static BYTE mKeyState[NUM_KEY_MAX];
	static BYTE mKeyStateRelease[NUM_KEY_MAX];

public:

	static void Init();
	static void Uninit();
	static void Update();

	// Getter
	static bool GetKeyPress( int Keycode);
	static bool GetKeyTrigger(int Keycode);
	static bool GetKeyRelease(int nKey);

};
