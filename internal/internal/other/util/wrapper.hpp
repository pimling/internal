#pragma once

#include <Windows.h>

#include "lazy.hpp"

class c_wrapper
{
public:
	template<typename T, typename K>
	static HANDLE create_thread( T func, K arg )
	{
		return LI_FN( CreateThread )( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( func ), reinterpret_cast< LPVOID >( arg ), 0, nullptr );
	}

	static void close_handle( const HANDLE handle )
	{
		LI_FN( CloseHandle )( handle );
	}

	static void free_library( const HMODULE module )
	{
		LI_FN( FreeLibraryAndExitThread )( module, EXIT_SUCCESS );
	}
};