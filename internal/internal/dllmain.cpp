#include <windows.h>

#include "other/util/wrapper.hpp"
#include "cheat/cheat.hpp"

BOOL APIENTRY DllMain( HMODULE module, DWORD  ul_reason_for_call, LPVOID reserved )
{
    if ( ul_reason_for_call == DLL_PROCESS_ATTACH )
    {
        if ( const auto thread = c_wrapper::create_thread( c_cheat::start, module ) )
            c_wrapper::close_handle( thread );
    }

    return TRUE;
}

