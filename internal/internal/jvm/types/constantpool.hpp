#pragma once

#include "array.hpp"
#include "../../other/memory/memory.hpp"

#include <iostream>

class c_constantpool
{
public:
	c_array<unsigned char>* tags( )
	{
		return c_memory::offset<c_array<unsigned char>*>( this, 0x8 );
	}

	size_t* base( )
	{
		return reinterpret_cast< size_t* >( reinterpret_cast< size_t >( this ) + ( c_version::is_lunar( ) ? 0x48 : 0x50 ) );
	}

	template<typename T>
	T* at_addr( const size_t index )
	{
		return reinterpret_cast< T* >( &this->base( )[ index ] );
	}

	template<typename T>
	T at( const size_t index )
	{
		return *this->at_addr<T>( index );
	}
};