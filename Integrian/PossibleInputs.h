#pragma once
#ifndef INTEGRIAN_POSSIBLEINPUTS_H
#define INTEGRIAN_POSSIBLEINPUTS_H

#include "pch.h"
#include "Logger.h"

enum class PossibleInputs
{
	LMB			= 0,
	MMB			= 1,
	RMB			= 2,
	LMBAndRMB	= 3,
	LMBAndMMB	= 4,
	RMBandMMB	= 5,
	A			= 6,
	B			= 7,
	C			= 8,
	D			= 9,
	E			= 10,
	F			= 11,
	G			= 12,
	H			= 13,
	I			= 14,
	J			= 15,
	K			= 16,
	L			= 17,
	M			= 18,
	N			= 19,
	O			= 20,
	P			= 21,
	Q			= 22,
	R			= 23,
	S			= 24,
	T			= 25,
	U			= 26,
	V			= 27,
	W			= 28,
	X			= 29,
	Y			= 30,
	Z			= 31,
};

inline SDL_Scancode GetSDLScancode(const PossibleInputs input)
{
	switch(input)
	{
		case PossibleInputs::A:
			return SDL_SCANCODE_A;
			break;
		case PossibleInputs::B:
			return SDL_SCANCODE_B;
			break;
		case PossibleInputs::C:
			return SDL_SCANCODE_C;
			break;
		case PossibleInputs::D:
			return SDL_SCANCODE_D;
			break;
		case PossibleInputs::E:
			return SDL_SCANCODE_E;
			break;
		case PossibleInputs::F:
			return SDL_SCANCODE_F;
			break;
		case PossibleInputs::G:
			return SDL_SCANCODE_G;
			break;
		case PossibleInputs::H:
			return SDL_SCANCODE_H;
			break;
		case PossibleInputs::I:
			return SDL_SCANCODE_I;
			break;
		case PossibleInputs::J:
			return SDL_SCANCODE_J;
			break;
		case PossibleInputs::K:
			return SDL_SCANCODE_K;
			break;
		case PossibleInputs::L:
			return SDL_SCANCODE_L;
			break;
		case PossibleInputs::M:
			return SDL_SCANCODE_M;
			break;
		case PossibleInputs::N:
			return SDL_SCANCODE_N;
			break;
		case PossibleInputs::O:
			return SDL_SCANCODE_O;
			break;
		case PossibleInputs::P:
			return SDL_SCANCODE_P;
			break;
		case PossibleInputs::Q:
			return SDL_SCANCODE_Q;
			break;
		case PossibleInputs::R:
			return SDL_SCANCODE_R;
			break;
		case PossibleInputs::S:
			return SDL_SCANCODE_S;
			break;
		case PossibleInputs::T:
			return SDL_SCANCODE_T;
			break;
		case PossibleInputs::U:
			return SDL_SCANCODE_U;
			break;
		case PossibleInputs::V:
			return SDL_SCANCODE_V;
			break;
		case PossibleInputs::W:
			return SDL_SCANCODE_W;
			break;
		case PossibleInputs::X:
			return SDL_SCANCODE_X;
			break;
		case PossibleInputs::Y:
			return SDL_SCANCODE_Y;
			break;
		case PossibleInputs::Z:
			return SDL_SCANCODE_Z;
			break;
		default:
			Integrian::Logger::GetInstance().Log("PossibleInput (keyboard) was not recognized!", ErrorLevel::error);
			return SDL_SCANCODE_UNKNOWN;
			break;
	}
}

#endif // INTEGRIAN_POSSIBLEINPUTS_H