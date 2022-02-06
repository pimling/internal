#pragma once

#include "../../other/module/module.hpp"

class c_modules
{
public:
	inline static c_module* m_lwjgl = nullptr;
	inline static c_module* m_jvm = nullptr;

	static bool init( );
};