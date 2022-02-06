#pragma once

#include "../../other/memory/memory.hpp"
#include "../../other/util/version.hpp"
#include "symbol.hpp"
#include "array.hpp"
#include "method.hpp"

class c_instanceklass
{
public:
	bool is_instance( )
	{
		return c_memory::offset<int>( this, 0x8 ) > 0;
	}

	c_instanceklass* next_link( )
	{
		return c_memory::offset<c_instanceklass*>( this, 0x88 );
	}

	c_symbol* name( )
	{
		return c_memory::offset<c_symbol*>( this, c_version::is_lunar( ) ? 0x18 : 0x10 );
	}

	size_t mirror( )
	{
		return c_memory::offset<size_t>( this, c_version::is_lunar( ) ? 0x68 : 0x60 );
	}

	c_array<c_method*>* methods( )
	{
		return c_memory::offset<c_array<c_method*>*>( this, c_version::is_lunar( ) ? 0x190 : 0x180 );
	}
};