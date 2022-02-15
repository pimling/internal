#include "minecraft.hpp"

c_minecraft::c_minecraft( c_instanceklass* mc_class )
	: m_class( mc_class )
{
}

c_minecraft c_minecraft::get( )
{
	return c_minecraft{ c_jvm::m_mc_class };
}
