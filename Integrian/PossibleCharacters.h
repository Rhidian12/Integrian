#pragma once
#ifndef INTEGRIAN_POSSIBLE_CHARACTERS_H
#define INTEGRIAN_POSSIBLE_CHARACTERS_H

#include <string>

namespace Integrian
{
	struct PossibleCharacters
	{
		// ReSharper disable once StringLiteralTypo
		inline static const std::string possibleChars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?!: \n" };
		inline static uint32_t sizeOfPossibleChars{ uint32_t(possibleChars.size()) };
	};
}

#endif