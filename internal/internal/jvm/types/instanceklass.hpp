#pragma once

#include "../../other/memory/memory.hpp"
#include "../../other/util/version.hpp"
#include "symbol.hpp"
#include "array.hpp"
#include "method.hpp"
#include "fielddescriptor.hpp"

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

	c_constantpool* constants( )
	{
		return c_memory::offset<c_constantpool*>( this, c_version::is_lunar( ) ? 0xe0 : 0xd8 );
	}

	c_array<c_instanceklass*>* interfaces( )
	{
		return c_memory::offset<c_array<c_instanceklass*>*>( this, c_version::is_lunar( ) ? 0x1A0 : 0x190 );
	}

	c_array<unsigned short>* fields( )
	{
		return c_memory::offset<c_array<unsigned short>*>( this, c_version::is_lunar( ) ? 0x1C0 : 0x1B0 );
	}
	 
	c_instanceklass* find_field( c_symbol* name, c_symbol* sig, c_fielddescriptor* fd )
	{
		/*
			for ( auto i = 0; i < this->fields_count( ); i++ )
			{
				auto field = c_fieldinfo::from_field_array( this->fields );
				if ( field->name( )->to_string( ) == name->to_string( ) )
				{
					// set fd to correct values
					return this;
				}
			}

			// loop through interfaces
			// loop through supers
		*/
	}
};