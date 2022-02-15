#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <jni.h>

class c_instanceklass;

class c_jvm
{
	inline static std::vector<c_instanceklass*> m_loaded_classes{ };

	static void find_minecraft_class( c_instanceklass* klass );

public:
	inline static std::unordered_map<c_instanceklass*, jclass> m_mirrors{ };
	inline static c_instanceklass* m_mc_class = nullptr;

	static void init( );
};