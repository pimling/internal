#include "jvm.hpp"
#include "../other/util/lazy.hpp"
#include "../other/memory/memory.hpp"
#include "../game/modules/modules.hpp"
#include "types/classloaderdata.hpp"
#include "types/instanceklass.hpp"

#include <iostream>

void c_jvm::find_minecraft_class( c_instanceklass* klass )
{
	m_loaded_classes.emplace_back( klass );

	if ( !klass->methods( ) || klass->methods( )->length( ) <= 0 )
		return;

	for ( auto i = 0; i < klass->methods( )->length( ); i++ )
	{
		auto method = klass->methods( )->get( i );

		if ( !method )
			continue;

		auto sig = method->signature( );

		if ( !sig )
			continue;

		if ( sig->to_string( ).find( "()Lcom/mojang/authlib/minecraft/MinecraftSessionService;" ) != std::string::npos )
		{
			std::cout << klass->name( )->to_string( ) << std::endl;
			break;
		}
	}
}

void c_jvm::init( )
{  
	const auto offset = c_modules::m_jvm->pattern_scan( { 0x48, 0x8b, 0x05, 0xff, 0xff, 0xff, 0xff, 0x48, 0x85, 0xc0, 0x74, 0xff, 0x33, 0xc9, 0x66 } ) + 0x3;
	const auto addr = offset + *reinterpret_cast< std::uint32_t* >( offset ) + sizeof( std::uint32_t );

	c_classloaderdatagraph::m_head = *reinterpret_cast< c_classloaderdata** >( addr );

	for ( auto node = c_classloaderdatagraph::m_head; node; node = node->next( ) )
	{
		for ( auto klass = node->klass( ); klass; klass = klass->next_link( ) )
		{
			if ( !klass->is_instance( ) )
				continue;

			m_loaded_classes.emplace_back( klass );
			find_minecraft_class( klass );
		}
	}
}