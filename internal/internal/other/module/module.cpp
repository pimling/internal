#include <windows.h>

#include "module.hpp"
#include "../hash/hash.hpp"
#include "../memory/memory.hpp"

c_module::c_module( )
{
	this->m_base = 0;
	this->m_size = 0;
}

c_module::c_module( const size_t base )
{
	this->m_base = base;
	this->m_size = 0;

	const auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( this->m_base );

	if ( !dos_header || dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return;

	const auto nt_header = reinterpret_cast< PIMAGE_NT_HEADERS >( this->m_base + dos_header->e_lfanew );

	if ( !nt_header || nt_header->Signature != IMAGE_NT_SIGNATURE )
		return;

	this->m_size = nt_header->OptionalHeader.SizeOfImage;

	const auto exports = reinterpret_cast< PIMAGE_EXPORT_DIRECTORY >( this->m_base + nt_header->OptionalHeader.DataDirectory->VirtualAddress );
	const auto names_addr = reinterpret_cast< unsigned int* >( this->m_base + exports->AddressOfNames );
	const auto ordinals_addr = reinterpret_cast< unsigned short* >( this->m_base + exports->AddressOfNameOrdinals );
	const auto functions_addr = reinterpret_cast< unsigned int* >( this->m_base + exports->AddressOfFunctions );

	for ( auto i = 0u; i < exports->NumberOfFunctions; i++ )
	{
		if ( i >= exports->NumberOfNames )
			break;

		auto name = reinterpret_cast< const char* >( this->m_base + names_addr[ i ] );
		this->m_exports[ c_hash::fnv( name ) ] = this->m_base + functions_addr[ ordinals_addr[ i ] ];
	}
}

size_t c_module::get_export( const size_t hash )
{
	return this->m_exports[ hash ];
}

size_t c_module::pattern_scan( const std::vector<unsigned char>& pattern )
{
	return c_memory::pattern_scan( this->m_base, pattern );
}
