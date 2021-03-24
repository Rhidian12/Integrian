#pragma once
#ifndef INTEGRIAN_POSSIBLEINPUTS_H
#define INTEGRIAN_POSSIBLEINPUTS_H

#include "pch.h"
#include "Logger.h"

// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// Do NOT auto-reformat this file
// Rhidian
// Don't
// I swear to god I'll kill you
// ~ Rhidian
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!

namespace Integrian
{
	//enum class PossibleInputs
	//{
	//	LMB,
	//	MMB,
	//	RMB,
	//	LMBAndRMB,
	//	LMBAndMMB,
	//	RMBandMMB,
	//	A = SDL_SCANCODE_A,
	//	B = SDL_SCANCODE_B,
	//	C = SDL_SCANCODE_C,
	//	D = SDL_SCANCODE_D,
	//	E = SDL_SCANCODE_E,
	//	F = SDL_SCANCODE_F,
	//	G = SDL_SCANCODE_G,
	//	H = SDL_SCANCODE_H,
	//	I = SDL_SCANCODE_I,
	//	J = SDL_SCANCODE_J,
	//	K = SDL_SCANCODE_K,
	//	L = SDL_SCANCODE_L,
	//	M = SDL_SCANCODE_M,
	//	N = SDL_SCANCODE_N,
	//	O = SDL_SCANCODE_O,
	//	P = SDL_SCANCODE_P,
	//	Q = SDL_SCANCODE_Q,
	//	R = SDL_SCANCODE_R,
	//	S = SDL_SCANCODE_S,
	//	T = SDL_SCANCODE_T,
	//	U = SDL_SCANCODE_U,
	//	V = SDL_SCANCODE_V,
	//	W = SDL_SCANCODE_W,
	//	X = SDL_SCANCODE_X,
	//	Y = SDL_SCANCODE_Y,
	//	Z = SDL_SCANCODE_Z,
	//	Keyboard_0 = SDL_SCANCODE_0,
	//	Keyboard_1 = SDL_SCANCODE_1,
	//	Keyboard_2 = SDL_SCANCODE_2,
	//	Keyboard_3 = SDL_SCANCODE_3,
	//	Keyboard_4 = SDL_SCANCODE_4,
	//	Keyboard_5 = SDL_SCANCODE_5,
	//	Keyboard_6 = SDL_SCANCODE_6,
	//	Keyboard_7 = SDL_SCANCODE_7,
	//	Keyboard_8 = SDL_SCANCODE_8,
	//	Keyboard_9 = SDL_SCANCODE_9,
	//	Keypad_0 = SDL_SCANCODE_KP_0,
	//	Keypad_1 = SDL_SCANCODE_KP_1,
	//	Keypad_2 = SDL_SCANCODE_KP_2,
	//	Keypad_3 = SDL_SCANCODE_KP_3,
	//	Keypad_4 = SDL_SCANCODE_KP_4,
	//	Keypad_5 = SDL_SCANCODE_KP_5,
	//	Keypad_6 = SDL_SCANCODE_KP_6,
	//	Keypad_7 = SDL_SCANCODE_KP_7,
	//	Keypad_8 = SDL_SCANCODE_KP_8,
	//	Keypad_9 = SDL_SCANCODE_KP_9,
	//	F1 = SDL_SCANCODE_F1,
	//	F2 = SDL_SCANCODE_F2,
	//	F3 = SDL_SCANCODE_F3,
	//	F4 = SDL_SCANCODE_F4,
	//	F5 = SDL_SCANCODE_F5,
	//	F6 = SDL_SCANCODE_F6,
	//	F7 = SDL_SCANCODE_F7,
	//	F8 = SDL_SCANCODE_F8,
	//	F9 = SDL_SCANCODE_F9,
	//	F10 = SDL_SCANCODE_F10,
	//	F11 = SDL_SCANCODE_F11,
	//	F12 = SDL_SCANCODE_F12,
	//	ButtonA = SDL_CONTROLLER_BUTTON_A,
	//	ButtonB = SDL_CONTROLLER_BUTTON_B,
	//	ButtonX = SDL_CONTROLLER_BUTTON_X,
	//	ButtonY = SDL_CONTROLLER_BUTTON_Y,
	//	DPadUp = SDL_CONTROLLER_BUTTON_DPAD_UP,
	//	DPadLeft = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
	//	DPadRight = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	//	DPadDown = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
	//	Start = SDL_CONTROLLER_BUTTON_START,
	//	Select = SDL_CONTROLLER_BUTTON_BACK,
	//	LeftThumbStick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
	//	RightThumbStick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
	//	LeftShoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
	//	RightShoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
	//	LeftTrigger,
	//	RightTrigger
	//};

