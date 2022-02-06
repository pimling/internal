#pragma once

#include <unordered_map>

#include "../module/module.hpp"

class c_peb
{
	inline static std::unordered_map<size_t, c_module> m_modules{ };

public:
	static bool init( );

	static c_module* get_module( const size_t hash );
};