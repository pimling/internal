#pragma once

#include <windows.h>

class c_cheat
{
public:
	inline static HMODULE m_module;

	static void __stdcall start( const HMODULE module );
};