	enum class MouseButton : Uint8
	{
		//#define SDL_BUTTON(X)       (1 << ((X)-1))
		//#define SDL_BUTTON_LEFT     1
		//#define SDL_BUTTON_MIDDLE   2
		//#define SDL_BUTTON_RIGHT    3
		// 0000 0001 << ((1) - 1) ===> 0000 0001 << (0) ===> 0000 0001		// SDL_BUTTON(SDL_BUTTON_LEFT) == 1
		// 0000 0001 << ((2) - 1) ===> 0000 0001 << (1) ===> 0000 0010		// SDL_BUTTON(SDL_BUTTON_MIDDLE) == 2
		// 0000 0001 << ((3) - 1) ===> 0000 0001 << (2) ===> 0000 0100		// SDL_BUTTON(SDL_BUTTON_RIGHT) == 4
		INVALID		= std::numeric_limits<Uint8>::max(), // internal usage
		LMB			= SDL_BUTTON(SDL_BUTTON_LEFT), // 0x0001 
		MMB			= SDL_BUTTON(SDL_BUTTON_MIDDLE), // 0x0002
		RMB			= SDL_BUTTON(SDL_BUTTON_RIGHT), // 0x0004
		LMBAndMMB	= SDL_BUTTON(SDL_BUTTON_LEFT)	| SDL_BUTTON(SDL_BUTTON_MIDDLE), // 0x0003
		LMBAndRMB	= SDL_BUTTON(SDL_BUTTON_LEFT)	| SDL_BUTTON(SDL_BUTTON_RIGHT), // 0x0005
		RMBandMMB	= SDL_BUTTON(SDL_BUTTON_RIGHT)	| SDL_BUTTON(SDL_BUTTON_MIDDLE), // 0x0006
	};

