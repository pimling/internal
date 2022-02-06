#pragma once

#include <array>
#include <windows.h>
#include <string>

#include "lazy.hpp"
#include "xors.hpp"
#include "../../game/modules/modules.hpp"

class c_version
{
public:
	static bool is_lunar( )
	{
		static auto res = 2;

		if ( res != 2 )
			return res;

		auto path = std::array<char, MAX_PATH>( );
		const auto jvm_dll = reinterpret_cast<HMODULE>( c_modules::m_jvm->base( ) );
		LI_FN( GetModuleFileNameA )( jvm_dll, path.data( ), static_cast< DWORD >( path.size( ) ) );

		res = std::string( path.data( ) ).find( xors( "zulu" ) ) != std::string::npos;

		return res;
	}
};