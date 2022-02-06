#pragma once

#include <vector>
#include <unordered_map>

class c_module
{
	size_t m_base;
	size_t m_size;
	std::unordered_map<size_t, size_t> m_exports{ };

public:
	c_module( );
	c_module( const size_t base );

	constexpr size_t base( )
	{
		return this->m_base;
	}

	constexpr size_t size( ) 
	{
		return this->m_size;
	}

	size_t get_export( const size_t hash );
	size_t pattern_scan( const std::vector<unsigned char>& pattern );
};