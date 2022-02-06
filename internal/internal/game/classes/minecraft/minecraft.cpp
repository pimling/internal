#include "minecraft.hpp"

c_minecraft::c_minecraft( c_instanceklass* mc_class )
{
	this->m_raw_class = mc_class;
	this->m_handle = this->m_raw_class->mirror( );
	this->m_class = reinterpret_cast< jclass >( &this->m_handle );
}
