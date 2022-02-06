#pragma once

#include "../../other/util/version.hpp"
#include "../../other/memory/memory.hpp"
#include <algorithm>

class c_symbol
{
public:

	const char* base( )
	{
		return reinterpret_cast<const char*>( reinterpret_cast< size_t >( this ) + ( c_version::is_lunar( ) ? 0x6 : 0x8 ) );
	}

	unsigned short length( )
	{
		return c_memory::offset<unsigned short>( this, c_version::is_lunar( ) ? 0x4 : 0x0 );
	}

	std::string to_string( )
	{
		const auto base = this->base( );
		return std::string( base, this->length( ) );
	}

	const char* c_str( )
	{
		auto buf = new char[ this->length( ) + 1 ]{ 0 };
		std::copy_n( this->base( ), this->length( ), buf );
		return buf;
	}
};