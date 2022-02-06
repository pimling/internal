#include <windows.h>

#include "memory.hpp"

size_t c_memory::get_module_size( const size_t module )
{
	const auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module );

	if ( !dos_header || dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return 0;

	const auto nt_header = reinterpret_cast< PIMAGE_NT_HEADERS >( module + dos_header->e_lfanew );

	if ( !nt_header || nt_header->Signature != IMAGE_NT_SIGNATURE )
		return 0;

	return nt_header->OptionalHeader.SizeOfCode;
}

size_t c_memory::pattern_scan( const size_t module, const std::vector<unsigned char>& pattern )
{
	const auto base = reinterpret_cast< unsigned char* >( module );
	const auto size = get_module_size( module );

	if ( size == 0 )
		return 0;

	for ( auto i = 0; i < size - pattern.size( ); i++ )
	{
		auto found = true;

		for ( auto j = 0; j < pattern.size( ); j++ )
		{
			if ( base[ i + j ] != pattern[ j ] && pattern[ j ] != 0xff )
			{
				found = false;
				break;
			}
		}

		if ( found )
			return reinterpret_cast< size_t >( &base[ i ] );
	}

	return 0;
}
