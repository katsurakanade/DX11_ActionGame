#include "main.h"
#include "input.h"

LPDIRECTINPUT8 Input::mInput;
LPDIRECTINPUTDEVICE8 Input::DevKeyboard;
BYTE Input::mOldKeyState[NUM_KEY_MAX];
BYTE Input::mKeyState[NUM_KEY_MAX];
BYTE Input::mKeyStateRelease[NUM_KEY_MAX];

void Input::Init()
{

	DirectInput8Create(GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInput, NULL);

	mInput->CreateDevice(GUID_SysKeyboard, &DevKeyboard, NULL);
	DevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	DevKeyboard->SetCooperativeLevel(GetWindow(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	DevKeyboard->Acquire();

}

void Input::Uninit()
{
	if (mInput != nullptr) {
		mInput->Release();
		mInput = nullptr;
	}

	if (DevKeyboard != NULL)
	{
		DevKeyboard->Unacquire();
		DevKeyboard->Release();
		DevKeyboard = NULL;
	}
}

void Input::Update()
{


	BYTE aKeyState[NUM_KEY_MAX];

	if (SUCCEEDED(DevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			mOldKeyState[nCnKey] = (mKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			mKeyStateRelease[nCnKey] = (mKeyState[nCnKey] ^ aKeyState[nCnKey]) & mKeyState[nCnKey];

			mKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		DevKeyboard->Acquire();
	}
}

bool Input::GetKeyPress(int Keycode)
{

	return (mKeyState[Keycode] & 0x80) ? true : false;
}

bool Input::GetKeyTrigger(int Keycode)
{

	return (mOldKeyState[Keycode] & 0x80) ? true : false;
}

bool Input::GetKeyRelease(int nKey)
{
	return (mKeyStateRelease[nKey] & 0x80) ? true : false;
}