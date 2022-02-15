#pragma once

#include <jni.h>
#include <memory>

#include "../../game/classes/minecraft/minecraft.hpp"

class c_context
{
public:
	JNIEnv* m_env;

	c_context( JNIEnv* env )
		: m_env( env )
	{ }
};