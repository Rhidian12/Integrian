#pragma once
#ifndef INTEGRIAN_MATRIX_H
#define INTEGRIAN_MATRIX_H

namespace Integrian
{
	template<int Size, typename Type>
	struct Matrix // I wish I could do this with Unique Pointers, but that will make copying a matrix practically impossible
	{
		Type (*matrix)[Size]{ new Type[Size][Size] }; // we always want to create a matrix of Size x Size

		~Matrix()
		{
			delete[] matrix;
		}
	};
}

#endif // INTEGRIAN_MATRIX_H