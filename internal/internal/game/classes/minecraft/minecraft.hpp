#pragma once

#include <jni.h>

#include "../../../jvm/jvm.hpp"
#include "../../../jvm/types/instanceklass.hpp"

class c_minecraft
{
	c_instanceklass* m_class;

public:
	c_minecraft( c_instanceklass* mc_class );

	static c_minecraft get( );
};