#include <jni.h>

#include "../hook.hpp"
#include "../../../game/modules/modules.hpp"
#include "../../../other/hash/hash.hpp"
#include "../../feature/feature.hpp"
#include "../../../jvm/jvm.hpp"

class c_opengl_fn : public c_hook
{
	static void get_intv( JNIEnv* env, void* obj, int name, size_t params, size_t fptr )
	{
		const auto o = get_original( &get_intv );

		const auto context = std::make_shared<c_context>( env );
		c_feature::run_features( context );

		o( env, obj, name, params, fptr );
	}

public:
	c_opengl_fn( )
	{
		m_hooks.emplace_back( this );
	}

	bool hook( ) override
	{
		/* use this hook to get jni env if you wanna use jni */
		if ( !this->hook_fn( c_modules::m_lwjgl->get_export( hashxor( "Java_org_lwjgl_opengl_GL11_nglGetIntegerv" ) ), &get_intv ) )
			return false;

		return true;
	}

	bool unhook( ) override
	{
		if ( !this->unhook_fn( &get_intv ) )
			return false;

		return true;
	}
};

inline auto g_opengl_hooks = c_opengl_fn{ };