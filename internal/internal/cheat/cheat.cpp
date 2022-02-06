#include <thread>

#include "cheat.hpp"
#include "../other/util/wrapper.hpp"
#include "../jvm/jvm.hpp"
#include "../other/peb/peb.hpp"
#include "../game/modules/modules.hpp"
#include "../cheat/hook/hook.hpp"

void __stdcall c_cheat::start( const HMODULE module )
{
	m_module = module;

	AllocConsole( );
	FILE* f;
	freopen_s( &f, "CONOUT$", "w", stdout );

	if ( !c_peb::init( ) )
		goto kill;

	if ( !c_modules::init( ) )
		goto kill;

	if ( !c_hook::init( ) )
		goto kill;

	if ( !c_hook::init_hooks( ) )
		goto kill;

	c_jvm::init( );

	while ( true )
		std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

kill:
	FreeConsole( );

	c_hook::uninit_hooks( );
	c_hook::uninit( );

	c_wrapper::free_library( module );
}