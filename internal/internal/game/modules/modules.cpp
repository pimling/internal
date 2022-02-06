#include "modules.hpp"
#include "../../other/peb/peb.hpp"
#include "../../other/hash/hash.hpp"

bool c_modules::init( )
{
	if ( !( m_lwjgl = c_peb::get_module( hashxor( "lwjgl64.dll" ) ) ) )
		return false;
	
	if ( !( m_jvm = c_peb::get_module( hashxor( "jvm.dll" ) ) ) )
		return false;

	return true;
}
