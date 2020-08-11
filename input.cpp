
#include "main.h"
#include "input.h"


BYTE Input::mOldKeyState[256];
BYTE Input::mKeyState[256];


void Input::Init()
{

	memset( mOldKeyState, 0, 256 );
	memset( mKeyState, 0, 256 );

}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy( mOldKeyState, mKeyState, 256 );

	GetKeyboardState( mKeyState );

}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (mKeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((mKeyState[KeyCode] & 0x80) && !(mOldKeyState[KeyCode] & 0x80));
}
