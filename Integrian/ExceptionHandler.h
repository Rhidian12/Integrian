#pragma once
// This class was taken from the book
// The C++ Standard Library Second Edition: A Tutorial and Reference
// Author: Nicolai M. Josuttis
// pages 50-51
// it has been VERY slightly adjusted for this framework, however most of the class has been taken from the book
#ifndef ENGINE_EXCEPTION_HANDLER_H
#define ENGINE_EXCEPTION_HANDLER_H

// All Custom exceptions
#include "InitialisationFailed.h"
#include "RuntimeInitFailed.h"
#include "CameraInitialisationFailed.h"
#include "StaticInstanceAlreadyCreated.h"
#include "MagnitudeZeroException.h"
#include "MatrixDivisionNotPossibleException.h"
#include "DivisionByZeroNotPossibleException.h"

#include <exception> // std::exception
#include <system_error> // std::system_error
#include <future> // std::async
#include <iostream> // std::cout

namespace Integrian
{
	class ExceptionHandler
	{
	public:
		inline void ProcessException()
		{
			try
			{
				throw; // rethrow exception
			}
			catch (const std::ios_base::failure& e)
			{
				std::cerr << "I/O EXCEPTION: " << e.what() << std::endl;
				ProcessCodeException(e);
			}
			catch (const std::system_error& e)
			{
				std::cerr << "SYSTEM EXCEPTION: " << e.what() << std::endl;
				ProcessCodeException(e);
			}
			catch (const std::future_error& e)
			{
				std::cerr << "FUTURE EXCEPTION: " << e.what() << std::endl;
				ProcessCodeException(e);
			}
			catch (const std::bad_alloc& e)
			{
				std::cerr << "BAD ALLOC EXCEPTION: " << e.what() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cerr << "EXCEPTION: " << e.what() << std::endl;
			}
			catch (const Integrian::InitialisationFailedException&)
			{}
			catch (const Integrian::RuntimeInitialisationFailed&)
			{}
			catch (const Integrian::CameraInitialisationFailedException&)
			{}
			catch (const Integrian::StaticInstanceAlreadyCreated&)
			{}
			catch (const Integrian::MagnitudeZeroException&)
			{}
			catch (const Integrian::MatrixDivisionNotPossibleException&)
			{}
			catch(const Integrian::DivisionByZeroNotPossible&)
			{}
			catch (...)
			{
				std::cerr << "EXCEPTION (unknown)" << std::endl;
			}
		}

	private:
		template<typename T>
		inline void ProcessCodeException(const T& e)
		{
			auto c = e.code();
			std::cerr << "- category:     " << c.category().name() << std::endl;
			std::cerr << "- value:        " << c.value() << std::endl;
			std::cerr << "- msg:          " << c.message() << std::endl;
			std::cerr << "- def category: " << c.default_error_condition().category().name() << std::endl;
			std::cerr << "- def value:    " << c.default_error_condition().value() << std::endl;
			std::cerr << "- def msg:      " << c.default_error_condition().message() << std::endl;
		}
	};
}

#endif // !ENGINE_EXCEPTION_HANDLER_H