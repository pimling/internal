#pragma once

#include "array.hpp"
#include "constantpool.hpp"

class c_constmethod
{
public:
	size_t m_fingerprint;
	c_constantpool* m_constants;

	unsigned short name_index( )
	{
		return c_memory::offset<unsigned short>( this, c_version::is_lunar( ) ? 0x2a : 0x20 );
	}

	unsigned short sig_index( )
	{
		return c_memory::offset<unsigned short>( this, c_version::is_lunar( ) ? 0x2C : 0x22 );
	}
};

class c_method
{
	void* m_vtable;
	c_constmethod* m_constmethod;

public:
	c_symbol* name( )
	{
		return m_constmethod->m_constants->at<c_symbol*>( this->m_constmethod->name_index( ) );
	}

	c_symbol* signature( )
	{
		return m_constmethod->m_constants->at<c_symbol*>( this->m_constmethod->sig_index( ) );
	}

	c_constantpool* constantpool( )
	{
		return this->m_constmethod->m_constants;
	}
};