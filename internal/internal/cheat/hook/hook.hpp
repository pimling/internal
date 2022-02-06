#pragma once

#include <vector>
#include <algorithm>
#include <MinHook.h>

#include <fmt/core.h>

class c_hook
{
protected:
	bool m_hooked = false;

	template<typename K>
	bool hook_fn( size_t func, K hook )
	{
		if ( this->m_hooked )
			return false;

		this->m_func = func;
		this->m_hook = reinterpret_cast< size_t >( hook );
		this->m_original = 0;

		if ( MH_CreateHook( reinterpret_cast< void* >( this->m_func ), reinterpret_cast< void* >( this->m_hook ), reinterpret_cast< void** >( &this->m_original ) ) != MH_OK )
			return false;

		if ( MH_EnableHook( reinterpret_cast< void* >( this->m_func ) ) != MH_OK )
			return false;

		this->m_hooked = true;

		return true;
	}

	template<typename T>
	bool unhook_fn( T hook )
	{
		if ( !this->m_hooked )
			return false;

		const auto hk = std::find_if( m_hooks.begin( ), m_hooks.end( ), [ & ] ( c_hook* h ) {
			return ( h && h->m_hook == reinterpret_cast< size_t >( hook ) );
			} );

		if ( hk == m_hooks.end( ) )
			return false;

		if ( MH_DisableHook( reinterpret_cast< void* >( ( *hk )->m_func ) ) != MH_OK )
			return false;

		if ( MH_RemoveHook( reinterpret_cast< void* >( ( *hk )->m_func ) ) != MH_OK )
			return false;

		this->m_hooked = false;

		return true;
	}

	constexpr size_t original( ) 
	{
		return this->m_original;
	}

public:
	size_t m_func, m_hook, m_original;
	inline static std::vector<c_hook*> m_hooks{ };

	virtual bool hook( ) = 0;
	virtual bool unhook( ) = 0;

	template<typename T>
	static T get_original( T hook )
	{
		const auto stored_hook = std::find_if( m_hooks.begin( ), m_hooks.end( ), [ & ] ( const c_hook* h ) {
			return h->m_hook == reinterpret_cast< size_t >( hook );
			} );

		if ( stored_hook == m_hooks.end( ) )
			return 0;

		return reinterpret_cast< T >( ( *stored_hook )->m_original );
	}

	static bool init( ) 
	{
		return MH_Initialize( ) == MH_OK;
	}

	static bool init_hooks( )
	{
		for ( auto h : c_hook::m_hooks )
		{
			if ( !h->hook( ) )
				return false;
		}

		return true;
	}

	static bool uninit_hooks( )
	{
		for ( auto h : c_hook::m_hooks )
		{
			if ( !h->unhook( ) )
				return false;
		}

		return true;
	}

	static bool uninit( )
	{
		return MH_Uninitialize( ) == MH_OK;
	}
};