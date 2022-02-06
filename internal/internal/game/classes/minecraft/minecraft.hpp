#pragma once

#include <jni.h>

#include "../../../jvm/types/instanceklass.hpp"

class c_minecraft
{
	c_instanceklass* m_raw_class;
	size_t m_handle;
	jclass m_class;

public:
	c_minecraft( c_instanceklass* mc_class );
};