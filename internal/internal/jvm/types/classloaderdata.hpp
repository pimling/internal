#pragma once

#include "../../other/util/version.hpp"
#include "../../other/memory/memory.hpp"
#include "instanceklass.hpp"

class c_classloaderdata;

class c_classloaderdatagraph
{
public:
	inline static c_classloaderdata* m_head = nullptr;
};

class c_classloaderdata
{
public:
	c_instanceklass* klass( )
	{
		return c_memory::offset<c_instanceklass*>( this, c_version::is_lunar( ) ? 0x38 : 0x28 );
	}

	c_classloaderdata* next( )
	{
		return c_memory::offset<c_classloaderdata*>( this, c_version::is_lunar( ) ? 0x70 : 0x48 );
	}
};