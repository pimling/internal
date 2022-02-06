#include <intrin.h>
#include <windows.h>
#include <winternl.h>
#include <algorithm>
#include <string>

#include "peb.hpp"
#include "../hash/hash.hpp"

bool c_peb::init( )
{
	const auto peb = reinterpret_cast< PPEB >( __readgsqword( 0x60 ) ); // x64

	if ( !peb )
		return false;

	const auto entry = &peb->Ldr->InMemoryOrderModuleList;

	for ( auto mod = entry->Flink; mod != entry; mod = mod->Flink )
	{
		const auto ldr_entry = CONTAINING_RECORD( mod, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );

		if ( !ldr_entry )
			continue;

		const auto unicode_name = reinterpret_cast< PUNICODE_STRING >( &ldr_entry->Reserved4[ 0 ] );
		const auto wide_name = std::wstring( unicode_name->Buffer, unicode_name->Length >> 1 );
		auto name = std::string( wide_name.size( ), 0 );

		std::transform( wide_name.begin( ), wide_name.end( ), name.begin( ), [ & ] ( const wchar_t c ) {
			return std::tolower( static_cast< char >( c ) );
			} );

		m_modules[ c_hash::fnv( name ) ] = c_module{ reinterpret_cast< size_t >( ldr_entry->DllBase ) };
	}

	return true;
}

c_module* c_peb::get_module( const size_t hash )
{
	auto& entry = m_modules[ hash ];

	if ( !entry.base( ) )
		return nullptr;

	return &entry;
}