	enum class KeyboardInput : Uint8
	{
		INVALID				= std::numeric_limits<Uint8>::max(), // internal usage
		A					= SDL_SCANCODE_A,
		B					= SDL_SCANCODE_B,
		C					= SDL_SCANCODE_C,
		D					= SDL_SCANCODE_D,
		E					= SDL_SCANCODE_E,
		F					= SDL_SCANCODE_F,
		G					= SDL_SCANCODE_G,
		H					= SDL_SCANCODE_H,
		I					= SDL_SCANCODE_I,
		J					= SDL_SCANCODE_J,
		K					= SDL_SCANCODE_K,
		L					= SDL_SCANCODE_L,
		M					= SDL_SCANCODE_M,
		N					= SDL_SCANCODE_N,
		O					= SDL_SCANCODE_O,
		P					= SDL_SCANCODE_P,
		Q					= SDL_SCANCODE_Q,
		R					= SDL_SCANCODE_R,
		S					= SDL_SCANCODE_S,
		T					= SDL_SCANCODE_T,
		U					= SDL_SCANCODE_U,
		V					= SDL_SCANCODE_V,
		W					= SDL_SCANCODE_W,
		X					= SDL_SCANCODE_X,
		Y					= SDL_SCANCODE_Y,
		Z					= SDL_SCANCODE_Z,
		Keyboard_0			= SDL_SCANCODE_0,
		Keyboard_1			= SDL_SCANCODE_1,
		Keyboard_2			= SDL_SCANCODE_2,
		Keyboard_3			= SDL_SCANCODE_3,
		Keyboard_4			= SDL_SCANCODE_4,
		Keyboard_5			= SDL_SCANCODE_5,
		Keyboard_6			= SDL_SCANCODE_6,
		Keyboard_7			= SDL_SCANCODE_7,
		Keyboard_8			= SDL_SCANCODE_8,
		Keyboard_9			= SDL_SCANCODE_9,
		Keypad_0			= SDL_SCANCODE_KP_0,
		Keypad_1			= SDL_SCANCODE_KP_1,
		Keypad_2			= SDL_SCANCODE_KP_2,
		Keypad_3			= SDL_SCANCODE_KP_3,
		Keypad_4			= SDL_SCANCODE_KP_4,
		Keypad_5			= SDL_SCANCODE_KP_5,
		Keypad_6			= SDL_SCANCODE_KP_6,
		Keypad_7			= SDL_SCANCODE_KP_7,
		Keypad_8			= SDL_SCANCODE_KP_8,
		Keypad_9			= SDL_SCANCODE_KP_9,
		F1					= SDL_SCANCODE_F1,
		F2					= SDL_SCANCODE_F2,
		F3					= SDL_SCANCODE_F3,
		F4					= SDL_SCANCODE_F4,
		F5					= SDL_SCANCODE_F5,
		F6					= SDL_SCANCODE_F6,
		F7					= SDL_SCANCODE_F7,
		F8					= SDL_SCANCODE_F8,
		F9					= SDL_SCANCODE_F9,
		F10					= SDL_SCANCODE_F10,
		F11					= SDL_SCANCODE_F11,
		F12					= SDL_SCANCODE_F12,
		Space				= SDL_SCANCODE_SPACE,
		Escape				= SDL_SCANCODE_ESCAPE,
		Enter				= SDL_SCANCODE_RETURN,
		Backspace			= SDL_SCANCODE_BACKSPACE,
		Tab					= SDL_SCANCODE_TAB,
		Minus				= SDL_SCANCODE_MINUS,
		Equals				= SDL_SCANCODE_EQUALS,
		Leftbracket			= SDL_SCANCODE_LEFTBRACKET,
		Rightbracket		= SDL_SCANCODE_RIGHTBRACKET,
		Backslash			= SDL_SCANCODE_BACKSLASH,
		Semicolon			= SDL_SCANCODE_SEMICOLON,
		Apostrophe			= SDL_SCANCODE_APOSTROPHE,
		Comma				= SDL_SCANCODE_COMMA,
		Slash				= SDL_SCANCODE_SLASH,
		Capslock			= SDL_SCANCODE_CAPSLOCK,
		Printscreen			= SDL_SCANCODE_PRINTSCREEN,
		Scrolllock			= SDL_SCANCODE_SCROLLLOCK,
		Keypad_Enter		= SDL_SCANCODE_KP_ENTER
	};

	enum class ControllerInput : Uint8
	{
		INVALID						= std::numeric_limits<Uint8>::max(), // internal usage
		ButtonA						= SDL_CONTROLLER_BUTTON_A,
		ButtonB						= SDL_CONTROLLER_BUTTON_B,
		ButtonX						= SDL_CONTROLLER_BUTTON_X,
		ButtonY						= SDL_CONTROLLER_BUTTON_Y,
		Back						= SDL_CONTROLLER_BUTTON_BACK,
		Start						= SDL_CONTROLLER_BUTTON_START,
		LeftStickPressed			= SDL_CONTROLLER_BUTTON_LEFTSTICK,
		RightStickPressed			= SDL_CONTROLLER_BUTTON_RIGHTSTICK,
		LeftShoulder				= SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		RightShoulder				= SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
		DPAD_Up						= SDL_CONTROLLER_BUTTON_DPAD_UP,
		DPAD_Down					= SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		DPAD_Left					= SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		DPAD_Right					= SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
		JoystickLeftHorizontalAxis	= SDL_CONTROLLER_AXIS_LEFTX,
		JoystickLeftVerticalAxis	= SDL_CONTROLLER_AXIS_LEFTY,
		JoystickRightHorizontalAxis = SDL_CONTROLLER_AXIS_RIGHTX,
		JoystickRightVerticalAxis	= SDL_CONTROLLER_AXIS_RIGHTY,
		LeftTrigger					= SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		RightTrigger				= SDL_CONTROLLER_AXIS_TRIGGERRIGHT
	};
}

#endif // INTEGRIAN_POSSIBLEINPUTS_H