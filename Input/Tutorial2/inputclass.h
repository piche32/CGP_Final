#pragma once
#ifndef _INPUTCLASS_H_ 
#define _INPUTCLASS_H_ 

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputClass {

public:
	InputClass(); 
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	// void Initialize();
	void Shutdown();
	bool Frame();

	//bool IsEscapePressed();
	void GetMouseLocation(int&, int&);

private:
	//bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput = nullptr;
	//IDirectInputDevice8* m_keyboard = nullptr;
	IDirectInputDevice8* m_mouse = nullptr;

	//unsigned char m_keyboardState[256] = { 0, };
	DIMOUSESTATE m_mouseState, mouseLastState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;

public:
	void KeyDown(unsigned int); 
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

	int getScreenHeight();
	int getScreenWidth();

	void isMouseMove(float&, float&);

private:
	bool m_keys[256];

};

#endif