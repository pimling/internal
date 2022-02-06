#pragma once

#include <vector>

class c_memory
{
public:
	static size_t get_module_size( const size_t module );
	static size_t pattern_scan( const size_t module, const std::vector<unsigned char>& pattern );
	
	template<typename T, typename K>
	static T offset( K base, const size_t offset )
	{
		return *reinterpret_cast< T* >( reinterpret_cast< size_t >( base ) + offset );
	}
};